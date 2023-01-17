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

#include "effect.h"

#include "pause.h"

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
bool start;

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
	InitEnemy(StageNum);
	InitEnemyBullet(StageNum);
	InitRhythm(StageNum);
	InitEffect();
	// 背景の初期化
	InitBG(StageNum);
	InitLane();

	//*****************************************************************************************************************
	//  ゲーム開始カウント
	//	true  = あり
	//	false = なし

		start = true;
	//*****************************************************************************************************************

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
	UninitEffect();

	StopSound(g_BGMGame);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	PAUSE* pPause = GetPause();

	//エンターキーが押されたらSCENE_GAMEへ移行する
	if (Keyboard_IsKeyDown(KK_G))
	{
		SceneTransition(SCENE_TITLE);
	}

	UpdateRhythm();
	if (GetFreame() > 30) {

		if (start)
		{
			pPause->pause = true;
			pPause->restart = true;
			pPause->pause_frame = 0;
			pPause->alpha = 0.2f;
		}

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

			if (start)
			{
				start = false;
			}

		}
		else {
			SceneTransition(SCENE_RESULT);
		}
	}

	if (!pPause->restart)
	{
		pPause->alpha = 0.7f;
	}

	UpdateEffect();
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
	DrawRhythm();
	DrawHp();
	DrawSpecial();
	DrawScore();
	DrawEnemy();
	DrawEffect();
}
