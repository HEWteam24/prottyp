#pragma once


#include "renderer.h"

int LoadTexture(char* fileName);
void UninitTexture(void);

ID3D11ShaderResourceView** GetTexture(int index);
