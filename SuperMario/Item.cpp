#include "Item.h"
#include "Define.h"
#include "Ground.h"
#include "Brick.h"

CItem::CItem()
{
	this->isInteractable = true;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(6));
}

CItem::~CItem()
{
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//if (disapperTimer->IsTimeUp())
	//	SetState(STATE_DESTROYED);
}

void CItem::Render()
{
	//animation
	animation_set->at(itemID)->Render(x, y);
	//RenderBoundingBox();
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


//state_destroyed