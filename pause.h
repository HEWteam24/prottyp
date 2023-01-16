#pragma once

#include "main.h"
#include "renderer.h"
#include "inputx.h"
#include "keyboard.h"
#include "sound.h"
#include "texture.h"
#include "sprite.h"
#include "rhythm.h"
#include "fade.h"

typedef struct
{
	bool pause;
	bool restart;
	int pause_frame;
	float alpha;

	int PauseAction;

}PAUSE;

enum State
{
	eContinue = 0,
	eReTry = 1,
	eBack = 2,
};

void InitPause();
void UpdatePause();
void UninitPause();
void DrawPause();

void ReTry();
void Back();

PAUSE* GetPause();