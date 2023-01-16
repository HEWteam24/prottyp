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
int dist;

PAUSE hoge;
D3DXCOLOR COL[3];

void InitPause()
{
	PauseTexture = LoadTexture((char*)"data/TEXTURE/UI_Back_B.png");
	PauseTextTexture = LoadTexture((char*)"data/TEXTURE/text_pause.png");
	PauseCntTexture = LoadTexture((char*)"data/TEXTURE/number.png");
	RetryTexture = LoadTexture((char*)"data/TEXTURE/text_pause_Set.png");
	BackTexture = LoadTexture((char*)"data/TEXTURE/text_pause_Set.png");
	ContinueTexture = LoadTexture((char*)"data/TEXTURE/text_pause_Set.png");
	ArrowTexture = LoadTexture((char*)"data/TEXTURE/arrow.png");

	hoge.pause = false;		//PAUSE�����ǂ����̔���
	hoge.restart = false;	//�R���e�B�j���[����
	hoge.pause_frame = 0;	//PAUSE���畜�A����܂ł̎���(3�b)
	hoge.PauseAction = 0;	//PAUSE�őI�������@�\�A�y�і��̏ꏊ(Continue�ARetry�ABackTitle)
	hoge.alpha = 0.7f;		//�Ó]�
	already = false;		//PAUSE��UI�̑����Trriger�����邽�߂̃t���O

	COL[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	COL[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	COL[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	dist = 20;
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

	if ((Keyboard_IsKeyDown(KK_W)|| (GetThumbLeftY(0) > 0.3f)) && already == false)
	{

		already = true;

		hoge.PauseAction -= 1;

		if (hoge.PauseAction == -1)
		{
			hoge.PauseAction = eBack;
		}


	}

	if ((Keyboard_IsKeyDown(KK_S) || (GetThumbLeftY(0) < -0.3f)) && already == false)
	{
		already = true;

		hoge.PauseAction += 1;
		if (hoge.PauseAction == 3)
		{
			hoge.PauseAction = eContinue;
		}

	
	}

	//if (Keyboard_IsKeyUp(KK_S) && Keyboard_IsKeyUp(KK_W))
	//{
	//	already = false;
	//}
	
	if (already)
	{
		dist -= 1;
	}

	if (dist <= 0)
	{
		dist = 20;
		already = false;
	}


	if ((Keyboard_IsKeyDown(KK_P)|| (IsButtonTriggered(0, XINPUT_GAMEPAD_START))) && hoge.pause == false)
	{
		PauseSound(BGM_RE());
		hoge.pause = true;
	}



	if ((Keyboard_IsKeyDown(KK_ENTER)|| (IsButtonTriggered(0, XINPUT_GAMEPAD_B))) && hoge.pause == true)
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

	switch (hoge.PauseAction)
	{
	case eContinue:
		COL[0] = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		COL[1] = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		COL[2] = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		break;

	case eReTry:
		COL[0] = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		COL[1] = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		COL[2] = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		break;

	case eBack:
		COL[0] = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		COL[1] = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		COL[2] = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		break;
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
			D3DXCOLOR(1.0f, 1.0f, 1.0f, hoge.alpha));

		//pause�e�L�X�g
		if (hoge.restart == false)
		{
			DrawSpriteColor(PauseTextTexture,
				CENTER_X,
				CENTER_Y - 400,
				500.0f,
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
				1.0f/3,
				COL[0]);
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
				1.0f/3,
				1.0f,
				1.0f/3,
				COL[1]);
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
				1.0f/3*2,
				1.0f,
				1.0f/3,
				COL[2]);
		}

		//���
		if (hoge.restart == false)
		{
			DrawSpriteColor(ArrowTexture,
				CENTER_X / 2 + 150,
				CENTER_Y - 150 + (hoge.PauseAction * 150),
				100.0f,
				100.0f,
				0.25f,
				0.0f,
				0.25f,
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
	SceneTransition(SCENE_STAGESELECT);
}

PAUSE* GetPause()
{
	return &hoge;
}