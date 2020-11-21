#pragma once
#include "GameObject.h"
#include "Define.h"

//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 16

class CGround :public CGameObject
{
	int width;
	int height;
	
public:
	bool interact;
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	CGround(int w, int h, bool i);
	int GetGroundWitdth() { return width * BRICK_BBOX_WIDTH; }
	int GetGroundHeight() { return height * BRICK_BBOX_HEIGHT; }
	~CGround();
};
