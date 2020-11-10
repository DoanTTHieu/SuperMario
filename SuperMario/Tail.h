#pragma once
#include "GameObject.h"
#include "Define.h"

#define KILL_ENEMY	2
class CTail :
	public CGameObject
{
	//static CTail* __instance;
public:
	CTail();
	//CTail(D3DXVECTOR2 position, int nx);
	~CTail();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR2 playerPos, int playerNx);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	void SetState(int state);
	//static CTail* GetInstance();
};


