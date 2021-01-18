#include "IntroObject.h"
#include "Utils.h"
#include "Define.h"

CIntroObject::CIntroObject()
{
	type = Type::INTRO_OBJ;
	vy = -0.06f;
}

void CIntroObject::Render()
{
	if (vy < 0)
		ani = CURTAIN_ANI_OPEN;
	else
		ani = CURTAIN_ANI_CLOSE;
	animation_set->at(ani)->Render(x, y);
}

void CIntroObject::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	y += dy;
	
	if (abs(y) > SCREEN_HEIGHT && y<0)
	{
		vy = -vy;
	}
	if (vy>0 && y>0)
	{
		vy = 0;
		//SetState(STATE_DESTROYED);
	}
}

void CIntroObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;

}

CIntroObject::~CIntroObject()
{
}