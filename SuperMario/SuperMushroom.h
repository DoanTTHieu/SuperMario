#pragma once
#include "Item.h"

class CSuperMushroom :
	public CItem
{

public:
	CSuperMushroom(D3DXVECTOR2 position, int t);
	~CSuperMushroom();

	virtual void Render();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
};