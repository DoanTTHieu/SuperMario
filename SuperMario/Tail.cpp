#include "Tail.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Define.h"
#include "Ground.h"
#include "Brick.h"
#include "Game.h"
#include "Define.h"

//CTail* CTail::__instance = NULL;
//
//CTail* CTail::GetInstance()
//{
//	if (__instance == NULL) __instance = new CTail();
//	return __instance;
//}

CTail::CTail()
{
	/*x = position.x;
	y = position.y;
	this->nx = nx;*/
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(1));
}
//CTail::CTail(D3DXVECTOR2 position, int nx)
//{
//	x = position.x;
//	y = position.y;
//	this->nx = nx;
//}
void CTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR2 playerPos, int playerNx)
{

	CGameObject::Update(dt);
	this->x = playerPos.x;
	this->y = playerPos.y;
	this->nx = playerNx;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetType() != Type::BRICK && coObjects->at(i)->GetType() != Type::GROUND)
		{
			if (IsAABB(coObjects->at(i)))
			{
				if (coObjects->at(i)->GetState() != STATE_DESTROYED && coObjects->at(i)->GetState() != EState::DIE_BY_CRUSH && coObjects->at(i)->GetState() != EState::DIE_BY_ATTACK)
				{
					CEnemy* enemy = dynamic_cast<CEnemy*>(coObjects->at(i));
					//can cap nhat nx cua enemy khi quat duoi
					//enemy->nx = this->nx;
					float ax, ay;
					float bx, by;
					GetPosition(ax, ay);//mario
					enemy->GetPosition(bx, by);
					if ((bx - ax) > 0)
						enemy->nx = 1;
					else
						enemy->nx = -1;
					enemy->DieByAttack();
					vy = -0.2;
				}
				state = STATE_DESTROYED;
			}
		}
	}

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

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

CTail::~CTail()
{
}

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KILL_ENEMY)
	{
		switch (animation_set->at(ani)->GetCurrentFrame())
		{
		case 0:
		case 4:
			if (nx > 0)
			{
				left = x + 2;
				top = y + 19.0f;
			}
			else
			{
				left = x + 21;//x, y cua player
				top = y + 19.0f;
			}
			break;
		case 2:
			if (nx > 0)
			{
				left = x + 23;
				top = y + 19.0f;
			}
			else
			{
				left = x;
				top = y + 19.0f;
			}
			break;
		default:
			break;
		}
		right = left + 10;
		bottom = top + 5;
	}
	else
		left = top = bottom = right = 0;
		

}

void CTail::Render()
{
	if (state == KILL_ENEMY) 
		nx > 0 ? ani = RACCOON_ANI_IDLE_RIGHT : RACCOON_ANI_IDLE_LEFT;
	RenderBoundingBox();
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case STATE_DESTROYED:
		break;
	case KILL_ENEMY:

		break;
	default:
		break;
	}
}
