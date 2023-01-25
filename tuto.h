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
	
	int TextFrame;
	int Phase;

	bool			use;
};
