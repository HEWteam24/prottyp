/*==============================================================================

   �^�C�g����ʏ��� [Result.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "Result.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
//#include "input.h"
#include "inputx.h"
#include "sound.h"
#include "fade.h" 
#include "keyboard.h"
#include "score.h"
#include "combo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_TextureBgTitle;//�^�C�g����ʗp�e�N�X�`���̎��ʎq
static int g_TextureShishamo;
static int g_TextureClear;
static int g_TextureRankCoin;
static int g_BGMNo;//�^�C�g���pBGM�̎��ʎq

PLAYER* pPlayerOne = GetPlayer();
SCORE* pScore = GetScore();

COIN g_Coin;

float	Shishamo_pos;
float	Shishamo_spd;
int Addcol;

bool	moving;

int		EnemyScore;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitResult(int stagenum,int enemynum,int texnums)
{
	float criteria = 1.0f + (((float)stagenum / 10) * 2);

	EnemyScore = enemynum;
	g_Coin.col = D3DXCOLOR(0.0f,0.0f,0.0f,1.0f);
	g_Coin.TextCol = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
	g_Coin.rad = 0.0f;
	g_Coin.u = 0.0f;
	g_Coin.u = 0.0f;

	g_TextureRankCoin= LoadTexture((char*)"data/TEXTURE/rank_coins_1200x200_B.png");
	g_TextureClear = LoadTexture((char*)"data/TEXTURE/text_clear.png");

	g_TextureBgTitle = LoadTexture((char*)"data/TEXTURE/Back.JPG");
	g_TextureShishamo = LoadTexture((char*)"data/TEXTURE/Shishamo_end_1.png");


	if (pScore->ToResult >= 0)
	{
		g_Coin.rank = 5;
	}
	if (pScore->ToResult >= 2000* criteria)
	{
		g_Coin.rank = 4;
	}
	if (pScore->ToResult >= 4000 * criteria)
	{
		g_Coin.rank = 3;
	}
	if (pScore->ToResult >= 8000 * criteria)
	{
		g_Coin.rank = 2;
	}
	if (pScore->ToResult >= 10000 * criteria)
	{
		g_Coin.rank = 1;
	}
	if (pScore->ToResult >= 12000* criteria)
	{
		g_Coin.rank = 0;
	}

	if (pPlayerOne->dead)
	{
		g_TextureClear = LoadTexture((char*)"data/TEXTURE/text_failed.png");
		g_Coin.TextCol = D3DXCOLOR(0.8f, 0.5f, 1.0f, 1.0f);
		g_Coin.rank = 5;
	}

	g_Coin.alpha = 0.3f;
	g_Coin.size = D3DXVECTOR2(300.0f, 300.0f);
	g_Coin.roted = false;

	InitScoreResult(texnums, enemynum);

	Shishamo_pos = -450.0f;
	Shishamo_spd = 85.0f;
	Addcol = 0;
	moving = true;

	//g_BGMNo = LoadSound((char*)"data/BGM/BGM_Result.wav");
	//PlaySound(g_BGMNo, -1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitResult(void)
{
	UninitPlayer();
	UninitScore();
	UninitCombo();
	StopSound(g_BGMNo);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResult(void)
{
	//�G���^�[�L�[�������ꂽ��SCENE_TITLE�ֈڍs����
	if (Keyboard_IsKeyDown(KK_ENTER))
	{
		SceneTransition(SCENE_STAGESELECT);
	}
	//�R���g���[���[B�{�^����������SCENE_TITLE�ֈڍs
	if (IsButtonTriggered(0, XINPUT_GAMEPAD_B))
	{
		SceneTransition(SCENE_STAGESELECT);
	}

	//��������ړ�
	if (moving)
	{
		Shishamo_pos += Shishamo_spd;	//�X�s�[�h�𑫂��Ĉړ�
		Shishamo_spd *= 0.9f;			//�X�s�[�h����
	}
	//�ړ�����
	if (Shishamo_spd <= 1.0f)
	{
		moving = false;
	}

	if (Addcol < 100)
	{
		Addcol++;
	}
	if (g_Coin.rad<=360*2-10)
	{
		g_Coin.rad+=10.0f;
	}
	else
	{
		g_Coin.roted = true;
	}

	g_Coin.col = D3DXCOLOR(0.0f + Addcol * 0.01f,
		0.0f + Addcol * 0.01f,
		0.0f + Addcol * 0.01f,
		1.0f);

	g_Coin.size.x += 8.0f;
	g_Coin.size.y += 8.0f;
	g_Coin.alpha -= 0.02f;

	if (g_Coin.alpha <= 0.0f)
	{
		g_Coin.size.x = 300.0f;
		g_Coin.size.y = 300.0f;
		g_Coin.alpha = 0.3f;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawResult(void)
{
	DrawSpriteLeftTop(g_TextureBgTitle, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f);

	DrawSpriteColor(g_TextureShishamo, Shishamo_pos, CENTER_Y, 800.0f, 800.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));

	DrawSpriteColor(g_TextureClear, CENTER_X, CENTER_Y - 300.0f, 600.0f, 100.0f,
		0.0f, 0.0f, 1.0f, 1.0f, g_Coin.TextCol);


	GetDeviceContext()->PSSetShaderResources(0, 1,
		GetTexture(g_TextureRankCoin));

	DrawSpriteColorRotation(
		CENTER_X,
		CENTER_Y,
		300.0f,
		300.0f,
		g_Coin.rad,
		g_Coin.col,
		g_Coin.rank,
		0.16665f,
		1.0f,
		6
	);

	if (g_Coin.roted)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1,
			GetTexture(g_TextureRankCoin));
		DrawSpriteColorRotation(
			CENTER_X,
			CENTER_Y,
			g_Coin.size.x,
			g_Coin.size.y,
			g_Coin.rad,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Coin.alpha),
			g_Coin.rank,
			0.16665f,
			1.0f,
			6
		);

	}



	DrawScore();
	DrawEnemyScore();
	DrawMaxCombo();
}
