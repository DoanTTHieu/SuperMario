#include "MapPoint.h"

CMapPoint::CMapPoint(bool hasPortal, int IdScene, bool l, bool r, bool a, bool u)
{
	this->type = Type::MAP_POINT;
	this->hasPortal = hasPortal;
	this->IdScene = IdScene;
	this->left = l;
	this->right = r;
	this->above = a;
	this->under = u;
}

CMapPoint::~CMapPoint()
{

}

void CMapPoint::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y;
	left = x;
	right = x + POINT_WIDTH;
	bottom = y + POINT_HEIGHT;
}

void CMapPoint::Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObj)
{
	CGameObject::Update(dt);
	
}

void CMapPoint::Render()
{
	//ani = 0;
	//animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CMapPoint::SetState(int state)
{
	CGameObject::SetState(state);

}


