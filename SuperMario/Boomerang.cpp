#include "Boomerang.h"

CBoomerang::CBoomerang(D3DXVECTOR2 position, int nx)
{
	x = position.x;
	y = position.y;
	this->start_x = x;
	this->nx = nx;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(58));
	SetState(BOOMERANG_STATE_NORMAL);
}

void CBoomerang::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	
	if (x > start_x + BOOMERANG_LIMIT)
		SetState(BOOMERANG_STATE_RETURN);
	if (state == BOOMERANG_STATE_NORMAL)
	{
	}
	if (state == BOOMERANG_STATE_RETURN)
	{
		if(abs(vx)<=abs(nx * BOOMERANG_SPEED_X))
			vx -=  BOOMERANG_SPEED_X * float(nx) * 0.1f;
		if (abs(vy) <= BOOMERANG_SPEED_X * 0.1)
			vy += (BOOMERANG_GRAVITY* dt);
	}
}

CBoomerang::~CBoomerang()
{
}

void CBoomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DESTROYED)
	{
		left = top = right = bottom = 0;
	}
	else
	{
		left = x;
		top = y;
		right = x + BOOMERANG_BBOX_WIDTH;
		bottom = y + BOOMERANG_BBOX_HEIGHT;
	}
}

void CBoomerang::Render()
{
	if (state == STATE_DESTROYED)
		return;
	int alpha = 255;
	animation_set->at(0)->Render(x, y, alpha);
	//RenderBoundingBox();
}

void CBoomerang::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DESTROYED:
		vx = vy = 0;
		break;
	case BOOMERANG_STATE_NORMAL:
		vx = nx * BOOMERANG_SPEED_X;
		vy = -BOOMERANG_SPEED_X * 0.1;
		break;
	case BOOMERANG_STATE_RETURN:
		break;
	}
		
}
