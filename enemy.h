//====================================================
//�G�l�~�[�փb�_�[
//�쐬�F�����͎�
//		2022/10/26
//====================================================
#pragma once
#ifndef ENEMY_H_
#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define			ENEMY00_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY00_SIZE_Y		(ENEMY00_SIZE_X*1.5)							//�G�l�~�[�T�C�YY
#define			ENEMY01_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY01_SIZE_Y		(ENEMY01_SIZE_X*1.5)							//�G�l�~�[�T�C�YY
#define			ENEMY02_SIZE_X		(LANE_SIZE_X*2)								//�G�l�~�[�T�C�YX
#define			ENEMY02_SIZE_Y		(ENEMY02_SIZE_X*3.0)							//�G�l�~�[�T�C�YY
#define			ENEMY03_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY03_SIZE_Y		(ENEMY03_SIZE_X*1.5)							//�G�l�~�[�T�C�YY
#define			ENEMY04_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY04_SIZE_Y		(ENEMY04_SIZE_X*1.5)							//�G�l�~�[�T�C�YY
#define			ENEMY05_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY05_SIZE_Y		(ENEMY05_SIZE_X*1.5)							//�G�l�~�[�T�C�YY
#define			ENEMY06_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY06_SIZE_Y		(ENEMY06_SIZE_X*1.5)							//�G�l�~�[�T�C�YY
#define			ENEMY07_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY07_SIZE_Y		(ENEMY07_SIZE_X*1.5)							//�G�l�~�[�T�C�YY
#define			ENEMY08_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY08_SIZE_Y		(ENEMY08_SIZE_X)							//�G�l�~�[�T�C�YY
#define			ENEMY09_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY09_SIZE_Y		(ENEMY09_SIZE_X*1.5)							//�G�l�~�[�T�C�YY
#define			ENEMY10_SIZE_X		(LANE_SIZE_X*3)								//�G�l�~�[�T�C�YX
#define			ENEMY10_SIZE_Y		(ENEMY10_SIZE_X*1.5)							//�G�l�~�[�T�C�YY

#define			ENEMY_SP			(1.5f)										//�G�l�~�[�X�s�[�h
#define			ENEMY_HP			(500)										//�G�l�~�[HP�����l
//#define			ENEMY_TEX			((char*)"data\\texture\\ZARI_BOSS_1.png")			//�G�l�~�[�e�N�X�`��
#define			ENEMY_HP_POS_X		(CENTER_X-460.0f)									//�G�l�~�[�̗̓Q�[�W���WX
#define			ENEMY_HP_POS_Y		(CENTER_Y)									//�G�l�~�[�̗̓Q�[�W���WY
#define			ENEMY_HP_SIZE_X		(50.0f)									//�G�l�~�[�̗̓T�C�YX
#define			ENEMY_HP_SIZE_Y		(900.0f)										//�G�l�~�[�̗̓T�C�YY
//#define			ENEMY_HPB_SIZE_X	(510.0f)									//�G�l�~�[�̗̓T�C�YX
//#define			ENEMY_HPB_SIZE_Y	(60.0f)										//�G�l�~�[�̗̓T�C�YY
#define			ENEMY_HPB_SIZE_X	(60.0f)									//�G�l�~�[�̗̓T�C�YX
#define			ENEMY_HPB_SIZE_Y	(910.0f)										//�G�l�~�[�̗̓T�C�YY
#define			ENEMY_HP_TEX_A		((char*)"data\\texture\\HP_player_A.png")		//�G�l�~�[�e�N�X�`��
#define			ENEMY_HP_TEX_B		((char*)"data\\texture\\HP_player_B.png")		//�G�l�~�[�e�N�X�`��
#define			ENEMY_SPAWN_POS_X	(SCREEN_WIDTH/2)
#define			ENEMY_SPAWN_POS_Y	(20.0f)


//*****************************************************************************
// �G�l�~�[�@�N���X
//*****************************************************************************
struct ENEMY
{
	D3DXVECTOR2		size;
	D3DXVECTOR2		pos;
	D3DXVECTOR2		sp;
	float			rot;
	D3DXCOLOR		col;
	float			texno;
	int				hp;
	bool			use;
};

struct ENEMYHP
{
	D3DXVECTOR2		size;
	D3DXVECTOR2		pos;
	float			rot;
	D3DXCOLOR		col;
	float			texnoA;
	float			texnoB;
};

HRESULT		InitEnemy(int StageNum);
void		UninitEnemy();
void		UpdateEnemy();
void		DrawEnemy();
ENEMY*		GetEnemy();
int			GetEnemyNum();
bool		BadEnd();
#endif // !EMEMY_H_



