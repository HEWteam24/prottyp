#pragma once
#ifndef FRAME_H_

#include "main.h"
#include <windows.h>

struct CTimer {
	BOOL            bPerf;          // 高解像度タイマーがサポートされているか
	LARGE_INTEGER   mFreq;          // システム周波数
	LARGE_INTEGER   mStart;         // 開始時間
	int             iFps;           // 割り込みタイミング
	int             iCount;         // 割り込みカウント数
};
#endif // !FRAME_H_

void	InitFrame();
BOOL	Start(int fps = 60);       // 指定のFPSで割り込みスタート
int		Run(void);                // 割り込みがあれば1以上を返す（割り込み回数）