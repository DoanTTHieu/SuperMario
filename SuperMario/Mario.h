#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Bullet.h"

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;

	//CBullet* bullet;
	vector<LPGAMEOBJECT> interactableObject;
	vector< LPGAMEOBJECT> listBullet;

	CBullet* CreateBullet(float x, float y, int nx)
	{
		CBullet* bullet = new CBullet({ x, y }, nx);
		//CBullet* a = new CBullet({ x, y }, nx);
		//a->SetPosition(x, y);
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
	DWORD attackStart;
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool isOnGround;
	bool isSiting;
	bool isblockJump;
	bool isFly;
	bool isAttack;

	void Jump();
	void JumpX();
	void ToRight();
	void ToLeft();
	void Idle();
	void Sit();
	void Fly();
	void Attack();
	void Stop();

	void Reset();
	void Raccoon();
	void FireMario();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};