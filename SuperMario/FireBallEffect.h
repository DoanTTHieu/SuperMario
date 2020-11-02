#pragma once
#include "Effect.h"
class CFireBallEffect :
	public CEffect
{
public:
	CFireBallEffect(D3DXVECTOR2 position);
	void Render();
	~CFireBallEffect();
};

