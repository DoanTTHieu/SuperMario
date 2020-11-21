#pragma once
#include "GameObject.h"
# include "Define.h"

//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 15

#define BRICK_ANI_NORMAL		0
#define BRICK_ANI_BROKEN		1
#define STATE_BEING_TOSSED		0
#define STATE_NORMAL			1

class CBrick : public CGameObject
{

public:
	bool isBroken;
	bool diddropItem = false;
	int Btype;
	float start_y;
public:
	CBrick(float x, float y, int type);
	~CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	int GetBrickType() { return Btype; }
	void SetBrickType(int type) { Btype = type; }
	
	void SetState(int state);
};