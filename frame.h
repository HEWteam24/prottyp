#pragma once
#ifndef FRAME_H_

#include "main.h"
#include <windows.h>

struct CTimer {
	BOOL            bPerf;          // ���𑜓x�^�C�}�[���T�|�[�g����Ă��邩
	LARGE_INTEGER   mFreq;          // �V�X�e�����g��
	LARGE_INTEGER   mStart;         // �J�n����
	int             iFps;           // ���荞�݃^�C�~���O
	int             iCount;         // ���荞�݃J�E���g��
};
#endif // !FRAME_H_

void	InitFrame();
BOOL	Start(int fps = 60);       // �w���FPS�Ŋ��荞�݃X�^�[�g
int		Run(void);                // ���荞�݂������1�ȏ��Ԃ��i���荞�݉񐔁j