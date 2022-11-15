//====================================================
//エネミー
//作成：勝沼力樹
//		2022/10/26
//====================================================
#include "enemy.h"
#include "collision.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"
#include "enemybullet.h"
#include "input.h"
#include "rhythm.h"
//#include "frame.h"
#include "score.h"
#include "combo.h"


ENEMY		Enemy;
ENEMYHP		EnemyHp;
int			EnemyNum;

//テクスチャ情報の保存変数
static	ID3D11ShaderResourceView	*g_TextureEnemy;
static	char	*g_TextureNameEnemy = ENEMY_TEX;//テクスチャ名
static	ID3D11ShaderResourceView	*g_TextureEnemyHp;
static	char	*g_TextureNameEnemyHpA = ENEMY_HP_TEX_A;//テクスチャ名
static	char	*g_TextureNameEnemyHpB = ENEMY_HP_TEX_B;//テクスチャ名

//===================================================
//　初期化
//===================================================
HRESULT InitEnemy()
{

	Enemy.size = D3DXVECTOR2(ENEMY_SIZE_X, ENEMY_SIZE_Y);
	Enemy.pos = D3DXVECTOR2(ENEMY_SPAWN_POS_X, ENEMY_SPAWN_POS_Y);
	Enemy.sp = D3DXVECTOR2(ENEMY_SP, ENEMY_SP);
	Enemy.rot = 0.0f;
	Enemy.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Enemy.hp = ENEMY_HP;
	Enemy.use = true;

	//テクスチャのロード
	Enemy.texno = LoadTexture(g_TextureNameEnemy);
	if (Enemy.texno == -1)
	{//ロードエラー
		exit(999);
	}

	EnemyHp.size = D3DXVECTOR2(ENEMY_HP_SIZE_X, ENEMY_HP_SIZE_Y);
	EnemyHp.pos = D3DXVECTOR2(ENEMY_HP_POS_X , ENEMY_HP_POS_Y);
	EnemyHp.rot = 0.0f;
	EnemyHp.col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	//テクスチャのロード
	EnemyHp.texnoA = LoadTexture(g_TextureNameEnemyHpA);
	if (EnemyHp.texnoA == -1)
	{//ロードエラー
		exit(999);
	}
	EnemyHp.texnoB = LoadTexture(g_TextureNameEnemyHpB);
	if (EnemyHp.texnoB == -1)
	{//ロードエラー
		exit(999);
	}

	EnemyNum = 1;
	return S_OK;
}

//===================================================
//　終了処理
//===================================================
void UninitEnemy()
{

}

//===================================================
//　更新処理
//===================================================
void UpdateEnemy()
{

	if (Enemy.use) 
	{
		Enemy.pos.x += Enemy.sp.x;		//エネミー横移動

		//エネミーがレーン端に触れたら反転
		if (Enemy.pos.x - Enemy.size.x/2 <= SCREEN_WIDTH/2 - LANE_SIZE_X*2 - LANE_SIZE_X/2) 
		{
			Enemy.sp.x *= -1;
		}
		else if (Enemy.pos.x + Enemy.size.x/2 >= SCREEN_WIDTH / 2 + LANE_SIZE_X * 2 + LANE_SIZE_X / 2)
		{
			Enemy.sp.x *= -1;
		}

		//体力0でエネミー死
		if (Enemy.hp <= 0) 
		{
			Enemy.use = false;
			Enemy.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, ENEMY_SPAWN_POS_Y - 300.0f);
 			ScorePlus((500 * EnemyNum)*GetComboScoreUp());
			EnemyNum++;

		}
	}

	//newエネミー誕生
	if(!Enemy.use)
	{
		Enemy.pos.y += Enemy.sp.y;
		if (Enemy.pos.y >= ENEMY_SPAWN_POS_Y) 
		{
			Enemy.hp  = ENEMY_HP ;
			Enemy.use = true;
		}
	}

	//enemyBullet	(デバッグ用)
	//if ((GetKeyboardTrigger(DIK_S)))
	//{
	//	SetEnemyBulletNomal(Enemy.pos);
	//}
}

//===================================================
//　描画処理
//===================================================
void DrawEnemy()
{

		DrawSprite(Enemy.texno, Enemy.pos.x, Enemy.pos.y, Enemy.size.x, Enemy.size.y,
			0.0f, 0.0f, 1.0f, 1.0f);

		DrawSpriteColor(EnemyHp.texnoB, EnemyHp.pos.x, EnemyHp.pos.y, EnemyHp.size.x + 10.0f, EnemyHp.size.y + 10.0f,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//横表示
		//DrawSpriteColor(EnemyHp.texnoA, EnemyHp.pos.x - ((ENEMY_HP - Enemy.hp)/2), EnemyHp.pos.y, EnemyHp.size.x -(ENEMY_HP- Enemy.hp) , EnemyHp.size.y,
		//	0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		//縦表示
		DrawSpriteColor(EnemyHp.texnoA, EnemyHp.pos.x, EnemyHp.pos.y + ((ENEMY_HP - Enemy.hp) / 1.11), EnemyHp.size.x, EnemyHp.size.y - (ENEMY_HP - Enemy.hp) * 1.8,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		

}

ENEMY * GetEnemy()
{
	return &Enemy;
}

int	GetEnemyNum()
{
	return EnemyNum;
}