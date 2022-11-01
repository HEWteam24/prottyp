/*==============================================================================

   �e�N�X�`���̕`�� [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920)						// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)						// �E�C���h�E�̍���

#define CENTER_X		(SCREEN_WIDTH/2)					//���SX
#define CENTER_Y		(SCREEN_HEIGHT/2)					//���SY

#define LANE_SIZE_X		(170.0f)						//���[���̕�
#define LANE_SIZE_Y		(1080.0f)						//���[���̍���

#define PLAYER_SIZE_X	(100*0.6)						//�v���C���[�̕�
#define PLAYER_SIZE_Y	(360*0.6)						//�v���C���[�̍���

#define PLAYER_POS_DEFAULT_X	(CENTER_X)			//�v���C���[�̈ʒu
#define PLAYER_POS_DEFAULT_Y	(CENTER_Y+350.0f)	//�v���C���[�̈ʒu

#define PLAYER_HP_DEFAULT	(300.0f)
#define GOOD_BAD_X			(400.0f*0.7f)
#define GOOD_BAD_Y			(100.0f*0.7f)



//�m�[�c�̏����l
#define		NOTES_MAX			(20)
#define		NOTES_POS_X_1		(582.5f)
#define		NOTES_POS_X_2		(1337.5f)
#define		NOTES_POS_Y			(SCREEN_HEIGHT-100)
#define		NOTES_SIZE_X		(75.0f)
#define		NOTES_SIZE_Y		(75.0f)
#define		NOTES_DIST			(6)
#define		NOTES_SP			(1.5f*NOTES_DIST)
#define		NOTES_TEX_RIGHT			(((char*)"data\\texture\\notes_right.png"))
#define		NOTES_TEX_LEFT			(((char*)"data\\texture\\notes_left.png"))
#define		NOTES_TEX_CENTER		(((char*)"data\\texture\\notes_center.png"))
#define		NOTESLANE_POS_X		(SCREEN_WIDTH/2)
#define		NOTESLANE_POS_Y		(NOTES_POS_Y)
#define		NOTESLANE_SIZE_X	(LANE_SIZE_X*5)
#define		NOTESLANE_SIZE_Y	(100.0f)
#define		NOTESLANE_TEX		(((char*)"data\\texture\\notes_lane.png"))

#define		SCORE_SIZE_X		(70)
#define		SCORE_SIZE_Y		(100)
#define		SCORE_POS_X		(1800 - (i * SCORE_SIZE_X))
#define		SCORE_POS_Y		(SCREEN_HEIGHT/2-200.0f)
#define		SCOER_DIGIT		(6)


#define		COMBO_SIZE_X	(150.0f)						//�v���C���[�̕�
#define		COMBO_SIZE_Y	(220.0f)						//�v���C���[�̍���
#define		COMBO_TEX		(((char*)"data\\texture\\number.png"))
#define		COMBO_DIGIT		(3)
#define		COMBO_UV_W		(0.2)
#define		COMBO_UV_H		(0.2)
#define		COMBO_POS_X		(1780 - (i * COMBO_SIZE_X))
#define		COMBO_POS_Y		(SCREEN_HEIGHT/2+250.0f)




//�V�[���̒�`
enum SCENE
{
	SCENE_NONE,		//�V�[������
	SCENE_TITLE,	//�^�C�g�����
	SCENE_GAME,		//�Q�[���{��
	SCENE_RESULT,	//���U���g���
	SCENE_GAMEOVER,

	SCENE_NUM,		//�I�[�R�[�h
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

void SetScene(SCENE nextScene);
float frand(void);
