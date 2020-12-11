#include "Goomba.h"
#include "Ground.h"
#include "Brick.h"
#include "Utils.h"

CGoomba::CGoomba()
{
	type = Type::GOOMBA;
	SetState(EState::WALK);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + GOOMBA_BBOX_WIDTH;
	bottom = y + GOOMBA_BBOX_HEIGHT;
	if (state == STATE_DESTROYED|| state == EState::DIE_BY_ATTACK)
		left = top = right = bottom = 0;
	else if (state == EState::DIE_BY_CRUSH)
		top = y + 7;
	else
		top = y;
		
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{

	////
	//// TO-DO: make sure Goomba can interact with the world and to each of them too!
	//// 

	CGameObject::Update(dt);
	if (state == EState::DIE_BY_CRUSH && dieByCrushTimer->IsTimeUp())
	{
		dieByCrushTimer->Stop();
		state = STATE_DESTROYED;
	}
	if (state == EState::DIE_BY_ATTACK && IsOutOfCamera())
	{
		state = STATE_DESTROYED;
	}
	//can define
	vy += (MARIO_GRAVITY * dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObj, coEvents);

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
		x += min_tx * dx + nx * 0.25f;

		if (ny != 0) vy = 0;

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			//DebugOut(L"EVENT: %d\n", coEventsResult.size());
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
						vx = -vx;
				}
			}
			else if (e->obj->GetType() == Type::BRICK|| e->obj->GetType() == Type::PIPE)
			{
				if (e->nx != 0)
				{
					vx = -vx;
				}
			}
			else if (e->obj->GetType() == Type::GOOMBA)
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (e->nx != 0)
				{
					vx = -vx;
					goomba->vx = -vx;
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == EState::DIE_BY_CRUSH) {
		ani = GOOMBA_ANI_DIE_BY_CRUSH;
	}
	else if (state == EState::DIE_BY_ATTACK)
	{
		ani = GOOMBA_ANI_DIE_BY_ATTACK;
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DESTROYED:
	case EState::DIE_BY_CRUSH:
		vx = 0;
		vy = 0;
		break;
	case EState::DIE_BY_ATTACK:
		vy = -MARIO_JUMP_SPEED_Y; 
		if (nx > 0)
		{
			vx = MARIO_WALKING_SPEED;
		}
		else
		{
			vx = -MARIO_WALKING_SPEED;
		}
		break;
	case EState::WALK:
		vx = -GOOMBA_WALKING_SPEED;
		isInteractable = true;
	}
}


