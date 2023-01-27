/*==============================================================================

   タイトル画面処理 [title.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LOGO_POS_Y	(300.0f)
#define LINE_DIST	(60.0f)
#define TITLE_SIZE	(1400.0f)
#define TITLE_POS_Y (650.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureBgTitle;//タイトル画面用テクスチャの識別子
static int g_TextureFFF;
static int g_TextureLine;
static int g_TextureCommand;
static int g_TextureCommand_Y;
static int g_TextureTitle;
static int g_TextureUIText;
static int g_TextureUIButton;

float	TitleAlpha;
float	lineX[2];
float	Fsize[3];
float	FposY[3];
bool	Fstate[3];
bool	change[3];

int FFFframe[3];
int FFFChange[3];
int TitleFrame;

static int g_BGMNo;//タイトル用BGMの識別子
static int g_SE;		//弾サウンド
static int g_SE_S;
static int g_SE_START;
static int g_VFFF;

bool kakusicommand[11] = { false,false,false,false,false,false,false,false,false,false,false};

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{
	//テクスチャを読み込んで識別子を受け取る
	g_TextureBgTitle = LoadTexture((char*)"data/TEXTURE/Bg_Bubbles.png");
	g_TextureFFF	 = LoadTexture((char*)"data/TEXTURE/fff.png");
	g_TextureLine	 = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	g_TextureCommand = LoadTexture((char*)"data/TEXTURE/command.png");
	g_TextureCommand_Y = LoadTexture((char*)"data/TEXTURE/command_y.png");
	g_TextureTitle	 = LoadTexture((char*)"data/TEXTURE/title_A.png");
	g_TextureUIText	 = LoadTexture((char*)"data/TEXTURE/text_pause_Set.png");
	g_TextureUIButton= LoadTexture((char*)"data/TEXTURE/UI_Buttons_B.png");

	//音声ファイルを読み込んで識別子を受け取る
	g_BGMNo = LoadSound((char*)"data/BGM/BGM_Title.wav");

	char	file_SE		 [] = "data\\SE\\SE_bullet.wav";
	char	file_SE_S	 [] = "data\\SE\\success.wav";
	char	file_VF		 []	= "data\\SE\\SE_FFF.wav";
	char	file_SE_START[]	= "data\\SE\\SE_MenuPush.wav";
	g_SE		= LoadSound(file_SE);
	g_SE_S		= LoadSound(file_SE_S);
	g_VFFF		= LoadSound(file_VF);
	g_SE_START	= LoadSound(file_SE_START);

	//BGMの再生（2つ目の引数はループ回数）
	//ループ回数に負の値を指定すると無限ループ


	lineX[0] = CENTER_X/2*1;
	lineX[1] = CENTER_X/2*3;

	for (int i = 0; i < 3; i++)
	{
		Fsize[i] = 200.0f;
		FposY[i] = LOGO_POS_Y;
		Fstate[i]= false;
		change[i]=false;
		FFFframe[i] = 100+20*i;
		FFFChange[i] = 0;
	}

	//タイトル
	TitleAlpha = 1.1f;
	TitleFrame = 0;

	//隠しコマンド
	for (int i = 0; i < 11; i++)
	{
		kakusicommand[i] = false;
	}

	PlaySound(g_VFFF, 0);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	StopSound(g_BGMNo);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{
	TitleFrame++;

	if (TitleFrame == 120)
	{
		PlaySound(g_BGMNo, 0);
	}

	//エンターキーが押されたらSCENE_STAGESELECTへ移行する
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		PlaySound(g_SE_START, 0);
		SceneTransition(SCENE_STAGESELECT);
	}
	//コントローラーBボタン押したらSCENE_STAGESELECTへ移行
	if (kakusicommand[7] == false && IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		PlaySound(g_SE_START, 0);
		SceneTransition(SCENE_STAGESELECT);
	}

	if (kakusicommand[9] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_START) || Keyboard_IsKeyDown(KK_SPACE)))
	{
		kakusicommand[9] = false;
		kakusicommand[10] = true;
		PlaySound(g_SE_S, 0);
	}
	else if (kakusicommand[8] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_A) || Keyboard_IsKeyDown(KK_A)))
	{
		kakusicommand[8] = false;
		kakusicommand[9] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[7] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_B) || Keyboard_IsKeyDown(KK_B)))
	{
		kakusicommand[7] = false;
		kakusicommand[8] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[6] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT) || Keyboard_IsKeyDown(KK_RIGHT)))
	{
		kakusicommand[6] = false;
		kakusicommand[7] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[5] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT) || Keyboard_IsKeyDown(KK_LEFT)))
	{
		kakusicommand[5] = false;
		kakusicommand[6] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[4] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT) || Keyboard_IsKeyDown(KK_RIGHT)))
	{
		kakusicommand[4] = false;
		kakusicommand[5] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[3] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT) || Keyboard_IsKeyDown(KK_LEFT)))
	{
		kakusicommand[3] = false;
		kakusicommand[4] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[2] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN) || Keyboard_IsKeyDown(KK_DOWN)))
	{
		kakusicommand[2] = false;
		kakusicommand[3] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[1] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN) || Keyboard_IsKeyDown(KK_DOWN)))
	{
		kakusicommand[1] = false;
		kakusicommand[2] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[0] == true && (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP) || Keyboard_IsKeyDown(KK_UP)))
	{
		kakusicommand[0] = false;
		kakusicommand[1] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[0] == false && (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP) || Keyboard_IsKeyDown(KK_UP)))
	{
		for (int i = 0; i < 11; i++)
		{
			kakusicommand[i] = false;
		}

		kakusicommand[0] = true;
		PlaySound(g_SE, 0);
	}

	if (kakusicommand[10] == true)
	{
		for (int i = 0; i < 11; i++)
		{
			kakusicommand[i] = false;
		}
		SceneTransition(SCENE_CREDIT);
	}


	for (int i = 0; i < 2; i++)
	{
		lineX[i] -= 10.0f;
		if (lineX[i] <= 0.0f)
		{
			lineX[i] = CENTER_X * 2;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		FFFframe[i]++;

		if (FFFframe[i] == 300)
		{
			FFFframe[i] = 0;
			FFFChange[i] = true;
		}

		if (FFFChange[i])
		{
			if (Fsize[i] >= 0.1f)
			{
				Fsize[i] *= 0.9;
			}
			else
			{
				if (Fstate[i])
				{
					Fstate[i] = false;
				}
				else
				{
					Fstate[i] = true;
				}

				FFFChange[i] = false;
			}	
		}
		else
		{
			if (Fsize[i] <= 200.0f)
			{
				Fsize[i] *= 1.2;
			}
		}
	}

	//フォルティシッシャモ
	TitleAlpha -= 0.052f;
	if (TitleAlpha <= -1.0f)
	{
		TitleAlpha = 1.0f;
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	DrawSpriteLeftTop(g_TextureBgTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f );

	if (kakusicommand[9])
	{
		DrawSpriteColor(g_TextureCommand_Y, SCREEN_WIDTH - 150, SCREEN_HEIGHT - 50, 210.0f, 50.0f,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
	}
	else
	{
		DrawSpriteColor(g_TextureCommand, SCREEN_WIDTH - 150, SCREEN_HEIGHT - 50, 210.0f, 50.0f,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.7f, 0.7f, 1.0f, 0.4f));
	}

	//Line
	for (int i = 0; i < 5; i++)
	{
		DrawSpriteColor(g_TextureLine,
			CENTER_X, LOGO_POS_Y + LINE_DIST * (i-2),
			SCREEN_WIDTH, 10.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0, 1.0, 1.0, 0.8));
	}

	for (int i = 0; i < 2; i++)
	{
		DrawSpriteColor(g_TextureLine,
			lineX[i], LOGO_POS_Y,
			10.0f, 60.0f*4.1,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0, 1.0, 1.0, 0.8));
	}

	DrawSpriteColor(g_TextureLine,
		CENTER_X, LOGO_POS_Y-100.0f,
		700.0f, 15.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		D3DXCOLOR(0.0, 0.0, 0.0, 1.0));

	for (int i = 0; i < 3; i++)
	{
		if (Fstate[i])
		{
			DrawSpriteColor(g_TextureFFF,
				CENTER_X + (200.0f * (i - 1)), FposY[i],
				Fsize[i], 600.0f,
				0.5f, 1.0f,
				0.5f, 1.0f,
				D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
		else
		{
			DrawSpriteColor(g_TextureFFF,
				CENTER_X + (200.0f * (i - 1)), FposY[i],
				Fsize[i], 600.0f,
				0.0f, 0.0f,
				0.5f, 1.0f,
				D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}

	DrawSpriteColor(g_TextureTitle,
		CENTER_X, LOGO_POS_Y + 300.0f,
		TITLE_SIZE + ((1.0f - TitleAlpha) * 80.0f), (TITLE_SIZE / 7) + ((1.0f - TitleAlpha) * 80.0f),
		0.0f, 0.0f,
		1.0f, 1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, TitleAlpha));

	DrawSpriteColor(g_TextureTitle,
		CENTER_X, LOGO_POS_Y + 300.0f,
		TITLE_SIZE, (TITLE_SIZE/7),
		0.0f, 0.0f,
		1.0f, 1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	//START
	DrawSpriteColor(g_TextureUIText,
		CENTER_X-100.0f, LOGO_POS_Y + 550.0f,
		500.0f+(TitleAlpha*8.0f), 100.0f+(TitleAlpha*8.0f),
		0.0f, 0.0f,
		0.999f, 0.99f/3.0f,
		D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	//START_Button
	DrawSpriteColor(g_TextureUIButton,
		CENTER_X+225.0f, LOGO_POS_Y + 550.0f,
		120.0f+(TitleAlpha * 8.0f), 120.0f+(TitleAlpha * 8.0f),
		0.167f * 2.0f, 0.249f, 0.167f, 0.249f,
		D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
}