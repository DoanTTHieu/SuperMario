#pragma once
#include "GameObject.h"
#include "Timer.h"


#define COIN_SPEED_Y	0.08
#define TIME_SCORE_EFFECT 400

class CScoreEffect :
	public CGameObject
{
protected:
	int score;
public:
	CScoreEffect(D3DXVECTOR2 position, int score);
	~CScoreEffect();

	CTimer* effectTimer = new CTimer(TIME_SCORE_EFFECT);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};

