//====================================================
//リズムへッダー
//作成：勝沼力樹
//		2022/10/26
//====================================================
#pragma once
#ifndef RHYTHM_H_
#include	"main.h"


//ノーツの構造体
struct NOTES
{
	D3DXVECTOR2		size;
	D3DXVECTOR2		pos;
	D3DXVECTOR2		sp;
	float			rot;
	D3DXCOLOR		col;
	bool			use;
	float			texno;
	float			alpha;
	int				num;
};

//ノーツレーンの構造体
struct NOTESLANE
{
	D3DXVECTOR2		size;
	D3DXVECTOR2		pos;
	float			rot;
	D3DXCOLOR		col;
	float			texno;
	float			texcent;

};


HRESULT	InitRhythm(int stagenum);
void	UpdateRhythm();
void	UninitRhythm();
void	DrawRhythm();
void	SetNotes();
bool	GetRhythm();
NOTES*	GetNotes();
int		GetFreame();
void	ReleaseNotes();
bool	MusicEnd();

int  BGM_RE();
float GetGradation();

#endif // RHYTHM_H_

