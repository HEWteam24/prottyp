// 12月1日
// 3:プレイヤーに近づいたらテクスチャが消える（弾自体は消えない）
// 
// 4:プレイヤーに近づいたら2つになる
// 
// 4→2 0 2
// 
// 5:プレイヤーに近づいたら爆発する　
// 
//      1
// 5→1 0 1
//      1 
// 
// 周りに弾がそもそも存在しているなら上書きする
// 
// 

#include"mapchip.h"

int StageBullet[STAGE_NUM][MAP_HEIGHT][MAP_WIDTH] =
{
	//Stage 1
	{
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 1,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		1, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 1,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 1,
		1, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1,
		1, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1,
		1, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 1,
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 1, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 1,
		1, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,

		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 1,
		1, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},
	
	//Stage 2
	{
	   0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
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
		0, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
		1, 0, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 1, 0,
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
		1, 0, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		0, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 1,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 1,
		0, 0, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 1, 1,
		0, 1, 0, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 0, 1, 0, 1,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 1, 1,

		0, 0, 1, 1, 0,
		1, 1, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 1,
		0, 0, 1, 1, 0,
		0, 0, 0, 1, 1,
		0, 0, 1, 0, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 0, 1,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},
	
	//Stage 3
	{
		 2, 2, 0, 2, 2,
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
		2, 2, 0, 0, 0,
		2, 0, 2, 0, 0,
		2, 0, 1, 0, 0,
		2, 1, 0, 2, 0,
		2, 0, 2, 2, 0,
		2, 0, 1, 0, 1,
		2, 2, 0, 1, 1,
		2, 0, 0, 0, 0,
		2, 0, 0, 0, 0,
		1, 0, 0, 0, 1,

		1, 1, 0, 1, 1,
		1, 1, 0, 1, 1,
		1, 0, 0, 0, 1,
		1, 0, 0, 0, 1,
		2, 0, 1, 0, 2,
		0, 2, 0, 2, 0,
		2, 0, 0, 0, 2,
		2, 0, 1, 0, 2,
		2, 1, 0, 1, 2,
		2, 0, 1, 0, 2,
		1, 1, 0, 1, 1,
		0, 0, 1, 0, 1,
		1, 2, 0, 1, 0,
		0, 0, 1, 2, 2,
		0, 0, 1, 2, 2,
		2, 0, 0, 0, 0,
		2, 2, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},

	//Stage 4
	{
		2, 3, 0, 3, 2,
		1, 0, 1, 0, 1,
		2, 3, 0, 3, 2,
		1, 0, 0, 0, 1,
		2, 3, 0, 3, 2,
		1, 0, 0, 0, 1,
		2, 3, 0, 3, 2,
		0, 0, 1, 0, 0,
		0, 1, 1, 0, 1,
		1, 0, 0, 3, 2,
		0, 3, 1, 0, 2,
		0, 0, 0, 0, 2,
		2, 1, 0, 1, 2,
		0, 0, 3, 0, 0,
		0, 0, 3, 0, 0,
		0, 0, 3, 1, 0,
		0, 0, 3, 1, 0,
		0, 0, 3, 0, 1,
		0, 0, 3, 1, 0,
		0, 0, 3, 0, 1,
		3, 3, 3, 0, 1,
		0, 1, 3, 0, 1,
		1, 0, 3, 1, 0,
		0, 0, 3, 0, 2,
		0, 1, 3, 0, 0,
		2, 0, 3, 0, 0,
		1, 0, 3, 3, 3,
		0, 0, 0, 0, 2,
		0, 0, 0, 2, 0,
		0, 0, 2, 0, 0,
		0, 2, 0, 1, 1,
		0, 0, 1, 0, 1,
		2, 0, 1, 1, 0,
		0, 2, 0, 0, 1,
		1, 0, 2, 0, 0,
		1, 1, 0, 2, 0,
		1, 0, 1, 0, 0,
		0, 1, 1, 0, 2,
		1, 0, 0, 3, 2,
		1, 0, 2, 0, 2,
		0, 3, 1, 0, 2,
		0, 0, 0, 3, 2,
		2, 0, 0, 0, 1,
		0, 3, 0, 0, 0,
		1, 0, 2, 0, 1,
		0, 1, 2, 3, 0,
		1, 0, 2, 0, 1,
		0, 1, 2, 1, 0,
		2, 0, 0, 0, 2,
		0, 1, 0, 1, 0,
		0, 1, 0, 1, 0,
		3, 0, 3, 0, 3,
		0, 3, 0, 3, 0,
		1, 0, 1, 0, 1,
		0, 0, 0, 3, 3,
		0, 0, 1, 3, 1,
		0, 1, 0, 0, 0,
		1, 0, 2, 0, 1,
		2, 0, 0, 1, 0,
		0, 1, 0, 1, 0,
		0, 0, 2, 0, 0,
		3, 0, 1, 0, 3,
		0, 1, 0, 1, 0,
		0, 2, 0, 2, 0,
		0, 2, 0, 2, 0,
		0, 3, 0, 3, 0,
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		2, 0, 0, 0, 2,
		1, 1, 0, 1, 1,
		0, 0, 0, 0, 0,
		1, 0, 3, 0, 1,
		0, 0, 0, 3, 0,
		0, 0, 1, 1, 0,
		0, 3, 2, 0, 1,
		0, 0, 2, 1, 0,
		3, 0, 2, 0, 1,
		0, 3, 0, 1, 0,
		0, 0, 0, 0, 0,
		3, 3, 0, 0, 0,
		0, 0, 0, 3, 3,
		3, 3, 0, 0, 0,
		0, 0, 0, 3, 3,
		2, 0, 2, 0, 0,
		0, 0, 0, 1, 0,
		0, 1, 0, 0, 2,
		0, 0, 1, 0, 1,
		1, 0, 0, 1, 0,
		2, 0, 0, 0, 0,
		2, 0, 0, 0, 3,
		2, 1, 0, 1, 0,
		2, 0, 1, 3, 0,
		1, 1, 0, 3, 0,
		0, 0, 2, 3, 0,
		0, 0, 0, 3, 0,
		0, 1, 0, 0, 1,
		2, 0, 0, 2, 0,
		0, 1, 0, 0, 0,
		3, 0, 3, 0, 3,
		3, 0, 3, 0, 3,

		0, 0, 0, 0, 0,
		3, 2, 0, 2, 3,
		0, 0, 0, 0, 0,
		1, 0, 2, 0, 1,
		2, 0, 0, 0, 2,
		3, 1, 0, 1, 3,
		3, 2, 0, 2, 3,
		3, 3, 0, 3, 3,
		3, 3, 0, 3, 3,
		0, 3, 0, 3, 0,
		0, 3, 0, 3, 0,
		0, 3, 0, 3, 0,
		0, 3, 0, 3, 0,
		0, 3, 0, 3, 0,
		0, 0, 3, 0, 0,
		1, 0, 0, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0

	},

	//Stage 5
	{
		2, 0, 4, 0, 2,//1
		1, 4, 0, 4, 1,//2 1
		2, 0, 0, 0, 2,//3 2
		1, 0, 0, 0, 1,//4 3
		2, 0, 0, 0, 2,//4.5ぐらいで刃ヒット 4 
		2, 0, 0, 0, 2,
		2, 1, 0, 1, 2,
		4, 4, 4, 4, 4,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		4, 4, 4, 4, 4,
		0, 0, 1, 0, 0,
		1, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		4, 4, 4, 4, 4,
		2, 0, 1, 0, 0,
		0, 0, 0, 2, 0,
		2, 0, 0, 0, 0,
		4, 4, 4, 4, 4,
		0, 0, 0, 0, 0,
		4, 4, 4, 4, 4,
		0, 0, 0, 0, 0,
		4, 4, 4, 4, 4,
		0, 0, 0, 0, 0,
		4, 4, 0, 4, 4,
		0, 0, 0, 0, 0,
		4, 4, 0, 4, 4,
		0, 0, 0, 0, 0,
		4, 4, 0, 4, 4,
		0, 1, 0, 1, 0,
		0, 1, 0, 1, 0,
		0, 1, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 2, 0, 1,
		4, 4, 2, 0, 1,
		0, 0, 2, 0, 1,
		0, 0, 2, 1, 0,
		0, 0, 2, 1, 0,
		0, 0, 2, 1, 0,
		0, 0, 2, 0, 1,
		1, 0, 2, 4, 1,
		0, 1, 0, 0, 1,
		0, 0, 0, 0, 2,
		1, 0, 1, 0, 0,
		0, 1, 2, 0, 4,
		0, 1, 1, 2, 0,
		0, 1, 0, 2, 0,
		2, 0, 0, 2, 0,
		2, 0, 0, 4, 0,
		2, 0, 0, 0, 2,
		2, 1, 0, 0, 2,
		2, 1, 0, 0, 2,
		1, 0, 2, 0, 4,
		0, 1, 1, 0, 0,
		1, 0, 2, 0, 0,
		0, 1, 2, 0, 1,
		1, 0, 2, 0, 2,
		0, 0, 2, 0, 0,
		0, 0, 0, 0, 0,
		1, 0, 1, 0, 0,
		0, 1, 4, 1, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		2, 0, 0, 0, 2,
		2, 0, 0, 0, 2,
		2, 1, 0, 1, 2,
		0, 0, 0, 4, 4,
		1, 0, 1, 4, 4,
		0, 1, 0, 4, 4,
		0, 0, 1, 0, 0,
		4, 4, 0, 0, 0,
		4, 4, 1, 0, 0,
		4, 4, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 1,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 0,
		2, 4, 2, 4, 2,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 2,
		1, 0, 1, 0, 1,
		4, 0, 4, 0, 4,
		0, 2, 0, 2, 0,
		0, 2, 0, 2, 0,
		0, 1, 0, 1, 0,
		0, 0, 0, 0, 0,
		1, 1, 0, 0, 0,
		0, 0, 0, 1, 1,
		1, 0, 1, 0, 0,
		0, 1, 4, 4, 1,
		0, 0, 1, 1, 0,
		1, 0, 0, 0, 2,
		0, 1, 0, 0, 1,
		0, 4, 0, 4, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		1, 0, 0, 0, 1,

		4, 4, 4, 4, 4,
		1, 0, 0, 0, 1,
		1, 0, 2, 0, 1,
		2, 0, 2, 0, 2,
		2, 4, 4, 4, 2,
		1, 0, 2, 0, 0,
		1, 0, 2, 0, 0,
		0, 0, 2, 0, 0,
		4, 0, 2, 0, 4,
		0, 0, 2, 0, 0,
		0, 0, 2, 0, 0,
		0, 0, 2, 0, 0,
		0, 4, 2, 4, 0,
		0, 0, 2, 0, 0,
		1, 0, 0, 0, 1,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},
	
	//Stage 6
	{
		1, 0, 0, 0, 1,
		3, 1, 0, 1, 3,
		1, 2, 0, 2, 1,
		3, 2, 0, 2, 3,
		1, 2, 4, 2, 1,
		3, 2, 0, 2, 3,
		1, 2, 0, 2, 1,
		0, 0, 0, 0, 0,
		1, 0, 1, 0, 0,
		0, 0, 0, 1, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 1, 0, 0, 1,
		1, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 1,
		1, 0, 1, 0, 1,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		1, 0, 1, 1, 0,
		0, 0, 0, 0, 0,
		2, 0, 1, 0, 2,
		2, 2, 0, 2, 2,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		2, 0, 2, 0, 2,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		2, 0, 0, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 2, 0, 0,
		2, 0, 1, 0, 2,
		2, 2, 0, 2, 2,
		0, 0, 0, 0, 0,
		1, 0, 2, 3, 3,
		0, 1, 2, 3, 3,
		0, 0, 0, 0, 0,
		3, 3, 2, 0, 1,
		3, 3, 2, 1, 0,
		1, 0, 0, 0, 0,
		0, 0, 1, 3, 3,
		0, 0, 0, 0, 0,
		3, 3, 1, 0, 0,
		1, 0, 0, 0, 1,
		3, 3, 0, 3, 3,
		0, 0, 3, 0, 0,
		3, 0, 3, 0, 3,
		0, 3, 0, 3, 0,
		1, 4, 1, 4, 1,
		1, 0, 1, 0, 1,
		0, 0, 0, 0, 0,
		4, 0, 0, 0, 0,
		0, 4, 0, 0, 0,
		0, 1, 4, 4, 4,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 4,
		0, 0, 1, 4, 0,
		4, 4, 4, 0, 0,
		4, 0, 0, 0, 4,
		0, 4, 0, 4, 0,
		0, 0, 4, 0, 0,
		0, 4, 0, 4, 0,
		4, 0, 0, 1, 4,
		0, 0, 4, 0, 0,
		0, 4, 4, 0, 4,
		0, 1, 4, 0, 0,
		4, 0, 0, 4, 0,
		0, 0, 4, 0, 4,
		0, 4, 1, 0, 1,
		4, 0, 0, 4, 0,
		1, 0, 0, 0, 0,
		4, 4, 4, 4, 4,
		0, 0, 0, 0, 0,
		1, 0, 0, 0, 2,
		0, 2, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 2, 0,
		2, 0, 0, 0, 1,
		0, 2, 0, 2, 0,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		0, 2, 0, 2, 0,
		0, 1, 0, 0, 0,
		1, 0, 2, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		2, 0, 2, 0, 2,
		2, 0, 0, 0, 2,
		2, 2, 4, 2, 2,
		0, 3, 0, 0, 0,
		0, 3, 0, 1, 0,
		2, 0, 1, 0, 0,
		0, 4, 0, 3, 3,
		0, 0, 0, 0, 0,
		2, 0, 2, 4, 2,

		0, 0, 1, 0, 2,
		1, 0, 0, 0, 0,
		0, 3, 4, 1, 0,
		3, 0, 1, 0, 2,
		0, 0, 0, 1, 3,
		0, 2, 0, 0, 0,
		4, 0, 0, 1, 0,
		0, 3, 1, 0, 4,
		0, 0, 0, 1, 0,
		0, 2, 0, 0, 0,
		0, 0, 2, 4, 2,
		1, 0, 2, 0, 0,
		0, 4, 4, 0, 1,
		1, 0, 0, 3, 0,
		0, 0, 0, 0, 0,
		0, 4, 0, 0, 4,
		0, 0, 1, 0, 0,
		2, 0, 0, 1, 0,
		0, 0, 0, 2, 0,
		0, 3, 1, 0, 1,

		4, 0, 0, 3, 0,
		0, 1, 2, 0, 0,
		0, 0, 4, 4, 0,
		0, 2, 0, 0, 2,
		1, 0, 0, 4, 2,
		0, 3, 4, 0, 2,
		1, 0, 0, 0, 0,
		4, 4, 4, 4, 4,
		0, 0, 0, 0, 0,
		1, 0, 0, 0, 0,
		1, 1, 0, 0, 1,
		0, 0, 2, 1, 0,
		4, 1, 4, 4, 1,
		0, 2, 0, 0, 2,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 0,
		1, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},

	//Stage 7
	{
	    0, 0, 1, 0, 0,
		0, 1, 1, 1, 0,
		1, 0, 1, 0, 1,
		0, 1, 1, 1, 0,
		1, 0, 1, 0, 1,
		1, 1, 0, 1, 1,
		1, 0, 1, 0, 1,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 0, 0, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 0,
		1, 0, 0, 0, 1,
		1, 0, 1, 0, 0,
		0, 1, 0, 0, 1,
		1, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		0, 0, 0, 1, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 1,
		1, 0, 1, 0, 1,
		1, 1, 0, 0, 1,
		1, 1, 0, 1, 1,
		1, 0, 1, 0, 1,
		1, 0, 1, 0, 1,
		1, 1, 0, 1, 1,
		1, 0, 1, 0, 1,
		1, 1, 0, 0, 1,
		1, 0, 1, 1, 1,
		1, 0, 0, 1, 1,
		1, 0, 1, 0, 1,
		1, 1, 0, 0, 1,
		1, 0, 0, 1, 1,
		1, 1, 0, 1, 1,
		1, 0, 0, 0, 1,
		1, 0, 1, 1, 0,
		1, 1, 0, 0, 0,
		0, 0, 0, 1, 1,
		0, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 0,
		1, 0, 0, 0, 1,
		0, 1, 0, 1, 0,
		0, 1, 0, 1, 0,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		0, 0, 0, 0, 0,
		0, 1, 1, 1, 0,
		0, 0, 1, 0, 0,
		1, 1, 0, 1, 0,
		0, 1, 0, 0, 1,
		0, 1, 1, 0, 1,
		0, 0, 0, 0, 1,
		0, 0, 1, 1, 1,
		1, 0, 0, 0, 1,
		0, 1, 0, 0, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 0, 1,
		0, 0, 1, 1, 0,
		1, 1, 0, 0, 1,
		1, 0, 0, 1, 1,
		0, 1, 1, 0, 0,
		0, 0, 1, 0, 1,
		1, 0, 0, 1, 0,
		1, 0, 0, 1, 0,
		0, 1, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 1, 0, 0, 0,
		1, 0, 0, 1, 0,
		0, 0, 0, 0, 1,
		1, 0, 1, 0, 0,
		0, 1, 1, 0, 1,
		1, 0, 1, 0, 0,
		1, 0, 1, 1, 0,
		0, 1, 1, 0, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 0, 0,
		0, 1, 0, 1, 0,
		0, 1, 0, 0, 1,
		0, 0, 1, 1, 0,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 0,
		1, 1, 0, 0, 1,
		1, 0, 1, 1, 0,
		0, 0, 1, 0, 1,
		0, 1, 1, 0, 1,
		1, 0, 1, 0, 1,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 0, 0, 1,
		0, 1, 1, 0, 1,
		0, 0, 1, 1, 0,
		1, 1, 0, 1, 1,
		0, 0, 1, 0, 0,
		0, 1, 1, 0, 1,
		1, 0, 1, 0, 0,

		1, 0, 0, 1, 1,
		1, 1, 0, 0, 1,
		1, 0, 1, 0, 1,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 1, 1, 0, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		1, 0, 0, 1, 0,
		0, 1, 0, 0, 1,
		0, 1, 0, 0, 0,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 0, 1, 0, 0,
		0, 1, 0, 0, 0,
		1, 0, 1, 1, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 1, 0,

		1, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 0, 0, 0, 1,
		1, 0, 1, 0, 0,
		1, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		1, 0, 0, 0, 0,
		0, 1, 0, 1, 1,
		1, 0, 0, 0, 1,
		1, 0, 1, 0, 0,
		1, 0, 0, 0, 1,
		0, 0, 1, 0, 0,
		0, 1, 1, 0, 1,
		1, 0, 0, 1, 1,
		1, 1, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 1, 1, 0,
		0, 0, 1, 0, 1,
		1, 0, 0, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 1, 1, 0, 0,
		1, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},

	//Stage 8
	{
		2, 2, 0, 2, 2,
		2, 0, 0, 0, 2,
		0, 0, 2, 0, 0,
		0, 0, 2, 0, 0,
		2, 0, 0, 0, 2,
		2, 2, 0, 2, 2,
		0, 0, 0, 0, 0,
		0, 0, 2, 0, 0,
		0, 2, 2, 2, 0,
		0, 0, 2, 0, 0,
		2, 0, 0, 0, 2,
		2, 2, 0, 2, 2,
		0, 0, 0, 0, 0,
		0, 0, 2, 0, 0,
		0, 2, 2, 2, 0,
		0, 2, 2, 2, 0,
		0, 0, 2, 0, 0,
		0, 0, 0, 0, 0,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 2,
		0, 0, 0, 0, 0,
		0, 2, 0, 2, 0,
		0, 2, 0, 2, 0,
		0, 0, 0, 0, 0,
		2, 0, 2, 0, 2,
		0, 0, 0, 0, 0,
		0, 2, 0, 2, 2,
		0, 0, 0, 0, 0,
		2, 0, 2, 0, 2,
		0, 0, 0, 0, 0,
		2, 2, 0, 2, 2,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 2, 2, 2, 0,
		0, 0, 0, 0, 0,
		2, 2, 0, 2, 2,
		0, 0, 0, 0, 0,
		0, 2, 2, 2, 0,
		0, 0, 0, 0, 0,
		2, 2, 0, 2, 2,
		0, 0, 0, 0, 0,
		0, 2, 2, 2, 0,
		0, 0, 2, 0, 0,
		2, 0, 0, 0, 2,
		0, 0, 2, 0, 0,
		2, 0, 0, 0, 2,
		2, 2, 0, 2, 2,
		2, 2, 0, 0, 2,
		2, 2, 2, 0, 2,
		2, 2, 0, 0, 2,
		2, 2, 0, 2, 2,
		2, 0, 0, 0, 2,
		2, 0, 2, 0, 0,
		0, 0, 2, 2, 0,
		0, 2, 2, 2, 0,
		0, 0, 0, 2, 0,
		2, 2, 0, 0, 0,
		2, 2, 0, 0, 2,
		2, 2, 2, 0, 2,
		2, 2, 2, 0, 2,
		2, 0, 0, 0, 2,
		2, 0, 2, 2, 2,
		2, 0, 2, 2, 2,
		2, 0, 0, 2, 2,
		2, 2, 0, 2, 2,
		2, 0, 0, 0, 2,
		2, 0, 2, 0, 2,
		0, 0, 0, 0, 0,
		0, 2, 0, 2, 0,
		0, 0, 0, 0, 0,
		0, 2, 2, 2, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 2, 2,
		2, 0, 2, 2, 2,
		2, 0, 0, 0, 0,
		2, 2, 0, 0, 0,
		2, 2, 2, 0, 2,
		2, 2, 0, 0, 2,
		2, 0, 0, 0, 2,
		2, 0, 2, 0, 2,
		2, 0, 0, 0, 2,
		2, 2, 0, 2, 2,
		2, 2, 0, 0, 0,
		0, 0, 0, 2, 0,
		0, 2, 0, 2, 0,
		0, 2, 0, 0, 0,
		0, 0, 0, 0, 2,
		2, 0, 0, 0, 2,
		0, 0, 0, 0, 0,
		0, 2, 2, 0, 2,
		0, 0, 0, 0, 0,
		2, 0, 0, 2, 2,
		0, 0, 0, 0, 0,
		2, 2, 2, 0, 0,
		0, 0, 0, 0, 0,
		0, 2, 0, 2, 0,
		0, 0, 0, 0, 0,
		2, 0, 2, 0, 2,

		0, 0, 0, 0, 0,
		0, 2, 0, 2, 0,
		0, 0, 0, 0, 0,
		2, 0, 2, 0, 2,
		0, 0, 0, 0, 0,
		0, 2, 0, 2, 0,
		0, 0, 0, 0, 0,
		2, 2, 0, 0, 0,
		0, 0, 0, 2, 2,
		0, 0, 2, 2, 2,
		0, 2, 2, 2, 2,
		0, 0, 2, 2, 2,
		2, 0, 0, 2, 2,
		2, 2, 0, 2, 2,
		0, 0, 0, 0, 0,
		0, 0, 2, 0, 0,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 2,
		2, 0, 0, 0, 2,
		2, 2, 0, 2, 2,

		2, 2, 0, 2, 2,
		2, 0, 0, 0, 2,
		0, 0, 2, 0, 0,
		2, 0, 2, 0, 2,
		0, 0, 0, 0, 0,
		0, 2, 0, 2, 0,
		0, 0, 2, 0, 0,
		0, 0, 2, 0, 0,
		0, 2, 2, 2, 0,
		0, 0, 2, 0, 0,
		2, 0, 0, 0, 2,
		2, 2, 0, 2, 2,
		2, 0, 0, 2, 2,
		2, 0, 2, 2, 2,
		2, 0, 2, 0, 2,
		2, 0, 0, 0, 2,
		2, 2, 0, 2, 2,
		2, 0, 0, 0, 2,
		2, 0, 2, 0, 0,
		2, 0, 0, 2, 0,
		2, 2, 0, 0, 0,
		2, 0, 0, 2, 2,
		2, 0, 0, 0, 2,
		0, 0, 2, 0, 2,
		0, 2, 0, 0, 0,
		0, 0, 0, 2, 2,
		2, 0, 0, 2, 2,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},

	//Stage 9
	{
		4, 0, 0, 1, 4,
		1, 0, 0, 1, 0,
		0, 3, 4, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 1, 1,
		3, 1, 1, 0, 0,
		0, 4, 1, 0, 0,
		1, 1, 1, 4, 1,
		0, 0, 1, 0, 0,
		4, 0, 0, 0, 0,
		0, 4, 1, 0, 4,
		1, 0, 1, 1, 0,
		0, 1, 0, 0, 4,
		0, 4, 0, 0, 0,
		1, 0, 1, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 4, 0, 4,
		1, 1, 1, 0, 0,
		1, 3, 4, 0, 0,
		0, 4, 0, 1, 0,
		3, 0, 3, 0, 3,
		3, 0, 0, 1, 1,
		0, 3, 0, 0, 1,
		0, 0, 1, 1, 0,
		3, 4, 0, 1, 0,
		0, 0, 1, 0, 3,
		1, 0, 0, 1, 0,
		3, 1, 3, 0, 0,
		0, 0, 0, 0, 1,
		3, 4, 0, 0, 1,
		0, 1, 3, 1, 0,
		3, 0, 3, 0, 1,
		0, 0, 0, 0, 0,
		0, 3, 0, 1, 1,
		0, 4, 1, 0, 0,
		3, 1, 0, 3, 0,
		0, 0, 3, 0, 1,
		3, 0, 0, 0, 0,
		0, 1, 0, 1, 0,
		0, 0, 0, 0, 3,
		0, 1, 3, 1, 0,
		0, 0, 0, 0, 0,
		3, 0, 4, 1, 0,
		0, 0, 0, 0, 3,
		1, 0, 0, 0, 1,
		0, 1, 0, 3, 4,
		3, 0, 0, 0, 0,
		4, 0, 3, 0, 1,
		0, 0, 0, 3, 0,
		0, 3, 0, 0, 0,
		0, 0, 0, 0, 0,
		1, 0, 1, 0, 3,
		0, 1, 0, 3, 0,
		1, 0, 0, 1, 0,
		1, 0, 3, 0, 4,
		0, 1, 0, 1, 0,
		3, 0, 4, 1, 0,
		0, 0, 0, 0, 3,
		1, 3, 0, 4, 0,
		1, 0, 0, 1, 0,
		1, 1, 0, 1, 0,
		0, 0, 1, 0, 4,
		1, 0, 0, 0, 1,
		0, 3, 4, 0, 0,
		0, 0, 0, 1, 0,
		4, 0, 0, 1, 0,
		1, 0, 1, 0, 0,
		1, 1, 0, 0, 1,
		1, 0, 4, 0, 0,
		1, 0, 0, 4, 1,
		1, 1, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 1, 3, 0, 4,
		1, 0, 0, 0, 0,
		4, 0, 1, 0, 0,
		1, 0, 1, 1, 0,
		0, 1, 0, 0, 3,
		0, 4, 0, 3, 3,
		0, 1, 1, 0, 0,
		1, 0, 0, 4, 1,
		0, 0, 1, 0, 4,
		1, 0, 0, 0, 0,
		1, 4, 0, 0, 1,
		1, 0, 0, 4, 0,
		1, 1, 3, 1, 0,
		0, 0, 4, 0, 0,
		0, 3, 0, 1, 0,
		1, 0, 3, 0, 0,
		1, 0, 3, 1, 1,
		1, 0, 3, 0, 1,
		0, 0, 0, 0, 0,
		4, 1, 4, 1, 0,
		0, 1, 0, 0, 1,
		1, 0, 0, 0, 0,
		1, 0, 4, 3, 0,
		0, 0, 1, 3, 0,
		1, 0, 0, 0, 0,
		0, 4, 3, 1, 0,
		1, 0, 0, 0, 1,
		4, 0, 1, 1, 0,

		0, 1, 0, 4, 3,
		0, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
		1, 0, 4, 0, 1,
		0, 3, 0, 3, 0,
		0, 0, 0, 0, 1,
		3, 0, 0, 1, 0,
		0, 1, 3, 0, 0,
		1, 0, 3, 4, 3,
		0, 4, 0, 1, 0,
		3, 0, 3, 0, 1,
		4, 0, 3, 0, 0,
		0, 0, 0, 1, 4,
		0, 3, 4, 0, 0,
		3, 0, 0, 1, 0,
		1, 4, 0, 0, 1,
		0, 0, 1, 0, 1,
		3, 0, 0, 1, 0,
		0, 0, 3, 4, 4,
		1, 0, 0, 0, 0,

		0, 1, 1, 0, 0,
		3, 0, 0, 0, 1,
		1, 4, 3, 0, 4,
		1, 0, 0, 3, 0,
		3, 4, 1, 4, 3,
		4, 0, 0, 0, 4,
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 3, 4, 3, 0,
		1, 0, 0, 0, 1,
		0, 3, 3, 3, 0,
		1, 4, 1, 4, 1,
		3, 0, 3, 0, 3,
		3, 0, 3, 0, 3,
		4, 0, 4, 0, 4,
		0, 0, 0, 0, 0,
		0, 3, 0, 3, 0,
		0, 3, 0, 3, 0,
		3, 0, 3, 0, 3,
		0, 0, 0, 0, 0,
		3, 3, 0, 4, 0,
		0, 0, 4, 3, 1,
		0, 4, 3, 0, 0,
		4, 0, 0, 0, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},

	//Stage 10
	{
		3, 0, 0, 4, 2,
		0, 0, 2, 0, 0,
		0, 4, 2, 0, 2,
		0, 4, 0, 0, 0,
		0, 3, 0, 2, 3,
		0, 3, 0, 4, 0,
		3, 4, 0, 0, 0,
		3, 0, 2, 3, 4,
		0, 0, 3, 2, 0,
		0, 3, 0, 0, 3,
		2, 0, 0, 3, 0,
		4, 0, 2, 4, 0,
		2, 0, 3, 2, 0,
		0, 3, 0, 2, 0,
		4, 2, 0, 0, 2,
		0, 4, 2, 0, 4,
		2, 3, 0, 0, 4,
		0, 4, 4, 2, 0,
		3, 0, 0, 0, 0,
		0, 0, 2, 0, 3,
		0, 0, 0, 2, 4,
		4, 3, 0, 4, 0,
		3, 0, 0, 0, 0,
		0, 2, 0, 4, 0,
		0, 3, 4, 0, 0,
		0, 0, 2, 2, 3,
		2, 0, 0, 3, 0,
		0, 0, 2, 0, 2,
		0, 3, 2, 0, 0,
		2, 4, 0, 0, 2,
		0, 0, 0, 3, 4,
		4, 0, 3, 4, 0,
		0, 4, 3, 0, 0,
		3, 0, 2, 0, 3,
		0, 2, 4, 0, 3,
		0, 0, 0, 0, 0,
		3, 0, 2, 3, 0,
		0, 2, 2, 0, 3,
		0, 0, 0, 4, 0,
		0, 3, 0, 2, 0,
		4, 0, 3, 4, 0,
		0, 2, 4, 0, 4,
		4, 2, 0, 0, 0,
		0, 4, 0, 0, 0,
		2, 0, 0, 0, 3,
		0, 0, 2, 2, 0,
		0, 3, 3, 0, 0,
		4, 2, 0, 2, 4,
		0, 0, 0, 0, 0,
		0, 3, 0, 2, 0,
		2, 0, 3, 0, 0,
		3, 4, 0, 3, 2,
		0, 3, 2, 4, 4,
		2, 0, 3, 2, 0,
		0, 2, 0, 0, 0,
		0, 2, 0, 3, 0,
		0, 3, 0, 0, 2,
		0, 0, 2, 0, 2,
		4, 2, 0, 0, 3,
		0, 0, 2, 0, 3,
		2, 0, 2, 2, 4,
		0, 0, 3, 0, 0,
		0, 2, 4, 0, 0,
		0, 4, 2, 0, 4,
		4, 2, 2, 3, 0,
		0, 0, 0, 0, 2,
		0, 3, 2, 3, 0,
		3, 0, 4, 0, 0,
		0, 0, 2, 0, 4,
		3, 0, 0, 3, 0,
		3, 2, 0, 0, 2,
		3, 0, 0, 0, 0,
		0, 2, 0, 4, 2,
		0, 2, 2, 0, 2,
		0, 0, 2, 0, 2,
		3, 0, 0, 0, 0,
		4, 2, 0, 2, 3,
		0, 2, 0, 3, 0,
		0, 0, 3, 0, 0,
		2, 0, 0, 2, 4,
		3, 0, 0, 0, 0,
		0, 2, 4, 3, 0,
		3, 2, 0, 3, 3,
		0, 2, 0, 3, 0,
		0, 0, 0, 3, 0,
		3, 4, 4, 3, 0,
		0, 2, 4, 4, 4,
		0, 3, 0, 3, 0,
		0, 2, 4, 3, 0,
		4, 3, 0, 3, 0,
		4, 0, 4, 3, 0,
		0, 2, 4, 0, 2,
		0, 3, 0, 0, 2,
		4, 0, 2, 4, 0,
		0, 2, 0, 2, 3,
		0, 4, 3, 0, 4,
		0, 0, 0, 0, 2,
		2, 0, 2, 0, 0,
		3, 0, 0, 0, 4,
		0, 4, 2, 0, 2,

		0, 3, 0, 4, 3,
		0, 0, 2, 0, 0,
		0, 2, 2, 0, 0,
		4, 0, 4, 0, 2,
		0, 3, 0, 3, 0,
		3, 0, 4, 2, 2,
		0, 2, 0, 0, 0,
		0, 3, 3, 0, 0,
		2, 0, 3, 4, 3,
		0, 4, 0, 2, 0,
		3, 0, 3, 0, 2,
		4, 0, 2, 0, 0,
		0, 0, 0, 2, 4,
		0, 3, 4, 0, 0,
		3, 0, 0, 2, 0,
		2, 4, 0, 0, 2,
		0, 0, 3, 0, 2,
		3, 0, 0, 3, 0,
		2, 0, 2, 4, 4,
		3, 0, 0, 0, 0,

		0, 2, 2, 0, 0,
		0, 0, 0, 0, 2,
		2, 4, 3, 0, 4,
		2, 0, 0, 3, 0,
		3, 4, 2, 4, 3,
		4, 0, 2, 0, 4,
		0, 0, 2, 0, 0,
		0, 0, 2, 0, 0,
		0, 0, 2, 0, 0,
		0, 2, 2, 2, 0,
		0, 3, 3, 3, 0,
		3, 0, 0, 0, 3,
		0, 3, 0, 3, 0,
		2, 0, 0, 0, 2,
		2, 0, 2, 0, 2,
		0, 0, 2, 0, 0,
		0, 3, 0, 3, 0,
		3, 0, 3, 0, 3,
		0, 3, 0, 3, 0,
		3, 0, 3, 0, 3,
		3, 2, 0, 2, 3,
		0, 0, 4, 0, 0,
		0, 4, 3, 4, 0,
		4, 0, 0, 0, 4,
		0, 4, 0, 4, 0,
		4, 0, 3, 0, 4,
		0, 3, 0, 3, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},


	//Stage 11
	{
		2, 2, 4, 2, 2,
		2, 2, 4, 2, 2,
		2, 2, 4, 2, 2,
		2, 2, 0, 2, 2,
		2, 2, 0, 2, 2,
		2, 2, 0, 2, 2,
		2, 2, 0, 2, 2,
		2, 1, 0, 1, 2,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 2,
		1, 0, 1, 0, 1,
		4, 2, 0, 2, 4,
		0, 2, 0, 2, 0,
		0, 2, 4, 2, 0,
		0, 2, 0, 2, 0,
		4, 1, 0, 1, 4,
		4, 0, 0, 0, 4,
		4, 0, 4, 0, 4,
		2, 2, 0, 2, 2,
		2, 2, 0, 2, 2,
		2, 3, 0, 1, 2,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 4,
		0, 0, 2, 2, 0,
		0, 2, 2, 2, 0,
		0, 2, 2, 2, 0,
		0, 0, 2, 2, 0,
		2, 0, 2, 0, 0,
		2, 0, 2, 0, 2,
		2, 0, 0, 0, 2,
		2, 1, 0, 1, 2,
		2, 3, 2, 4, 2,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 2,
		2, 0, 2, 0, 2,
		1, 0, 2, 0, 4,
		0, 2, 2, 2, 0,
		0, 2, 2, 1, 0,
		0, 0, 1, 0, 2,
		2, 0, 0, 2, 2,
		4, 4, 2, 2, 2,
		0, 2, 2, 2, 2,
		0, 1, 2, 2, 2,
		4, 3, 2, 2, 2,
		0, 3, 0, 2, 2,
		4, 3, 0, 1, 2,
		4, 3, 0, 0, 2,
		0, 3, 0, 0, 1,
		0, 3, 0, 1, 4,
		3, 3, 1, 0, 1,
		2, 1, 0, 1, 0,
		1, 0, 1, 0, 1,
		0, 1, 4, 1, 2,
		1, 1, 0, 2, 2,
		2, 0, 0, 2, 2,
		1, 0, 0, 2, 2,
		0, 1, 0, 2, 2,
		1, 0, 1, 2, 2,
		0, 1, 0, 2, 2,
		0, 1, 1, 2, 2,
		1, 1, 0, 2, 2,
		0, 1, 1, 2, 2,
		1, 1, 0, 2, 2,
		0, 1, 1, 2, 2,
		4, 4, 4, 2, 2,
		2, 0, 3, 2, 2,
		2, 0, 0, 0, 0,
		2, 2, 0, 0, 0,
		2, 2, 2, 0, 0,
		4, 4, 4, 4, 4,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		4, 4, 4, 4, 4,
		1, 0, 1, 0, 1,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		2, 0, 3, 0, 2,
		2, 2, 0, 2, 2,
		2, 0, 0, 0, 2,
		1, 0, 2, 0, 1,
		0, 2, 2, 2, 0,
		0, 1, 2, 1, 0,
		1, 1, 0, 1, 1,
		2, 1, 4, 3, 2,
		0, 4, 1, 0, 0,
		0, 1, 2, 1, 0,
		0, 2, 2, 2, 0,
		4, 1, 2, 1, 4,
		1, 0, 1, 0, 1,
		2, 1, 0, 1, 2,
		1, 0, 2, 0, 1,
		4, 2, 2, 2, 4,
		0, 2, 2, 2, 0,
		0, 2, 2, 2, 0,
		0, 2, 2, 2, 0,
		0, 3, 3, 3, 0,
		0, 3, 0, 3, 0,
		3, 0, 3, 0, 3,
		4, 3, 4, 3, 0,
		0, 3, 0, 3, 0,
		0, 3, 0, 3, 0,
		4, 3, 0, 3, 4,
		0, 3, 0, 3, 0,
		0, 3, 0, 3, 0,
		0, 3, 4, 3, 0,
		0, 3, 0, 3, 0,
		4, 3, 0, 3, 4,
		1, 0, 1, 0, 1,
		2, 0, 2, 0, 2,
		1, 0, 1, 0, 1,
		0, 2, 0, 2, 0,
		0, 0, 0, 0, 0,
		0, 1, 1, 1, 0,
		1, 1, 0, 1, 1,
		0, 1, 1, 1, 0,
		2, 0, 2, 0, 2,
		2, 0, 1, 0, 2,
		2, 1, 1, 0, 0,
		2, 2, 1, 1, 0,
		2, 1, 0, 1, 1,
		1, 0, 1, 1, 2,
		0, 1, 1, 2, 2,
		1, 1, 0, 1, 2,
		2, 1, 1, 0, 0,
		2, 2, 1, 1, 0,
		1, 1, 0, 1, 1,
		1, 0, 1, 1, 0,
		0, 1, 1, 0, 0,
		1, 1, 4, 0, 0,
		2, 0, 2, 0, 2,
		0, 0, 0, 0, 0,
		0, 2, 0, 2, 0,
		0, 0, 0, 0, 0,
		2, 0, 0, 0, 2,
		3, 3, 0, 3, 3,
		3, 3, 0, 3, 3,
		1, 0, 1, 0, 0,
		0, 1, 0, 1, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		1, 0, 0, 0, 1,
		0, 1, 1, 0, 0,
		1, 0, 0, 1, 0,
		0, 0, 1, 0, 1,
		0, 1, 0, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	}
};


