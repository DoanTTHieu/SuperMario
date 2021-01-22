#pragma once
#include "Enemy.h"
#include "Define.h"
#include "Timer.h"

class CPlant : public CEnemy
{

public:
	CPlant(float x, float y);

	CTimer* hiddenTimer;
	CTimer* attackTimer;

	virtual void GetZoneAtive(float& left, float& top, float& right, float& bottom);
	
	bool CheckPlayerInZone(D3DXVECTOR4 player);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR4 player);
	virtual void Render();
	virtual void SetState(int state);
};