#pragma once
#include "GameObject.h"
#include "Define.h"

class CBullet :
	public CGameObject
{
public:
	CBullet(D3DXVECTOR2 position, int nx);
	~CBullet();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	void SetState(int state);
};


