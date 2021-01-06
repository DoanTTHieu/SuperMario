#pragma once
#include "GameObject.h"
#include "Define.h"

class CWorldMapObject :public CGameObject
{

public:
	bool interact;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	CWorldMapObject(int w, int h, bool i);
	~CWorldMapObject();
};
