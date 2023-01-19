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

#define RING_SIZE  (340.0f)
#define ICON_SIZE  (300.0f)
#define ICON_ZOOM  (1.16f)
#define ICON_SPACE (320.0f)
#define ICON_POS_Y (CENTER_Y-120.0f)
#define PLATE_SIZE (260.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************


static int g_TextureBgStageSelect;//背景用テクスチャの識別子
static int g_TextureRing;
static int g_TextureSkillPlate;
static int g_TextureTextArrow;
static int g_BGMNo;//BGMの識別子

int NowSSelect = SKILL_1;

float RingRot;	//リング角度
float RingPosY;	//リング位置
float TextPosX; //説明文位置
float TextAlpha;

int changeN;	//移動猶予
bool movingSp;	//移動フラグ

SKILL_PANEL g_SkillPanel[SKILL_MAX];

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSkillSelect(void)
{
	//テクスチャを読み込んで識別子を受け取る
	g_TextureBgStageSelect = LoadTexture((char*)"data/TEXTURE/fade_white.png");

	g_SkillPanel[SKILL_0].texno = LoadTexture((char*)"data/TEXTURE/icon_heal.png");
	g_SkillPanel[SKILL_1].texno = LoadTexture((char*)"data/TEXTURE/icon_damage.png");
	g_SkillPanel[SKILL_2].texno = LoadTexture((char*)"data/TEXTURE/icon_protect.png");

	g_TextureSkillPlate = LoadTexture((char*)"data/TEXTURE/skill_plate.png");
	g_TextureTextArrow = LoadTexture((char*)"data/TEXTURE/arrow.png");

	g_TextureRing = LoadTexture((char*)"data/TEXTURE/icon_ring.png");

	//構造体の初期化
	for (int i = 0; i < SKILL_MAX; i++)
	{
		g_SkillPanel[i].pos = D3DXVECTOR2(CENTER_X*2.25, (CENTER_Y - ICON_SPACE) + i * ICON_SPACE);
		g_SkillPanel[i].size = D3DXVECTOR2(ICON_SIZE, ICON_SIZE);
		g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SkillPanel[i].moving = false;
	}

	changeN = 60;

	RingRot = 0.0f;
	RingPosY = 0.0f;
	TextPosX = CENTER_X * 1.3;
	TextAlpha = 0.0f;

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
	//StopSound(g_BGMNo);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSkillSelect(void)
{
	SPECIAL* pSp = GetSpecial();

	//SCENE_GAMEへ
	//エンターキー
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		pSp->type = NowSSelect;
		//SceneTransition(SCENE_GAME);
	}
	//コントローラーBボタン
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		pSp->type = NowSSelect;
		//SceneTransition(SCENE_GAME);
	}
	
	for (int i = 0; i < SKILL_MAX; i++)
	{
		if (g_SkillPanel[i].pos.x > CENTER_X*1.75)
		{
			g_SkillPanel[i].pos.x -= 50.0f;
		}

	//下側に選択移動
		if (((GetThumbLeftY(0) < -0.3f)||(Keyboard_IsKeyDown(KK_S))) && (movingSp == false) && (NowSSelect < 2))
		{
			NowSSelect+=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
			TextAlpha = 0.0f;
			TextPosX = CENTER_X * 1.5;
		}
	//上側に選択移動
		if (((GetThumbLeftY(0) > 0.3f) || (Keyboard_IsKeyDown(KK_W))) && (movingSp == false) && (NowSSelect > 0))
		{
			NowSSelect-=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
			TextAlpha = 0.0f;
			TextPosX = CENTER_X * 1.5;
		}
		
	//選択されてたら拡大 & されてなかったら縮小
		if (i == NowSSelect)
		{
			g_SkillPanel[i].size = D3DXVECTOR2(ICON_SIZE * ICON_ZOOM, ICON_SIZE * ICON_ZOOM);
			g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			g_SkillPanel[i].size = D3DXVECTOR2(ICON_SIZE,ICON_SIZE);
			g_SkillPanel[i].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.6f);
		}	

	//選択移動猶予
		if (movingSp==true)
		{
			changeN -= 1;
			if (changeN <= 0)
			{
				changeN = 30;
				movingSp = false;
			}
		}

	//説明文のフェード
		if (TextAlpha < 1.0f)
		{
			TextAlpha += 0.025f;
		}
		if (TextPosX > CENTER_X*1.35)
		{
			TextPosX -= 15.0f;
		}

	}

	//セレクト超過を抑える
	if (NowSSelect >= 3)
	{
		NowSSelect = 0;
	}
	if (NowSSelect <= -1)
	{
		NowSSelect = 2;
	}

	//リングの処理
	RingRot += 0.5f;
	RingPosY = (CENTER_Y - ICON_SPACE) + NowSSelect * ICON_SPACE;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSkillSelect(void)
{
	////背景表示
	//DrawSpriteColor(g_TextureBgStageSelect, CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_WIDTH,
	//	0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));

	//説明
	DrawSpriteColor(g_TextureSkillPlate,TextPosX, RingPosY, PLATE_SIZE * 2, PLATE_SIZE,
		0.0f, 1.0f / 3 * NowSSelect - 1, 1.0f, 1.0 / 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, TextAlpha));

	if (NowSSelect < 2)
	{
		DrawSpriteColor(g_TextureTextArrow, TextPosX, RingPosY + (PLATE_SIZE / 2) + 30.0f, 80.0f, 80.0f,
			0.25f * 3, 0.0f, 0.25f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, TextAlpha));
	}
	if (NowSSelect > 0)
	{
		DrawSpriteColor(g_TextureTextArrow, TextPosX, RingPosY - (PLATE_SIZE / 2) - 30.0f, 80.0f, 80.0f,
			0.25f * 2, 0.0f, 0.25f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, TextAlpha));
	}



	//スキルアイコンの表示
	for (int i = 0; i < SKILL_MAX; i++)
	{
			DrawSpriteColor(g_SkillPanel[i].texno, g_SkillPanel[i].pos.x, g_SkillPanel[i].pos.y, g_SkillPanel[i].size.x, g_SkillPanel[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0f, g_SkillPanel[i].col);
	}


	//リング
	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRing));
	DrawSpriteColorRotation(
		g_SkillPanel[0].pos.x,
		RingPosY,
		RING_SIZE,
		RING_SIZE,
		RingRot,
		D3DXCOLOR(0.0f, 0.8f, 0.6f, 1.0f),
		0.0f,
		1.0f,
		1.0f,
		1
	);

	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRing));
	DrawSpriteColorRotation(
		g_SkillPanel[0].pos.x,
		RingPosY,
		RING_SIZE*1.15,
		RING_SIZE*1.15,
		RingRot*-1.5,
		D3DXCOLOR(0.0f, 1.0f, 0.8f, 1.0f),
		0.0f,
		1.0f,
		1.0f,
		1
	);


}
