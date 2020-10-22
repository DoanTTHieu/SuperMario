#pragma once
#include "GameObject.h"

//#define MARIO_WALKING_SPEED		0.12f 
////0.1f
//#define MARIO_JUMP_SPEED_Y		0.35f
//#define MARIO_JUMP_DEFLECT_SPEED 0.2f
//#define MARIO_GRAVITY			0.001f
//#define MARIO_DIE_DEFLECT_SPEED	 0.5f
//#define MARIO_ACCELERATION		0.002f


#define MARIO_WALKING_SPEED				0.08f
#define MARIO_JUMP_SPEED_Y				0.25f
#define MARIO_JUMP_DEFLECT_SPEED		0.1f
#define MARIO_GRAVITY					0.0005f
#define MARIO_FALLING_SPEED_Y			0.45f
#define MARIO_DIE_DEFLECT_SPEED			0.5f
#define MARIO_RUN_SPEED_THRESH			0.24f
#define MARIO_ACCELERATION				0.0003f

#define MARIO_STATE_IDLE				0
#define MARIO_STATE_WALKING_RIGHT		1
#define MARIO_STATE_WALKING_LEFT		2
#define MARIO_STATE_JUMP				3
#define MARIO_STATE_JUMP_LOW			4
#define MARIO_STATE_DIE					5
#define MARIO_STATE_SIT					6
#define MARIO_STATE_RUN_RIGHT			8
#define MARIO_STATE_RUN_LEFT			9
#define MARIO_STATE_FLY					10


#define MARIO_ANI_IDLE_RIGHT				0
#define MARIO_ANI_WALK_RIGHT				1
#define MARIO_ANI_JUMP_RIGHT				2
#define MARIO_ANI_FALL_RIGHT				3
#define MARIO_ANI_SIT_RIGHT					4
#define MARIO_ANI_RUN_RIGHT					5
#define MARIO_ANI_STOP_RIGHT				6


#define MARIO_ANI_IDLE_LEFT					7
#define MARIO_ANI_WALK_LEFT					8
#define MARIO_ANI_JUMP_LEFT					9
#define MARIO_ANI_FALL_LEFT					10
#define MARIO_ANI_SIT_LEFT					11
#define MARIO_ANI_RUN_LEFT					12
#define MARIO_ANI_STOP_LEFT					13

#define mario_ANI_IDLE_RIGHT				14
#define mario_ANI_WALK_RIGHT				15
#define mario_ANI_JUMP_RIGHT				16
#define mario_ANI_RUN_RIGHT					17
#define mario_ANI_STOP_RIGHT				18


#define mario_ANI_IDLE_LEFT					19
#define mario_ANI_WALK_LEFT					20
#define mario_ANI_JUMP_LEFT					21
#define mario_ANI_RUN_LEFT					22
#define mario_ANI_STOP_LEFT					23


#define MARIO_ANI_DIE						24

#define RACCOON_ANI_IDLE_RIGHT				25
#define RACCOON_ANI_WALK_RIGHT				26
#define RACCOON_ANI_RUN_RIGHT				27
#define RACCOON_ANI_JUMP_RIGHT				28
#define RACCOON_ANI_STOP_RIGHT				29
#define RACCOON_ANI_FIGHT_IDLE_RIGHT		30//
#define RACCOON_ANI_SIT_RIGHT				31
#define RACCOON_ANI_FALL_RIGHT				32
#define RACCOON_ANI_ATTACK_RIGHT			33
#define RACCOON_ANI_FLY_RIGHT				34


#define RACCOON_ANI_IDLE_LEFT				35
#define RACCOON_ANI_WALK_LEFT				36
#define RACCOON_ANI_RUN_LEFT				37
#define RACCOON_ANI_JUMP_LEFT				38
#define RACCOON_ANI_STOP_LEFT				39
#define RACCOON_ANI_FIGHT_IDLE_LEFT			40//
#define RACCOON_ANI_SIT_LEFT				41
#define RACCOON_ANI_FALL_LEFT				42
#define RACCOON_ANI_ATTACK_LEFT				43
#define RACCOON_ANI_FLY_LEFT				44

#define FIRE_ANI_IDLE_RIGHT				45
#define FIRE_ANI_WALK_RIGHT				46
#define FIRE_ANI_RUN_RIGHT				47
#define FIRE_ANI_JUMP_RIGHT				48
#define FIRE_ANI_STOP_RIGHT				49
#define FIRE_ANI_FIGHT_IDLE_RIGHT		50//
#define FIRE_ANI_ATTACK_RIGHT			51
#define FIRE_ANI_SIT_RIGHT				52
#define FIRE_ANI_FALL_RIGHT				53

#define FIRE_ANI_IDLE_LEFT				54
#define FIRE_ANI_WALK_LEFT				55
#define FIRE_ANI_RUN_LEFT				56
#define FIRE_ANI_JUMP_LEFT				57
#define FIRE_ANI_STOP_LEFT				58
#define FIRE_ANI_FIGHT_IDLE_LEFT		59//
#define FIRE_ANI_ATTACK_LEFT			60
#define FIRE_ANI_SIT_LEFT				61
#define FIRE_ANI_FALL_LEFT				62



#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON	3
#define	MARIO_LEVEL_FIRE	4

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_RACCOON_BBOX_WIDTH  14
#define MARIO_RACCOON_BBOX_HEIGHT 28

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 2000


class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
	


	vector<LPGAMEOBJECT> interactableObject;
public:
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	bool IsAABB(LPGAMEOBJECT object);
	void CheckInteraction();

	void SetState(int state);
	
	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; }
	DWORD startRun;
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool isOnGround;
	bool isSiting;
	bool isblockJump;


	void Jump();
	void JumpX();
	void ToRight();
	void ToLeft();
	void Idle();
	void Sit();
	void Fly();
	void Reset();
	void Raccoon();
	void FireMario();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};