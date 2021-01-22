#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "Animations.h"

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
	LPANIMATION_SET aniCard;
public:
	CEffect(D3DXVECTOR2 position, int type);
	~CEffect();

	CTimer* effectTimer = new CTimer(EFFECT_TIMER);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	int GetEffectType() { return effectType; }
};

