#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Define.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/


void CPlayScene::_ParseSection_TEXTURES(string line)
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

void CPlayScene::_ParseSection_SPRITES(string line)
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

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
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
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

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
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick({ x,y }); break;
	case OBJECT_TYPE_KOOPAS: 
	{
		int type = atof(tokens[4].c_str());
		obj = new CKoopas(type); 
	}
	break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	case OBJECT_TYPE_GROUND:
	{
		int w = atof(tokens[4].c_str());
		int h = atof(tokens[5].c_str());
		int i = atof(tokens[6].c_str());
		obj = new CGround(w, h, i);
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

/*
	Parse a line in section [TILE_MAP]
*/
void CPlayScene::_ParseSection_TILE_MAP(string line)
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
void CPlayScene::Load()
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
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	//xoa may cai da chet
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetState() == STATE_DESTROYED/*|| objects[i]->IsOutOfCamera()*/)
		{
			objects.erase(objects.begin() + i);
			i--;
		}
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	//CGame* game = CGame::GetInstance();
	//cx -= game->GetScreenWidth() / 2;
	//cy -= game->GetScreenHeight() / 2;

	//CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	//map di theo nhan vat, ko di qua map
	
	//CGame::GetInstance()->cam_y = 250;
	if (player->x > (SCREEN_WIDTH / 2) && player->x + (SCREEN_WIDTH / 2) < map->GetMapWidth())
	{
		cx = player->x - (SCREEN_WIDTH / 2);
		CGame::GetInstance()->cam_x = cx;
	}
	CGame::GetInstance()->cam_y = 250;
	//if (player->y > (SCREEN_HEIGHT / 2) && player->y + (SCREEN_HEIGHT / 2) < map->GetMapHeight())
	//{
	//	cy = player->y - (SCREEN_HEIGHT / 2);
	//	CGame::GetInstance()->cam_y = cy;
	//}
	//else
	//{
	//	CGame::GetInstance()->cam_y = 250;
	//}
	
}

void CPlayScene::Render()
{
	map->Draw();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if (mario->GetLevel() == Level::Raccoon && abs(mario->vx) == MARIO_RUN_SPEED_THRESH)
			mario->Fly();
		else
		{
			if (mario->isOnGround)
			{
				mario->Jump();
			}
		}
			
		if (mario->GetLevel() == Level::Raccoon && mario->vy > 0)
		{
			mario->isWaggingTail = true;
		}
		break;
	case DIK_X:
		if (mario->isOnGround)
			mario->JumpX();
		break;
	case DIK_2:
		mario->Reset();
		CGame::GetInstance()->cam_x = 0;
		break;
	case DIK_3:
		mario->Raccoon();
		CGame::GetInstance()->cam_x = 0;
		break;
	case DIK_4:
		mario->FireMario();
		CGame::GetInstance()->cam_x = 0;
		break;
	case DIK_A:
		if (mario->GetLevel() == Level::Fire|| mario->GetLevel() == Level::Raccoon)
			mario->Attack();
		break;

	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if (mario->isblockJump == true)
			return;

		if (!mario->flyTimer->IsTimeUp())
		{	
			mario->vy = -(MARIO_GRAVITY+0.002f*4) * mario->dt;
			/*if (mario->GetLevel() == Level::Raccoon)*/
				//mario->vy = mario->vy - MARIO_GRAVITY * 10 * mario->dt;
			/*else
				mario->vy = MARIO_JUMP_SPEED_Y*1.5f;*/
		}
		else 
		{
			//if(mario->GetLevel() == Level::Raccoon)
				mario->vy = 0;
			//else
				//mario->vy = mario->vy + MARIO_GRAVITY * mario->dt;
				
				//mario->vy = +(MARIO_GRAVITY + 0.002f * 4) * mario->dt;
		}
		
		if (mario->GetLevel() == Level::Raccoon)
		{
			mario->isblockJump = false;
		}
		else
		{
			mario->isblockJump = true;
		}
		mario->isWaggingTail = false;
		
		break;
	case DIK_DOWN:
		if(mario->isOnGround)
			mario->isSitting = false;
		break;
	case DIK_A:
		break;
	case DIK_SPACE:
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	if (mario->GetState() == MState::Die)
		return;
	if (mario->isWaitingForAni)
		return;

	if (mario->isOnGround)
	{
		if ((game->IsKeyDown(DIK_LEFT) && game->IsKeyDown(DIK_RIGHT))//bo nay vao thi render idle khi dang stop 
			|| (game->IsKeyDown(DIK_DOWN) && game->IsKeyDown(DIK_UP)))
		{
			mario->Idle();
		}
		else if (game->IsKeyDown(DIK_A) && game->IsKeyDown(DIK_RIGHT))
		{
			if (mario->vx < 0)
			{
				mario->Stop();
			}
			else
				mario->SetState(MState::Run_right);
		}
		else if (game->IsKeyDown(DIK_A) && game->IsKeyDown(DIK_LEFT))
		{

			if (mario->vx > 0)
			{
				mario->Stop();
			}
			else
				mario->SetState(MState::Run_left);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (mario->vx > 0)
			{
				mario->Stop();
			}
			else
			{
				mario->WalkingLeft();
			}
		}
		else if (game->IsKeyDown(DIK_RIGHT))
		{	
			if (mario->vx < 0)
			{
				mario->Stop();
			}
				
			else
			{
				mario->WalkingRight();
			}

		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			if (mario->GetLevel() != Level::Small)
			{
				mario->Sit();
			}
			else
				mario->Idle();
		}
		else mario->Idle();
	}
	else
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			mario->ToRight();
		}
		if (game->IsKeyDown(DIK_LEFT))
		{
			mario->ToLeft();
		}

	}
	
}