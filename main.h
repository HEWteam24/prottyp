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
#pragma comment (lib, "xinput.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920.0f)						// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080.0f)						// �E�C���h�E�̍���

#define CENTER_X		(SCREEN_WIDTH/2)					//���SX
#define CENTER_Y		(SCREEN_HEIGHT/2)					//���SY

#define LANE_SIZE_X		(170.0f)						//���[���̕�
#define LANE_SIZE_Y		(1080.0f)						//���[���̍���

#define BULLETLANE_1 (SCREEN_WIDTH / 2 - LANE_SIZE_X * 2)	//���[��1
#define BULLETLANE_2 (SCREEN_WIDTH / 2 - LANE_SIZE_X)		//���[��2
#define BULLETLANE_3 (SCREEN_WIDTH / 2)						//���[��3
#define BULLETLANE_4 (SCREEN_WIDTH / 2 + LANE_SIZE_X)		//���[��4
#define BULLETLANE_5 (SCREEN_WIDTH / 2 + LANE_SIZE_X * 2)	//���[��5

#define PLAYER_SIZE_X	(100*0.6)						//�v���C���[�̕�
#define PLAYER_SIZE_Y	(360*0.6)						//�v���C���[�̍���

#define PLAYER_POS_DEFAULT_X	(CENTER_X)			//�v���C���[�̈ʒu
#define PLAYER_POS_DEFAULT_Y	(CENTER_Y+380.0f)	//�v���C���[�̈ʒu

#define PLAYER_HP_DEFAULT	(300.0f)
#define GOOD_BAD_X			(400.0f*0.7f)
#define GOOD_BAD_Y			(100.0f*0.7f)



//�m�[�c�̏����l
#define		NOTES_MAX			(6)
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

#define		SCORE_SIZE_X		(45)
#define		SCORE_SIZE_Y		(60)
#define		SCORE_POS_X		(1860 - (i * SCORE_SIZE_X))
#define		SCORE_POS_Y		(80.0f)
#define		SCOER_DIGIT		(8)

#define		SCORE_R_SIZE_X		(60)
#define		SCORE_R_SIZE_Y		(80)
#define		SCORE_R_POS_X		(1760 - (i * SCORE_R_SIZE_X))
#define		SCORE_R_POS_Y		(CENTER_Y+40.0f)
#define		SCOER_R_DIGIT		(8)

#define		SCORE_R_TEXT_POS_X			(1381.0f)
#define		SCORE_R_TEXT_POS_Y			(CENTER_Y-40.0f)
#define		SCORE_R_TEXT_SIZE_X			(133)
#define		SCORE_R_TEXT_SIZE_Y			(60)


#define		SCORETEXT_POS_X				(1580.0f)
#define		SCORETEXT_POS_Y				(25.0f)
#define		SCORETEXT_SIZE_X			(100)
#define		SCORETEXT_SIZE_Y			(45)

#define		COMBO_SIZE_X	(190.0f)						//�v���C���[�̕�
#define		COMBO_SIZE_Y	(220.0f)						//�v���C���[�̍���
#define		COMBO_TEX		(((char*)"data\\texture\\number.png"))
#define		COMBO_DIGIT		(3)
#define		COMBO_UV_W		(0.2)
#define		COMBO_UV_H		(0.2)
#define		COMBO_POS_X		(SCREEN_WIDTH/2+COMBO_SIZE_X - (i * COMBO_SIZE_X))
#define		COMBO_POS_Y		(SCREEN_HEIGHT/2)

#define		COMBOTEXT_POS_X				(SCREEN_WIDTH/2)
#define		COMBOTEXT_POS_Y				(SCREEN_HEIGHT/2-170)
#define		COMBOTEXT_SIZE_X			(230)
#define		COMBOTEXT_SIZE_Y			(80)

#define		COMBO_R_SIZE_X		(60)
#define		COMBO_R_SIZE_Y		(80)
#define		COMBO_R_POS_X		(1650 - (i * SCORE_R_SIZE_X))
#define		COMBO_R_POS_Y		(CENTER_Y+170.0f)

#define		COMBO_R_TEXT_POS_Y			(CENTER_Y+160.0f)

#define		COMBOMAG_SIZE_X				(80.0f)
#define		COMBOMAG_SIZE_Y				(95.0f)
#define		COMBOMAG_POS_X				(SCREEN_WIDTH/2+COMBOMAG_SIZE_X - (i * COMBOMAG_SIZE_X))
#define		COMBOMAG_POS_Y				(SCREEN_HEIGHT/2+180)


//���[���̏����l
#define		LANE_MAX			(5)				//���[����
#define		LANE_DRAW_SIZE_X	(150)
#define		LANE_DRAW_SIZE_Y	(SCREEN_HEIGHT)

#define			PLAYER_HP_POS_X		(CENTER_X+460.0f)							//�v���C���[�̗̓Q�[�W���WX
#define			PLAYER_HP_POS_Y		(CENTER_Y-10.0f)							//�v���C���[�̗̓Q�[�W���WY
#define			PLAYER_HP_SIZE_X	(50.0f)										//�v���C���[�̗̓T�C�YX
#define			PLAYER_HP_SIZE_Y	(900.0f)									//�v���C���[�̗̓T�C�YY
#define			PLAYER_HPB_SIZE_X	(60.0f)										//�v���C���[�̗̓T�C�YX
#define			PLAYER_HPB_SIZE_Y	(910.0f)									//�v���C���[�̗̓T�C�YY
#define			PLAYER_HP_TEX_A		((char*)"data\\texture\\enemyHpBar00.png")	//�v���C���[�e�N�X�`��
#define			PLAYER_HP_TEX_B		((char*)"data\\texture\\enemyHpBar01.png")	//�v���C���[�e�N�X�`��


//�V�[���̒�`
enum SCENE
{
	SCENE_NONE,			//�V�[������
	SCENE_TITLE,		//�^�C�g�����
	SCENE_GAME,			//�Q�[���{��
	SCENE_RESULT,		//���U���g���
	SCENE_GAMEOVER,		//�Q�[���I�[�o�[
	SCENE_STAGESELECT,	//�Z���N�g
	SCENE_SKILLSELECT,	//�X�L���Z���N�g
	SCENE_TUTO,
	SCENE_STAGE_0,
	SCENE_CREDIT,

	SCENE_NUM,		//�I�[�R�[�h
};

struct NOW_SCENE
{
	int SceneNow;
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

void SetScene(int nextScene);
NOW_SCENE* GetNowScene();
float frand(void);
