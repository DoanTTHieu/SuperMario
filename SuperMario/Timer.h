#pragma once
#pragma once
#include <Windows.h>

class CTimer
{
	ULONGLONG start;
	ULONGLONG limitedTime;

public:
	CTimer(int limitedTime) { this->limitedTime = limitedTime; start = 0; }

	void Start() { start = GetTickCount64(); }
	void Reset() { start = GetTickCount64(); }
	void Stop() { start = 0; }
	bool IsTimeUp() { return GetTickCount64() - start > limitedTime; }

	ULONGLONG GetStartTime() { return start; }
	ULONGLONG GetLimitedTime() { return limitedTime; }
	void SetLimitedTime(int temp) { limitedTime = temp; }
};
