#pragma once
#include "GameObject.h"

#define EFFECT_TIME	500

class CEffect :
	public CGameObject
{
protected:

	DWORD startEffect;
public:
	CEffect();
	~CEffect();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

