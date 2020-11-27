#pragma once
#include "GameObject.h"
#include "Define.h"

#define PIPE_ANI_LONG		0
#define PIPE_ANI_SHORT		1

#define PIPE_BBOX_WIDTH			32
#define PIPE_BBOX_HEIGHT_LONG	48
#define PIPE_BBOX_HEIGHT_SHORT	32

enum PipeType {
	pipe_Long = 1,
	pipe_Short = 2,
};

class CPipe : public CGameObject
{
	int pipeType;
public:
	CPipe(int t);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

