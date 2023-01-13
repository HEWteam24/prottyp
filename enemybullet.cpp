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
ENEMYBULLET g_EnemyBulletWide[ENEMYBULLETWIDE_MAX];
PLAYER* pPlayer;
BULLET* pBullet;
//テクスチャのロード
int g_EnemyBulletNomalTex;
static	ID3D11ShaderResourceView* g_TextureEnemyBulletNomal;
static	char *g_TextureEnemyBulletNomalName = (char*)"data\\TEXTURE\\rank_coins_1200x200_B.png";//テクスチャ名

int g_EnemyBulletLongTex;
static	ID3D11ShaderResourceView* g_TextureEnemyBulletLong;
static	char *g_TextureEnemyBulletLongName = (char*)"data\\TEXTURE\\EnemyBullet01.png";//テクスチャ名

int g_EnemyBulletWideTex;
static	ID3D11ShaderResourceView* g_TextureEnemyBulleWide;
static	char *g_TextureEnemyBulletWideName = (char*)"data\\TEXTURE\\enemy_tooth.png";//テクスチャ名

int nowY = 0;	//マップのその時の縦列数

static int g_SE_Damage;		//ダメージサウンド
static float BulletSp;
//================================
//初期化
//================================

HRESULT InitEnemyBullet(int Stagenum)
{

	switch (Stagenum)
	{
	case 0:
		BulletSp = ENEMYBULLET_SPEED2;
	case 1:
		BulletSp = ENEMYBULLET_SPEED2;
	case 2:
		BulletSp = ENEMYBULLET_SPEED2;
	case 3:
		BulletSp = ENEMYBULLET_SPEED3;
	case 4:
		BulletSp = ENEMYBULLET_SPEED3;
	case 8:
		BulletSp = ENEMYBULLET_SPEED3;
	case 9:
		BulletSp = ENEMYBULLET_SPEED1;
	default:
		break;
	}

	pBullet = GetBullet();

	g_EnemyBulletNomalTex = LoadTexture(g_TextureEnemyBulletNomalName);
	g_EnemyBulletLongTex = LoadTexture(g_TextureEnemyBulletLongName);
	g_EnemyBulletWideTex = LoadTexture(g_TextureEnemyBulletWideName);

	//構造体の初期化
	for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
	{
		//Nomal
		g_EnemyBulletNomal[i].use = false;
		g_EnemyBulletNomal[i].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletNomal[i].h = ENEMYBULLET_SIZE_H;
		g_EnemyBulletNomal[i].pos = D3DXVECTOR2(0, -10);
		g_EnemyBulletNomal[i].mov = D3DXVECTOR2(0, BulletSp);
		g_EnemyBulletNomal[i].hp = 1;
	}
	for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
	{
		//Long
		g_EnemyBulletLong[k].use = false;
		g_EnemyBulletLong[k].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletLong[k].h = ENEMYBULLET_SIZE_H * 3;
		g_EnemyBulletLong[k].pos = D3DXVECTOR2(0, -40);
		g_EnemyBulletLong[k].mov = D3DXVECTOR2(0, BulletSp);
		g_EnemyBulletLong[k].hp = 1;

	}
	for (int j = 0; j < ENEMYBULLETWIDE_MAX; j++)
	{
		//Wide
		g_EnemyBulletWide[j].use = false;
		g_EnemyBulletWide[j].w = ENEMYBULLET_SIZE_W * 2;
		g_EnemyBulletWide[j].h = ENEMYBULLET_SIZE_H * 2;
		g_EnemyBulletWide[j].pos = D3DXVECTOR2(0, -20);
		g_EnemyBulletWide[j].mov = D3DXVECTOR2(0, BulletSp / 2.0f);
		g_EnemyBulletWide[j].hp = 3;
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
		//nowY++;
	}

	for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
	{
		if (g_EnemyBulletNomal[i].use == true)
		{
			g_EnemyBulletNomal[i].pos += g_EnemyBulletNomal[i].mov;	//移動

			if (g_EnemyBulletNomal[i].pos.y > SCREEN_HEIGHT - g_EnemyBulletNomal[i].h / 2)
			{
				g_EnemyBulletNomal[i].use = false;
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

				g_EnemyBulletNomal[i].pos -= g_EnemyBulletNomal[i].mov;
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
				g_EnemyBulletLong[k].pos -= g_EnemyBulletLong[k].mov;
				PlaySound(g_SE_Damage, 0);
			}

		}
	}
	
	for (int j = 0; j < ENEMYBULLETWIDE_MAX; j++)
	{
		if (g_EnemyBulletWide[j].use == true)
		{
			g_EnemyBulletWide[j].pos += g_EnemyBulletWide[j].mov;	//移動

			if (g_EnemyBulletWide[j].pos.y > SCREEN_HEIGHT - g_EnemyBulletWide[j].h / 2)
			{
				g_EnemyBulletWide[j].use = false;
			}
			
			for (int h = 0; h < BULLET_MAX; h++)
			{
				if ((pBullet + h)->use)
				{
 					if (CollisionBB(g_EnemyBulletWide[j].pos, (pBullet + h)->pos, D3DXVECTOR2(g_EnemyBulletWide[j].w, g_EnemyBulletWide[j].h), D3DXVECTOR2((pBullet + h)->w / 2, (pBullet + h)->h / 2)))
					{
						g_EnemyBulletWide[j].hp--;
						(pBullet + h)->use = false;
		
						if (g_EnemyBulletWide[j].hp <= 0)
						{
							g_EnemyBulletWide[j].use = false;
						}
					}
				}
			}

			if (CollisionBB(g_EnemyBulletWide[j].pos, pPlayer->pos, D3DXVECTOR2(g_EnemyBulletWide[j].w, g_EnemyBulletWide[j].h), pPlayer->size/2))
			{
				g_EnemyBulletWide[j].use = false;
				if (sp->get_damage_down == true)
				{
					pPlayer->hp -= 5.0f;
				}
				else
				{
					pPlayer->hp -= 25.0f;
				}
				g_EnemyBulletWide[j].pos -= g_EnemyBulletWide[j].mov;
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
			DrawSpriteColor(g_EnemyBulletNomalTex, g_EnemyBulletNomal[x].pos.x, g_EnemyBulletNomal[x].pos.y, g_EnemyBulletNomal[x].w, g_EnemyBulletNomal[x].h,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}

	for (int y = 0; y < ENEMYBULLETLONG_MAX; y++)
	{
		if (g_EnemyBulletLong[y].use)
		{
			DrawSpriteColor(g_EnemyBulletLongTex, g_EnemyBulletLong[y].pos.x, g_EnemyBulletLong[y].pos.y, g_EnemyBulletLong[y].w, g_EnemyBulletLong[y].h,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}

	for (int z = 0; z < ENEMYBULLETWIDE_MAX; z++)
	{
		if (g_EnemyBulletWide[z].use)
		{
			DrawSpriteColor(g_EnemyBulletWideTex, g_EnemyBulletWide[z].pos.x, g_EnemyBulletWide[z].pos.y, g_EnemyBulletWide[z].w, g_EnemyBulletWide[z].h,
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
					atk = BULLETLANE_1;
					break;
				case 1:
					atk = BULLETLANE_2;
					break;
				case 2:
					atk = BULLETLANE_3;
					break;
				case 3:
					atk = BULLETLANE_4;
					break;
				case 4:
					atk = BULLETLANE_5;
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
							g_EnemyBulletNomal[i].pos.y = -10.0f;
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
					atk = BULLETLANE_1;
					break;
				case 1:
					atk = BULLETLANE_2;
					break;
				case 2:
					atk = BULLETLANE_3;
					break;
				case 3:
					atk = BULLETLANE_4;
					break;
				case 4:
					atk = BULLETLANE_5;
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
							g_EnemyBulletLong[k].pos.y = -40.0f;
							g_EnemyBulletLong[k].use = true;
							break;
						}
					}
				}
				break;
			case 3:
				switch (j)
				{
				case 0:
					atk = BULLETLANE_1;
					break;
				case 1:
					atk = BULLETLANE_2;
					break;
				case 2:
					atk = BULLETLANE_3;
					break;
				case 3:
					atk = BULLETLANE_4;
					break;
				case 4:
					atk = BULLETLANE_5;
					break;
				default:
					break;
				}
				if (IsAtk)
				{
					for (int k = 0; k < ENEMYBULLETWIDE_MAX; k++)
					{
						if (g_EnemyBulletWide[k].use == false)
						{
							g_EnemyBulletWide[k].pos.x = atk;
							g_EnemyBulletWide[k].pos.y = -20.0f;
							g_EnemyBulletWide[k].hp = 3;
							g_EnemyBulletWide[k].use = true;
							break;
						}
					}
				}
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
		nowY++;
	}
}