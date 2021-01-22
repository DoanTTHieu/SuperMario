#pragma once
#include "Plant.h"
#include "Define.h"
#include "Timer.h"
#include "VenusFireBall.h"

enum ZoneOfMario
{
	l_up_near = 0,
	l_up_far = 1,
	l_down_near = 2,
	l_down_far = 3,
	r_up_near = 4,
	r_up_far = 5,
	r_down_near = 6,
	r_down_far = 7
};

class CVenusFireTrap : public CPlant
{
	int venusFireTrapType;
	bool isAttack = false;
	int zoneOfMario = 0;
	CVenusFireBall *fireBall = nullptr;
public:
	CVenusFireTrap(float x, float y, int type);

	int GetVenusFireTrapType() { return venusFireTrapType; }

	bool CheckDistanceNear(D3DXVECTOR4 player);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR4 player);
	virtual void Render();
	virtual void SetState(int state);
};