#include "CoinEffect.h"
#include "Utils.h"

CCoinEffect::CCoinEffect(D3DXVECTOR2 position)
{
	this->type = Type::COIN;
	x = position.x;
	y = position.y - BRICK_BBOX_HEIGHT;
	GetPosition(start_x, start_y);
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(32));
	vy = -COIN_SPEED_Y;
	isFalling = false;
}

CCoinEffect::~CCoinEffect()
{

}

void CCoinEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}

void CCoinEffect::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;
	if (state != STATE_DESTROYED)
		vy += MARIO_GRAVITY * dt;
	else
		vy = 0;
	if (vy >= 0)
		isFalling = true;
	if (isFalling && y > start_y)
		state = STATE_DESTROYED;
}

void CCoinEffect::Render()
{
	animation_set->at(1)->Render(x, y);
	RenderBoundingBox();
}
