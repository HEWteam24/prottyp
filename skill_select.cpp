/*==============================================================================

   タイトル画面処理 [StageSelect.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "skill_select.h"
#include "special.h"
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
int NowSSelect = SKILL_1;
float Salpha;
float Scolor;
int changeN;
bool movingSp;
SKILL_PANEL g_SkillPanel[SKILL_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSkillSelect(void)
{
	//テクスチャを読み込んで識別子を受け取る
	g_TextureBgStageSelect[0] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");
	g_TextureBgStageSelect[1] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");

	g_SkillPanel[SKILL_0].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel0.png");
	g_SkillPanel[SKILL_1].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel1.png");
	g_SkillPanel[SKILL_2].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel2.png");
	//g_SkillPanel[STAGE_6].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel6.png");
	//g_SkillPanel[STAGE_7].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel7.png");
	//g_SkillPanel[STAGE_8].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel8.png");
	//g_SkillPanel[STAGE_9].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel9.png");
	//g_SkillPanel[STAGE_10].texno= LoadTexture((char*)"data/TEXTURE/Stage_Panel10.png");

	//構造体の初期化
	for (int i = 0; i < SKILL_MAX; i++)
	{
		g_SkillPanel[i].pos = D3DXVECTOR2((CENTER_X-480.0f)+i*480.f, CENTER_Y - 50.0f);
		g_SkillPanel[i].spd = 10.0f;
		g_SkillPanel[i].size = D3DXVECTOR2(300.0f, 300.0f);
		g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SkillPanel[i].direction = SD_RIGHT;
		g_SkillPanel[i].moving = false;
	}

	g_SkillPanel[1].size = D3DXVECTOR2(395.0f, 395.0f);;

	Salpha = 1.0f;
	Scolor = 1.0f;
	changeN = 60;

	NowSSelect = 1;
	movingSp = false;
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
void UninitSkillSelect(void)
{
	StopSound(g_BGMNo);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSkillSelect(void)
{
	SPECIAL* pSp = GetSpecial();

	//エンターキーが押されたらSCENE_GAMEへ移行する
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		pSp->type = NowSSelect;
		SceneTransition(SCENE_GAME);
		//SceneTransition(NowSSelect+6);
	}
	//コントローラーBボタン押したらSCENE_GAMEへ移行
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		SceneTransition(SCENE_GAME);
		//SceneTransition(NowSSelect+6);
	}
	for (int i = 0; i < SKILL_MAX; i++)
	{
		if ((Keyboard_IsKeyDown(KK_D)) && (movingSp == false) && (NowSSelect < 2))
		{
			NowSSelect+=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
		}
		if ((Keyboard_IsKeyDown(KK_A)) && (movingSp == false) && (NowSSelect > 0))
		{
			NowSSelect-=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
		}
		
		if (i == NowSSelect)
		{
			g_SkillPanel[i].size = D3DXVECTOR2(395.0f,395.0f);
			g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			g_SkillPanel[i].size = D3DXVECTOR2(340.0f, 340.0f);
			g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		}	

		if (movingSp==true)
		{
			changeN -= 1;
			if (changeN <= 0)
			{
				changeN = 30;
				//g_SkillPanel[i].moving = false;
				movingSp = false;
			}
		}
	}

	if (NowSSelect >= 3)
	{
		NowSSelect = 0;
	}
	if (NowSSelect <= -1)
	{
		NowSSelect = 2;
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSkillSelect(void)
{
	//背景表示
	DrawSpriteColor(g_TextureBgStageSelect[1], CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_WIDTH,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
	DrawSpriteColor(g_TextureBgStageSelect[0], CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_WIDTH,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.6f, 0.6f, 0.6f, Salpha));


	//ステージパネルの表示
	for (int i = 0; i < SKILL_MAX; i++)
	{
		//DrawSpriteLeftTop(g_SkillPanel[i].texno, 0.0f, 0.0f, g_SkillPanel[i].size.x, g_SkillPanel[i].size.y,
		//	0.0f, 0.0f, 1.0f, 1.0);

			DrawSpriteColor(g_SkillPanel[i].texno, g_SkillPanel[i].pos.x, g_SkillPanel[i].pos.y, g_SkillPanel[i].size.x, g_SkillPanel[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0, g_SkillPanel[i].col);
	}
}
