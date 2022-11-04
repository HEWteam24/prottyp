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
ENEMYBULLET g_EnemyBullet[ENEMYBULLET_MAX];
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
	for (int i = 0; i < ENEMYBULLET_MAX; i++)
	{
		g_EnemyBullet[i].use = false;
		g_EnemyBullet[i].w = ENEMYBULLET_SIZE_W;
		g_EnemyBullet[i].h = ENEMYBULLET_SIZE_H;
		g_EnemyBullet[i].pos = D3DXVECTOR2(0, -10);
		g_EnemyBullet[i].texNo = texno;
		g_EnemyBullet[i].mov = D3DXVECTOR2(0, ENEMYBULLET_SPEED);

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

	for (int i = 0; i < ENEMYBULLET_MAX; i++)
	{
		if (g_EnemyBullet[i].use == true)
		{
			g_EnemyBullet[i].oldpos = g_EnemyBullet[i].pos;	//当たり判定用の座標コピー

			g_EnemyBullet[i].pos += g_EnemyBullet[i].mov;	//移動

			if (g_EnemyBullet[i].pos.y > SCREEN_HEIGHT - g_EnemyBullet[i].h / 2)
			{
				g_EnemyBullet[i].use = false;
				g_EnemyBullet[i].pos.y = -10.0f;
			}

			if (CollisionBB(g_EnemyBullet[i].pos, pPlayer->pos, D3DXVECTOR2(g_EnemyBullet[i].w, g_EnemyBullet[i].h), pPlayer->size/2))
			{
				g_EnemyBullet[i].use = false;
				pPlayer->hp -= 10.0f;
				g_EnemyBullet[i].pos.y = -10.0f;
				PlaySound(g_SE_Damage, 0);
			}

		}

	}
}

void DrawEnemyBullet()
{

	for (int i = 0; i < ENEMYBULLET_MAX; i++)
	{
		if (g_EnemyBullet[i].use)
		{
			DrawSpriteColor(g_EnemyBullet[i].texNo, g_EnemyBullet[i].pos.x, g_EnemyBullet[i].pos.y, ENEMYBULLET_SIZE_W, ENEMYBULLET_SIZE_H,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}
}

ENEMYBULLET * GetEnemyBullet()
{
	return &g_EnemyBullet[0];
}

void SetEnemyBullet()
{
	srand((unsigned int)time(NULL));
	int numm;		//乱数用
	int atk = 0;	//敵の攻撃用
	numm = rand() % 9;

	switch (numm)
	{
	case 0:
		atk = SCREEN_WIDTH / 2;
		break;
	case 1:
		atk = SCREEN_WIDTH / 2;
		break;
	case 2:
		atk = SCREEN_WIDTH / 2;
		break;
	case 3:
		atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
		break;
	case 4:
		atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
		break;
	case 5:
		atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
		break;
	case 6:
		atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
		break;
	case 7:
		atk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
		break;
	case 8:
		atk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
		break;
	default:
		break;

	}

	for (int i = 0; i < ENEMYBULLET_MAX; i++)
	{
		if (g_EnemyBullet[i].use == false)
		{
			g_EnemyBullet[i].pos.x = atk;
			g_EnemyBullet[i].use = true;
			return;
		}
	}

}

