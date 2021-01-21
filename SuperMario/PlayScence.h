#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "TileMap.h"
#include "Ground.h"
#include "Effect.h"
#include "Item.h"
#include "SuperMushroom.h"
#include "FireBallEffect.h"
#include "SuperLeaf.h"
#include "HUD.h"
#include "Camera.h"
#include "Grid.h"
class CPlayScene : public CScene
{
protected:
	CMario* player = nullptr;					// A play scene has to have player, right? 
	CTileMap* map = nullptr;
	LPCAMERA cam = nullptr;
	LPHUD hud;

	LPGRIG gridMoving;
	LPGRIG gridStatic;

	CTimer* playTimer = new CTimer(PLAY_TIME * MINISEC_PER_SEC);
	int remainingTime=0;

	vector<LPGAMEOBJECT> listObj;

	vector<LPGAMEOBJECT> listItem;
	vector<LPGAMEOBJECT> listEffect;
	
	vector<LPGAMEOBJECT> listMoving;
	vector<LPGAMEOBJECT> listStatic;
	
	vector<LPGAMEOBJECT> listGet;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILE_MAP(string line);


public:

	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(ULONGLONG dt);
	virtual void Render();
	virtual void Unload();
	void GetObjectGrid();

	CMario* GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:

	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

