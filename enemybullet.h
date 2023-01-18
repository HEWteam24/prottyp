#pragma once
#include "main.h"
#include "renderer.h"

//==================================
//マクロ定義
//==================================
#define	ENEMYBULLET_NOMAL_MAX		20		//弾の最大数
#define	ENEMYBULLET_LONG_MAX		20		//弾の最大数
#define	ENEMYBULLET_WIDE_MAX		20		//弾の最大数
#define ENEMYBULLET_HP_MAX			20
#define ENEMYBULLET_TRANSLUCENT_MAX 20
#define	ENEMYBULLET_SPEED1	10.0/2	//弾のスピードBPM90
#define	ENEMYBULLET_SPEED2	13.0f/2	//弾のスピードBPM120
#define	ENEMYBULLET_SPEED3	16.3/2	//弾のスピードBPM150
#define	ENEMYBULLET_SIZE_W	140		//弾の横サイズ
#define	ENEMYBULLET_SIZE_H	60		//弾の縦サイズ
#define ENEMYBULLET_ALFA_CHANGE	0.006f	//アルファ値変更

//以下マップチップ用
#define	MAP_SIZE_X	5	//横レーン数
#define	MAP_SIZE_Y	145	//縦ノーツ総数(現状１秒に１個)

//==================================
//グローバル変数
//==================================

//構造体
struct ENEMYBULLET
{
	bool use;
	float w, h;
	D3DXVECTOR2	pos;
	float	rot;
	D3DXVECTOR2	mov;	//移動ベクトル
	int	texNo;
	int hp;
};

//==================================
//プロトタイプ宣言
//==================================
HRESULT InitEnemyBullet(int Stagenum);
void	UninitEnemyBullet();
void	UpdateEnemyBullet();
void	DrawEnemyBullet();

void	SETBULLET();
