#include "Pipe.h"

CPipe::CPipe(int t)
{
	this->type = Type::PIPE;
	this->pipeType = t;
}

void CPipe::Render()
{
	if (pipeType == PipeType::pipe_Long)
		ani = PIPE_ANI_LONG;
	else
		ani = PIPE_ANI_SHORT;
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + PIPE_BBOX_WIDTH;
	if (pipeType == PipeType::pipe_Long)
	{
		b = t + PIPE_BBOX_HEIGHT_LONG;
	}
	else
	{
		b = t + PIPE_BBOX_HEIGHT_SHORT;
	}
}