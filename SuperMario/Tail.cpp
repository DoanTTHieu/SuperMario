#include "Tail.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Define.h"
#include "Ground.h"
#include "Brick.h"
#include "Game.h"
#include "Define.h"
#include "Mario.h"
#include "P_Switch.h"

CTail* CTail::__instance = nullptr;

CTail::CTail()
{
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(1));
}

CTail* CTail::GetInstance()
{
	if (__instance == NULL) __instance = new CTail();
	return __instance;
}

void CTail::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR2 playerPos, int playerNx)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;
	this->x = playerPos.x;
	this->y = playerPos.y;
	this->nx = playerNx;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	for (size_t i = 0; i < coObjects->size(); i++)
	{
		if (IsAABB(coObjects->at(i)))
		{
			if (coObjects->at(i)->GetType() == Type::P_SWITCH)
			{

			}
			else if (coObjects->at(i)->GetType() == Type::BRICK)
			{
				CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
				if (brick->GetBrickType() != BrickType::question_broken)
				{
					if (brick->GetItemRemaining() == 1 && brick->GetBrickType() == BrickType::question)
					{
						brick->SetBrickType(BrickType::question_broken);
					}
					if (brick->GetBrickType() != BrickType::bronze)
						brick->SetState(STATE_BEING_TOSSED);
					else
						//brick->SetState(STATE_DESTROYED);
						if (!brick->isBroken)
						{
							if (brick->containItem == CONTAIN_PSWITCH)
							{
								CGameObject* obj = new CP_Switch(brick->start_x, brick->start_y-16);
								coObjects->push_back(obj);
								brick->SetBrickType(BrickType::question_broken);
							}
							else
								brick->SetState(STATE_BROKEN);
							CMario::GetInstance()->AddScore(10);
						}
					if (brick->containItem == CONTAIN_COIN)
					{
						CMario::GetInstance()->AddScore(100);
						CMario::GetInstance()->AddCoin();
					}
					brick->sl--;
				}
			}
			else
			{
				if (coObjects->at(i)->GetType() != Type::BRICK && coObjects->at(i)->GetType() != Type::GROUND && coObjects->at(i)->GetType() != Type::PIPE)
				{
					if (coObjects->at(i)->GetState() != STATE_DESTROYED && coObjects->at(i)->GetState() != EState::DIE_BY_CRUSH && coObjects->at(i)->GetState() != EState::DIE_BY_ATTACK)
					{
						if (coObjects->at(i)->GetType() == Type::KOOPAS)
						{
							CKoopas* koopas = dynamic_cast<CKoopas*>(coObjects->at(i));
							//koopas->checkSupine = true;
							float ax, ay;
							float bx, by;
							GetPosition(ax, ay);//mario
							koopas->GetPosition(bx, by);
							if ((bx - ax) > 0)
								koopas->nx = 1;
							else
								koopas->nx = -1;
							koopas->IdleSupine();
							CMario::GetInstance()->AddScore(100);
							koopas->vy = -0.2f;
							DebugOut(L"checkDone: %d\n", koopas->checkDone);
							if (!koopas->checkDone)
							{
								if (koopas->nx > 0)
									koopas->vx = 0.05f;
								else
									koopas->vx = -0.05f;
								koopas->checkDone = true;
							}

						}
						else
						{
							DebugOut(L"Type: %d\n", coObjects->at(i)->GetType());
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
							CMario::GetInstance()->AddScore(100);
							vy = -0.2f;
						}
					}
					//state = STATE_DESTROYED;
				}

			}
		}
	}
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
		nx > 0 ? ani = RACCOON_ANI_FIGHT_IDLE_RIGHT : RACCOON_ANI_FIGHT_IDLE_LEFT;
	//RenderBoundingBox();
}

void CTail::SetState(int state)
{
	CGameObject::SetState(state);
}
