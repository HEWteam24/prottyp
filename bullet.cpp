//====================================================
//�o���b�g
//�쐬�F���c�T��
//		2022/10/26
//====================================================
#include "bullet.h"
#include "enemy.h"
#include "texture.h"
#include "sprite.h"
#include "special.h"

//================================
//�O���[�o���ϐ�
//================================
BULLET g_Bullet[BULLET_MAX];


//================================
//������
//================================

HRESULT InitBullet()
{
	//�e�N�X�`���̃��[�h
	int texno = LoadTexture((char*)"data\\TEXTURE\\bullet_P.png");
	//�\���̂̏�����
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].use = false;
		g_Bullet[i].w = BULLET_SIZE_W;
		g_Bullet[i].h = BULLET_SIZE_H;
		g_Bullet[i].pos = D3DXVECTOR2(0, 0);
		g_Bullet[i].texNo = texno;
		g_Bullet[i].mov = D3DXVECTOR2(0, -BULLET_SPEED);

	}
	return S_OK;
}

//�I������
void UninitBullet()
{
}

//�X�V����
void UpdateBullet()
{
	ENEMY* pEnemy = GetEnemy();

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)
		{
			g_Bullet[i].oldpos = g_Bullet[i].pos;	//�����蔻��p�̍��W�R�s�[

			g_Bullet[i].pos += g_Bullet[i].mov;	//�ړ�

			if (g_Bullet[i].pos.y < 0 - g_Bullet[i].h / 2)
			{
				g_Bullet[i].use = false;
			}

			if (pEnemy->use)
			{
				if (
					g_Bullet[i].pos.y - (g_Bullet[i].h / 2) < (pEnemy->pos.y + pEnemy->size.y / 2) &&
					g_Bullet[i].oldpos.y - (g_Bullet[i].h / 2) > (pEnemy->pos.y - pEnemy->size.y / 2) &&
					g_Bullet[i].pos.x < (pEnemy->pos.x + pEnemy->size.x / 2) &&
					g_Bullet[i].pos.x >(pEnemy->pos.x - pEnemy->size.x / 2)
					)
				{
					if (GetEnemyNum() > 0) {
						pEnemy->hp -= Damage() / (GetEnemyNum() * 1.5);
						g_Bullet[i].use = false;
					}
					else {
						pEnemy->hp -= Damage();
						g_Bullet[i].use = false;
					}
					//if (pEnemy->hp <= 0)
					//{
					//	pEnemy->use = false;
					//}
				}

			}
		}


	}
}

void DrawBullet()
{
	
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use)
		{
			////�e�N�X�`���̃Z�b�g
			//GetDeviceContext()->PSSetShaderResources
			//(0, 1, GetTexture(g_Bullet[i].texNo));	//�X�v���C�g�̕`��

			//DrawSprite
			//(
			//	g_Bullet[i].pos.x,
			//	g_Bullet[i].pos.y,
			//	g_Bullet[i].w,
			//	g_Bullet[i].h,
			//	g_Bullet[i].rot,
			//	D3DXCOLOR(1.0, 1.0, 1.0, 1.0),	//���F
			//	g_Bullet[i].texNo,		//�A�j���[�V�����p�^�[���ԍ�
			//	1,				//�p�^�[���̉��T�C�Y
			//	1				//    �@�@�@�c�T�C�Y
			//						//���ɕ��ԃp�^�[���̐�

			//);

			DrawSpriteColor(g_Bullet[i].texNo, g_Bullet[i].pos.x, g_Bullet[i].pos.y, BULLET_SIZE_W, BULLET_SIZE_H,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}
}

BULLET * GetBullet()
{
	return &g_Bullet[0];
}

void SetBullet(D3DXVECTOR2 pos)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == false)
		{
			g_Bullet[i].pos = pos;
			g_Bullet[i].use = true;
			return;
		}
	}
}

//�_���[�W�̌v�Z�@return�Ń_���[�W�̐��l��Ԃ�
int Damage()
{
	SPECIAL* sp = GetSpecial();

	int damage;

	//���Yspecial�������̃_���[�W�̑���
	if (sp->damage_up == true)
	{
		damage = 450;
		return damage;
	}
	//�񔭓����̃f�t�H���g���l
	else
	{
		damage = 90;
		return damage;
	}
}