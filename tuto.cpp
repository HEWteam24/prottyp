/*==============================================================================

   �Q�[���{�ҏ��� [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "tuto.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "bg.h"
#include "collision.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "bullet.h"
#include "enemy.h"
#include "enemybullet.h"
#include "rhythm.h"
#include "frame.h"
#include "score.h"
#include "combo.h"
#include "lane.h"
#include "keyboard.h"
#include "special.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int g_BGMGame;
static int g_TextureTutoDark;
bool stop;

CIRCLE circle;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTuto(void)
{
	g_TextureTutoDark = LoadTexture((char*)"data/TEXTURE/Tuto.png");

	InitPlayer();
	InitBullet();
	InitScore();
	InitCombo();

	InitSpecial();
	InitEnemy(0);
	InitEnemyBullet();
	InitRhythm(0);
	// �w�i�̏�����
	InitBG(0);
	InitLane();

	stop = false;

	circle.size = D3DXVECTOR2(1920.0f,1920.0f*3);
	circle.pos  = D3DXVECTOR2(CENTER_X, 0.0f-450.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTuto(void)
{
	UninitBG();
	UninitLane();

	UninitBullet();

	UninitEnemy();
	UninitEnemyBullet();
	UninitRhythm();
	UninitCombo();
	UninitSpecial();

	StopSound(g_BGMGame);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTuto(void)
{
	//�G���^�[�L�[�������ꂽ��SCENE_GAME�ֈڍs����
	if (Keyboard_IsKeyDown(KK_G))
	{
		SceneTransition(SCENE_TITLE);
	}

	if (stop == false)
	{
		UpdateRhythm();
	}

	if ((GetFreame() > 120)&&(stop==false)) {

		if (!MusicEnd()) {
			

			UpdateBG();
			UpdateLane();

			UpdatePlayer();
			UpdateBullet();
			UpdateEnemy();
			UpdateEnemyBullet();
			UpdateScore();
			UpdateCombo();
			UpdateSpecial();
		}
		else {
			SceneTransition(SCENE_STAGESELECT);
		}
	}

	if (GetFreame() == 121)
	{
		PauseSound(BGM_RE());
		stop = true;
	}


	if (((Keyboard_IsKeyDown(KK_ENTER)))&&(stop == true))
	{
		RePlaySound(BGM_RE());
		stop = false;
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTuto(void)
{
	//�w�i�̕`�揈��
	//DrawBG();
	DrawLane();

	DrawCombo();
	DrawBullet();
	DrawPlayer();
	DrawEnemyBullet();
	DrawEnemy();
	DrawRhythm();
	DrawHp();
	DrawSpecial();
	DrawScore();

	if (stop == true) {
		DrawSpriteColor(g_TextureTutoDark, circle.pos.x, circle.pos.y, circle.size.x, circle.size.y,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
}
