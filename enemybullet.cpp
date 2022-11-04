//====================================================
//エネミーバレット
//作成：町田裕哉
//		2022/10/26
//====================================================
#include "enemybullet.h"
#include "texture.h"
#include "bullet.h"
#include "player.h"
#include "sprite.h"
#include "sound.h"
#include "collision.h"
#include "rhythm.h"
#include <time.h>
#include <stdlib.h>

//================================
//グローバル変数
//================================
ENEMYBULLET g_EnemyBulletNomal[ENEMYBULLETNOMAL_MAX];
ENEMYBULLET g_EnemyBulletLong[ENEMYBULLETLONG_MAX];
PLAYER* pPlayer;
NOTESLANE* pRhythm;

static int g_SE_Damage;		//ダメージサウンド
//================================
//初期化
//================================

HRESULT InitEnemyBullet()
{
	//テクスチャのロード
	int texno = LoadTexture((char*)"data\\TEXTURE\\Back.JPG");
	//構造体の初期化
	for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
	{
		//Nomal
		g_EnemyBulletNomal[i].use = false;
		g_EnemyBulletNomal[i].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletNomal[i].h = ENEMYBULLET_SIZE_H;
		g_EnemyBulletNomal[i].pos = D3DXVECTOR2(0, -10);
		g_EnemyBulletNomal[i].texNo = texno;
		g_EnemyBulletNomal[i].mov = D3DXVECTOR2(0, ENEMYBULLET_SPEED);
	}
	for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
	{
		//Long
		g_EnemyBulletLong[k].use = false;
		g_EnemyBulletLong[k].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletLong[k].h = ENEMYBULLET_SIZE_H * 3;
		g_EnemyBulletLong[k].pos = D3DXVECTOR2(0, -40);
		g_EnemyBulletLong[k].texNo = texno;
		g_EnemyBulletLong[k].mov = D3DXVECTOR2(0, ENEMYBULLET_SPEED);

	}
	char	file_SE_Damage[] = "data\\SE\\SE_deadEnm.wav";
	g_SE_Damage = LoadSound(file_SE_Damage);

	pPlayer = GetPlayer();
	pRhythm = GetNotesLane();

	return S_OK;
}

//終了処理
void UninitEnemyBullet()
{
}

//更新処理
void UpdateEnemyBullet()
{
	

	if (pRhythm->frame % 60*1.5 == 0.0f)
	{
		SetEnemyBullet();
	}

	for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
	{
		if (g_EnemyBulletNomal[i].use == true)
		{
			g_EnemyBulletNomal[i].pos += g_EnemyBulletNomal[i].mov;	//移動

			if (g_EnemyBulletNomal[i].pos.y > SCREEN_HEIGHT - g_EnemyBulletNomal[i].h / 2)
			{
				g_EnemyBulletNomal[i].use = false;
				g_EnemyBulletNomal[i].pos.y = -10.0f;
			}

			if (CollisionBB(g_EnemyBulletNomal[i].pos, pPlayer->pos, D3DXVECTOR2(g_EnemyBulletNomal[i].w, g_EnemyBulletNomal[i].h), pPlayer->size))
			{
				g_EnemyBulletNomal[i].use = false;
				pPlayer->hp -= 10.0f;
				g_EnemyBulletNomal[i].pos.y = -10.0f;
				PlaySound(g_SE_Damage, 0);
			}
		}
	}

	for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
	{
		if (g_EnemyBulletLong[k].use == true)
		{
			g_EnemyBulletLong[k].pos += g_EnemyBulletLong[k].mov;	//移動

			if (g_EnemyBulletLong[k].pos.y > SCREEN_HEIGHT - g_EnemyBulletLong[k].h / 2)
			{
				g_EnemyBulletLong[k].use = false;
				g_EnemyBulletLong[k].pos.y = -10.0f;
			}

			if (CollisionBB(g_EnemyBulletLong[k].pos, pPlayer->pos, D3DXVECTOR2(g_EnemyBulletLong[k].w, g_EnemyBulletLong[k].h), pPlayer->size))
			{
				g_EnemyBulletLong[k].use = false;
				pPlayer->hp -= 10.0f;
				g_EnemyBulletLong[k].pos.y = -10.0f;
				PlaySound(g_SE_Damage, 0);
			}

		}
	}
}

void DrawEnemyBullet()
{

	for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
	{
		if (g_EnemyBulletNomal[i].use)
		{
			DrawSpriteColor(g_EnemyBulletNomal[i].texNo, g_EnemyBulletNomal[i].pos.x, g_EnemyBulletNomal[i].pos.y, ENEMYBULLET_SIZE_W, ENEMYBULLET_SIZE_H,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}

	for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
	{
		if (g_EnemyBulletLong[k].use)
		{
			DrawSpriteColor(g_EnemyBulletLong[k].texNo, g_EnemyBulletLong[k].pos.x, g_EnemyBulletLong[k].pos.y, ENEMYBULLET_SIZE_W, ENEMYBULLET_SIZE_H * 3,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}
}

ENEMYBULLET* GetEnemyBulletNomal()
{
	return &g_EnemyBulletNomal[0];
}

ENEMYBULLET* GetEnemyBulletLong()
{
	return &g_EnemyBulletLong[0];
}

void SetEnemyBullet()
{
	srand((unsigned int)time(NULL));
	int num,numm;		//乱数用
	int atk = 0,atkk = 0;	//敵の攻撃用
	num = rand() % 9;
	numm = rand() % 2;

	switch (num)
	{
	case 0:
		if (numm == 0)
			atk = SCREEN_WIDTH / 2;
		else
			atkk = SCREEN_WIDTH / 2;
		break;
	case 1:
		if (numm == 0)
			atk = SCREEN_WIDTH / 2;
		else
			atkk = SCREEN_WIDTH / 2;
		break;
	case 2:
		if (numm == 0)
			atk = SCREEN_WIDTH / 2;
		else
			atkk = SCREEN_WIDTH / 2;
		break;
	case 3:
		if (numm == 0)
			atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
		else
			atkk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
		break;
	case 4:
		if (numm == 0)
			atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
		else
			atkk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
		break;
	case 5:
		if (numm == 0)
			atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
		else
			atkk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
		break;
	case 6:
		if (numm == 0)
			atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
		else
			atkk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
		break;
	case 7:
		if (numm == 0)
			atk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
		else
			atkk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
		break;
	case 8:
		if (numm == 0)
			atk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
		else
			atkk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
		break;
	default:
		break;

	}


	if (atkk == 0)
	{
		for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
		{
			if (g_EnemyBulletNomal[i].use == false)
			{
				g_EnemyBulletNomal[i].pos.x = atk;
				g_EnemyBulletNomal[i].use = true;
				return;
			}
		}
	}
	else
	{
		for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
		{
			if (g_EnemyBulletLong[k].use == false)
			{
				g_EnemyBulletLong[k].pos.x = atkk;
				g_EnemyBulletLong[k].use = true;
				return;
			}

		}
	}
}