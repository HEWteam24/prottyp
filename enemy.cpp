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
int			UnagiPosY;
bool		BadFlag;
//テクスチャ情報の保存変数
static	ID3D11ShaderResourceView	*g_TextureEnemy;
static  int		g_TextureEnemyID;
static	ID3D11ShaderResourceView	*g_TextureEnemyHp;
static	char	*g_TextureNameEnemyHpA = ENEMY_HP_TEX_A;//テクスチャ名
static	char	*g_TextureNameEnemyHpB = ENEMY_HP_TEX_B;//テクスチャ名
static  int		g_TextureEnemyIcon;

//===================================================
//　初期化
//===================================================
HRESULT InitEnemy(int StageNum)
{
	UnagiPosY = 0;

	//テクスチャのロード
	switch (StageNum)
	{
	default:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_zarigani_dummy.png");
			Enemy.size = D3DXVECTOR2(ENEMY00_SIZE_X, ENEMY00_SIZE_Y);
		break;

		case 0:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_zarigani_dummy.png");
			Enemy.size = D3DXVECTOR2(ENEMY00_SIZE_X, ENEMY00_SIZE_Y);
		break;
		case 1:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_zarigani.png");
			Enemy.size = D3DXVECTOR2(ENEMY01_SIZE_X, ENEMY01_SIZE_Y);
			break;
		case 2:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_unagi.png");
			Enemy.size = D3DXVECTOR2(ENEMY02_SIZE_X, ENEMY02_SIZE_Y);
			UnagiPosY = 200.0;
			break;
		case 3:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_octopus.png");
			Enemy.size = D3DXVECTOR2(ENEMY03_SIZE_X, ENEMY03_SIZE_Y);
			break;
		case 4:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_shark.png");
			Enemy.size = D3DXVECTOR2(ENEMY04_SIZE_X, ENEMY04_SIZE_Y);
			break;
		case 5:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_shishamo muscle.png");
			Enemy.size = D3DXVECTOR2(ENEMY05_SIZE_X, ENEMY05_SIZE_Y);
			break;
		case 6:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_zarigani_shirokuro.png");
			Enemy.size = D3DXVECTOR2(ENEMY06_SIZE_X, ENEMY06_SIZE_Y);
			break;
		case 7:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_unagidon_yankee.png");
			Enemy.size = D3DXVECTOR2(ENEMY07_SIZE_X, ENEMY07_SIZE_Y);
			break;
		case 8:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_shiokara_musha.png");
			Enemy.size = D3DXVECTOR2(ENEMY08_SIZE_X, ENEMY08_SIZE_Y);
			break;
		case 9:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_shark_yankee.png");
			Enemy.size = D3DXVECTOR2(ENEMY09_SIZE_X, ENEMY09_SIZE_Y);
			break;
		case 10:
			g_TextureEnemyID = LoadTexture((char*)"data/TEXTURE/chara_mm meka(combinated).png");
			Enemy.size = D3DXVECTOR2(ENEMY10_SIZE_X, ENEMY10_SIZE_Y);
			break;
	}
	g_TextureEnemyIcon = LoadTexture((char*)"data/TEXTURE/HP_Icon.png");
	
	Enemy.pos = D3DXVECTOR2(ENEMY_SPAWN_POS_X, ENEMY_SPAWN_POS_Y - UnagiPosY);
	Enemy.sp = D3DXVECTOR2(ENEMY_SP, ENEMY_SP);
	Enemy.rot = 0.0f;
	Enemy.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Enemy.hp = ENEMY_HP;
	Enemy.use = true;


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

	BadFlag = false;
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
		if (Enemy.pos.y >= ENEMY_SPAWN_POS_Y - UnagiPosY)
		{
			Enemy.hp  = ENEMY_HP ;
			Enemy.use = true;
		}
	}
}

//===================================================
//　描画処理
//===================================================
void DrawEnemy()
{

		DrawSprite(g_TextureEnemyID, Enemy.pos.x, Enemy.pos.y, Enemy.size.x, Enemy.size.y,
		0.0f, 0.0f, 1.0f, 1.0f);

		//縦表示
		DrawSpriteColor(EnemyHp.texnoA, EnemyHp.pos.x, EnemyHp.pos.y + ((ENEMY_HP - Enemy.hp) / 1.11), EnemyHp.size.x, EnemyHp.size.y - (ENEMY_HP - Enemy.hp) * 1.8,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		
		DrawSpriteColor(EnemyHp.texnoB, EnemyHp.pos.x, EnemyHp.pos.y, EnemyHp.size.x + 10.0f, EnemyHp.size.y + 10.0f,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		//HPアイコン
		DrawSpriteColor(g_TextureEnemyIcon, EnemyHp.pos.x, PLAYER_HP_POS_Y - 490.0f, PLAYER_HP_SIZE_X + 15.0f, PLAYER_HP_SIZE_X + 15.0f,
			0.0f, 0.0f, 0.5f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

}

ENEMY * GetEnemy()
{
	return &Enemy;
}

int	GetEnemyNum()
{
	return EnemyNum;
}
int GetEnemyTex() 
{
	return g_TextureEnemyID;
}
bool BadEnd()
{
	if (!BadFlag) {
		Enemy.sp.x = 0;
		Enemy.pos.y -= Enemy.sp.y * 4.2;
		if (Enemy.pos.y + Enemy.size.y < 0) {
			BadFlag = true;
		}
	}
	else {
		Enemy.size.x = Enemy.size.x * 1.05;
		Enemy.size.y = Enemy.size.y * 1.05;

		Enemy.pos.x = ENEMY_SPAWN_POS_X;
		Enemy.pos.y -= Enemy.sp.y * 2.0;

		if (Enemy.pos.y < 1080 - 200) {
			return true;
		}
		else {
			return false;
		}
	}
}