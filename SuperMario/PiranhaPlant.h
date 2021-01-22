#pragma once
#include "Plant.h"
#include "Define.h"
#include "Timer.h"

class CPiranhaPlant : public CPlant
{
public:
	CPiranhaPlant(float x, float y);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR4 player);
	virtual void Render();
	virtual void SetState(int state);
};