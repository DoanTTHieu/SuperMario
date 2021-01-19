#include "Koopas.h"
#include "Ground.h"
#include "Brick.h"

CKoopas::CKoopas() 
{
	type = Type::KOOPAS;
	Ktype = 1;
	colidingGround = NULL;
	SetState(KOOPAS_STATE_IDLE);
}

CKoopas::CKoopas(int t, float x, float y)
{
	type = Type::KOOPAS;
	Ktype = t;
	colidingGround = NULL;
	SetState(KOOPAS_STATE_WALKING);
	this->start_x = x;
	this->start_y = y;
}


void CKoopas::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (koopasTimer->IsTimeUp() && !idleTimer->IsTimeUp())
	{
		koopasTimer->Stop();
		isRelife = true;
	}

	if (GetState() == KOOPAS_STATE_IDLE && idleTimer->IsTimeUp())
	{
		idleTimer->Stop();
		isRelife = false;
		checkSupine = false;
		SetState(KOOPAS_STATE_WALKING);
		if (isBeingHeld)
			isBeingHeld = false;
	}

	//neu ko bi cam thi update binh thuong
	if (!isBeingHeld)
	{
		vector<LPGAMEOBJECT> bronzeBricks;
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->GetType() == Type::BRICK)
			{
				CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
				if (brick->GetBrickType() == BrickType::bronze && brick->GetState() != BRICK_STATE_HIDDEN)
					bronzeBricks.push_back(coObjects->at(i));
			}
		}

		if (colidingGround&& Ktype == KoopaType::Red_troopa && GetState() != KOOPAS_STATE_DIE_MOVE)
		{
			float kl, kt, kr, kb, gl, gt, gr, gb;
			GetBoundingBox(kl, kt, kr, kb);
			colidingGround->GetBoundingBox(gl, gt, gr, gb);

			if (colidingGround->GetType() == Type::BRICK)
			{
				CBrick* brick = dynamic_cast<CBrick*>(colidingGround);
				if (brick->GetBrickType() == BrickType::bronze && brick->GetState() != BRICK_STATE_HIDDEN)
				{
					for (int i = 0; i < bronzeBricks.size(); i++)
					{
						//tim cuc gach ma con rua dang dung o tren
						if (colidingGround == bronzeBricks.at(i))
						{
							bool check = false;

							//KIEM TRA CON BRONZE BRICK NAO NUA KO
							for (int j = 0; j < bronzeBricks.size(); j++)
							{
								//if (colidingGround->start_y == bronzeBricks.at(j)->start_y)
								{
									float l, t, r, b;
									bronzeBricks.at(j)->GetBoundingBox(l, t, r, b);

									if ((i != j) && AABBCheck(l, t, r, b, gl - 1.0f, gt, gr + 1.0f, gb))
									{
										check = true;
										if (bronzeBricks.at(j)->start_x < colidingGround->start_x)
										{
											if (start.x < 0)
												start.x = bronzeBricks.at(j)->start_x - 5.0f;
											else if (start.x > bronzeBricks.at(j)->start_x - 5.0f)
												start.x = bronzeBricks.at(j)->start_x - 5.0f;
											if (end.x < (gr - 5.0f) || end.x < 0)
											{
												end.x = gr - 5.0f;
											}
											
										}
										if (bronzeBricks.at(j)->start_x > colidingGround->start_x)
										{
											if (end.x < 0)
												end.x = bronzeBricks.at(j)->start_x + 16.0f - 5.0f;
											else if (end.x < bronzeBricks.at(j)->start_x + 16.0f - 5.0f)
												end.x = bronzeBricks.at(j)->start_x + 16.0f - 5.0f;
											if (start.x > (gl - 5.0f) || start.x < 0)
											{
												start.x = gl - 5.0f;
											}
										}
									}
								}
								//DebugOut(L"start: %f\n", start.x);
								//DebugOut(L"end: %f\n", end.x);
							}
							if (!check)
							{
								start.x = gl - 5.0f;
								start.y = end.y = gb;
								end.x = gr - 5.0f;
							}
						}
					}
				}
				else//khong phai bronzebrick
				{
					start.x = gl - 5.0f;
					//start.y = end.y = gb;
					end.x = gr - 5.0f;
				}
			}
			else//colorbox, ground
			{
				start.x = gl - 5.0f;
				//start.y = end.y = gb;
				end.x = gr - 5.0f;
			}
			if (kl < start.x || kl > end.x)//vi lay toa do cua rua la top left nen de rua di tren gach hop ly thi phai tru
			{
				if (kl < start.x)
					this->x = gl - 4.0f;//them de cho rua khoi bi lac
				else
					this->x = gr - 5.5f;//them de cho rua khoi bi lac
				this->vx = -vx;
			}
		}
		
		if(Ktype != KoopaType::Red_paratroopa)
			vy += KOOPA_GRAVITY * dt;
		if (Ktype == KoopaType::Red_paratroopa && GetState() == KOOPAS_STATE_WALKING && y < (start_y - KOOPAS_LIMIT_Y))
		{
			y = start_y - KOOPAS_LIMIT_Y +2;
			SetState(KOOPAS_STATE_WALKING_DOWN);
		}
		if (Ktype == KoopaType::Red_paratroopa && GetState() == KOOPAS_STATE_WALKING_DOWN && y > start_y)
		{
			y = start_y - 2;
			SetState(KOOPAS_STATE_WALKING);
		}

		vector<LPGAMEOBJECT> groundObjs;

		for (int i = 0; i < coObjects->size(); i++)
		{
			switch (coObjects->at(i)->GetType())
			{
			case Type::BRICK:
			case Type::GROUND:
			case Type::PIPE:
				groundObjs.push_back(coObjects->at(i));
				break;
			}
		}


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
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;
			LPGAMEOBJECT objectX = NULL;
			LPGAMEOBJECT objectY = NULL;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy, objectX, objectY);

			// block every object first!
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.25f;

			if (ny != 0) 
			{
				vy = 0;
				if (ny < 0)
				{
					colidingGround = objectY;
					if (Ktype == KoopaType::Green_paratroopa/* || Ktype == KoopaType::Red_paratroopa*/)
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
				else if (e->obj->GetType() == Type::BRICK)
				{
					CBrick* brick = dynamic_cast<CBrick*>(e->obj);
					if (e->nx != 0 || e->ny != 0)
					{
						if (brick->GetBrickType() == BrickType::bronze)
						{
							if (brick->GetState() == BRICK_STATE_HIDDEN)
							{
								x += dx;
								y += dy;
							}
						}
					}
					if (e->nx != 0&& brick->start_y <(y + KOOPAS_BBOX_HEIGHT))
					{
						vx = -vx;
						if (state == KOOPAS_STATE_DIE_MOVE && brick->GetBrickType() == BrickType::bronze && brick->GetState()!= BRICK_STATE_HIDDEN)
						{
							brick->SetState(STATE_BROKEN);
						}
						else if (brick->GetBrickType() == BrickType::question)
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
				else if (e->obj->GetType() == Type::KOOPAS && e->obj->GetState()== KOOPAS_STATE_WALKING && state == KOOPAS_STATE_WALKING)
				{
					CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
					if (e->nx != 0)
					{
						vx = -vx;
						koopas->vx = -vx;
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
		{
			if (isRelife)
				ani = KOOPAS_ANI_RELIFE_SUPINE;
			else
				ani = KOOPAS_ANI_DIE_SUPINE;
		}
		else
		{
			if (isRelife)
				ani = KOOPAS_ANI_RELIFE;
			else
				ani = KOOPAS_ANI_DIE;
		}
		break;
	case KOOPAS_STATE_WALKING:
	case KOOPAS_STATE_WALKING_DOWN:
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
		ani = KOOPAS_ANI_WALKING_LEFT;
		break;
	}

	//DebugOut(L"ani:%d \n", ani);
	animation_set->at(ani)->Render(x, y);
	
	RenderBoundingBox();
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
		break;
	case KOOPAS_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		if(Ktype != KoopaType::Red_paratroopa)
			vx = -KOOPAS_WALKING_SPEED;
		if (Ktype == KoopaType::Green_paratroopa)
			vy = -KOOPAS_SPEED_Y;
		if(Ktype == KoopaType::Red_paratroopa)
			vy = -RED_KOOPAS_SPEED_Y;
		break;
	case KOOPAS_STATE_WALKING_DOWN:
		vy = RED_KOOPAS_SPEED_Y;
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
	koopasTimer->Start();
}

void CKoopas::IdleSupine()
{
	SetState(KOOPAS_STATE_IDLE);
	idleTimer->Start();
	koopasTimer->Start();
	checkSupine = true;
}
