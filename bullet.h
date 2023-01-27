#pragma once
#include "main.h"
#include "renderer.h"

//==================================
//マクロ定義
//==================================
#define	BULLET_MAX		12		//弾の最大数
#define	BULLET_SPEED	20.0f	//弾のスピード
#define	BULLET_SIZE_W	50		//弾の横サイズ
#define	BULLET_SIZE_H	50		//弾の縦サイズ

//構造体
struct BULLET
{
	bool use;
	float w, h;
	D3DXVECTOR2	pos;
	D3DXVECTOR2	oldpos;	//当たり判定用
	float	rot;
	D3DXVECTOR2	mov;	//移動ベクトル
	int	texNo;
};

//==================================
//プロトタイプ宣言
//==================================
HRESULT InitBullet();
void	UninitBullet();
void	UpdateBullet();
void	DrawBullet();

BULLET*	GetBullet();
void	SetBullet(D3DXVECTOR2 pos);	//弾発生

int Damage();
