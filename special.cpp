/*==============================================================================

   スペシャルの制御 [special.cpp]
														 Author :　柴田 祐希
														 Date   :　11/19
--------------------------------------------------------------------------------
とりあえず、HP全回復、30sダメージ5倍、30s被ダメージ1/5になってます。
30goodで一回発動。ゲージが溜まって黄色くなったら「Yボタン」または「Lキー」で発動します。

回復・・・緑色
ダメージ増加・・・赤色
被ダメージ低下・・・青色
==============================================================================*/

#include "special.h""

//スペシャルのテクスチャ
static int g_SpecialFrameTexture;
static int g_SpecialNowTexture;
static int g_SpecialIconTexture;

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
float IconcolorR;
float IconcolorG;
float IconcolorB;

SPECIAL sp;

void InitSpecial()
{
	//テクスチャのロード
	g_SpecialNowTexture = LoadTexture((char*)"data/TEXTURE/HP_player_A.png");
	g_SpecialFrameTexture = LoadTexture((char*)"data/TEXTURE/HP_player_B.png");
	g_SpecialIconTexture = LoadTexture((char*)"data/TEXTURE/fade_white.png");

	//SEのロード
	char	file_SE_Special[] = "data\\SE\\SE_Special.wav";
	g_SE_Special = LoadSound(file_SE_Special);

	//初期化
	sp.IconPos.x = 0;
	sp.IconPos.y = 0;
	sp.w = 0;
	sp.h = 0;

	timer = 0;
	colorR = 1.0f;
	colorG = 1.0f;
	colorB = 1.0f;
	IconcolorR = 1.0f;
	IconcolorG = 1.0f;
	IconcolorB = 1.0f;
	sp.type = 1;  //0回復、1与ダメ増加、２被ダメ低減

	sp.charge = 25;		//スペシャルの初期値。提出時には0にしてください。
	sp.UseOk = false;
	sp.damage_up = false;
	sp.get_damage_down = false;
	start_timer = false;
}

void UninitSpecial()
{
}

void UpdateSpecial()
{
	PLAYER* player = GetPlayer();

	switch (sp.type) {
	case SP_TYPE::DAMAGE_UP: //与えるダメージ増加

		IconcolorR = 1.0f;
		IconcolorG = 0.0f;
		IconcolorB = 0.0f;
		break;

	case SP_TYPE::HEAL:		//プレイヤーの体力回復
		IconcolorR = 0.0f;
		IconcolorG = 1.0f;
		IconcolorB = 0.0f;
		break;

	case SP_TYPE::GET_DAMAGE_DOWN:	//プレイヤーの被ダメージ軽減
		IconcolorR = 0.0f;
		IconcolorG = 0.0f;
		IconcolorB = 1.0f;
		break;
	}

	//スペシャルゲージがたまりきったら発動可能
	if (sp.charge == SPECIAL_MAX)
	{
		colorB = 0.0f;
		sp.UseOk = true;
	}

	//Yボタンでスペシャル発動
	if (((IsButtonTriggered(0, XINPUT_GAMEPAD_Y)) || (Keyboard_IsKeyDown(KK_L))) && sp.UseOk == true)
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
		colorG = 0.0f;
		colorR = 1.0f;
	}

	//30秒で終了
	if (timer >= 1800)
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
		colorG = 0.0f;
		colorB = 1.0f;
	}

}

void DrawSpecial()
{

	//HP下地
	DrawSpriteColor(g_SpecialFrameTexture,
		SPECIAL_POS_X, 
		SPECIAL_POS_Y,
		SPECIAL_F_SIZE_X,
		SPECIAL_F_SIZE_Y,
		0.0f,
		0.0f, 
		1.0f,
		1.0f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//HPバー
	DrawSpriteColor(g_SpecialNowTexture, 
		SPECIAL_POS_X,
		SPECIAL_POS_Y,
		SPECIAL_SIZE_X,
		SPECIAL_SIZE_Y - ((SPECIAL_MAX - sp.charge) * 15),
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		D3DXCOLOR(colorR, colorG, colorB, 1.0f));

	DrawSpriteColor(g_SpecialIconTexture,
		1775.0f,
		900.0f,
		200.0f,
		200.0f,
		0.0f,
		0.0f,
		1.0f,
		1.0f,
		D3DXCOLOR(IconcolorR, IconcolorG, IconcolorB, 1.0f));
}

//スペシャルの増加
void SpecialPlus()
{
	if (sp.charge < 30)
	{
		sp.charge += 1;
	}
}

//ゲッター
SPECIAL* GetSpecial(void)
{
	return &sp;
}