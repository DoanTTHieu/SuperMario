#pragma once
#include "GameObject.h"
# include "Define.h"
#include "Utils.h"

class CBronzeBrickPiece : public CGameObject
{
public:
	CBronzeBrickPiece(D3DXVECTOR2 position, int nx, float v);
	~CBronzeBrickPiece();

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects);

};