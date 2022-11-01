#pragma once

#include "main.h"

bool HitCheckCircle(D3DXVECTOR2 cir1pos, float cir1r,
	D3DXVECTOR2 cir2pos, float cir2r);

bool HitCheckCircleSq(D3DXVECTOR2 cir1pos, float cir1r,
	D3DXVECTOR2 cir2pos, float cir2r);

bool	CollisionBB(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

void Collision_Bullet_Enemy(void);