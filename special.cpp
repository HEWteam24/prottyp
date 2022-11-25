/*==============================================================================

   �X�y�V�����̐��� [special.cpp]
														 Author :�@�ēc �S��
														 Date   :�@11/19
--------------------------------------------------------------------------------
�Ƃ肠�����AHP�S�񕜁A30s�_���[�W5�{�A30s��_���[�W1/5�ɂȂ��Ă܂��B
30good�ň�񔭓��B�Q�[�W�����܂��ĉ��F���Ȃ�����uY�{�^���v�܂��́uL�L�[�v�Ŕ������܂��B

�񕜁E�E�E�ΐF
�_���[�W�����E�E�E�ԐF
��_���[�W�ቺ�E�E�E�F
==============================================================================*/

#include "special.h""

//�X�y�V�����̃e�N�X�`��
static int g_SpecialFrameTexture;
static int g_SpecialNowTexture;
static int g_SpecialIconTexture;

//�X�y�V������SE
static int g_SE_Special;		

//�^�C�}�[
unsigned int timer = 0;

//�^�C�}�[�̃X�^�[�g�t���O
bool start_timer = false;

//�X�y�V�����Q�[�W�̃J���[
float colorR;
float colorG;
float colorB;
float IconcolorR;
float IconcolorG;
float IconcolorB;

SPECIAL sp;

void InitSpecial()
{
	//�e�N�X�`���̃��[�h
	g_SpecialNowTexture = LoadTexture((char*)"data/TEXTURE/HP_player_A.png");
	g_SpecialFrameTexture = LoadTexture((char*)"data/TEXTURE/HP_player_B.png");
	g_SpecialIconTexture = LoadTexture((char*)"data/TEXTURE/fade_white.png");

	//SE�̃��[�h
	char	file_SE_Special[] = "data\\SE\\SE_Special.wav";
	g_SE_Special = LoadSound(file_SE_Special);

	//������
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
	sp.type = 1;  //0�񕜁A1�^�_�������A�Q��_���ጸ

	sp.charge = 25;		//�X�y�V�����̏����l�B��o���ɂ�0�ɂ��Ă��������B
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
	case SP_TYPE::DAMAGE_UP: //�^����_���[�W����

		IconcolorR = 1.0f;
		IconcolorG = 0.0f;
		IconcolorB = 0.0f;
		break;

	case SP_TYPE::HEAL:		//�v���C���[�̗͉̑�
		IconcolorR = 0.0f;
		IconcolorG = 1.0f;
		IconcolorB = 0.0f;
		break;

	case SP_TYPE::GET_DAMAGE_DOWN:	//�v���C���[�̔�_���[�W�y��
		IconcolorR = 0.0f;
		IconcolorG = 0.0f;
		IconcolorB = 1.0f;
		break;
	}

	//�X�y�V�����Q�[�W�����܂肫�����甭���\
	if (sp.charge == SPECIAL_MAX)
	{
		colorB = 0.0f;
		sp.UseOk = true;
	}

	//Y�{�^���ŃX�y�V��������
	if (((IsButtonTriggered(0, XINPUT_GAMEPAD_Y)) || (Keyboard_IsKeyDown(KK_L))) && sp.UseOk == true)
	{
		PlaySound(g_SE_Special, 0);

		switch (sp.type) {
		case SP_TYPE::DAMAGE_UP: //�^����_���[�W����
			sp.damage_up = true;
			start_timer = true;
			break;

		case SP_TYPE::HEAL:		//�v���C���[�̗͉̑�
			player->hp = 300.0f;
			sp.charge = 0;
			sp.UseOk = false;
			colorB = 1.0f;
			break;

		case SP_TYPE::GET_DAMAGE_DOWN:	//�v���C���[�̔�_���[�W�y��
			sp.get_damage_down = true;
			start_timer = true;
			break;
		}
	}


	//�X�y�V�����̌o�ߎ��Ԃ̃^�C�}�[
	if (start_timer == true)
	{
		timer++;
		colorB = 1.0f;
		colorG = 0.0f;
		colorR = 1.0f;
	}

	//30�b�ŏI��
	if (timer >= 1800)
	{
		//�X�y�V������ǉ�����ꍇ�͂����ɂ��̃X�y�V�����̏I��������ǉ�
		sp.get_damage_down = false;
		sp.damage_up = false;


		//�^�C�}�[�ƃX�y�V�����̃��Z�b�g
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

	//HP���n
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

	//HP�o�[
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

//�X�y�V�����̑���
void SpecialPlus()
{
	if (sp.charge < 30)
	{
		sp.charge += 1;
	}
}

//�Q�b�^�[
SPECIAL* GetSpecial(void)
{
	return &sp;
}