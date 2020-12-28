#pragma once
#include "Animations.h"

class CSpeedBar 
{
	LPANIMATION_SET bar;
public:
	CSpeedBar();
	~CSpeedBar();
	
	void Render(float x, float y, float vx);
};