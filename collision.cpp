
#include "collision.h"

//円と円の当たり判定
bool HitCheckCircle(D3DXVECTOR2 cir1pos, float cir1r,
	                D3DXVECTOR2 cir2pos, float cir2r)
{
	//cir1からcir2に向かうベクトルを作る
	D3DXVECTOR2 dist;
	dist = cir2pos - cir1pos;

	//distベクトルの大きさを計算する
	float length;
	//ベクトルの大きさは「各成分を2乗して全部足す。全部足し終わったら平方根をとる」で計算
	length = sqrt((dist.x*dist.x) + (dist.y*dist.y));

	//circle1の半径とcircle2の半径を足した値を作る
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
	//cir1からcir2に向かうベクトルを作る
	D3DXVECTOR2 dist;
	dist = cir2pos - cir1pos;

	//distベクトルの大きさを計算する
	float length;
	//ベクトルの大きさは「各成分を2乗して全部足す。全部足し終わったら平方根をとる」で計算
	length = (dist.x*dist.x) + (dist.y*dist.y);

	//circle1の半径とcircle2の半径を足した値を作る
	float R;
	R = (cir1r + cir2r) * (cir1r + cir2r);

	if (length < R)
		return true;
	else
		return false;
}

//*****************************************************************************
// 箱同士の当たり判定
//　引数：中心座標１、中心座標２、サイズ１、サイズ２
//　戻り：true:当たってる、false:当たってない
//*****************************************************************************
bool	CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2) {

	D3DXVECTOR2		min1, min2;//箱の最小座標(左下の座標)
	D3DXVECTOR2		max1, max2;//箱の最大座標(右上の座標)

	min1.x = pos1.x - size1.x / 2;//箱１　左上
	min1.y = pos1.y - size1.y / 2;

	max1.x = pos1.x + size1.x / 2;
	max1.y = pos1.y + size1.y / 2;

	min2.x = pos2.x - size2.x / 2;//箱１　左上
	min2.y = pos2.y - size2.y / 2;

	max2.x = pos2.x + size2.x / 2;
	max2.y = pos2.y + size2.y / 2;

	//当たり判定
	if (max1.x < min2.x) { return false; }
	if (max1.y < min2.y) { return false; }
	if (min1.x > max2.x) { return false; }
	if (min1.y > max2.y) { return false; }

	return	true;
}
