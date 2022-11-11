#include "combo.h"
#include "texture.h"
#include "sprite.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
COMBO	g_Combo[COMBO_DIGIT];
COMBOTEXT	g_ComboText;

static	ID3D11ShaderResourceView	*g_ComboTexture;//�摜1����1�̕ϐ����K�v
static	char	*g_TextureNameCombo = COMBO_TEX;//�e�N�X�`���t�@�C���p�X JPG BMP PNG

static	ID3D11ShaderResourceView* g_ComboTextTexture;//�摜1����1�̕ϐ����K�v
static	char* g_TextureNameComboText = (char*)"data\\texture\\text_combo.png";//�e�N�X�`���t�@�C���p�X JPG BMP PNG

int		ComboAdd;
float	ComboTexno;
float	ComboTextTexNo;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCombo()
{

	ComboTextTexNo = LoadTexture(g_TextureNameComboText);
	if (ComboTextTexNo == -1)
	{//���[�h�G���[
		exit(999);
	}

	g_ComboText.Pos = D3DXVECTOR2(COMBOTEXT_POS_X, COMBOTEXT_POS_Y);
	g_ComboText.Size = D3DXVECTOR2(COMBOTEXT_SIZE_X, COMBOTEXT_SIZE_Y);
	g_ComboText.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < COMBO_DIGIT; i++) 
	{
		g_Combo[i].pos = D3DXVECTOR2(COMBO_POS_X, COMBO_POS_Y);	//�ʒu
		g_Combo[i].size = D3DXVECTOR2(COMBO_SIZE_X, COMBO_SIZE_Y);	//�T�C�Y
		g_Combo[i].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.2);
		g_Combo[i].combonum = 0;					//�R���{��
	}

	ComboTexno = LoadTexture(g_TextureNameCombo);
	if (ComboTexno == -1)
	{//���[�h�G���[
		exit(999);
	}

	ComboAdd = 0;
	return S_OK;
}

void UninitCombo()
{
	if (g_ComboTexture)
	{
		g_ComboTexture->Release();
		g_ComboTexture = NULL;
	}
	if (g_ComboTextTexture)
	{
		g_ComboTextTexture->Release();
		g_ComboTextTexture = NULL;
	}
}

void UpdateCombo()
{
	GetComboDizit();
}

void DrawCombo()
{
	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(ComboTexno));
	for (int i = 0; i < COMBO_DIGIT; i++) {
		DrawSpriteColorRotation(
			g_Combo[i].pos.x,
			g_Combo[i].pos.y,
			g_Combo[i].size.x,
			g_Combo[i].size.y,
			0.0f,
			g_Combo[i].col,
			g_Combo[i].combonum,
			0.2f,
			0.2f,
			5
		);
	}
	//GetDeviceContext()->PSSetShaderResources(0, 1,
	//	GetTexture(ComboTextTexNo));

	//DrawSpriteColorRotation(
	//	g_ComboText.Pos.x,
	//	g_ComboText.Pos.y,
	//	g_ComboText.Size.x,
	//	g_ComboText.Size.y,
	//	0.0f,
	//	g_ComboText.col,
	//	0.0f,
	//	1.0f,
	//	1.0f,
	//	1
	//);
}

void ComboPlus(int combo)
{
	ComboAdd += combo;
}

void GetComboDizit()
{
	for (int i = 0; i < COMBO_DIGIT; i++) {
		int j, ComboDigit;
		j = i;
		ComboDigit = 10;
		while (j > 0)
		{
			ComboDigit *= 10;
			j--;
		}
		g_Combo[i].combonum = ComboAdd % ComboDigit / (ComboDigit / 10);
	}
}

void ResetCombo()
{
	ComboAdd = 0;
}

int GetComboScoreUp()
{
	int Up = 0;
	if (ComboAdd >= 10) {
		Up = ComboAdd / 10;
	}
	return Up;
}
