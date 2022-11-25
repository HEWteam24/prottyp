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
				if (
					g_Bullet[i].pos.y - (g_Bullet[i].h / 2) < (pEnemy->pos.y + pEnemy->size.y / 2) &&
					g_Bullet[i].oldpos.y - (g_Bullet[i].h / 2) > (pEnemy->pos.y - pEnemy->size.y / 2) &&
					g_Bullet[i].pos.x < (pEnemy->pos.x + pEnemy->size.x / 2) &&
					g_Bullet[i].pos.x >(pEnemy->pos.x - pEnemy->size.x / 2)
					)
				{
					if (GetEnemyNum() > 0) {
						pEnemy->hp -= Damage() / (GetEnemyNum() * 1.5);
						g_Bullet[i].use = false;
					}
					else {
						pEnemy->hp -= Damage();
						g_Bullet[i].use = false;
					}
					//if (pEnemy->hp <= 0)
					//{
					//	pEnemy->use = false;
					//}
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
			////テクスチャのセット
			//GetDeviceContext()->PSSetShaderResources
			//(0, 1, GetTexture(g_Bullet[i].texNo));	//スプライトの描画

			//DrawSprite
			//(
			//	g_Bullet[i].pos.x,
			//	g_Bullet[i].pos.y,
			//	g_Bullet[i].w,
			//	g_Bullet[i].h,
			//	g_Bullet[i].rot,
			//	D3DXCOLOR(1.0, 1.0, 1.0, 1.0),	//白色
			//	g_Bullet[i].texNo,		//アニメーションパターン番号
			//	1,				//パターンの横サイズ
			//	1				//    　　　縦サイズ
			//						//横に並ぶパターンの数

			//);

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
		damage = 450;
		return damage;
	}
	//非発動時のデフォルト数値
	else
	{
		damage = 90;
		return damage;
	}
}