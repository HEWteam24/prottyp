#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

typedef struct
{
	float	u;
	float	v;
	float	rad;
	int		rank;
	D3DXCOLOR	col;
}COIN;
