#include "Coin.h"
#include "Utils.h"


CCoin::CCoin() {
	this->type = Type::COIN;
	//this->isInteractable = true;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(21));
}

CCoin::~CCoin()
{

}


void CCoin::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

}
void CCoin::Render()
{
	animation_set->at(1)->Render(x, y);
	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == STATE_DESTROYED)
		l = t = b = r = 0;
	else
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}
}