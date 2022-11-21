#pragma once
#ifndef SCORE_H_
#include "main.h"

#define		SCORE_UV_MAX	(10)

#define		SCORE_UV_W		(0.2)
#define		SCORE_UV_H		(0.2)


typedef struct {
	D3DXVECTOR2		Pos;
	D3DXVECTOR2		Size;
	int			Score;
	int			ToResult;

}SCORE;

typedef struct {
	D3DXVECTOR2		Pos;
	D3DXVECTOR2		Size;
	D3DXCOLOR		col;
}SCORETEXT;

void InitScore();
void InitScoreResult();
void UpdateScore();
void UninitScore();
void DrawScore();
void ScorePlus(int score);
void GetDizit();
SCORE* GetScore(void);

void SetScore(D3DXVECTOR2 Pos, D3DXVECTOR2 Size);

#endif // !SCORE_H_

