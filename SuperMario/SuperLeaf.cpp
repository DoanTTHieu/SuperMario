#include "SuperLeaf.h"
#include "Ground.h"
#include "Brick.h"
#include "Utils.h"


CSuperLeaf::CSuperLeaf(D3DXVECTOR2 position) {
	this->x = position.x;
	this->y = position.y;
	GetPosition(start_x, start_y);
	//ani
	itemID = ItemID::superLeaf;
	this->type = Type::ITEM;
	vy = -0.115f;
}
CSuperLeaf::~CSuperLeaf()
{

}


void CSuperLeaf::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);
	x += dx;
	y += dy;
	vy += (ITEM_GRAVITY * dt);

	if (!isFalling && y < (start_y - 20.0f))
	{
		DebugOut(L"n\n");
		isFalling = true;
	}

	//vy = (ITEM_GRAVITY * dt);
	DebugOut(L"vy: %f\n", vy);

	if (isFalling)
	{
		DebugOut(L"falling\n");
		DebugOut(L"vx: %f\n", vx);
		//vx = sqrt(60*abs(vy));
		vx = sqrt(2 * 9.8 * 0.002 * (1 - cos(0.25)));
			//vx = sqrt(vy) ;
	/*	if (vx > 0 && x >= start_x + 20)
			vx = -vx;
		if (vx < 0 && x <= start_x - 20)
			vx = -vx;*/
	}


	//if (GetBrickType() == BrickType::question)
	//	DebugOut(L"t: %f\n", float(dt));
	////if (GetBrickType() == BrickType::question)
		
	////if (GetBrickType() == BrickType::question)
		//DebugOut(L"vvvv: %f\n", vx);

	//vx = W * S0 *0.001f * sinf(W * dt + phi) ;
	//vy += (ITEM_GRAVITY*0.01f * dt);

	//vy = W * S0 * 0.001f * sinf(W * dt + phi) * cosf(0.25);

	/*if (x > 245)
		vx = -vx;*/	//vector<LPCOLLISIONEVENT> coEvents;
	//vector<LPCOLLISIONEVENT> coEventsResult;

	//coEvents.clear();
	//CalcPotentialCollisions(coObjects, coEvents);


	//if (coEvents.size() == 0)
	//{
	//	x += dx;
	//	y += dy;
	//}
	//else
	//{
	//	float min_tx, min_ty, nx = 0, ny = 0;
	//	float rdx = 0;
	//	float rdy = 0;

	//	// TODO: This is a very ugly designed function!!!!
	//	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	//	// block every object first!
	//	y += min_ty * dy + ny * 0.4f;
	//	x += min_tx * dx + nx * 0.4f;

	//	/*if (ny != 0)
	//	{
	//		vy = 0;
	//	}*/
	//	//
	//	// Collision logic with other objects
	//	//
	//	for (UINT i = 0; i < coEventsResult.size(); i++)
	//	{
	//		LPCOLLISIONEVENT e = coEventsResult[i];

	//		//if (e->obj->GetType() == Type::GROUND)
	//		//{
	//		//	CGround* ground = dynamic_cast<CGround*>(e->obj);
	//		//	if (e->nx != 0)
	//		//	{
	//		//		if (ground->interact)
	//		//		{
	//		//			x += dx;
	//		//		}
	//		//		else
	//		//			vx = -this->vx;
	//		//	}
	//		//}
	//		//else if (e->obj->GetType() == Type::BRICK|| e->obj->GetType() == Type::PIPE)
	//		//{
	//		//	if (e->nx != 0)
	//		//		vx = -this->vx;
	//		//}
	//	}
	//}

	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


}
