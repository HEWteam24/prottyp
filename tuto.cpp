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

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTuto(void)
{
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
	UpdateRhythm();

	if (GetFreame() > 120) {

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

}
