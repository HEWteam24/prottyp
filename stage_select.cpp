/*==============================================================================

   タイトル画面処理 [StageSelect.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "stage_select.h"
#include "texture.h"
#include "sprite.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WHITE_MAX  (15)
#define WHITE_DIST (40)
#define	HARD_SIZE  (300.0f)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************


static int g_TextureBgStageSelect[2];//タイトル画面用テクスチャの識別子
static int g_TextureNamePlate;
static int g_TextureArrow;
static int g_TextureWhite;
static int g_TextureOct;
static int g_TextureUIButton;
static int g_TextureUIHard;

static int g_BGMNo[11];//タイトル用BGMの識別子

int NowSelect = (int)STAGE_1;

float alpha;
float color;

float HardCol[2];
float octRot[2];
float arrowSize[2];
STAGE_PANEL g_StagePanel[STAGE_MAX];
WHITEBOX	g_White[WHITE_MAX];
int whiteCnt;

D3DXCOLOR ARROW_COL[2];
D3DXCOLOR PLATE_COL;
bool ura = false;
bool change = false;
bool first = true;
bool playing = true;
int playFst = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStageSelect(void)
{
	//テクスチャを読み込んで識別子を受け取る
	g_TextureBgStageSelect[0] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");
	g_TextureBgStageSelect[1] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");

	g_TextureOct = LoadTexture((char*)"data/TEXTURE/oct.png");

	g_TextureNamePlate = LoadTexture((char*)"data/TEXTURE/BOSS_NAME.png");
	g_TextureArrow	   = LoadTexture((char*)"data/TEXTURE/arrow.png");

	g_StagePanel[STAGE_0].texnoA = LoadTexture((char*)"data/TEXTURE/Stage_Panel0.png");
	g_StagePanel[STAGE_1].texnoA = LoadTexture((char*)"data/TEXTURE/Stage_Panel1.png");
	g_StagePanel[STAGE_2].texnoA = LoadTexture((char*)"data/TEXTURE/Stage_Panel2.png");
	g_StagePanel[STAGE_3].texnoA = LoadTexture((char*)"data/TEXTURE/Stage_Panel3.png");
	g_StagePanel[STAGE_4].texnoA = LoadTexture((char*)"data/TEXTURE/Stage_Panel4.png");
	g_StagePanel[STAGE_5].texnoA = LoadTexture((char*)"data/TEXTURE/Stage_Panel5.png");

	g_StagePanel[STAGE_0].texnoB = LoadTexture((char*)"data/TEXTURE/Stage_Panel0.png");
	g_StagePanel[STAGE_1].texnoB = LoadTexture((char*)"data/TEXTURE/Stage_Panel6.png");
	g_StagePanel[STAGE_2].texnoB = LoadTexture((char*)"data/TEXTURE/Stage_Panel7.png");
	g_StagePanel[STAGE_3].texnoB = LoadTexture((char*)"data/TEXTURE/Stage_Panel8.png");
	g_StagePanel[STAGE_4].texnoB = LoadTexture((char*)"data/TEXTURE/Stage_Panel9.png");
	g_StagePanel[STAGE_5].texnoB = LoadTexture((char*)"data/TEXTURE/Stage_Panel10.png");

	g_TextureWhite = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	g_TextureUIButton = LoadTexture((char*)"data/TEXTURE/UI_Buttons.png");
	g_TextureUIHard = LoadTexture((char*)"data/TEXTURE/UI_Hard.png");

	char	filename0[] = "data\\BGM\\00_Tutorial_120.wav";
	char	filename1[] = "data\\BGM\\01_Zarigani_120.wav";
	char	filename2[] = "data\\BGM\\02_Unagi_120.wav";
	char	filename3[] = "data\\BGM\\01_Zarigani_120.wav";
	char	filename4[] = "data\\BGM\\04_Shark_120.wav";
	char	filename5[] = "data\\BGM\\05_Shishamo_150.wav";
	char	filename6[] = "data\\BGM\\06_Zarigani_150.wav";
	char	filename7[] = "data\\BGM\\07_Unadon_150.wav";
	char	filename8[] = "data\\BGM\\08_Shiokara_150.wav";
	char	filename9[] = "data\\BGM\\07_Unadon_150.wav";
	char	filename10[] = "data\\BGM\\08_Shiokara_150.wav";

	//初回のみ実行
	if (first)
	{
		//構造体の初期化
		for (int i = 0; i < STAGE_MAX; i++)
		{
			g_StagePanel[i].pos = D3DXVECTOR2(-480.0f * 2 + i * 480.0f, CENTER_Y - 50.0f);
			g_StagePanel[i].spd = 10.0f;
			g_StagePanel[i].size = D3DXVECTOR2(300.0f, 300.0f);
			g_StagePanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_StagePanel[i].direction = D_RIGHT;
			g_StagePanel[i].moving = true;
			g_StagePanel[i].NowLane = i + 3;
		}
		ura = false;
		first = false;
		playing = true;

		g_StagePanel[1].size = D3DXVECTOR2(395.0f, 395.0f);;
		g_StagePanel[STAGE_5].NowLane = PLANE_1;

		g_BGMNo[0] = LoadSound(filename0);
		g_BGMNo[1] = LoadSound(filename1);
		g_BGMNo[2] = LoadSound(filename2);
		g_BGMNo[3] = LoadSound(filename3);
		g_BGMNo[4] = LoadSound(filename4);
		g_BGMNo[5] = LoadSound(filename5);
		g_BGMNo[6] = LoadSound(filename6);
		g_BGMNo[7] = LoadSound(filename7);
		g_BGMNo[8] = LoadSound(filename8);
		g_BGMNo[9] = LoadSound(filename9);
		g_BGMNo[10]= LoadSound(filename10);
	}
	
	alpha = 1.0f;
	color = 1.0f;
	change = false;
	playFst = 0;
	
	octRot[0] = 1.0f;
	octRot[1] = 0.1f;
	HardCol[0] = 1.0f;
	HardCol[1] = 0.3f;

	ARROW_COL[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ARROW_COL[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	arrowSize[0] = 100.0f;
	arrowSize[1] = 100.0f;
	PLATE_COL	 = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ホワイト
	for (int w = 0; w < WHITE_MAX; w++)
	{
		g_White[w].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_White[w].spd = 5.0f;
		g_White[w].size= D3DXVECTOR2(50.0f, 50.0f);
		g_White[w].rot = 0.0f;
		g_White[w].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_White[w].use = false;
	}
	whiteCnt = 0;

	//音声ファイルを読み込んで識別子を受け取る
	//g_BGMNo = LoadSound((char*)"data/BGM/BGM_Title.wav");

	//BGMの再生（2つ目の引数はループ回数）
	//ループ回数に負の値を指定すると無限ループ
	PlaySound(g_BGMNo[NowSelect], -1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStageSelect(void)
{
	for (int i = 0; i < 11; i++)
	{
		StopSound(g_BGMNo[i]);
	}
	g_TextureArrow = NULL;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStageSelect(void)
{

	if ((g_StagePanel[0].moving ==false)&&(!playing))
	{
		playing = true;
		if ((playFst == 1)&&(NowSelect>0))
		{
			PlaySound(g_BGMNo[NowSelect+=5], -1);
			playFst++;
		}
		else
		{
			PlaySound(g_BGMNo[NowSelect], -1);
		}

	}

	if (((Keyboard_IsKeyDown(KK_W)) || (Keyboard_IsKeyDown(KK_S))) && (change == false))
	{
		change = true;
	}
	if (((GetThumbLeftY(0) < -0.3f)|| (GetThumbLeftY(0) > 0.3f)) && (change == false))
	{
		change = true;
	}

	//エンターキー、またはBボタンが押されたらSCENE_GAMEへ移行する
	if (Keyboard_IsKeyDown(KK_ENTER) || IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{


		if (NowSelect == 0)
		{
			SceneTransition(SCENE_TUTO);
		}

		else
		{
			SceneTransition(SCENE_SKILLSELECT);
		}
	}

	for (int i = 0; i < STAGE_MAX; i++)
	{
		//右に移動
		if (((Keyboard_IsKeyDown(KK_A)) || (GetThumbLeftX(0) < -0.3f)) && (g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//移動中
			g_StagePanel[i].NowLane++;
			g_StagePanel[i].spd = 60.0f;			//スピードを+に
			g_StagePanel[i].direction = D_RIGHT;		//右移動
			alpha = 1.0f;
			ARROW_COL[1] = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			arrowSize[1] = 110.0f;
		}
		//左に移動
		if (((Keyboard_IsKeyDown(KK_D)) || (GetThumbLeftX(0) > 0.3f)) && (g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//移動中
			g_StagePanel[i].NowLane--;
			g_StagePanel[i].spd = -60.0f;		//スピードを-に
			g_StagePanel[i].direction = D_LEFT;		//左移動
			alpha = 1.0f;
			ARROW_COL[0] = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
			arrowSize[0] = 110.0f;
		}


		//選択移動
		if ((g_StagePanel[i].moving))
		{
			for (int m = 0; m < 11; m++)
			{
				StopSound(g_BGMNo[m]);
			}
		
			alpha *= 0.99f;
			g_StagePanel[i].pos.x += g_StagePanel[i].spd;	//スピードを足して移動
			g_StagePanel[i].spd *= 0.9f;			//スピード減衰
			if (g_StagePanel[i].NowLane == PLANE_3)
			{
				g_StagePanel[i].size.x += 7.0f;
				g_StagePanel[i].size.y += 7.0f;
			}
			else
			{
				g_StagePanel[i].size.x = 300.0f;
				g_StagePanel[i].size.y = 300.0f;
			}
		}

		//右移動完了
		if ((g_StagePanel[i].spd <= 15.0f) && (g_StagePanel[i].direction == D_RIGHT) && (g_StagePanel[i].moving == true))
		{
			g_StagePanel[i].pos.x = -480.0f * 2 + g_StagePanel[i].NowLane * 480.0f;	//レーンの中心に
			g_StagePanel[i].moving = false;
			//NowSelect++;	//選択ステージ変更
			ARROW_COL[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			arrowSize[1] = 100.0f;
			playing = false;
		}
		//左移動完了
		if ((g_StagePanel[i].spd >= -15.0f) && (g_StagePanel[i].direction == D_LEFT) && (g_StagePanel[i].moving == true))
		{
			g_StagePanel[i].pos.x = -480.0f * 2 + g_StagePanel[i].NowLane * 480.0f;	//レーンの中心に
			g_StagePanel[i].moving = false;
			//NowSelect--;	//選択ステージ変更
			ARROW_COL[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			arrowSize[0] = 100.0f;
			playing = false;
		}

		if (g_StagePanel[i].NowLane == PLANE_3)
		{
			if (ura)
			{
				g_TextureBgStageSelect[1] = g_StagePanel[i].texnoB;
			}
			else
			{
				g_TextureBgStageSelect[1] = g_StagePanel[i].texnoA;
			}

			g_StagePanel[i].col = D3DXCOLOR(color, color, color, 1.0f);
			if (g_StagePanel[i].moving == false)
			{
				alpha = 1.0f;
				if (ura)
				{
					g_TextureBgStageSelect[0] = g_StagePanel[i].texnoB;
				}
				else
				{
					g_TextureBgStageSelect[0] = g_StagePanel[i].texnoA;
				}
			}
			NowSelect = i;
			if ((ura) && NowSelect > 0)
			{
				NowSelect += 5;
			}
			//g_TextureBgStageSelect[1] = g_StagePanel[i].texnoA;
		}
		else
		{
			g_StagePanel[i].col = D3DXCOLOR(color, color, color, 0.5f);
		}

		if (g_StagePanel[i].NowLane == PLANE_6)
		{
			g_StagePanel[i].NowLane = PLANE_0;
		}
		if (g_StagePanel[i].NowLane == PLANE_MIN)
		{
			g_StagePanel[i].NowLane = PLANE_5;
		}


		if (change)
		{
			for (int m = 0; m < 11; m++)
			{
				StopSound(g_BGMNo[m]);
			}

			octRot[1] = 1.0f;
			color *= 0.98f;
			if (color <= 0.01f)
			{
				if (ura)
				{
					ura = false;
					HardCol[0] = 1.0f;
					HardCol[1] = 0.3f;
				}
				else
				{
					ura = true;
					HardCol[0] = 0.3f;
					HardCol[1] = 1.0f;
				}
				change = false;
				playing = false;
				playFst++;
			}
		}
		else if (color < 1.0f)
		{
			color *= 1.02;
			octRot[1] = 0.05f;
			
		}

		octRot[0] += octRot[1];


		for (int w = 0; w < WHITE_MAX; w++)
		{
			g_White[w].pos.y -= g_White[w].spd;
			g_White[w].rot += 1.0f;
			if (g_White[w].pos.y <= SCREEN_HEIGHT*-1)
			{
				g_White[w].use = false;
			}
		}
		whiteCnt += 1;
		if (whiteCnt == 30)
		{
			SetWhite((frand() * (1920 / 4)) * 4, frand() * 5, frand() * 3);
		}
		if (whiteCnt == 60)
		{
			SetWhite((frand() * (1920 / 4)) * 1, frand() * 5, frand() * 3);
			whiteCnt = 0;
		}
		
		
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStageSelect(void)
{
	//背景表示
	DrawSpriteColor(g_TextureBgStageSelect[1], CENTER_X, CENTER_Y, SCREEN_WIDTH * 1.1, SCREEN_WIDTH * 1.1,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(color * 0.6f, color * 0.6f, color * 0.6f, 1.0f));
	DrawSpriteColor(g_TextureBgStageSelect[0], CENTER_X, CENTER_Y, SCREEN_WIDTH * 1.1, SCREEN_WIDTH * 1.1,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(color * 0.6f, color * 0.6f, color * 0.6f, alpha));

	//ネームプレート
	

	if (color >= 1.0f)
	{
		DrawSpriteColor(g_TextureNamePlate, CENTER_X, CENTER_Y + 250.0f, 500.0f, 100.0f,
			0.0f, (1.0f / 11) * NowSelect, 1.0f, (1.0f / 11), PLATE_COL);

		//矢印
		DrawSpriteColor(g_TextureArrow, CENTER_X - 300.0f, CENTER_Y + 250.0f, arrowSize[1], arrowSize[1],
			0.0f, 0.0f, 0.25f, 1.0f, ARROW_COL[1]);
		DrawSpriteColor(g_TextureArrow, CENTER_X + 300.0f, CENTER_Y + 250.0f, arrowSize[0], arrowSize[0],
			0.25f, 0.0f, 0.25f, 1.0f, ARROW_COL[0]);

		//難易度パネル
		DrawSpriteColor(g_TextureUIHard, CENTER_X - HARD_SIZE / 2, CENTER_Y - 350.0f - HardCol[0] * 10, HARD_SIZE, HARD_SIZE / 3,
			0.0f, 0.0f, 0.5f, 1.0f, D3DXCOLOR(HardCol[0], HardCol[0], HardCol[0], 1.0f));
		DrawSpriteColor(g_TextureUIHard, CENTER_X + HARD_SIZE / 2, CENTER_Y - 350.0f - HardCol[1] * 10, HARD_SIZE, HARD_SIZE / 3,
			0.5f, 0.0f, 0.5f, 1.0f, D3DXCOLOR(HardCol[1], HardCol[1], HardCol[1], 1.0f));
		DrawSpriteColor(g_TextureUIButton, CENTER_X, CENTER_Y - 350.0f, HARD_SIZE / 3, HARD_SIZE / 3,
			0.25 * 2, 0.0f, 0.25f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	}

	//ステージパネルの表示
	for (int i = 0; i < STAGE_MAX; i++)
	{
		//DrawSpriteLeftTop(g_StagePanel[i].texnoA, 0.0f, 0.0f, g_StagePanel[i].size.x, g_StagePanel[i].size.y,
		//	0.0f, 0.0f, 1.0f, 1.0);
		if (ura)
		{
			DrawSpriteColor(g_StagePanel[i].texnoB, g_StagePanel[i].pos.x, g_StagePanel[i].pos.y, g_StagePanel[i].size.x, g_StagePanel[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0, g_StagePanel[i].col);
		}
		else
		{
			DrawSpriteColor(g_StagePanel[i].texnoA, g_StagePanel[i].pos.x, g_StagePanel[i].pos.y, g_StagePanel[i].size.x, g_StagePanel[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0, g_StagePanel[i].col);
		}
	}


	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureOct));

	DrawSpriteColorRotation(
		CENTER_X,
		CENTER_Y,
		2200.0f,
		2200.0f,
		octRot[0],
		D3DXCOLOR(0.5f,0.8f,1.0f,0.1f),
		0.0f,
		1.0f,
		1.0f,
		1
	);

	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureOct));

	DrawSpriteColorRotation(
		CENTER_X,
		CENTER_Y,
		2200.0f,
		2200.0f,
		octRot[0] * -1,
		D3DXCOLOR(0.5f, 1.0f, 0.8f, 0.1f),
		0.0f,
		1.0f,
		1.0f,
		1
	);

	for (int i = 0; i < WHITE_MAX; i++)
	{
		if (g_White[i].use == true)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1,
				GetTexture(g_TextureWhite));

			DrawSpriteColorRotation(
				g_White[i].pos.x,
				g_White[i].pos.y,
				g_White[i].size.x,
				g_White[i].size.y,
				g_White[i].rot,
				g_White[i].col,
				0.0f,
				1.0f,
				1.0f,
				1
			);
		}
	}
}

int GetGemeStageNum(void)
{
	return NowSelect;
}

void SetWhite(int x,int sz,int rt)
{
	for (int i = 0; i < WHITE_MAX; i++)
	{
		if (g_White[i].use == false)
		{
			g_White[i].pos.x = x;
			g_White[i].pos.y = SCREEN_HEIGHT*1.1;
			g_White[i].size.x = sz * 8.0f;
			g_White[i].size.y = sz * 8.0f;
			g_White[i].rot = rt * 45.0f;
			g_White[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_White[i].use = true;
			return;
		}
	}
}
