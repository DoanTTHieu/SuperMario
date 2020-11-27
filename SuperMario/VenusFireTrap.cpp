#include "VenusFireTrap.h"
#include "Utils.h"
#include "Define.h"

CVenusFireTrap::CVenusFireTrap(float x, float y, int type):CPlant(x,y)
{
	hiddenTimer = new CTimer(TIME_HIDDEN);
	attackTimer = new CTimer(TIME_ATTACK);
	this->type = Type::VENUS_FIRE_TRAP;
	this->venusFireTrapType = type;
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

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlant::Update(dt, coObjects);
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

void CVenusFireTrap::Render()
{
	ani = 0;
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CVenusFireTrap::SetState(int state)
{
	CPlant::SetState(state);
}


