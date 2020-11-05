#include "FireBallEffect.h"

CFireBallEffect::CFireBallEffect(D3DXVECTOR2 position)
{
		x = position.x;
		y = position.y;
		this->SetAnimationSet(CAnimationSets::GetInstance()->Get(7));
}

void CFireBallEffect::Render()
{
	animation_set->at(0)->Render(x, y);
}

CFireBallEffect::~CFireBallEffect()
{
}
