#include "VenusFireBall.h"


CVenusFireBall::CVenusFireBall(D3DXVECTOR2 position, int nx, int zoneOfMario) :CBullet(position, nx)
{
	this->zone = zoneOfMario;
	this->isInteractable = true;
	this->type = Type::VENUS_FIRE_BALL;
	this->isInteractable = true;
}

void CVenusFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	SetSpeed();

	x += dx;
	y += dy;
	
	if (IsOutOfCamera())
		SetState(STATE_DESTROYED);
}

CVenusFireBall::~CVenusFireBall()
{
}

void CVenusFireBall::SetSpeed()
{
	vx = nx * BULLET_SPEED_X;
	//vx = nx * BULLET_SPEED_X*0.004;
	switch (zone)
	{
	case ZoneActive::left_up_far:
	case ZoneActive::right_up_far:
	case ZoneActive::right_up_near:
	case ZoneActive::left_up_near:
		vy = abs(vx);
		break;

	case ZoneActive::left_down_near:
	case ZoneActive::right_down_near:
	case ZoneActive::left_down_far:
	case ZoneActive::right_down_far:
		vy = -abs(vx / 3);
		break;
	}
}