#pragma once
#include "Enemy.h"
#include "Define.h"
#include "Timer.h"

#define STATE_HIDDEN		5
#define STATE_ATTACK		6
#define STATE_MOVING_UP		7
#define STATE_MOVING_DOWN	8

class CPlant : public CEnemy
{

public:
	CPlant(float x, float y);

	CTimer* hiddenTimer;
	CTimer* attackTimer;

	virtual void GetZoneAtive(float& left, float& top, float& right, float& bottom);
	
	bool CheckPlayerInZone(D3DXVECTOR4 player);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR4 player);
	virtual void Render();
	virtual void SetState(int state);
};