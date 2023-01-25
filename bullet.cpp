//====================================================
//バレット
//作成：町田裕哉
//		2022/10/26
//====================================================
#include "bullet.h"
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "special.h"
#include "effect.h"
#include "collision.h"

//================================
//グローバル変数
//================================
BULLET g_Bullet[BULLET_MAX];


//================================
//初期化
//================================

HRESULT InitBullet()
{
	//テクスチャのロード
	int texno = LoadTexture((char*)"data\\TEXTURE\\bullet_P.png");
	//構造体の初期化
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use = false;
		g_Bullet[i].w = BULLET_SIZE_W;
		g_Bullet[i].h = BULLET_SIZE_H;
		g_Bullet[i].pos = D3DXVECTOR2(0, 0);
		g_Bullet[i].texNo = texno;
		g_Bullet[i].mov = D3DXVECTOR2(0, -BULLET_SPEED);

	}
	return S_OK;
}

//終了処理
void UninitBullet()
{
}

//更新処理
void UpdateBullet()
{
	ENEMY* pEnemy = GetEnemy();

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)
		{
			g_Bullet[i].oldpos = g_Bullet[i].pos;	//当たり判定用の座標コピー

			g_Bullet[i].pos += g_Bullet[i].mov;	//移動

			if (g_Bullet[i].pos.y < 0 - g_Bullet[i].h / 2)
			{
				g_Bullet[i].use = false;
			}

			if (pEnemy->use)
			{
				if(CollisionBB(g_Bullet[i].pos,pEnemy->pos,D3DXVECTOR2(g_Bullet[i].w,g_Bullet[i].h),pEnemy->size))
				{

					pEnemy->hp -= Damage();
					SetEffect(EFFECT_2, g_Bullet[i].pos, D3DXVECTOR2(100,100));
					g_Bullet[i].use = false;
				}
			}
		}
	}
}

void DrawBullet()
{
	
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use)
		{
			DrawSpriteColor(g_Bullet[i].texNo, g_Bullet[i].pos.x, g_Bullet[i].pos.y, BULLET_SIZE_W, BULLET_SIZE_H,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}
}

BULLET * GetBullet()
{
	return &g_Bullet[0];
}

void SetBullet(D3DXVECTOR2 pos)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == false)
		{
			g_Bullet[i].pos = pos;
			g_Bullet[i].use = true;
			return;
		}
	}
}

//ダメージの計算　returnでダメージの数値を返す
int Damage()
{
	SPECIAL* sp = GetSpecial();

	int damage;

	//当該special発動中のダメージの増加
	if (sp->damage_up == true)
	{
		float m = 1, n = GetEnemyNum();
		for (int i = 0; i < n; i++) {
			m *= 0.9f;
		}
		damage = 250 * m;
		return damage;
	}
	//非発動時のデフォルト数値
	else
	{
		float m = 1, n = GetEnemyNum();
		for (int i = 0; i < n; i++) {
			m *= 0.9f;
		}
		damage = 90 * m;
		return damage;
	}
}