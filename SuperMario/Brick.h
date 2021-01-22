#pragma once
#include "GameObject.h"
# include "Define.h"

class CBrick : public CGameObject
{

public:
	bool isBroken;
	bool diddropItem = false;
	int Btype;
	int containItem;
	int sl;
	vector<LPGAMEOBJECT> listPiece;

public:
	CBrick(float x, float y, int type, int isContain, int sl);
	~CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects);

	int GetBrickType() { return Btype; }
	int GetItemRemaining() { return sl; };
	void SetBrickType(int type) { Btype = type; }
	
	void SetState(int state);
};