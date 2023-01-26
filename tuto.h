#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTuto(int StageNum);
void UninitTuto(void);
void UpdateTuto(void);
void DrawTuto(void);
void SetCircle(D3DXVECTOR2 szst, D3DXVECTOR2 pos, D3DXVECTOR2 TextUV);
void SetArrow (D3DXVECTOR2 pos, float rot);

struct T_CIRCLE
{
	D3DXVECTOR2		size;
	D3DXVECTOR2		pos;
	D3DXVECTOR2		Tuv;
	D3DXCOLOR		col;
	
	D3DXVECTOR2		ArPos;
	D3DXVECTOR2		ArSpd;
	float			ArRot;

	float			ButtonSize;
	float			ButtonAdd;
	
	int TextFrame;
	int Phase;

	bool			use;
};

T_CIRCLE* GetTuto();
