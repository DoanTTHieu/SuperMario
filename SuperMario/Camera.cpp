#include "Camera.h"

CCamera* CCamera::__instance = nullptr;

CCamera::CCamera()
{
	vx = 0;
	height = SCREEN_HEIGHT-32;
	width = SCREEN_WIDTH;
	lockUpdate = false;
	lockUpdateY = false;
	lockUpdateVx = false;
	position = { 0,0 };
	CGame::GetInstance()->SetCamPos(0, 250);
}

void CCamera::Update(D3DXVECTOR2 playerPos, D3DXVECTOR2 start, D3DXVECTOR2 end, bool isFlying)
{
	DebugOut(L"endxxxxxxxxxxx: %f\n", start.x);
	DebugOut(L"x: %f\n", position.x);

	if (lockUpdate)
		return;
	if (lockUpdateVx)
	{

	}
	else
	{
		position.x = playerPos.x - width / 2 + 16;

		// Check if camera out of world screen
		if (position.x > end.x)
			position.x = end.x;
		if (position.x < start.x)
			position.x = start.x;

		if (playerPos.x < start.x)
			CMario::GetInstance()->SetPosition(start.x, playerPos.y);
		if (playerPos.x > end.x)
			CMario::GetInstance()->SetPosition(end.x, playerPos.y);

		if (lockUpdateY)
		{
			CGame::GetInstance()->SetCamPosX(position.x);
			CGame::GetInstance()->SetCamPosY(608 - SCREEN_HEIGHT + 110);
			return;

		}			//them dieu kien van toc mario am thi cam theo và trong khoan <end.y		
		if (isFlying || playerPos.y < end.y-64)
		{
			position.y = int(playerPos.y - height / 2 + 32);
		}
		else
			position.y = end.y;

		if (position.y < start.y)
			position.y = start.y;
		CGame::GetInstance()->SetCamPos(position.x, position.y);
	}

}

CCamera* CCamera::GetInstance()
{
	if (!__instance)
		__instance = new CCamera();

	return __instance;
}
