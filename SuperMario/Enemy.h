#pragma once
#include "Define.h"
#include "GameObject.h"
#include "Timer.h"

enum EState
{
	WALK = 01,
	DIE_BY_CRUSH = 02,
	DIE_BY_ATTACK = 03,
	DESTROYED = 04,
	FLY = 05
	//JUMP = 02,
	//ATTACK = 03,
	//STOP = 04,
	//SIT = 05,
};


#define TIME_DIE_BY_CRUSH		300

class CEnemy : public CGameObject
{
public:
	CTimer* dieByCrushTimer = new CTimer(TIME_DIE_BY_CRUSH);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Render() = 0;

	virtual void DieByCrush();
	virtual void DieByAttack();
};