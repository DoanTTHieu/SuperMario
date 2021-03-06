#include "FireFlower.h"
#include "Ground.h"
#include "Brick.h"


CFireFlower::CFireFlower(D3DXVECTOR2 position) {
	this->x = position.x;
	this->y = position.y;
	//ani
	itemID = ItemID::fireFlower;
	this->type = Type::ITEM;
	isInCam = false;
	vx = -ITEM_SPEED_Y;
}
CFireFlower::~CFireFlower()
{

}


void CFireFlower::Render()
{
	animation_set->at(itemID)->Render(x, y);
	//RenderBoundingBox();
}

void CFireFlower::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);
	vy += (ITEM_GRAVITY * dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block every object first!
		y += min_ty * dy + ny * 0.4f;
		x += min_tx * dx + nx * 0.4f;

		if (ny != 0)
		{
			vy = 0;
		}
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->GetType() == Type::GROUND)
			{
				CGround* ground = dynamic_cast<CGround*>(e->obj);
				if (e->nx != 0)
				{
					if (ground->interact)
					{
						x += dx;
					}
					else
						vx = -this->vx;
				}
			}
			else if (e->obj->GetType() == Type::BRICK|| e->obj->GetType() == Type::PIPE)
			{
				if (e->nx != 0)
					vx = -this->vx;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


}
