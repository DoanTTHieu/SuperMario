#include "SuperMushroom.h"

CSuperMushroom::CSuperMushroom(D3DXVECTOR2 position) {
	this->x = position.x;
	this->y = position.y;
	//ani
	itemID = ID_ITEM_SUPER_MUSHROOM;
}
CSuperMushroom::~CSuperMushroom()
{

}


void CSuperMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);
	//update roi
}