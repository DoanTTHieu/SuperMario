#include "Plant.h"
#include "Utils.h"
#include "Define.h"

CPlant::CPlant(float x, float y)
{
	this->x = x;
	this->y = y;
	GetPosition(this->start_x, this->start_y);
	SetState(STATE_MOVING_UP);
	this->isInteractable = true;
}

void CPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;

	//4
	if (hiddenTimer->GetStartTime() != 0 && hiddenTimer->IsTimeUp())
	{
		hiddenTimer->Stop();
		SetState(STATE_MOVING_UP);
	}

	//2
	if (attackTimer->GetStartTime() != 0 && attackTimer->IsTimeUp())
	{
		attackTimer->Stop();
		SetState(STATE_MOVING_DOWN);
	}

	//3
	if (GetState() == STATE_MOVING_DOWN && y > start_y)
	{
		y = start_y + 1;
		SetState(STATE_HIDDEN);
	}


}

void CPlant::Render()
{
}

void CPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DESTROYED:
	case EState::DIE_BY_ATTACK:
		vx = 0;
		vy = 0;
		break;
	case STATE_ATTACK:
		vy = 0;
		attackTimer->Start();
		break;
	case STATE_HIDDEN:
		vy = 0;
		hiddenTimer->Start();
		break;
	case STATE_MOVING_UP:
		vy = -PLANT_SPEED_Y;
		break;
	case STATE_MOVING_DOWN:
		vy = PLANT_SPEED_Y;
		break;
	}
}


