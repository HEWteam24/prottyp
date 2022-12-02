/*==============================================================================

   �^�C�g����ʏ��� [StageSelect.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "skill_select.h"
#include "special.h"
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
int NowSSelect = SKILL_1;
float Salpha;
float Scolor;
int changeN;
bool movingSp;
SKILL_PANEL g_SkillPanel[SKILL_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSkillSelect(void)
{
	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_TextureBgStageSelect[0] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");
	g_TextureBgStageSelect[1] = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");

	g_SkillPanel[SKILL_0].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel0.png");
	g_SkillPanel[SKILL_1].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel1.png");
	g_SkillPanel[SKILL_2].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel2.png");
	//g_SkillPanel[STAGE_6].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel6.png");
	//g_SkillPanel[STAGE_7].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel7.png");
	//g_SkillPanel[STAGE_8].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel8.png");
	//g_SkillPanel[STAGE_9].texno = LoadTexture((char*)"data/TEXTURE/Stage_Panel9.png");
	//g_SkillPanel[STAGE_10].texno= LoadTexture((char*)"data/TEXTURE/Stage_Panel10.png");

	//�\���̂̏�����
	for (int i = 0; i < SKILL_MAX; i++)
	{
		g_SkillPanel[i].pos = D3DXVECTOR2((CENTER_X-480.0f)+i*480.f, CENTER_Y - 50.0f);
		g_SkillPanel[i].spd = 10.0f;
		g_SkillPanel[i].size = D3DXVECTOR2(300.0f, 300.0f);
		g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SkillPanel[i].direction = SD_RIGHT;
		g_SkillPanel[i].moving = false;
	}

	g_SkillPanel[1].size = D3DXVECTOR2(395.0f, 395.0f);;

	Salpha = 1.0f;
	Scolor = 1.0f;
	changeN = 60;

	NowSSelect = 1;
	movingSp = false;
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
void UninitSkillSelect(void)
{
	StopSound(g_BGMNo);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSkillSelect(void)
{
	SPECIAL* pSp = GetSpecial();

	//�G���^�[�L�[�������ꂽ��SCENE_GAME�ֈڍs����
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		pSp->type = NowSSelect;
		SceneTransition(SCENE_GAME);
		//SceneTransition(NowSSelect+6);
	}
	//�R���g���[���[B�{�^����������SCENE_GAME�ֈڍs
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		SceneTransition(SCENE_GAME);
		//SceneTransition(NowSSelect+6);
	}
	for (int i = 0; i < SKILL_MAX; i++)
	{
		if ((Keyboard_IsKeyDown(KK_D)) && (movingSp == false) && (NowSSelect < 2))
		{
			NowSSelect+=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
		}
		if ((Keyboard_IsKeyDown(KK_A)) && (movingSp == false) && (NowSSelect > 0))
		{
			NowSSelect-=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
		}
		
		if (i == NowSSelect)
		{
			g_SkillPanel[i].size = D3DXVECTOR2(395.0f,395.0f);
			g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			g_SkillPanel[i].size = D3DXVECTOR2(340.0f, 340.0f);
			g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		}	

		if (movingSp==true)
		{
			changeN -= 1;
			if (changeN <= 0)
			{
				changeN = 30;
				//g_SkillPanel[i].moving = false;
				movingSp = false;
			}
		}
	}

	if (NowSSelect >= 3)
	{
		NowSSelect = 0;
	}
	if (NowSSelect <= -1)
	{
		NowSSelect = 2;
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSkillSelect(void)
{
	//�w�i�\��
	DrawSpriteColor(g_TextureBgStageSelect[1], CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_WIDTH,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
	DrawSpriteColor(g_TextureBgStageSelect[0], CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_WIDTH,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.6f, 0.6f, 0.6f, Salpha));


	//�X�e�[�W�p�l���̕\��
	for (int i = 0; i < SKILL_MAX; i++)
	{
		//DrawSpriteLeftTop(g_SkillPanel[i].texno, 0.0f, 0.0f, g_SkillPanel[i].size.x, g_SkillPanel[i].size.y,
		//	0.0f, 0.0f, 1.0f, 1.0);

			DrawSpriteColor(g_SkillPanel[i].texno, g_SkillPanel[i].pos.x, g_SkillPanel[i].pos.y, g_SkillPanel[i].size.x, g_SkillPanel[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0, g_SkillPanel[i].col);
	}
}
