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
#include "special.h"
#include "MapChip.h"
#include "stage_select.h"

#include <time.h>
#include <stdlib.h>


//================================
//グローバル変数
//================================
ENEMYBULLET g_EnemyBulletNomal[ENEMYBULLET_NOMAL_MAX];
ENEMYBULLET g_EnemyBulletLong[ENEMYBULLET_LONG_MAX];
ENEMYBULLET g_EnemyBulletHp[ENEMYBULLET_HP_MAX];
ENEMYBULLET g_EnemyBulletTrans[ENEMYBULLET_TRANSLUCENT_MAX];
PLAYER* pPlayer;
BULLET* pBullet;
//テクスチャのロード
int g_EnemyBulletNomalTex;
static	ID3D11ShaderResourceView* g_TextureEnemyBulletNomal;
static	char *g_TextureEnemyBulletNomalName = (char*)"data\\TEXTURE\\stone.png";//テクスチャ名

int g_EnemyBulletLongTex;
static	ID3D11ShaderResourceView* g_TextureEnemyBulletLong;
static	char *g_TextureEnemyBulletLongName = (char*)"data\\TEXTURE\\water.png";//テクスチャ名

int g_EnemyBulletHpTex;
static	ID3D11ShaderResourceView* g_TextureEnemyBulletHp;
static	char *g_TextureEnemyBulletHpName = (char*)"data\\TEXTURE\\enemy_tooth02.png";//テクスチャ名

int g_EnemyBulletTransTex;
static	ID3D11ShaderResourceView* g_TextureEnemyBulletTrans;
static	char *g_TextureEnemyBulletTransName = (char*)"data\\TEXTURE\\chara_octopus.png";//テクスチャ名

//裏用
static	ID3D11ShaderResourceView* g_TextureEnemyBulletSlash;
static	char *g_TextureEnemyBulletSlashName = (char*)"data\\TEXTURE\\Slash.png";//テクスチャ名

int nowY = 0;	//マップのその時の縦列数

static int g_SE_Damage;		//ダメージサウンド

float EnemyAlfa = 1.0f;
bool AddAlfa = true;
bool HitBullet = true;

static float	 BulletSp;
int NowStage;


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
		BulletSp = ENEMYBULLET_SPEED2;
	case 4:
		BulletSp = ENEMYBULLET_SPEED2;
	case 5:
		BulletSp = ENEMYBULLET_SPEED3;
	case 6:
		BulletSp = ENEMYBULLET_SPEED3;
	case 7:
		BulletSp = ENEMYBULLET_SPEED3;
	case 8:
		BulletSp = ENEMYBULLET_SPEED3;
	case 9:
		BulletSp = ENEMYBULLET_SPEED3;
	case 10:
		BulletSp = ENEMYBULLET_SPEED3;
	default:
		break;
	}

	pBullet = GetBullet();

	g_EnemyBulletNomalTex = LoadTexture(g_TextureEnemyBulletNomalName);
	g_EnemyBulletLongTex = LoadTexture(g_TextureEnemyBulletLongName);
	if (GetUra() == false)
	{
		g_EnemyBulletHpTex = LoadTexture(g_TextureEnemyBulletHpName);
	}
	else if (GetUra() == true)
	{
		g_EnemyBulletHpTex = LoadTexture(g_TextureEnemyBulletSlashName);
	}
	g_EnemyBulletTransTex = LoadTexture(g_TextureEnemyBulletTransName);

	//構造体の初期化
	for (int i = 0; i < ENEMYBULLET_NOMAL_MAX; i++)
	{
		//Nomal
		g_EnemyBulletNomal[i].use = false;
		g_EnemyBulletNomal[i].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletNomal[i].h = ENEMYBULLET_SIZE_H;
		g_EnemyBulletNomal[i].pos = D3DXVECTOR2(0, -10);
		g_EnemyBulletNomal[i].mov = D3DXVECTOR2(0, BulletSp);
		g_EnemyBulletNomal[i].hp = 1;
	}
	for (int k = 0; k < ENEMYBULLET_LONG_MAX; k++)
	{
		//Long
		g_EnemyBulletLong[k].use = false;
		g_EnemyBulletLong[k].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletLong[k].h = ENEMYBULLET_SIZE_H * 3;
		g_EnemyBulletLong[k].pos = D3DXVECTOR2(0, -40);
		g_EnemyBulletLong[k].mov = D3DXVECTOR2(0, BulletSp);
		g_EnemyBulletLong[k].hp = 1;
	}
	for (int j = 0; j < ENEMYBULLET_TRANSLUCENT_MAX; j++)
	{
		//Trans
		g_EnemyBulletTrans[j].use = false;
		g_EnemyBulletTrans[j].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletTrans[j].h = ENEMYBULLET_SIZE_H * 2;
		g_EnemyBulletTrans[j].pos = D3DXVECTOR2(0, -10);
		g_EnemyBulletTrans[j].mov = D3DXVECTOR2(0, BulletSp);
		g_EnemyBulletTrans[j].hp = 1;
	}
	for (int j = 0; j < ENEMYBULLET_HP_MAX; j++)
	{
		//Hp
		g_EnemyBulletHp[j].use = false;
		g_EnemyBulletHp[j].w = ENEMYBULLET_SIZE_W * 2;
		g_EnemyBulletHp[j].h = ENEMYBULLET_SIZE_H * 2;
		g_EnemyBulletHp[j].pos = D3DXVECTOR2(0, -20);
		g_EnemyBulletHp[j].mov = D3DXVECTOR2(0, BulletSp / 2.0f);
		g_EnemyBulletHp[j].hp = 2;
	}
	char	file_SE_Damage[] = "data\\SE\\SE_Damage_B.wav";
	g_SE_Damage = LoadSound(file_SE_Damage);

	pPlayer = GetPlayer();
	nowY = 0;

	NowStage = Stagenum;

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
	if (g_TextureEnemyBulletTrans)
	{						
		g_TextureEnemyBulletTrans->Release();
		g_TextureEnemyBulletTrans = NULL;
	}
	if (g_TextureEnemyBulletHp)
	{
		g_TextureEnemyBulletHp->Release();
		g_TextureEnemyBulletHp = NULL;
	}


}

//更新処理
void UpdateEnemyBullet()
{
	

	SPECIAL* sp = GetSpecial();

	if (EnemyAlfa >= 1.0f)
	{
		AddAlfa = false;
	}
	else if (EnemyAlfa <= 0.25f)
	{
		AddAlfa = true;
	}

	if (AddAlfa)
	{
		EnemyAlfa += ENEMYBULLET_ALFA_CHANGE;
	}
	else
	{
		EnemyAlfa -= ENEMYBULLET_ALFA_CHANGE;
	}

	if (EnemyAlfa >= 0.65f)
	{
		HitBullet = true;
	}
	else
	{
		HitBullet = false;
	}


	for (int i = 0; i < ENEMYBULLET_NOMAL_MAX; i++)
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
					pPlayer->hp -= 0.0f;
				}
				else
				{
					pPlayer->hp -= 50.0f;
				}

				PlaySound(g_SE_Damage, 0);
			}
		}
	}

	for (int k = 0; k < ENEMYBULLET_LONG_MAX; k++)
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
					pPlayer->hp -= 0.0f;
				}
				else
				{
					pPlayer->hp -= 30.0f;
				}
				g_EnemyBulletLong[k].pos -= g_EnemyBulletLong[k].mov;
				PlaySound(g_SE_Damage, 0);
			}

		}
	}
	

	for (int k = 0; k < ENEMYBULLET_TRANSLUCENT_MAX; k++)
	{
		if (g_EnemyBulletTrans[k].use == true)
		{
			g_EnemyBulletTrans[k].pos += g_EnemyBulletTrans[k].mov;	//移動

			if (g_EnemyBulletTrans[k].pos.y > SCREEN_HEIGHT - g_EnemyBulletTrans[k].h)
			{
				g_EnemyBulletTrans[k].use = false;
			}

			if (CollisionBB(g_EnemyBulletTrans[k].pos, pPlayer->pos, D3DXVECTOR2(g_EnemyBulletTrans[k].w, g_EnemyBulletTrans[k].h), pPlayer->size / 2))
			{
				if (HitBullet)
				{
					g_EnemyBulletTrans[k].use = false;
					if (sp->get_damage_down == true)
					{
						pPlayer->hp -= 0.0f;
					}
					else
					{
						pPlayer->hp -= 50.0f;
					}
					PlaySound(g_SE_Damage, 0);
				}
			}

		}
	}
	for (int j = 0; j < ENEMYBULLET_HP_MAX; j++)
	{
		if (g_EnemyBulletHp[j].use == true)
		{
			g_EnemyBulletHp[j].pos += g_EnemyBulletHp[j].mov;	//移動

			if (g_EnemyBulletHp[j].pos.y > SCREEN_HEIGHT - g_EnemyBulletHp[j].h / 2)
			{
				g_EnemyBulletHp[j].use = false;
			}

			for (int h = 0; h < BULLET_MAX; h++)
			{
				if ((pBullet + h)->use)
				{
					if (CollisionBB(g_EnemyBulletHp[j].pos, (pBullet + h)->pos, D3DXVECTOR2(g_EnemyBulletHp[j].w, g_EnemyBulletHp[j].h), D3DXVECTOR2((pBullet + h)->w / 2, (pBullet + h)->h / 2)))
					{
						if (sp->damage_up)
						{
							g_EnemyBulletHp[j].hp = 0;
						}
						else
						{
							g_EnemyBulletHp[j].hp--;
						}
						(pBullet + h)->use = false;

						if (g_EnemyBulletHp[j].hp <= 0)
						{
							g_EnemyBulletHp[j].use = false;
						}
					}
				}
			}

			if (CollisionBB(g_EnemyBulletHp[j].pos, pPlayer->pos - D3DXVECTOR2(0.0f, pPlayer->size.y / 4.0f), D3DXVECTOR2(g_EnemyBulletHp[j].w, g_EnemyBulletHp[j].h), pPlayer->size / 2))
			{
				g_EnemyBulletHp[j].use = false;
				if (sp->get_damage_down == true)
				{
					pPlayer->hp -= 0.0f;
				}
				else
				{
					pPlayer->hp -= 70.0f;
				}
				PlaySound(g_SE_Damage, 0);
			}

		}
	}

}

void DrawEnemyBullet()
{

	for (int x = 0; x < ENEMYBULLET_NOMAL_MAX; x++)
	{
		if (g_EnemyBulletNomal[x].use)
		{
			DrawSpriteColor(g_EnemyBulletNomalTex, g_EnemyBulletNomal[x].pos.x, g_EnemyBulletNomal[x].pos.y, g_EnemyBulletNomal[x].w, g_EnemyBulletNomal[x].h,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}

	for (int y = 0; y < ENEMYBULLET_LONG_MAX; y++)
	{
		if (g_EnemyBulletLong[y].use)
		{
			DrawSpriteColor(g_EnemyBulletLongTex, g_EnemyBulletLong[y].pos.x, g_EnemyBulletLong[y].pos.y, g_EnemyBulletLong[y].w, g_EnemyBulletLong[y].h,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}

	for (int w = 0; w < ENEMYBULLET_TRANSLUCENT_MAX; w++)
	{
		if (g_EnemyBulletTrans[w].use)
		{
			DrawSpriteColor(g_EnemyBulletTransTex, g_EnemyBulletTrans[w].pos.x, g_EnemyBulletTrans[w].pos.y, g_EnemyBulletTrans[w].w, g_EnemyBulletTrans[w].h,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, EnemyAlfa));
		}
	}
	for (int z = 0; z < ENEMYBULLET_HP_MAX; z++)
	{
		if (g_EnemyBulletHp[z].use)
		{
			DrawSpriteColor(g_EnemyBulletHpTex, g_EnemyBulletHp[z].pos.x, g_EnemyBulletHp[z].pos.y, g_EnemyBulletHp[z].w, g_EnemyBulletHp[z].h,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 0.3 * g_EnemyBulletHp[z].hp, 0.3 * g_EnemyBulletHp[z].hp, 1.0));
		}
	}
}

void SETBULLET()
{
	int atk = 0;	//敵の攻撃用
	bool IsAtk = true;

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
					for (int i = 0; i < ENEMYBULLET_NOMAL_MAX; i++)
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
					for (int k = 0; k < ENEMYBULLET_LONG_MAX; k++)
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
					for (int i = 0; i < ENEMYBULLET_TRANSLUCENT_MAX; i++)
					{
						if (g_EnemyBulletTrans[i].use == false)
						{
							g_EnemyBulletTrans[i].pos.x = atk;
							g_EnemyBulletTrans[i].pos.y = -10.0f;
							g_EnemyBulletTrans[i].use = true;
							break;
						}
					}
				}
				break;
			case 4:
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
					for (int k = 0; k < ENEMYBULLET_HP_MAX; k++)
					{
						if (g_EnemyBulletHp[k].use == false)
						{
							g_EnemyBulletHp[k].pos.x = atk;
							g_EnemyBulletHp[k].pos.y = -20.0f;
							g_EnemyBulletHp[k].hp = 3;
							g_EnemyBulletHp[k].use = true;
							break;
						}
					}
				}
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