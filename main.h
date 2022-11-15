/*==============================================================================

   テクスチャの描画 [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "xinput.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1920)						// ウインドウの幅
#define SCREEN_HEIGHT	(1080)						// ウインドウの高さ

#define CENTER_X		(SCREEN_WIDTH/2)					//中心X
#define CENTER_Y		(SCREEN_HEIGHT/2)					//中心Y

#define LANE_SIZE_X		(170.0f)						//レーンの幅
#define LANE_SIZE_Y		(1080.0f)						//レーンの高さ

#define PLAYER_SIZE_X	(100*0.6)						//プレイヤーの幅
#define PLAYER_SIZE_Y	(360*0.6)						//プレイヤーの高さ

#define PLAYER_POS_DEFAULT_X	(CENTER_X)			//プレイヤーの位置
#define PLAYER_POS_DEFAULT_Y	(CENTER_Y+380.0f)	//プレイヤーの位置

#define PLAYER_HP_DEFAULT	(300.0f)
#define GOOD_BAD_X			(400.0f*0.7f)
#define GOOD_BAD_Y			(100.0f*0.7f)



//ノーツの初期値
#define		NOTES_MAX			(20)
#define		NOTES_POS_X_1		(582.5f)
#define		NOTES_POS_X_2		(1337.5f)
#define		NOTES_POS_Y			(SCREEN_HEIGHT-100)
#define		NOTES_SIZE_X		(75.0f)
#define		NOTES_SIZE_Y		(75.0f)
#define		NOTES_DIST			(6)
#define		NOTES_SP			(1.5f*NOTES_DIST)
#define		NOTES_TEX_RIGHT			(((char*)"data\\texture\\notes_right.png"))
#define		NOTES_TEX_LEFT			(((char*)"data\\texture\\notes_left.png"))
#define		NOTES_TEX_CENTER		(((char*)"data\\texture\\notes_center.png"))
#define		NOTESLANE_POS_X		(SCREEN_WIDTH/2)
#define		NOTESLANE_POS_Y		(NOTES_POS_Y)
#define		NOTESLANE_SIZE_X	(LANE_SIZE_X*5)
#define		NOTESLANE_SIZE_Y	(100.0f)
#define		NOTESLANE_TEX		(((char*)"data\\texture\\notes_lane.png"))

#define		SCORE_SIZE_X		(45)
#define		SCORE_SIZE_Y		(60)
#define		SCORE_POS_X		(1860 - (i * SCORE_SIZE_X))
#define		SCORE_POS_Y		(80.0f)
#define		SCOER_DIGIT		(8)

#define		SCORETEXT_POS_X				(1580.0f)
#define		SCORETEXT_POS_Y				(25.0f)
#define		SCORETEXT_SIZE_X			(100)
#define		SCORETEXT_SIZE_Y			(45)

#define		COMBO_SIZE_X	(190.0f)						//プレイヤーの幅
#define		COMBO_SIZE_Y	(220.0f)						//プレイヤーの高さ
#define		COMBO_TEX		(((char*)"data\\texture\\number.png"))
#define		COMBO_DIGIT		(3)
#define		COMBO_UV_W		(0.2)
#define		COMBO_UV_H		(0.2)
#define		COMBO_POS_X		(SCREEN_WIDTH/2+COMBO_SIZE_X - (i * COMBO_SIZE_X))
#define		COMBO_POS_Y		(SCREEN_HEIGHT/2)

#define		COMBOTEXT_POS_X				(SCREEN_WIDTH/2)
#define		COMBOTEXT_POS_Y				(SCREEN_HEIGHT/2-170)
#define		COMBOTEXT_SIZE_X			(230)
#define		COMBOTEXT_SIZE_Y			(80)

#define		COMBOMAG_SIZE_X				(85.0f)
#define		COMBOMAG_SIZE_Y				(100.0f)
#define		COMBOMAG_POS_X				(SCREEN_WIDTH/2+COMBOMAG_SIZE_X+750 - (i * COMBOMAG_SIZE_X))
#define		COMBOMAG_POS_Y				(SCREEN_HEIGHT/2-170)


//レーンの初期値
#define		LANE_MAX			(5)				//レーン数
#define		LANE_DRAW_SIZE_X	(150)
#define		LANE_DRAW_SIZE_Y	(SCREEN_HEIGHT)

#define			PLAYER_HP_POS_X		(CENTER_X+460.0f)							//プレイヤー体力ゲージ座標X
#define			PLAYER_HP_POS_Y		(CENTER_Y)									//プレイヤー体力ゲージ座標Y
#define			PLAYER_HP_SIZE_X	(50.0f)										//プレイヤー体力サイズX
#define			PLAYER_HP_SIZE_Y	(900.0f)									//プレイヤー体力サイズY
#define			PLAYER_HPB_SIZE_X	(60.0f)										//プレイヤー体力サイズX
#define			PLAYER_HPB_SIZE_Y	(910.0f)									//プレイヤー体力サイズY
#define			PLAYER_HP_TEX_A		((char*)"data\\texture\\enemyHpBar00.png")	//プレイヤーテクスチャ
#define			PLAYER_HP_TEX_B		((char*)"data\\texture\\enemyHpBar01.png")	//プレイヤーテクスチャ


//シーンの定義
enum SCENE
{
	SCENE_NONE,		//シーン無し
	SCENE_TITLE,	//タイトル画面
	SCENE_GAME,		//ゲーム本編
	SCENE_RESULT,	//リザルト画面
	SCENE_GAMEOVER,

	SCENE_NUM,		//終端コード
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

void SetScene(SCENE nextScene);
float frand(void);
