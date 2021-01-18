#pragma once

//GAME
#define SCREEN_WIDTH 272
#define SCREEN_HEIGHT 256
//#define SCREEN_WIDTH 1500
////#define SCREEN_HEIGHT 600
//#define SCREEN_HEIGHT 900
#define KEYBOARD_BUFFER_SIZE 1024

#define ID_SCENE_WORLD_MAP	4
#define ID_SCENE_1			1
#define ID_SCENE_4			2

#define PLAY_TIME		300
#define MINISEC_PER_SEC	1000

enum Type
{
	MARIO = 01,

	// static objects
	GROUND = 02,
	BRICK = 03,
	PIPE = 04,

	//enemy
	GOOMBA = 05,
	KOOPAS = 06,
	PIRANHA_PLANT = 07,
	VENUS_FIRE_TRAP = 8,

	//item and coin
	ITEM = 9,
	COIN = 10,

	//weapon
	VENUS_FIRE_BALL = 11,

	//
	PORTAL = 12,
	MAP_POINT = 13,

	//end Scene
	LAST_ITEM = 14,
	P_SWITCH = 15,
	WM_OBJECT = 16,
	INTRO_OBJ = 17,
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
	Walk_down = 13,
	Walk_up = 14,
	Idle_WM = 15
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

enum GoombaType
{
	yellow = 1,
	red_para = 2,
};

enum BrickType
{
	normal = 01,
	question = 02,
	question_broken = 03,
	bronze = 04,
};

enum VenusFireTrapType
{
	red = 0,
	green = 01
};

enum WM_Obj_Type
{
	plant = 01,
	help = 02,
	guard = 03
};

#define STATE_DESTROYED				99
//brick
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

//play scene
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_TILE_MAP	7

#define OBJECT_TYPE_MARIO			0
//static objects
#define OBJECT_TYPE_BRICK			1
#define OBJECT_TYPE_GROUND			2
#define OBJECT_TYPE_PIPE			3
#define OBJECT_TYPE_COIN			4
//enemy
#define OBJECT_TYPE_GOOMBA			11
#define OBJECT_TYPE_KOOPAS			12
#define OBJECT_TYPE_VENUS_FIRE_TRAP	13
#define OBJECT_TYPE_PIRANHA_PLANT	14
//
#define OBJECT_TYPE_PORTAL			50
#define OBJECT_MAP_POINT			51
#define OBJECT_WORLD_MAP_OBJ		52


#define OBJECT_TYPE_LAST_ITEM		100
#define OBJECT_CURTAIN				101

#define MAX_SCENE_LINE 1024

//mario
#define TIME_DEFAULT				300
#define TIME_FLY					3000
#define MARIO_TIME_ATTACK			400
#define MARIO_TIME_SHOOT			300
#define MARIO_TIME_STOP				100

#define MARIO_WALKING_SPEED				0.08f
#define MARIO_JUMP_SPEED_Y				0.25f
#define MARIO_JUMP_DEFLECT_SPEED		0.1f
#define MARIO_GRAVITY					0.0005f
#define GOOMBA_GRAVITY					0.0005f
#define KOOPA_GRAVITY					0.0004f

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
#define MARIO_ANI_IDLE_HOLD_RIGHT			7
#define MARIO_ANI_WALK_HOLD_RIGHT			8
#define MARIO_ANI_ON_AIR_HOLD_RIGHT			9

#define MARIO_ANI_IDLE_LEFT					10
#define MARIO_ANI_WALK_LEFT					11
#define MARIO_ANI_JUMP_LEFT					12
#define MARIO_ANI_FALL_LEFT					13
#define MARIO_ANI_SIT_LEFT					14
#define MARIO_ANI_RUN_LEFT					15
#define MARIO_ANI_STOP_LEFT					16
#define MARIO_ANI_IDLE_HOLD_LEFT			17
#define MARIO_ANI_WALK_HOLD_LEFT			18
#define MARIO_ANI_ON_AIR_HOLD_LEFT			19

#define mario_ANI_IDLE_RIGHT				20
#define mario_ANI_WALK_RIGHT				21
#define mario_ANI_JUMP_RIGHT				22
#define mario_ANI_RUN_RIGHT					23
#define mario_ANI_STOP_RIGHT				24
#define mario_ANI_IDLE_HOLD_RIGHT			25
#define mario_ANI_WALK_HOLD_RIGHT			26
#define mario_ANI_ON_AIR_HOLD_RIGHT			27

#define mario_ANI_IDLE_LEFT					28
#define mario_ANI_WALK_LEFT					29
#define mario_ANI_JUMP_LEFT					30
#define mario_ANI_RUN_LEFT					31
#define mario_ANI_STOP_LEFT					32
#define mario_ANI_IDLE_HOLD_LEFT			33
#define mario_ANI_WALK_HOLD_LEFT			34
#define mario_ANI_ON_AIR_HOLD_LEFT			35

#define MARIO_ANI_DIE						36

#define RACCOON_ANI_IDLE_RIGHT				37
#define RACCOON_ANI_WALK_RIGHT				38
#define RACCOON_ANI_RUN_RIGHT				39
#define RACCOON_ANI_JUMP_RIGHT				40
#define RACCOON_ANI_STOP_RIGHT				41
#define RACCOON_ANI_FIGHT_IDLE_RIGHT		42
#define RACCOON_ANI_SIT_RIGHT				43
#define RACCOON_ANI_FALL_RIGHT				44
#define RACCOON_ANI_WAG_TAIL_RIGHT			45
#define RACCOON_ANI_FLY_RIGHT				46
#define RACCOON_ANI_IDLE_HOLD_RIGHT			47
#define RACCOON_ANI_WALK_HOLD_RIGHT			48
#define RACCOON_ANI_ON_AIR_HOLD_RIGHT		49

#define RACCOON_ANI_IDLE_LEFT				50
#define RACCOON_ANI_WALK_LEFT				51
#define RACCOON_ANI_RUN_LEFT				52
#define RACCOON_ANI_JUMP_LEFT				53
#define RACCOON_ANI_STOP_LEFT				54
#define RACCOON_ANI_FIGHT_IDLE_LEFT			55
#define RACCOON_ANI_SIT_LEFT				56
#define RACCOON_ANI_FALL_LEFT				57
#define RACCOON_ANI_WAG_TAIL_LEFT			58
#define RACCOON_ANI_FLY_LEFT				59
#define RACCOON_ANI_IDLE_HOLD_LEFT			60
#define RACCOON_ANI_WALK_HOLD_LEFT			61
#define RACCOON_ANI_ON_AIR_HOLD_LEFT		62

#define FIRE_ANI_IDLE_RIGHT					63
#define FIRE_ANI_WALK_RIGHT					64
#define FIRE_ANI_RUN_RIGHT					65
#define FIRE_ANI_JUMP_RIGHT					66
#define FIRE_ANI_STOP_RIGHT					67
#define FIRE_ANI_FIGHT_IDLE_RIGHT			68
#define FIRE_ANI_ATTACK_RIGHT				69
#define FIRE_ANI_SIT_RIGHT					70
#define FIRE_ANI_FALL_RIGHT					71
#define FIRE_ANI_IDLE_HOLD_RIGHT			72
#define FIRE_ANI_WALK_HOLD_RIGHT			73
#define FIRE_ANI_ON_AIR_HOLD_RIGHT			74

#define FIRE_ANI_IDLE_LEFT					75
#define FIRE_ANI_WALK_LEFT					76
#define FIRE_ANI_RUN_LEFT					77
#define FIRE_ANI_JUMP_LEFT					78
#define FIRE_ANI_STOP_LEFT					79
#define FIRE_ANI_FIGHT_IDLE_LEFT			80
#define FIRE_ANI_ATTACK_LEFT				81
#define FIRE_ANI_SIT_LEFT					82
#define FIRE_ANI_FALL_LEFT					83
#define FIRE_ANI_IDLE_HOLD_LEFT				84
#define FIRE_ANI_WALK_HOLD_LEFT				85
#define FIRE_ANI_ON_AIR_HOLD_LEFT			86

#define mario_WORLD_MAP						87
#define MARIO_WORLD_MAP						88
#define RACCOON_WORLD_MAP					89
#define FIRE_WORLD_MAP						90

//==============================================SIZE========================================
#define MARIO_BIG_BBOX_WIDTH				14
#define MARIO_BIG_BBOX_HEIGHT				27

#define MARIO_RACCOON_BBOX_WIDTH			15
#define MARIO_RACCOON_BBOX_HEIGHT			28

#define MARIO_SMALL_BBOX_WIDTH				13
#define MARIO_SMALL_BBOX_HEIGHT				15

#define MARIO_UNTOUCHABLE_TIME				2000

//PLANT
#define PLANT_BBOX_WIDTH				16
#define PLANT_BBOX_LOW					24
#define PLANT_BBOX_HIGH					32
//plant speed
#define PLANT_SPEED_Y		0.05f;