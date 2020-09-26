#include "Koopas.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//float l, t, r, b;
	//gomba->getbou(l, t, r, b);
	//check(lm, tm, rm, btm, l, t, r, b);
	//aabb
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_DIE_MOVE)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += 0.2 * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
	//
	// TO-DO: make sure Koopas can interact with the world and to each of them too!
	// 

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
			//x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;///chinh lai xet va cham koopas voi brick -> cai nay do no xet y trung hop r

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_DIE_MOVE) {
		ani = KOOPAS_ANI_DIE_MOVE;
	}
	else if (state == KOOPAS_STATE_DIE) {
		ani = KOOPAS_ANI_DIE;
	}
	else if (vx > 0) { 
		nx = 1;
		ani = KOOPAS_ANI_WALKING_RIGHT; 
	}
	else if (vx <= 0)
	{
		nx = -1;
		ani = KOOPAS_ANI_WALKING_LEFT;
	}
	
	//DebugOut(L"ani:%d \n", ani);
	animation_set->at(ani)->Render(x, y);
	
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE_MOVE:	
		vx = KOOPAS_DIE_MOVE_SPEED;
		//y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		break;
	case KOOPAS_STATE_DIE:
		//y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		//vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
	}

}