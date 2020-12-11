#pragma once
#include "Plant.h"
#include "Define.h"
#include "Timer.h"

#define PLANT_PIRANHA_ANI_FACE_UP_LEFT			0

#define PIRANHA_PLANT_TIME_HIDDEN		1500
#define PIRANHA_PLANT_TIME_ATTACK		1500

class CPiranhaPlant : public CPlant
{
public:
	CPiranhaPlant(float x, float y);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR4 player);
	virtual void Render();
	virtual void SetState(int state);
};