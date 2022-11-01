#include "combo.h"
#include "texture.h"
#include "sprite.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
COMBO	g_Combo[COMBO_DIGIT];

static	ID3D11ShaderResourceView	*g_ComboTexture;//画像1枚で1つの変数が必要
static	char	*g_TextureNameCombo = COMBO_TEX;//テクスチャファイルパス JPG BMP PNG

int		ComboAdd;
float	ComboTexno;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCombo()
{
	for (int i = 0; i < COMBO_DIGIT; i++) 
	{
		g_Combo[i].pos = D3DXVECTOR2(COMBO_POS_X, COMBO_POS_Y);	//位置
		g_Combo[i].size = D3DXVECTOR2(COMBO_SIZE_X, COMBO_SIZE_Y);	//サイズ
		g_Combo[i].col = D3DXCOLOR(1.0, 0.0, 0.0, 1.0);
		g_Combo[i].combonum = 0;					//コンボ数
	}

	ComboTexno = LoadTexture(g_TextureNameCombo);
	if (ComboTexno == -1)
	{//ロードエラー
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
