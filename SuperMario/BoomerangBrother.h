#pragma once
#include "Enemy.h"
#include "Define.h"
#include "Timer.h"
#include "Boomerang.h"

class CBoomerangBrother : public CEnemy
{
public:
	vector< LPGAMEOBJECT> listBoomerang;

	CBoomerangBrother(float x, float y);

	CBoomerang* CreateBoomerang(float x, float y, int nx)
	{
		CBoomerang* boomerang = new CBoomerang({ x, y }, nx);
		return boomerang;
	}

	bool isAttacking;

	CTimer* idleTimer = new CTimer(TIME_IDLE);
	CTimer* attackTimer = new CTimer(TIME_ATTACK);
	CTimer* cooldown = new CTimer(TIME_COOLDOWN);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObj);
	virtual void Render();
	virtual void SetState(int state);

};