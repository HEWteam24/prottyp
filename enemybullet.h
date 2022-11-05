#pragma once

#pragma once
#include "main.h"
#include "renderer.h"

//==================================
//マクロ定義
//==================================
#define	ENEMYBULLETNOMAL_MAX		20		//弾の最大数
#define	ENEMYBULLETLONG_MAX		5		//弾の最大数
#define	ENEMYBULLET_SPEED	8.0f	//弾のスピード
#define	ENEMYBULLET_SIZE_W	140		//弾の横サイズ
#define	ENEMYBULLET_SIZE_H	60		//弾の縦サイズ

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
};

//==================================
//プロトタイプ宣言
//==================================
HRESULT InitEnemyBullet();
void	UninitEnemyBullet();
void	UpdateEnemyBullet();
void	DrawEnemyBullet();

ENEMYBULLET* GetEnemyBulletNomal();
ENEMYBULLET* GetEnemyBulletLong();
void	SetEnemyBullet();	//弾発生
