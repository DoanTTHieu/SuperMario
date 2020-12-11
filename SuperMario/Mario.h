#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Bullet.h"
#include "Timer.h"
#include "Tail.h"
#include "Koopas.h"

class CMario : public CGameObject
{
	int score;
	int coin;
	int level;
	int untouchable;
	ULONGLONG untouchable_start;

	vector<LPGAMEOBJECT> interactableObject;
	//vector< LPGAMEOBJECT> listEffect;
	
	CTail* tail = new CTail();
	CKoopas* koopas = new CKoopas();

	CBullet* CreateBullet(float x, float y, int nx)
	{
		CBullet* bullet = new CBullet({ x, y }, nx);
		return bullet;
	}


public:
	vector< LPGAMEOBJECT> listBullet;

	CMario(float x = 0.0f, float y = 0.0f);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObj, vector <LPGAMEOBJECT>* coItem);
	virtual void Render();
	void CheckInteraction();

	void SetState(int state);
	
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	bool isOnGround;
	bool isSitting;
		
	bool isblockJump;
	bool isAttack;
	bool isWaggingTail;
	bool isWaitingForAni;
	bool canHoldShell;
	bool isHolding;

	CTimer* flyTimer = new CTimer(TIME_FLY);
	ULONGLONG attackStart;

	void Jump();
	void JumpX();
	void ToRight();
	void ToLeft();
	void Idle();
	void Sit();
	void Fly();
	void Attack();
	void Stop();
	void DecreaseSpeedToStop();
	void UpdateLevel();
	void WalkingRight();
	void WalkingLeft();
	int changedNx = 0;

	void Reset();
	void Small();
	void Big();
	void Raccoon();
	void FireMario();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};