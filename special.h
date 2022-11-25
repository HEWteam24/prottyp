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

#define SPECIAL_MAX (30) //スペシャル発動に必要なコンボ数
#define SPECIAL_POS_X		(CENTER_X+530.0f)		//スペシャルのUIポジション				
#define	SPECIAL_POS_Y		(CENTER_Y+225.0)		//スペシャルのUIポジション							
#define	SPECIAL_SIZE_X	(59.9f)						//スペシャル現在値のサイズ						
#define	SPECIAL_SIZE_Y	(450.0f)					//スペシャル現在値のサイズ					
#define	SPECIAL_F_SIZE_X	(60.0f)					//スペシャルフレームのサイズ						
#define	SPECIAL_F_SIZE_Y	(450.0f)				//スペシャルフレームのサイズ						


typedef struct {

	D3DXVECTOR2		IconPos; //スペシャルゲージの場所
	
	float w, h;		//スペシャルゲージのサイズ

	int type;		//選択したスペシャルの種類
	int	charge;		//スペシャルをチャージしている数値

	bool UseOk;		//TRUEでスペシャルが発動可能
	bool damage_up;	//ダメージが増えるスペシャル
	bool get_damage_down;	//被ダメージが減るスペシャル

}SPECIAL;


enum SP_TYPE { //プレイヤー構造体の movement に入れてプレイヤーの動きを制御するenum

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
