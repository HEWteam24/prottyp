/*==============================================================================

   タイトル画面処理 [Result.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Result.h"
#include "texture.h"
#include "sprite.h"
//#include "input.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"

#include "score.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureBgTitle;//タイトル画面用テクスチャの識別子
static int g_TextureShishamo;
static int g_BGMNo;//タイトル用BGMの識別子

float	Shishamo_pos;
float	Shishamo_spd;
bool	moving;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(void)
{
	g_TextureBgTitle = LoadTexture((char*)"data/TEXTURE/Back_Clear.png");
	g_TextureShishamo = LoadTexture((char*)"data/TEXTURE/Shishamo_end_1.png");
	InitScoreResult();

	Shishamo_pos = -450.0f;
	Shishamo_spd = 85.0f;
	moving = true;
	//g_BGMNo = LoadSound((char*)"data/BGM/BGM_Result.wav");
	//PlaySound(g_BGMNo, -1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	UninitScore();
	StopSound(g_BGMNo);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	//エンターキーが押されたらSCENE_TITLEへ移行する
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_TITLE);
	}
	//コントローラーBボタン押したらSCENE_TITLEへ移行
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		SceneTransition(SCENE_TITLE);
	}

	//キャラクター移動
	if (moving)
	{
		Shishamo_pos += Shishamo_spd;	//スピードを足して移動
		Shishamo_spd *= 0.9f;			//スピード減衰
	}

	//右移動完了
	if (Shishamo_spd <= 1.0f)
	{
		//Shishamo_pos = 450.0f;	//レーンの中心に
		moving = false;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	DrawSpriteLeftTop(g_TextureBgTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteColor(g_TextureShishamo, Shishamo_pos, CENTER_Y, 900.0f, 900.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));

	DrawScore();
}
