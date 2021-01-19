#pragma once
#include "Item.h"
#include "Define.h"

#define LEAF_ANI_LEAF	3
#define LEAF_ANI_RIGHT	4
#define LEAF_SPEED_X	0.08f
#define LEAF_SPEED_Y	0.115f
#define LEAF_SPEED_FALL	0.03f

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