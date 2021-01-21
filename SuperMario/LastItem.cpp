#include "LastItem.h"
#include "Utils.h"


CLastItem::CLastItem() {
	this->type = Type::LAST_ITEM;
	isEaten = false;
}

CLastItem::~CLastItem()
{

}

void CLastItem::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

}
void CLastItem::Render()
{
	// animation_set->at(0)->GetCurrentFrame()
	//0: star
	//1: mushroom
	//2: flower
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CLastItem::GetBoundingBox(float& l, float& t, float& r, float& b)
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