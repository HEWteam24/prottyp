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

#define RING_SIZE  (400.0f)
#define ICON_SIZE  (340.0f)
#define ICON_ZOOM  (1.16f)
#define ICON_SPACE (480.0f)
#define ICON_POS_Y (CENTER_Y-50.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


static int g_TextureBgStageSelect;//�w�i�p�e�N�X�`���̎��ʎq
static int g_TextureRing;
static int g_BGMNo;//BGM�̎��ʎq

int NowSSelect = SKILL_1;

float RingRot;	//�����O�p�x
float RingPosX;	//�����O�T�C�Y

int changeN;	//�ړ��P�\
bool movingSp;	//�ړ��t���O

SKILL_PANEL g_SkillPanel[SKILL_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSkillSelect(void)
{
	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_TextureBgStageSelect = LoadTexture((char*)"data/TEXTURE/Back_Select.JPG");

	g_SkillPanel[SKILL_0].texno = LoadTexture((char*)"data/TEXTURE/icon_heal.png");
	g_SkillPanel[SKILL_1].texno = LoadTexture((char*)"data/TEXTURE/icon_damage.png");
	g_SkillPanel[SKILL_2].texno = LoadTexture((char*)"data/TEXTURE/icon_protect.png");

	g_TextureRing = LoadTexture((char*)"data/TEXTURE/icon_ring.png");

	//�\���̂̏�����
	for (int i = 0; i < SKILL_MAX; i++)
	{
		g_SkillPanel[i].pos = D3DXVECTOR2((CENTER_X-ICON_SPACE)+i*ICON_SPACE, ICON_POS_Y);
		g_SkillPanel[i].size = D3DXVECTOR2(ICON_SIZE, ICON_SIZE);
		g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SkillPanel[i].moving = false;
	}

	changeN = 60;

	RingRot = 0.0f;
	RingPosX = 0.0f;

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
	//StopSound(g_BGMNo);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSkillSelect(void)
{
	SPECIAL* pSp = GetSpecial();

	//SCENE_GAME��
	//�G���^�[�L�[
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		pSp->type = NowSSelect;
		SceneTransition(SCENE_GAME);
	}
	//�R���g���[���[B�{�^��
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		pSp->type = NowSSelect;
		SceneTransition(SCENE_GAME);
	}

	
	for (int i = 0; i < SKILL_MAX; i++)
	{
		//�E���ɑI���ړ�
		if (((GetThumbLeftX(0) > 0.3f)||(Keyboard_IsKeyDown(KK_D))) && (movingSp == false) && (NowSSelect < 2))
		{
			NowSSelect+=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
		}
		//�����ɑI���ړ�
		if (((GetThumbLeftX(0) < -0.3f) || (Keyboard_IsKeyDown(KK_A))) && (movingSp == false) && (NowSSelect > 0))
		{
			NowSSelect-=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
		}
		
		//�I������Ă���g�� & ����ĂȂ�������k��
		if (i == NowSSelect)
		{
			g_SkillPanel[i].size = D3DXVECTOR2(ICON_SIZE * ICON_ZOOM, ICON_SIZE * ICON_ZOOM);
			g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			g_SkillPanel[i].size = D3DXVECTOR2(ICON_SIZE,ICON_SIZE);
			g_SkillPanel[i].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.6f);
		}	

		//�I���ړ��P�\
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

	//�Z���N�g���߂�}����
	if (NowSSelect >= 3)
	{
		NowSSelect = 0;
	}
	if (NowSSelect <= -1)
	{
		NowSSelect = 2;
	}

	//�����O�̏���
	RingRot += 0.5f;
	RingPosX = (CENTER_X - ICON_SPACE) + NowSSelect * ICON_SPACE;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSkillSelect(void)
{
	//�w�i�\��
	DrawSpriteColor(g_TextureBgStageSelect, CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_WIDTH,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�X�L���A�C�R���̕\��
	for (int i = 0; i < SKILL_MAX; i++)
	{
			DrawSpriteColor(g_SkillPanel[i].texno, g_SkillPanel[i].pos.x, g_SkillPanel[i].pos.y, g_SkillPanel[i].size.x, g_SkillPanel[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0, g_SkillPanel[i].col);
	}

	//�����O
	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRing));
	DrawSpriteColorRotation(
		RingPosX,
		ICON_POS_Y,
		RING_SIZE,
		RING_SIZE,
		RingRot,
		D3DXCOLOR(0.0f, 0.8f, 0.6f, 1.0f),
		0.0f,
		1.0f,
		1.0f,
		1
	);

	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRing));
	DrawSpriteColorRotation(
		RingPosX,
		ICON_POS_Y,
		RING_SIZE*1.15,
		RING_SIZE*1.15,
		RingRot*-1.5,
		D3DXCOLOR(0.0f, 1.0f, 0.8f, 1.0f),
		0.0f,
		1.0f,
		1.0f,
		1
	);
}
