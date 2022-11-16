//====================================================
//�G�l�~�[
//�쐬�F�����͎�
//		2022/10/26
//====================================================
#include "enemy.h"
#include "collision.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"
#include "enemybullet.h"
#include "input.h"
#include "rhythm.h"
//#include "frame.h"
#include "score.h"
#include "combo.h"


ENEMY		Enemy;
ENEMYHP		EnemyHp;
int			EnemyNum;

//�e�N�X�`�����̕ۑ��ϐ�
static	ID3D11ShaderResourceView	*g_TextureEnemy;
static	char	*g_TextureNameEnemy = ENEMY_TEX;//�e�N�X�`����
static	ID3D11ShaderResourceView	*g_TextureEnemyHp;
static	char	*g_TextureNameEnemyHpA = ENEMY_HP_TEX_A;//�e�N�X�`����
static	char	*g_TextureNameEnemyHpB = ENEMY_HP_TEX_B;//�e�N�X�`����

//===================================================
//�@������
//===================================================
HRESULT InitEnemy()
{

	Enemy.size = D3DXVECTOR2(ENEMY_SIZE_X, ENEMY_SIZE_Y);
	Enemy.pos = D3DXVECTOR2(ENEMY_SPAWN_POS_X, ENEMY_SPAWN_POS_Y);
	Enemy.sp = D3DXVECTOR2(ENEMY_SP, ENEMY_SP);
	Enemy.rot = 0.0f;
	Enemy.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Enemy.hp = ENEMY_HP;
	Enemy.use = true;

	//�e�N�X�`���̃��[�h
	Enemy.texno = LoadTexture(g_TextureNameEnemy);
	if (Enemy.texno == -1)
	{//���[�h�G���[
		exit(999);
	}

	EnemyHp.size = D3DXVECTOR2(ENEMY_HP_SIZE_X, ENEMY_HP_SIZE_Y);
	EnemyHp.pos = D3DXVECTOR2(ENEMY_HP_POS_X , ENEMY_HP_POS_Y);
	EnemyHp.rot = 0.0f;
	EnemyHp.col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	//�e�N�X�`���̃��[�h
	EnemyHp.texnoA = LoadTexture(g_TextureNameEnemyHpA);
	if (EnemyHp.texnoA == -1)
	{//���[�h�G���[
		exit(999);
	}
	EnemyHp.texnoB = LoadTexture(g_TextureNameEnemyHpB);
	if (EnemyHp.texnoB == -1)
	{//���[�h�G���[
		exit(999);
	}

	EnemyNum = 1;
	return S_OK;
}

//===================================================
//�@�I������
//===================================================
void UninitEnemy()
{

}

//===================================================
//�@�X�V����
//===================================================
void UpdateEnemy()
{

	if (Enemy.use) 
	{
		Enemy.pos.x += Enemy.sp.x;		//�G�l�~�[���ړ�

		//�G�l�~�[�����[���[�ɐG�ꂽ�甽�]
		if (Enemy.pos.x - Enemy.size.x/2 <= SCREEN_WIDTH/2 - LANE_SIZE_X*2 - LANE_SIZE_X/2) 
		{
			Enemy.sp.x *= -1;
		}
		else if (Enemy.pos.x + Enemy.size.x/2 >= SCREEN_WIDTH / 2 + LANE_SIZE_X * 2 + LANE_SIZE_X / 2)
		{
			Enemy.sp.x *= -1;
		}

		//�̗�0�ŃG�l�~�[��
		if (Enemy.hp <= 0) 
		{
			Enemy.use = false;
			Enemy.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, ENEMY_SPAWN_POS_Y - 300.0f);
 			ScorePlus((500 * EnemyNum)*GetComboScoreUp());
			EnemyNum++;

		}
	}

	//new�G�l�~�[�a��
	if(!Enemy.use)
	{
		Enemy.pos.y += Enemy.sp.y;
		if (Enemy.pos.y >= ENEMY_SPAWN_POS_Y) 
		{
			Enemy.hp  = ENEMY_HP ;
			Enemy.use = true;
		}
	}

	//enemyBullet	(�f�o�b�O�p)
	//if ((GetKeyboardTrigger(DIK_S)))
	//{
	//	SetEnemyBulletNomal(Enemy.pos);
	//}
}

//===================================================
//�@�`�揈��
//===================================================
void DrawEnemy()
{

		DrawSprite(Enemy.texno, Enemy.pos.x, Enemy.pos.y, Enemy.size.x, Enemy.size.y,
			0.0f, 0.0f, 1.0f, 1.0f);

		DrawSpriteColor(EnemyHp.texnoB, EnemyHp.pos.x, EnemyHp.pos.y, EnemyHp.size.x + 10.0f, EnemyHp.size.y + 10.0f,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		//���\��
		//DrawSpriteColor(EnemyHp.texnoA, EnemyHp.pos.x - ((ENEMY_HP - Enemy.hp)/2), EnemyHp.pos.y, EnemyHp.size.x -(ENEMY_HP- Enemy.hp) , EnemyHp.size.y,
		//	0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		//�c�\��
		DrawSpriteColor(EnemyHp.texnoA, EnemyHp.pos.x, EnemyHp.pos.y + ((ENEMY_HP - Enemy.hp) / 1.11), EnemyHp.size.x, EnemyHp.size.y - (ENEMY_HP - Enemy.hp) * 1.8,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		

}

ENEMY * GetEnemy()
{
	return &Enemy;
}

int	GetEnemyNum()
{
	return EnemyNum;
}