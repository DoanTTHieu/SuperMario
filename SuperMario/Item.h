#pragma once
#include "GameObject.h"
#include "Timer.h"
#include "Define.h"

enum ItemID
{
	superMushroom = 0,
	superLeaf = 01,
	fireFlower = 02,
	upMushroom = 03,
};

class CItem :
	public CGameObject {
public:
	int itemID;
	CItem();
	~CItem();
	
	CTimer* disapperTimer = new CTimer(ITEM_DISAPPEAR_TIME);
	int GetItemID() { return itemID; }

	virtual void Render() = 0;
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};