//====================================================
//���Y���փb�_�[
//�쐬�F�����͎�
//		2022/10/26
//====================================================
#pragma once
#ifndef RHYTHM_H_
#include	"main.h"


//�m�[�c�̍\����
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

//�m�[�c���[���̍\����
struct NOTESLANE
{
	D3DXVECTOR2		size;
	D3DXVECTOR2		pos;
	float			rot;
	D3DXCOLOR		col;
	float			texno;
	float			texcent;

};


HRESULT	InitRhythm();
void	UpdateRhythm();
void	UninitRhythm();
void	DrawRhythm();
void	SetNotes();
bool	GetRhythm();
NOTES*	GetNotes();
int		GetFreame();
void	ReleaseNotes();
bool	MusicEnd();

#endif // RHYTHM_H_

