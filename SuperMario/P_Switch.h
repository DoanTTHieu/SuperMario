#pragma once
#include "GameObject.h"
# include "Define.h"
#include "Timer.h"
#include "Brick.h"

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