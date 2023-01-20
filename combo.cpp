#include "combo.h"
#include "texture.h"
#include "sprite.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
COMBO	g_Combo[COMBO_DIGIT],g_ComboMag[4];
COMBOTEXT	g_ComboText;
D3DXCOLOR	MagColor[5]{
	D3DXCOLOR(0.6f,0.6f,0.6f,0.2f),
	D3DXCOLOR(1.0f,1.0f,1.0f,0.2f),
	D3DXCOLOR(0.0f,1.0f,0.0f,0.2f),
	D3DXCOLOR(1.0f,1.0f,0.0f,0.2f),
	D3DXCOLOR(1.0f,0.0f,0.0f,0.2f),
};

static	ID3D11ShaderResourceView	*g_ComboTexture;//画像1枚で1つの変数が必要
static	char	*g_TextureNameCombo = COMBO_TEX;//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_ComboTextTexture;//画像1枚で1つの変数が必要
static	char* g_TextureNameComboText = (char*)"data\\texture\\text_combo.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_MaxComboTextTexture;//画像1枚で1つの変数が必要
static	char* g_TextureNameMaxComboText = (char*)"data\\texture\\alphabet_01.png";//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_ComboMagTexture;//画像1枚で1つの変数が必要
static	char* g_TextureNameComboMag = (char*)"data\\texture\\number_03.png";//テクスチャファイルパス JPG BMP PNG

int		ComboAdd, ComboMagNum, ComboMax, ComboMaxTextureW[3], ComboMaxTextureH[3];
float	ComboTexno;
float	ComboTextTexNo;
float	MaxComboTextTexNo;
float	ComboMagTexNo;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitCombo()
{

	ComboTextTexNo = LoadTexture(g_TextureNameComboText);
	if (ComboTextTexNo == -1)
	{//ロードエラー
		exit(999);
	}

	g_ComboText.Pos = D3DXVECTOR2(COMBOTEXT_POS_X, COMBOTEXT_POS_Y);
	g_ComboText.Size = D3DXVECTOR2(COMBOTEXT_SIZE_X, COMBOTEXT_SIZE_Y);
	g_ComboText.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);

	ComboMagTexNo = LoadTexture(g_TextureNameComboMag);
	if (ComboMagTexNo == -1)
	{//ロードエラー
		exit(999);
	}
	for (int i = 0; i < 4; i++)
	{
		g_ComboMag[i].pos = D3DXVECTOR2(COMBOMAG_POS_X, COMBOMAG_POS_Y);	//位置
		g_ComboMag[i].size = D3DXVECTOR2(COMBOMAG_SIZE_X, COMBOMAG_SIZE_Y);	//サイズ
		g_ComboMag[i].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		g_ComboMag[i].combonum = 0;								//コンボの倍率一桁抽出
	}
	g_ComboMag[1].combonum = 18;
	g_ComboMag[2].combonum = 1;
	g_ComboMag[3].combonum = 16;

	for (int i = 0; i < COMBO_DIGIT; i++)
	{
		g_Combo[i].pos = D3DXVECTOR2(COMBO_POS_X, COMBO_POS_Y);		//位置
		g_Combo[i].size = D3DXVECTOR2(COMBO_SIZE_X, COMBO_SIZE_Y);	//サイズ
		g_Combo[i].col = D3DXCOLOR(1.0, 1.0, 1.0, 0.2);
		g_Combo[i].combonum = 1;					//コンボ数
	}

	ComboTexno = LoadTexture(g_TextureNameCombo);
	if (ComboTexno == -1)
	{//ロードエラー
		exit(999);
	}

	MaxComboTextTexNo = LoadTexture(g_TextureNameMaxComboText);
	if (MaxComboTextTexNo == -1)
	{//ロードエラー
		exit(999);
	}
	ComboAdd = 0;
	ComboMagNum = 0;
	ComboMax = 0;
	ComboMaxTextureW[0] = 23;
	ComboMaxTextureW[1] = 0;
	ComboMaxTextureW[2] = 12;
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
	if (g_ComboMagTexture)
	{
		g_ComboMagTexture->Release();
		g_ComboMagTexture = NULL;
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
	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(ComboTextTexNo));

	DrawSpriteColorRotation(
		g_ComboText.Pos.x,
		g_ComboText.Pos.y,
		g_ComboText.Size.x,
		g_ComboText.Size.y,
		0.0f,
		g_ComboText.col,
		0.0f,
		1.0f,
		1.0f,
		1
	);

	int MagColNum = min((int)((ComboMagNum)/5),4);

	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(ComboMagTexNo));

	for (int i = 0; i < 4; i++) {
		DrawSpriteColorRotation(
			g_ComboMag[i].pos.x,			
			g_ComboMag[i].pos.y,
			g_ComboMag[i].size.x,
			g_ComboMag[i].size.y,
			0.0f,
			MagColor[MagColNum],
			g_ComboMag[i].combonum,
			0.2f,
			0.2f,
			5
		);
	}

}

void DrawMaxCombo()
{
	COMBO g_MaxCombo[COMBO_DIGIT];

	for (int i = 0; i < COMBO_DIGIT; i++) {
		int j, ComboDigit;
		j = i;
		ComboDigit = 10;
		while (j > 0)
		{
			ComboDigit *= 10;
			j--;
		}
		g_MaxCombo[i].combonum = ComboMax % ComboDigit / (ComboDigit / 10);
		g_MaxCombo[i].pos = D3DXVECTOR2(COMBO_R_POS_X, COMBO_R_POS_Y);		//位置
		g_MaxCombo[i].size = D3DXVECTOR2(COMBO_R_SIZE_X, COMBO_R_SIZE_Y);	//サイズ
		g_MaxCombo[i].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	}

	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(ComboTexno));
	for (int i = 0; i < COMBO_DIGIT; i++) {
		DrawSpriteColorRotation(
			g_MaxCombo[i].pos.x,
			g_MaxCombo[i].pos.y,
			g_MaxCombo[i].size.x,
			g_MaxCombo[i].size.y,
			0.0f,
			g_MaxCombo[i].col,
			g_MaxCombo[i].combonum,
			0.2f,
			0.2f,
			5
		);
	}

	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(ComboTextTexNo));

	DrawSpriteColorRotation(
		g_MaxCombo[0].pos.x + 80.0f,
		COMBO_R_TEXT_POS_Y + 20.0f,
		100.0f,
		60.0f,
		0.0f,
		D3DXCOLOR(1.0, 1.0, 1.0, 1.0),
		0.0f,
		1.0f,
		1.0f,
		1
	);


	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(MaxComboTextTexNo));
	for (int i = 0; i < 3; i++) {


		DrawSpriteColorRotation(
			g_MaxCombo[2].pos.x - (60.0f * i) - 70.0f,
			COMBO_R_TEXT_POS_Y + 20.0f,
			60.0f,
			60.0f,
			0.0f,
			D3DXCOLOR(1.0, 1.0, 1.0, 1.0),
			ComboMaxTextureW[i],
			0.2f,
			1.0f / 6.0f,
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

void ComboMagUp()
{
	g_ComboMag[0].combonum = ComboMagNum % 10;
	if (ComboMagNum == 0)
	{
		g_ComboMag[2].combonum = 1;
	}
	else if (ComboMagNum % 10 == 0)
	{
		g_ComboMag[2].combonum++;
		g_ComboMag[0].combonum = 0;
	}
}
void ResetCombo()
{
	if (ComboMax < ComboAdd) {
		ComboMax = ComboAdd;
	}
	ComboAdd = 0;
	ComboMagNum = 0;
	ComboMagUp();
}

float GetComboScoreUp()
{
	float Up = 1.0f;
	if (ComboAdd >= 10)
	{
		if (ComboAdd % 10 == 0) {
			ComboMagNum = ComboAdd*2 / 10;
			if (ComboMagNum <= 30) {
				ComboMagUp();
			}
			else {
 				ComboMagNum = 30;
			}
		}
		Up += ComboMagNum / 10.0f;
	}
	return Up;
}
