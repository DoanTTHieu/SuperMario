#include "Brick.h"
#include "Item.h"
#include "SuperMushroom.h"
#include "SuperLeaf.h"

CBrick::CBrick(D3DXVECTOR2 position)
{
	type = Type::BRICK;
	this->x = position.x;
	this->y = position.y;
	isBroken = false;
}
CBrick::~CBrick()
{

}

void CBrick::Render()
{
	animation_set->at(0)->Render(x, y);
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
	if (!isBroken)
	{
		isBroken = true;

		CItem* item = new CSuperMushroom({ x, y - 16 });
		//chua co khoi tao itemID cua item ma
		/*switch (item->itemID)
		{
		case ID_ITEM_SUPER_MUSHROOM:
			item = new CSuperMushroom({ x, y-16 });
			break;
		case ID_ITEM_SUPER_LEAF:
			item = new CSuperLeaf({ x, y-16 });
			break;

		default:
			item = NULL;
			break;
		}*/
		if (item)
			objects->push_back(item);
	}
}
