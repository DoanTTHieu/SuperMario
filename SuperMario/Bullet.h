#pragma once
#include "GameObject.h"
#include "Define.h"

#define BULLET_BBOX_WIDTH	8
#define BULLET_BBOX_HEIGHT	8
//#define BULLET_GRAVITY		0.00005f
//#define BULLET_SPEED_X		0.08f
#define BULLET_GRAVITY		0.0008f
#define BULLET_SPEED_X		0.2f
#define BULLET_SPEED_Y		0.15f
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


