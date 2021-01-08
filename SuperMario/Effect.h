#pragma once
#include "GameObject.h"
#include "Timer.h"

#define ANI_FIREBALL_EFFECT					0
#define ANI_BRONZE_BRICK_BROKEN_EFFECT		1


#define EFFECT_TIME		120
#define EFFECT_TIMER	2000
enum EffectType
{
	fireBall = 01,
	text = 02,

};


class CEffect :
	public CGameObject
{
protected:

	ULONGLONG startEffect;
	int effectType;
public:
	CEffect(D3DXVECTOR2 position, int type);
	~CEffect();

	CTimer* effectTimer = new CTimer(EFFECT_TIMER);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int GetEffectType() { return effectType; }
};

