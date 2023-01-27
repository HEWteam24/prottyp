/*==============================================================================

   タイトル画面処理 [Result.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Result.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
//#include "input.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"
#include "score.h"
#include "combo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int g_TextureBand;//タイトル画面用テクスチャの識別子
static int g_TextureBgResult;
static int g_TextureShishamo;
static int g_TextureClear;
static int g_TextureRankCoin;
static int g_TextureReButton;
static int g_SE_CLEAR;//タイトル用BGMの識別子
static int g_SE_FAILED;

D3DXCOLOR g_BandCol;
PLAYER* pPlayerOne = GetPlayer();
SCORE* pScore = GetScore();

COIN g_Coin;

float	Shishamo_pos;
float	Shishamo_spd;
float	ReButton_size;
float	ReButton_add;
int Addcol;
int ResultFrame;

bool	moving;

int		EnemyScore;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitResult(int stagenum,int enemynum,int texnums)
{
	float criteria = 1.0f + (((float)stagenum / 10) * 2);

	EnemyScore = enemynum;
	g_Coin.col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	g_BandCol  = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	g_Coin.TextCol = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
	g_Coin.rad = 0.0f;
	g_Coin.u = 0.0f;
	g_Coin.u = 0.0f;

	g_TextureRankCoin= LoadTexture((char*)"data/TEXTURE/rank_coins_1200x200_B.png");
	g_TextureClear = LoadTexture((char*)"data/TEXTURE/text_clear.png");

	g_TextureBand	  = LoadTexture((char*)"data/TEXTURE/UI_Result_Band.png");
	g_TextureShishamo = LoadTexture((char*)"data/TEXTURE/Shishamo_end_1.png");
	g_TextureReButton = LoadTexture((char*)"data/TEXTURE/UI_Buttons_B.png");

	char	file_SE_CLEAR[]  = "data\\SE\\SE_RESULT_CLEAR.wav";
	char	file_SE_FAILED[] = "data\\SE\\SE_RESULT_FAILED.wav";
	g_SE_CLEAR  = LoadSound(file_SE_CLEAR);
	g_SE_FAILED = LoadSound(file_SE_FAILED);

	if (pScore->ToResult >= 0)
	{
		g_Coin.rank = 5;
		g_BandCol	= D3DXCOLOR(0.5f, 0.2f, 0.5f, 1.0f);
	}
	if (pScore->ToResult >= 4000 * criteria)
	{
		g_Coin.rank = 4;
		g_BandCol = D3DXCOLOR(0.6f, 0.6f, 0.7f, 1.0f);
	}
	if (pScore->ToResult >= 8000 * criteria)
	{
		g_Coin.rank = 3;
		g_BandCol = D3DXCOLOR(0.9f, 0.3f, 0.1f, 1.0f);
	}
	if (pScore->ToResult >= 17000 * criteria)
	{
		g_Coin.rank = 2;
		g_BandCol = D3DXCOLOR(0.9f, 0.9f, 0.95f, 1.0f);
	}
	if (pScore->ToResult >= 27000 * criteria)
	{
		g_Coin.rank = 1;
		g_BandCol = D3DXCOLOR(0.9f, 0.8f, 0.3f, 1.0f);
	}
	if (pScore->ToResult >= 38000 * criteria)
	{
		g_Coin.rank = 0;
		g_BandCol = D3DXCOLOR(0.7f, 0.7f, 1.0f, 1.0f);
	}

	//死亡時
	if (pPlayerOne->dead)
	{
		g_TextureClear = LoadTexture((char*)"data/TEXTURE/text_failed.png");
		g_Coin.TextCol = D3DXCOLOR(0.8f, 0.5f, 1.0f, 1.0f);
		g_Coin.rank	   = 5;
		g_BandCol	   = D3DXCOLOR(0.5f, 0.2f, 0.5f, 1.0f);
		PlaySound(g_SE_FAILED, 0);
	}
	else
	{
		PlaySound(g_SE_CLEAR, 0);
	}

	g_Coin.alpha = 0.3f;
	g_Coin.size = D3DXVECTOR2(300.0f, 300.0f);
	g_Coin.roted = false;

	InitScoreResult(texnums, enemynum);

	Shishamo_pos = -450.0f;
	Shishamo_spd = 85.0f;
	ReButton_size = 200.0f;
	ReButton_add  = 1.0f;
	Addcol = 0;
	ResultFrame = 0;
	moving = true;

	switch (stagenum)
	{
	default:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel0.png");
		break;

	case 0:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel0.png");
		break;
	case 1:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel1.png");
		break;
	case 2:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel2.png");
		break;
	case 3:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel3.png");
		break;
	case 4:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel4.png");
		break;
	case 5:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel5.png");
		break;
	case 6:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel6.png");
		break;
	case 7:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel7.png");
		break;
	case 8:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel8.png");
		break;
	case 9:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel9.png");
		break;
	case 10:
		g_TextureBgResult = LoadTexture((char*)"data/TEXTURE/Stage_Panel10.png");
		break;
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitResult(void)
{
	UninitPlayer();
	UninitScore();
	UninitCombo();
	StopSound(g_SE_CLEAR);
	StopSound(g_SE_FAILED);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateResult(void)
{
	ResultFrame++;

	//エンターキーが押されたらSCENE_TITLEへ移行する
	if ((Keyboard_IsKeyDown(KK_ENTER))&&(ResultFrame>=150))
	{
		SceneTransition(SCENE_STAGESELECT);
	}
	//コントローラーBボタン押したらSCENE_TITLEへ移行
	if ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) && (ResultFrame >= 150))
	{
		SceneTransition(SCENE_STAGESELECT);
	}

	//ししゃも移動
	if (moving)
	{
		Shishamo_pos += Shishamo_spd;	//スピードを足して移動
		Shishamo_spd *= 0.9f;			//スピード減衰
	}
	//移動完了
	if (Shishamo_spd <= 1.0f)
	{
		moving = false;
	}

	if (Addcol < 100)
	{
		Addcol++;
	}
	if (g_Coin.rad<=360*2-10)
	{
		g_Coin.rad+=10.0f;
	}
	else
	{
		g_Coin.roted = true;
	}

	g_Coin.col = D3DXCOLOR(0.0f + Addcol * 0.01f,
		0.0f + Addcol * 0.01f,
		0.0f + Addcol * 0.01f,
		1.0f);

	g_Coin.size.x += 8.0f;
	g_Coin.size.y += 8.0f;
	g_Coin.alpha -= 0.02f;

	if (g_Coin.alpha <= 0.0f)
	{
		g_Coin.size.x = 300.0f;
		g_Coin.size.y = 300.0f;
		g_Coin.alpha = 0.3f;
	}

	ReButton_size += ReButton_add;
	if ((ReButton_size >= 210.0f) || (ReButton_size <= 190.0f))
	{
		ReButton_add *= -1;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawResult(void)
{
	//背景
	DrawSpriteColor(g_TextureBgResult, CENTER_X, CENTER_Y, SCREEN_WIDTH*1.1f, SCREEN_WIDTH*1.1f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	//リザルト
	DrawSpriteColor(g_TextureBand, CENTER_X, CENTER_Y-30.0f, SCREEN_WIDTH, 600.0f,
		0.0f, 0.0f, 1.0f, 1.0f,g_BandCol);
	//シシャモ
	DrawSpriteColor(g_TextureShishamo, Shishamo_pos, CENTER_Y, 800.0f, 800.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	DrawSpriteColor(g_TextureClear, CENTER_X, CENTER_Y - 300.0f+50.0f, 600.0f, 100.0f,
		0.0f, 0.0f, 1.0f, 1.0f, g_Coin.TextCol);


	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRankCoin));

	DrawSpriteColorRotation(
		CENTER_X,
		CENTER_Y+25.0f,
		300.0f,
		300.0f,
		g_Coin.rad,
		g_Coin.col,
		g_Coin.rank,
		0.16665f,
		1.0f,
		6
	);

	if (g_Coin.roted)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1,
			GetTexture(g_TextureRankCoin));
		DrawSpriteColorRotation(
			CENTER_X,
			CENTER_Y+25.0f,
			g_Coin.size.x,
			g_Coin.size.y,
			g_Coin.rad,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Coin.alpha),
			g_Coin.rank,
			0.16665f,
			1.0f,
			6
		);

	}

	if (ResultFrame >= 150)
	{
		DrawSpriteColor(g_TextureReButton, 1700.0f, 950.0f, ReButton_size, ReButton_size,
			0.167f * 2.0f, 0.249f, 0.167f, 0.249f, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	}

	DrawScore();
	DrawEnemyScore();
	DrawMaxCombo();
}
