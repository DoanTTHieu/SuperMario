#include "Brick.h"
#include "Item.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"
#include "Utils.h"

CBrick::CBrick(float x, float y, int type, int typeItem, int sl)
{
	Btype = type;
	this->type = Type::BRICK;
	this->x = x;
	this->y = y;
	this->start_y = y;
	this->containItem = typeItem;
	this->sl = sl;
	isBroken = false;
	state = STATE_NORMAL;
}
CBrick::~CBrick()
{

}

void CBrick::Render()
{
	//if(state==STATE_BROKEN)
	if (Btype == BrickType::question_broken)
		ani = BRICK_ANI_BROKEN;
	else
		ani = BRICK_ANI_NORMAL;
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
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

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	if (y < (start_y - 5.0f) && vy<0)
	{
		vy = -vy;
	}
	if (y > start_y)
	{
		y = start_y;
		//vy = 0;
		SetState(STATE_NORMAL);
	}
	y += dy;
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case STATE_DESTROYED:
	case STATE_BROKEN:
		break;
	case STATE_BEING_TOSSED:
		if(containItem==1 && sl==1)
			diddropItem = true;
		vy = -0.2f;
		DebugOut(L"CONTAIN: %d \n", sl);
		break;
	case STATE_NORMAL:
		vy = 0;
	default:
		break;
	}
}
