#pragma once
#include "Enemy.h"
#include "Define.h"
#include "Timer.h"

class CGoomba : public CEnemy
{
	int Gtype;
public:
	bool wing;
	bool isOnGround;
	CTimer* readyToJumpTimer = new CTimer(TIME_DIE_BY_CRUSH);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObj);
	virtual void Render();
	int GetGoombaType() { return Gtype; }
	CGoomba();
	CGoomba(int x);

	virtual void SetState(int state);
};