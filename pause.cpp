/*==============================================================================

   ポーズの制御 [pause.cpp]
														 Author :　柴田 祐希
														 Date   :　12/13
--------------------------------------------------------------------------------
Pボタンでポーズ(ESCはコンソールが終了するからできなかった)

WとSで機能の選択(上からコンティニュー、リトライ、タイトル画面に戻る)

ENTERで機能の実行です。

安定のために今までのENTERでタイトルに戻るは「Gキー」に動作を移しています。
*/

//==============================================================================

#include "pause.h"

static int PauseTexture;
static int PauseTextTexture;
static int PauseCntTexture;
static int RetryTexture;
static int BackTexture;
static int ContinueTexture;
static int ArrowTexture;

int arrowNum;
float num;
bool already;

PAUSE hoge;

void InitPause()
{
	PauseTexture = LoadTexture((char*)"data/TEXTURE/UI_Back_B.png");
	PauseTextTexture = LoadTexture((char*)"data/TEXTURE/text_pause.png");
	PauseCntTexture = LoadTexture((char*)"data/TEXTURE/number.png");
	RetryTexture = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	BackTexture = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	ContinueTexture = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	ArrowTexture = LoadTexture((char*)"data/TEXTURE/notes_right.png");

	hoge.pause = false;		//PAUSE中かどうかの判定
	hoge.restart = false;	//コンティニュー判定
	hoge.pause_frame = 0;	//PAUSEから復帰するまでの時間(3秒)
	hoge.PauseAction = 0;	//PAUSEで選択した機能、及び矢印の場所(Continue、Retry、BackTitle)
	already = false;		//PAUSEでUIの操作をTrriger化するためのフラグ
}

void UninitPause()
{
	hoge.pause = false;
	hoge.restart = false;
	hoge.pause_frame = 0;
	hoge.PauseAction = 0;
	already = false;
}


void UpdatePause()
{
	//コンティニューの処理
	//
	if (hoge.restart == true)
	{
		hoge.pause_frame++;
	}

	if (hoge.pause_frame == 180)
	{
		hoge.pause_frame = 0;
		hoge.restart = false;
		hoge.pause = false;
		RePlaySound(BGM_RE());
	}

	if (Keyboard_IsKeyDown(KK_W) && already == false)
	{

		already = true;

		hoge.PauseAction -= 1;

		if (hoge.PauseAction == -1)
		{
			hoge.PauseAction = eBack;
		}


	}

	if (Keyboard_IsKeyDown(KK_S) && already == false)
	{
		already = true;

		hoge.PauseAction += 1;
		if (hoge.PauseAction == 3)
		{
			hoge.PauseAction = eContinue;
		}

	
	}

	if (Keyboard_IsKeyUp(KK_S) && Keyboard_IsKeyUp(KK_W))
	{
		already = false;
	}


	if (Keyboard_IsKeyDown(KK_P) && hoge.pause == false)
	{
		PauseSound(BGM_RE());
		hoge.pause = true;
	}



	if (Keyboard_IsKeyDown(KK_ENTER) && hoge.pause == true)
	{
		switch (hoge.PauseAction)
		{
		case eContinue:
			hoge.restart = true;
			break;

		case eReTry:
			ReTry();
			break;
		case eBack:
			Back();
			break;
		}
	}
}

void DrawPause()
{


	if (hoge.pause == true)
	{
		//暗転
		DrawSpriteColor(PauseTexture,
			0.0f,
			0.0f,
			10000.0f,
			10000.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));

		//pauseテキスト
		if (hoge.restart == false)
		{
			DrawSpriteColor(PauseTextTexture,
				CENTER_X,
				CENTER_Y - 300,
				400.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//続ける
		if (hoge.restart == false)
		{
			DrawSpriteColor(ContinueTexture,
				CENTER_X,
				CENTER_Y - 150,
				500.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}

		//リトライ
		if (hoge.restart == false)
		{
			DrawSpriteColor(RetryTexture,
				CENTER_X,
				CENTER_Y,
				500.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		}

		//back
		if (hoge.restart == false)
		{
			DrawSpriteColor(BackTexture,
				CENTER_X,
				CENTER_Y + 150,
				500.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		}

		//矢印
		if (hoge.restart == false)
		{
			DrawSpriteColor(ArrowTexture,
				CENTER_X / 2 + 150,
				CENTER_Y - 150 + (hoge.PauseAction * 150),
				100.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}




	if (hoge.restart == true)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1,
			GetTexture(PauseCntTexture));
		for (int i = 0; i < SCOER_DIGIT; i++) {
			DrawSpriteColorRotation(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2,
				300.0f,
				300.0f,
				0.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				(3.0f - (hoge.pause_frame / 60)),
				0.2f,
				0.2f,
				5
			);
		}
	}
}

void ReTry()
{
	SceneTransition(SCENE_GAME);
}

void Back()
{ 
	SceneTransition(SCENE_TITLE);
}

PAUSE* GetPause()
{
	return &hoge;
}