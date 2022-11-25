//==============================================================================================
//
//
//
//==============================================================================================
#pragma once
#ifndef _SPECIAL_H_
#define _SPECIAL_H_
#include "main.h"
#include "input.h"
#include "texture.h"
#include "sprite.h" 
#include "keyboard.h"
#include "inputx.h"
#include <algorithm>
#include "player.h"
#include "sound.h"

#define SPECIAL_MAX (30) //�X�y�V���������ɕK�v�ȃR���{��
#define SPECIAL_POS_X		(CENTER_X+530.0f)		//�X�y�V������UI�|�W�V����				
#define	SPECIAL_POS_Y		(CENTER_Y+225.0)		//�X�y�V������UI�|�W�V����							
#define	SPECIAL_SIZE_X	(59.9f)						//�X�y�V�������ݒl�̃T�C�Y						
#define	SPECIAL_SIZE_Y	(450.0f)					//�X�y�V�������ݒl�̃T�C�Y					
#define	SPECIAL_F_SIZE_X	(60.0f)					//�X�y�V�����t���[���̃T�C�Y						
#define	SPECIAL_F_SIZE_Y	(450.0f)				//�X�y�V�����t���[���̃T�C�Y						


typedef struct {

	D3DXVECTOR2		IconPos; //�X�y�V�����Q�[�W�̏ꏊ
	
	float w, h;		//�X�y�V�����Q�[�W�̃T�C�Y

	int type;		//�I�������X�y�V�����̎��
	int	charge;		//�X�y�V�������`���[�W���Ă��鐔�l

	bool UseOk;		//TRUE�ŃX�y�V�����������\
	bool damage_up;	//�_���[�W��������X�y�V����
	bool get_damage_down;	//��_���[�W������X�y�V����

}SPECIAL;


enum SP_TYPE { //�v���C���[�\���̂� movement �ɓ���ăv���C���[�̓����𐧌䂷��enum

	HEAL = 0,
	DAMAGE_UP = 1,
	GET_DAMAGE_DOWN = 2,

};

void InitSpecial();
void UninitSpecial();
void UpdateSpecial();
void DrawSpecial();

void SpecialPlus();

SPECIAL* GetSpecial(void);



#endif //_SPECIAL_H_
