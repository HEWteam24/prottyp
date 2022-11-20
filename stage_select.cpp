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

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************


static int g_TextureBgStageSelect[2];//タイトル画面用テクスチャの識別子
static int g_BGMNo;//タイトル用BGMの識別子
int NowSelect = STAGE_1;
float alpha;
STAGE_PANEL g_StagePanel[STAGE_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStageSelect(void)
{
	//テクスチャを読み込んで識別子を受け取る
	g_TextureBgStageSelect[0] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");
	g_TextureBgStageSelect[1] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");

	g_StagePanel[STAGE_0].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel0.png");
	g_StagePanel[STAGE_1].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel1_test.png");
	g_StagePanel[STAGE_2].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel2.png");
	g_StagePanel[STAGE_3].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel3.png");
	g_StagePanel[STAGE_4].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel4.png");
	g_StagePanel[STAGE_5].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel5.png");
	g_StagePanel[STAGE_6].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel6.png");
	g_StagePanel[STAGE_7].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel7.png");
	g_StagePanel[STAGE_8].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel8.png");
	g_StagePanel[STAGE_9].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel9.png");
	g_StagePanel[STAGE_10].texno= LoadTexture((char*)"data/TEXTURE/Stage_Panel10.png");

	//構造体の初期化
	for (int i = 0; i < STAGE_MAX; i++)
	{
		g_StagePanel[i].pos = D3DXVECTOR2(-480.0f*2+i*480.0f,CENTER_Y-50.0f);
		g_StagePanel[i].spd = 10.0f;
		g_StagePanel[i].size= D3DXVECTOR2(300.0f, 300.0f);
		g_StagePanel[i].col = D3DXCOLOR(1.0f, 1.0f,1.0f,1.0f);
		g_StagePanel[i].direction = D_RIGHT;
		g_StagePanel[i].moving = false;
		g_StagePanel[i].NowLane = i+3;
	}
	
	g_StagePanel[1].size = D3DXVECTOR2(395.0f, 395.0f);;
	g_StagePanel[10].NowLane =PLANE_1;

	alpha = 1.0f;

	//音声ファイルを読み込んで識別子を受け取る
	//g_BGMNo = LoadSound((char*)"data/BGM/BGM_Title.wav");

	//BGMの再生（2つ目の引数はループ回数）
	//ループ回数に負の値を指定すると無限ループ
	//PlaySound(g_BGMNo, -1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStageSelect(void)
{
	StopSound(g_BGMNo);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStageSelect(void)
{
	//エンターキーが押されたらSCENE_GAMEへ移行する
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		
		SceneTransition(SCENE_GAME);
		//SceneTransition(NowSelect+6);
	}
	//コントローラーBボタン押したらSCENE_GAMEへ移行
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		SceneTransition(SCENE_GAME);
		//SceneTransition(NowSelect+6);
	}
	for (int i = 0; i < STAGE_MAX; i++)
	{
		//スティックで移動
		if ((GetThumbLeftX(0) < -0.3f) &&(g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//移動中
			g_StagePanel[i].NowLane++;
			g_StagePanel[i].spd = 60.0f;			//スピードを+に
			g_StagePanel[i].direction = D_RIGHT;		//右移動
			alpha = 1.0f;
		}
		//左
		if ((GetThumbLeftX(0) > 0.3f) && (g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//移動中
			g_StagePanel[i].NowLane--;
			g_StagePanel[i].spd = -60.0f;		//スピードを-に
			g_StagePanel[i].direction = D_LEFT;		//左移動
			alpha = 1.0f;
		}

		//Dキーで右移動
		if ((Keyboard_IsKeyDown(KK_D)) && (g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//移動中
			g_StagePanel[i].NowLane--;
			g_StagePanel[i].spd = -60.0f;		//スピードを-に
			g_StagePanel[i].direction = D_LEFT;		//左移動
			alpha = 1.0f;
		}

		//Aキー で左移動
		if ((Keyboard_IsKeyDown(KK_A)) && (g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//移動中
			g_StagePanel[i].NowLane++;
			g_StagePanel[i].spd = 60.0f;			//スピードを+に
			g_StagePanel[i].direction = D_RIGHT;		//右移動
			alpha = 1.0f;
		}

		//選択移動
		if ((g_StagePanel[i].moving))
		{
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
		if ((g_StagePanel[i].spd <= 15.0f) && (g_StagePanel[i].direction == D_RIGHT))
		{
			g_StagePanel[i].pos.x = -480.0f*2 + g_StagePanel[i].NowLane * 480.0f;	//レーンの中心に
			g_StagePanel[i].moving = false;
			NowSelect++;	//選択ステージ変更
			
		}
		//左移動完了
		if ((g_StagePanel[i].spd >= -15.0f) && (g_StagePanel[i].direction == D_LEFT))
		{
			g_StagePanel[i].pos.x = -480.0f*2 + g_StagePanel[i].NowLane * 480.0f;	//レーンの中心に
			g_StagePanel[i].moving = false;
			NowSelect--;	//選択ステージ変更
		
		}

		if (g_StagePanel[i].NowLane == PLANE_3)
		{
			g_TextureBgStageSelect[1] = g_StagePanel[i].texno;
			g_StagePanel[i].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			if (g_StagePanel[i].moving == false)
			{
				alpha = 1.0f;
				g_TextureBgStageSelect[0] = g_StagePanel[i].texno;
			}

			//g_TextureBgStageSelect[1] = g_StagePanel[i].texno;
		}
		else
		{
			g_StagePanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}

		if (g_StagePanel[i].NowLane == PLANE_11)
		{
			g_StagePanel[i].NowLane = PLANE_0;
		}
		if (g_StagePanel[i].NowLane == PLANE_MIN)
		{
			g_StagePanel[i].NowLane = PLANE_10;
		}


	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStageSelect(void)
{
	//背景表示
	DrawSpriteColor(g_TextureBgStageSelect[1], CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_WIDTH,
		0.0f, 0.0f, 1.0f, 1.0f,D3DXCOLOR(0.6f,0.6f,0.6f,1.0f));
	DrawSpriteColor(g_TextureBgStageSelect[0], CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_WIDTH,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.6f, 0.6f, 0.6f, alpha));


	//ステージパネルの表示
	for (int i = 0; i < STAGE_MAX; i++)
	{
		//DrawSpriteLeftTop(g_StagePanel[i].texno, 0.0f, 0.0f, g_StagePanel[i].size.x, g_StagePanel[i].size.y,
		//	0.0f, 0.0f, 1.0f, 1.0);
		
		DrawSpriteColor(g_StagePanel[i].texno, g_StagePanel[i].pos.x, g_StagePanel[i].pos.y, g_StagePanel[i].size.x, g_StagePanel[i].size.y,
			0.0f, 0.0f, 1.0f, 1.0, g_StagePanel[i].col);
	}
}
