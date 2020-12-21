#pragma once

#include "GameObject.h"
#include"Utils.h"
#include "Timer.h"
#include "Define.h"
#include "Enemy.h"

#define KOOPAS_WALKING_SPEED	0.03f;
#define KOOPAS_SPEED_Y			0.16f;
#define KOOPAS_DIE_MOVE_SPEED	0.2f;


#define KOOPAS_BBOX_WIDTH 15
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 15

#define KOOPAS_STATE_WALKING	100
#define KOOPAS_STATE_IDLE		200
#define KOOPAS_STATE_DIE_MOVE	300 

#define KOOPAS_ANI_WALKING_LEFT		0
#define KOOPAS_ANI_WALKING_RIGHT	1
#define KOOPAS_ANI_DIE				2
#define KOOPAS_ANI_DIE_SUPINE		3
#define KOOPAS_ANI_RELIFE			4
#define KOOPAS_ANI_RELIFE_SUPINE	5
#define KOOPAS_ANI_DIE_MOVE			6
#define KOOPAS_ANI_DIE_MOVE_SUPINE	7

#define PARA_KOOPAS_ANI_LEFT		8
#define PARA_KOOPAS_ANI_RIGHT		9


#define KOOPAS_TIME_IDLE			8000
#define KOOPAS_TIME_RELIFE			1000

class CKoopas : public CEnemy
{
	int Ktype;

public:
	bool checkSupine = false;
	bool isBeingHeld = false;
	bool checkDone = false;
	bool isRelife = false;
	LPGAMEOBJECT colidingGround;


	CTimer* idleTimer = new CTimer(KOOPAS_TIME_IDLE);
	CTimer* koopasTimer = new CTimer(KOOPAS_TIME_IDLE- KOOPAS_TIME_RELIFE);

	CKoopas();
	CKoopas(int x);
	virtual void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int GetKoopaType() { return Ktype; }
	void SetKoopaType(int type) { Ktype = type; }

	void Idle();
	void IdleSupine();
};