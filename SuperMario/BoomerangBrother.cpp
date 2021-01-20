#include "BoomerangBrother.h"
#include "Ground.h"
#include "Koopas.h"
#include "Brick.h"
#include "Utils.h"
#include "Mario.h"

CBoomerangBrother::CBoomerangBrother(float x, float y)
{
	type = Type::BOOMERANG_BROTHER;
	this->start_x = x;
	this->start_y = y;
	nx = 1;
	SetState(EState::WALK);
	isAttacking = false;
	cooldown->Start();
}

void CBoomerangBrother::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_DESTROYED || state == EState::DIE_BY_ATTACK|| state == EState::DIE_BY_CRUSH)
		left = top = right = bottom = 0;
	else
	{
		top = y;
		left = x;
		right = x + BOOMERANG_BROTHER_BBOX_WIDTH;
		bottom = y + BOOMERANG_BROTHER_BBOX_HEIGHT;
	}
}

void CBoomerangBrother::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObj)
{
	CGameObject::Update(dt);
	vy += GOOMBA_GRAVITY * dt;
	
	if (listBoomerang.size() == 0)
	{
		if (isAttacking && cooldown->GetStartTime() == 0)
		{
			cooldown->Start();
			isAttacking = false;
		}
	}

	if (x > start_x + END_POSITION)
	{
		x = start_x + END_POSITION;
		nx = -1;
		SetState(BOOMERANG_BROTHER_STATE_IDLE);
		idleTimer->Start();
	}
	if (x < start_x)
	{
		x = start_x;
		nx = 1;
		SetState(BOOMERANG_BROTHER_STATE_IDLE);
		idleTimer->Start();
	}
	if (idleTimer->GetStartTime() && idleTimer->IsTimeUp())
	{
		idleTimer->Stop();
		SetState(EState::WALK);
	}

	// them boomerang vao list
	if (cooldown->GetStartTime() && cooldown->IsTimeUp())
	{
		isAttacking = true;
		cooldown->Stop();
		if (listBoomerang.size() < 2)
		{
			int n = (CMario::GetInstance()->x > x ? 1 : -1);
			listBoomerang.push_back(CreateBoomerang(x, y, n));
			attackTimer->Start();
		}
	}
	if (isAttacking)
	{
		if (listBoomerang.size() < 2 && attackTimer->IsTimeUp() && attackTimer->GetStartTime())
		{
			attackTimer->Stop();
			int n = (CMario::GetInstance()->x > x ? 1 : -1);
			listBoomerang.push_back(CreateBoomerang(x, y, n));
		}
	}

	for (size_t i = 0; i < listBoomerang.size(); i++)
	{
		listBoomerang[i]->Update(dt, coObj);
		if(this->IsCollidingWithObjectNx(listBoomerang[i])|| this->IsCollidingWithObjectNy(listBoomerang[i]))
			listBoomerang[i]->SetState(STATE_DESTROYED);
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
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBoomerangBrother::Render()
{
	if (state == BOOMERANG_BROTHER_STATE_IDLE)
		ani = BROTHER_ANI_IDLE_RIGHT;
	if (state == EState::WALK)
		ani = BROTHER_ANI_WALK_RIGHT;
	if (state == EState::DIE_BY_CRUSH)
		ani = BROTHER_ANI_DIE_RIGHT;
	if (state == EState::DIE_BY_ATTACK)
		ani = BROTHER_ANI_DIE_RIGHT;
	for (size_t i = 0; i < listBoomerang.size(); i++)
		listBoomerang[i]->Render();

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CBoomerangBrother::SetState(int state)
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
		vy = -BOOMERANG_BROTHER_SPEED_x;
		if (nx > 0)
		{
			vx = BOOMERANG_BROTHER_SPEED_x;
		}
		else
		{
			vx = -BOOMERANG_BROTHER_SPEED_x;
		}
		break;
	case BOOMERANG_BROTHER_STATE_IDLE:
		vx = vy = 0;
		break;
	case EState::WALK:
		vx = nx * BOOMERANG_BROTHER_SPEED_x;
		break;
	}
}


