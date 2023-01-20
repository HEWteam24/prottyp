/*==============================================================================

   �^�C�g����ʏ��� [title.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "title.h"
#include "texture.h"
#include "sprite.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOGO_POS_Y	(300.0f)
#define LINE_DIST	(60.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_TextureBgTitle;//�^�C�g����ʗp�e�N�X�`���̎��ʎq
static int g_TextureFFF;
static int g_TextureLine;
static int g_TextureCommand;

float	lineX[2];
float	Fsize[3];
float	FposY[3];
bool	Fstate[3];
bool	change[3];

int FFFframe[3];
int FFFChange[3];

static int g_BGMNo;//�^�C�g���pBGM�̎��ʎq
static int g_SE;		//�e�T�E���h

int count = 0;
bool kakusicommand[11] = { false,false,false,false,false,false,false,false,false,false,false};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
{
	//�e�N�X�`����ǂݍ���Ŏ��ʎq���󂯎��
	g_TextureBgTitle = LoadTexture((char*)"data/TEXTURE/Title.png");
	g_TextureFFF = LoadTexture((char*)"data/TEXTURE/fff.png");
	g_TextureLine = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	g_TextureCommand = LoadTexture((char*)"data/TEXTURE/command.png");
	//�����t�@�C����ǂݍ���Ŏ��ʎq���󂯎��
	//g_BGMNo = LoadSound((char*)"data/BGM/BGM_Title.wav");
	char	file_SE[] = "data\\SE\\SE_bullet.wav";
	g_SE = LoadSound(file_SE);

	//BGM�̍Đ��i2�ڂ̈����̓��[�v�񐔁j
	//���[�v�񐔂ɕ��̒l���w�肷��Ɩ������[�v
	//PlaySound(g_BGMNo, -1);

	lineX[0] = CENTER_X/2*1;
	lineX[1] = CENTER_X/2*3;

	for (int i = 0; i < 3; i++)
	{
		Fsize[i] = 200.0f;
		FposY[i] = LOGO_POS_Y;
		Fstate[i]= false;
		change[i]=false;
		FFFframe[i] = 100+20*i;
		FFFChange[i] = 0;
	}

	for (int i = 0; i < 11; i++)
	{
		kakusicommand[i] = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	//StopSound(g_BGMNo);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	//�G���^�[�L�[�������ꂽ��SCENE_STAGESELECT�ֈڍs����
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_STAGESELECT);
	}
	//�R���g���[���[B�{�^����������SCENE_STAGESELECT�ֈڍs
	if (kakusicommand[7] == false && IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		SceneTransition(SCENE_STAGESELECT);
	}

	if (kakusicommand[9] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_START))
	{
		kakusicommand[10] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[8] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_A))
	{
		kakusicommand[9] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[7] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		kakusicommand[8] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[6] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		kakusicommand[7] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[5] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT))
	{
		kakusicommand[6] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[4] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		kakusicommand[5] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[3] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_LEFT))
	{
		kakusicommand[4] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[2] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN))
	{
		kakusicommand[3] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[1] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_DOWN))
	{
		kakusicommand[2] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[0] == true && IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP))
	{
		kakusicommand[1] = true;
		PlaySound(g_SE, 0);
	}
	else if (kakusicommand[0] == false && IsButtonTriggered(0, XINPUT_GAMEPAD_DPAD_UP))
	{
		kakusicommand[0] = true;
		PlaySound(g_SE, 0);
	}

	if (kakusicommand[10] == true)
	{
		for (int i = 0; i < 11; i++)
		{
			kakusicommand[i] = false;
		}
		SceneTransition(SCENE_STAGESELECT);
	}


	for (int i = 0; i < 2; i++)
	{
		lineX[i] -= 10.0f;
		if (lineX[i] <= 0.0f)
		{
			lineX[i] = CENTER_X * 2;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		FFFframe[i]++;

		if (FFFframe[i] == 300)
		{
			FFFframe[i] = 0;
			FFFChange[i] = true;
		}

		if (FFFChange[i])
		{
			if (Fsize[i] >= 0.1f)
			{
				Fsize[i] *= 0.9;
			}
			else
			{
				if (Fstate[i])
				{
					Fstate[i] = false;
				}
				else
				{
					Fstate[i] = true;
				}

				FFFChange[i] = false;
			}	
		}
		else
		{
			if (Fsize[i] <= 200.0f)
			{
				Fsize[i] *= 1.2;
			}
		}
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	DrawSpriteLeftTop(g_TextureBgTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f );

	DrawSpriteColor(g_TextureCommand, SCREEN_WIDTH - 150, SCREEN_HEIGHT - 50, 200.0f, 50.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(0.7f, 0.7f, 1.0f, 0.5f));

	//Line
	for (int i = 0; i < 5; i++)
	{
		DrawSpriteColor(g_TextureLine,
			CENTER_X, LOGO_POS_Y + LINE_DIST * (i-2),
			SCREEN_WIDTH, 10.0f,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0, 1.0, 1.0, 0.8));
	}

	for (int i = 0; i < 2; i++)
	{
		DrawSpriteColor(g_TextureLine,
			lineX[i], LOGO_POS_Y,
			10.0f, 60.0f*4.1,
			0.0f, 0.0f,
			1.0f, 1.0f,
			D3DXCOLOR(1.0, 1.0, 1.0, 0.8));
	}

	DrawSpriteColor(g_TextureLine,
		CENTER_X, LOGO_POS_Y-100.0f,
		700.0f, 15.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		D3DXCOLOR(0.0, 0.0, 0.0, 1.0));

	for (int i = 0; i < 3; i++)
	{
		if (Fstate[i])
		{
			DrawSpriteColor(g_TextureFFF,
				CENTER_X + (200.0f * (i - 1)), FposY[i],
				Fsize[i], 600.0f,
				0.5f, 1.0f,
				0.5f, 1.0f,
				D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
		else
		{
			DrawSpriteColor(g_TextureFFF,
				CENTER_X + (200.0f * (i - 1)), FposY[i],
				Fsize[i], 600.0f,
				0.0f, 0.0f,
				0.5f, 1.0f,
				D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}
}