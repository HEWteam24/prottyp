//====================================================
//�G�l�~�[�o���b�g
//�쐬�F���c�T��
//		2022/10/26
//====================================================
#include "enemybullet.h"
#include "texture.h"
#include "bullet.h"
#include "player.h"
#include "sprite.h"
#include "sound.h"
#include "collision.h"
#include "rhythm.h"
#include "special.h"
#include <time.h>
#include <stdlib.h>


//================================
//�O���[�o���ϐ�
//================================
ENEMYBULLET g_EnemyBulletNomal[ENEMYBULLETNOMAL_MAX];
ENEMYBULLET g_EnemyBulletLong[ENEMYBULLETLONG_MAX];
PLAYER* pPlayer;

int nowY = 0;	//�}�b�v�̂��̎��̏c��

static int g_SE_Damage;		//�_���[�W�T�E���h

STAGE StageLv = STAGE01;

//================================
//�}�b�v�`�b�v
//================================
int StageBullet01[MAP_SIZE_Y][MAP_SIZE_X] =
{
	//1��

		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 0, 0, 1,
		0, 0, 1, 1, 0,
		1, 1, 0, 0, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 0, 1, 1,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
		1, 0, 0, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 0, 1, 1, 0,
		1, 1, 0, 0, 0,
		0, 0, 0, 1, 1,
		0, 0, 1, 1, 0,
		0, 1, 1, 0, 0,
		1, 1, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
		0, 0, 0, 1, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 1, 1,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		0, 1, 1, 0, 0,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 0, 1, 0, 1,

};
int StageBullet02[MAP_SIZE_Y][MAP_SIZE_X] =
{
	2, 2, 2, 2, 2,
	0, 0, 0, 2, 0,
	0, 2, 1, 0, 0,
	0, 0, 0, 1, 0,
	0, 2, 0, 0, 1,
	0, 0, 1, 0, 0,
	0, 0, 1, 0, 1,
	0, 1, 0, 0, 1,
	0, 0, 2, 1, 0,
	1, 0, 0, 0, 0,
	0, 2, 0, 0, 0,
	0, 0, 0, 1, 2,
	0, 0, 1, 0, 0,
	2, 0, 2, 0, 0,
	0, 0, 0, 1, 0,
	0, 1, 2, 0, 0,
	1, 0, 0, 0, 2,
	0, 0, 0, 1, 0,
	1, 0, 2, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 2,
	0, 0, 0, 1, 2,
	2, 0, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 0, 2, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	2, 0, 0, 0, 2,
	0, 2, 0, 2, 0,
	0, 0, 0, 0, 0,
	0, 0, 2, 0, 0,
	0, 2, 0, 0, 1,
	0, 1, 0, 0, 0,
	1, 0, 0, 1, 0,
	0, 1, 0, 0, 0,
	0, 0, 0, 0, 2,
	0, 0, 1, 0, 2,
	1, 0, 0, 1, 2,
	0, 1, 0, 0, 2,
	0, 1, 0, 1, 2,
	1, 0, 1, 0, 2,
	1, 0, 1, 0, 2,
	0, 0, 0, 0, 1,
	0, 1, 0, 0, 0,
	0, 2, 0, 1, 0,
	0, 0, 0, 0, 1,
	1, 0, 0, 1, 1,
	1, 1, 0, 0, 2,
	0, 0, 0, 2, 0,
	0, 1, 0, 0, 0,
	0, 0, 0, 2, 0,
	0, 0, 2, 0, 0,
	0, 0, 0, 0, 0,
	0, 2, 0, 1, 0,
	0, 0, 0, 0, 1,
	1, 0, 0, 1, 0,
	0, 1, 0, 0, 2,
	0, 2, 0, 0, 0,
	2, 0, 0, 0, 2,
	2, 2, 0, 2, 2,
	2, 2, 0, 2, 2,
	2, 2, 0, 2, 2,
	2, 0, 0, 0, 2,
	0, 0, 0, 0, 0,
	0, 1, 0, 1, 0,
	1, 0, 1, 0, 1,
	0, 1, 0, 1, 0,
	1, 0, 1, 0, 1,
	0, 2, 0, 2, 0,
	0, 0, 0, 0, 0,
	2, 2, 1, 0, 0,
	0, 0, 0, 1, 2,
	1, 2, 1, 0, 0,
	0, 0, 0, 0, 0,
	0, 0, 0, 1, 0,
	0, 1, 0, 0, 0,
	0, 0, 2, 0, 1,
	2, 0, 0, 0, 0,
	2, 2, 0, 0, 0,
	2, 2, 2, 0, 0,
	2, 2, 2, 0, 0,
	2, 2, 2, 0, 0,
	2, 2, 2, 2, 0,
	2, 2, 2, 0, 1,
	2, 2, 0, 1, 1,
	2, 2, 0, 0, 0,
	2, 0, 0, 0, 0,
	1, 0, 0, 0, 1,
};


//================================
//������
//================================

HRESULT InitEnemyBullet()
{
	//�e�N�X�`���̃��[�h
	int texno = LoadTexture((char*)"data\\TEXTURE\\Back.JPG");
	//�\���̂̏�����
	for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
	{
		//Nomal
		g_EnemyBulletNomal[i].use = false;
		g_EnemyBulletNomal[i].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletNomal[i].h = ENEMYBULLET_SIZE_H;
		g_EnemyBulletNomal[i].pos = D3DXVECTOR2(0, -10);
		g_EnemyBulletNomal[i].texNo = texno;
		g_EnemyBulletNomal[i].mov = D3DXVECTOR2(0, ENEMYBULLET_SPEED);
	}
	for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
	{
		//Long
		g_EnemyBulletLong[k].use = false;
		g_EnemyBulletLong[k].w = ENEMYBULLET_SIZE_W;
		g_EnemyBulletLong[k].h = ENEMYBULLET_SIZE_H * 3;
		g_EnemyBulletLong[k].pos = D3DXVECTOR2(0, -40);
		g_EnemyBulletLong[k].texNo = texno;
		g_EnemyBulletLong[k].mov = D3DXVECTOR2(0, ENEMYBULLET_SPEED);

	}
	char	file_SE_Damage[] = "data\\SE\\SE_deadEnm.wav";
	g_SE_Damage = LoadSound(file_SE_Damage);

	pPlayer = GetPlayer();
	nowY = 0;
	return S_OK;
}

//�I������
void UninitEnemyBullet()
{
}

//�X�V����
void UpdateEnemyBullet()
{
	SPECIAL* sp = GetSpecial();
	
	int eFreame = GetFreame();

	if (eFreame % 60*1.5 == 0.0f)
	{
		SETBULLET();
		nowY++;
	}

	for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
	{
		if (g_EnemyBulletNomal[i].use == true)
		{
			g_EnemyBulletNomal[i].pos += g_EnemyBulletNomal[i].mov;	//�ړ�

			if (g_EnemyBulletNomal[i].pos.y > SCREEN_HEIGHT - g_EnemyBulletNomal[i].h / 2)
			{
				g_EnemyBulletNomal[i].use = false;
				g_EnemyBulletNomal[i].pos.y = -10.0f;
			}

			if (CollisionBB(g_EnemyBulletNomal[i].pos, pPlayer->pos, D3DXVECTOR2(g_EnemyBulletNomal[i].w, g_EnemyBulletNomal[i].h), pPlayer->size))
			{
				g_EnemyBulletNomal[i].use = false;
				//�X�y�V�����̔�_������
				if (sp->get_damage_down == true)
				{
					pPlayer->hp -= 5.0f;
				}
				else
				{
					pPlayer->hp -= 25.0f;
				}

				g_EnemyBulletNomal[i].pos.y = -10.0f;
				PlaySound(g_SE_Damage, 0);
			}
		}
	}

	for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
	{
		if (g_EnemyBulletLong[k].use == true)
		{
			g_EnemyBulletLong[k].pos += g_EnemyBulletLong[k].mov;	//�ړ�

			if (g_EnemyBulletLong[k].pos.y > SCREEN_HEIGHT - g_EnemyBulletLong[k].h / 2)
			{
				g_EnemyBulletLong[k].use = false;
				g_EnemyBulletLong[k].pos.y = -10.0f;
			}

			if (CollisionBB(g_EnemyBulletLong[k].pos, pPlayer->pos, D3DXVECTOR2(g_EnemyBulletLong[k].w, g_EnemyBulletLong[k].h), pPlayer->size/2))
			{
				g_EnemyBulletLong[k].use = false;
				if (sp->get_damage_down == true)
				{
					pPlayer->hp -= 3.0f;
				}
				else
				{
					pPlayer->hp -= 15.0f;
				}
				g_EnemyBulletLong[k].pos.y = -10.0f;
				PlaySound(g_SE_Damage, 0);
			}

		}
	}
}

void DrawEnemyBullet()
{

	for (int x = 0; x < ENEMYBULLETNOMAL_MAX; x++)
	{
		if (g_EnemyBulletNomal[x].use)
		{
			DrawSpriteColor(g_EnemyBulletNomal[x].texNo, g_EnemyBulletNomal[x].pos.x, g_EnemyBulletNomal[x].pos.y, ENEMYBULLET_SIZE_W, ENEMYBULLET_SIZE_H,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}

	for (int y = 0; y < ENEMYBULLETLONG_MAX; y++)
	{
		if (g_EnemyBulletLong[y].use)
		{
			DrawSpriteColor(g_EnemyBulletLong[y].texNo, g_EnemyBulletLong[y].pos.x, g_EnemyBulletLong[y].pos.y, ENEMYBULLET_SIZE_W, ENEMYBULLET_SIZE_H * 3,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
		}
	}
}

ENEMYBULLET* GetEnemyBulletNomal()
{
	return &g_EnemyBulletNomal[0];
}

ENEMYBULLET* GetEnemyBulletLong()
{
	return &g_EnemyBulletLong[0];
}

void SetEnemyBullet()
{
	//srand((unsigned int)time(NULL));
	//int num,numm;		//�����p
	//int atk = 0,atkk = 0;	//�G�̍U���p
	//num = rand() % 9;
	//numm = rand() % 2;

	//switch (num)
	//{
	//case 0:
	//	if (numm == 0)
	//		atk = SCREEN_WIDTH / 2;
	//	else
	//		atkk = SCREEN_WIDTH / 2;
	//	break;
	//case 1:
	//	if (numm == 0)
	//		atk = SCREEN_WIDTH / 2;
	//	else
	//		atkk = SCREEN_WIDTH / 2;
	//	break;
	//case 2:
	//	if (numm == 0)
	//		atk = SCREEN_WIDTH / 2;
	//	else
	//		atkk = SCREEN_WIDTH / 2;
	//	break;
	//case 3:
	//	if (numm == 0)
	//		atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
	//	else
	//		atkk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
	//	break;
	//case 4:
	//	if (numm == 0)
	//		atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
	//	else
	//		atkk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
	//	break;
	//case 5:
	//	if (numm == 0)
	//		atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
	//	else
	//		atkk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
	//	break;
	//case 6:
	//	if (numm == 0)
	//		atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
	//	else
	//		atkk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
	//	break;
	//case 7:
	//	if (numm == 0)
	//		atk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
	//	else
	//		atkk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
	//	break;
	//case 8:
	//	if (numm == 0)
	//		atk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
	//	else
	//		atkk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
	//	break;
	//default:
	//	break;

	//}


	//if (atkk == 0)
	//{
	//	for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
	//	{
	//		if (g_EnemyBulletNomal[i].use == false)
	//		{
	//			g_EnemyBulletNomal[i].pos.x = atk;
	//			g_EnemyBulletNomal[i].use = true;
	//			return;
	//		}
	//	}
	//}
	//else
	//{
	//	for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
	//	{
	//		if (g_EnemyBulletLong[k].use == false)
	//		{
	//			g_EnemyBulletLong[k].pos.x = atkk;
	//			g_EnemyBulletLong[k].use = true;
	//			return;
	//		}

	//	}
	//}
}


void SETBULLET()
{


	int atk = 0;	//�G�̍U���p
	bool IsAtk = true;
	StageLv = STAGE01;		//���݂̃X�e�[�W(�e�X�g�p)
	if (nowY < MAP_SIZE_Y)
	{

		switch (StageLv)
		{
		case STAGE01:
			for (int j = 0; j < MAP_SIZE_X; j++)
			{
				switch (StageBullet01[nowY][j])
				{
				case 0:
					IsAtk = false;
					break;
				case 1:
					switch (j)
					{
					case 0:
						atk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
						break;
					case 1:
						atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
						break;
					case 2:
						atk = SCREEN_WIDTH / 2;
						break;
					case 3:
						atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
						break;
					case 4:
						atk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
						break;
					default:
						break;
					}
					if (IsAtk)
					{
						for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
						{
							if (g_EnemyBulletNomal[i].use == false)
							{
								g_EnemyBulletNomal[i].pos.x = atk;
								g_EnemyBulletNomal[i].use = true;
								break;
							}
						}
					}
					break;
				case 2:
					switch (j)
					{
					case 0:
						atk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
						break;
					case 1:
						atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
						break;
					case 2:
						atk = SCREEN_WIDTH / 2;
						break;
					case 3:
						atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
						break;
					case 4:
						atk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
						break;
					default:
						break;
					}
					if (IsAtk)
					{
						for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
						{
							if (g_EnemyBulletLong[k].use == false)
							{
								g_EnemyBulletLong[k].pos.x = atk;
								g_EnemyBulletLong[k].use = true;
								break;
							}
						}
					}
					break;
				case 3:
					IsAtk = false;
					break;
				case 4:
					IsAtk = false;
					break;
				default:
					IsAtk = false;
					break;
				}
				IsAtk = true;
				atk = 0;
			}
			break;




		case STAGE02:
			for (int j = 0; j < MAP_SIZE_X; j++)
			{
				switch (StageBullet02[nowY][j])
				{
				case 0:
					IsAtk = false;
					break;
				case 1:
					switch (j)
					{
					case 0:
						atk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
						break;
					case 1:
						atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
						break;
					case 2:
						atk = SCREEN_WIDTH / 2;
						break;
					case 3:
						atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
						break;
					case 4:
						atk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
						break;
					default:
						break;
					}
					if (IsAtk)
					{
						for (int i = 0; i < ENEMYBULLETNOMAL_MAX; i++)
						{
							if (g_EnemyBulletNomal[i].use == false)
							{
								g_EnemyBulletNomal[i].pos.x = atk;
								g_EnemyBulletNomal[i].use = true;
								break;
							}
						}
					}
					break;
				case 2:
					switch (j)
					{
					case 0:
						atk = SCREEN_WIDTH / 2 - LANE_SIZE_X * 2;
						break;
					case 1:
						atk = SCREEN_WIDTH / 2 - LANE_SIZE_X;
						break;
					case 2:
						atk = SCREEN_WIDTH / 2;
						break;
					case 3:
						atk = SCREEN_WIDTH / 2 + LANE_SIZE_X;
						break;
					case 4:
						atk = SCREEN_WIDTH / 2 + LANE_SIZE_X * 2;
						break;
					default:
						break;
					}
					if (IsAtk)
					{
						for (int k = 0; k < ENEMYBULLETLONG_MAX; k++)
						{
							if (g_EnemyBulletLong[k].use == false)
							{
								g_EnemyBulletLong[k].pos.x = atk;
								g_EnemyBulletLong[k].use = true;
								break;
							}
						}
					}
					break;
				case 3:
					IsAtk = false;
					break;
				case 4:
					IsAtk = false;
					break;
				default:
					IsAtk = false;
					break;
				}
				IsAtk = true;
				atk = 0;
			}
			break;
		}
	}
}