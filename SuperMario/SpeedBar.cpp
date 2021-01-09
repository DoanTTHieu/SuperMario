#include "SpeedBar.h"
#include "Utils.h"


CSpeedBar::CSpeedBar() {
	//bar = CAnimationSets::GetInstance()->Get(1121);
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(1121));
}

CSpeedBar::~CSpeedBar()
{

}


void CSpeedBar::Render(float x, float y, float vx)
{
	if (abs(vx) > (MARIO_WALKING_SPEED + temp * 6))
		ani = 7;
	else if (abs(vx) > (MARIO_WALKING_SPEED + temp * 5))
		ani = 6;
	else if (abs(vx) > (MARIO_WALKING_SPEED + temp * 4))
		ani = 5;
	else if (abs(vx) > (MARIO_WALKING_SPEED + temp * 3))
		ani = 4;
	else if (abs(vx) > (MARIO_WALKING_SPEED + temp * 2))
		ani = 3;
	else if (abs(vx) > (MARIO_WALKING_SPEED + temp * 1))
		ani = 2;
	else if (abs(vx) > (MARIO_WALKING_SPEED + temp * 0))
		ani = 1;
	else
		ani = 0;
	animation_set->at(ani)->Render(x, y);
	//animation_set->at(1)->Render(x, y);
}
