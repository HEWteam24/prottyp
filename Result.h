#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitResult(int stagenum);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

typedef struct
{
	float	u;
	float	v;
	float	rad;
	int		rank;
	float	alpha;
	
	bool roted;
	D3DXVECTOR2	size;

	D3DXCOLOR	col;
	D3DXCOLOR	TextCol;
}COIN;
