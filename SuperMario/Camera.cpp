#include "Camera.h"

CCamera* CCamera::__instance = nullptr;

CCamera::CCamera()
{
	height = SCREEN_HEIGHT-32;
	width = SCREEN_WIDTH;
	lockUpdate = false;
	CGame::GetInstance()->SetCamPos(0, 250);
}

void CCamera::Update(D3DXVECTOR2 playerPos, D3DXVECTOR2 start, D3DXVECTOR2 end, bool isFlying)
{
	if (lockUpdate)
		return;
	position.x = playerPos.x - width / 2 + 16;

	// Check if camera out of world screen
	if (position.x > end.x)
		position.x = end.x;
	if (position.x < start.x)
		position.x = start.x;

	if (lockUpdateY)
	{
		CGame::GetInstance()->SetCamPosX(position.x);
		CGame::GetInstance()->SetCamPosY(608 - SCREEN_HEIGHT + 110);
		return;

	}
	if (isFlying|| playerPos.y < end.y-64)
	{
		position.y = int(playerPos.y - height / 2 + 16);
	}
	else
		position.y = end.y;

	if (position.y > end.y)
		position.y = end.y;
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
