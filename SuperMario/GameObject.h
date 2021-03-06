#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include "Define.h"
#include "Sprites.h"
#include "Animations.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;
	int ny;

	int state;
	int ani;

	float start_x;
	float start_y;

	int type;

	bool isInCam;

	ULONGLONG dt;

	LPANIMATION_SET animation_set;

public:
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	float GetPositionX() { return x; }
	float GetPositionY() { return y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return state; }
	int GetType() { return type; }
	void SetType(int x) { type = x; }
	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	bool AABBCheck(float l_a, float t_a, float r_a, float b_a, float l_b, float t_b, float r_b, float b_b);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy,
		LPGAMEOBJECT& objx,
		LPGAMEOBJECT& objy);

	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);
	CGameObject();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(ULONGLONG dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	virtual void ResetAnimation();
	bool IsOutOfCamera();
	bool IsAABB(LPGAMEOBJECT object);
	bool IsCollidingWithObject(LPGAMEOBJECT object);
	bool IsCollidingWithObjectNx1(LPGAMEOBJECT object);
	bool IsCollidingWithObjectNx_1(LPGAMEOBJECT object);
	bool IsCollidingWithObjectNx(LPGAMEOBJECT object);
	bool IsCollidingWithObjectNy(LPGAMEOBJECT object);
	bool IsCollidingWithObjectNy1(LPGAMEOBJECT object);
	bool IsCollidingWithObjectNy_1(LPGAMEOBJECT object);
	~CGameObject();
};

