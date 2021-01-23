#include "Portal.h"


CPortal::CPortal(float l, float t, float r, float b, int scene_id, D3DXVECTOR2 des)
{
	this->type = Type::PORTAL;
	this->scene_id = scene_id;
	this->destination.x = des.x;
	this->destination.y = des.y;
	x = l;
	y = t;
	width = r - l + 1;
	height = b - t + 1;
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + width;
	b = t + height;
}