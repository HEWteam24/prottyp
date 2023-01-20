#pragma once
#include "main.h"
#include "renderer.h"

#define EFFECT_MAX (20)

enum EFFECT_TYPE
{
	EFFECT_1 = 0,
	EFFECT_2,		
	EFFECT_3,		//ÉmÅ[Écè¡ãééû
};

struct EFFECT
{
	D3DXVECTOR2		pos;
	D3DXVECTOR2		size;
	D3DXVECTOR2		uv;
	int frame;
	int type;
	int patternX;
	int patternY;
	int patternMAX;
	bool use;
};

void InitEffect();
void UninitEffect();
void UpdateEffect();
void DrawEffect();
void SetEffect(EFFECT_TYPE type, D3DXVECTOR2 pos, D3DXVECTOR2 sz);

EFFECT* GetEffect();
