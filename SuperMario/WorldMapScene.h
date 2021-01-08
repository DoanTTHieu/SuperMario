#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Mario.h"
#include "TileMap.h"
#include "Ground.h"
#include "Effect.h"
#include "HUD.h"
#include "Camera.h"
#include "MapPoint.h"
#include "WorldMapObject.h"

class CWorldMapScene : public CScene
{
protected:
	CMario* player = nullptr;					// A play scene has to have player, right? 
	CTileMap* map = nullptr;
	LPHUD hud;
	vector<CGameObject*> listObj;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILE_MAP(string line);


public:
	CWorldMapScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(ULONGLONG dt);
	virtual void Render();
	virtual void Unload();

	CMario* GetPlayer() { return player; }

	//friend class CPlayScenceKeyHandler;
};

class CWorldMapScenceKeyHandler : public CScenceKeyHandler
{
public:

	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CWorldMapScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

