#pragma once
#include "Item.h"
#define		W	8
#define		S0	20
#define		phi	-0.5f

class CSuperLeaf :
	public CItem
{
public:
	CSuperLeaf(D3DXVECTOR2 position);
	~CSuperLeaf();
	bool isFalling = false;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

};