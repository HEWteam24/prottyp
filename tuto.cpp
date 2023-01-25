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

#include "effect.h"

#include "pause.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
//static int g_BGMTuto;
bool Tutostart;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTuto(int StageNum)
{
	InitPlayer();
	InitBullet();
	InitScore();
	InitCombo();

	InitSpecial();
	InitEnemy(StageNum);
	InitEnemyBullet(StageNum);
	InitRhythm(StageNum);
	InitEffect();
	// �w�i�̏�����
	InitBG(StageNum);
	InitLane();

	//*****************************************************************************************************************
	//  �Q�[���J�n�J�E���g
	//	true  = ����
	//	false = �Ȃ�

	Tutostart = true;
	//*****************************************************************************************************************

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
	UninitSpecial();
	UninitEffect();

	//StopSound(g_BGM);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTuto(void)
{
	PAUSE* pPause = GetPause();

	//�G���^�[�L�[�������ꂽ��SCENE_GAME�ֈڍs����
	if (Keyboard_IsKeyDown(KK_G))
	{
		SceneTransition(SCENE_TITLE);
	}
	if (!MusicEnd()) {
		UpdateRhythm();

		if (GetFreame() > 120) {



			if (Tutostart)
			{
				PauseSound(BGM_RE());
				pPause->pause = true;
				pPause->restart = true;
				pPause->pause_frame = 0;
				pPause->alpha = 0.2f;
			}
			else {
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
			if (Tutostart)
			{
				Tutostart = false;
			}






		}

	}
	else {
		StopSoundAll();
		SceneTransition(SCENE_RESULT);
	}

	if (!pPause->restart)
	{
		pPause->alpha = 0.7f;
	}

	UpdateEffect();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTuto(void)
{
	//�w�i�̕`�揈��
	DrawBG();
	DrawLane();

	DrawCombo();
	DrawBullet();
	DrawPlayer();
	DrawEnemyBullet();
	DrawRhythm();
	DrawHp();
	DrawSpecial();
	DrawScore();
	DrawEnemy();
	DrawEffect();
}
