#include "Camera.h"

CCamera* CCamera::__instance = nullptr;

CCamera::CCamera()
{
	vx = 0;
	height = SCREEN_HEIGHT- HUD_HEIGHT;
	width = SCREEN_WIDTH;
	lockUpdate = false;
	lockUpdateVx = true;
	lockY = true;
	position = { 0,0 };
	CGame::GetInstance()->SetCamPos(0, 250);
}

void CCamera::Update(ULONGLONG dt, D3DXVECTOR2 playerPos, D3DXVECTOR2 start, D3DXVECTOR2 end, bool isFlying, bool isOnGround)
{
	if (lockUpdate)
		return;
	if (!lockUpdateVx)
	{
		position.x += CAMERA_SPEED_X * dt;
		//if (position.x < (playerPos.x - width / 2 + 16))
		//	position.x = playerPos.x - width / 2 + 16;
	}
	else
	{
		position.x = playerPos.x - width / 2 + MARIO_BIG_BBOX_WIDTH;
	}

	// Check if camera out of world screen
	if (position.x > end.x)
		position.x = end.x;
	if (position.x < start.x)
		position.x = start.x;

	if (playerPos.y < end.y && isFlying)
		lockY = false;
	if (playerPos.y > end.y && isOnGround)
		lockY = true;

	if (isFlying)
	{
		if (int(playerPos.y - height / 2 + HUD_HEIGHT) < end.y)
			position.y = int(playerPos.y - height / 2 + HUD_HEIGHT);
	}
	else if (!lockY)
	{
		if (int(playerPos.y - height / 2 + HUD_HEIGHT) < end.y)
			position.y = int(playerPos.y - height / 2 + HUD_HEIGHT);
	}
	else if (lockY)
	{
		position.y = end.y;
	}

	if (position.y < start.y)
		position.y = start.y;
	CGame::GetInstance()->SetCamPos(position.x, position.y);

}

CCamera* CCamera::GetInstance()
{
	if (!__instance)
		__instance = new CCamera();

	return __instance;
 }
