#pragma once
#pragma once
#include <Windows.h>

class CTimer
{
	int start;
	int limitedTime;

public:
	CTimer(int limitedTime) { this->limitedTime = limitedTime; start = 0; }

	void Start() { start = GetTickCount(); }
	void Stop() { start = 0; }
	bool IsTimeUp() { return GetTickCount() - start > limitedTime; }

	int GetStartTime() { return start; }
	int GetLimitedTime() { return limitedTime; }
	void SetLimitedTime(int temp) { limitedTime = temp; }
};
