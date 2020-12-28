#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Bullet.h"
#include "Timer.h"
#include "Tail.h"
#include "Koopas.h"

class CMario : public CGameObject
{
	static CMario* __instance;

	int score;
	int coin;
	int level;
	int life;
	int time;
	int stage;
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
	static CMario* GetInstance();

	vector< LPGAMEOBJECT> listBullet;

	CMario(float x = 0.0f, float y = 0.0f);
	~CMario();

	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObj, vector <LPGAMEOBJECT>* coItem, vector<LPGAMEOBJECT>* listEffect);
	virtual void Render();

	void SetState(int state);
	void SetStage(int stage) { this->stage = stage; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	
	bool isOnGround;
	bool isSitting;
	bool isblockJump;
	bool isAttack;
	bool isWaggingTail;
	bool isWaitingForAni;
	bool canHoldShell;
	bool isHolding;
	bool isFlying;//cam_y theo mario khi bay, ko theo khi nhay
	bool isFalling;
	bool isIdling;
	bool inHiddenArea;

	bool isAutoGo;

	bool canWalkLeft;
	bool canWalkRight;
	bool canWalkUp;
	bool canWalkDown;
	bool canSwitchScene;
	bool canGoThroughPipe_Up;
	bool canGoThroughPipe_Down;

	LPGAMEOBJECT colidingGround;

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

	int GetCoin() { return coin; }
	void SetCoin(int x) { coin = x; }
	void AddCoin() { coin++; }

	int GetScore() { return score; }
	void SetScore(int x) { score = x; }
	void AddScore(int x) { score += x; }

	int GetLevel() { return level; }
	void SetLevel(int l) { level = l; }

	int GetLife() { return life; }
	void SetLife(int x) { life = x; }
	void SubLife() { life -= 1; }
	void AddLife() { life += 1; }

	void CollideWithItem(vector<LPGAMEOBJECT>* listItem);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};