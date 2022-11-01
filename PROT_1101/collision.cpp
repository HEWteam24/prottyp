
#include "collision.h"

//�~�Ɖ~�̓����蔻��
bool HitCheckCircle(D3DXVECTOR2 cir1pos, float cir1r,
	                D3DXVECTOR2 cir2pos, float cir2r)
{
	//cir1����cir2�Ɍ������x�N�g�������
	D3DXVECTOR2 dist;
	dist = cir2pos - cir1pos;

	//dist�x�N�g���̑傫�����v�Z����
	float length;
	//�x�N�g���̑傫���́u�e������2�悵�đS�������B�S�������I������畽�������Ƃ�v�Ōv�Z
	length = sqrt((dist.x*dist.x) + (dist.y*dist.y));

	//circle1�̔��a��circle2�̔��a�𑫂����l�����
	float R;
	R = (cir1r + cir2r);

	if (length < R)
		return true;
	else
		return false;
}

bool HitCheckCircleSq(D3DXVECTOR2 cir1pos, float cir1r,
	D3DXVECTOR2 cir2pos, float cir2r)
{
	//cir1����cir2�Ɍ������x�N�g�������
	D3DXVECTOR2 dist;
	dist = cir2pos - cir1pos;

	//dist�x�N�g���̑傫�����v�Z����
	float length;
	//�x�N�g���̑傫���́u�e������2�悵�đS�������B�S�������I������畽�������Ƃ�v�Ōv�Z
	length = (dist.x*dist.x) + (dist.y*dist.y);

	//circle1�̔��a��circle2�̔��a�𑫂����l�����
	float R;
	R = (cir1r + cir2r) * (cir1r + cir2r);

	if (length < R)
		return true;
	else
		return false;
}

//*****************************************************************************
// �����m�̓����蔻��
//�@�����F���S���W�P�A���S���W�Q�A�T�C�Y�P�A�T�C�Y�Q
//�@�߂�Ftrue:�������Ă�Afalse:�������ĂȂ�
//*****************************************************************************
bool	CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2) {

	D3DXVECTOR2		min1, min2;//���̍ŏ����W(�����̍��W)
	D3DXVECTOR2		max1, max2;//���̍ő���W(�E��̍��W)

	min1.x = pos1.x - size1.x / 2;//���P�@����
	min1.y = pos1.y - size1.y / 2;

	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;//���P�@����
	min2.y = pos2.y - size2.y / 2;

	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//�����蔻��
	if (max1.x < min2.x) { return false; }
	if (max1.y < min2.y) { return false; }
	if (min1.x > max2.x) { return false; }
	if (min1.y > max2.y) { return false; }

	return	true;
}
