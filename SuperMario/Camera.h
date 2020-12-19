#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Utils.h"
#include "Game.h"

#define HUD_HEIGHT		30
#define CAMERA_SPEED_X	 0.065f

class CCamera
{
private:
	static CCamera* __instance;
	D3DXVECTOR2 position;

	int width;
	int height;

	bool lockUpdate;
public:
	CCamera();
	~CCamera() {}
	static CCamera* GetInstance();
	void Update(D3DXVECTOR2 playerPos, D3DXVECTOR2 start, D3DXVECTOR2 end, bool isFlying);

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void LockUpdate() { lockUpdate = true; }
	void UnlockUpdate() { lockUpdate = false; }
};

typedef CCamera* LPCAMERA;
