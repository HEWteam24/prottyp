#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTuto(int StageNum);
void UninitTuto(void);
void UpdateTuto(void);
void DrawTuto(void);

struct CIRCLE
{
	D3DXVECTOR2		size;
	D3DXVECTOR2		pos;
	D3DXCOLOR		col;
	bool			use;
};
