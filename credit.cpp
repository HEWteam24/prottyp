/*==============================================================================

   �N���W�b�g��ʏ��� [credit.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "credit.h"
#include "texture.h"
#include "sprite.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#define CREDIT_Y	(3800.0f)
float credit_nowY = SCREEN_HEIGHT + (CREDIT_Y / 2);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_TextureCredit;
static int g_TextureThankyou;

static int g_BGM_CREDIT;//�N���W�b�g�pBGM�̎��ʎq

float t_alfa = 0.0f;
bool credit = true;
bool thankyou = false;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitCredit(void)
{
	credit_nowY = SCREEN_HEIGHT + (CREDIT_Y / 2);
	t_alfa = 0.0f;
	credit = true;
	thankyou = false;

	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_TextureCredit = LoadTexture((char*)"data/TEXTURE/credit.png");
	g_TextureThankyou = LoadTexture((char*)"data/TEXTURE/thankyou.png");
	//�����t�@�C����ǂݍ���Ŏ��ʎq���󂯎��
	char	file_BGM_CREDIT[] = "data\\BGM\\credit_B.wav";
	g_BGM_CREDIT = LoadSound(file_BGM_CREDIT);

	//BGM�̍Đ��i2�ڂ̈����̓��[�v�񐔁j
	//���[�v�񐔂ɕ��̒l���w�肷��Ɩ������[�v
	PlaySound(g_BGM_CREDIT,0);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCredit(void)
{
	StopSound(g_BGM_CREDIT);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCredit(void)
{
	//�G���^�[�L�[�������ꂽ��SCENE_STAGESELECT�ֈڍs����
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_TITLE);
	}
	//�R���g���[���[B�{�^����������SCENE_STAGESELECT�ֈڍs
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_A) || IsButtonTriggered(0, XINPUT_GAMEPAD_B)|| IsButtonTriggered(0, XINPUT_GAMEPAD_X)|| IsButtonTriggered(0, XINPUT_GAMEPAD_Y)|| IsButtonTriggered(0, XINPUT_GAMEPAD_START))
	{
		SceneTransition(SCENE_TITLE);
	}

	if (credit_nowY - 700 >= -CREDIT_Y / 2)
	{
		credit_nowY--;
	}
	else
	{
		credit = false;
	}

	if (!credit && t_alfa <= 1.0f || thankyou && t_alfa <= 1.0f)
	{
		t_alfa += 0.002f;
	}
	else if(!thankyou && !credit)
	{
		thankyou = true;
		t_alfa = 0.0f;
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCredit(void)
{
	if (!thankyou)
	{
		DrawSpriteColor(g_TextureCredit, CENTER_X, credit_nowY, 1500.0f, CREDIT_Y,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - t_alfa));
	}
	else
	{
		DrawSpriteColor(g_TextureThankyou, CENTER_X, CENTER_Y, SCREEN_WIDTH, SCREEN_HEIGHT,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, t_alfa));
	}
}
