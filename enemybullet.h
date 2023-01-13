#pragma once
#include "main.h"
#include "renderer.h"

//==================================
//�}�N����`
//==================================
#define	ENEMYBULLET_NOMAL_MAX		20		//�e�̍ő吔
#define	ENEMYBULLET_LONG_MAX		20		//�e�̍ő吔
#define	ENEMYBULLET_HP_MAX		20		//�e�̍ő吔
#define	ENEMYBULLET_TRANSLUCENT_MAX		20		//�e�̍ő吔
#define	ENEMYBULLET_SPEED	8.0f	//�e�̃X�s�[�h
#define	ENEMYBULLET_SIZE_W	140		//�e�̉��T�C�Y
#define	ENEMYBULLET_SIZE_H	60		//�e�̏c�T�C�Y
#define ENEMYBULLET_ALFA_CHANGE	0.002f	//�A���t�@�l�ύX

//�ȉ��}�b�v�`�b�v�p
#define	MAP_SIZE_X	5	//�����[����
#define	MAP_SIZE_Y	115	//�c�m�[�c����(����P�b�ɂP��)

//==================================
//�O���[�o���ϐ�
//==================================

//�\����
struct ENEMYBULLET
{
	bool use;
	float w, h;
	D3DXVECTOR2	pos;
	float	rot;
	D3DXVECTOR2	mov;	//�ړ��x�N�g��
	int	texNo;
	int hp;
};

//==================================
//�v���g�^�C�v�錾
//==================================
HRESULT InitEnemyBullet();
void	UninitEnemyBullet();
void	UpdateEnemyBullet();
void	DrawEnemyBullet();

void	SETBULLET();
