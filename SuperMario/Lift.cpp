#include "Lift.h"
#include "Utils.h"

CLift::CLift()
{
	this->type = Type::LIFT;
	SetState(LIFT_STATE_GO_LEFT);
}

CLift::~CLift()
{

}

void CLift::Render()
{
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CLift::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == STATE_DESTROYED)
		l = t = b = r = 0;
	else
	{
		l = x;
		t = y;
		r = x + LIFT_BBOX_WIDTH;
		b = y + LIFT_BBOX_HEIGHT;
	}
}

void CLift::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	x +=dx;
	y += dy;
	if(GetState()== LIFT_STATE_GO_DOWN)
		vy += MARIO_GRAVITY * 0.5f * dt;
}

void CLift::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case LIFT_STATE_GO_LEFT:
		vy = 0;
		vx = -LIFT_SPEED_X;
		break;
	case LIFT_STATE_GO_DOWN:
		vx = 0;
		break;
	default:
		break;
	}
}
