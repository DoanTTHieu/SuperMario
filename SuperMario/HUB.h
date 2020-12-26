#pragma once
#include "Game.h"
#include "Textures.h"
#include "Mario.h"
#include "Sprites.h"
#include "define.h"

class CHUD
{
	static CHUD* __instance;

	LPDIRECT3DTEXTURE9 texBackground;
	//LPDIRECT3DTEXTURE9 texSpeedBar;
	
	CMario* player;
public:
	CHUD();
	~CHUD();

	void Render(D3DXVECTOR2 position);
	static CHUD* GetInstance();
};

typedef CHUD* LPHUD;
