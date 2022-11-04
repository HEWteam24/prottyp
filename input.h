////=============================================================================
////
//// ���͏��� [input.h]
//// Author : 
////
////=============================================================================
//#pragma once
//
//#include "main.h"
//
////*****************************************************************************
//// �}�N����`
////*****************************************************************************
//
//// �v���O������������Ƃ��Ɏg��
//#define	USE_KEYBOARD				// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
//#define	USE_MOUSE					// �錾����ƃ}�E�X�ő���\�ɂȂ�
//
//enum {	// �{�^���ɑ΂���rgbButtons[?]�z��̔z��ԍ�(DirectInput��ł�XYAB�{�^���ʒu�ɍ��킹��)
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
//// �v���g�^�C�v�錾
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
//BOOL IsMouseLeftPressed(void);      // ���N���b�N�������
//BOOL IsMouseLeftTriggered(void);    // ���N���b�N�����u��
//BOOL IsMouseRightPressed(void);     // �E�N���b�N�������
//BOOL IsMouseRightTriggered(void);   // �E�N���b�N�����u��
//BOOL IsMouseCenterPressed(void);    // ���N���b�N�������
//BOOL IsMouseCenterTriggered(void);  // ���N���b�N�����u��
//long GetMouseX(void);               // �}�E�X��X�����ɓ��������Βl
//long GetMouseY(void);               // �}�E�X��Y�����ɓ��������Βl
//long GetMouseZ(void);               // �}�E�X�z�C�[�������������Βl
//
////---------------------------- game pad
//BOOL IsButtonPressed(int padNo,DWORD button);
//BOOL IsButtonTriggered(int padNo,DWORD button);
//
//
