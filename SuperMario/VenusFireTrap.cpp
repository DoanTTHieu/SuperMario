#include "VenusFireTrap.h"
#include "Utils.h"
#include "Define.h"

CVenusFireTrap::CVenusFireTrap(float x, float y, int type):CPlant(x,y)
{
	hiddenTimer = new CTimer(VENUS_FIRE_TRAP_TIME_HIDDEN);
	attackTimer = new CTimer(VENUS_FIRE_TRAP_TIME_ATTACK);
	this->type = Type::VENUS_FIRE_TRAP;
	this->venusFireTrapType = type;
	fireBall = nullptr;
}

void CVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == STATE_DESTROYED)
	{
		l = t = r = b = 0;
	}
	else
	{
		l = x;
		t = y;
		r = l + PLANT_BBOX_WIDTH;
		if (venusFireTrapType == VenusFireTrapType::green)
		{
			b = t + PLANT_BBOX_LOW;
		}
		else
		{
			b = t + PLANT_BBOX_HIGH;
		}
	}

}

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR4 player)
{
	CPlant::Update(dt, coObjects,player);
	if (player.x < start_x)
	{
		if (player.y < y)
		{
			if (CheckDistanceNear(player))
				zoneOfMario = ZoneOfMario::l_down_near;
			else
				zoneOfMario = ZoneOfMario::l_down_far;
		}
		else
		{
			if (CheckDistanceNear(player))
				zoneOfMario = ZoneOfMario::l_up_near;
			else
				zoneOfMario = ZoneOfMario::l_up_far;
		}
		nx = -1;
	}
	else
	{
		if (player.y < y)
		{
			if (CheckDistanceNear(player))
				zoneOfMario = ZoneOfMario::r_down_near;
			else
				zoneOfMario = ZoneOfMario::r_down_far;
		}
		else
		{
			if (CheckDistanceNear(player))
				zoneOfMario = ZoneOfMario::r_up_near;
			else
				zoneOfMario = ZoneOfMario::r_up_far;
		}
		nx = 1;
	}

	if (isAttack)
	{
		if (nx > 0)
			fireBall = new CVenusFireBall({ x + 10.0f, y + 6 }, nx, zoneOfMario);
		else
			fireBall = new CVenusFireBall({ x - 6, y + 6 }, nx, zoneOfMario);
		isAttack = false;
	}
	if (fireBall) coObjects->push_back(fireBall);
	//if(fireBall) fireBall->Update(dt, coObjects);

	//1
	if (GetVenusFireTrapType() == VenusFireTrapType::red)
	{
		if (GetState() == STATE_MOVING_UP && y < start_y - PLANT_BBOX_HIGH)
		{
			y = start_y - PLANT_BBOX_HIGH;
			SetState(STATE_ATTACK);
		}
	}
	else
	{
		if (GetState() == STATE_MOVING_UP && y < start_y - PLANT_BBOX_LOW)
		{
			y = start_y - PLANT_BBOX_LOW;
			SetState(STATE_ATTACK);
		}
	}

}

bool CVenusFireTrap::CheckDistanceNear(D3DXVECTOR4 player)
{
	if (abs(player.x - start_x) < DISTANCE_THRESH)
		return true;
	return false;
}


void CVenusFireTrap::Render()
{
	switch (zoneOfMario)
	{
	case ZoneOfMario::l_down_far:
	case ZoneOfMario::l_down_near:
		ani = VENUS_FIRE_TRAP_ANI_FACE_DOWN_LEFT;
		break;
	case ZoneOfMario::l_up_far:
	case ZoneOfMario::l_up_near:
		ani = VENUS_FIRE_TRAP_ANI_FACE_UP_LEFT;
		break;
	case ZoneOfMario::r_down_far:
	case ZoneOfMario::r_down_near:
		ani = VENUS_FIRE_TRAP_ANI_FACE_DOWN_RIGHT;
		break;
	case ZoneOfMario::r_up_far:
	case ZoneOfMario::r_up_near:
		ani = VENUS_FIRE_TRAP_ANI_FACE_UP_RIGHT;
		break;
	}

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();

	//if (fireBall) fireBall->Render();
}

void CVenusFireTrap::SetState(int state)
{
	CPlant::SetState(state);
	if (state == STATE_ATTACK)
		isAttack = true;
}


