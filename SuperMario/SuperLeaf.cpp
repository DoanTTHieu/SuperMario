#include "SuperLeaf.h"

CSuperLeaf::CSuperLeaf(D3DXVECTOR2 position) {
	this->x = position.x;
	this->y = position.y;
	//ani
	itemID = ID_ITEM_SUPER_LEAF;
}
CSuperLeaf::~CSuperLeaf()
{

}


void CSuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);
	//update roi
}