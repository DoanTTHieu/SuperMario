#pragma once
#include "Game.h"
#include "Textures.h"
#include "Mario.h"
#include "Sprites.h"
#include "define.h"
#include "Animations.h"
#include "Sprites.h"
#include "Text.h"
#include "SpeedBar.h"

class CHUD
{
	LPANIMATION_SET board;
	LPSPRITE background;
	LPANIMATION_SET card;

	CText text;
	CSpeedBar* speedBar = nullptr;

public:
	CHUD();
	~CHUD();

	void Render(D3DXVECTOR2 position, CMario * mario, int reamainingTime, int stage);
};

typedef CHUD* LPHUD;
