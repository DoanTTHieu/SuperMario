#include "Bullet.h"
#include "Goomba.h"
#include "Koopas.h"

CBullet::CBullet(D3DXVECTOR2 position, int nx)
{
	x = position.x;
	y = position.y;
	this->nx = nx;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(5));
	//id = ID_BULLET;

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

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				if (e->ny != 0 || e->nx != 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -0.2;
					}
				}
			}
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				if (e->ny != 0 || e->nx != 0)
				{
					if (koopas->GetState() != KOOPAS_STATE_DIE)
					{
						koopas->SetState(KOOPAS_STATE_DIE);
						vy = -0.6;
					}
				}
			} // if Koopas
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

CBullet::~CBullet()
{
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y - BULLET_BBOX_HEIGHT;
	r = x + BULLET_BBOX_WIDTH;
	b = y;

}

void CBullet::Render()
{
	//int ani=1;
	//ani = nx > 0 ? 1 : 2;
	int alpha = 255;
	animation_set->at(0)->Render(x, y, alpha);
}