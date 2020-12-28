#pragma once
#include "GameObject.h"

class CLastItem :
	public CGameObject
{
public:
	CLastItem();
	~CLastItem();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
};