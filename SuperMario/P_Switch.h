#pragma once
#include "GameObject.h"
# include "Define.h"
#include "Timer.h"
#include "Brick.h"

#define P_SWITCH_ANI_ON			0
#define P_SWITCH_ANI_OFF		1
#define STATE_BEING_TOSSED		0
#define STATE_ON				1
#define STATE_OFF				2

#define TIME_CHANGE			12000
class CP_Switch : public CGameObject
{

public:
	CP_Switch(float x, float y);
	~CP_Switch();

	bool checkTurn = false;

	CTimer* changeTimer = new CTimer(TIME_CHANGE);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects, vector<LPGAMEOBJECT>* coObj);

	void SetState(int state);
};