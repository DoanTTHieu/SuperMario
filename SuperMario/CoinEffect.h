#pragma once
#include "GameObject.h"
#include "Timer.h"

class CCoinEffect :
	public CGameObject
{
protected:

	ULONGLONG startEffect;
	bool isFalling; 
public:
	CCoinEffect(D3DXVECTOR2 position);
	~CCoinEffect();
	//CTimer* effectTimer = new CTimer(TIME_DEFAULT);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

