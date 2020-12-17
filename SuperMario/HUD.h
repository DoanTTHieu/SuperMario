#pragma once
#include "Game.h"
#include "Textures.h"
#include "Mario.h"
#include "Sprites.h"
#include "define.h"
#include "Animations.h"
#include "Sprites.h"
#include "Text.h"

class CHUD
{
	LPANIMATION_SET background;
	//LPDIRECT3DTEXTURE9 texBackground;
	CText text;

public:
	CHUD();
	~CHUD();

	void Render(D3DXVECTOR2 position, CMario * mario);
};

typedef CHUD* LPHUD;
