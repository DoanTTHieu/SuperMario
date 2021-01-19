#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "TileMap.h"
#include "HUD.h"
#include "Camera.h"
#include "Timer.h"
#include "Animations.h"

#define NEXT_TIMER 10000

#define INTRO_SCENE_ANI_BG		0
#define INTRO_SCENE_ANI_1PLAYER	1
#define INTRO_SCENE_ANI_2PLAYER	2
#define INTRO_SCENE_ANI_3NUMBER	3

class CIntroScene : public CScene
{
protected:

	//truoc khi chon man
	// sau khi chon man
	CTileMap* map = nullptr;
	int phase = 0;
	bool option;
	LPANIMATION_SET aniBG;

	vector<CGameObject*> listObj;
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILE_MAP(string line);

public:
	//CIntroScene() {};

	~CIntroScene() {};
	CIntroScene(int id, LPCWSTR filePath);

	CTimer* nextTimer = new CTimer(NEXT_TIMER);
	void NextPhase();
	void NextOption();
	virtual void Load();
	virtual void Update(ULONGLONG dt);
	virtual void Render();
	virtual void Unload();

	//friend class CPlayScenceKeyHandler;
};

class CIntroScenceKeyHandler : public CScenceKeyHandler
{
public:

	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CIntroScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};
