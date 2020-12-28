#pragma once
#include "GameObject.h"
#include "Timer.h"


#define COIN_SPEED_Y	0.2
//#define TIME_DEFAULT 200
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

