﻿#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Define.h"
#include "PiranhaPlant.h"
#include "VenusFireTrap.h"
#include "Pipe.h"
#include "Coin.h"
#include "ScoreEffect.h"
#include "LastItem.h"
#include "P_Switch.h"
#include "Lift.h"
#include "BoomerangBrother.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	playTimer->Start();
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#pragma region PARSESECTION	AND LOAD
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
	for (size_t i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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
void CPlayScene::_ParseSection_OBJECTS(string line)
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
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}

		obj = CMario::GetInstance();
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		obj->SetAnimationSet(ani_set);
		if (CMario::GetInstance()->tail)
			CMario::GetInstance()->tail->SetAnimationSet(CAnimationSets::GetInstance()->Get(1));
		player = (CMario*)obj;
		float px, py;
		player->GetWorldMapPosition(px, py);
		player->SetStage(this->id);
		player->Refresh();

		hud = new CHUD();

		DebugOut(L"[INFO] Player object created!\n");
		break;
	}
	case OBJECT_TYPE_GOOMBA: 
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int gtype = atoi(tokens[4].c_str());
		int top = atoi(tokens[5].c_str());
		int bot = atoi(tokens[6].c_str());
		int left = atoi(tokens[7].c_str());
		int right = atoi(tokens[8].c_str());
		obj = new CGoomba(gtype);
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set); 
		listMoving.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridMoving->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_COIN:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new CCoin();
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set); 
		listStatic.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridStatic->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_LAST_ITEM:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new CLastItem();
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set); 
		listStatic.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridStatic->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_BRICK: 
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int btype = atoi(tokens[4].c_str());
		int contain = atoi(tokens[5].c_str());
		int sl = atoi(tokens[6].c_str());
		int top = atoi(tokens[7].c_str());
		int bot = atoi(tokens[8].c_str());
		int left = atoi(tokens[9].c_str());
		int right = atoi(tokens[10].c_str());
		obj = new CBrick( x,y , btype, contain, sl); 
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set); 
		listStatic.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridStatic->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_LIFT:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new CLift();
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		listMoving.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridMoving->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_BOOMERANG_BROTHER:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new CBoomerangBrother(x, y);
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		listMoving.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridMoving->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_VENUS_FIRE_TRAP:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int t = atoi(tokens[4].c_str());
		int top = atoi(tokens[5].c_str());
		int bot = atoi(tokens[6].c_str());
		int left = atoi(tokens[7].c_str());
		int right = atoi(tokens[8].c_str());
		obj = new CVenusFireTrap(x, y, t);
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set); 
		listMoving.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridMoving->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_PIRANHA_PLANT:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int top = atoi(tokens[4].c_str());
		int bot = atoi(tokens[5].c_str());
		int left = atoi(tokens[6].c_str());
		int right = atoi(tokens[7].c_str());
		obj = new CPiranhaPlant(x, y);
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set); 
		listMoving.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridMoving->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_KOOPAS: 
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int type = atoi(tokens[4].c_str());
		int top = atoi(tokens[5].c_str());
		int bot = atoi(tokens[6].c_str());
		int left = atoi(tokens[7].c_str());
		int right = atoi(tokens[8].c_str());
		obj = new CKoopas(type, x,y);
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set); 
		listMoving.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridMoving->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		float r = strtof(tokens[4].c_str(), NULL);
		float b = strtof(tokens[5].c_str(), NULL);
		int scene_id = atoi(tokens[6].c_str());
		float des_x = strtof(tokens[7].c_str(), NULL);
		float des_y = strtof(tokens[8].c_str(), NULL);
		int top = atoi(tokens[9].c_str());
		int bot = atoi(tokens[10].c_str());
		int left = atoi(tokens[11].c_str());
		int right = atoi(tokens[12].c_str());
		obj = new CPortal(x, y, r, b, scene_id, { des_x, des_y });
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set); 
		listStatic.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridStatic->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_GROUND:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int w = atoi(tokens[4].c_str());
		int h = atoi(tokens[5].c_str());
		int i = atoi(tokens[6].c_str());
		int top = atoi(tokens[7].c_str());
		int bot = atoi(tokens[8].c_str());
		int left = atoi(tokens[9].c_str());
		int right = atoi(tokens[10].c_str());
		obj = new CGround(w, h, i);
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		listStatic.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridStatic->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	case OBJECT_TYPE_PIPE:
	{
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
		int t = atoi(tokens[4].c_str());
		int hasPortal = atoi(tokens[5].c_str());
		float des_x = strtof(tokens[6].c_str(), NULL);
		float des_y = strtof(tokens[7].c_str(), NULL);
		int dir = atoi(tokens[8].c_str());
		int top = atoi(tokens[9].c_str());
		int bot = atoi(tokens[10].c_str());
		int left = atoi(tokens[11].c_str());
		int right = atoi(tokens[12].c_str());
		obj = new CPipe(t, hasPortal, { des_x, des_y }, dir);
		obj->SetPosition(x, y);
		obj->SetAnimationSet(ani_set);
		listStatic.push_back(obj);
		for (int row = top; row < bot; row++)
		{
			for (int col = left; col < right; col++)
				gridStatic->pushObjIntoGrid(obj, row, col);
		}
		break;
	}
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
	cam = CCamera::GetInstance();
}

/*
	Parse a line in section [TILE_MAP]
*/
void CPlayScene::_ParseSection_TILE_MAP(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 13) return; // skip invalid lines - an object set must have at least id, x, y

	int ID = atoi(tokens[0].c_str());

	wstring FilePath_tex = ToWSTR(tokens[1]);
	wstring FilePath_data = ToWSTR(tokens[2]);

	int Map_height = atoi(tokens[3].c_str());
	int Map_width = atoi(tokens[4].c_str());
	int Num_row_read = atoi(tokens[5].c_str());
	int Num_col_read = atoi(tokens[6].c_str());
	int Tile_width = atoi(tokens[7].c_str());
	int Tile_height = atoi(tokens[8].c_str());
	float main_start = strtof(tokens[9].c_str(), NULL);
	float main_end = strtof(tokens[10].c_str(), NULL);
	float hidden_start = strtof(tokens[11].c_str(), NULL);
	float hidden_end = strtof(tokens[12].c_str(), NULL);

	map = new CTileMap(ID, FilePath_tex.c_str(), FilePath_data.c_str(), Map_height, Map_width, Num_row_read, Num_col_read, Tile_width, Tile_height, main_start, main_end, hidden_start, hidden_end);
	if (map)
	{
		gridMoving = new CGrid(map->GetNumsCols(), map->GetNumsRows(), CELL_WIDTH, CELL_HEIGHT);
		gridStatic = new CGrid(map->GetNumsCols(), map->GetNumsRows(), CELL_WIDTH, CELL_HEIGHT);
		DebugOut(L"create GRID\n");
	}
	DebugOut(L"[INFO] DONE LOAD MAP! \n");
}
//load object/ textures/ sprites -> animations
void CPlayScene::Load()
{
	if (playTimer)
		playTimer->Reset();
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
#pragma endregion

void CPlayScene::Update(ULONGLONG dt)
{
	gridMoving->ResetCamGrid(listMoving);
	gridStatic->ResetCamGrid(listStatic);
	GetObjectGrid();

	if(player->GetState()!=MState::Die)
		this->remainingTime = PLAY_TIME - (int)((GetTickCount64() - playTimer->GetStartTime())/ MINISEC_PER_SEC);
	if (this->remainingTime < 0)
	{
		player->SetState(MState::Die);
		this->remainingTime = 0;
	}

	//duyet list object
	for (size_t i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == Type::BRICK)
		{
			CBrick* brick = dynamic_cast<CBrick*>(listObj[i]);
			//push vao listitem
			if (brick->GetBrickType() == BrickType::bronze && brick->GetState() == BRICK_STATE_HIDDEN)
				listItem.push_back(brick);
			if (brick->diddropItem)
			{
				brick->diddropItem = false;
				//RANDOM ITEM
				CItem* item;
				if (brick->containItem == 4)
				{
					item = new CSuperMushroom({ brick->x, brick->y - 16 }, ItemID::upMushroom);
				}
				else
				{
					if (player->GetLevel() >= Level::Big)
						item = new CSuperLeaf({ brick->x, brick->y - 16 });
					else
						item = new CSuperMushroom({ brick->x, brick->y - 16 }, ItemID::superMushroom);
				}
				if (item != NULL)
				{
					listItem.push_back(item);
					/*listMoving.push_back(listObj[i]);
					gridMoving->pushNewObjIntoGrid(listObj[i]);*/
				}
			}
		}
	}
#pragma region xu ly tien bien thanh gach va gach thanh tien
	//xoa ra khoi list object
	for (size_t i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == Type::BRICK)
		{
			CBrick* brick = dynamic_cast<CBrick*>(listObj[i]);
			if (brick->GetBrickType() == BrickType::bronze && brick->GetState() == BRICK_STATE_HIDDEN)
			{
				listObj.erase(listObj.begin() + i);
				i--;
			}
		}
	}

	//them vao objectsect
	for (size_t i = 0; i < listItem.size(); i++)
	{
		if (listItem[i]->GetType() == Type::BRICK)
		{
			CBrick* brick = dynamic_cast<CBrick*>(listItem[i]);
			//push vao listitem
			if (brick->GetBrickType() == BrickType::bronze && brick->GetState() != BRICK_STATE_HIDDEN)
				listObj.push_back(brick);
		}
	}

	//xoa ra khoi list Item
	for (size_t i = 0; i < listItem.size(); i++)
	{
		if (listItem[i]->GetType() == Type::BRICK)
		{
			CBrick* brick = dynamic_cast<CBrick*>(listItem[i]);
			if (brick->GetBrickType() == BrickType::bronze && brick->GetState() != BRICK_STATE_HIDDEN)
			{
				listItem.erase(listItem.begin() + i);
				i--;
			}
		}
	}
#pragma endregion

	//update
	for (size_t i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == Type::PIRANHA_PLANT || listObj[i]->GetType() == Type::VENUS_FIRE_TRAP)
		{
			float l, t, r, b;
			player->GetBoundingBox(l, t, r, b);
			CPlant* plant = dynamic_cast<CPlant*>(listObj[i]);
			plant->Update(dt, &listObj, { l,t,r,b });
		}
		else if (listObj[i]->GetType() == Type::P_SWITCH)
		{
			CP_Switch* PSwitch = dynamic_cast<CP_Switch*>(listObj[i]);
			PSwitch->Update(dt, &listObj, &listItem);
		}
		else
			listObj[i]->Update(dt, &listObj);
	}
	for (size_t i = 0; i < listItem.size(); i++)
	{
		listItem[i]->Update(dt, &listObj);
	}

	////mario
	player->Update(dt, &listObj, &listItem, &listEffect);

	for (size_t i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == Type::P_SWITCH && !listObj[i]->isInCam)
		{
			listObj[i]->isInCam = true;
			listStatic.push_back(listObj[i]);
			gridStatic->pushNewObjIntoGrid(listObj[i]);
		}
		if (listObj[i]->GetType() == Type::VENUS_FIRE_BALL && !listObj[i]->isInCam)
		{
			listObj[i]->isInCam = true;
			listMoving.push_back(listObj[i]);
			gridMoving->pushNewObjIntoGrid(listObj[i]);
		}
	}
	for (size_t i = 0; i < listItem.size(); i++)
	{
		if (!listItem[i]->isInCam)
		{
			listItem[i]->isInCam = true;
			listMoving.push_back(listItem[i]);
			gridMoving->pushNewObjIntoGrid(listItem[i]);
		}
	}


	//them effect dan cho mario
	for (size_t i = 0; i < player->listBullet.size(); i++)
	{
		if (player->listBullet[i]->GetState() == STATE_DESTROYED)
		{
			float bx, by;
			player->listBullet[i]->GetPosition(bx, by);
			//CEffect* effect = new CEffect({ bx, by }, EffectType::fireBall);
			CGameObject* effect = new CEffect({ bx, by }, EffectType::fireBall);
			listEffect.push_back(effect);
		}
	}

	//xoa vien dan bien mat
	for (size_t i = 0; i < player->listBullet.size(); i++)
		if (player->listBullet[i]->GetState() == STATE_DESTROYED || player->listBullet[i]->IsOutOfCamera())
		{
			player->listBullet.erase(player->listBullet.begin() + i);
			i--;
		}

	//them effect
	for (size_t i = 0; i < listEffect.size(); i++)
	{
		listEffect[i]->Update(dt);
		//if coin
		if (listEffect[i]->GetType() == Type::COIN && listEffect[i]->GetState() == STATE_DESTROYED)
		{
			float bx, by;
			listEffect[i]->GetPosition(bx, by);
			CGameObject* effect = new CScoreEffect({ bx, by }, 100);
			listEffect.push_back(effect);
		}
		if (dynamic_cast<CEffect*>(listEffect[i]))
		{
			CEffect* effect = dynamic_cast<CEffect*>(listEffect[i]);
			if (effect->GetEffectType() == EffectType::text && effect->GetState() == STATE_DESTROYED)
				player->canSwitchScene = true;
		}	
	}

	//xoa obj co state = STATE_DESTROYED
	for (size_t i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetState() == STATE_DESTROYED)
		{
			listObj.erase(listObj.begin() + i);
			i--;
		}
	}
	for (size_t i = 0; i < listItem.size(); i++)
	{
		if (listItem[i]->GetState() == STATE_DESTROYED|| (listItem[i]->IsOutOfCamera() && listItem[i]->GetType()==Type::ITEM))
		{
			listItem.erase(listItem.begin() + i);
			i--;
		}
	}
	for (size_t i = 0; i < listEffect.size(); i++)
	{
		if (listEffect[i]->GetState() == STATE_DESTROYED/*|| listObj[i]->IsOutOfCamera()*/)
		{
			listEffect.erase(listEffect.begin() + i);
			i--;
		}
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

#pragma region Xu ly camera va ngan mario ko roi ra khoi map
	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	if (player->GetState() == MState::Die)
		cam->LockUpdate();
	if(cam->IsLockUpdate() && player->GetState() != MState::Die)
		cam->UnlockUpdate();

	if (!player->inHiddenArea)
	{
		if (this->id == ID_SCENE_4)
			cam->UnlockUpdateVx();
		if (player->keyLockCam)
			cam->LockUpdateVx();

		cam->Update(dt, { cx,cy }, { 0,0 }, { float(map->mainEnd_x - SCREEN_WIDTH) , float(map->GetMapHeight() - SCREEN_HEIGHT + 64) }, player->isFlying, player->isOnGround);

		//xet mario khong ra khoi MAP CHINH
		if (cam->IsLockUpdateVx() && player->x < map->mainStart_x)
			player->SetPosition(map->mainStart_x, cy);
		if (!cam->IsLockUpdateVx() && player->x < cam->GetPositionX())
			player->SetPosition(cam->GetPositionX(), cy);
		if (!cam->IsLockUpdateVx() && player->x > cam->GetPositionX() + SCREEN_WIDTH - MARIO_BIG_BBOX_WIDTH)
			player->SetPosition(cam->GetPositionX() + SCREEN_WIDTH - MARIO_BIG_BBOX_WIDTH, cy);
		if (!player->isAutoGo && player->x > map->mainEnd_x - MARIO_BIG_BBOX_WIDTH*2)
			player->SetPosition(map->mainEnd_x - MARIO_BIG_BBOX_WIDTH*2, cy);
	}
	else
	{
		if (!cam->IsLockUpdateVx())
			cam->LockUpdateVx();
		cam->Update(dt, { cx,cy }, { map->hiddenStart_x,0 }, { float(map->hiddenEnd_x/*3360*/ - SCREEN_WIDTH) , float(map->GetMapHeight()- SCREEN_HEIGHT + 64) }, player->isFlying, player->isOnGround);
		
		//xet mario khong ra khoi MAP AN
		if (player->x < map->hiddenStart_x)
			player->SetPosition(map->hiddenStart_x, cy);
		if (!player->isAutoGo && player->x > map->hiddenEnd_x - MARIO_BIG_BBOX_WIDTH * 2)
			player->SetPosition(map->hiddenEnd_x - MARIO_BIG_BBOX_WIDTH * 2, cy);
	}
#pragma endregion

	//effect endscene
	if (player->isAutoGo && player->IsOutOfCamera())
	{
		CGameObject* effect;
		if (!player->inHiddenArea)
			effect = new CEffect({ map->mainEnd_x - (SCREEN_WIDTH / 2) - 68, 270 }, EffectType::text);
		else
			effect = new CEffect({ map->hiddenEnd_x - (SCREEN_WIDTH / 2) - 68, 270 }, EffectType::text);
		listEffect.push_back(effect);
	}

	gridMoving->UpdateGrid(listMoving);
	//chuyen scene
	if(player->canSwitchScene)
		CGame::GetInstance()->SwitchScene(ID_SCENE_WORLD_MAP);
}

void CPlayScene::GetObjectGrid()
{
	listItem.clear();
	listObj.clear();
	listGet.clear();

	gridMoving->GetObjFromGrid(listGet);
	gridStatic->GetObjFromGrid(listGet);

	for (UINT i = 0; i < listGet.size(); i++)
	{
		if (listGet[i]->GetType() == Type::COIN || listGet[i]->GetType() == Type::LAST_ITEM|| listGet[i]->GetType() == Type::ITEM)
			listItem.push_back(listGet[i]);
		else
			listObj.push_back(listGet[i]);
	}
}

void CPlayScene::Render()
{
	if (map)map->Draw();
	for (size_t i = 0; i < listObj.size(); i++)
		/*if (listObj.at(i) != NULL)*/
		if(listObj.at(i)->GetType()!=Type::VENUS_FIRE_BALL || listObj.at(i)->GetType() != Type::LIFT || listObj.at(i)->GetType() != Type::BOOMERANG_BROTHER)
			listObj[i]->Render();
	for (size_t i = 0; i < listObj.size(); i++)
		if (listObj.at(i)->GetType() == Type::VENUS_FIRE_BALL || listObj.at(i)->GetType() == Type::LIFT|| listObj.at(i)->GetType() == Type::BOOMERANG_BROTHER)
			listObj[i]->Render();
	for (size_t i = 0; i < listItem.size(); i++)
		if (listItem.at(i) != NULL)
			listItem.at(i)->Render();
	for (size_t i = 0; i < listEffect.size(); i++)
		listEffect.at(i)->Render();
	player->Render();
	hud->Render({ CGame::GetInstance()->GetCamPosX(), CGame::GetInstance()->GetCamPosY() }, player, remainingTime, this->id);
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (size_t i = 0; i < listItem.size(); i++)
		delete listItem[i];
	listItem.clear();

	for (size_t i = 0; i < listObj.size(); i++)
		delete listObj[i];
	listObj.clear();

	for (size_t i = 0; i < listEffect.size(); i++)
		delete listEffect[i];
	listEffect.clear();

	player = NULL;
	delete hud;
	delete gridMoving;
	delete gridStatic;

	gridMoving = NULL;
	gridStatic = NULL;

	if(cam) cam->ResetPosition();
	//delete cam;
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario->GetState() == MState::Die && KeyCode !=DIK_F1)
		return;
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
	case DIK_F1:
		mario->Reset();
		CGame::GetInstance()->cam_x = 0;
		break;
	case DIK_1:
		mario->Small();
		CGame::GetInstance()->cam_x = 0;
		break;
	case DIK_2:
		mario->Big();
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
	case DIK_SPACE:
		mario->keyLockCam = !mario->keyLockCam;
		break;
	case DIK_A:
		if (!mario->isAttack)
		{
			if (mario->GetLevel() == Level::Fire || mario->GetLevel() == Level::Raccoon)
				mario->Attack();
		}
		break;

	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario->GetState() == MState::Die)
		return;
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
		mario->canHoldShell = false;
		break;
	case DIK_SPACE:
		break;
	case DIK_RIGHT:
		mario->nx = 1;
		break;
	case DIK_LEFT:
		mario->nx = -1;
		break;
	}	
}

void CPlayScenceKeyHandler::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();

	if (mario->GetState() == MState::Die)
		return;
	if (mario->isAutoGo)
		return;
	if (mario->isWaitingForAni)
		return;
	if (game->IsKeyDown(DIK_A))
		mario->canHoldShell = true;

	if (game->IsKeyDown(DIK_UP))
	{
		mario->canGoThroughPipe_Up = true;
	}
	else
	{
		mario->canGoThroughPipe_Up = false;
	}

	if (game->IsKeyDown(DIK_DOWN))
	{
		mario->canGoThroughPipe_Down = true;
	}
	else
	{
		mario->canGoThroughPipe_Down = false;
	}

	if (mario->isOnGround)
	{
		if ((game->IsKeyDown(DIK_LEFT) && game->IsKeyDown(DIK_RIGHT))//bo nay vao thi render idle khi dang stop 
			|| (game->IsKeyDown(DIK_DOWN) && game->IsKeyDown(DIK_UP)))
		{
			mario->Idle();
			//DebugOut(L"NX: %d\n", mario->nx);
		}
		else if (game->IsKeyDown(DIK_A) && game->IsKeyDown(DIK_RIGHT))
		{
			if (mario->vx < 0)
			{
				mario->nx = 1;
				mario->Stop();
			}
			else
				mario->SetState(MState::Run_right);
		}
		else if (game->IsKeyDown(DIK_A) && game->IsKeyDown(DIK_LEFT))
		{
			if (mario->vx > 0)
			{
				mario->nx = -1;
				mario->Stop();
			}
			else
				mario->SetState(MState::Run_left);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (mario->vx > 0)
			{
				mario->nx = -1;
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
				mario->nx = 1;
				mario->Stop();
			}
			else
			{
				mario->WalkingRight();
			}
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			if (mario->GetLevel() != Level::Small && !mario->isHolding)
			{
				mario->Sit();
			}
			else
				mario->Idle();
		}
		else if(!mario->isAutoGo) mario->Idle();
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