#include "SpeedBar.h"
#include "Utils.h"


CSpeedBar::CSpeedBar() {
	bar = CAnimationSets::GetInstance()->Get(1121);
}

CSpeedBar::~CSpeedBar()
{

}


void CSpeedBar::Render(float x, float y, float vx)
{
	bar->at(0)->Render(x, y);
	//animation_set->at(1)->Render(x, y);
}
