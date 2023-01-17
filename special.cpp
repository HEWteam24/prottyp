/*==============================================================================

   スペシャルの制御 [special.cpp]
														 Author :　柴田 祐希
														 Date   :　11/19
--------------------------------------------------------------------------------
とりあえず、HP全回復、5sダメージ5倍、5s被ダメージ1/5になってます。
30goodで一回発動。ゲージが溜まって黄色くなったら「Yボタン」または「Lキー」で発動します。

回復・・・緑色
ダメージ増加・・・赤色
被ダメージ低下・・・青色


回復量は [special.cpp] の UpdateSpecial 内にある switch(sp.type) Case::HEAL内の数値を変更してください]

与ダメージ増加は [bullet.cpp]　内にある int Damage(){} 内の数値を変更してください。

被ダメージ低減はプレイヤーのHPが減少するところの数値を変えてください。

*/

//==============================================================================

#include "special.h""
#include "combo.h"

#define SKILL_ICON_POS_X	(1600.0f)
#define SKILL_ICON_POS_Y	( 900.0f)
#define SKILL_ICON_SIZE		( 220.0f)


//スペシャルのテクスチャ
static int g_SpecialFrameTexture;
static int g_SpecialNowTexture;
static int g_SpecialIconTexture;
static int g_TextureGoRing;
static int g_TextureCharge;

//スペシャルのSE
static int g_SE_Special;		

//タイマー
unsigned int timer = 0;

//タイマーのスタートフラグ
bool start_timer = false;

//スペシャルゲージのカラー
float colorR;
float colorG;
float colorB;
float Calpha;
float IconcolorR;
float IconcolorG;
float IconcolorB;

int chargeUv;

float GoRingrot;

SPECIAL sp;

void InitSpecial()
{
	//テクスチャのロード
	g_SpecialNowTexture = LoadTexture((char*)"data/TEXTURE/HP_player_A.png");
	g_SpecialFrameTexture = LoadTexture((char*)"data/TEXTURE/HP_player_B.png");
	g_SpecialIconTexture = LoadTexture((char*)"data/TEXTURE/fade_white.png");
	g_TextureGoRing = LoadTexture((char*)"data/TEXTURE/icon_ring.png");
	g_TextureCharge= LoadTexture((char*)"data/TEXTURE/skill_charge.png");

	//SEのロード
	char	file_SE_Special[] = "data\\SE\\SE_Special.wav";
	g_SE_Special = LoadSound(file_SE_Special);

	//初期化
	sp.IconPos.x = 0;
	sp.IconPos.y = 0;
	sp.w = 0;
	sp.h = 0;

	GoRingrot = 0.0f;

	timer = 0;
	colorR = 1.0f;
	colorG = 1.0f;
	colorB = 1.0f;
	Calpha = 0.5f;
	IconcolorR = 1.0f;
	IconcolorG = 1.0f;
	IconcolorB = 1.0f;

	chargeUv = 0;

	//sp.type = 0;  //0回復、1与ダメ増加、２被ダメ低減

	sp.charge = 0;		//スペシャルの初期値。提出時には0にしてください。
	sp.UseOk = false;
	sp.damage_up = false;
	sp.get_damage_down = false;
	start_timer = false;

	switch (sp.type) {
	case SP_TYPE::DAMAGE_UP: //与えるダメージ増加
		g_SpecialIconTexture = LoadTexture((char*)"data/TEXTURE/icon_damage.png");
		break;

	case SP_TYPE::HEAL:		//プレイヤーの体力回復
		g_SpecialIconTexture = LoadTexture((char*)"data/TEXTURE/icon_heal.png");
		break;

	case SP_TYPE::GET_DAMAGE_DOWN:	//プレイヤーの被ダメージ軽減
		g_SpecialIconTexture = LoadTexture((char*)"data/TEXTURE/icon_protect.png");
		break;
	}
}

void UninitSpecial()
{
}

void UpdateSpecial()
{
	PLAYER* player = GetPlayer();

	//switch (sp.type) {
	//case SP_TYPE::DAMAGE_UP: //与えるダメージ増加

	//	IconcolorR = 1.0f;
	//	IconcolorG = 0.0f;
	//	IconcolorB = 0.0f;
	//	break;

	//case SP_TYPE::HEAL:		//プレイヤーの体力回復
	//	IconcolorR = 0.0f;
	//	IconcolorG = 1.0f;
	//	IconcolorB = 0.0f;
	//	break;

	//case SP_TYPE::GET_DAMAGE_DOWN:	//プレイヤーの被ダメージ軽減
	//	IconcolorR = 0.0f;
	//	IconcolorG = 0.0f;
	//	IconcolorB = 1.0f;
	//	break;
	//}

	//スペシャルゲージがたまりきったら発動可能
	if (sp.charge >= SPECIAL_MAX)
	{
		colorB = 0.0f;
		sp.UseOk = true;
		Calpha = 1.0f;
	}

	//Yボタンでスペシャル発動
	if (((IsButtonTriggered(0, XINPUT_GAMEPAD_RIGHT_SHOULDER)) || (Keyboard_IsKeyDown(KK_S))) && sp.UseOk == true)
	{
		PlaySound(g_SE_Special, 0);

		switch (sp.type) {
		case SP_TYPE::DAMAGE_UP: //与えるダメージ増加
			sp.damage_up = true;
			start_timer = true;
			break;

		case SP_TYPE::HEAL:		//プレイヤーの体力回復
			player->hp = 300.0f;
			sp.charge = 0;
			sp.UseOk = false;
			colorB = 1.0f;
			break;

		case SP_TYPE::GET_DAMAGE_DOWN:	//プレイヤーの被ダメージ軽減
			sp.get_damage_down = true;
			start_timer = true;
			break;
		}
	}


	//スペシャルの経過時間のタイマー
	if (start_timer == true)
	{
		timer++;
		colorB = 1.0f;
		colorG = 0.4f;
		colorR = 1.0f;
		GoRingrot += 4.0f;
	}

	//5秒で終了
	if (timer >= 300)
	{
		//スペシャルを追加する場合はここにそのスペシャルの終了処理を追加
		sp.get_damage_down = false;
		sp.damage_up = false;


		//タイマーとスペシャルのリセット
		start_timer = false;
		timer = 0;
		sp.charge = 0;
		sp.UseOk = false;
		colorR = 1.0f;
		colorG = 1.0f;
		colorB = 1.0f;
		Calpha = 0.5f;
	}

	if (sp.UseOk == true)
	{
		GoRingrot += 1.0f;
	}

	if (sp.charge >= 15)
	{
		chargeUv = 1;
	}
	else
	{
		chargeUv = 0;
	}
}

void DrawSpecial()
{

	////HP下地
	//DrawSpriteColor(g_SpecialFrameTexture,
	//	SPECIAL_POS_X, 
	//	SPECIAL_POS_Y,
	//	SPECIAL_F_SIZE_X,
	//	SPECIAL_F_SIZE_Y,
	//	0.0f,
	//	0.0f, 
	//	1.0f,
	//	1.0f,
	//	D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	////HPバー
	//DrawSpriteColor(g_SpecialNowTexture,
	//	SPECIAL_POS_X,
	//	SPECIAL_POS_Y +((SPECIAL_MAX - sp.charge) * 15)/2,
	//	SPECIAL_SIZE_X,
	//	SPECIAL_SIZE_Y - ((SPECIAL_MAX - sp.charge) * 15),
	//	0.0f,
	//	0.0f,
	//	1.0f,
	//	1.0f,
	//	D3DXCOLOR(colorR, colorG, colorB, 1.0f));

	//アイコン チャージ
	DrawSpriteColor(g_TextureCharge,
		SKILL_ICON_POS_X,
		SKILL_ICON_POS_Y,
		SKILL_ICON_SIZE*0.85,
		SKILL_ICON_SIZE*0.85,
		1.0f / 15 * sp.charge,
		0.5f * chargeUv,
		1.0f / 15,
		0.5f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//アイコン
	DrawSpriteColor(g_SpecialIconTexture,
		SKILL_ICON_POS_X,
		SKILL_ICON_POS_Y,
		SKILL_ICON_SIZE,
		SKILL_ICON_SIZE,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, Calpha));


	//リング
		GetDeviceContext()->PSSetShaderResources(0, 1,
			GetTexture(g_TextureGoRing));
		DrawSpriteColorRotation(
			SKILL_ICON_POS_X,
			SKILL_ICON_POS_Y,
			SKILL_ICON_SIZE*1.1,
			SKILL_ICON_SIZE*1.1,
			GoRingrot,
			D3DXCOLOR(colorR, colorG, colorB, 1.0f),
			0.0f,
			1.0f,
			1.0f,
			1
		);

		//リング
		GetDeviceContext()->PSSetShaderResources(0, 1,
			GetTexture(g_TextureGoRing));
		DrawSpriteColorRotation(
			SKILL_ICON_POS_X,
			SKILL_ICON_POS_Y,
			SKILL_ICON_SIZE * 0.95,
			SKILL_ICON_SIZE * 0.95,
			GoRingrot*0.8,
			D3DXCOLOR(colorR*0.8, colorG*0.8, colorB*0.8, 1.0f),
			0.0f,
			1.0f,
			1.0f,
			1
		);

}

//スペシャルの増加
void SpecialPlus()
{
	if (sp.charge < SPECIAL_MAX)
	{
		sp.charge += 1 + (GetComboScoreUp() / 2);
	}
}

//ゲッター
SPECIAL* GetSpecial(void)
{
	return &sp;
}



