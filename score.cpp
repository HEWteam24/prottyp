#include "score.h"
#include "texture.h"
#include "sprite.h"



SCORE	g_Score[SCOER_DIGIT];

static	ID3D11ShaderResourceView	*g_ScoreTexture;//画像1枚で1つの変数が必要
static	char	*g_TextureNameScore = (char*)"data\\texture\\number.png";//テクスチャファイルパス JPG BMP PNG

float	ScoreTexNo;
int		ScoreAdd;

void InitScore()
{
	ScoreAdd = 0;


	ScoreTexNo = LoadTexture(g_TextureNameScore);
	if (ScoreTexNo == -1)
	{//ロードエラー
		exit(999);
	}
	for (int i = 0; i < SCOER_DIGIT; i++) {
		g_Score[i].Pos = D3DXVECTOR2(SCORE_POS_X, SCORE_POS_Y);
		g_Score[i].Size = D3DXVECTOR2(SCORE_SIZE_X, SCORE_SIZE_Y);
		g_Score[i].Score = 0;
	}
}

void UpdateScore()
{
	GetDizit();
}

void UninitScore()
{
	if (g_ScoreTexture)
	{
		g_ScoreTexture->Release();
		g_ScoreTexture = NULL;
	}
}

void DrawScore()
{
	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(ScoreTexNo));
	for (int i = 0; i < SCOER_DIGIT; i++) {
		DrawSpriteColorRotation(
			g_Score[i].Pos.x, 
			g_Score[i].Pos.y, 
			g_Score[i].Size.x, 
			g_Score[i].Size.y,
			0.0f,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			g_Score[i].Score,
			0.2f,
			0.2f,
			5
			);
	}
}

void ScorePlus(int score)
{
	ScoreAdd += score;
}

void GetDizit()
{
	for (int i = 0; i < SCOER_DIGIT; i++) {
		int j, ScoreDigit;
		j = i;
		ScoreDigit = 10;
		while (j > 0)
		{
			ScoreDigit *= 10;
			j--;
		}
		g_Score[i].Score = ScoreAdd % ScoreDigit / (ScoreDigit / 10);
	}
}

void SetScore(D3DXVECTOR2 Pos, D3DXVECTOR2 Size)
{
	for (int i = 0; i < SCOER_DIGIT; i++) {
		g_Score[i].Pos = D3DXVECTOR2(Pos.x - (i * Size.x), Pos.y);
		g_Score[i].Size = D3DXVECTOR2(Size.x, Size.y);
	}
}