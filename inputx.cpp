//=============================================================================
//
// ���͏��� [input.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "inputx.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DEADZONE			2200	// �e����25%�𖳌��]�[���Ƃ���
#define MAX_CONTROLLERS     4

struct CONTROLER_STATE
{
	XINPUT_STATE		lastState;
	XINPUT_STATE		state;
	XINPUT_STATE		trigger;
	XINPUT_VIBRATION	vibration;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitializePad(void);			// �p�b�h������
void UpdatePad(void);
void UninitPad(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CONTROLER_STATE g_Controllers[MAX_CONTROLLERS];
static float	g_LeftStickX[MAX_CONTROLLERS];
static float	g_LeftStickY[MAX_CONTROLLERS];
static float	g_RightStickX[MAX_CONTROLLERS];
static float	g_RightStickY[MAX_CONTROLLERS];


//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{	
	// �p�b�h�̏�����
	InitializePad();

	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void UninitInput(void)
{
	// �p�b�h�̏I������
	UninitPad();
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void UpdateInput(void)
{
	// �p�b�h�̍X�V
	UpdatePad();
}

//---------------------------------------- ������
HRESULT InitializePad(void)			// �p�b�h������
{
	//������
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	XInputEnable(true);
		
	return true;

}

//------------------------------------------- �I������
void UninitPad(void)
{
	//�p�����[�^�̃��Z�b�g
	ZeroMemory(g_Controllers, sizeof(CONTROLER_STATE) * MAX_CONTROLLERS);

	//�o�C�u���[�V������~
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
		XInputSetState(i, &g_Controllers[i].vibration);

	XInputEnable(false);
}

//------------------------------------------ �X�V
void UpdatePad(void)
{
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		XInputSetState(i, &g_Controllers[i].vibration);

		g_Controllers[i].lastState = g_Controllers[i].state;

		//����FERROR_SUCCESS�@0
		//�ڑ������FERROR_DEVICE_NOT_CONNECTED 1167
		DWORD result;
		result = XInputGetState(i, &g_Controllers[i].state);

		//�g���K�[�쐬
		g_Controllers[i].trigger.Gamepad.wButtons = ((g_Controllers[i].lastState.Gamepad.wButtons ^ g_Controllers[i].state.Gamepad.wButtons) & g_Controllers[i].state.Gamepad.wButtons);

		//���X�e�B�b�N���̍쐬
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

		//�E�X�e�B�b�N���̍쐬
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

//�X�e�B�b�N�͈̔�
// X ��-1.0�@�E 1.0
// Y �� 1.0�@��-1.0
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

//�g���K�[�͈̔�
// 0 �` 255
int GetLeftTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bLeftTrigger;
}

int GetRightTrigger(int padNo)
{
	return g_Controllers[padNo].state.Gamepad.bRightTrigger;
}

// �o�C�u���[�V�����͈̔�
// 0 �` 255
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

//�{�^��������Ԃ̎擾
BOOL IsButtonPressed(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].state.Gamepad.wButtons);
}

//�{�^���p���X��Ԃ̎擾
BOOL IsButtonTriggered(int padNo, DWORD button)
{
	return (button & g_Controllers[padNo].trigger.Gamepad.wButtons);
}
