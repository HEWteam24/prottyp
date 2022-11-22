/*==============================================================================

   テクスチャの描画 [main.cpp]
                                                         Author : うんち
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include <time.h>
#include "renderer.h"
//#include "input.h"
#include "inputx.h"
#include "keyboard.h"
#include "sound.h"
#include "texture.h"
#include "sprite.h"

#include "title.h"
#include "game.h"
#include "Over.h"
#include "Result.h"
#include "stage_select.h"

#include "fade.h"
#include "frame.h"
#include "rhythm.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// ウインドウのクラス名
#define WINDOW_CAPTION		"フォルティシッシャモ"			// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************

#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用

#endif


static int g_Scene;//現在実行されているシーン


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//ランダムシードの初期化
	srand((unsigned int)time(NULL));

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	Start(60);
	int	op = 0;
	// メッセージループ
	while(1)
	{

			
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{// PostQuitMessage()が呼ばれたらループ終了
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
				dwCurrentTime = timeGetTime();					// システム時刻を取得

				if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
				{
#ifdef _DEBUG
					g_CountFPS = dwFrameCount;
#endif
					dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
					dwFrameCount = 0;							// カウントをクリア
				}

				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
				{
					dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
					wsprintf(g_DebugStr, WINDOW_CAPTION);
					wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
					SetWindowText(hWnd, g_DebugStr);

#endif			
				int	loop = Run();
				for (int i = 0; i < loop; i++) {

						Update();			// 更新処理
						Draw();				// 描画処理

						dwFrameCount++;		// 処理回数のカウントを加算
					}
				}
			}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Keyboard_ProcessMessage(message, wParam, lParam);

	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);

	// 入力処理の初期化
	InitInput(hInstance, hWnd);
	Keyboard_Initialize();

	InitFrame();
	// サウンドの初期化
	InitSound(hWnd);

	InitSprite();

	// フェードの初期化処理
	InitFade();

	//シーンの初期化（タイトルからスタート）
	SetFadeColor(0.0f, 0.0f, 0.0f);
	SceneFadeIn(SCENE_TITLE);

	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// フェードの終了処理
	UninitFade();

	// テクスチャの解放
	UninitTexture();

	// サウンドの終了処理
	UninitSound();

	// 入力処理の終了処理
	UninitInput();

	// レンダリングの終了処理
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力処理の更新処理
	UpdateInput();

	switch (g_Scene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE_STAGESELECT:
		UpdateStageSelect();
		break;
	case SCENE_GAME:
		UpdateGame();
		break;
	case SCENE_GAMEOVER:
		UpdateOver();
		break;
	case SCENE_RESULT:
		UpdateResult();
		break;
	}

	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	switch (g_Scene)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_STAGESELECT:
		DrawStageSelect();
		break;

	case SCENE_GAME:
		DrawGame();
		break;

	case SCENE_GAMEOVER:
		DrawOver();
		break;
	case SCENE_RESULT:
		DrawResult();
		break;
	}

	//フェードの描画
	DrawFade();

	// バックバッファ、フロントバッファ入れ替え
	Present();
}


void SetScene(int nextScene)
{
	//現在動作しているシーンの終了処理を実行する
	switch (g_Scene)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_STAGESELECT:
		UninitStageSelect();
	case SCENE_GAME:
		UninitGame();
		break;
		break;
	case SCENE_GAMEOVER:
		UninitOver();
		break;
	case SCENE_RESULT:
		UninitResult();
		break;
	}

	//動作するシーンを更新する
	g_Scene = nextScene;

	//動作するシーンの初期化処理を実行する
	switch (g_Scene)
	{
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_STAGESELECT:
		InitStageSelect();
		break;
	case SCENE_GAME:
		InitGame();
		break;
	case SCENE_GAMEOVER:
		InitOver();
		break;
	case SCENE_RESULT:
		InitResult();
		break;
	}
}

float frand(void)
{
	return (float)rand() / RAND_MAX;
}
