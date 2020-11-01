#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Bullet.h"
#include "Timer.h"

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	vector<LPGAMEOBJECT> interactableObject;
	vector< LPGAMEOBJECT> listBullet;

	CBullet* CreateBullet(float x, float y, int nx)
	{
		CBullet* bullet = new CBullet({ x, y }, nx);
		return bullet;
	}
public:
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	bool IsAABB(LPGAMEOBJECT object);
	void CheckInteraction();

	void SetState(int state);
	
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool isOnGround;
	bool isSitting;
		
	bool isblockJump;
	bool isAttack;
	bool isWaggingTail;
	bool isWaitingForAni;

	CTimer* flyTimer = new CTimer(TIME_FLY);

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

	void Reset();
	void Raccoon();
	void FireMario();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};