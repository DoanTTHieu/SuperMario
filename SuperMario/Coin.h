#pragma once
#pragma once
#include "GameObject.h"


class CCoin :
	public CGameObject
{
public:
	CCoin();
	~CCoin();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
};