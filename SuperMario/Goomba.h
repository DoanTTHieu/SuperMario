#pragma once
#include "Enemy.h"
#include "Define.h"
#include "Timer.h"

#define GOOMBA_WALKING_SPEED		0.05f;
#define GOOMBA_JUMP_HIGH_SPEED		0.1f;
#define GOOMBA_JUMP_LOW_SPEED		0.03f;

#define GOOMBA_BBOX_WIDTH			16
#define GOOMBA_BBOX_HEIGHT			15
#define GOOMBA_BBOX_HEIGHT_DIE		9

#define RED_PARA_BBOX_WIDTH			20
#define RED_PARA_BBOX_HEIGHT		24

#define RED_PARA_STATE_WALKING		10
#define RED_PARA_STATE_JUMP_LOW		11
#define RED_PARA_STATE_JUMP_HIGH	12

#define GOOMBA_ANI_WALKING			0
#define GOOMBA_ANI_DIE_BY_CRUSH		1
#define GOOMBA_ANI_DIE_BY_ATTACK	2

#define RED_PARA_ANI_WING_WALKING	3
#define RED_PARA_ANI_FLY_LOW		4
#define RED_PARA_ANI_FLY_HIGH		5

#define RED_PARA_ANI_WALKING		6
#define RED_PARA_ANI_DIE_BY_CRUSH	7
#define RED_PARA_ANI_DIE_BY_ATTACK	8



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