#pragma once
#include "Enemy.h"
#include "Define.h"
#include "Timer.h"

#define GOOMBA_WALKING_SPEED		0.05f;

#define GOOMBA_BBOX_WIDTH			16
#define GOOMBA_BBOX_HEIGHT			15
#define GOOMBA_BBOX_HEIGHT_DIE		9

#define GOOMBA_ANI_WALKING			0
#define GOOMBA_ANI_DIE_BY_CRUSH		1
#define GOOMBA_ANI_DIE_BY_ATTACK	2

class CGoomba : public CEnemy
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj);
	virtual void Render();

public:
	CGoomba();
	virtual void SetState(int state);
};