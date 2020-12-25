#include "PiranhaPlant.h"
#include "Utils.h"
#include "Define.h"

CPiranhaPlant::CPiranhaPlant(float x, float y):CPlant(x,y)
{
	hiddenTimer = new CTimer(PIRANHA_PLANT_TIME_HIDDEN);
	attackTimer = new CTimer(PIRANHA_PLANT_TIME_ATTACK);
	type = Type::PIRANHA_PLANT;
}

void CPiranhaPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
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
		b = t + PLANT_BBOX_LOW;
	}

}

void CPiranhaPlant::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR4 player)
{
	CPlant::Update(dt, coObjects, player);
	//1
	if (GetState() == STATE_MOVING_UP && y < start_y - PLANT_BBOX_LOW)
	{
		y = start_y - PLANT_BBOX_LOW;
		SetState(STATE_ATTACK);
	}
}


void CPiranhaPlant::Render()
{
	ani = 0;
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CPiranhaPlant::SetState(int state)
{
	CPlant::SetState(state);
}


