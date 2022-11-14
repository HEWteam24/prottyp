#include "score.h"
#include "texture.h"
#include "sprite.h"



SCORE	g_Score[SCOER_DIGIT];
SCORETEXT g_ScoreText;

static	ID3D11ShaderResourceView* g_ScoreTexture;//画像1枚で1つの変数が必要
static	char* g_TextureNameScore = (char*)"data\\texture\\number.png";	//テクスチャファイルパス JPG BMP PNG

static	ID3D11ShaderResourceView* g_ScoreTextTexture;//画像1枚で1つの変数が必要
static	char* g_TextureNameScoreText = (char*)"data\\texture\\text_score.png";	//テクスチャファイルパス JPG BMP PNG

float	ScoreTexNo;
float	ScoreTextTexNo;
float	ScoreMagTexNo;
int		ScoreAdd;

void InitScore()
{
	ScoreAdd = 0;

	ScoreTextTexNo = LoadTexture(g_TextureNameScoreText);
	if (ScoreTextTexNo == -1)
	{//ロードエラー
		exit(999);
	}
	g_ScoreText.Pos = D3DXVECTOR2(SCORETEXT_POS_X, SCORETEXT_POS_Y);
	g_ScoreText.Size = D3DXVECTOR2(SCORETEXT_SIZE_X, SCORETEXT_SIZE_Y);
	g_ScoreText.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


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
	if (g_ScoreTextTexture)
	{
		g_ScoreTextTexture->Release();
		g_ScoreTextTexture = NULL;
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
	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(ScoreTextTexNo));

	DrawSpriteColorRotation(
			g_ScoreText.Pos.x,
			g_ScoreText.Pos.y,
			g_ScoreText.Size.x,
			g_ScoreText.Size.y,
			0.0f,
			g_ScoreText.col,
			0.0f,
			1.0f,
			1.0f,
			1
	);
	
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