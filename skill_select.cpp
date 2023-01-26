/*==============================================================================

   �^�C�g����ʏ��� [StageSelect.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "skill_select.h"
#include "stage_select.h"
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

#define RING_SIZE  (340.0f)
#define ICON_SIZE  (300.0f)
#define ICON_ZOOM  (1.16f)
#define ICON_SPACE (320.0f)
#define ICON_POS_Y (CENTER_Y-120.0f)
#define PLATE_SIZE (260.0f)
#define PLATE_POS  (CENTER_X*1.46f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


static int g_TextureBgStageSelect;//�w�i�p�e�N�X�`���̎��ʎq
static int g_TextureRing;
static int g_TextureBPM;
static int g_TextureSkillPlate;
static int g_TextureTextArrow;

static int g_SE_SpSelect;
static int g_BGMNo;//BGM�̎��ʎq

int NowSSelect = SKILL_1;

float RingRot;	//�����O�p�x
float RingPosY;	//�����O�ʒu
float TextPosX; //�������ʒu
float TextAlpha;
float BPMSize;
float BPMAdd;
float BackRingrot;

int changeN;	//�ړ��P�\
bool movingSp;	//�ړ��t���O

D3DXCOLOR BackRingCol;
SKILL_PANEL g_SkillPanel[SKILL_MAX];

//=============================================================================
// ����������
//=============================================================================
HRESULT InitSkillSelect(void)
{
	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_TextureBgStageSelect = LoadTexture((char*)"data/TEXTURE/fade_white.png");

	g_SkillPanel[SKILL_0].texno = LoadTexture((char*)"data/TEXTURE/icon_heal.png");
	g_SkillPanel[SKILL_1].texno = LoadTexture((char*)"data/TEXTURE/icon_damage.png");
	g_SkillPanel[SKILL_2].texno = LoadTexture((char*)"data/TEXTURE/icon_protect.png");

	g_TextureSkillPlate = LoadTexture((char*)"data/TEXTURE/skill_plate.png");
	g_TextureTextArrow = LoadTexture((char*)"data/TEXTURE/arrow.png");

	g_TextureRing = LoadTexture((char*)"data/TEXTURE/icon_ring.png");
	g_TextureBPM = LoadTexture((char*)"data/TEXTURE/UI_BPM_B.png");

	char	file_SE_SpSelect[] = "data\\SE\\SE_MenuMove.wav";
	g_SE_SpSelect = LoadSound(file_SE_SpSelect);

	//�\���̂̏�����
	for (int i = 0; i < SKILL_MAX; i++)
	{
		g_SkillPanel[i].pos = D3DXVECTOR2(CENTER_X*2.25, (CENTER_Y - ICON_SPACE) + i * ICON_SPACE);
		g_SkillPanel[i].size = D3DXVECTOR2(ICON_SIZE, ICON_SIZE);
		g_SkillPanel[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SkillPanel[i].moving = false;
	}
	BackRingCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	changeN = 60;

	RingRot		= 0.0f;
	RingPosY	= 0.0f;
	BPMSize		= 300.0f;
	BPMAdd		= 1.5f;
	BackRingrot = 0.0f;
	TextPosX	= PLATE_POS;
	TextAlpha	= 0.0f;

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
		//SceneTransition(SCENE_GAME);
	}
	//�R���g���[���[B�{�^��
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		pSp->type = NowSSelect;
		//SceneTransition(SCENE_GAME);
	}
	
	for (int i = 0; i < SKILL_MAX; i++)
	{
		if (g_SkillPanel[i].pos.x > CENTER_X*1.785f)
		{
			g_SkillPanel[i].pos.x -= 50.0f;
		}

	//�����ɑI���ړ�
		if (((GetThumbLeftY(0) < -0.3f)||(Keyboard_IsKeyDown(KK_S))|| (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN))) && (movingSp == false) && (NowSSelect < 2))
		{
			NowSSelect+=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
			TextAlpha = 0.0f;
			TextPosX = CENTER_X * 1.5;
			PlaySound(g_SE_SpSelect, 0);
		}
	//�㑤�ɑI���ړ�
		if (((GetThumbLeftY(0) > 0.3f) || (Keyboard_IsKeyDown(KK_W)) || (IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP))) && (movingSp == false) && (NowSSelect > 0))
		{
			NowSSelect-=1;
			//g_SkillPanel[i].moving = true;
			movingSp = true;
			TextAlpha = 0.0f;
			TextPosX = CENTER_X * 1.5;
			PlaySound(g_SE_SpSelect, 0);
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
			g_SkillPanel[i].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		}	

	//�I���ړ��P�\
		if (movingSp==true)
		{
			changeN -= 1;
			if (changeN <= 0)
			{
				changeN = 30;
				movingSp = false;
			}
		}

	//�������̃t�F�[�h
		if (TextAlpha < 1.0f)
		{
			TextAlpha += 0.025f;
		}
		if (TextPosX > PLATE_POS)
		{
			TextPosX -= 15.0f;
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
	BackRingrot += 0.5f;
	RingPosY = (CENTER_Y - ICON_SPACE) + NowSSelect * ICON_SPACE;

	BPMSize += BPMAdd;
	if ((BPMSize >= 310.0f)|| (BPMSize <= 290.0f))
	{
		BPMAdd *= -1;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSkillSelect(void)
{
	int sStageNum = GetGemeStageNum();
	if (sStageNum>=5)
	{
		BPMSize += BPMAdd;
		BackRingCol = D3DXCOLOR(0.5f, 0.1f, 0.1f, 1.0f);
		BackRingrot += 3.5f;
		DrawSpriteColor(g_TextureBPM, CENTER_X, CENTER_Y, BPMSize, BPMSize / 6.0f * 5.0f,
			0.5f, 0.0f, 0.5f, 1.0f, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f));
	}
	else
	{
		BackRingCol = D3DXCOLOR(0.1f, 0.5f, 0.1f, 1.0f);
		DrawSpriteColor(g_TextureBPM, CENTER_X, CENTER_Y, BPMSize, BPMSize / 6.0f * 5.0f,
			0.0f, 0.0f, 0.5f, 1.0f,D3DXCOLOR(0.2f, 0.9f, 0.2f, 1.0f));
	}
	//�����O
	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRing));
	DrawSpriteColorRotation(
		CENTER_X,
		CENTER_Y,
		RING_SIZE*3.0f,
		RING_SIZE*3.0f,
		BackRingrot*-1.0f,
		BackRingCol,
		0.0f,
		1.0f,
		1.0f,
		1
	);
	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRing));
	DrawSpriteColorRotation(
		CENTER_X,
		CENTER_Y,
		RING_SIZE * 2.7f,
		RING_SIZE * 2.7f,
		BackRingrot * -1.5f,
		BackRingCol,
		0.0f,
		1.0f,
		1.0f,
		1
	);

	//����
	DrawSpriteColor(g_TextureSkillPlate,TextPosX, RingPosY, PLATE_SIZE * 2, PLATE_SIZE,
		0.0f, 1.0f / 3 * NowSSelect - 1, 1.0f, 1.0f / 3.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, TextAlpha));

	if (NowSSelect < 2)
	{
		DrawSpriteColor(g_TextureTextArrow, TextPosX, RingPosY + (PLATE_SIZE / 2) + 30.0f, 80.0f, 80.0f,
			0.25f * 3, 0.0f, 0.25f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, TextAlpha));
	}
	if (NowSSelect > 0)
	{
		DrawSpriteColor(g_TextureTextArrow, TextPosX, RingPosY - (PLATE_SIZE / 2) - 30.0f, 80.0f, 80.0f,
			0.25f * 2, 0.0f, 0.25f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, TextAlpha));
	}



	//�X�L���A�C�R���̕\��
	for (int i = 0; i < SKILL_MAX; i++)
	{
			DrawSpriteColor(g_SkillPanel[i].texno, g_SkillPanel[i].pos.x, g_SkillPanel[i].pos.y, g_SkillPanel[i].size.x, g_SkillPanel[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0f, g_SkillPanel[i].col);
	}


	//�����O
	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRing));
	DrawSpriteColorRotation(
		g_SkillPanel[0].pos.x,
		RingPosY,
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
		g_SkillPanel[0].pos.x,
		RingPosY,
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
