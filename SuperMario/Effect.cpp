#include "Effect.h"

CEffect::CEffect(D3DXVECTOR2 position, int type)
{
	this->effectType = type;
	x = position.x;
	y = position.y;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(41));
	//startEffect = GetTickCount64();
	effectTimer->Start();
}

CEffect::~CEffect()
{
}

void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}

void CEffect::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//if (GetTickCount64() - startEffect > EFFECT_TIME)
	if(effectTimer && effectTimer->IsTimeUp())
		state = STATE_DESTROYED;
}

void CEffect::Render()
{
	switch (effectType)
	{
	case EffectType::fireBall:
		ani = ANI_FIREBALL_EFFECT;
		break;
	case EffectType::text:
		ani = 3;
		break;
	}
	animation_set->at(ani)->Render(x, y);
}
