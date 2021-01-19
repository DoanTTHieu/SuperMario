#pragma once
#include "Item.h"

#define SUPERMUSHROOM_ANI	0
#define UP_MUSHROOM_ANI		5

class CSuperMushroom :
	public CItem
{

public:
	CSuperMushroom(D3DXVECTOR2 position, int t);
	~CSuperMushroom();

	virtual void Render();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
};