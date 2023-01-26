//====================================================
//���Y��
//�쐬�F�����͎�
//		2022/10/26
//====================================================
#include "rhythm.h"
#include "sound.h"
#include "game.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "keyboard.h"
#include "enemybullet.h"
#include "effect.h"


//�Ȃ�BPM�̃p�^�[��
#define		BPM1				(150)
#define		BPM2				(120)
#define		BPM3				(90)

int			NowBPM;
int			GameSoundNo;

int			NotesNum = 1;
int			Frame;

int			sp;
float		NotesT = 0.0f;
int			errors = 0;
NOTES		Notes[NOTES_MAX];
NOTESLANE	NotesLane;
int			BGMError;

//�e�N�X�`�����̕ۑ��ϐ�
static	ID3D11ShaderResourceView	*g_TextureNotes;
static	char	*g_TextureNameNotesRight = NOTES_TEX_RIGHT;//�e�N�X�`����
static	char	*g_TextureNameNotesLeft  = NOTES_TEX_LEFT;//�e�N�X�`����
static	char	*g_TextureNameNotesCenter= NOTES_TEX_CENTER;//�e�N�X�`����
static	ID3D11ShaderResourceView	*g_TextureNotesLane;
static	char	*g_TextureNameNotesLane = NOTESLANE_TEX;//�e�N�X�`����
static	int		g_TextureNameStageProg;
static	int		g_TextureNameProgFlag;
static	int		g_TextureNameRunPlayer;

int Notestipindex1, Notestipindex2,indexNum;
int Notestip[10][10]
{//15�t���[������
	{1,0,1,0,1,0,1,0},
	{1,0,1,0,1,0,1,0},
	{1,0,1,0,1,0,1,0},
};
//BPM90��24�t���[���ň��
HRESULT InitRhythm(int stagenum)
{
	char	filename0[] = "data\\BGM\\00_Tutorial_120.wav";
	char	filename1[] = "data\\BGM\\01_Zarigani_120.wav";
	char	filename2[] = "data\\BGM\\02_Unagi_120.wav";
	char	filename3[] = "data\\BGM\\03_Tako_120.wav";
	char	filename4[] = "data\\BGM\\04_Shark_120.wav";
	char	filename5[] = "data\\BGM\\05_Shishamo_150.wav";
	char	filename6[] = "data\\BGM\\06_Zarigani_150.wav";
	char	filename7[] = "data\\BGM\\07_Unadon_150.wav";
	char	filename8[] = "data\\BGM\\08_Shiokara_150.wav";
	char	filename9[] = "data\\BGM\\09_Jawge_150.wav";
	char	filename10[]= "data\\BGM\\10_FullArmor_150.wav";


	switch (stagenum)
	{
	case 0://�`���[�g���A��

		GameSoundNo = LoadSound(filename0);

		Notestipindex1 = 1;
		indexNum = 8;
		errors = 0;
		sp = 10.8f;
		NowBPM = BPM2;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = -10;
		break;
	case 1://�U���K�j

		GameSoundNo = LoadSound(filename1);

		Notestipindex1 = 1;
		indexNum = 8;
		errors = 0;
		sp = 10.8f;
		NowBPM = BPM2;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = 0;
		break;
	case 2://�E�i�M

		GameSoundNo = LoadSound(filename2);

		Notestipindex1 = 1;
		indexNum = 8;
		errors = 2;
		sp = 10.8f;
		NowBPM = BPM2;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = 0;
		break;
	case 3://�^�R

		GameSoundNo = LoadSound(filename3);

		Notestipindex1 = 1;
		indexNum = 8;
		errors = -4;
		sp = 10.8f;
		NowBPM = BPM2;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = 0;
		break;
	case 4://�T��


		GameSoundNo = LoadSound(filename4);

		Notestipindex1 = 1;
		indexNum = 8;
		errors = 0;
		sp = 10.8f;
		NowBPM = BPM2;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = 0;
		break;

	case 5://�V�V����

		GameSoundNo = LoadSound(filename5);

		Notestipindex1 = 2;
		indexNum = 8;
		errors = 0;
		sp = 12.0f;
		NowBPM = BPM1;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = 0;
		break;
	case 6://�U���K�j��	//�����k

		GameSoundNo = LoadSound(filename6);

		Notestipindex1 = 2;
		indexNum = 8;
		errors = 0;
		sp = 12.0f;
		NowBPM = BPM1;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = 0;
		break;
	case 7://�E�i�M��	//���ȏd

		GameSoundNo = LoadSound(filename7);

		Notestipindex1 = 2;
		indexNum = 8;
		errors = 0;
		sp = 12.0f;
		NowBPM = BPM1;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = 0;
		break;
	case 8://�^�R��		//�V�I�J������

		GameSoundNo = LoadSound(filename8);

		Notestipindex1 = 2;
		indexNum = 8;
		errors = 0;
		sp = 12.0f;
		NowBPM = BPM1;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = 0;
		break;
	case 9://�T����		//�W���[�W

		GameSoundNo = LoadSound(filename9);

		Notestipindex1 = 2;
		indexNum = 8;
		errors = -1;
		sp = 12.0f;
		NowBPM = BPM1;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = -150;
		break;
	case 10://�V�V������ //�t���A�[�}�[�U���K�j

		GameSoundNo = LoadSound(filename10);

		Notestipindex1 = 2;
		indexNum = 8;
		errors = -1;
		sp = 12.0f;
		NowBPM = BPM1;
		NotesT = (60.0f / (NowBPM / 60.0f)) / 2.0f;
		BGMError = 330;
		break;
	default:
		break;
	}

	for (int i = 0; i < NOTES_MAX; i += 2) 
	{
		//�m�[�c���̏�����
			Notes[i].pos = D3DXVECTOR2(NOTES_POS_X_1, NOTES_POS_Y);
			Notes[i].size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
			Notes[i].sp = D3DXVECTOR2(sp, 0.0f);
			Notes[i].rot = 0.0f;
			Notes[i].alpha = 1.0f;
			Notes[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - Notes[i].alpha);
			Notes[i].use = false;
			Notes[i].num = -1;


			//�e�N�X�`���̃��[�h
			Notes[i].texno = LoadTexture(g_TextureNameNotesLeft);
			if (Notes[i].texno == -1)
			{//���[�h�G���[
				exit(999);
			}
	

		//�m�[�c�E�̏�����
			Notes[i + 1].pos = D3DXVECTOR2(NOTES_POS_X_2, NOTES_POS_Y);
			Notes[i + 1].size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
			Notes[i + 1].sp = D3DXVECTOR2(-sp, 0.0f);
			Notes[i + 1].rot = 0.0f;
			Notes[i + 1].alpha = 1.0f;
			Notes[i + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - Notes[i + 1].alpha);
			Notes[i + 1].use = false;
			Notes[i + 1].num = -1;


			//�e�N�X�`���̃��[�h
			Notes[i+1].texno = LoadTexture(g_TextureNameNotesRight);
			if (Notes[i+1].texno == -1)
			{//���[�h�G���[
				exit(999);
			}

			
	}
	//�m�[�c���[���̏�����
	NotesLane.pos = D3DXVECTOR2(NOTESLANE_POS_X, NOTESLANE_POS_Y);
	NotesLane.size = D3DXVECTOR2(NOTESLANE_SIZE_X, NOTESLANE_SIZE_Y);
	NotesLane.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̃��[�h
	NotesLane.texno = LoadTexture(g_TextureNameNotesLane);
	if (NotesLane.texno == -1)
	{//���[�h�G���[
		exit(999);
	}
	NotesLane.texcent = LoadTexture(g_TextureNameNotesCenter);
	if (NotesLane.texcent == -1)
	{//���[�h�G���[
		exit(999);
	}

	g_TextureNameRunPlayer = LoadTexture((char*)"data/TEXTURE/player.png");
	if (g_TextureNameRunPlayer == -1)
	{
		exit(999);
	}
	g_TextureNameStageProg = LoadTexture((char*)"data/TEXTURE/UI_StageProg.png");
	if (g_TextureNameStageProg == -1)
	{
		exit(999);
	}
	g_TextureNameProgFlag = LoadTexture((char*)"data/TEXTURE/UI_ProgFlag.png");
	if (g_TextureNameProgFlag == -1)
	{
		exit(999);
	}
	
	Frame = 0;
	

	Notestipindex2 = 0;
	return	S_OK;
}

void UpdateRhythm()
{
	

	if (Frame == 120)
	{
		PlaySound(GameSoundNo, 0);
	}
	Frame++;
	if (Frame >= 120)
	{
		if (((Frame - errors) % (int)NotesT) == 0.0f)
		{
			if (Notestip[Notestipindex1][Notestipindex2 % indexNum] == 1)
			{
				SetNotes();
			}
			if ((Frame - errors) % ((int)NotesT * 4)  == 0.0f) {
				SETBULLET();
			}
			Notestipindex2++;
		}

		for (int i = 0; i < NOTES_MAX; i++)
		{
			if (!Notes[i].use) continue;

			Notes[i].pos.x += Notes[i].sp.x;
			Notes[i].alpha -= 0.01f * NOTES_DIST;
			if (i % 2 == 0)
			{
				if (Notes[i].pos.x + NOTES_SIZE_X / 2 >= SCREEN_WIDTH / 2 - NOTES_SIZE_X / 2) {
 					Notes[i].alpha += 0.065f * NOTES_DIST;
					Notes[i+1].alpha += 0.065f * NOTES_DIST;
				}
				//�m�[�c�����^�񒆂ɗ���������������
				if (Notes[i].pos.x + NOTES_SIZE_X / 2 >= SCREEN_WIDTH / 2 + 25.0f)
				{
					Notes[i].use = false;
					Notes[i + 1].use = false;
				}
			}
		}
	}

}

void UninitRhythm()
{
	if (g_TextureNotes)
	{
		g_TextureNotes->Release();
		g_TextureNotes = NULL;
	}
	if (g_TextureNotesLane)
	{
		g_TextureNotesLane->Release();
		g_TextureNotesLane = NULL;
	}

	StopSound(GameSoundNo);
}

void DrawRhythm()
{
	//�m�[�c���[���̕\��
	DrawSpriteColor(NotesLane.texno, NotesLane.pos.x, NotesLane.pos.y, NotesLane.size.x, NotesLane.size.y,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	
	//�m�[�c ���S
	DrawSpriteColor(NotesLane.texcent, NotesLane.pos.x, NotesLane.pos.y, NOTES_SIZE_X * 3 * 1.01f, NOTES_SIZE_Y*1.01f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 0.4, 1.0));
	for (int i = 0; i < NOTES_MAX; i++)
	{
		if (!Notes[i].use) continue;

		DrawSpriteColor(Notes[i].texno, Notes[i].pos.x, Notes[i].pos.y, Notes[i].size.x, Notes[i].size.y,
			0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0 - Notes[i].alpha));
	}


	DrawSpriteColor(g_TextureNameStageProg, 1700.0f, 470.0f, 40.0f, 440.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));

	DrawSpriteColor(g_TextureNameProgFlag, 1710.0f, 240.0f, 50.0f, 50.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));


	DrawSpriteColor(g_TextureNameRunPlayer, 1700.0f, 700.0f - ((Frame - 120) * 0.06f), 20.0f,60.0f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
}

void SetNotes()
{
	for (int n = 0; n < NOTES_MAX; n += 2)
	{
		if (!Notes[n].use)
		{
			Notes[n].pos = D3DXVECTOR2(NOTES_POS_X_1, NOTES_POS_Y);
			Notes[n].use = true;
			Notes[n].num = NotesNum;
			Notes[n].alpha = 1.0f;

			Notes[n + 1].pos = D3DXVECTOR2(NOTES_POS_X_2, NOTES_POS_Y);
			Notes[n + 1].use = true;
			Notes[n + 1].alpha = 1.0f;
			Notes[n + 1].num = NotesNum;
			NotesNum++;

			return;
		}
	}
}

bool GetRhythm()
{//���Y���ɍ����Ă��邩�̔���
	//�m�[�c�̍��W�Ŕ����
	for (int i = 0; i < NOTES_MAX; i += 2) {
		if (Notes[i].use) {
			if (Notes[i].pos.x < (880 + (Notes[i].sp.x * 5.0f)) && Notes[i].pos.x >(880 - (Notes[i].sp.x * 3.0f))) {
				return true;
			}
		}
	}
	return	false;
}

NOTES * GetNotes()
{
	return Notes;
}

int  GetFreame()
{
	return Frame;
}

void ReleaseNotes()
{//��Ԑ^�񒆂ɋ߂��m�[�c�������֐�

	for (int i = 0; i < NOTES_MAX; i += 2) {
		if (!Notes[i].use) continue;
		if (Notes[i].pos.x < (880 + (Notes[i].sp.x * 6.0f)) && Notes[i].pos.x >(880 - (Notes[i].sp.x * 6.0f))) {
			SetEffect(EFFECT_4, Notes[i].pos, Notes[i].size+ D3DXVECTOR2(130.0f,130.0f));
			SetEffect(EFFECT_4, Notes[i].pos, Notes[i].size + D3DXVECTOR2(130.0f, 130.0f));
			SetEffect(EFFECT_4, Notes[i].pos, Notes[i].size + D3DXVECTOR2(130.0f, 130.0f));
			SetEffect(EFFECT_3, Notes[i + 1].pos, Notes[i + 1].size + D3DXVECTOR2(130.0f, 130.0f));
			SetEffect(EFFECT_3, Notes[i + 1].pos, Notes[i + 1].size + D3DXVECTOR2(130.0f, 130.0f));
			SetEffect(EFFECT_3, Notes[i + 1].pos, Notes[i + 1].size + D3DXVECTOR2(130.0f, 130.0f));
			Notes[i].use = false;
			Notes[i + 1].use = false;
			break;
		}
	}
}

bool	MusicEnd()
{
	if ((Frame - 120) < 120 * 60 + BGMError) {
		return false;
	}
	else {
		return true;
	}
}

int BGM_RE()
{
	return GameSoundNo;
}