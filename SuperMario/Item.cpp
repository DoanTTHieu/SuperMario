#include "Item.h"
#include "Define.h"
#include "Ground.h"
#include "Brick.h"

CItem::CItem()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(31));
}

CItem::~CItem()
{
}

void CItem::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == STATE_DESTROYED)
		l = t = r = b = 0;
	else
	{
		l = x;
		t = y;
		r = x + BRICK_BBOX_WIDTH;
		b = y + BRICK_BBOX_HEIGHT;
	}	
}
