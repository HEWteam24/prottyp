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
typedef struct {
	D3DXVECTOR2		Pos;
	D3DXVECTOR2		Size;
	D3DXCOLOR		col;
}COMBOTEXT;

HRESULT		InitCombo();
void		UninitCombo();
void		UpdateCombo();
void		DrawCombo();
void		ComboPlus(int combo);
void		GetComboDizit();
void		ComboMagUp();
void		ResetCombo();
float		GetComboScoreUp();

#endif // !COMBO_H_
