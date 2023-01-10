/*==============================================================================

   ゲーム本編処理 [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "tuto.h"
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
static int g_TextureTutoDark;
bool stop;

CIRCLE circle;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTuto(void)
{
	g_TextureTutoDark = LoadTexture((char*)"data/TEXTURE/Tuto.png");

	InitPlayer();
	InitBullet();
	InitScore();
	InitCombo();

	InitSpecial();
	InitEnemy(0);
	InitEnemyBullet();
	InitRhythm(0);
	// 背景の初期化
	InitBG(0);
	InitLane();

	stop = false;

	circle.size = D3DXVECTOR2(1920.0f,1920.0f*3);
	circle.pos  = D3DXVECTOR2(CENTER_X, 0.0f-450.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTuto(void)
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
void UpdateTuto(void)
{
	//エンターキーが押されたらSCENE_GAMEへ移行する
	if (Keyboard_IsKeyDown(KK_G))
	{
		SceneTransition(SCENE_TITLE);
	}

	if (stop == false)
	{
		UpdateRhythm();
	}

	if ((GetFreame() > 120)&&(stop==false)) {

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
			SceneTransition(SCENE_STAGESELECT);
		}
	}

	if (GetFreame() == 121)
	{
		PauseSound(BGM_RE());
		stop = true;
	}


	if (((Keyboard_IsKeyDown(KK_ENTER)))&&(stop == true))
	{
		RePlaySound(BGM_RE());
		stop = false;
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTuto(void)
{
	//背景の描画処理
	//DrawBG();
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

	if (stop == true) {
		DrawSpriteColor(g_TextureTutoDark, circle.pos.x, circle.pos.y, circle.size.x, circle.size.y,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
}
