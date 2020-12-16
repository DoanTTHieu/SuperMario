#include "BronzeBrickPiece.h"

CBronzeBrickPiece::CBronzeBrickPiece(D3DXVECTOR2 position, int nx, float v)
{
	x = position.x;
	y = position.y;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(41));
	vy = -PIECE_SPEED_Y * v;
	vx = PIECE_SPEED_X * nx;
}

CBronzeBrickPiece::~CBronzeBrickPiece()
{
}

void CBronzeBrickPiece::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == STATE_DESTROYED)
		l = t = r = b = 0;
	else
	{
		l = x;
		t = y;
		r = l + 8;
		b = t + 8;
	}
}

void CBronzeBrickPiece::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);
	vy += PIECE_GRAVITY * dt;
	x += dx;
	y += dy;
	if (this->IsOutOfCamera())
		SetState(STATE_DESTROYED);
}

void CBronzeBrickPiece::Render()
{
	int alpha = 255;
	animation_set->at(1)->Render(x, y, alpha);
	//RenderBoundingBox();
}
