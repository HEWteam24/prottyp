/*==============================================================================

   �v���C���[�Ǘ�[player.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct PLAYER
{
	D3DXVECTOR2		pos;	//�ʒu
	D3DXVECTOR2		oldpos;	//�ʒu
	D3DXVECTOR2     uv;		//UV�l
	D3DXVECTOR2		size;	//�T�C�Y
	D3DXVECTOR2		speed;	//���x

	int		direction;		//����
	int		NowLane;		//���݂̃��[��
	float	hp;				//�̗�
	bool	moving;			//�ړ����t���O

	int		animeIndex;		//�A�j���[�V��������
	int		animeWait;		//�A�j���[�V����
	bool	flag;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

void	InitPlayer(void);
void	UninitPlayer(void);
void	UpdatePlayer(void);
void	DrawPlayer(void);
void	DrawHp(void);
void	PlayerCheck(void);
PLAYER* GetPlayer(void);

