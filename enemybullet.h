#pragma once

#pragma once
#include "main.h"
#include "renderer.h"

//==================================
//�}�N����`
//==================================
#define	ENEMYBULLET_MAX		20		//�e�̍ő吔
#define	ENEMYBULLET_SPEED	8.0f	//�e�̃X�s�[�h
#define	ENEMYBULLET_SIZE_W	140		//�e�̉��T�C�Y
#define	ENEMYBULLET_SIZE_H	60		//�e�̏c�T�C�Y

//==================================
//�O���[�o���ϐ�
//==================================

//�\����
struct ENEMYBULLET
{
	bool use;
	float w, h;
	D3DXVECTOR2	pos;
	D3DXVECTOR2	oldpos;	//�����蔻��p
	float	rot;
	D3DXVECTOR2	mov;	//�ړ��x�N�g��
	int	texNo;
};

//==================================
//�v���g�^�C�v�錾
//==================================
HRESULT InitEnemyBullet();
void	UninitEnemyBullet();
void	UpdateEnemyBullet();
void	DrawEnemyBullet();

ENEMYBULLET*	GetEnemyBullet();
void	SetEnemyBullet();	//�e����
