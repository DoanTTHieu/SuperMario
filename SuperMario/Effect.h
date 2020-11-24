#pragma once
#include "GameObject.h"

#define ANI_FIREBALL_EFFECT					0
#define ANI_BRONZE_BRICK_BROKEN_EFFECT		1


#define EFFECT_TIME	120
enum EffectType
{
	fireBall = 01,
	broze_bick_broken = 02,

};


class CEffect :
	public CGameObject
{
protected:

	DWORD startEffect;
	int effectType;
public:
	CEffect(D3DXVECTOR2 position, int type);
	~CEffect();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt);
	virtual void Render();
	int GetEffectType() { return effectType; }
};

