#pragma once
#include "GameObject.h"
# include "Define.h"

//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 15

class CBrick : public CGameObject
{
public:
	bool isBroken;
public:
	CBrick(D3DXVECTOR2 position);
	~CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};