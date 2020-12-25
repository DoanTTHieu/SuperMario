#pragma once
#include "GameObject.h"
# include "Define.h"
#include "Utils.h"

#define PIECE_GRAVITY		0.0008f
#define PIECE_SPEED_X		0.03f
#define PIECE_SPEED_Y		0.1f

class CBronzeBrickPiece : public CGameObject
{
public:
	CBronzeBrickPiece(D3DXVECTOR2 position, int nx, float v);
	~CBronzeBrickPiece();

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects);

};