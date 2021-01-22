#pragma once
#include "GameObject.h"
#include "Define.h"

enum PipeType {
	pipe_Long = 1,
	pipe_Short = 2,
};

class CPipe : public CGameObject
{
	int pipeType;
	bool hasPortal;
	D3DXVECTOR2 destination;
	bool direction;
public:
	CPipe(int t, bool hasPortal, D3DXVECTOR2 des, bool direction);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	D3DXVECTOR2 GetDestination() { return destination; }
	bool GetDirection() { return this->direction; }
	bool IsHasPortal() { return hasPortal; }
};

