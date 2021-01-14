#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Utils.h"
#include "Game.h"
//#include "Mario.h"

#define HUD_HEIGHT		30
#define CAMERA_SPEED_X	 0.06f

class CCamera
{
private:
	static CCamera* __instance;
	D3DXVECTOR2 position;

	int width;
	int height;
	float vx;
	bool lockUpdate;
	bool lockUpdateVx;
public:
	CCamera();
	~CCamera() {}
	static CCamera* GetInstance();
	void Update(ULONGLONG dt, D3DXVECTOR2 playerPos, D3DXVECTOR2 start, D3DXVECTOR2 end, bool isFlying);

	float GetPositionX() { return position.x; }
	float GetSpeedX() { return vx; }

	void SetSpeedX(float x) { vx = x; }
	void ResetPosition() { position.x = 0; position.y = 0; }
	void Move(ULONGLONG dt)
	{
		position.x += CAMERA_SPEED_X * dt;
	}

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	bool IsLockUpdate() { return lockUpdate; }
	void LockUpdate() { lockUpdate = true; }
	void UnlockUpdate() { lockUpdate = false; }

	bool IsLockUpdateVx() { return lockUpdateVx; }
	void LockUpdateVx() { lockUpdateVx = true; }
	void UnlockUpdateVx() { lockUpdateVx = false; }
};

typedef CCamera* LPCAMERA;
