#pragma once

enum Type
{
	MARIO = 01,
	//
	GROUND = 02,
	BRICK = 03,
	//
	GOOMBA = 04,
	KOOPAS = 05,

};

enum MState
{
	Idle = 01,
	Walk_right = 02,
	Walk_left = 03,
	Jump = 04,
	Jump_low = 05,
	Die = 06,
	Sit = 07,
	Run_right = 8,
	Run_left = 9,
	Fly = 10,
	Stop = 11,
	Attack = 12,
};

enum Level
{
	Small = 01,
	Big = 02,
	Raccoon = 03,
	Fire = 04,
};

enum KoopaType
{
	Green_troopa = 01,
	Red_troopa = 02,
	Green_paratroopa = 03,
	Red_paratroopa = 04,
};

enum BrickType
{
	normal = 01,
	question = 02,
	question_broken = 03,
	bronze = 04,
};

#define STATE_DESTROYED				99
//brick
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 15

//play scene
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_TILE_MAP	7

#define OBJECT_TYPE_MARIO		0
#define OBJECT_TYPE_BRICK		1
#define OBJECT_TYPE_GOOMBA		2
#define OBJECT_TYPE_KOOPAS		3
#define OBJECT_TYPE_RED_KOOPA	4
#define OBJECT_TYPE_GROUND		40
#define OBJECT_TYPE_PORTAL		50

#define MAX_SCENE_LINE 1024

//mario
#define TIME_FLY					3000
#define MARIO_TIME_ATTACK			400
#define MARIO_TIME_SHOOT			300
#define MARIO_TIME_STOP				100

#define MARIO_WALKING_SPEED				0.08f
#define MARIO_JUMP_SPEED_Y				0.25f
#define MARIO_JUMP_DEFLECT_SPEED		0.1f
#define MARIO_GRAVITY					0.0005f

#define MARIO_FALLING_SPEED_Y			0.45f
#define MARIO_DIE_DEFLECT_SPEED			0.5f
#define MARIO_RUN_SPEED_THRESH			0.16f
#define MARIO_ACCELERATION				0.0006f
#define mario_ACCELERATION				0.0003f

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
#define RACCOON_ANI_WAG_TAIL_RIGHT			33
#define RACCOON_ANI_FLY_RIGHT				34


#define RACCOON_ANI_IDLE_LEFT				35
#define RACCOON_ANI_WALK_LEFT				36
#define RACCOON_ANI_RUN_LEFT				37
#define RACCOON_ANI_JUMP_LEFT				38
#define RACCOON_ANI_STOP_LEFT				39
#define RACCOON_ANI_FIGHT_IDLE_LEFT			40//
#define RACCOON_ANI_SIT_LEFT				41
#define RACCOON_ANI_FALL_LEFT				42
#define RACCOON_ANI_WAG_TAIL_LEFT			43
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


#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_RACCOON_BBOX_WIDTH  15
#define MARIO_RACCOON_BBOX_HEIGHT 28

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 2000
