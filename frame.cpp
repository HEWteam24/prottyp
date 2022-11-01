#include "frame.h"

CTimer	Timer;

void InitFrame()
{
	if (QueryPerformanceFrequency(&Timer.mFreq)) {
		// ���𑜓x�J�E���^�[�ɑΉ�
		Timer.bPerf = TRUE;
	}
	else {
		// ���𑜓x�J�E���^�[�ɔ�Ή�
		Timer.mFreq.QuadPart = 1000LL;       // timeGetTime()�ő�p
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
