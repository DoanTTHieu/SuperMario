#pragma once
#include "GameObject.h"
#include "Define.h"

class CIntroObject :public CGameObject
{
public:
	virtual void Render();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	CIntroObject();
	~CIntroObject();
};
