#pragma once
#include "Bullet.h"
enum ZoneActive
{
	left_up_near = 0,
	left_up_far = 1,
	left_down_near = 2,
	left_down_far = 3,
	right_up_near = 4,
	right_up_far = 5,
	right_down_near = 6,
	right_down_far = 7
};


class CVenusFireBall :
	public CBullet
{
	int zone;
public:
	CVenusFireBall(D3DXVECTOR2 position, int nx, int zoneOfMario);
	~CVenusFireBall();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetSpeed();
};

