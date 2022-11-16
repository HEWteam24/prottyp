/*==============================================================================

   �^�C�g����ʏ��� [StageSelect.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "stage_select.h"
#include "texture.h"
#include "sprite.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


static int g_TextureBgStageSelect[2];//�^�C�g����ʗp�e�N�X�`���̎��ʎq
static int g_BGMNo;//�^�C�g���pBGM�̎��ʎq
int NowSelect = STAGE_1;

STAGE_PANEL g_StagePanel[STAGE_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStageSelect(void)
{
	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_TextureBgStageSelect[0] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");
	g_TextureBgStageSelect[1] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");

	g_StagePanel[STAGE_0].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel0.png");
	g_StagePanel[STAGE_1].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel1_test.png");
	g_StagePanel[STAGE_2].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel2.png");
	g_StagePanel[STAGE_3].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel3.png");
	g_StagePanel[STAGE_4].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel4.png");
	g_StagePanel[STAGE_5].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel5.png");
	g_StagePanel[STAGE_6].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel6.png");
	g_StagePanel[STAGE_7].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel7.png");
	g_StagePanel[STAGE_8].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel8.png");
	g_StagePanel[STAGE_9].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel9.png");
	g_StagePanel[STAGE_10].texno= LoadTexture((char*)"data/TEXTURE/Stage_Panel10.png");

	//�\���̂̏�����
	for (int i = 0; i < STAGE_MAX; i++)
	{
		g_StagePanel[i].pos = D3DXVECTOR2(-480.0f*2+i*480.0f,CENTER_Y-50.0f);
		g_StagePanel[i].spd = 10.0f;
		g_StagePanel[i].size= D3DXVECTOR2(300.0f, 300.0f);
		g_StagePanel[i].col = D3DXCOLOR(1.0f, 1.0f,1.0f,1.0f);
		g_StagePanel[i].direction = D_RIGHT;
		g_StagePanel[i].moving = false;
		g_StagePanel[i].NowLane = i+3;
	}
	
	g_StagePanel[1].size = D3DXVECTOR2(395.0f, 395.0f);;
	g_StagePanel[10].NowLane =PLANE_1;

	//�����t�@�C����ǂݍ���Ŏ��ʎq���󂯎��
	//g_BGMNo = LoadSound((char*)"data/BGM/BGM_Title.wav");

	//BGM�̍Đ��i2�ڂ̈����̓��[�v�񐔁j
	//���[�v�񐔂ɕ��̒l���w�肷��Ɩ������[�v
	//PlaySound(g_BGMNo, -1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStageSelect(void)
{
	StopSound(g_BGMNo);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStageSelect(void)
{
	//�G���^�[�L�[�������ꂽ��SCENE_GAME�ֈڍs����
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		
		SceneTransition(SCENE_GAME);
		//SceneTransition(NowSelect+6);
	}
	//�R���g���[���[B�{�^����������SCENE_GAME�ֈڍs
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		SceneTransition(SCENE_GAME);
		//SceneTransition(NowSelect+6);
	}
	for (int i = 0; i < STAGE_MAX; i++)
	{
		//�X�e�B�b�N�ňړ�
		if ((GetThumbLeftX(0) < -0.3f) &&(g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//�ړ���
			g_StagePanel[i].NowLane++;
			g_StagePanel[i].spd = 60.0f;			//�X�s�[�h��+��
			g_StagePanel[i].direction = D_RIGHT;		//�E�ړ�

		}
		//��
		if ((GetThumbLeftX(0) > 0.3f) && (g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//�ړ���
			g_StagePanel[i].NowLane--;
			g_StagePanel[i].spd = -60.0f;		//�X�s�[�h��-��
			g_StagePanel[i].direction = D_LEFT;		//���ړ�
		}

		//D�L�[�ŉE�ړ�
		if ((Keyboard_IsKeyDown(KK_D)) && (g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//�ړ���
			g_StagePanel[i].NowLane--;
			g_StagePanel[i].spd = -60.0f;		//�X�s�[�h��-��
			g_StagePanel[i].direction = D_LEFT;		//���ړ�

		}

		//A�L�[ �ō��ړ�
		if ((Keyboard_IsKeyDown(KK_A)) && (g_StagePanel[i].moving == false))
		{
			g_StagePanel[i].moving = true;				//�ړ���
			g_StagePanel[i].NowLane++;
			g_StagePanel[i].spd = 60.0f;			//�X�s�[�h��+��
			g_StagePanel[i].direction = D_RIGHT;		//�E�ړ�
		}

		//�I���ړ�
		if ((g_StagePanel[i].moving))
		{
			g_StagePanel[i].pos.x += g_StagePanel[i].spd;	//�X�s�[�h�𑫂��Ĉړ�
			g_StagePanel[i].spd *= 0.9f;			//�X�s�[�h����
			if (g_StagePanel[i].NowLane == PLANE_3)
			{
				g_StagePanel[i].size.x += 7.0f;
				g_StagePanel[i].size.y += 7.0f;
			}
			else
			{
				g_StagePanel[i].size.x = 300.0f;
				g_StagePanel[i].size.y = 300.0f;
			}
		}

		//�E�ړ�����
		if ((g_StagePanel[i].spd <= 15.0f) && (g_StagePanel[i].direction == D_RIGHT))
		{
			g_StagePanel[i].pos.x = -480.0f*2 + g_StagePanel[i].NowLane * 480.0f;	//���[���̒��S��
			g_StagePanel[i].moving = false;
			NowSelect++;	//�I���X�e�[�W�ύX
		}
		//���ړ�����
		if ((g_StagePanel[i].spd >= -15.0f) && (g_StagePanel[i].direction == D_LEFT))
		{
			g_StagePanel[i].pos.x = -480.0f*2 + g_StagePanel[i].NowLane * 480.0f;	//���[���̒��S��
			g_StagePanel[i].moving = false;
			NowSelect--;	//�I���X�e�[�W�ύX
		}

		if (g_StagePanel[i].NowLane == PLANE_3)
		{
			g_StagePanel[i].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		}
		else
		{
			g_StagePanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}

		if (g_StagePanel[i].NowLane == PLANE_11)
		{
			g_StagePanel[i].NowLane = PLANE_0;
		}
		if (g_StagePanel[i].NowLane == PLANE_MIN)
		{
			g_StagePanel[i].NowLane = PLANE_10;
		}


	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStageSelect(void)
{
	//�w�i�\��
	DrawSpriteLeftTop(g_TextureBgStageSelect[0], 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);
	DrawSpriteLeftTop(g_TextureBgStageSelect[1], 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	//�X�e�[�W�p�l���̕\��
	for (int i = 0; i < STAGE_MAX; i++)
	{
		//DrawSpriteLeftTop(g_StagePanel[i].texno, 0.0f, 0.0f, g_StagePanel[i].size.x, g_StagePanel[i].size.y,
		//	0.0f, 0.0f, 1.0f, 1.0);
		
		DrawSpriteColor(g_StagePanel[i].texno, g_StagePanel[i].pos.x, g_StagePanel[i].pos.y, g_StagePanel[i].size.x, g_StagePanel[i].size.y,
			0.0f, 0.0f, 1.0f, 1.0, g_StagePanel[i].col);
	}
}
