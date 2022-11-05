/*==============================================================================

   頂点管理 [polygon.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"
#include "sound.h"
#include "main.h"
#include "bullet.h"
#include "fade.h"
#include "rhythm.h"
#include "combo.h"
#include "score.h"
#include "keyboard.h"
#include "inputx.h"
#include <algorithm>

//*****************************************************************************
// マクロ定義
//*****************************************************************************


enum LANE		//レーンのやつ
{
	LANE_1 =-2,
	LANE_2 =-1,
	LANE_3 = 0,
	LANE_4 = 1,
	LANE_5 = 2,
	LANE_NUM,
};
enum DIRECTION	//移動の向き
{
	D_LEFT  = 0,
	D_RIGHT = 1,
};
enum CHECK		//タイミング評価
{
	C_NONE	= 0,
	C_GOOD	= 1,
	C_BAD	= 2,
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TexturePlayer;	//テクスチャのやつ
static int g_TextureHp;		//テクスチャのやつ
static int g_TextureHpGrid;	//テクスチャのやつ
static int g_TextureHpA;	//テクスチャのやつ
static int g_TextureHpB;	//テクスチャのやつ
static int g_TextureCGood;	//テクスチャのやつ
static int g_TextureCBad;	//テクスチャのやつ


static int g_SE_Bullet;		//弾サウンド
static int g_SE_Damage;		//ダメージサウンド

static PLAYER g_Player;


int fire_dist;
int good;
int checkFrame;
float goodAlpha;
float goodPosY;

float  effectPos[10] = {0.0f,0.0f,0.0f,0.0f,0.0f,
						0.0f,0.0f,0.0f,0.0f,0.0f };

static float g_AnimeTable[4] =
{
	0.0f,
	0.125f,
	0.250f,
	0.125f,
};
//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	g_TexturePlayer  = LoadTexture((char*)"data/TEXTURE/player02.png");
	g_TextureHp		 = LoadTexture((char*)"data/TEXTURE/Hp.png");
	g_TextureHpGrid	 = LoadTexture((char*)"data/TEXTURE/HpGrid.png");
	g_TextureHpA = LoadTexture((char*)"data/TEXTURE/HP_player_A.png");
	g_TextureHpB = LoadTexture((char*)"data/TEXTURE/HP_player_B.png");
	g_TextureCGood	 = LoadTexture((char*)"data/TEXTURE/rythm_good.png");
	g_TextureCBad	 = LoadTexture((char*)"data/TEXTURE/rythm_bad.png");

	char	file_SE_Bullet[] = "data\\SE\\SE_bullet.wav";
	char	file_SE_Damage[] = "data\\SE\\SE_deadEnm.wav";
	g_SE_Bullet = LoadSound(file_SE_Bullet);
	g_SE_Damage = LoadSound(file_SE_Damage);
	//初期化
	g_Player.pos	= D3DXVECTOR2(PLAYER_POS_DEFAULT_X, PLAYER_POS_DEFAULT_Y);	//位置
	g_Player.oldpos = D3DXVECTOR2(PLAYER_POS_DEFAULT_X, PLAYER_POS_DEFAULT_Y);	//oldpos
	g_Player.size	= D3DXVECTOR2(PLAYER_SIZE_X,PLAYER_SIZE_Y);	//サイズ
	g_Player.speed	= D3DXVECTOR2(0.0f,	0.0f);					//スピード
	g_Player.uv		= D3DXVECTOR2(0.0f, 0.0f);					//uv

	g_Player.hp = PLAYER_HP_DEFAULT;			//HP

	g_Player.moving		= false;	//移動中フラグ
	g_Player.direction	= D_LEFT;	//移動方向
	g_Player.NowLane	= LANE_3;	//初期レーン
	g_Player.flag		= false;

	//effectPosを初期化
	for (int i = 0; i <= 9; i++)
	{
		effectPos[i] = g_Player.pos.x;
	}

	good = C_NONE;
	checkFrame = 0.0f;
	goodAlpha =1.0f;
	goodPosY = 0.0f;
	fire_dist = 0;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	g_TexturePlayer = NULL;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	BULLET* pBullet = GetBullet();

	goodAlpha -= 0.05f;
	goodPosY  *= 0.1f;

	//残像用 effectPosを保存
	for (int i = 1; i <= 10;i++)
	{
		effectPos[10-i] = effectPos[10 - i - 1];
	}
	effectPos[0] = g_Player.pos.x;

	//体力0でゲームオーバー
	if (g_Player.hp <= 0)
	{
		SceneTransition(SCENE_GAMEOVER);
	}

	//----------------------------------------
	// コントローラー入力
	// ---------------------------------------
	if ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) && (g_Player.moving == false))
	{
		PlayerCheck();
		if (g_Player.flag) {
			SetBullet(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y - g_Player.size.y / 2));
			PlaySound(g_SE_Bullet, 0);
			//g_Player.hp -= 30.0f;
		}
	}


	//スティックで移動
	if ((GetThumbLeftX(0) < -0.3f) && (g_Player.NowLane >= LANE_2) && (g_Player.moving == false))
	{
		g_Player.moving = true;				//移動中
		g_Player.oldpos.x = g_Player.pos.x;	//現在位置保存

		g_Player.speed.x = -50.0f;		//スピードを-に
		g_Player.direction = D_LEFT;		//左移動
		g_Player.NowLane -= 1;			//レーン変更
		PlayerCheck();
	}
	//左
	if ((GetThumbLeftX(0) > 0.3f) && (g_Player.NowLane <= LANE_4) && (g_Player.moving == false))
	{
		g_Player.moving = true;				//移動中
		g_Player.oldpos.x = g_Player.pos.x; //現在位置保存

		g_Player.speed.x = 50.0f;			//スピードを+に
		g_Player.direction = D_RIGHT;		//右移動
		g_Player.NowLane += 1;				//レーン変更
		PlayerCheck();
	}

	//----------------------------------------
	// キーボード入力
	// ---------------------------------------
	//弾発射
	if ((Keyboard_IsKeyDown(KK_SPACE))&&(g_Player.moving==false)&&(fire_dist==0))
	{
		g_Player.moving = true;
		PlayerCheck();
		if (g_Player.flag) {
			SetBullet(D3DXVECTOR2(g_Player.pos.x, g_Player.pos.y - g_Player.size.y / 2));
			PlaySound(g_SE_Bullet, 0);
			//g_Player.hp -= 30.0f;
			
		}
		fire_dist = 30;
	}
	if (fire_dist > 0)
	{
		fire_dist--;
	}

	//Aキーで右移動
	if ((Keyboard_IsKeyDown(KK_A)) && (g_Player.NowLane >= LANE_2) && (g_Player.moving == false))
	{
		g_Player.moving = true;				//移動中
		g_Player.oldpos.x = g_Player.pos.x;	//現在位置保存
		
		g_Player.speed.x	=  -50.0f;		//スピードを-に
		g_Player.direction	=  D_LEFT;		//左移動
		g_Player.NowLane	-= 1;			//レーン変更
		PlayerCheck();
	}

	// Dキー で右移動
	if ((Keyboard_IsKeyDown(KK_D)) && (g_Player.NowLane <= LANE_4) && (g_Player.moving == false))
	{
		g_Player.moving = true;				//移動中
		g_Player.oldpos.x = g_Player.pos.x; //現在位置保存

		g_Player.speed.x = 50.0f;			//スピードを+に
		g_Player.direction = D_RIGHT;		//右移動
		g_Player.NowLane += 1;				//レーン変更
		PlayerCheck();
	}

	//キャラクター移動
	if ((g_Player.moving))
	{
		g_Player.pos.x += g_Player.speed.x;	//スピードを足して移動
		g_Player.speed.x *= 0.7f;			//スピード減衰
	}

	//右移動完了
	if ((g_Player.speed.x <= 1.0f)&&(g_Player.direction	==	D_RIGHT))
	{
		g_Player.pos.x = CENTER_X + g_Player.NowLane*LANE_SIZE_X;	//レーンの中心に
		g_Player.moving = false;
	}
	//左移動完了
	if ((g_Player.speed.x >= -1.0f) && (g_Player.direction == D_LEFT))
	{
		g_Player.pos.x = CENTER_X + g_Player.NowLane*LANE_SIZE_X;	//レーンの中心に
		g_Player.moving = false;
	}



}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	//残像3描画
	DrawSpriteColor(g_TexturePlayer, effectPos[9], g_Player.pos.y, g_Player.size.x, g_Player.size.y,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 0.3));

	//残像2描画
	DrawSpriteColor(g_TexturePlayer, effectPos[6], g_Player.pos.y, g_Player.size.x, g_Player.size.y,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 0.3));

	//残像1描画
	DrawSpriteColor(g_TexturePlayer, effectPos[3], g_Player.pos.y, g_Player.size.x, g_Player.size.y,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 0.3));

	//プレイヤー描画
	DrawSpriteColor(g_TexturePlayer, g_Player.pos.x, g_Player.pos.y, g_Player.size.x, g_Player.size.y,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
}

void DrawHp(void)
{
	////HP下地
	//DrawSpriteColor(g_TextureHp, NOTESLANE_POS_X, NOTESLANE_POS_Y, NOTES_SIZE_X, NOTES_SIZE_Y,
	//	0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.6, 0.6, 0.6, 1.0));
	////HPバー
	//DrawSpriteColor(g_TextureHp, NOTESLANE_POS_X, NOTESLANE_POS_Y+(PLAYER_HP_DEFAULT - g_Player.hp)/(PLAYER_HP_DEFAULT/20), NOTES_SIZE_X, ((PLAYER_HP_DEFAULT-(PLAYER_HP_DEFAULT-g_Player.hp))/(PLAYER_HP_DEFAULT/NOTES_SIZE_Y)),
	//	0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.5, 1.0, 0.3, 1.0));
	////HPグリッド
	//DrawSpriteColor(g_TextureHpGrid, NOTESLANE_POS_X, NOTESLANE_POS_Y, NOTES_SIZE_X, NOTES_SIZE_Y,
	//	0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.8, 0.8, 0.8, 1.0));
	
	//HP下地
	DrawSpriteColor(g_TextureHpB, PLAYER_HP_POS_X, PLAYER_HP_POS_Y, PLAYER_HPB_SIZE_X, PLAYER_HPB_SIZE_Y,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//HPバー
	DrawSpriteColor(g_TextureHpA, PLAYER_HP_POS_X, PLAYER_HP_POS_Y + ((PLAYER_HP_DEFAULT - g_Player.hp) / 0.665), PLAYER_HP_SIZE_X, PLAYER_HP_SIZE_Y - (PLAYER_HP_DEFAULT - g_Player.hp) * 3.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.5f, 1.0f, 0.4f, 1.0f));

	//評価 Good Bad
	if (good == C_NONE)
	{
		//DrawSpriteColor(g_TextureHpGrid, NOTESLANE_POS_X, NOTESLANE_POS_Y, NOTES_SIZE_X, NOTES_SIZE_Y,
		//	0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.8, 0.8, 0.8, 1.0));
	}
	if (good == C_GOOD)
	{
		DrawSpriteColor(g_TextureCGood, NOTESLANE_POS_X, NOTESLANE_POS_Y - 75.0f + (goodPosY), GOOD_BAD_X, GOOD_BAD_Y,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 0.6, 0.4, goodAlpha));
	}
	if (good == C_BAD)
	{
		DrawSpriteColor(g_TextureCBad, NOTESLANE_POS_X, NOTESLANE_POS_Y - 75.0f + (goodPosY), GOOD_BAD_X, GOOD_BAD_Y,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.8, 0.5, 1.0, goodAlpha));
	}
}

//=============================================================================
// ゲッター
//=============================================================================
PLAYER* GetPlayer(void)
{
	return &g_Player;
}
//=============================================================================
// リズムチェック
//=============================================================================
void PlayerCheck(void)
{
	//NOTESLANE* pRythm = GetNotesLane();
	goodAlpha = 1.0f;
	goodPosY = 100.0f;

	//リズムOK判定
	if (GetRhythm())
	{
		good = C_GOOD;

		g_Player.hp = min(g_Player.hp += 1, PLAYER_HP_DEFAULT);
		ComboPlus(1);
		ScorePlus(10+ GetComboScoreUp());
		g_Player.flag = true;
	}
	else  //BAD評価
	{
		good = C_BAD;
		g_Player.hp -= 10.0f;
		PlaySound(g_SE_Damage, 0);
		ResetCombo();
		g_Player.flag = false;
	}
}

