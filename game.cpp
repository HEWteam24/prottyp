/*==============================================================================

   ゲーム本編処理 [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "game.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "bg.h"
#include "collision.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "bullet.h"
#include "enemy.h"
#include "enemybullet.h"
#include "rhythm.h"
#include "frame.h"
#include "score.h"
#include "combo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_BGMGame;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	InitPlayer();
	InitBullet();
	InitEnemy();
	InitEnemyBullet();
	InitRhythm();
	InitScore();
	InitCombo();

	// 背景の初期化
	InitBG();

	//音声ファイルを読み込んで識別子を受け取る
	g_BGMGame = LoadSound((char*)"data/BGM/BGM_Tanbo120.wav");
	//PlaySound(g_BGMGame, -1);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	UninitBG();

	UninitBullet();
	UninitPlayer();
	UninitEnemy();
	UninitEnemyBullet();
	UninitRhythm();
	UninitScore();
	UninitCombo();

	StopSound(g_BGMGame);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	//エンターキーが押されたらSCENE_GAMEへ移行する
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SceneTransition(SCENE_TITLE);
	}
	UpdateBG();

	UpdatePlayer();
	UpdateBullet();
	UpdateEnemy();
	UpdateEnemyBullet();
	UpdateRhythm();
	UpdateScore();
	UpdateCombo();

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();
	
	DrawBullet();
	DrawPlayer();
	DrawEnemyBullet();
	DrawEnemy();
	DrawRhythm();
	DrawHp();
	DrawScore();
	DrawCombo();

}
