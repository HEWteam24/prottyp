/*==============================================================================

   �Q�[���{�ҏ��� [game.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#include "game.h"
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
HRESULT InitGame(void)
{
	InitPlayer();
	InitBullet();
	InitEnemy();
	InitEnemyBullet();
	InitRhythm();
	InitScore();
	InitCombo();

	// �w�i�̏�����
	InitBG();

	//�����t�@�C����ǂݍ���Ŏ��ʎq���󂯎��
	g_BGMGame = LoadSound((char*)"data/BGM/BGM_Tanbo120.wav");
	//PlaySound(g_BGMGame, -1);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	UninitBG();

	UninitBullet();
	UninitPlayer();
	UninitEnemy();
	UninitEnemyBullet();
	UninitRhythm();
	UninitScore();
	UninitCombo();

	StopSound(g_BGMGame);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	//�G���^�[�L�[�������ꂽ��SCENE_GAME�ֈڍs����
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SceneTransition(SCENE_TITLE);
	}
	UpdateBG();

	UpdatePlayer();
	UpdateBullet();
	UpdateEnemy();
	UpdateEnemyBullet();
	UpdateRhythm();
	UpdateScore();
	UpdateCombo();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();
	
	DrawBullet();
	DrawPlayer();
	DrawEnemyBullet();
	DrawEnemy();
	DrawRhythm();
	DrawHp();
	DrawScore();
	DrawCombo();

}
