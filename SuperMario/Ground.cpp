#include "Ground.h"

CGround::CGround(int w, int h)
{
	this->width = w;
	this->height = h;
}

void CGround::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BRICK_BBOX_WIDTH * width;
	b = t + BRICK_BBOX_HEIGHT * height;
}

CGround::~CGround()
{
}