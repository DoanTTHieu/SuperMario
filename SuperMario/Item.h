#pragma once
#include "GameObject.h"
#include "Timer.h"

#define ITEM_GRAVITY			0.0003f
#define ITEM_DISAPPEAR_TIME		5000
#define ID_ITEM_SUPER_MUSHROOM	0
#define ID_ITEM_SUPER_LEAF		1
#define ID_ITEM_FIRE_FLOWER		2


class CItem :
	public CGameObject {
public:
	int itemID;
public:
	CItem();
	~CItem();
	//CTimer* disapperTimer = new CTimer(ITEM_DISAPPEAR_TIME);

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};