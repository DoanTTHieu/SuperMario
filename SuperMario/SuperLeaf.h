#pragma once
#include "Item.h"
#include "Define.h"

class CSuperLeaf :
	public CItem
{
	float left, right;
public:
	CSuperLeaf(D3DXVECTOR2 position);
	~CSuperLeaf();
	bool isFalling;
	virtual void Render();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);

};