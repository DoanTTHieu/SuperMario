#pragma once

//GAME
#define SCREEN_WIDTH 272
#define SCREEN_HEIGHT 256

#define CELL_WIDTH		8
#define CELL_HEIGHT		6
//#define SCREEN_WIDTH 1500
////#define SCREEN_HEIGHT 600
//#define SCREEN_HEIGHT 900
#define KEYBOARD_BUFFER_SIZE 1024

#define ID_SCENE_WORLD_MAP	4
#define ID_SCENE_INTRO		3
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
	LIFT = 05,
	//enemy
	GOOMBA = 06,
	KOOPAS = 07,
	PIRANHA_PLANT = 8,
	VENUS_FIRE_TRAP = 9,
	BOOMERANG_BROTHER = 19,

	//item and coin
	ITEM = 10,
	COIN = 11,

	//weapon
	VENUS_FIRE_BALL = 12,

	//
	PORTAL = 13,
	MAP_POINT = 14,

	//end Scene
	LAST_ITEM = 15,
	P_SWITCH = 16,
	WM_OBJECT = 17,
	INTRO_OBJ = 18,
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

#define CONTAIN_PSWITCH	3
#define CONTAIN_COIN	2
#define CONTAIN_ITEM	1
#define CONTAIN_NULL	0

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

#define OBJECT_TYPE_LIFT			5

//enemy
#define OBJECT_TYPE_GOOMBA				11
#define OBJECT_TYPE_KOOPAS				12
#define OBJECT_TYPE_VENUS_FIRE_TRAP		13
#define OBJECT_TYPE_PIRANHA_PLANT		14
#define OBJECT_TYPE_BOOMERANG_BROTHER	15

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

//LIFT

#define LIFT_BBOX_WIDTH  48
#define LIFT_BBOX_HEIGHT 16

#define LIFT_STATE_GO_LEFT	0
#define LIFT_STATE_GO_DOWN	1

#define LIFT_SPEED_X	0.04f


//================================  HUD ============================
#define MARGINLEFT			10

#define board_margin_y		192

#define score_margin_x		110
#define score_margin_y		207

#define time_margin_x		150

#define money_margin_y		199

#define speedbar_margin_x	61

#define left_margin_x		48

#define card_1_margin_x		174
#define card_2_margin_x		199
#define card_3_margin_x		222
#define card_margin_y		198


//BOOMERANG

#define BOOMERANG_BBOX_WIDTH	16
#define BOOMERANG_BBOX_HEIGHT	16

#define BOOMERANG_GRAVITY		0.0008f
#define BOOMERANG_SPEED_X		0.1f
#define BOOMERANG_SPEED_Y		0.15f

//goomba
#define GOOMBA_WALKING_SPEED		0.05f;
#define GOOMBA_JUMP_HIGH_SPEED		0.1f;
#define GOOMBA_JUMP_LOW_SPEED		0.03f;

#define GOOMBA_BBOX_WIDTH			16
#define GOOMBA_BBOX_HEIGHT			15
#define GOOMBA_BBOX_HEIGHT_DIE		9

#define RED_PARA_BBOX_WIDTH			20
#define RED_PARA_BBOX_HEIGHT		24

#define RED_PARA_STATE_WALKING		10
#define RED_PARA_STATE_JUMP_LOW		11
#define RED_PARA_STATE_JUMP_HIGH	12

#define GOOMBA_ANI_WALKING			0
#define GOOMBA_ANI_DIE_BY_CRUSH		1
#define GOOMBA_ANI_DIE_BY_ATTACK	2

#define RED_PARA_ANI_WING_WALKING	3
#define RED_PARA_ANI_FLY_LOW		4
#define RED_PARA_ANI_FLY_HIGH		5

#define RED_PARA_ANI_WALKING		6
#define RED_PARA_ANI_DIE_BY_CRUSH	7
#define RED_PARA_ANI_DIE_BY_ATTACK	8

//EFFECT
#define ANI_FIREBALL_EFFECT					0
#define ANI_BRONZE_BRICK_BROKEN_EFFECT		1


#define EFFECT_TIME		120
#define EFFECT_TIMER	3000

//ENEMY
enum EState
{
	WALK = 01,
	DIE_BY_CRUSH = 02,
	DIE_BY_ATTACK = 03,
	DESTROYED = 04,
	FLY = 05
	//JUMP = 02,
	//ATTACK = 03,
	//STOP = 04,
	//SIT = 05,
};
#define TIME_DIE_BY_CRUSH		300

//KOOPAS

#define KOOPAS_WALKING_SPEED	0.03f;
#define KOOPAS_SPEED_Y			0.16f;
#define RED_KOOPAS_SPEED_Y		0.06f;
#define KOOPAS_DIE_MOVE_SPEED	0.2f;

#define KOOPAS_LIMIT_Y		100.0f

#define KOOPAS_BBOX_WIDTH 15
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 15

#define KOOPAS_STATE_WALKING		100
#define KOOPAS_STATE_IDLE			200
#define KOOPAS_STATE_DIE_MOVE		300
#define KOOPAS_STATE_WALKING_DOWN	400

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

//BOOMERANG
#define BOOMERANG_LIMIT				128
#define BOOMERANG_STATE_RETURN		1
#define BOOMERANG_STATE_NORMAL		2

//BOOMERANG BROTHER
#define BOOMERANG_BROTHER_BBOX_WIDTH			16
#define BOOMERANG_BROTHER_BBOX_HEIGHT			24
#define TIME_IDLE								300
#define TIME_ATTACK								1200
#define TIME_COOLDOWN							600

#define END_POSITION							32

#define BOOMERANG_BROTHER_STATE_IDLE			7
#define BOOMERANG_BROTHER_SPEED_x				0.03f

#define BROTHER_ANI_IDLE_RIGHT		0
#define BROTHER_ANI_WALK_RIGHT		1
#define BROTHER_ANI_ATTACK_RIGHT	2
#define BROTHER_ANI_DIE_RIGHT		3

#define BROTHER_ANI_IDLE_LEFT		4
#define BROTHER_ANI_WALK_LEFT		5
#define BROTHER_ANI_ATTACK_LEFT		6
#define BROTHER_ANI_DIE_LEFT		7

//BRICK

//#define BRICK_BBOX_WIDTH  16
//#define BRICK_BBOX_HEIGHT 15

#define BRICK_ANI_NORMAL		0
#define BRICK_ANI_BROKEN		1
#define BRICK_ANI_HIDDEN		2
#define STATE_BEING_TOSSED		0
#define STATE_NORMAL			1
#define STATE_BROKEN			2
#define BRICK_STATE_HIDDEN		3

//BRONZE BRICK PIECE
#define PIECE_GRAVITY		0.0008f
#define PIECE_SPEED_X		0.03f
#define PIECE_SPEED_Y		0.1f

//BULLET
#define BULLET_BBOX_WIDTH	8
#define BULLET_BBOX_HEIGHT	8
//#define BULLET_GRAVITY		0.00005f
//#define BULLET_SPEED_X		0.08f
#define BULLET_GRAVITY		0.0008f
#define BULLET_SPEED_X		0.2f
#define BULLET_SPEED_Y		0.15f
#define FIRE_BALL		1

//CAMERA
#define HUD_HEIGHT		30
#define CAMERA_SPEED_X	 0.03f

//COIN

#define COIN_SPEED_Y	0.2
//#define TIME_DEFAULT 200

//grid
#define CELL_WIDTH	8
#define CELL_HEIGHT 6

//INTRO
#define CURTAIN_ANI_OPEN			0
#define CURTAIN_ANI_CLOSE			1

//Item
#define ITEM_GRAVITY			0.0003f
#define ITEM_DISAPPEAR_TIME		5000

//MAP POINT
#define POINT_WIDTH		16
#define POINT_HEIGHT	16

//p-switch
#define P_SWITCH_ANI_ON			0
#define P_SWITCH_ANI_OFF		1
#define STATE_BEING_TOSSED		0
#define STATE_ON				1
#define STATE_OFF				2

#define TIME_CHANGE			12000

//pipe
#define PIPE_ANI_LONG		0
#define PIPE_ANI_SHORT		1
#define BLACK_ANI_SHORT		2

#define PIPE_BBOX_WIDTH			32
#define PIPE_BBOX_HEIGHT_LONG	48
#define PIPE_BBOX_HEIGHT_SHORT	32

//piranha plant
#define PLANT_PIRANHA_ANI_FACE_UP_LEFT			0

#define PIRANHA_PLANT_TIME_HIDDEN		1500
#define PIRANHA_PLANT_TIME_ATTACK		1500

//plant

#define STATE_HIDDEN		5
#define STATE_ATTACK		6
#define STATE_MOVING_UP		7
#define STATE_MOVING_DOWN	8

//score effect
#define EFFECT_COIN_SPEED_Y	0.08
#define TIME_SCORE_EFFECT 400

//super leaf
#define LEAF_ANI_LEAF	3
#define LEAF_ANI_RIGHT	4
#define LEAF_SPEED_X	0.08f
#define LEAF_SPEED_Y	0.115f
#define LEAF_SPEED_FALL	0.03f

//super mushroom

#define SUPERMUSHROOM_ANI	0
#define UP_MUSHROOM_ANI		5

//tail
#define KILL_ENEMY	200

//text
# define No_0 1110
# define No_1 1111
# define No_2 1112
# define No_3 1113
# define No_4 1114
# define No_5 1115
# define No_6 1116
# define No_7 1117
# define No_8 1118
# define No_9 1119

//venus fire trap
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

//world map
#define WM_OBJ_ANI_PLANT		0
#define WM_OBJ_ANI_HELP			1
#define WM_OBJ_ANI_GUARD_RIGHT	2
#define WM_OBJ_ANI_GUARD_LEFT	3



