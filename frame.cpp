#include "frame.h"

CTimer	Timer;

void InitFrame()
{
	if (QueryPerformanceFrequency(&Timer.mFreq)) {
		// 高解像度カウンターに対応
		Timer.bPerf = TRUE;
	}
	else {
		// 高解像度カウンターに非対応
		Timer.mFreq.QuadPart = 1000LL;       // timeGetTime()で代用
		Timer.bPerf = FALSE;
	}
	Timer.iFps = 60;
}

BOOL Start(int fps)
{
	Timer.iFps = fps;
	Timer.iCount = 0;

	if (Timer.bPerf) {
		QueryPerformanceCounter(&Timer.mStart);
	}
	else {
		Timer.mStart.QuadPart = (LONGLONG)timeGetTime();
	}
	return TRUE;
}

int Run(void)
{
	LARGE_INTEGER now;
	if (Timer.bPerf) {
		QueryPerformanceCounter(&now);
	}
	else {
		now.QuadPart = (LONGLONG)timeGetTime();
	}

	int count = (int)((now.QuadPart - Timer.mStart.QuadPart) / (Timer.mFreq.QuadPart / Timer.iFps));
	if (count != Timer.iCount) {
		int ret = count - Timer.iCount;
		Timer.iCount = count;
		return ret;
	}

	return 0;
}
