#pragma once
#include "GameObject.h"

class CLastItem :
	public CGameObject
{
	bool isEaten;
public:
	CLastItem();
	~CLastItem();
	void IsEaten() { isEaten = true; }
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
};