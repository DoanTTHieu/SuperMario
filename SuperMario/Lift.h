#pragma once
#include "GameObject.h"
#include "Define.h"

class CLift :public CGameObject
{
public:
	CLift();
	~CLift();

	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
};
