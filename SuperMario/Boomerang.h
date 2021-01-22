#pragma once
#include "GameObject.h"
#include "Define.h"

class CBoomerang :
	public CGameObject
{
public:
	CBoomerang(D3DXVECTOR2 position, int nx);
	~CBoomerang();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	void SetState(int state);
};


