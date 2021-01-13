#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Utils.h"
#include "Game.h"
//#include "Mario.h"

#define HUD_HEIGHT		30
#define CAMERA_SPEED_X	 0.065f

class CCamera
{
private:
	static CCamera* __instance;
	D3DXVECTOR2 position;

	int width;
	int height;
	float vx;
	bool lockUpdate;
	bool lockUpdateY;
	bool lockUpdateVx;
public:
	CCamera();
	~CCamera() {}
	static CCamera* GetInstance();
	void Update(D3DXVECTOR2 playerPos, D3DXVECTOR2 start, D3DXVECTOR2 end, bool isFlying);

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	bool IsLockUpdate() { return lockUpdate; }
	void LockUpdate() { lockUpdate = true; }
	void UnlockUpdate() { lockUpdate = false; }

	bool IsLockUpdateY() { return lockUpdateY; }
	void LockUpdateY() { lockUpdateY = true; }
	void UnlockUpdateY() { lockUpdateY = false; }

	bool IsLockUpdateVx() { return lockUpdateVx; }
	void LockUpdateVx() { lockUpdateVx = true; }
	void UnlockUpdateVx() { lockUpdateVx = false; }
};

typedef CCamera* LPCAMERA;
