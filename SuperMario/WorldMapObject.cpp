#include "WorldMapObject.h"
#include "Utils.h"

CWorldMapObject::CWorldMapObject(int t)
{
	this->WM_obj_type = t;
	type = Type::WM_OBJECT;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(3));
	GetPosition(this->start_x, this->start_y);
	if (GetWMObjectType() == WM_Obj_Type::guard)
	{
		vx = 0.015f;
	}

}

void CWorldMapObject::Render()
{
	if (GetWMObjectType() == WM_Obj_Type::plant)
		ani = WM_OBJ_ANI_PLANT;
	else if (GetWMObjectType() == WM_Obj_Type::help)
		ani = WM_OBJ_ANI_HELP;
	else
	{
		if (vx < 0)
			ani = WM_OBJ_ANI_GUARD_LEFT;
		else
			ani = WM_OBJ_ANI_GUARD_RIGHT;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CWorldMapObject::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	if (GetWMObjectType() == WM_Obj_Type::guard)
	{
		x += dx;
		if (x > start_x + 16 || x < start_x)
		{
			if (x > start_x + 16)
				x = start_x + 16;
			if (x < start_x)
				x = start_x;
			vx = -vx;
		}
		//DebugOut(L"x: %f\n", x);
	}

}

void CWorldMapObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;

}

CWorldMapObject::~CWorldMapObject()
{
}