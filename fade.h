//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �t�F�[�h�̏��
enum FADE_STATE
{
	FADE_NONE = 0,	// �t�F�[�h���������Ă��Ȃ�
	FADE_IN,		// �t�F�[�h�C��������
	FADE_OUT,		// �t�F�[�h�A�E�g������

	FADE_NUM,		// �I�[�R�[�h	
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SceneFadeIn(SCENE nextScene);
void SceneTransition(SCENE nextScene);
FADE_STATE GetFadeState(void);

void SetFadeColor(float r, float g, float b);
