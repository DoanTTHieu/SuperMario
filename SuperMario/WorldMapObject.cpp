#include "WorldMapObject.h"

CWorldMapObject::CWorldMapObject(int w, int h, bool i)
{
	type = Type::GROUND;
}

void CWorldMapObject::Render()
{
	//animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CWorldMapObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;

}

CWorldMapObject::~CWorldMapObject()
{
}