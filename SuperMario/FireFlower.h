#pragma once
#include "Item.h"

class CFireFlower :
	public CItem
{
public:
	CFireFlower(D3DXVECTOR2 position);
	~CFireFlower();

	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};