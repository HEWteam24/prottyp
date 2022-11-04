//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "inputx.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DEADZONE			2200	// 各軸の25%を無効ゾーンとする
#define MAX_CONTROLLERS     4

struct CONTROLER_STATE
{
	XINPUT_STATE		lastState;
	XINPUT_STATE		state;
	XINPUT_STATE		trigger;
	XINPUT_VIBRATION	vibration;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitializePad(void);			// パッド初期化
void UpdatePad(void);
void UninitPad(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
CONTROLER_STATE g_Controllers[MAX_CONTROLLERS];
static float	g_LeftStickX[MAX_CONTROLLERS];
static float	g_LeftStickY[MAX_CONTROLLERS];
static float	g_RightStickX[MAX_CONTROLLERS];
static float	g_RightStickY[MAX_CONTROLLERS];


//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{	
	// パッドの初期化
	InitializePad();

	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	// パッドの終了処理
	UninitPad();
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
	// パッドの更新
	UpdatePad();
}

//---------------------------------------- 初期化
HRESULT InitializePad(void)			// パッド初期化
{
	//初期化
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	XInputEnable(true);
		
	return true;

}

//------------------------------------------- 終了処理
void UninitPad(void)
{
	//パラメータのリセット
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	//バイブレーション停止
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
		XInputSetState(i, &g_Controllers[i].vibration);

	XInputEnable(false);
}

//------------------------------------------ 更新
void UpdatePad(void)
{
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		XInputSetState(i, &g_Controllers[i].vibration);

		g_Controllers[i].lastState = g_Controllers[i].state;

		//正常：ERROR_SUCCESS　0
		//接続無し：ERROR_DEVICE_NOT_CONNECTED 1167
		DWORD result;
		result = XInputGetState(i, &g_Controllers[i].state);

		//トリガー作成
		g_Controllers[i].trigger.Gamepad.wButtons = ((g_Controllers[i].lastState.Gamepad.wButtons ^ g_Controllers[i].state.Gamepad.wButtons) & g_Controllers[i].state.Gamepad.wButtons);

		//左スティック情報の作成
		float LX = g_Controllers[i].state.Gamepad.sThumbLX;
		float LY = g_Controllers[i].state.Gamepad.sThumbLY;

		float magnitude = sqrtf((LX * LX) + (LY * LY));

		if (magnitude > 32767)
			magnitude = 32767;

		magnitude -= DEADZONE;

		if (magnitude <= 0)
		{
			g_Controllers[i].state.Gamepad.sThumbLX = 0;
			g_Controllers[i].state.Gamepad.sThumbLY = 0;
		}

		if(g_Controllers[i].state.Gamepad.sThumbLX >= 0)
			g_LeftStickX[i] = (float)g_Controllers[i].state.Gamepad.sThumbLX / 32767;
		else
			g_LeftStickX[i] = (float)g_Controllers[i].state.Gamepad.sThumbLX / 32768;

		if (g_Controllers[i].state.Gamepad.sThumbLY >= 0)
			g_LeftStickY[i] = (float)g_Controllers[i].state.Gamepad.sThumbLY / 32767;
		else
			g_LeftStickY[i] = (float)g_Controllers[i].state.Gamepad.sThumbLY / 32768;

		//右スティック情報の作成
		float RX = g_Controllers[i].state.Gamepad.sThumbRX;
		float RY = g_Controllers[i].state.Gamepad.sThumbRY;

		magnitude = sqrtf((RX * RX) + (RY * RY));

		if (magnitude > 32767)
			magnitude = 32767;

		magnitude -= DEADZONE;

		if (magnitude <= 0)
		{
			g_Controllers[i].state.Gamepad.sThumbRX = 0;
			g_Controllers[i].state.Gamepad.sThumbRY = 0;
		}

		if (g_Controllers[i].state.Gamepad.sThumbRX >= 0)
			g_RightStickX[i] = (float)g_Controllers[i].state.Gamepad.sThumbRX / 32767;
		else
			g_RightStickX[i] = (float)g_Controllers[i].state.Gamepad.sThumbRX / 32768;

		if (g_Controllers[i].state.Gamepad.sThumbLY >= 0)
			g_RightStickY[i] = (float)g_Controllers[i].state.Gamepad.sThumbRY / 32767;
		else
			g_RightStickY[i] = (float)g_Controllers[i].state.Gamepad.sThumbRY / 32768;
	}
}

//スティックの範囲
// X 左-1.0　右 1.0
// Y 上 1.0　下-1.0
float GetThumbLeftX(int padNo)
{
	return g_LeftStickX[padNo];
}

float GetThumbLeftY(int padNo)
{
	return g_LeftStickY[padNo];
}

float GetThumbRightX(int padNo)
{
	return g_RightStickX[padNo];
}

float GetThumbRightY(int padNo)
{
	return g_RightStickY[padNo];
}

//トリガーの範囲
// 0 ～ 255
int GetLeftTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bLeftTrigger;
}

int GetRightTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bRightTrigger;
}

// バイブレーションの範囲
// 0 ～ 255
void SetLeftVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
}

void SetRightVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void SetVibration(int padNo, int speed)
{
	speed %= 256;
	g_Controllers[padNo].vibration.wLeftMotorSpeed = ((speed + 1) * 256) - 1;
	g_Controllers[padNo].vibration.wRightMotorSpeed = ((speed + 1) * 256) - 1;
}

void StopVibration(int padNo)
{
	g_Controllers[padNo].vibration.wLeftMotorSpeed = 0;
	g_Controllers[padNo].vibration.wRightMotorSpeed = 0;
}

//ボタン押下状態の取得
BOOL IsButtonPressed(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].state.Gamepad.wButtons);
}

//ボタンパルス状態の取得
BOOL IsButtonTriggered(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].trigger.Gamepad.wButtons);
}
