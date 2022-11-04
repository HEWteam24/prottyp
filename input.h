////=============================================================================
////
//// 入力処理 [input.h]
//// Author : 
////
////=============================================================================
//#pragma once
//
//#include "main.h"
//
////*****************************************************************************
//// マクロ定義
////*****************************************************************************
//
//// プログラム分けするときに使う
//#define	USE_KEYBOARD				// 宣言するとキーボードで操作可能になる
//#define	USE_MOUSE					// 宣言するとマウスで操作可能になる
//
//enum {	// ボタンに対するrgbButtons[?]配列の配列番号(DirectInput上でのXYABボタン位置に合わせた)
//	rgbButtons_X,
//	rgbButtons_A,
//	rgbButtons_B,
//	rgbButtons_Y,
//	rgbButtons_L,
//	rgbButtons_R,
//	rgbButtons_L2,
//	rgbButtons_R2,
//	rgbButtons_SELECT,
//	rgbButtons_START,
//};
//
//
//
////*****************************************************************************
//// プロトタイプ宣言
////*****************************************************************************
//HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
//void UninitInput(void);
//void UpdateInput(void);
//
////---------------------------- keyboard
//bool GetKeyboardPress(int nKey);
//bool GetKeyboardTrigger(int nKey);
//bool GetKeyboardRepeat(int nKey);
//bool GetKeyboardRelease(int nKey);
//
////---------------------------- mouse
//BOOL IsMouseLeftPressed(void);      // 左クリックした状態
//BOOL IsMouseLeftTriggered(void);    // 左クリックした瞬間
//BOOL IsMouseRightPressed(void);     // 右クリックした状態
//BOOL IsMouseRightTriggered(void);   // 右クリックした瞬間
//BOOL IsMouseCenterPressed(void);    // 中クリックした状態
//BOOL IsMouseCenterTriggered(void);  // 中クリックした瞬間
//long GetMouseX(void);               // マウスがX方向に動いた相対値
//long GetMouseY(void);               // マウスがY方向に動いた相対値
//long GetMouseZ(void);               // マウスホイールが動いた相対値
//
////---------------------------- game pad
//BOOL IsButtonPressed(int padNo,DWORD button);
//BOOL IsButtonTriggered(int padNo,DWORD button);
//
//
