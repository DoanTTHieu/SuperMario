#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "Define.h"

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

