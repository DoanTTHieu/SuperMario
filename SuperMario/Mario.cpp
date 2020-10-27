#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Bullet.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Portal.h"
#include "Ground.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	Idle();
	
	isOnGround = true;
	isSiting = false;
	isblockJump = false;
	isFly = false;
	isAttack = false;
	isWaggingTail = false;

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;
	
	//khoi tao list dan cua mario
	if (isAttack)
	{
		if (nx > 0)
			listBullet.push_back(CreateBullet(x + 10, y + 6, nx));
		else
			listBullet.push_back(CreateBullet(x -6 , y + 6 , nx));
		isAttack = false;
	}


	if (isWaitingForAni && animation_set->at(state)->IsFinished())
	{
		//SetState(MARIO_STATE_ATTACK);
		isWaitingForAni = false;

	}

	//update list dan trong mario
	for (int i = 0; i < listBullet.size(); i++)
		listBullet[i]->Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	interactableObject.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->isInteractable)
		{
			interactableObject.push_back(coObjects->at(i));
		}
	}
	CheckInteraction();


	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	//checkenemies(coObjects);

	// No collision occured, proceed normally
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
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//if (nx != 0) vx = 0;

		if (ny != 0)
		{
			vy = 0;
			if (ny == -1)
			{
				if (!isOnGround)//cham dat thi het nhay
					isOnGround = true;
				isblockJump = false;
				isFly = false;
				isWaggingTail = false;
			}
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

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -0.2;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							UpdateLevel();
						}
					}
				}
			} // if Koopas
			else if (dynamic_cast<CKoopas*>(e->obj)) // if e->obj is Koopas 
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				
				// jump on top >> lam cho no bat tinh(kill Koopas and deflect a bit) 
				if (untouchable == 0)
				{
					if (e->ny < 0)
					{
						if (koopas->GetState() != KOOPAS_STATE_DIE)
						{
							koopas->SetState(KOOPAS_STATE_DIE);
							vy = -0.2;
						}
					}
					else if (e->nx != 0)
					{
						if (untouchable == 0)
						{
							if (koopas->GetState() != KOOPAS_STATE_DIE)
							{
								UpdateLevel();
							}
							else
							{
								koopas->SetState(KOOPAS_STATE_DIE_MOVE);
							}
						}
					}
				}
			} // if Koopas
			else if (dynamic_cast<CGround*>(e->obj))
			{
				isOnGround = true;
				
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				/*CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());*/
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CMario::CheckInteraction()
{
	if (interactableObject.size() > 0)
	{
		for (auto object : interactableObject)
		{
			if (IsAABB(object))
				if (dynamic_cast<CKoopas*>(object))
				{
					object->SetState(KOOPAS_STATE_DIE_MOVE);
				}
		}
	}
}

void CMario::Render()
{
	int ani = -1;
	//con lua
	if (GetLevel() == MARIO_LEVEL_FIRE)
	{
		switch (state)
		{
		case MARIO_STATE_DIE:
			ani = MARIO_ANI_DIE;
			break;
		case MARIO_STATE_STOP:
			if (nx > 0)
				ani = FIRE_ANI_STOP_RIGHT;
			else
				ani = FIRE_ANI_STOP_LEFT;
			break;
		case MARIO_STATE_WALKING_RIGHT:
			ani = FIRE_ANI_WALK_RIGHT;
			break;
		case MARIO_STATE_WALKING_LEFT:
			ani = FIRE_ANI_WALK_LEFT;
			break;
		case MARIO_STATE_RUN_RIGHT:
			if (vx < MARIO_RUN_SPEED_THRESH)
				ani = FIRE_ANI_WALK_RIGHT;
			else
				ani = FIRE_ANI_RUN_RIGHT;
			break;
		case MARIO_STATE_RUN_LEFT:
			if (vx > -MARIO_RUN_SPEED_THRESH)
				ani = FIRE_ANI_WALK_LEFT;
			else
				ani = FIRE_ANI_RUN_LEFT;
			break;
		case MARIO_STATE_ATTACK:
			if (isOnGround)
			{
				if (nx > 0)
					ani = FIRE_ANI_FIGHT_IDLE_RIGHT;
				else
					ani = FIRE_ANI_FIGHT_IDLE_LEFT;
			}
			else
			{
				if (nx > 0)
					ani = FIRE_ANI_ATTACK_RIGHT;
				else
					ani = FIRE_ANI_ATTACK_LEFT;
			}
			break;
		case MARIO_STATE_JUMP:
		case MARIO_STATE_JUMP_LOW:
			if (isSiting)
			{
				if (nx > 0)
					ani = FIRE_ANI_SIT_RIGHT;
				else
					ani = FIRE_ANI_SIT_LEFT;
			}
			else
				if (vy < 0)
				{
					if (nx > 0)
						ani = FIRE_ANI_JUMP_RIGHT;
					else
						ani = FIRE_ANI_JUMP_LEFT;
				}
				else
				{
					if (nx > 0)
						ani = FIRE_ANI_FALL_RIGHT;
					else
						ani = FIRE_ANI_FALL_LEFT;
				}
			break;
		case MARIO_STATE_SIT:
			if (nx > 0)
				ani = FIRE_ANI_SIT_RIGHT;
			else
				ani = FIRE_ANI_SIT_LEFT;
			break;
		default:
			if (!isOnGround)
			{
				break;
			}
			else
			{
				if (vx > 0)
				{
					ani = FIRE_ANI_WALK_RIGHT;
				}
				else if (vx < 0)
				{
					ani = FIRE_ANI_WALK_LEFT;
				}
				else
					if (nx > 0)
						ani = FIRE_ANI_IDLE_RIGHT;
					else
						ani = FIRE_ANI_IDLE_LEFT;
			}
			break;
		}

	}
	//con raccoon
	else if (GetLevel() == MARIO_LEVEL_RACCOON)
	{
		switch (state)
		{
		case MARIO_STATE_DIE:
			ani = MARIO_ANI_DIE;
			break;
		case MARIO_STATE_STOP:
			if (nx > 0)
				ani = RACCOON_ANI_STOP_RIGHT;
			else
				ani = RACCOON_ANI_STOP_LEFT;
			break;
		case MARIO_STATE_WALKING_RIGHT:
			ani = RACCOON_ANI_WALK_RIGHT;
			break;
		case MARIO_STATE_WALKING_LEFT:
			ani = RACCOON_ANI_WALK_LEFT;
			break;
		case MARIO_STATE_RUN_RIGHT:
			if (vx < MARIO_RUN_SPEED_THRESH)
				ani = RACCOON_ANI_WALK_RIGHT;
			else
				ani = RACCOON_ANI_RUN_RIGHT;
			break;
		case MARIO_STATE_RUN_LEFT:
			if (vx > -MARIO_RUN_SPEED_THRESH)
				ani = RACCOON_ANI_WALK_LEFT;
			else
				ani = RACCOON_ANI_RUN_LEFT;
			break;
		case MARIO_STATE_FLY:
			if (vx > 0)
				ani = RACCOON_ANI_FLY_RIGHT;
			else
				ani = RACCOON_ANI_FLY_LEFT;
			break;
		case MARIO_STATE_ATTACK:
			if (nx > 0)
				ani = RACCOON_ANI_FIGHT_IDLE_RIGHT;
			else
				ani = RACCOON_ANI_FIGHT_IDLE_LEFT;
			break;
		case MARIO_STATE_JUMP:
		case MARIO_STATE_JUMP_LOW:
			if (isSiting)
			{
				if (nx > 0)
					ani = RACCOON_ANI_SIT_RIGHT;
				else
					ani = RACCOON_ANI_SIT_LEFT;
			}
			else
				if (vy < 0)
				{
					if (nx > 0)
						ani = RACCOON_ANI_JUMP_RIGHT;
					else
						ani = RACCOON_ANI_JUMP_LEFT;
				}
				else
				{
					if (isWaggingTail)
					{
						if (nx > 0)
							ani = RACCOON_ANI_WAG_TAIL_RIGHT;
						else
							ani = RACCOON_ANI_WAG_TAIL_LEFT;
					}
					else
					{
						if (nx > 0)
							ani = RACCOON_ANI_FALL_RIGHT;
						else
							ani = RACCOON_ANI_FALL_LEFT;
					}
				}
			break;
		case MARIO_STATE_SIT:
			if (nx > 0)
				ani = RACCOON_ANI_SIT_RIGHT;
			else
				ani = RACCOON_ANI_SIT_LEFT;
			break;
		default:
			if (!isOnGround)
			{
				break;
			}
			else
			{
				if (vx > 0)
				{
					ani = RACCOON_ANI_WALK_RIGHT;
				}
				else if (vx < 0)
				{
					ani = RACCOON_ANI_WALK_LEFT;
				}
				else
					if (nx > 0)
						ani = RACCOON_ANI_IDLE_RIGHT;
					else
						ani = RACCOON_ANI_IDLE_LEFT;
			}
			break;
		}

	}
	//con lon
	else if (GetLevel() == MARIO_LEVEL_BIG)
	{
		switch (state)
		{
		case MARIO_STATE_DIE:
			ani = MARIO_ANI_DIE;
			break;
		case MARIO_STATE_STOP:
			if (nx>0)
				ani = MARIO_ANI_STOP_RIGHT;
			else
				ani = MARIO_ANI_STOP_LEFT;
			break;
		case MARIO_STATE_WALKING_RIGHT:
			/*if (vx < 0)
				ani = MARIO_ANI_STOP_RIGHT;*/
			ani = MARIO_ANI_WALK_RIGHT;
			break;
		case MARIO_STATE_WALKING_LEFT:
			/*if (vx > 0)
				ani = MARIO_ANI_STOP_LEFT;*/
			ani = MARIO_ANI_WALK_LEFT;
			break;
		case MARIO_STATE_RUN_RIGHT:
			if (vx < MARIO_RUN_SPEED_THRESH)
				ani = MARIO_ANI_WALK_RIGHT;
			else
				ani = MARIO_ANI_RUN_RIGHT;
			break;
		case MARIO_STATE_RUN_LEFT:
			if (vx > -MARIO_RUN_SPEED_THRESH)
				ani = MARIO_ANI_WALK_LEFT;
			else
				ani = MARIO_ANI_RUN_LEFT;
			break;
		case MARIO_STATE_JUMP:
		case MARIO_STATE_JUMP_LOW:
			if (isSiting)
			{
				if (nx > 0)
					ani = MARIO_ANI_SIT_RIGHT;
				else
					ani = MARIO_ANI_SIT_LEFT;
			}
			else
				if (vy < 0)
				{
					if (nx > 0)
						ani = MARIO_ANI_JUMP_RIGHT;
					else
						ani = MARIO_ANI_JUMP_LEFT;
				}
				else
				{
					if (nx > 0)
						ani = MARIO_ANI_FALL_RIGHT;
					else
						ani = MARIO_ANI_FALL_LEFT;
				}
			break;
		case MARIO_STATE_SIT:
			if (nx > 0)
				ani = MARIO_ANI_SIT_RIGHT;
			else
				ani = MARIO_ANI_SIT_LEFT;
			break;
		default:
			if (!isOnGround)
			{
				break;
			}
			else
			{
				if (vx > 0)
				{
					ani = MARIO_ANI_WALK_RIGHT;
				}
				else if (vx < 0)
				{
					ani = MARIO_ANI_WALK_LEFT;
				}
				else
					if (nx > 0)
						ani = MARIO_ANI_IDLE_RIGHT;
					else
						ani = MARIO_ANI_IDLE_LEFT;
			}
			break;
		}

	}
	//con nho
	else
	{
		switch (state)
		{
		case MARIO_STATE_DIE:
			ani = MARIO_ANI_DIE;
			break;
		case MARIO_STATE_STOP:
			if (nx > 0)
				ani = mario_ANI_STOP_RIGHT;
			else
				ani = mario_ANI_STOP_LEFT;
			break;
		case MARIO_STATE_WALKING_RIGHT:
			ani = mario_ANI_WALK_RIGHT;
			break;
		case MARIO_STATE_WALKING_LEFT:
			ani = mario_ANI_WALK_LEFT;
			break;
		case MARIO_STATE_RUN_RIGHT:
			if (vx < MARIO_RUN_SPEED_THRESH)
				ani = mario_ANI_WALK_RIGHT;
			else
				ani = mario_ANI_RUN_RIGHT;
			break;
		case MARIO_STATE_RUN_LEFT:
			if (vx > -MARIO_RUN_SPEED_THRESH)
				ani = mario_ANI_WALK_LEFT;
			else
				ani = mario_ANI_RUN_LEFT;
			break;
		case MARIO_STATE_JUMP:
		case MARIO_STATE_JUMP_LOW:
			if (nx > 0)
				ani = mario_ANI_JUMP_RIGHT;
			else
				ani = mario_ANI_JUMP_LEFT;
			break;
		default:
			if (!isOnGround)
			{
				break;
			}
			else
			{
				if (vx > 0)
				{
					ani = mario_ANI_WALK_RIGHT;
				}
				else if (vx < 0)
				{
					ani = mario_ANI_WALK_LEFT;
				}
				else
					if (nx > 0)
						ani = mario_ANI_IDLE_RIGHT;
					else
						ani = mario_ANI_IDLE_LEFT;
			}
			break;
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	for (int i = 0; i < listBullet.size(); i++)
		listBullet[i]->Render();

	//RenderBoundingBox();
}

bool CMario::IsAABB(LPGAMEOBJECT object)
{
	float l_mob, t_mob, r_mob, b_mob, l_mario, t_mario, r_mario, b_mario;
	GetBoundingBox(l_mario, t_mario, r_mario, b_mario);
	object->GetBoundingBox(l_mob, t_mob, r_mob, b_mob);
	return AABBCheck(l_mob, t_mob, r_mob, b_mob, l_mario, t_mario, r_mario, b_mario);

}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	if (attackStart > 0)
		return;

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_RUN_RIGHT:
		nx = 1;
		vx += MARIO_ACCELERATION * dt;
		if (vx >= MARIO_RUN_SPEED_THRESH)
			vx = MARIO_RUN_SPEED_THRESH;
		break;
	case MARIO_STATE_RUN_LEFT:
		nx = -1;
		vx -= MARIO_ACCELERATION * dt;
		if (vx <= -MARIO_RUN_SPEED_THRESH)
			vx = -MARIO_RUN_SPEED_THRESH;
		break;
	case MARIO_STATE_FLY:
		if(vx>0)
			vx = MARIO_WALKING_SPEED;
		else
			vx = -MARIO_WALKING_SPEED;
		vy = -MARIO_JUMP_SPEED_Y;
		//y -= 5;
		break;
	case MARIO_STATE_JUMP:
		vy = -MARIO_JUMP_SPEED_Y;
		y -= 5;
		break;
	case MARIO_STATE_JUMP_LOW:
		vy = -MARIO_JUMP_SPEED_Y*0.75;
		y -= 5;
		break;

	case MARIO_STATE_ATTACK:
		break;
	case MARIO_STATE_STOP:
		//vx = 0;
		//break;
	case MARIO_STATE_IDLE:
	case MARIO_STATE_SIT:
		if (vx > 0.08)
		{
			if (vx > 0) {
				vx -= 0.00054 * dt;
				if (vx < 0)
					vx = 0;
			}
			else if (vx < 0) {
				vx += 0.00054 * dt;
				if (vx > 0)
					vx = 0;
			}		
		}
		else
		{
			if (vx > 0) {
				vx -= 0.00018 * dt;
				if (vx < 0)
					vx = 0;
			}
			else if (vx < 0) {
				vx += 0.00018 * dt;
				if (vx > 0)
					vx = 0;
			}
		}
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
	
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_RACCOON)
	{
		right = x + MARIO_RACCOON_BBOX_WIDTH;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_BIG|| level == MARIO_LEVEL_FIRE )
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
		// chua xu ly bbox khi ngoi

	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	Idle();
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CMario::Raccoon()
{
	Idle();
	SetLevel(MARIO_LEVEL_RACCOON);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CMario::FireMario()
{
	Idle();
	SetLevel(MARIO_LEVEL_FIRE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

//level giam
void CMario::UpdateLevel() {
	
	if (level > MARIO_LEVEL_BIG)
	{
		level = MARIO_LEVEL_BIG;
		StartUntouchable();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		level = MARIO_LEVEL_SMALL;
		StartUntouchable();
	}
	else
		SetState(MARIO_STATE_DIE);

}

void CMario::Jump() {
	SetState(MARIO_STATE_JUMP);
	isOnGround = false;
}

void CMario::JumpX() {
	SetState(MARIO_STATE_JUMP_LOW);
	isOnGround = false;
}

void CMario::Fly() {
	SetState(MARIO_STATE_FLY);
	isOnGround = false;
	isFly = true;
}

void CMario::Stop() {

	SetState(MARIO_STATE_STOP);
	isOnGround = true;

	ResetAnimation();
	isWaitingForAni = true;
}

void CMario::Attack() {

	SetState(MARIO_STATE_ATTACK);
	if (GetLevel() == MARIO_LEVEL_FIRE)
		isAttack = true;

	ResetAnimation();
	isWaitingForAni = true;

}

void CMario::Sit() {
	SetState(MARIO_STATE_SIT);
	isSiting = true;
}


void CMario::Idle() {
	SetState(MARIO_STATE_IDLE);
	isOnGround = true;
	isSiting = false;
	isFly = false;
}

void CMario::ToRight() {
	vx = MARIO_WALKING_SPEED;
	nx = 1;
}

void CMario::ToLeft() {
	vx = -MARIO_WALKING_SPEED;
	nx = -1;
}