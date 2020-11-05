#include "Bullet.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Define.h"
#include "Ground.h"
#include "Brick.h"
#include "Game.h"


CBullet::CBullet(D3DXVECTOR2 position, int nx)
{
	x = position.x;
	y = position.y;
	this->nx = nx;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(5));

}
void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vx = nx * BULLET_SPEED_X;
	vy += (BULLET_GRAVITY * dt);
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

		if (ny < 0)
		{
			vy = -BULLET_SPEED_X;
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
						state = STATE_DESTROYED;
				}
			}
			else if (e->obj->GetType() == Type::BRICK)
			{
				if (e->nx != 0)
				{
					state = STATE_DESTROYED;
				}
			}
			else //quai di chuyen: 1 phat dan la chet
			{
				if (e->ny != 0 || e->nx != 0)
				{
					if (e->obj->GetState() != STATE_DESTROYED && e->obj->GetState() != EState::DIE_BY_CRUSH && e->obj->GetState() != EState::DIE_BY_ATTACK)
					{
						CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
						
						goomba->nx = this->nx;
						goomba->DieByAttack();
						//e->obj->SetState(STATE_DESTROYED);
						vy = -0.2;
					}
					state = STATE_DESTROYED;
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
	
}

CBullet::~CBullet()
{
}

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;

}

void CBullet::Render()
{
	int alpha = 255;
	animation_set->at(0)->Render(x, y, alpha);
	RenderBoundingBox();
}

