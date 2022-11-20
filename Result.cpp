/*==============================================================================

   �^�C�g����ʏ��� [Result.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Result.h"
#include "texture.h"
#include "sprite.h"
//#include "input.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"

#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_TextureBgTitle;//�^�C�g����ʗp�e�N�X�`���̎��ʎq
static int g_TextureShishamo;
static int g_BGMNo;//�^�C�g���pBGM�̎��ʎq

float	Shishamo_pos;
float	Shishamo_spd;
bool	moving;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(void)
{
	g_TextureBgTitle = LoadTexture((char*)"data/TEXTURE/Back_Clear.png");
	g_TextureShishamo = LoadTexture((char*)"data/TEXTURE/Shishamo_end_1.png");
	InitScoreResult();

	Shishamo_pos = -450.0f;
	Shishamo_spd = 85.0f;
	moving = true;
	//g_BGMNo = LoadSound((char*)"data/BGM/BGM_Result.wav");
	//PlaySound(g_BGMNo, -1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	UninitScore();
	StopSound(g_BGMNo);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	//�G���^�[�L�[�������ꂽ��SCENE_TITLE�ֈڍs����
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_TITLE);
	}
	//�R���g���[���[B�{�^����������SCENE_TITLE�ֈڍs
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		SceneTransition(SCENE_TITLE);
	}

	//�L�����N�^�[�ړ�
	if (moving)
	{
		Shishamo_pos += Shishamo_spd;	//�X�s�[�h�𑫂��Ĉړ�
		Shishamo_spd *= 0.9f;			//�X�s�[�h����
	}

	//�E�ړ�����
	if (Shishamo_spd <= 1.0f)
	{
		//Shishamo_pos = 450.0f;	//���[���̒��S��
		moving = false;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	DrawSpriteLeftTop(g_TextureBgTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteColor(g_TextureShishamo, Shishamo_pos, CENTER_Y, 900.0f, 900.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));

	DrawScore();
}
