#pragma once
#include "GameObject.h"
# include "Define.h"

//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 15

#define BRICK_ANI_NORMAL		0
#define BRICK_ANI_BROKEN		1

class CBrick : public CGameObject
{

public:
	bool isBroken;
	int Btype;
public:
	CBrick(D3DXVECTOR2 position, int type);
	~CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	int GetBrickType() { return Btype; }
	void SetBrickType(int type) { Btype = type; }
	
};