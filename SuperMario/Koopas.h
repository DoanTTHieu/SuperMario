#pragma once

#include "GameObject.h"
#include"Utils.h"
#include "Timer.h"
#include "Define.h"
#include "Enemy.h"

class CKoopas : public CEnemy
{
	int Ktype;

	D3DXVECTOR2 start = { -1,-1 };
	D3DXVECTOR2 end = { -1,-1 };

public:
	bool checkSupine = false;
	bool isBeingHeld = false;
	bool checkDone = false;
	bool isRelife = false;
	LPGAMEOBJECT colidingGround;


	CTimer* idleTimer = new CTimer(KOOPAS_TIME_IDLE);
	CTimer* koopasTimer = new CTimer(KOOPAS_TIME_IDLE- KOOPAS_TIME_RELIFE);

	CKoopas();
	CKoopas(int type, float x, float y);
	virtual void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int GetKoopaType() { return Ktype; }
	void SetKoopaType(int type) { Ktype = type; }

	void Idle();
	void IdleSupine();
};