#pragma once
#include "Define.h"
#include "GameObject.h"
#include "Timer.h"

class CEnemy : public CGameObject
{
public:
	CTimer* dieByCrushTimer = new CTimer(TIME_DIE_BY_CRUSH);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Render() = 0;

	virtual void DieByCrush();
	virtual void DieByAttack();
};