#include "Koopas.h"
#include "Ground.h"
#include "Brick.h"

CKoopas::CKoopas() 
{
	type = Type::KOOPAS;
	Ktype = 1;
	SetState(KOOPAS_STATE_IDLE);
}

CKoopas::CKoopas(int x)
{
	type = Type::KOOPAS;
	Ktype = x;
	SetState(KOOPAS_STATE_WALKING);
}


void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	
	if (GetState() == KOOPAS_STATE_IDLE && idleTimer->IsTimeUp())
	{
		idleTimer->Stop();
		checkSupine = false;
		SetState(KOOPAS_STATE_WALKING);
		if (isBeingHeld)
			isBeingHeld = false;
	}

	//neu ko bi cam thi update binh thuong
	if (!isBeingHeld)
	{
		vy += MARIO_GRAVITY * dt;

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
			if (ny != 0) 
			{
				vy = 0;
				if (ny < 0)
				{
					if (Ktype == KoopaType::Green_paratroopa || Ktype == KoopaType::Red_paratroopa)
					{
						vy = -KOOPAS_SPEED_Y;
					}
				}
				
				
				if (checkDone && ny == -1)
				{
					//if (state==KOOPAS_STATE_IDLE && checkSupine)
					{
						checkDone = false;
						vx = 0;
					}
				}
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
							vx = -vx;
					}
					else if (e->ny == -1)
					{
						if (Ktype == KoopaType::Red_troopa && GetState() != KOOPAS_STATE_DIE_MOVE)
						{
							if (x<ground->x || x>(ground->x + ground->GetGroundWitdth() - KOOPAS_BBOX_WIDTH))
								vx = -vx;
						}
					}
					
				}
				else if (e->obj->GetType() == Type::BRICK)
				{
					CBrick* brick = dynamic_cast<CBrick*>(e->obj);
					if (e->nx != 0)
					{
						vx = -vx;
						if (brick->GetBrickType() == BrickType::question)
						{
							brick->SetBrickType(BrickType::question_broken);
							brick->SetState(STATE_BEING_TOSSED);
						}
					}
				}
				else if (e->obj->GetType() == Type::PIPE)
				{
					if (e->nx != 0)
					{
						vx = -vx;
					}
				}
				else if (dynamic_cast<CEnemy*>(e->obj) && state == KOOPAS_STATE_DIE_MOVE)
				{
					CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
					enemy->nx = this->nx;
					enemy->DieByAttack();
				}
			}

		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else // ko co tac dung cua trong luc
	{
		if (GetState() == EState::DIE_BY_ATTACK)
		{
			vy += MARIO_GRAVITY * dt;
		}
		else
			vy = 0;
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

			//
			// Collision logic with other objects
			//
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				
				if (dynamic_cast<CEnemy*>(e->obj) && state == KOOPAS_STATE_IDLE)
				{
					CEnemy* enemy = dynamic_cast<CEnemy*>(e->obj);
					enemy->nx = -nx;
					enemy->DieByAttack();
					this->nx = -nx;
					this->DieByAttack();
				}
			}

		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	
		
}

void CKoopas::Render()
{
	switch (state)
	{
	case EState::DIE_BY_ATTACK:
		ani = KOOPAS_ANI_DIE_SUPINE;
		break;
	case KOOPAS_STATE_DIE_MOVE:
		if (checkSupine)
			ani = KOOPAS_ANI_DIE_MOVE_SUPINE;
		else
			ani = KOOPAS_ANI_DIE_MOVE;
		break;
	case KOOPAS_STATE_IDLE:
		if (checkSupine)
			ani = KOOPAS_ANI_DIE_SUPINE;
		else
			ani = KOOPAS_ANI_DIE;
		break;
	case KOOPAS_STATE_WALKING:
		if (Ktype == KoopaType::Green_paratroopa || Ktype == KoopaType::Red_paratroopa)
		{
			if (vx > 0)
				ani = PARA_KOOPAS_ANI_RIGHT;
			else
			{
				ani = PARA_KOOPAS_ANI_LEFT;
			}
		}
		else
		{
			if (vx > 0)
				ani = KOOPAS_ANI_WALKING_RIGHT;
			else
			{
				ani = KOOPAS_ANI_WALKING_LEFT;
			}
		}
		break;
	default:
		ani = KOOPAS_ANI_WALKING_RIGHT;
		break;
	}

	//DebugOut(L"ani:%d \n", ani);
	animation_set->at(ani)->Render(x, y);
	
	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DESTROYED:
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
	case KOOPAS_STATE_DIE_MOVE:	
		vx = -nx * KOOPAS_DIE_MOVE_SPEED;
		isInteractable = false;
		break;
	case KOOPAS_STATE_IDLE:
		vx = 0;
		isInteractable = false;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		if (Ktype == KoopaType::Green_paratroopa || Ktype == KoopaType::Red_paratroopa)
		{
			vy = -KOOPAS_SPEED_Y;
		}
		isInteractable = true;
		break;
	default:
		break;
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
	case STATE_DESTROYED:
	case EState::DIE_BY_ATTACK:
		left = top = right = bottom = 0;
		break;
	default:
		break;
	}

}

void CKoopas::Idle()
{
	SetState(KOOPAS_STATE_IDLE);
	idleTimer->Start();
}

void CKoopas::IdleSupine()
{
	SetState(KOOPAS_STATE_IDLE);
	idleTimer->Start();
	checkSupine = true;
}
