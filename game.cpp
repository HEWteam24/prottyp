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
#include "lane.h"
#include "keyboard.h"
#include "special.h"

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
HRESULT InitGame(int StageNum)
{
	InitPlayer();
	InitBullet();
	InitScore();
	InitCombo();

	InitSpecial();
	InitEnemy();
	InitEnemyBullet();
	InitRhythm(StageNum);
	// 背景の初期化
	InitBG();
	InitLane();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	UninitBG();
	UninitLane();

	UninitBullet();

	UninitEnemy();
	UninitEnemyBullet();
	UninitRhythm();
	UninitCombo();
	UninitSpecial();

	StopSound(g_BGMGame);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	//エンターキーが押されたらSCENE_GAMEへ移行する
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_TITLE);
	}
	UpdateRhythm();

	if (GetFreame() > 120) {

		if (!MusicEnd()) {
			UpdateBG();
			UpdateLane();

			UpdatePlayer();
			UpdateBullet();
			UpdateEnemy();
			UpdateEnemyBullet();
			UpdateScore();
			UpdateCombo();
			UpdateSpecial();
		}
		else {
			SceneTransition(SCENE_RESULT);
		}
	}
	

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();
	DrawLane();
	
	DrawCombo();
	DrawBullet();
	DrawPlayer();
	DrawEnemyBullet();
	DrawEnemy();
	DrawRhythm();
	DrawHp();
	DrawSpecial();
	DrawScore();

}
