#pragma once
#include "Enemy.h"
#include "Define.h"
#include "Timer.h"
#include "Boomerang.h"

#define BOOMERANG_BROTHER_BBOX_WIDTH			16
#define BOOMERANG_BROTHER_BBOX_HEIGHT			24
#define TIME_IDLE								300
#define TIME_ATTACK								1200
#define TIME_COOLDOWN							600

#define END_POSITION							32

#define BOOMERANG_BROTHER_STATE_IDLE			7
#define BOOMERANG_BROTHER_SPEED_x				0.03f

#define BROTHER_ANI_IDLE_RIGHT		0
#define BROTHER_ANI_WALK_RIGHT		1
#define BROTHER_ANI_ATTACK_RIGHT	2
#define BROTHER_ANI_DIE_RIGHT		3

#define BROTHER_ANI_IDLE_LEFT		4
#define BROTHER_ANI_WALK_LEFT		5
#define BROTHER_ANI_ATTACK_LEFT		6
#define BROTHER_ANI_DIE_LEFT		7


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