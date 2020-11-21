#include "Effect.h"

CEffect::CEffect()
{
	startEffect = GetTickCount64();
}

CEffect::~CEffect()
{
}

void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount64() - startEffect > EFFECT_TIME)
		state = STATE_DESTROYED;
}

void CEffect::Render()
{
	//animation_set->at(0)->Render(x, y);
}
