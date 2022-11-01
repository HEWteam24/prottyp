#pragma once
#ifndef COMBO_H_
#include "main.h"
struct COMBO 
{
	D3DXVECTOR2	pos;
	D3DXVECTOR2 size;
	D3DXCOLOR	col;
	int			combonum;
	float		texno;
};

HRESULT		InitCombo();
void		UninitCombo();
void		UpdateCombo();
void		DrawCombo();
void		ComboPlus(int combo);
void		GetComboDizit();
void		ResetCombo();
int			GetComboScoreUp();

#endif // !COMBO_H_
