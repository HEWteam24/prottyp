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

#include "effect.h"

#include "pause.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTO_TEXT_SIZE_X (600.0f)
#define TEXT_CAN_PUSH	 (80)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//static int g_BGMTuto;
static int g_TextureCircle;
static int g_TextureText;
static int g_TextureTutoButton;
static int g_TextureTutoArrow;
static int g_SE_Tuto;
int	TutoFrame;
int ArroFrame;
bool TutoNext;
bool Tutostart;
bool B_Pushed;
T_CIRCLE g_Tuto;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTuto(int StageNum)
{
	InitPlayer();
	InitBullet();
	InitScore();
	InitCombo();

	InitSpecial();
	InitEnemy(StageNum);
	InitEnemyBullet(StageNum);
	InitRhythm(StageNum);
	InitEffect();
	// 背景の初期化
	InitBG(StageNum);
	InitLane();

	g_TextureCircle		= LoadTexture((char*)"data/TEXTURE/Tuto.png");
	g_TextureText		= LoadTexture((char*)"data/TEXTURE/UI_TutoText.png");
	g_TextureTutoArrow	= LoadTexture((char*)"data/TEXTURE/UI_TutoArrow.png");
	g_TextureTutoButton	= LoadTexture((char*)"data/TEXTURE/UI_Buttons.png");
	g_Tuto.col			= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	g_Tuto.pos			= D3DXVECTOR2(CENTER_X, CENTER_Y);
	g_Tuto.size			= D3DXVECTOR2(CENTER_X*4, CENTER_Y*4);
	g_Tuto.Tuv			= D3DXVECTOR2(0.0f, 0.0f);
	g_Tuto.ArPos		= D3DXVECTOR2(-100.0f, -100.0f);
	g_Tuto.ArSpd		= D3DXVECTOR2(2.5f, 2.5f);
	g_Tuto.ArRot		= 0.0f;
	g_Tuto.ButtonSize	= 80.0f;
	g_Tuto.ButtonAdd	= 0.5f;
	g_Tuto.Phase		= 0;
	g_Tuto.use			= false;

	char	file_SE_Tuto[] = "data\\SE\\SE_MenuPush.wav";
	g_SE_Tuto = LoadSound(file_SE_Tuto);

	TutoFrame = 0;
	ArroFrame = 0;
	TutoNext  = false;
	B_Pushed  = false;
	//*****************************************************************************************************************
	//  ゲーム開始カウント
	//	true  = あり
	//	false = なし

	Tutostart = true;
	//*****************************************************************************************************************

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
	UninitSpecial();
	UninitEffect();

	TutoFrame = 0;
	//StopSound(g_BGM);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTuto(void)
{
	PAUSE*		pPause = GetPause();
	PLAYER*		pPlayer = GetPlayer();
	SPECIAL*	pSkill = GetSpecial();

	//エンターキーが押されたらSCENE_GAMEへ移行する
	if (Keyboard_IsKeyDown(KK_G))
	{
		SceneTransition(SCENE_TITLE);
	}
	if (!MusicEnd() && (!g_Tuto.use)) {
		UpdateRhythm();

		if ((GetFreame() > 120)) {



			if (Tutostart)
			{
				PauseSound(BGM_RE());
				pPause->pause = true;
				pPause->restart = true;
				pPause->pause_frame = 0;
				pPause->alpha = 0.2f;
			}
			else {
				TutoFrame++;

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
			if (Tutostart)
			{
				Tutostart = false;
			}






		}

	}
	else {
		//StopSoundAll();
		if (!g_Tuto.use)
		{
			SceneTransition(SCENE_RESULT);
		}
	}

	if (!pPause->restart)
	{
		pPause->alpha = 0.7f;
	}

	UpdateEffect();


	if (g_Tuto.use)
	{
		PauseSound(BGM_RE());

		if (Keyboard_IsKeyDown(KK_N))
		{
			g_Tuto.use = false;
			RePlaySound(BGM_RE());
		}
	}

	if (TutoFrame <= 1597)
	{
		pSkill->charge = 0;
	}
	if (TutoFrame == 1598)
	{
		pSkill->charge = 30;
	}

	if (pPlayer->hp <=40)
	{
		pPlayer->hp = 40;
	}


	//ようこそ
	if ((TutoFrame==110)&&(g_Tuto.Phase == 0))
	{
		SetCircle(D3DXVECTOR2(1920.0f * 3.0f, 1920.0f * 3.0f), D3DXVECTOR2(CENTER_X*2.5f, CENTER_Y*2.5f), D3DXVECTOR2(0.0f, 0.0f));
		g_Tuto.Phase = 1;
		g_Tuto.TextFrame = 0;
	}
	//移動
	if ((TutoFrame == 780) && (g_Tuto.Phase == 7))
	{
		SetCircle(D3DXVECTOR2(1920.0f * 0.7f, 1920.0f * 0.7f), D3DXVECTOR2(CENTER_X, CENTER_Y * 0.9f), D3DXVECTOR2(0.0f, 2.0f));
		SetArrow(D3DXVECTOR2(CENTER_X, CENTER_Y + 100.0f), 90.0f);
		g_Tuto.Phase = 8;
		g_Tuto.TextFrame = 0;
	}
	//スキル
	if ((TutoFrame == 1600) && (g_Tuto.Phase == 12))
	{
		SetCircle(D3DXVECTOR2(1920.0f * 3.0f, 1920.0f * 3.0f), D3DXVECTOR2(CENTER_X*2.5f, CENTER_Y * 2.5f), D3DXVECTOR2(0.0f, 3.0f));
		g_Tuto.Phase = 13;
		g_Tuto.TextFrame = 0;
	}
	//スコア
	if ((TutoFrame == 2800) && (g_Tuto.Phase == 17))
	{
		SetCircle(D3DXVECTOR2(1920.0f * 1.5f, 1920.0f * 0.6f), D3DXVECTOR2(1860.0f-135.0f, SCORE_POS_Y), D3DXVECTOR2(0.0f, 4.0f));
		SetArrow(D3DXVECTOR2(1860.0f - 135.0f, SCORE_POS_Y+150.0f), 90.0f);
		g_Tuto.Phase = 18;
		g_Tuto.TextFrame = 0;
	}

	if ((TutoFrame == 4800) && (g_Tuto.Phase == 22))
	{
		SceneTransition(SCENE_RESULT);
	}

	if (g_Tuto.use)
	{
		g_Tuto.TextFrame++;
		if (g_Tuto.TextFrame >= TEXT_CAN_PUSH)
		{
			//ようこそ
			if ((g_Tuto.Phase == 1) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 3.0f, 1920.0f * 3.0f), D3DXVECTOR2(CENTER_X * 2.5f, CENTER_Y * 2.5f), D3DXVECTOR2(1.0f, 0.0f));
				g_Tuto.Phase = 2;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}

			//紹介
			if ((g_Tuto.Phase == 2) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 3.0f, 1920.0f * 3.0f), D3DXVECTOR2(CENTER_X * 2.5f, CENTER_Y * 2.5f), D3DXVECTOR2(0.0f, 1.0f));
				g_Tuto.Phase = 3;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//攻撃1
			if ((g_Tuto.Phase == 3) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 1.5f, 1920.0f * 0.6f), D3DXVECTOR2(CENTER_X, CENTER_Y * 1.8f), D3DXVECTOR2(1.0f, 1.0f));
				SetArrow(D3DXVECTOR2(CENTER_X, CENTER_Y + 300.0f), -90.0f);
				g_Tuto.Phase = 4;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//攻撃2
			if ((g_Tuto.Phase == 4) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 1.5f, 1920.0f * 0.6f), D3DXVECTOR2(CENTER_X, CENTER_Y * 1.8f), D3DXVECTOR2(2.0f, 1.0f));
				g_Tuto.Phase = 5;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//攻撃3
			if ((g_Tuto.Phase == 5) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetArrow(D3DXVECTOR2(-100.0f, -100.0f), -90.0f);
				SetCircle(D3DXVECTOR2(1920.0f * 3.0f, 1920.0f * 3.0f), D3DXVECTOR2(CENTER_X * 2.5f, CENTER_Y * 2.5f), D3DXVECTOR2(3.0f, 1.0f));
				g_Tuto.Phase= 6;
				B_Pushed	= true;
				TutoNext	= true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//攻撃4
			if ((g_Tuto.Phase == 6) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				//SetCircle(D3DXVECTOR2(1920.0f * 1.5f, 1920.0f * 1.5f), D3DXVECTOR2(CENTER_X, CENTER_Y), D3DXVECTOR2(4.0f, 1.0f));
				g_Tuto.Phase= 7;
				B_Pushed	= true;
				g_Tuto.use	= false;
				TutoNext	= false;
				RePlaySound(BGM_RE());
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}

			//移動1
			if ((g_Tuto.Phase == 8) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 1.5f, 1920.0f * 0.6f), D3DXVECTOR2(CENTER_X, CENTER_Y * 1.8f), D3DXVECTOR2(1.0f, 2.0f));
				SetArrow(D3DXVECTOR2(CENTER_X, CENTER_Y + 300.0f), -90.0f);
				g_Tuto.Phase = 9;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//移動2
			if ((g_Tuto.Phase == 9) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 3.0f, 1920.0f * 3.0f), D3DXVECTOR2(CENTER_X * 2.5f, CENTER_Y * 2.5f), D3DXVECTOR2(2.0f, 2.0f));
				SetArrow(D3DXVECTOR2(-100.0f, -100.0f), -90.0f);
				g_Tuto.Phase = 10;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//移動3
			if ((g_Tuto.Phase == 10) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 3.0f, 1920.0f * 3.0f), D3DXVECTOR2(CENTER_X * 2.5f, CENTER_Y * 2.5f), D3DXVECTOR2(3.0f, 2.0f));
				g_Tuto.Phase = 11;
				B_Pushed = true;
				TutoNext = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//移動4
			if ((g_Tuto.Phase == 11) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				//SetCircle(D3DXVECTOR2(1920.0f * 1.5f, 1920.0f * 1.5f), D3DXVECTOR2(CENTER_X, CENTER_Y), D3DXVECTOR2(3.0f, 2.0f));
				g_Tuto.Phase = 12;
				B_Pushed = true;
				TutoNext = false;
				g_Tuto.use = false;
				RePlaySound(BGM_RE());
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}

			//スキル1
			if ((g_Tuto.Phase == 13) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 1.25f, 1920.0f * 1.25f), D3DXVECTOR2(SKILL_ICON_POS_X, SKILL_ICON_POS_Y), D3DXVECTOR2(1.0f, 3.0f));
				SetArrow(D3DXVECTOR2(SKILL_ICON_POS_X, SKILL_ICON_POS_Y - 200.0f), -90.0f);
				g_Tuto.Phase = 14;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//スキル2
			if ((g_Tuto.Phase == 14) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 1.25f, 1920.0f * 1.25f), D3DXVECTOR2(SKILL_ICON_POS_X, SKILL_ICON_POS_Y), D3DXVECTOR2(2.0f, 3.0f));
				g_Tuto.Phase = 15;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//スキル3
			if ((g_Tuto.Phase == 15) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 1.25f, 1920.0f * 1.25f), D3DXVECTOR2(SKILL_ICON_POS_X, SKILL_ICON_POS_Y), D3DXVECTOR2(3.0f, 3.0f));
				g_Tuto.Phase = 16;
				B_Pushed = true;
				TutoNext = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
			//スキル4
			if ((g_Tuto.Phase == 16) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				//SetCircle(D3DXVECTOR2(1920.0f * 1.25f, 1920.0f * 1.25f), D3DXVECTOR2(SKILL_ICON_POS_X, SKILL_ICON_POS_Y), D3DXVECTOR2(2.0f, 3.0f));
				SetArrow(D3DXVECTOR2(-100.0f, -100.0f), -90.0f);
				g_Tuto.Phase = 17;
				B_Pushed = true;
				g_Tuto.use = false;
				TutoNext = false;
				RePlaySound(BGM_RE());
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}

			//スコア1
			if ((g_Tuto.Phase == 18) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 1.5f, 1920.0f * 0.6f), D3DXVECTOR2(1860.0f - 135.0f, SCORE_POS_Y), D3DXVECTOR2(1.0f, 4.0f));
				g_Tuto.Phase = 19;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}

			//スコア2
			if ((g_Tuto.Phase == 19) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 2.0f, 1920.0f * 1.75f), D3DXVECTOR2(CENTER_X, CENTER_Y), D3DXVECTOR2(2.0f, 4.0f));
				SetArrow(D3DXVECTOR2(CENTER_X, CENTER_Y + 300.0f), 90.0f);
				g_Tuto.Phase = 20;
				B_Pushed = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}

			//スコア3
			if ((g_Tuto.Phase == 20) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				SetCircle(D3DXVECTOR2(1920.0f * 2.0f, 1920.0f * 1.75f), D3DXVECTOR2(CENTER_X, CENTER_Y), D3DXVECTOR2(3.0f, 4.0f));
				g_Tuto.Phase = 21;
				B_Pushed = true;
				TutoNext = true;
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}

			//スコア4
			if ((g_Tuto.Phase == 21) && (!B_Pushed) && ((IsButtonTriggered(0, XINPUT_GAMEPAD_B)) || (Keyboard_IsKeyDown(KK_ENTER))))
			{
				//SetCircle(D3DXVECTOR2(1920.0f * 1.5f, 1920.0f * 0.6f), D3DXVECTOR2(1860.0f - 135.0f, SCORE_POS_Y), D3DXVECTOR2(2.0f, 4.0f));
				g_Tuto.Phase = 22;
				B_Pushed = true;
				TutoNext = false;
				g_Tuto.use = false;
				RePlaySound(BGM_RE());
				g_Tuto.TextFrame = 0;
				PlaySound(g_SE_Tuto, 0);
			}
		}
	}

	//チュートリアルの長押し遷移を防ぐ
	if ((!IsButtonTriggered(0, XINPUT_GAMEPAD_B))&& (!Keyboard_IsKeyDown(KK_ENTER)))
	{
		B_Pushed = false;
	}

	ArroFrame++;
	if (ArroFrame >= 10)
	{
		ArroFrame = 0;
		g_Tuto.ArSpd.y *= -1;
	}
	g_Tuto.ArPos.y += g_Tuto.ArSpd.y;

	//ボタン
	if ((g_Tuto.ButtonSize <= 70.0f)|| (g_Tuto.ButtonSize >= 90.0f))
	{
		g_Tuto.ButtonAdd *= -1.0f;
	}
	g_Tuto.ButtonSize += g_Tuto.ButtonAdd;
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTuto(void)
{
	//背景の描画処理
	DrawBG();
	if ((g_Tuto.Phase < 20) || (g_Tuto.Phase > 21))
	{
		DrawLane();
		DrawBullet();
	}
	DrawCombo();
	DrawPlayer();
	DrawEnemyBullet();
	DrawRhythm();
	DrawHp();
	DrawSpecial();
	DrawScore();
	DrawEnemy();
	DrawEffect();

	if (g_Tuto.use)
	{

		//中心サークル
		DrawSpriteColor(g_TextureCircle,
			g_Tuto.pos.x, g_Tuto.pos.y,
			g_Tuto.size.x, g_Tuto.size.y,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
		
		//上部サークル
		DrawSpriteColor(g_TextureCircle,
			g_Tuto.pos.x, g_Tuto.pos.y- g_Tuto.size.y,
			g_Tuto.size.x, g_Tuto.size.y,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
		//下部サークル
		DrawSpriteColor(g_TextureCircle,
			g_Tuto.pos.x, g_Tuto.pos.y + g_Tuto.size.y,
			g_Tuto.size.x, g_Tuto.size.y,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
		//左サークル
		DrawSpriteColor(g_TextureCircle,
			g_Tuto.pos.x - g_Tuto.size.x, g_Tuto.pos.y,
			g_Tuto.size.x, g_Tuto.size.y,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
		//右サークル
		DrawSpriteColor(g_TextureCircle,
			g_Tuto.pos.x + g_Tuto.size.x, g_Tuto.pos.y,
			g_Tuto.size.x, g_Tuto.size.y,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));


		//テキスト
		DrawSpriteColor(g_TextureText,
			CENTER_X, CENTER_Y-375.0f,
			TUTO_TEXT_SIZE_X, TUTO_TEXT_SIZE_X/2.0f,
			(1.0f / 4.0f)*g_Tuto.Tuv.x, (1.0f / 5.0f)*g_Tuto.Tuv.y,
			1.0f / 4.0f, 1.0f / 5.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		
		if (g_Tuto.TextFrame >= TEXT_CAN_PUSH)
		{
			//テキスト 次
			if (TutoNext)
			{
				DrawSpriteColor(g_TextureText,
					CENTER_X + 200.0f, CENTER_Y - 174.0f,
					200.0f, 100.0f,
					(1.0f / 4.0f) * 3.0f, (1.0f / 5.0f) * 0.0f,
					1.0f / 4.0f, 1.0f / 5.0f,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				DrawSpriteColor(g_TextureText,
					CENTER_X + 200.0f, CENTER_Y - 174.0f,
					200.0f, 100.0f,
					(1.0f / 4.0f) * 2.0f, (1.0f / 5.0f) * 0.0f,
					1.0f / 4.0f, 1.0f / 5.0f,
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			//ボタン
			DrawSpriteColor(g_TextureTutoButton,
				CENTER_X + 145.0f, CENTER_Y - 174.0f,
				g_Tuto.ButtonSize, g_Tuto.ButtonSize,
				(1.0f / 4.0f) * 1.0f, (1.0f / 2.0f) * 0.0f,
				1.0f / 4.0f, 1.0f / 2.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//矢印
		GetDeviceContext()->PSSetShaderResources(0, 1,
			GetTexture(g_TextureTutoArrow));

		DrawSpriteColorRotation(
			g_Tuto.ArPos.x,
			g_Tuto.ArPos.y,
			100.0f,
			100.0f,
			g_Tuto.ArRot,
			D3DXCOLOR(1.0f,0.5f,0.5f, 1.0f),
			0.0f,
			1.0f,
			1.0f,
			1
		);
	}

}


void SetCircle(D3DXVECTOR2 szst, D3DXVECTOR2 pos,D3DXVECTOR2 TextUV)
{
	g_Tuto.pos = pos;
	g_Tuto.size = szst;
	g_Tuto.Tuv = TextUV;
	g_Tuto.use = true;
}

void SetArrow(D3DXVECTOR2 pos,float rot)
{
	g_Tuto.ArPos = pos;
	g_Tuto.ArRot = rot;
}

T_CIRCLE* GetTuto()
{
	return &g_Tuto;
}
