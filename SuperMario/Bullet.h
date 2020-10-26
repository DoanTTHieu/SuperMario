#pragma once
#include "GameObject.h"

#define BULLET_BBOX_WIDTH	8
#define BULLET_BBOX_HEIGHT	8
#define BULLET_GRAVITY		0.00008f
#define BULLET_SPEED_X		0.16f
#define FIRE_BALL		1

class CBullet :
	public CGameObject
{
public:
	CBullet(D3DXVECTOR2 position, int nx);
	~CBullet();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
};


