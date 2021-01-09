#pragma once
#include "Animations.h"
#include "Define.h"
#include "GameObject.h"

class CSpeedBar: public CGameObject
{
	//LPANIMATION_SET bar;
	//int ani;
	float temp = (MARIO_RUN_SPEED_THRESH - MARIO_WALKING_SPEED) / 7;

public:
	CSpeedBar();
	~CSpeedBar();
	
	void Render(float x, float y, float vx);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Render() {};
};