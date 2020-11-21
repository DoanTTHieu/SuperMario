#include "Brick.h"
#include "Item.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"
#include "Utils.h"

CBrick::CBrick(float x, float y, int type)
{
	Btype = type;
	this->type = Type::BRICK;
	this->x = x;
	this->y = y;
	this->start_y = y;
	isBroken = false;
	state = STATE_NORMAL;
}
CBrick::~CBrick()
{

}

void CBrick::Render()
{
	if (Btype == BrickType::question_broken)
		ani = BRICK_ANI_BROKEN;
	else
		ani = BRICK_ANI_NORMAL;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	y += dy;

	if (y < start_y - 5.0f)
	{
		vy = -vy;
	}
	if (y > start_y)
	{
		state = STATE_NORMAL;
		y = start_y;
	}

	if (diddropItem)
	{
		diddropItem = false;
		CItem* item = new CSuperMushroom({ x, y - 16 });
		if (item)
		{
			objects->push_back(item);
			//DebugOut(L"BJAHJASSJ\n");
		}
	}
	
	//	CItem* item = new CSuperMushroom({ x, y - 16 });
	//	//chua co khoi tao itemID cua item ma
	//	/*switch (item->itemID)
	//	{
	//	case ID_ITEM_SUPER_MUSHROOM:
	//		item = new CSuperMushroom({ x, y-16 });
	//		break;
	//	case ID_ITEM_SUPER_LEAF:
	//		item = new CSuperLeaf({ x, y-16 });
	//		break;

	//	default:
	//		item = NULL;
	//		break;
	//	}*/
	//	if (item)
	//		objects->push_back(item);
	//}
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case STATE_DESTROYED:
		break;
	case STATE_BEING_TOSSED:
		diddropItem = true;
		vy = -0.2f;
		break;
	case STATE_NORMAL:
		vy = 0;
	default:
		break;
	}
}
