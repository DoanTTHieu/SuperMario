#pragma once
#include "GameObject.h"
#include "Define.h"

#define KILL_ENEMY	200
class CTail :
	public CGameObject
{
public:
	CTail();
	~CTail();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR2 playerPos, int playerNx);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	void SetState(int state);	
};


