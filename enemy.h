//====================================================
//エネミーへッダー
//作成：勝沼力樹
//		2022/10/26
//====================================================
#pragma once
#ifndef ENEMY_H_
#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define			ENEMY_SIZE_X		(LANE_SIZE_X*3)								//エネミーサイズX
#define			ENEMY_SIZE_Y		(ENEMY_SIZE_X*1.5)							//エネミーサイズY
#define			ENEMY_SP			(1.5f)										//エネミースピード
#define			ENEMY_HP			(500)										//エネミーHP初期値
#define			ENEMY_TEX			((char*)"data\\texture\\ZARI_BOSS_1.png")			//エネミーテクスチャ
#define			ENEMY_HP_POS_X		(CENTER_X-460.0f)									//エネミー体力ゲージ座標X
#define			ENEMY_HP_POS_Y		(CENTER_Y)									//エネミー体力ゲージ座標Y
#define			ENEMY_HP_SIZE_X		(50.0f)									//エネミー体力サイズX
#define			ENEMY_HP_SIZE_Y		(900.0f)										//エネミー体力サイズY
//#define			ENEMY_HPB_SIZE_X	(510.0f)									//エネミー体力サイズX
//#define			ENEMY_HPB_SIZE_Y	(60.0f)										//エネミー体力サイズY
#define			ENEMY_HPB_SIZE_X	(60.0f)									//エネミー体力サイズX
#define			ENEMY_HPB_SIZE_Y	(910.0f)										//エネミー体力サイズY
#define			ENEMY_HP_TEX_A		((char*)"data\\texture\\HP_player_A.png")		//エネミーテクスチャ
#define			ENEMY_HP_TEX_B		((char*)"data\\texture\\HP_player_B.png")		//エネミーテクスチャ
#define			ENEMY_SPAWN_POS_X	(SCREEN_WIDTH/2)
#define			ENEMY_SPAWN_POS_Y	(0.0f)


//*****************************************************************************
// エネミー　クラス
//*****************************************************************************
struct ENEMY
{
	D3DXVECTOR2		size;
	D3DXVECTOR2		pos;
	D3DXVECTOR2		sp;
	float			rot;
	D3DXCOLOR		col;
	float			texno;
	int				hp;
	bool			use;
};

struct ENEMYHP
{
	D3DXVECTOR2		size;
	D3DXVECTOR2		pos;
	float			rot;
	D3DXCOLOR		col;
	float			texnoA;
	float			texnoB;
};

HRESULT		InitEnemy(int StageNum);
void		UninitEnemy();
void		UpdateEnemy();
void		DrawEnemy();
ENEMY*		GetEnemy();
int			GetEnemyNum();
#endif // !EMEMY_H_



