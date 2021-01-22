#include "Goomba.h"
#include "Ground.h"
#include "Koopas.h"
#include "Brick.h"
#include "Utils.h"

CGoomba::CGoomba()
{
	type = Type::GOOMBA;
	SetState(EState::WALK);
}

CGoomba::CGoomba(int x)
{
	type = Type::GOOMBA;
	Gtype = x;
	if (Gtype == GoombaType::yellow)
	{
		SetState(EState::WALK);
		wing = false;
	}
	else
	{
		SetState(EState::WALK);
		//readyToJumpTimer->Start();
		DebugOut(L"time: %d\n", readyToJumpTimer);
		wing = true;
	}
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DESTROYED || state == EState::DIE_BY_ATTACK)
		left = top = right = bottom = 0;
	else if (state == EState::DIE_BY_CRUSH)
	{
		top = y + 7;
		left = x;
		right = x + GOOMBA_BBOX_WIDTH;
		bottom = y + GOOMBA_BBOX_HEIGHT;
	}
	else if (Gtype == GoombaType::red_para)
	{
		top = y;
		left = x;
		right = x + RED_PARA_BBOX_WIDTH;
		bottom = y + RED_PARA_BBOX_HEIGHT;
	}
	else if (Gtype == GoombaType::yellow)
	{
		top = y;
		left = x;
		right = x + GOOMBA_BBOX_WIDTH;
		bottom = y + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObj)
{ 
	CGameObject::Update(dt);
	vy += GOOMBA_GRAVITY  * dt;
	//ani khi chet
	if (state == EState::DIE_BY_CRUSH && dieByCrushTimer->IsTimeUp())
	{
		dieByCrushTimer->Stop();
		state = STATE_DESTROYED;
	}
	if (state == EState::DIE_BY_ATTACK && IsOutOfCamera())
	{
		state = STATE_DESTROYED;
	}

	if (wing)
	{
		//DebugOut(L"state: %d\n", this->state);
		/*if (!readyToJumpTimer->IsTimeUp() && readyToJumpTimer)
			state = EState::WALK;*/
		if ( readyToJumpTimer->IsTimeUp()&& readyToJumpTimer->GetStartTime())
		{
			readyToJumpTimer->Stop();
			SetState(RED_PARA_STATE_JUMP_HIGH);
			//state = RED_PARA_STATE_JUMP_HIGH;
		}
		if (state == RED_PARA_STATE_JUMP_HIGH && isOnGround)
			SetState(EState::WALK);
	}

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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		y += min_ty * dy + ny * 0.4f;
		x += min_tx * dx + nx * 0.25f;

		if (ny != 0)
		{
			vy = 0;
			if (ny < 0)
			{
				//if(state== RED_PARA_STATE_JUMP_HIGH)
				//	vy = -2.0f * GOOMBA_JUMP_HIGH_SPEED;
				isOnGround = true;
			}
		}

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
					if (this->GetGoombaType() == goomba->GetGoombaType())
					{
						vx = -vx;
						goomba->vx = -vx;
					}
					else
						x += dx;
				}
			}
			else if (e->obj->GetType() == Type::KOOPAS)
			{
				if (e->nx != 0)
					x += dx;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CGoomba::Render()
{
	if (Gtype == GoombaType::red_para)
	{
		ani = RED_PARA_ANI_FLY_HIGH;
	}
	else if (Gtype == GoombaType::yellow)
	{
		ani = GOOMBA_ANI_WALKING;
		if (state == EState::DIE_BY_CRUSH) {
			ani = GOOMBA_ANI_DIE_BY_CRUSH;
		}
		else if (state == EState::DIE_BY_ATTACK)
		{
			ani = GOOMBA_ANI_DIE_BY_ATTACK;
		}
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
		readyToJumpTimer->Start();
		isOnGround = true;
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case RED_PARA_STATE_WALKING:
		isOnGround = true;
		vx = nx * GOOMBA_WALKING_SPEED;
		break;
	case RED_PARA_STATE_JUMP_LOW:
		isOnGround = false;
		vx = - GOOMBA_WALKING_SPEED;
		vy = -GOOMBA_JUMP_HIGH_SPEED;
		break;
	case RED_PARA_STATE_JUMP_HIGH:
		isOnGround = false;
		//vx = -1 * GOOMBA_WALKING_SPEED;
		//vy = -10.0f * GOOMBA_JUMP_HIGH_SPEED ;
		vy = -2*GOOMBA_JUMP_HIGH_SPEED;
		break;

	}
}


