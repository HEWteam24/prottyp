////=============================================================================
////
//// 入力処理 [input.cpp]
//// Author : 
////
////=============================================================================
//#include "input.h"
//
//
////*****************************************************************************
//// マクロ定義
////*****************************************************************************
//#define	NUM_KEY_MAX			(256)
//
//// game pad用設定値
//#define DEADZONE		2500			// 各軸の25%を無効ゾーンとする
//#define RANGE_MAX		1000			// 有効範囲の最大値
//#define RANGE_MIN		-1000			// 有効範囲の最小値
//
//
////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//
//HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
//void UninitKeyboard(void);
//HRESULT UpdateKeyboard(void);
//
//HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow); // マウスの初期化
//void UninitMouse();										// マウスの終了処理
//HRESULT UpdateMouse();									// マウスの更新処理
//
//HRESULT InitializePad(void);			// パッド初期化
////BOOL CALLBACK SearchPadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	// パッド検査コールバック
//void UpdatePad(void);
//void UninitPad(void);
//
////*****************************************************************************
//// グローバル変数
////*****************************************************************************
//
////------------------------------- keyboard
//LPDIRECTINPUT8			g_pDInput = NULL;					// IDirectInput8インターフェースへのポインタ
//LPDIRECTINPUTDEVICE8	g_pDIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
//BYTE					g_keyState[NUM_KEY_MAX];			// キーボードの状態を受け取るワーク
//BYTE					g_keyStateTrigger[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
//BYTE					g_keyStateRepeat[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
//BYTE					g_keyStateRelease[NUM_KEY_MAX];		// キーボードの状態を受け取るワーク
//int						g_keyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
//
////--------------------------------- mouse
//static LPDIRECTINPUTDEVICE8 pMouse = NULL; // mouse
//
//static DIMOUSESTATE2   mouseState;		// マウスのダイレクトな状態
//static DIMOUSESTATE2   mouseTrigger;	// 押された瞬間だけON
//
////=============================================================================
//// 入力処理の初期化
////=============================================================================
//HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
//{
//	HRESULT hr;
//
//	if(!g_pDInput)
//	{
//		// DirectInputオブジェクトの作成
//		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
//									IID_IDirectInput8, (void**)&g_pDInput, NULL);
//	}
//
//	// キーボードの初期化
//	InitKeyboard(hInst, hWnd);
//
// 	// マウスの初期化
//	InitializeMouse(hInst, hWnd);
//	
//	return S_OK;
//}
//
////=============================================================================
//// 入力処理の終了処理
////=============================================================================
//void UninitInput(void)
//{
//	// キーボードの終了処理
//	UninitKeyboard();
//
//	// マウスの終了処理
//	UninitMouse();
//
//	if(g_pDInput)
//	{
//		g_pDInput->Release();
//		g_pDInput = NULL;
//	}
//}
//
////=============================================================================
//// 入力処理の更新処理
////=============================================================================
//void UpdateInput(void)
//{
//	// キーボードの更新
//	UpdateKeyboard();
//	
//	// マウスの更新
//	UpdateMouse();
//}
//
////=============================================================================
//// キーボードの初期化
////=============================================================================
//HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
//{
//	HRESULT hr;
//
//	// デバイスオブジェクトを作成
//	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDIDevKeyboard, NULL);
//	// データフォーマットを設定
//	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
//	// 協調モードを設定（フォアグラウンド＆非排他モード）
//	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
//	// キーボードへのアクセス権を獲得(入力制御開始)
//	g_pDIDevKeyboard->Acquire();
//
//	return S_OK;
//}
//
////=============================================================================
//// キーボードの終了処理
////=============================================================================
//void UninitKeyboard(void)
//{
//	if(g_pDIDevKeyboard)
//	{
//		g_pDIDevKeyboard->Release();
//		g_pDIDevKeyboard = NULL;
//	}
//}
//
////=============================================================================
//// キーボードの更新
////=============================================================================
//HRESULT UpdateKeyboard(void)
//{
//	HRESULT hr;
//	BYTE keyStateOld[256];
//
//	// 前回のデータを保存
//	memcpy(keyStateOld, g_keyState, NUM_KEY_MAX);
//
//	// デバイスからデータを取得
//	hr = g_pDIDevKeyboard->GetDeviceState(sizeof(g_keyState), g_keyState);
//	if(SUCCEEDED(hr))
//	{
//		for(int cnt = 0; cnt < NUM_KEY_MAX; cnt++)
//		{
//			g_keyStateTrigger[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & g_keyState[cnt];
//			g_keyStateRelease[cnt] = (keyStateOld[cnt] ^ g_keyState[cnt]) & ~g_keyState[cnt];
//			g_keyStateRepeat[cnt] = g_keyStateTrigger[cnt];
//
//			if(g_keyState[cnt])
//			{
//				g_keyStateRepeatCnt[cnt]++;
//				if(g_keyStateRepeatCnt[cnt] >= 20)
//				{
//					g_keyStateRepeat[cnt] = g_keyState[cnt];
//				}
//			}
//			else
//			{
//				g_keyStateRepeatCnt[cnt] = 0;
//				g_keyStateRepeat[cnt] = 0;
//			}
//		}
//	}
//	else
//	{
//		// キーボードへのアクセス権を取得
//		g_pDIDevKeyboard->Acquire();
//	}
//
//	return S_OK;
//}
//
////=============================================================================
//// キーボードのプレス状態を取得
////=============================================================================
//bool GetKeyboardPress(int key)
//{
//	return (g_keyState[key] & 0x80) ? true : false;
//}
//
////=============================================================================
//// キーボードのトリガー状態を取得
////=============================================================================
//bool GetKeyboardTrigger(int key)
//{
//	return (g_keyStateTrigger[key] & 0x80) ? true : false;
//}
//
////=============================================================================
//// キーボードのリピート状態を取得
////=============================================================================
//bool GetKeyboardRepeat(int key)
//{
//	return (g_keyStateRepeat[key] & 0x80) ? true : false;
//}
//
////=============================================================================
//// キーボードのリリ－ス状態を取得
////=============================================================================
//bool GetKeyboardRelease(int key)
//{
//	return (g_keyStateRelease[key] & 0x80) ? true : false;
//}
//
//
////=============================================================================
//// マウス関係の処理
////=============================================================================
//// マウスの初期化
//HRESULT InitializeMouse(HINSTANCE hInst,HWND hWindow)
//{
//	HRESULT result;
//	// デバイス作成
//	result = g_pDInput->CreateDevice(GUID_SysMouse,&pMouse,NULL);
//	if(FAILED(result) || pMouse==NULL)
//	{
//		MessageBox(hWindow,"No mouse","Warning",MB_OK | MB_ICONWARNING);
//		return result;
//	}
//	// データフォーマット設定
//	result = pMouse->SetDataFormat(&c_dfDIMouse2);
//	if(FAILED(result))
//	{
//		MessageBox(hWindow,"Can't setup mouse","Warning",MB_OK | MB_ICONWARNING);
//		return result;
//	}
//	// 他のアプリと協調モードに設定
//	result = pMouse->SetCooperativeLevel(hWindow, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
//	if(FAILED(result))
//	{
//		MessageBox(hWindow,"Mouse mode error","Warning",MB_OK | MB_ICONWARNING);
//		return result;
//	}
//	
//	// デバイスの設定
//	DIPROPDWORD prop;
//	
//	prop.diph.dwSize = sizeof(prop);
//	prop.diph.dwHeaderSize = sizeof(prop.diph);
//	prop.diph.dwObj = 0;
//	prop.diph.dwHow = DIPH_DEVICE;
//	prop.dwData = DIPROPAXISMODE_REL;		// マウスの移動値　相対値
//
//	result = pMouse->SetProperty(DIPROP_AXISMODE,&prop.diph);
//	if(FAILED(result))
//	{
//		MessageBox(hWindow,"Mouse property error","Warning",MB_OK | MB_ICONWARNING);
//		return result;	
//	}
//	
//	// アクセス権を得る
//	pMouse->Acquire();
//	return result;
//}
////---------------------------------------------------------
//void UninitMouse()
//{
//	if(pMouse)
//	{
//		pMouse->Unacquire();
//		pMouse->Release();
//		pMouse = NULL;
//	}
//
//}
////-----------------------------------------------------------
//HRESULT UpdateMouse()
//{
//	HRESULT result;
//	// 前回の値保存
//	DIMOUSESTATE2 lastMouseState = mouseState;
//	// データ取得
//	result = pMouse->GetDeviceState(sizeof(mouseState),&mouseState);
//	if(SUCCEEDED(result))
//	{
//		mouseTrigger.lX = mouseState.lX;
//		mouseTrigger.lY = mouseState.lY;
//		mouseTrigger.lZ = mouseState.lZ;
//		// マウスのボタン状態
//		for(int i=0;i<8;i++)
//		{
//			mouseTrigger.rgbButtons[i] = ((lastMouseState.rgbButtons[i] ^
//				mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);
//		}
//	}
//	else	// 取得失敗
//	{
//		// アクセス権を得てみる
//		result = pMouse->Acquire();
//	}
//	return result;
//	
//}
//
////----------------------------------------------
//BOOL IsMouseLeftPressed(void)
//{
//	return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
//}
//BOOL IsMouseLeftTriggered(void)
//{
//	return (BOOL)(mouseTrigger.rgbButtons[0] & 0x80);
//}
//BOOL IsMouseRightPressed(void)
//{
//	return (BOOL)(mouseState.rgbButtons[1] & 0x80);
//}
//BOOL IsMouseRightTriggered(void)
//{
//	return (BOOL)(mouseTrigger.rgbButtons[1] & 0x80);
//}
//BOOL IsMouseCenterPressed(void)
//{
//	return (BOOL)(mouseState.rgbButtons[2] & 0x80);
//}
//BOOL IsMouseCenterTriggered(void)
//{
//	return (BOOL)(mouseTrigger.rgbButtons[2] & 0x80);
//}
////------------------
//long GetMouseX(void)
//{
//	return mouseState.lX;
//}
//long GetMouseY(void)
//{
//	return mouseState.lY;
//}
//long GetMouseZ(void)
//{
//	return mouseState.lZ;
//}
