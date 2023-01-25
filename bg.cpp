/*==============================================================================
	
	bg.cpp

--------------------------------------------------------------------------------

==============================================================================*/
#include "bg.h"
#include "texture.h"
#include "sprite.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_VERTEX 4	//必要な頂点の数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureBg;	//背景テクスチャ
static int g_TextureUIBack;
static int g_TextureUICtrl;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBG(int StageNum)
{
	ID3D11Device *pDevice = GetDevice();

	g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
	g_TextureUIBack = LoadTexture((char*)"data/TEXTURE/UI_Back_B.png");
	g_TextureUICtrl = LoadTexture((char*)"data/TEXTURE/UI_ctrl.png");
	
	switch (StageNum)
	{
	default:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
		break;

	case 0:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/Bg_Tuto.png");
		break;
	case 1:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_SeaCity.png");
		break;
	case 2:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
		break;
	case 3:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_SeaRock.png");
		break;
	case 4:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_Bubbles.png");
		break;
	case 5:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
		break;
	case 6:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
		break;
	case 7:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_SeaCity.png");
		break;
	case 8:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_SeaRock.png");
		break;
	case 9:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_Bubbles.png");
		break;
	case 10:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_Space.png");
		break;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBG(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBG(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBG(void)
{

	DrawSprite(g_TextureBg, SCREEN_WIDTH/2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteColor(g_TextureUIBack, 0.0f+200.0f, CENTER_Y, 400.0f, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 0.4));

	DrawSpriteColor(g_TextureUIBack, SCREEN_WIDTH-200.0f, CENTER_Y, 400.0f, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 0.4));

	DrawSpriteColor(g_TextureUICtrl, 0.0f+250.0f, CENTER_Y-250.0f, 500.0f*0.9f, 350.0f*0.9f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));

}
