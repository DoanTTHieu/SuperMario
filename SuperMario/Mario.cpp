#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"
#include "FireBallEffect.h"

#include "Bullet.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Portal.h"
#include "Ground.h"
#include "Brick.h"
#include "Item.h"
#include "PiranhaPlant.h"
#include "VenusFireTrap.h"

//CMario* CMario::__instance;

CMario::CMario(float x, float y) : CGameObject()
{
	type = Type::MARIO;

	score = 100;
	coin = 0;
	life = 4;
	time = TIME_DEFAULT;

	level = Level::Big;
	untouchable = 0;
	Idle();

	//isOnGround = true;
	isSitting = false;
	isblockJump = false;
	isAttack = false;
	isWaggingTail = false;
	canHoldShell = false;
	isHolding = false;
	isFlying = false;
	attackStart = 0;

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

//CMario* CMario::GetInstance()
//{
//	if (__instance == NULL) __instance = new CMario();
//	return __instance;
//}

CMario::~CMario()
{
	delete tail;

	for (auto iter : listBullet)
		delete iter;
	listBullet.clear();

	//delete __instance;
	//__instance = NULL;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj, vector<LPGAMEOBJECT>* coItem)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;

	if (flyTimer->IsTimeUp())
		flyTimer->Stop();
	if (!isAttack && tail)	tail->SetState(STATE_DESTROYED);

	//can sua
	//dieu kien tha
	if (isHolding)
	{
		if (!koopas->isBeingHeld || koopas->GetState() == EState::DIE_BY_ATTACK)
			isHolding = false;
		koopas->nx = -nx;
		if (level == Level::Small)
		{
			if (nx < 0)
				koopas->SetPosition(x - 12, y - 12);
			else
				koopas->SetPosition(x + 12, y - 12);
		}
		else if (level == Level::Raccoon)
		{
			if (nx < 0)
				koopas->SetPosition(x - 5, y);
			else
				koopas->SetPosition(x + 19, y);
		}
		else
		{
			if (nx < 0)
				koopas->SetPosition(x - 12, y);
			else
				koopas->SetPosition(x + 12, y);
		}

	}
	if (!canHoldShell && isHolding)
	{
		koopas->SetState(KOOPAS_STATE_DIE_MOVE);
		isHolding = false;
		koopas->isBeingHeld = false;
	}

	//khoi tao list dan cua mario
	if (isAttack)
	{
		if (level == Level::Fire)
		{
			if (listBullet.size() < 2)
			{
				if (nx > 0)
					listBullet.push_back(CreateBullet(x + 10, y + 6, nx));
				else
					listBullet.push_back(CreateBullet(x - 6, y + 6, nx));
			}
		}
		isAttack = false;
	}

	if (GetLevel() == Level::Raccoon)
	{
		if (attackStart && GetTickCount64() - attackStart <= MARIO_TIME_ATTACK)
		{
			state = MState::Attack;
			tail->SetState(KILL_ENEMY);
			//cap nhat nx cua mario 
			//con thieu moot truong hop khi ani = 4
			if (GetTickCount64() - attackStart < MARIO_TIME_ATTACK / 2 && changedNx == 0)
			{
				nx = -nx;
				changedNx++;
			}
			if (GetTickCount64() - attackStart >= MARIO_TIME_ATTACK / 2 && changedNx == 1)
			{
				changedNx = 0;
				nx = -nx;
			}
		}
		else
		{
			if (!isOnGround)
			{
				if (!flyTimer->IsTimeUp())
					state = MState::Fly;
				else
					state = MState::Jump;
			}
			isAttack = false;
			attackStart = 0;
		}
	}

	if (GetLevel() == Level::Fire)
	{
		if (attackStart && GetTickCount64() - attackStart <= MARIO_TIME_SHOOT)
		{
			state = MState::Attack;
		}
		else
		{
			if (!isOnGround)
			{
				state = MState::Jump;
			}
			isAttack = false;
			attackStart = 0;
		}
	}

	//tail update
	if (tail) tail->Update(dt, coObj, { x, y }, nx);

	//update list dan trong mario
	for (size_t i = 0; i < listBullet.size(); i++)
	{
		listBullet[i]->Update(dt, coObj);
	}

	//Collide with objects
	interactableObject.clear();
	for (UINT i = 0; i < coObj->size(); i++)
	{
		if (coObj->at(i)->isInteractable)
		{
			interactableObject.push_back(coObj->at(i));
		}
	}

	//aabb
	CheckInteraction();

	//Collide with items and coins
	CollideWithItem(coItem);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	// turn off collision when die 
	if (state != MState::Die)
		CalcPotentialCollisions(coObj, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

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
		y += min_ty * dy + ny * 0.25f;

		//if (nx != 0) vx = 0;

		if (ny != 0)
		{
			vy = 0;
			if (ny == -1)
			{
				isOnGround = true;
				isFlying = false;
				isblockJump = false;
				isWaggingTail = false;
			}
		}

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			//truong hop CPortal

			if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			if (e->obj->GetType() == Type::PIRANHA_PLANT|| e->obj->GetType() == Type::VENUS_FIRE_TRAP)
			{
				x += dx;
				y += dy;
			}
			//ny
			if (e->ny != 0)
			{
				//quai di chuyen
				if (e->ny < 0)
				{
					//goomba
					if (e->obj->GetType() == Type::GOOMBA)
					{
						if (e->obj->GetState() != STATE_DESTROYED && e->obj->GetState() != EState::DIE_BY_CRUSH && e->obj->GetState() != EState::DIE_BY_ATTACK)
						{
							CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
							goomba->DieByCrush();
							AddScore(100);
							vy = -0.2f;
						}
					}
					//koopas
					if (e->obj->GetType() == Type::KOOPAS)
					{
						CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
						if (koopas->GetState() != KOOPAS_STATE_IDLE)
						{
							if (koopas->GetKoopaType() > 2)
							{
								if (koopas->GetKoopaType() == KoopaType::Green_paratroopa)
									koopas->SetKoopaType(KoopaType::Green_troopa);
								if (koopas->GetKoopaType() == KoopaType::Red_paratroopa)
									koopas->SetKoopaType(KoopaType::Red_troopa);
							}
							else
							{
								koopas->Idle();
								AddScore(100);
								vy = -0.2f;
							}
						}
						else
						{
							float ax, ay;
							float bx, by;
							GetPosition(ax, ay);//mario
							koopas->GetPosition(bx, by);
							if ((bx - ax) > 0)
								koopas->nx = -1;
							else
								koopas->nx = 1;
							koopas->SetState(KOOPAS_STATE_DIE_MOVE);
							koopas->isInteractable = false;
						}

					}

				}
				//block, pipe,..
				if (e->ny > 0)
				{
					if (e->obj->GetType() == Type::BRICK)
					{
						CBrick* brick = dynamic_cast<CBrick*>(e->obj);
						if (brick->GetBrickType() != BrickType::question_broken)
						{
							if (brick->GetItemRemaining() == 1)
							{
								if (brick->GetBrickType() == BrickType::question)
									//brick->SetState(STATE_BROKEN);
									brick->SetBrickType(BrickType::question_broken);
								else
									brick->SetState(STATE_DESTROYED);
							}
							brick->SetState(STATE_BEING_TOSSED);
							brick->sl--;
						}

					}
					else if (e->obj->GetType() == Type::GROUND)
					{
						CGround* ground = dynamic_cast<CGround*>(e->obj);
						if (ground->interact)
						{
							x += dx;
						}
					}

				}

			}
			//nx
			//else
			if (e->nx != 0)
			{
				//ko di xuyen qua duoc ne
				//xet block, pipe,...
				if (e->obj->GetType() == Type::GROUND || e->obj->GetType() == Type::BRICK|| e->obj->GetType() == Type::PIPE)
				{
					if (e->obj->GetType() == Type::GROUND)
					{
						CGround* ground = dynamic_cast<CGround*>(e->obj);
						if (ground->interact)
						{
							x += dx;
						}
						else
						{
							//dang chay nhanh ma va cham thi ko con o trang thai chay nhanh
							if (state == MState::Run_right || state == MState::Run_left)
							{
								if (vx > 0)
									state = MState::Walk_right;
								else
									state = MState::Walk_left;
							}

						}
					}
					else
					{
						//dang chay nhanh ma va cham thi ko con o trang thai chay nhanh
						if (state == MState::Run_right || state == MState::Run_left)
						{
							if (vx > 0)
								state = MState::Walk_right;
							else
								state = MState::Walk_left;
						}
					}

				}
				else
				{
					//tinh luon truong hop untouchable = 0 -> ddi xuyeen qua
					//xet may con di chuyen 
					if (untouchable == 0)//chi xet voi may con di chuyen thoi
					{
						//goomba
						if (e->obj->GetType() == Type::GOOMBA)
							if (e->obj->GetState() != STATE_DESTROYED && e->obj->GetState() != EState::DIE_BY_CRUSH && e->obj->GetState() != EState::DIE_BY_ATTACK)
							{
								UpdateLevel();
							}
						//koopas
						if (e->obj->GetType() == Type::KOOPAS)
						{
							CKoopas* newkoopas = dynamic_cast<CKoopas*>(e->obj);
							if (newkoopas->GetState() == KOOPAS_STATE_IDLE)
							{
								if (canHoldShell)
								{
									this->koopas = newkoopas;
									newkoopas->isBeingHeld = true;
									isHolding = true;
								}
								else
								{
									newkoopas->nx = int(nx);
									newkoopas->SetState(KOOPAS_STATE_DIE_MOVE);
									newkoopas->isInteractable = true;
								}
							}
							else if (newkoopas->GetState() != KOOPAS_STATE_IDLE || newkoopas->GetState() != STATE_DESTROYED)
							{
								if (newkoopas->GetKoopaType() == KoopaType::Green_paratroopa || newkoopas->GetKoopaType() == KoopaType::Red_paratroopa)
									newkoopas->vx = -newkoopas->vx;
								//UpdateLevel();
							}
						}
					}
					else
						x += dx;
				}
			}
			//else//truong hop dang ONGROUND ma roi
			//	if (e->obj->GetType() == Type::BRICK|| e->obj->GetType() == Type::GROUND)
			//		isOnGround = false;
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CMario::CheckInteraction()
{
	if (GetState() == MState::Die)
		return;
	if (interactableObject.size() > 0)
	{
		for (auto object : interactableObject)
		{
			if (untouchable == 0)
			{
				if (IsAABB(object))
				{
					if (object->GetType() == Type::KOOPAS || object->GetType() == Type::PIRANHA_PLANT|| object->GetType() == Type::VENUS_FIRE_TRAP
						|| object->GetType() == Type::VENUS_FIRE_BALL)
					{
						if (object->GetState() != STATE_DESTROYED)
							this->UpdateLevel();
						if (object->GetType() == Type::VENUS_FIRE_BALL)
							object->SetState(STATE_DESTROYED);
					}
					//if (object->GetType() == Type::COIN)
					//{
					//	AddCoin();
					//	object->SetState(STATE_DESTROYED);
					//}
				}

			}
		}
	}
}

void CMario::Render()
{
	//con lua
	if (GetLevel() == Level::Fire)
	{
		if (isHolding)
		{
			switch (state)
			{
			case MState::Walk_right:
			case MState::Run_right:
				ani = FIRE_ANI_WALK_HOLD_RIGHT;
				break;
			case MState::Walk_left:
			case MState::Run_left:
				ani = FIRE_ANI_WALK_HOLD_LEFT;
				break;
			case MState::Jump:
			case MState::Jump_low:
				if (nx > 0)
					ani = FIRE_ANI_ON_AIR_HOLD_RIGHT;
				else
					ani = FIRE_ANI_ON_AIR_HOLD_LEFT;
				break;
			default:
				if (!isOnGround)
				{
					break;
				}
				else
				{
					if (nx > 0 && (vx > 0 || vx < 0))
						ani = FIRE_ANI_WALK_HOLD_RIGHT;
					else if (nx < 0 && (vx > 0 || vx < 0))
						ani = FIRE_ANI_WALK_HOLD_LEFT;
					else if (nx > 0)
						ani = FIRE_ANI_IDLE_HOLD_RIGHT;
					else
						ani = FIRE_ANI_IDLE_HOLD_LEFT;
				}
				break;
			}
		}
		else
			switch (state)
			{
			case MState::Die:
				ani = MARIO_ANI_DIE;
				break;
			case MState::Stop:
				if (nx > 0)
					ani = FIRE_ANI_STOP_RIGHT;
				else
					ani = FIRE_ANI_STOP_LEFT;
				break;
			case MState::Walk_right:
				ani = FIRE_ANI_WALK_RIGHT;
				break;
			case MState::Walk_left:
				ani = FIRE_ANI_WALK_LEFT;
				break;
			case MState::Run_right:
				if (vx < MARIO_RUN_SPEED_THRESH)
					ani = FIRE_ANI_WALK_RIGHT;
				else
					ani = FIRE_ANI_RUN_RIGHT;
				break;
			case MState::Run_left:
				if (vx > -MARIO_RUN_SPEED_THRESH)
					ani = FIRE_ANI_WALK_LEFT;
				else
					ani = FIRE_ANI_RUN_LEFT;
				break;
			case MState::Attack:
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
			case MState::Jump:
			case MState::Jump_low:
				if (isSitting)
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
			case MState::Sit:
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
					if (nx > 0 && (vx > 0 || vx < 0))
						ani = FIRE_ANI_WALK_RIGHT;
					else if (nx < 0 && (vx > 0 || vx < 0))
						ani = FIRE_ANI_WALK_LEFT;
					else if (nx > 0)
						ani = FIRE_ANI_IDLE_RIGHT;
					else
						ani = FIRE_ANI_IDLE_LEFT;
				}
				break;
			}

	}
	//con raccoon
	else if (GetLevel() == Level::Raccoon)
	{
		if (isHolding)
		{
			switch (state)
			{
			case MState::Walk_right:
			case MState::Run_right:
				ani = RACCOON_ANI_WALK_HOLD_RIGHT;
				break;
			case MState::Walk_left:
			case MState::Run_left:
				ani = RACCOON_ANI_WALK_HOLD_LEFT;
				break;
			case MState::Jump:
			case MState::Jump_low:
				if (nx > 0)
					ani = RACCOON_ANI_ON_AIR_HOLD_RIGHT;
				else
					ani = RACCOON_ANI_ON_AIR_HOLD_LEFT;
				break;
			default:
				if (!isOnGround)
				{
					break;
				}
				else
				{
					if (nx > 0 && (vx > 0 || vx < 0))
						ani = RACCOON_ANI_WALK_HOLD_RIGHT;
					else if (nx < 0 && (vx > 0 || vx < 0))
						ani = RACCOON_ANI_WALK_HOLD_LEFT;
					else if (nx > 0)
						ani = RACCOON_ANI_IDLE_HOLD_RIGHT;
					else
						ani = RACCOON_ANI_IDLE_HOLD_LEFT;
				}
				break;
			}
		}
		else
			switch (state)
			{
			case MState::Die:
				ani = MARIO_ANI_DIE;
				break;
			case MState::Stop:
				if (nx > 0)
					ani = RACCOON_ANI_STOP_RIGHT;
				else
					ani = RACCOON_ANI_STOP_LEFT;
				break;
			case MState::Walk_right:
				ani = RACCOON_ANI_WALK_RIGHT;//
				break;
			case MState::Walk_left:
				ani = RACCOON_ANI_WALK_LEFT;//
				break;
			case MState::Run_right:
				if (vx < MARIO_RUN_SPEED_THRESH)
					ani = RACCOON_ANI_WALK_RIGHT;//
				else
					ani = RACCOON_ANI_RUN_RIGHT;
				break;
			case MState::Run_left:
				if (vx > -MARIO_RUN_SPEED_THRESH)
					ani = RACCOON_ANI_WALK_LEFT;//
				else
					ani = RACCOON_ANI_RUN_LEFT;
				break;
			case MState::Fly:
				if (!flyTimer->IsTimeUp())
				{
					if (vx > 0)
						ani = RACCOON_ANI_FLY_RIGHT;
					else
						ani = RACCOON_ANI_FLY_LEFT;
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
			case MState::Attack:
				if (nx > 0)
					ani = RACCOON_ANI_FIGHT_IDLE_RIGHT;
				else
					ani = RACCOON_ANI_FIGHT_IDLE_LEFT;
				break;
			case MState::Jump:
			case MState::Jump_low:
				if (isSitting)
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
			case MState::Sit:
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
					if (nx > 0 && (vx > 0 || vx < 0))
						ani = RACCOON_ANI_WALK_RIGHT;
					else if (nx < 0 && (vx > 0 || vx < 0))
						ani = RACCOON_ANI_WALK_LEFT;
					else if (nx > 0)
						ani = RACCOON_ANI_IDLE_RIGHT;
					else
						ani = RACCOON_ANI_IDLE_LEFT;
				}
				break;
			}

	}
	//con lon
	else if (GetLevel() == Level::Big)
	{
	if (isHolding)
	{
		switch (state)
		{
		case MState::Walk_right:
		case MState::Run_right:
			ani = MARIO_ANI_WALK_HOLD_RIGHT;
			break;
		case MState::Walk_left:
		case MState::Run_left:
			ani = MARIO_ANI_WALK_HOLD_LEFT;
			break;
		case MState::Jump:
		case MState::Jump_low:
			if (nx > 0)
				ani = MARIO_ANI_ON_AIR_HOLD_RIGHT;
			else
				ani = MARIO_ANI_ON_AIR_HOLD_LEFT;
			break;
		default:
			if (!isOnGround)
			{
				break;
			}
			else
			{
				if (nx > 0 && (vx > 0 || vx < 0))
					ani = MARIO_ANI_WALK_HOLD_RIGHT;
				else if (nx < 0 && (vx > 0 || vx < 0))
					ani = MARIO_ANI_WALK_HOLD_LEFT;
				else if (nx > 0)
					ani = MARIO_ANI_IDLE_HOLD_RIGHT;
				else
					ani = MARIO_ANI_IDLE_HOLD_LEFT;
			}
			break;
		}
	}
	else
		switch (state)
		{
		case MState::Die:
			ani = MARIO_ANI_DIE;
			break;
		case MState::Stop:
			if (nx > 0)
				ani = MARIO_ANI_STOP_RIGHT;
			else
				ani = MARIO_ANI_STOP_LEFT;
			break;
		case MState::Walk_right:
			ani = MARIO_ANI_WALK_RIGHT;
			break;
		case MState::Walk_left:
			ani = MARIO_ANI_WALK_LEFT;
			break;
		case MState::Run_right:
			if (vx < MARIO_RUN_SPEED_THRESH)
				ani = MARIO_ANI_WALK_RIGHT;
			else
				ani = MARIO_ANI_RUN_RIGHT;
			break;
		case MState::Run_left:
			if (vx > -MARIO_RUN_SPEED_THRESH)
				ani = MARIO_ANI_WALK_LEFT;
			else
				ani = MARIO_ANI_RUN_LEFT;
			break;
		case MState::Jump:
		case MState::Jump_low:
			if (isSitting)
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
		case MState::Sit:
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
				if (nx > 0 && (vx > 0 || vx < 0))
					ani = MARIO_ANI_WALK_RIGHT;
				else if (nx < 0 && (vx > 0 || vx < 0))
					ani = MARIO_ANI_WALK_LEFT;
				else if (nx > 0)
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
	if (isHolding)
	{
		switch (state)
		{
		case MState::Walk_right:
		case MState::Run_right:
			ani = mario_ANI_WALK_HOLD_RIGHT;
			break;
		case MState::Walk_left:
		case MState::Run_left:
			ani = mario_ANI_WALK_HOLD_LEFT;
			break;
		case MState::Jump:
		case MState::Jump_low:
			if (nx > 0)
				ani = mario_ANI_ON_AIR_HOLD_RIGHT;
			else
				ani = mario_ANI_ON_AIR_HOLD_LEFT;
			break;
		default:
			if (!isOnGround)
			{
				break;
			}
			else
			{
				if (nx > 0 && (vx > 0 || vx < 0))
					ani = mario_ANI_WALK_HOLD_RIGHT;
				else if (nx < 0 && (vx > 0 || vx < 0))
					ani = mario_ANI_WALK_HOLD_LEFT;
				else if (nx > 0)
					ani = mario_ANI_IDLE_HOLD_RIGHT;
				else
					ani = mario_ANI_IDLE_HOLD_LEFT;
			}
			break;
		}
	}
	else
		switch (state)
		{
		case MState::Die:
			ani = MARIO_ANI_DIE;
			break;
		case MState::Stop:
			if (nx < 0)
				ani = mario_ANI_STOP_RIGHT;
			else
				ani = mario_ANI_STOP_LEFT;
			break;
		case MState::Walk_right:
			ani = mario_ANI_WALK_RIGHT;
			break;
		case MState::Walk_left:
			ani = mario_ANI_WALK_LEFT;
			break;
		case MState::Run_right:
			if (vx < MARIO_RUN_SPEED_THRESH)
				ani = mario_ANI_WALK_RIGHT;
			else
				ani = mario_ANI_RUN_RIGHT;
			break;
		case MState::Run_left:
			if (vx > -MARIO_RUN_SPEED_THRESH)
				ani = mario_ANI_WALK_LEFT;
			else
				ani = mario_ANI_RUN_LEFT;
			break;
		case MState::Jump:
		case MState::Jump_low:
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
				if (nx > 0 && (vx > 0 || vx < 0))
					ani = mario_ANI_WALK_RIGHT;
				else if (nx < 0 && (vx > 0 || vx < 0))
					ani = mario_ANI_WALK_LEFT;
				else if (nx > 0)
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

	for (size_t i = 0; i < listBullet.size(); i++)
		listBullet[i]->Render();
	
	//if (tail) tail->Render();
	//RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MState::Walk_right:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MState::Walk_left:
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MState::Run_right:
		if (vx <= 0)
			vx = MARIO_WALKING_SPEED;
		vx += mario_ACCELERATION * 0.2f * dt;
		if (vx >= MARIO_RUN_SPEED_THRESH)
			vx = MARIO_RUN_SPEED_THRESH;
		nx = 1;
		break;
	case MState::Run_left:
		if (vx >= 0)
			vx = -MARIO_WALKING_SPEED;
		vx -= mario_ACCELERATION * 0.2f * dt;
		if (vx <= -MARIO_RUN_SPEED_THRESH)
			vx = -MARIO_RUN_SPEED_THRESH;
		nx = -1;
		break;
	case MState::Fly:
		if (vx > 0)
			vx = MARIO_WALKING_SPEED;
		else
			vx = -MARIO_WALKING_SPEED;
		vy = -MARIO_JUMP_SPEED_Y;
		//y -= 5;
		break;
	case MState::Jump:
		vy = -MARIO_JUMP_SPEED_Y;
		y -= 5;
		break;
	case MState::Jump_low:
		vy = -MARIO_JUMP_SPEED_Y * 0.75;
		y -= 5;
		break;

	case MState::Attack:
		break;
	case MState::Stop:
	case MState::Idle:
		DecreaseSpeedToStop();
		break;
	case MState::Sit:
		DecreaseSpeedToStop();
		break;
	case MState::Die:
		flyTimer->Stop();
		vy = -MARIO_DIE_DEFLECT_SPEED;
		SubLife();
		break;
	}

}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	switch (level)
	{
	case Level::Raccoon:
		right = x + MARIO_RACCOON_BBOX_WIDTH;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;

		if (nx > 0)
		{
			left = x + 7;
			right = left + MARIO_RACCOON_BBOX_WIDTH;
		}
		else
		{
			left = x + 7;
			right = left + MARIO_RACCOON_BBOX_WIDTH;
		}
		if (isSitting)
		{
			top = y + 10;
		}
		break;
	case Level::Fire:
	case Level::Big:
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
		if (isSitting)
		{
			top = y + 10;
		}
		break;
	default:
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
		break;
	}

}

/*
	Mario collides with objects
*/
void CMario::CollideWithItem(vector<LPGAMEOBJECT>* coItem)
{
	for (UINT i = 0; i < coItem->size(); i++)
	{
		if (IsAABB(coItem->at(i)))
		{
			if (coItem->at(i)->GetType() == Type::COIN)
			{
				AddCoin();
			}
			else
			{
				CItem* item = dynamic_cast<CItem*>(coItem->at(i));
				switch (item->GetItemID())
				{
				case ItemID::superLeaf:
					this->SetPosition(x, y - 1.0f);
					this->SetLevel(Level::Raccoon);
					break;
				case ItemID::superMushroom:
					this->SetPosition(x, y - 12.0f);
					this->SetLevel(Level::Big);
					break;
				case ItemID::fireFlower:
					this->SetLevel(Level::Fire);
					break;
				}

			}
			coItem->at(i)->SetState(STATE_DESTROYED);

		}
	}

}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetLevel(Level::Small);
	Idle();
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CMario::Small()
{
	Idle();
	SetLevel(Level::Small);
	SetPosition(x, y-15);
}

void CMario::Big()
{
	Idle();
	SetLevel(Level::Big);
	SetPosition(x, y-15);
}

void CMario::Raccoon()
{
	Idle();
	SetLevel(Level::Raccoon);
	SetPosition(x, y-15);
}

void CMario::FireMario()
{
	Idle();
	SetLevel(Level::Fire);
	SetPosition(x, y - 15);
}

//level giam
void CMario::UpdateLevel() {

	if (level > Level::Big)
	{
		level = Level::Big;
		StartUntouchable();
	}
	else if (level == Level::Big)
	{
		level = Level::Small;
		StartUntouchable();
	}
	else
		SetState(MState::Die);

}

void CMario::Jump() {
	SetState(MState::Jump);
	isOnGround = false;
}

void CMario::JumpX() {
	SetState(MState::Jump_low);
	isOnGround = false;
}

void CMario::Fly() {
	SetState(MState::Fly);
	isFlying = true;
	isOnGround = false;
	flyTimer->Start();
}

void CMario::Stop() {

	SetState(MState::Stop);
	isSitting = false;
}

void CMario::Attack() {
	SetState(MState::Attack);
	/*if (GetLevel() == Level::Fire)*/
	isAttack = true;
	attackStart = GetTickCount64();
}

void CMario::Sit() {
	SetState(MState::Sit);
	isSitting = true;
}

void CMario::Idle() {
	SetState(MState::Idle);
	isSitting = false;
}

void CMario::WalkingLeft() {
	SetState(MState::Walk_left);
	isSitting = false;
}

void CMario::WalkingRight() {
	SetState(MState::Walk_right);
	isSitting = false;
}

void CMario::ToRight() {
	if (vx == 0)
		vx = MARIO_WALKING_SPEED;
	if (vx > 0)
		vx -= MARIO_WALKING_SPEED * mario_ACCELERATION * dt;
	if (vx <= 0)
		vx = 0;
	nx = 1;
}

void CMario::ToLeft() {
	if (vx == 0)
		vx = -MARIO_WALKING_SPEED;
	if (vx < 0)
		vx += MARIO_WALKING_SPEED * mario_ACCELERATION * dt;
	if (vx >= 0)
		vx = 0;
	nx = -1;
}

void CMario::DecreaseSpeedToStop()
{
	if (abs(vx) > 0.08)
	{
		if (vx > 0) {
			vx -= MARIO_ACCELERATION * dt;
			if (vx < 0)
				vx = 0;
		}
		else if (vx < 0) {
			vx += MARIO_ACCELERATION * dt;
			if (vx > 0)
				vx = 0;
		}
	}
	else
	{
		if (vx > 0) {
			vx -= mario_ACCELERATION * dt;
			if (vx < 0)
				vx = 0;
		}
		else if (vx < 0) {
			vx += mario_ACCELERATION * dt;
			if (vx > 0)
				vx = 0;
		}
	}
}