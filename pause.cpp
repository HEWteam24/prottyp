/*==============================================================================

   �|�[�Y�̐��� [pause.cpp]
														 Author :�@�ēc �S��
														 Date   :�@12/13
--------------------------------------------------------------------------------
P�{�^���Ń|�[�Y(ESC�̓R���\�[�����I�����邩��ł��Ȃ�����)

W��S�ŋ@�\�̑I��(�ォ��R���e�B�j���[�A���g���C�A�^�C�g����ʂɖ߂�)

ENTER�ŋ@�\�̎��s�ł��B

����̂��߂ɍ��܂ł�ENTER�Ń^�C�g���ɖ߂�́uG�L�[�v�ɓ�����ڂ��Ă��܂��B
*/

//==============================================================================

#include "pause.h"

static int PauseTexture;
static int PauseTextTexture;
static int PauseCntTexture;
static int RetryTexture;
static int BackTexture;
static int ContinueTexture;
static int ArrowTexture;

int arrowNum;
float num;
bool already;

PAUSE hoge;

void InitPause()
{
	PauseTexture = LoadTexture((char*)"data/TEXTURE/UI_Back_B.png");
	PauseTextTexture = LoadTexture((char*)"data/TEXTURE/text_pause.png");
	PauseCntTexture = LoadTexture((char*)"data/TEXTURE/number.png");
	RetryTexture = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	BackTexture = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	ContinueTexture = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	ArrowTexture = LoadTexture((char*)"data/TEXTURE/notes_right.png");

	hoge.pause = false;		//PAUSE�����ǂ����̔���
	hoge.restart = false;	//�R���e�B�j���[����
	hoge.pause_frame = 0;	//PAUSE���畜�A����܂ł̎���(3�b)
	hoge.PauseAction = 0;	//PAUSE�őI�������@�\�A�y�і��̏ꏊ(Continue�ARetry�ABackTitle)
	already = false;		//PAUSE��UI�̑����Trriger�����邽�߂̃t���O
}

void UninitPause()
{
	hoge.pause = false;
	hoge.restart = false;
	hoge.pause_frame = 0;
	hoge.PauseAction = 0;
	already = false;
}


void UpdatePause()
{
	//�R���e�B�j���[�̏���
	//
	if (hoge.restart == true)
	{
		hoge.pause_frame++;
	}

	if (hoge.pause_frame == 180)
	{
		hoge.pause_frame = 0;
		hoge.restart = false;
		hoge.pause = false;
		RePlaySound(BGM_RE());
	}

	if (Keyboard_IsKeyDown(KK_W) && already == false)
	{

		already = true;

		hoge.PauseAction -= 1;

		if (hoge.PauseAction == -1)
		{
			hoge.PauseAction = eBack;
		}


	}

	if (Keyboard_IsKeyDown(KK_S) && already == false)
	{
		already = true;

		hoge.PauseAction += 1;
		if (hoge.PauseAction == 3)
		{
			hoge.PauseAction = eContinue;
		}

	
	}

	if (Keyboard_IsKeyUp(KK_S) && Keyboard_IsKeyUp(KK_W))
	{
		already = false;
	}


	if (Keyboard_IsKeyDown(KK_P) && hoge.pause == false)
	{
		PauseSound(BGM_RE());
		hoge.pause = true;
	}



	if (Keyboard_IsKeyDown(KK_ENTER) && hoge.pause == true)
	{
		switch (hoge.PauseAction)
		{
		case eContinue:
			hoge.restart = true;
			break;

		case eReTry:
			ReTry();
			break;
		case eBack:
			Back();
			break;
		}
	}
}

void DrawPause()
{


	if (hoge.pause == true)
	{
		//�Ó]
		DrawSpriteColor(PauseTexture,
			0.0f,
			0.0f,
			10000.0f,
			10000.0f,
			0.0f,
			0.0f,
			1.0f,
			1.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));

		//pause�e�L�X�g
		if (hoge.restart == false)
		{
			DrawSpriteColor(PauseTextTexture,
				CENTER_X,
				CENTER_Y - 300,
				400.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//������
		if (hoge.restart == false)
		{
			DrawSpriteColor(ContinueTexture,
				CENTER_X,
				CENTER_Y - 150,
				500.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}

		//���g���C
		if (hoge.restart == false)
		{
			DrawSpriteColor(RetryTexture,
				CENTER_X,
				CENTER_Y,
				500.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
		}

		//back
		if (hoge.restart == false)
		{
			DrawSpriteColor(BackTexture,
				CENTER_X,
				CENTER_Y + 150,
				500.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		}

		//���
		if (hoge.restart == false)
		{
			DrawSpriteColor(ArrowTexture,
				CENTER_X / 2 + 150,
				CENTER_Y - 150 + (hoge.PauseAction * 150),
				100.0f,
				100.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}




	if (hoge.restart == true)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1,
			GetTexture(PauseCntTexture));
		for (int i = 0; i < SCOER_DIGIT; i++) {
			DrawSpriteColorRotation(
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2,
				300.0f,
				300.0f,
				0.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				(3.0f - (hoge.pause_frame / 60)),
				0.2f,
				0.2f,
				5
			);
		}
	}
}

void ReTry()
{
	SceneTransition(SCENE_GAME);
}

void Back()
{ 
	SceneTransition(SCENE_TITLE);
}

PAUSE* GetPause()
{
	return &hoge;
}