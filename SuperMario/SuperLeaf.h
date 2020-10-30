#pragma once
#include "Item.h"

class CSuperLeaf :
	public CItem
{
public:
	CSuperLeaf(D3DXVECTOR2 position);
	~CSuperLeaf();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

};