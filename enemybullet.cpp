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
#include "special.h"
#include "MapChip.h"
#include "stage_select.h"

#include <time.h>
#include <stdlib.h>


//================================
//グローバル変数
//================================
ENEMYBULLET g_EnemyBulletNomal[ENEMYBULLETNOMAL_MAX];
ENEMYBULLET g_EnemyBulletLong[ENEMYBULLETLONG_MAX];
PLAYER* pPlayer;

//テクスチャのロード
int g_EnemyBulletNomalTex;
static	ID3D11ShaderResourceView* g_TextureEnemyBulletNomal;
static	char *g_TextureEnemyBulletNomalName = (char*)"data\\TEXTURE\\rank_coins_1200x200_B.png";//テクスチャ名

int g_EnemyBulletLongTex;
static	ID3D11ShaderResourceView* g_TextureEnemyBulletLong;
static	char *g_TextureEnemyBulletLongName = (char*)"data\\TEXTURE\\EnemyBullet01.png";//テクスチャ名

int nowY = 0;	//マップのその時の縦列数

static int g_SE_Damage;		//ダメージサウンド

//STAGE StageLv = STAGE01;

//================================
//マップチップ
//================================
/*
int StageBullet01[MAP_SIZE_Y][MAP_SIZE_X] =
{
	//1個め

		1, 0, 0, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 0,
		1, 0, 0, 0, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 0, 0, 1,
		0, 0, 1, 1, 0,
		1, 1, 0, 0, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 0, 1, 1,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
		1, 0, 0, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 0, 1, 1, 0,
		1, 1, 0, 0, 0,
		0, 0, 0, 1, 1,
		0, 0, 1, 1, 0,
		0, 1, 1, 0, 0,
		1, 1, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
		0, 0, 0, 1, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 1, 1,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		0, 1, 1, 0, 0,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 0, 1, 0, 1,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		0, 1, 1, 0, 0,
		1, 0, 0, 0, 1,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		0, 0, 1, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 0, 1,
		1, 0, 1, 0, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 1, 0, 1, 1,
		0, 1, 1, 0, 0,
		0, 0, 1, 1, 0,

};
int StageBullet02[MAP_SIZE_Y][MAP_SIZE_X] =
{
2, 2, 0, 1, 1,
1, 0, 2, 1, 0,
2, 0, 0, 0, 1,
0, 2, 2, 2, 1,
0, 0, 0, 1, 0,
2, 0, 2, 2, 0,
0, 1, 1, 1, 0,
0, 1, 2, 0, 2,
0, 0, 0, 1, 0,
1, 2, 2, 1, 0,
0, 0, 2, 2, 1,
2, 1, 0, 1, 0,
0, 1, 0, 1, 1,
2, 1, 0, 2, 1,
2, 1, 0, 0, 0,
0, 2, 0, 0, 2,
0, 2, 1, 1, 2,
0, 2, 0, 2, 0,
0, 0, 1, 1, 1,
1, 0, 0, 2, 1,
1, 0, 2, 0, 2,
2, 0, 2, 0, 1,
1, 2, 2, 0, 0,
1, 0, 0, 0, 0,
1, 2, 0, 2, 2,
0, 2, 2, 2, 0,
0, 1, 0, 1, 0,
1, 0, 0, 0, 2,
0, 2, 0, 1, 0,
1, 0, 1, 2, 1,
0, 2, 1, 2, 2,
2, 0, 1, 2, 0,
0, 2, 2, 1, 0,
1, 0, 0, 0, 2,
0, 1, 0, 2, 2,
0, 2, 2, 0, 2,
0, 0, 0, 2, 0,
2, 2, 1, 0, 0,
0, 1, 1, 0, 2,
0, 0, 2, 2, 0,
2, 0, 2, 2, 0,
0, 2, 1, 0, 0,
1, 2, 1, 1, 0,
1, 0, 1, 1, 2,
2, 0, 2, 1, 0,
0, 0, 2, 0, 1,
1, 0, 0, 1, 1,
0, 0, 0, 0, 1,
0, 2, 0, 2, 2,
0, 1, 0, 0, 0,
2, 1, 0, 1, 0,
0, 0, 0, 0, 0,
2, 0, 2, 0, 0,
0, 0, 0, 0, 2,
0, 0, 1, 2, 2,
2, 0, 0, 0, 1,
2, 0, 1, 0, 1,
2, 0, 2, 0, 1,
0, 2, 1, 1, 0,
0, 0, 1, 2, 1,
1, 0, 2, 2, 0,
1, 0, 0, 2, 2,
2, 2, 0, 1, 2,
1, 0, 0, 1, 2,
2, 0, 0, 1, 2,
2, 1, 2, 0, 0,
0, 2, 0, 0, 0,
2, 0, 1, 0, 1,
2, 0, 1, 0, 0,
0, 0, 0, 2, 0,
0, 0, 0, 1, 2,
0, 2, 1, 1, 0,
0, 0, 0, 1, 2,
2, 0, 0, 1, 2,
1, 2, 0, 2, 1,
2, 0, 2, 0, 2,
2, 0, 0, 1, 0,
0, 0, 0, 0, 1,
2, 2, 2, 0, 1,
0, 1, 2, 2, 0,
0, 0, 0, 2, 0,
0, 0, 0, 0, 2,
0, 0, 2, 2, 0,
2, 1, 0, 1, 0,
0, 1, 0, 0, 1,
0, 0, 0, 0, 0,
2, 1, 2, 0, 0,
0, 0, 2, 1, 0,
0, 1, 1, 2, 0,
2, 1, 0, 2, 0,
1, 0, 0, 1, 0,
0, 0, 1, 1, 0,
2, 0, 0, 0, 2,
1, 1, 1, 0, 1,
0, 2, 0, 2, 1,
1, 0, 0, 2, 2,
2, 0, 2, 2, 2,
2, 1, 0, 0, 0,
2, 0, 1, 0, 2,
1, 0, 2, 1, 1,
0, 0, 2, 2, 0,
2, 1, 0, 0, 0,
2, 2, 0, 2, 2,
0, 2, 0, 2, 1,
1, 2, 1, 0, 0,
1, 1, 0, 2, 0,
1, 0, 1, 2, 2,
1, 0, 0, 2, 2,
0, 1, 2, 2, 1,
1, 1, 0, 2, 0,
0, 0, 0, 1, 0,
2, 1, 0, 1, 0,
0, 1, 2, 0, 2,
0, 1, 2, 0, 2,
1, 0, 2, 0, 0, 
};
*/





//================================
//初期化
//================================

HRESULT InitEnemyBullet()
{
	g_EnemyBulletNomalTex = LoadTexture(g_TextureEnemyBulletNomalName);
	g_EnemyBulletLongTex = LoadTexture(g_TextureEnemyBulletLongName);

	//構造体の初期化
	for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
	{
		//Nomal
		g_EnemyBulletNomal[i].use = false;
		g_EnemyBulletNomal[i].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletNomal[i].h = ENEMYBULLET_SIZE_H;
		g_EnemyBulletNomal[i].pos = D3DXVECTOR2(0, -10);
		g_EnemyBulletNomal[i].mov = D3DXVECTOR2(0, ENEMYBULLET_SPEED);
	}
	for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
	{
		//Long
		g_EnemyBulletLong[k].use = false;
		g_EnemyBulletLong[k].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletLong[k].h = ENEMYBULLET_SIZE_H * 3;
		g_EnemyBulletLong[k].pos = D3DXVECTOR2(0, -40);
		g_EnemyBulletLong[k].mov = D3DXVECTOR2(0, ENEMYBULLET_SPEED);

	}
	char	file_SE_Damage[] = "data\\SE\\SE_deadEnm.wav";
	g_SE_Damage = LoadSound(file_SE_Damage);

	pPlayer = GetPlayer();
	nowY = 0;
	return S_OK;
}

//終了処理
void UninitEnemyBullet()
{
	if (g_TextureEnemyBulletNomal)
	{
		g_TextureEnemyBulletNomal->Release();
		g_TextureEnemyBulletNomal = NULL;
	}
	if (g_TextureEnemyBulletLong)
	{
		g_TextureEnemyBulletLong->Release();
		g_TextureEnemyBulletLong = NULL;
	}
}

//更新処理
void UpdateEnemyBullet()
{
	SPECIAL* sp = GetSpecial();
	
	int eFreame = GetFreame();

	if (eFreame % 60*1.5 == 0.0f)
	{
		SETBULLET();
		nowY++;
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

			if (CollisionBB(g_EnemyBulletNomal[i].pos, pPlayer->pos - D3DXVECTOR2(0.0f,pPlayer->size.y / 2.5), D3DXVECTOR2(g_EnemyBulletNomal[i].w, g_EnemyBulletNomal[i].h), D3DXVECTOR2(pPlayer->size.x,1.0f)))
			{
				g_EnemyBulletNomal[i].use = false;
				//スペシャルの被ダメ減少
				if (sp->get_damage_down == true)
				{
					pPlayer->hp -= 5.0f;
				}
				else
				{
					pPlayer->hp -= 25.0f*1;
				}

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

			if (CollisionBB(g_EnemyBulletLong[k].pos, pPlayer->pos, D3DXVECTOR2(g_EnemyBulletLong[k].w, g_EnemyBulletLong[k].h), pPlayer->size/2))
			{
				g_EnemyBulletLong[k].use = false;
				if (sp->get_damage_down == true)
				{
					pPlayer->hp -= 3.0f;
				}
				else
				{
					pPlayer->hp -= 15.0f;
				}
				g_EnemyBulletLong[k].pos.y = -10.0f;
				PlaySound(g_SE_Damage, 0);
			}

		}
	}
}

void DrawEnemyBullet()
{

	for (int x = 0; x < ENEMYBULLETNOMAL_MAX; x++)
	{
		if (g_EnemyBulletNomal[x].use)
		{
			DrawSpriteColor(g_EnemyBulletNomalTex, g_EnemyBulletNomal[x].pos.x, g_EnemyBulletNomal[x].pos.y, ENEMYBULLET_SIZE_W, ENEMYBULLET_SIZE_H,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}

	for (int y = 0; y < ENEMYBULLETLONG_MAX; y++)
	{
		if (g_EnemyBulletLong[y].use)
		{
			DrawSpriteColor(g_EnemyBulletLongTex, g_EnemyBulletLong[y].pos.x, g_EnemyBulletLong[y].pos.y, ENEMYBULLET_SIZE_W, ENEMYBULLET_SIZE_H * 3,
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

void SETBULLET()
{
	int atk = 0;	//敵の攻撃用
	bool IsAtk = true;

	int NowStage = GetGemeStageNum();
	if (nowY < MAP_SIZE_Y)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			switch (StageBullet[NowStage][nowY][j])
			{
			case 0:
				IsAtk = false;
				break;
			case 1:
				switch (j)
				{
				case 0:
					atk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
					break;
				case 1:
					atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
					break;
				case 2:
					atk = SCREEN_WIDTH / 2;
					break;
				case 3:
					atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
					break;
				case 4:
					atk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
					break;
				default:
					break;
				}
				if (IsAtk)
				{
					for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
					{
						if (g_EnemyBulletNomal[i].use == false)
						{
							g_EnemyBulletNomal[i].pos.x = atk;
							g_EnemyBulletNomal[i].use = true;
							break;
						}
					}
				}
				break;
			case 2:
				switch (j)
				{
				case 0:
					atk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
					break;
				case 1:
					atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
					break;
				case 2:
					atk = SCREEN_WIDTH / 2;
					break;
				case 3:
					atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
					break;
				case 4:
					atk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
					break;
				default:
					break;
				}
				if (IsAtk)
				{
					for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
					{
						if (g_EnemyBulletLong[k].use == false)
						{
							g_EnemyBulletLong[k].pos.x = atk;
							g_EnemyBulletLong[k].use = true;
							break;
						}
					}
				}
				break;
			case 3:
				IsAtk = false;
				break;
			case 4:
				IsAtk = false;
				break;
			default:
				IsAtk = false;
				break;
			}
			IsAtk = true;
			atk = 0;
		}
	}
}