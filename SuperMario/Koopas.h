#pragma once

#include "GameObject.h"
#include"Utils.h"

#define KOOPAS_WALKING_SPEED 0.03f;
#define KOOPAS_DIE_MOVE_SPEED 0.1f;


#define KOOPAS_BBOX_WIDTH 15
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_DIE_MOVE 300

#define KOOPAS_ANI_WALKING_LEFT 0
#define KOOPAS_ANI_WALKING_RIGHT 1
#define KOOPAS_ANI_DIE 2
#define KOOPAS_ANI_DIE_MOVE 3

class CKoopas : public CGameObject
{
	

public:
	CKoopas();
	virtual void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};