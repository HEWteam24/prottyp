#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
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
