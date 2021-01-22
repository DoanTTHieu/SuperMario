#include "SuperLeaf.h"
#include "Ground.h"
#include "Brick.h"
#include "Utils.h"


CSuperLeaf::CSuperLeaf(D3DXVECTOR2 position) {
	this->x = position.x;
	this->y = position.y;
	GetPosition(start_x, start_y);
	left = start_x - BRICK_BBOX_WIDTH;
	right = start_x + BRICK_BBOX_WIDTH;

	//ani
	itemID = ItemID::superLeaf;
	this->type = Type::ITEM;
	vy = -LEAF_SPEED_Y;
	isFalling = false;
	isInCam = false;
}
CSuperLeaf::~CSuperLeaf()
{

}

void CSuperLeaf::Render()
{
	if (vx <= 0)
		ani = LEAF_ANI_LEAF;
	else
		ani = LEAF_ANI_RIGHT;
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CSuperLeaf::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (!isFalling)
		vy += (ITEM_GRAVITY * dt);
	else
		vy = LEAF_SPEED_FALL;

	if (!isFalling && vy>0)
	{
		isFalling = true;
		vx = -LEAF_SPEED_X;
	}

	if (isFalling)
	{
		if (vx < 0 && x < left)
		{
			vx = -vx;
			x = left;
		}
		if (vx > 0 && x > right)
		{
			vx = -vx;
			x = right;
		}
	}
}
