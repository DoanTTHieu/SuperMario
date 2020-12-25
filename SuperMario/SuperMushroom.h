#pragma once
#include "Item.h"

class CSuperMushroom :
	public CItem
{
public:
	CSuperMushroom(D3DXVECTOR2 position);
	~CSuperMushroom();

	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
};