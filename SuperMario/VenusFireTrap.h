#pragma once
#include "Plant.h"
#include "Define.h"
#include "Timer.h"
#include "VenusFireBall.h"

#define VENUS_FIRE_TRAP_ANI_FACE_UP_LEFT			0
#define VENUS_FIRE_TRAP_ANI_FACE_DOWN_LEFT			1
#define VENUS_FIRE_TRAP_ANI_FACE_UP_RIGHT			2
#define VENUS_FIRE_TRAP_ANI_FACE_DOWN_RIGHT			3
#define VENUS_FIRE_TRAP_ANI_ATTACK_UP_LEFT			4
#define VENUS_FIRE_TRAP_ANI_ATTACK_DOWN_LEFT		5
#define VENUS_FIRE_TRAP_ANI_ATTACK_UP_RIGHT			6
#define VENUS_FIRE_TRAP_ANI_ATTACK_DOWN_RIGHT		7

#define VENUS_FIRE_TRAP_TIME_HIDDEN		2500
#define VENUS_FIRE_TRAP_TIME_ATTACK		2500

#define DISTANCE_THRESH					48

enum ZoneOfMario
{
	l_up_near = 0,
	l_up_far = 1,
	l_down_near = 2,
	l_down_far = 3,
	r_up_near = 4,
	r_up_far = 5,
	r_down_near = 6,
	r_down_far = 7
};

class CVenusFireTrap : public CPlant
{
	int venusFireTrapType;
	bool isAttack = false;
	int zoneOfMario = 0;
	CVenusFireBall *fireBall = nullptr;
public:
	CVenusFireTrap(float x, float y, int type);

	int GetVenusFireTrapType() { return venusFireTrapType; }

	bool CheckDistanceNear(D3DXVECTOR4 player);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects, D3DXVECTOR4 player);
	virtual void Render();
	virtual void SetState(int state);
};