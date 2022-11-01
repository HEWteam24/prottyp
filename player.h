/*==============================================================================

   プレイヤー管理[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct PLAYER
{
	D3DXVECTOR2		pos;	//位置
	D3DXVECTOR2		oldpos;	//位置
	D3DXVECTOR2     uv;		//UV値
	D3DXVECTOR2		size;	//サイズ
	D3DXVECTOR2		speed;	//速度

	int		direction;		//向き
	int		NowLane;		//現在のレーン
	float	hp;				//体力
	bool	moving;			//移動中フラグ

	int		animeIndex;		//アニメーション枚数
	int		animeWait;		//アニメーション
	bool	flag;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

void	InitPlayer(void);
void	UninitPlayer(void);
void	UpdatePlayer(void);
void	DrawPlayer(void);
void	DrawHp(void);
void	PlayerCheck(void);
PLAYER* GetPlayer(void);

