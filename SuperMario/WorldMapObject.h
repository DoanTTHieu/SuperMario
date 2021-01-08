#pragma once
#include "GameObject.h"
#include "Define.h"

#define WM_OBJ_ANI_PLANT		0
#define WM_OBJ_ANI_HELP			1
#define WM_OBJ_ANI_GUARD_RIGHT	2
#define WM_OBJ_ANI_GUARD_LEFT	3


class CWorldMapObject :public CGameObject
{
	int WM_obj_type;
public:
	virtual void Render();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetWMObjectType() { return WM_obj_type; }

	CWorldMapObject(int t);
	~CWorldMapObject();
};
