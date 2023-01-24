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
#include "effect.h"
#include "collision.h"

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
				if(CollisionBB(g_Bullet[i].pos,pEnemy->pos,D3DXVECTOR2(g_Bullet[i].w,g_Bullet[i].h),pEnemy->size))
				{

					pEnemy->hp -= Damage();
					SetEffect(EFFECT_2, g_Bullet[i].pos, D3DXVECTOR2(100,100));
					g_Bullet[i].use = false;
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
		float m = 1, n = GetEnemyNum();
		for (int i = 0; i < n; i++) {
			m *= 0.9f;
		}
		damage = 250 * m;
		return damage;
	}
	//�񔭓����̃f�t�H���g���l
	else
	{
		float m = 1, n = GetEnemyNum();
		for (int i = 0; i < n; i++) {
			m *= 0.9f;
		}
		damage = 90 * m;
		return damage;
	}
}