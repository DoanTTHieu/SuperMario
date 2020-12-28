#include <iostream>
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

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	playTimer->Start();
	DebugOut(L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaa: %d\n", id);
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
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		//obj = new CMario(x, y);
		//player = (CMario*)obj;
		// Add simon

		obj = CMario::GetInstance();
		player = (CMario*)obj;
		player->SetStage(this->id);

		player->SetPosition(x, y);
		hud = new CHUD();

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: 
	{
		int gtype = atoi(tokens[4].c_str());
		obj = new CGoomba(gtype);
		if (gtype==2) DebugOut(L"red para goobaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa!\n");
	}
	break;
	case OBJECT_TYPE_COIN:
	{
		obj = new CCoin();
	}
	break;
	case OBJECT_TYPE_LAST_ITEM:
	{
		obj = new CLastItem();
		DebugOut(L"noooooooooooooooooooooooooooooooooooooo!\n");
	}
	break;
	case OBJECT_TYPE_BRICK: 
	{
		int btype = atoi(tokens[4].c_str());
		int contain = atoi(tokens[5].c_str());
		int sl = atoi(tokens[6].c_str());
		obj = new CBrick( x,y , btype, contain, sl); 
	}
	break;
	case OBJECT_TYPE_VENUS_FIRE_TRAP:
	{
		int t = atoi(tokens[4].c_str());
		obj = new CVenusFireTrap(x, y, t);
	}
	break;
	case OBJECT_TYPE_PIRANHA_PLANT:
	{
		obj = new CPiranhaPlant(x, y);
	}
	break;
	case OBJECT_TYPE_KOOPAS: 
	{
		int type = atoi(tokens[4].c_str());
		obj = new CKoopas(type);
	}
	break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = strtof(tokens[4].c_str(), NULL);
		float b = strtof(tokens[5].c_str(), NULL);
		int scene_id = atoi(tokens[6].c_str());
		float des_x = strtof(tokens[7].c_str(), NULL);
		float des_y = strtof(tokens[8].c_str(), NULL);
		obj = new CPortal(x, y, r, b, scene_id, { des_x, des_y });
	}
	break;
	case OBJECT_TYPE_GROUND:
	{
		int w = atoi(tokens[4].c_str());
		int h = atoi(tokens[5].c_str());
		int i = atoi(tokens[6].c_str());
		obj = new CGround(w, h, i);
	}
	break;
	case OBJECT_TYPE_PIPE:
	{
		int t = atoi(tokens[4].c_str());
		int hasPortal = atoi(tokens[5].c_str());
		float des_x = strtof(tokens[6].c_str(), NULL);
		float des_y = strtof(tokens[7].c_str(), NULL);
		int dir = atoi(tokens[8].c_str());
		DebugOut(L"d2: %d\n", dir);
		obj = new CPipe(t, hasPortal, { des_x, des_y }, dir);
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
	
	switch (obj->GetType())
	{
	case Type::BRICK:
	case Type::GROUND:
	case Type::PORTAL:
	case Type::PIPE:
	case Type::VENUS_FIRE_TRAP:
	case Type::PIRANHA_PLANT:
	case Type::KOOPAS:
	case Type::GOOMBA:
		listObj.push_back(obj);
		break;
	case Type::COIN:
	case Type::LAST_ITEM:
		listItem.push_back(obj);
		break;
	}
	//hud = CHUD::GetInstance();
	cam = CCamera::GetInstance();
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

void CPlayScene::Update(ULONGLONG dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	//	//mario
	//player->Update(dt, &listObj, &listItem);

	if(player->GetState()!=MState::Die)
		this->remainingTime = PLAY_TIME - (int)((GetTickCount64() - playTimer->GetStartTime())/ MINISEC_PER_SEC);
	
	//duyet list object
	for (size_t i = 0; i < listObj.size(); i++)
	{
		if (listObj[i]->GetType() == Type::BRICK)
		{
			CBrick* brick = dynamic_cast<CBrick*>(listObj[i]);
			if (brick->diddropItem)
			{
				brick->diddropItem = false;
				//RANDOM ITEM
				CItem* item;
				if(player->GetLevel()>=Level::Big)
					item = new CSuperLeaf({ brick->x, brick->y - 16 });
				else 
					item = new CSuperMushroom({ brick->x, brick->y - 16 });
				if(item!=NULL)
					listItem.push_back(item);
			}
		}
		
	}

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
		else
			listObj[i]->Update(dt, &listObj);
	}
	for (size_t i = 0; i < listItem.size(); i++)
	{
		listItem[i]->Update(dt, &listObj);
	}

	////mario
	player->Update(dt, &listObj, &listItem, &listEffect);

	if (player->isAutoGo && player->IsOutOfCamera())
	{
		//CGameObject* effect = new CEffect({ 2700, 350 }, EffectType::text);
		//listEffect.push_back(effect);

		//CGame::GetInstance()->SwitchScene(/*ID_SCENE_WORLD_MAP*/2);
	}

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
	//DebugOut(L"sl: %d\n",listObj.size());
	//for (size_t i = 0; i < listEnemy.size(); i++)
	//{
	//	if (listEnemy[i]->GetState() == STATE_DESTROYED|| (listEnemy[i]->IsOutOfCamera()&& listEnemy[i]->GetType()==Type::VENUS_FIRE_BALL))
	//	{
	//		listEnemy.erase(listEnemy.begin() + i);
	//		i--;
	//	}
	//}
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
		if (listEffect[i]->GetState() == STATE_DESTROYED/*|| objects[i]->IsOutOfCamera()*/)
		{
			listEffect.erase(listEffect.begin() + i);
			i--;
		}
	}
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	if (player->GetState() == MState::Die)
		cam->LockUpdate();
	if(cam->IsLockUpdate() && player->GetState() != MState::Die)
		cam->UnlockUpdate();
	if (player->inHiddenArea)
		cam->LockUpdateY();
	if (cam->IsLockUpdateY() && !player->inHiddenArea)
		cam->UnlockUpdateY();

	//thieu dieu kien inHiddenArea = false -> cho gia tri int = 1 -> port -> *-1
	cam->Update({ cx,cy }, { 0,0 }, { float(map->GetMapWidth() - SCREEN_WIDTH * 2-226) , float(map->GetMapHeight()-14 *16 - SCREEN_HEIGHT+64) /*(float)200*/ }, player->isFlying);
	//cam->Update({ cx,cy }, { 0,0 }, { float(map->GetMapWidth() /*- SCREEN_WIDTH * 2*/-226) , float(0/*map->GetMapHeight()*/ /*- SCREEN_HEIGHT+64*/) }, player->isFlying);
	//DebugOut(L"map: %d\n", map->GetMapHeight());
}

void CPlayScene::Render()
{
	map->Draw();
	for (size_t i = 0; i < listObj.size(); i++)
		if (listObj.at(i) != NULL)
			listObj[i]->Render();
	//for (size_t i = 0; i < listEnemy.size(); i++)
	//	if (listEnemy.at(i) != NULL)
	//		listEnemy[i]->Render();
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

	//for (size_t i = 0; i < listEnemy.size(); i++)
	//	delete listEnemy[i];
	//listEnemy.clear();

	for (size_t i = 0; i < listObj.size(); i++)
		delete listObj[i];
	listObj.clear();

	for (size_t i = 0; i < listEffect.size(); i++)
		delete listEffect[i];
	listEffect.clear();

	player = NULL;
	delete hud;
	delete cam;
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