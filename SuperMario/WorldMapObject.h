#pragma once
#include "GameObject.h"
#include "Define.h"

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
