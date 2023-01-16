
#include "effect.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"

static EFFECT	g_Effect[EFFECT_MAX];
static int		g_TextureEffect[3];

void InitEffect()
{
	g_TextureEffect[EFFECT_1] = LoadTexture((char*)"data/TEXTURE/effect_kira.png");
	g_TextureEffect[EFFECT_2] = LoadTexture((char*)"data/TEXTURE/effect_bullet_hit.png");
	g_TextureEffect[EFFECT_3] = LoadTexture((char*)"data/TEXTURE/effect_notes.png");

	for (int i = 0; i < EFFECT_MAX; i++)
	{
		g_Effect[i].frame	= 0;
		g_Effect[i].pos		= D3DXVECTOR2(0.0f,0.0f);
		g_Effect[i].size	= D3DXVECTOR2(0.0f,0.0f);
		g_Effect[i].uv		= D3DXVECTOR2(0.0f,0.0f);
		g_Effect[i].use		= false;
		g_Effect[i].type	= EFFECT_1;
	}
}


void UninitEffect()
{

}


void UpdateEffect()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].use)
		{
			//アニメーション 最終パターン表示後にfalse
			g_Effect[i].frame++;
			g_Effect[i].uv.x += 1.0f / g_Effect[i].patternX;
			if (g_Effect[i].frame % g_Effect[i].patternX == 0)
			{
				g_Effect[i].uv.x = 0.0f;
				g_Effect[i].uv.y += 1.0f / g_Effect[i].patternY;
			}
			if (g_Effect[i].frame % g_Effect[i].patternMAX == 0)
			{
				g_Effect[i].use = false;
			}

			
			//種類ごとの挙動

			if (g_Effect[i].type == EFFECT_1)
			{

			}

			if (g_Effect[i].type == EFFECT_2)
			{

			}

			if (g_Effect[i].type == EFFECT_3)
			{

			}
		}
	}
}


void DrawEffect()
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].use)
		{
			DrawSpriteColor(g_TextureEffect[g_Effect[i].type],
				g_Effect[i].pos.x, g_Effect[i].pos.y,
				g_Effect[i].size.x, g_Effect[i].size.y,
				g_Effect[i].uv.x, g_Effect[i].uv.y,
				1.0f / g_Effect[i].patternX, 1.0f / g_Effect[i].patternY,
				D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}
}


//エフェクトの種類、出現位置、サイズの指定
void SetEffect(EFFECT_TYPE type, D3DXVECTOR2 pos, D3DXVECTOR2 sz)
{
	for (int i = 0; i < EFFECT_MAX; i++)
	{
		if (g_Effect[i].use == false)
		{
			g_Effect[i].type = type;
			g_Effect[i].pos  = pos;
			g_Effect[i].size = sz;

			g_Effect[i].uv		= D3DXVECTOR2(0.0f, 0.0f);
			g_Effect[i].frame	= 0;
			g_Effect[i].use		= true;


			if (g_Effect[i].type == EFFECT_1)
			{
				g_Effect[i].patternX = 8;
				g_Effect[i].patternY = 3;
				g_Effect[i].patternMAX = 20;
			}

			if (g_Effect[i].type == EFFECT_2)
			{
				g_Effect[i].patternX = 8;
				g_Effect[i].patternY = 2;
				g_Effect[i].patternMAX = 10;
			}

			if (g_Effect[i].type == EFFECT_3)
			{
				g_Effect[i].patternX = 8;
				g_Effect[i].patternY = 4;
				g_Effect[i].patternMAX = 16;
			}

			return;
		}
	}
}


EFFECT* GetEffect()
{
	return &g_Effect[0];
}
