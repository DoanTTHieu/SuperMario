#include <iostream>
#include <fstream>

#include "Utils.h"
#include "Sprites.h"
#include "Portal.h"
#include "Define.h"
#include "WorldMapScene.h"

using namespace std;

CWorldMapScene::CWorldMapScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CWorldMapScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/


void CWorldMapScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CWorldMapScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CWorldMapScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (size_t i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CWorldMapScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (size_t i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CWorldMapScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = strtof(tokens[1].c_str(), NULL);
	float y = strtof(tokens[2].c_str(), NULL);

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = CMario::GetInstance();
		player = (CMario*)obj;
		player->SetStage(this->id);
		player->Refresh();
		float px, py;
		player->GetWorldMapPosition(px, py);
		if (px == -1 && py == -1)
			player->SetPosition(x, y);
		else
			player->SetPosition(px, py);
		hud = new CHUD();

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_MAP_POINT:
	{
		int Portal = atoi(tokens[4].c_str());
		int idscene = atoi(tokens[5].c_str());
		int l = atoi(tokens[6].c_str());
		int r = atoi(tokens[7].c_str());
		int a = atoi(tokens[8].c_str());
		int u = atoi(tokens[9].c_str());
		obj = new CMapPoint(Portal, idscene, l, r, a, u);
		obj->SetPosition(x, y);
	}
		break;
	case OBJECT_WORLD_MAP_OBJ:
	{
		int t = atoi(tokens[4].c_str());
		obj = new CWorldMapObject(t);
		obj->SetPosition(x, y);
	}
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	/*obj->SetPosition(x, y);*/
	obj->GetPosition(obj->start_x, obj->start_y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);

	//list obj pushback
	switch (obj->GetType())
	{
	case Type::WM_OBJECT:
	case Type::MAP_POINT:
		listObj.push_back(obj);
		break;

	}
}

/*
	Parse a line in section [TILE_MAP]
*/
void CWorldMapScene::_ParseSection_TILE_MAP(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 9) return; // skip invalid lines - an object set must have at least id, x, y

	int ID = atoi(tokens[0].c_str());

	wstring FilePath_tex = ToWSTR(tokens[1]);
	wstring FilePath_data = ToWSTR(tokens[2]);

	int Map_width = atoi(tokens[3].c_str());
	int Map_height = atoi(tokens[4].c_str());
	int Num_row_read = atoi(tokens[5].c_str());
	int Num_col_read = atoi(tokens[6].c_str());
	int Tile_width = atoi(tokens[7].c_str());
	int Tile_height = atoi(tokens[8].c_str());

	map = new CTileMap(ID, FilePath_tex.c_str(), FilePath_data.c_str(), Map_width, Map_height, Num_row_read, Num_col_read, Tile_width, Tile_height);
}

//load object/ textures/ sprites -> animations
void CWorldMapScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[TILEMAP]") {
			section = SCENE_SECTION_TILE_MAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_TILE_MAP: _ParseSection_TILE_MAP(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
	CGame::GetInstance()->SetCamPos(0, 0);
}

void CWorldMapScene::Update(ULONGLONG dt)
{
	//mario
	player->Update(dt, &listObj);

	for (size_t i = 0; i < listObj.size(); i++)
	{
		listObj[i]->Update(dt, &listObj);
	}

	//skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
	
}

void CWorldMapScene::Render()
{
	map->Draw();
	for (size_t i = 0; i < listObj.size(); i++)
	{
		listObj[i]->Render();
	}
	player->Render();
	hud->Render({ CGame::GetInstance()->GetCamPosX(), CGame::GetInstance()->GetCamPosY() }, player,0, this->id);
}

/*
	Unload current scene
*/
void CWorldMapScene::Unload()
{
	for (size_t i = 0; i < listObj.size(); i++)
		delete listObj[i];
	listObj.clear();

	player = NULL;
	delete hud;
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CWorldMapScenceKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CWorldMapScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_RIGHT:
		if(mario->isIdling && mario->canWalkRight)
			mario->SetState(MState::Walk_right);
		break;
	case DIK_LEFT:
		if (mario->isIdling && mario->canWalkLeft)
			mario->SetState(MState::Walk_left);
		break;
	case DIK_UP:
		if (mario->isIdling && mario->canWalkUp)
			mario->SetState(MState::Walk_up);
		break;
	case DIK_DOWN:
		if (mario->isIdling && mario->canWalkDown)
			mario->SetState(MState::Walk_down);
		break;
	}

}

void CWorldMapScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CWorldMapScene*)scence)->GetPlayer();

	if (game->IsKeyDown(DIK_S))
	{
		mario->canSwitchScene = true;
	}
	else
	{
		mario->canSwitchScene = false;
	}
}
