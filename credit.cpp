/*==============================================================================

   クレジット画面処理 [credit.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "credit.h"
#include "texture.h"
#include "sprite.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#define CREDIT_Y	(3800.0f)
float credit_nowY = SCREEN_HEIGHT + (CREDIT_Y / 2);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureCredit;
static int g_TextureThankyou;

static int g_BGM_CREDIT;//クレジット用BGMの識別子

float t_alfa = 0.0f;
bool credit = true;
bool thankyou = false;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCredit(void)
{
	credit_nowY = SCREEN_HEIGHT + (CREDIT_Y / 2);
	t_alfa = 0.0f;
	credit = true;
	thankyou = false;

	//テクスチャを読み込んで識別子を受け取る
	g_TextureCredit = LoadTexture((char*)"data/TEXTURE/credit_B.png");
	g_TextureThankyou = LoadTexture((char*)"data/TEXTURE/thankyou.png");
	//音声ファイルを読み込んで識別子を受け取る
	char	file_BGM_CREDIT[] = "data\\BGM\\credit_B.wav";
	g_BGM_CREDIT = LoadSound(file_BGM_CREDIT);

	//BGMの再生（2つ目の引数はループ回数）
	//ループ回数に負の値を指定すると無限ループ
	PlaySound(g_BGM_CREDIT,0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitCredit(void)
{
	StopSound(g_BGM_CREDIT);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateCredit(void)
{
	//エンターキーが押されたらSCENE_STAGESELECTへ移行する
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_TITLE);
	}
	//コントローラーBボタン押したらSCENE_STAGESELECTへ移行
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) || IsButtonTriggered(0, XINPUT_GAMEPAD_B)|| IsButtonTriggered(0, XINPUT_GAMEPAD_X)|| IsButtonTriggered(0, XINPUT_GAMEPAD_Y)|| IsButtonTriggered(0, XINPUT_GAMEPAD_START))
	{
		SceneTransition(SCENE_TITLE);
	}

	if (credit_nowY - 700 >= -CREDIT_Y / 2)
	{
		credit_nowY--;
	}
	else
	{
		credit = false;
	}

	if (!credit && t_alfa <= 1.0f || thankyou && t_alfa <= 1.0f)
	{
		t_alfa += 0.002f;
	}
	else if(!thankyou && !credit)
	{
		thankyou = true;
		t_alfa = 0.0f;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawCredit(void)
{
	if (!thankyou)
	{
		DrawSpriteColor(g_TextureCredit, CENTER_X, credit_nowY, 1500.0f, CREDIT_Y,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - t_alfa));
	}
	else
	{
		DrawSpriteColor(g_TextureThankyou, CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_HEIGHT,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, t_alfa));
	}
}
