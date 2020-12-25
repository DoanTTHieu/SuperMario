#pragma once
#include "GameObject.h"
#include "Timer.h"

#define ITEM_GRAVITY			0.0003f
#define ITEM_DISAPPEAR_TIME		5000

enum ItemID
{
	superMushroom = 0,
	superLeaf = 01,
	fireFlower = 02,
};

class CItem :
	public CGameObject {
public:
	int itemID;
public:
	CItem();
	~CItem();
	
	CTimer* disapperTimer = new CTimer(ITEM_DISAPPEAR_TIME);
	int GetItemID() { return itemID; }

	virtual void Render();
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};