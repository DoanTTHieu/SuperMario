#include "WorldMapObject.h"

CWorldMapObject::CWorldMapObject(int t)
{
	this->WM_obj_type = t;
	type = Type::WM_OBJECT;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(3));
}

void CWorldMapObject::Render()
{
	if (GetWMObjectType() == WM_Obj_Type::plant)
		ani = WM_OBJ_ANI_PLANT;
	else if (GetWMObjectType() == WM_Obj_Type::help)
		ani = WM_OBJ_ANI_HELP;
	else
	{
		ani = WM_OBJ_ANI_GUARD_LEFT;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CWorldMapObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;

}

CWorldMapObject::~CWorldMapObject()
{
}