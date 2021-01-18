#pragma once
#include "GameObject.h"
#include "Define.h"

#define CURTAIN_ANI_OPEN			0
#define CURTAIN_ANI_CLOSE			1

class CIntroObject :public CGameObject
{
public:
	virtual void Render();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	CIntroObject();
	~CIntroObject();
};
