#pragma once
#include "GameObject.h"
#include "Define.h"

#define BOOMERANG_LIMIT				128
#define BOOMERANG_STATE_RETURN		1
#define BOOMERANG_STATE_NORMAL		2
class CBoomerang :
	public CGameObject
{
public:
	CBoomerang(D3DXVECTOR2 position, int nx);
	~CBoomerang();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Render();
	void SetState(int state);
};


