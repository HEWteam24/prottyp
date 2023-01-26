/*==============================================================================
	
	bg.cpp

--------------------------------------------------------------------------------

==============================================================================*/
#include "bg.h"
#include "tuto.h"
#include "texture.h"
#include "sprite.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VERTEX 4	//�K�v�Ȓ��_�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_TextureBg;	//�w�i�e�N�X�`��
static int g_TextureUIBack;
static int g_TextureUICtrl;
bool tutoFlag;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBG(int StageNum)
{
	tutoFlag = false;
	ID3D11Device *pDevice = GetDevice();

	g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
	g_TextureUIBack = LoadTexture((char*)"data/TEXTURE/UI_Back_B.png");
	g_TextureUICtrl = LoadTexture((char*)"data/TEXTURE/UI_ctrl.png");
	
	switch (StageNum)
	{
	default:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
		break;

	case 0:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/Bg_Tuto.png");
		tutoFlag = true;
		break;
	case 1:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_SeaCity.png");
		break;
	case 2:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
		break;
	case 3:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_SeaRock.png");
		break;
	case 4:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_Bubbles.png");
		break;
	case 5:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
		break;
	case 6:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_River.png");
		break;
	case 7:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_SeaCity.png");
		break;
	case 8:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_SeaRock.png");
		break;
	case 9:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_Bubbles.png");
		break;
	case 10:
		g_TextureBg = LoadTexture((char*)"data/TEXTURE/BG_Space.png");
		break;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBG(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBG(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBG(void)
{
	T_CIRCLE* pTuto = GetTuto();

	DrawSprite(g_TextureBg, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteColor(g_TextureUIBack, 0.0f + 200.0f, CENTER_Y, 400.0f, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 0.4));

	DrawSpriteColor(g_TextureUIBack, SCREEN_WIDTH - 200.0f, CENTER_Y, 400.0f, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 0.4));
	if (tutoFlag)
	{
		if (pTuto->Phase >= 7)
		{
			DrawSpriteColor(g_TextureUICtrl, 0.0f + 200.0f, CENTER_Y - 250.0f, 500.0f * 0.8f, (350.0f * 0.8f) / 3.0f,
				0.0f, (1.0f / 3.0f) * 1.0f, 1.0f, (1.0f / 3.0f), D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
		if (pTuto->Phase >= 12)
		{
			DrawSpriteColor(g_TextureUICtrl, 0.0f + 200.0f, CENTER_Y - 250.0f - ((350.0f * 0.8f) / 2.0f), 500.0f * 0.8f, (350.0f * 0.8f)/3.0f,
				0.0f, (1.0f / 3.0f) * 0.0f, 1.0f, (1.0f / 3.0f), D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
		if (pTuto->Phase >= 17)
		{
			DrawSpriteColor(g_TextureUICtrl, 0.0f + 200.0f, CENTER_Y - 250.0f + ((350.0f * 0.8f) / 2.0f), 500.0f * 0.8f, (350.0f * 0.8f)/3.0f,
				0.0f, (1.0f / 3.0f) * 2.0f, 1.0f, (1.0f / 3.0f), D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}

	}
	else
	{
		DrawSpriteColor(g_TextureUICtrl, 0.0f + 200.0f, CENTER_Y - 250.0f, 500.0f * 0.8f, 350.0f * 0.8f,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	}
}
