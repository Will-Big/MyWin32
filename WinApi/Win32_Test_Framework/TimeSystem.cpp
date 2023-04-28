#include "WinApp.h"
#include "TimeSystem.h"
#include <cmath>

namespace time
{
	LARGE_INTEGER previousTime = { 0 };
	LARGE_INTEGER currentTime = { 0 };
	LARGE_INTEGER frequency = { 0 };

	float deltaTime = 0;

	void InitTime()
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&previousTime);
	}

	void UpdateTime()
	{
		previousTime = currentTime;
		QueryPerformanceCounter(&currentTime);

		deltaTime = (float)(currentTime.QuadPart - previousTime.QuadPart) / (float)frequency.QuadPart * 1000.0f; //ms
	}

	const float GetFrameRate()
	{
		if (deltaTime == 0) return 0;

		return ceil(((1000.0f / deltaTime) * 1000) / 1000);
	}

	const float GetDeltaTime() { return deltaTime; }

}