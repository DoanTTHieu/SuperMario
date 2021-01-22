#pragma once
#include <d3dx9math.h>
#include "GameObject.h"

class CMapPoint : public CGameObject
{
	bool hasPortal;
	int IdScene;
public:
	bool left;
	bool right;
	bool above;
	bool under;

	CMapPoint( bool hasPortal, int IdScene, bool l, bool r, bool a, bool u);
	~CMapPoint();

	int GetSceneId() { return IdScene; }
	int IsContainPortal() { return hasPortal; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObj);
	virtual void Render();

	void SetState(int state);
};