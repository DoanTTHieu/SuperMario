#pragma once
#include "Plant.h"
#include "Define.h"
#include "Timer.h"

#define VENUS_FIRE_TRAP_ANI_FACE_UP_LEFT			0
#define VENUS_FIRE_TRAP_ANI_FACE_DOWN_LEFT			1
#define VENUS_FIRE_TRAP_ANI_FACE_UP_RIGHT			2
#define VENUS_FIRE_TRAP_ANI_FACE_DOWN_RIGHT			3
#define VENUS_FIRE_TRAP_ANI_ATTACK_UP_LEFT			4
#define VENUS_FIRE_TRAP_ANI_ATTACK_DOWN_LEFT		5
#define VENUS_FIRE_TRAP_ANI_ATTACK_UP_RIGHT			6
#define VENUS_FIRE_TRAP_ANI_ATTACK_DOWN_RIGHT		7

#define TIME_HIDDEN		2500
#define TIME_ATTACK		2500

class CVenusFireTrap : public CPlant
{
	int venusFireTrapType;
public:
	CVenusFireTrap(float x, float y, int type);

	int GetVenusFireTrapType() { return venusFireTrapType; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};