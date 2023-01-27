#pragma once
#include "main.h"
#include "renderer.h"

//==================================
//�}�N����`
//==================================
#define	BULLET_MAX		12		//�e�̍ő吔
#define	BULLET_SPEED	20.0f	//�e�̃X�s�[�h
#define	BULLET_SIZE_W	50		//�e�̉��T�C�Y
#define	BULLET_SIZE_H	50		//�e�̏c�T�C�Y

//�\����
struct BULLET
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
HRESULT InitBullet();
void	UninitBullet();
void	UpdateBullet();
void	DrawBullet();

BULLET*	GetBullet();
void	SetBullet(D3DXVECTOR2 pos);	//�e����

int Damage();
