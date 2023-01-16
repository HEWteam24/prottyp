
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SKILL_MAX (3)

enum SKILL_E
{
	SKILL_0,
	SKILL_1,
	SKILL_2
};

enum SKILL_PANEL_LANE
{
	S_PLANE_MIN,
	S_PLANE_0,
	S_PLANE_1,
	S_PLANE_2,
	S_PLANE_3,
	S_PLANE_4
};

enum S_DIRECTION_PANEL	//移動の向き
{
	SD_LEFT = 0,
	SD_RIGHT = 1,
};

struct SKILL_PANEL
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXCOLOR	col;
	int texno;
	bool moving;
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSkillSelect(void);
void UninitSkillSelect(void);
void UpdateSkillSelect(void);
void DrawSkillSelect(void);
#pragma once
