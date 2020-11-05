#include "Koopas.h"
#include "Ground.h"
#include "Brick.h"

CKoopas::CKoopas()
{
	type = Type::KOOPAS;
	SetState(KOOPAS_STATE_WALKING);
}



void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//can define
	vy += 0.02 * dt;

	if (GetState() == KOOPAS_STATE_IDLE && idleTimer->IsTimeUp())
	{
		idleTimer->Stop();
		SetState(KOOPAS_STATE_WALKING);
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
			//x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;///chinh lai xet va cham koopas voi brick -> cai nay do no xet y trung hop r

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		//DebugOut(L"size:%d \n", coEvents.size());
		//if (coEvents.size() >= 3) 
		//	vx *= -1;

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGround*>(e->obj))
			{
				//DebugOut(L"GROUND\n");
				CGround* ground = dynamic_cast<CGround*>(e->obj);
				if (e->nx != 0)
				{
					//DebugOut(L"NX: %d\n", e->nx);
					if (ground->interact)
					{
						x += dx;
					}
					else
						vx = -vx;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->nx != 0)
				{
					vx = -vx;
				}
			}
		}

	}


	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	switch (state)
	{
	case KOOPAS_STATE_DIE_MOVE:
		ani = KOOPAS_ANI_DIE_MOVE;
		break;
	case KOOPAS_STATE_IDLE:
		ani = KOOPAS_ANI_DIE;
		break;
	case KOOPAS_STATE_WALKING:
		if (vx > 0) 
			ani = KOOPAS_ANI_WALKING_RIGHT;
		else
			ani = KOOPAS_ANI_WALKING_LEFT;
		break;
	default:
		ani = KOOPAS_ANI_WALKING_RIGHT;
		break;
	}

	//DebugOut(L"ani:%d \n", ani);
	animation_set->at(ani)->Render(x, y);
	
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE_MOVE:	
		vx = -nx * KOOPAS_DIE_MOVE_SPEED;
		isInteractable = false;
		break;
	case KOOPAS_STATE_IDLE:
		vx = 0;
		isInteractable = false;
		//isInteractable = true;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		isInteractable = true;
	}

}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;
	bottom = y + KOOPAS_BBOX_HEIGHT;
	switch (state)
	{
	case KOOPAS_STATE_IDLE:
	case KOOPAS_STATE_DIE_MOVE:
		top = y+ KOOPAS_BBOX_HEIGHT- KOOPAS_BBOX_HEIGHT_DIE;
		break;
	default:
		break;
	}


	//if (state == KOOPAS_STATE_IDLE || state == KOOPAS_STATE_DIE_MOVE)
	//	bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	//else
}

void CKoopas::Idle()
{
	SetState(KOOPAS_STATE_IDLE);
	idleTimer->Start();

}