#pragma once
#include "GameObject.h"
#include "Define.h"

class CTail :
	public CGameObject
{
	static CTail* __instance;
public:
	CTail();
	~CTail();
	static CTail* GetInstance();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR2 playerPos, int playerNx);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	void SetState(int state);	
};


