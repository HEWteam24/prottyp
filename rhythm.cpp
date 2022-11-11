//====================================================
//リズム
//作成：勝沼力樹
//		2022/10/26
//====================================================
#include "rhythm.h"
#include "sound.h"
#include "game.h"
#include "texture.h"
#include "sprite.h"
#include "main.h"
#include "keyboard.h"



//曲のBPMのパターン
#define		BPM1				(60)
#define		BPM2				(120)
#define		BPM3				(90)

int			NowBPM;
int			GameSoundNo;

int			NotesNum = 0;
int			Frame;


NOTES		Notes[NOTES_MAX];
NOTESLANE	NotesLane;

//テクスチャ情報の保存変数
static	ID3D11ShaderResourceView	*g_TextureNotes;
static	char	*g_TextureNameNotesRight = NOTES_TEX_RIGHT;//テクスチャ名
static	char	*g_TextureNameNotesLeft  = NOTES_TEX_LEFT;//テクスチャ名
static	char	*g_TextureNameNotesCenter= NOTES_TEX_CENTER;//テクスチャ名
static	ID3D11ShaderResourceView	*g_TextureNotesLane;
static	char	*g_TextureNameNotesLane = NOTESLANE_TEX;//テクスチャ名

HRESULT InitRhythm()
{
	for (int i = 0; i < NOTES_MAX; i+=2) 
	{
		//ノーツ左の初期化
			Notes[i].pos = D3DXVECTOR2(NOTES_POS_X_1, NOTES_POS_Y);
			Notes[i].size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
			Notes[i].sp = D3DXVECTOR2(NOTES_SP, 0.0f);
			Notes[i].rot = 0.0f;
			Notes[i].alpha = 1.0f;
			Notes[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - Notes[i].alpha);
			Notes[i].use = false;
			Notes[i].num = 0;


			//テクスチャのロード
			Notes[i].texno = LoadTexture(g_TextureNameNotesLeft);
			if (Notes[i].texno == -1)
			{//ロードエラー
				exit(999);
			}
	

		//ノーツ右の初期化
			Notes[i + 1].pos = D3DXVECTOR2(NOTES_POS_X_2, NOTES_POS_Y);
			Notes[i + 1].size = D3DXVECTOR2(NOTES_SIZE_X, NOTES_SIZE_Y);
			Notes[i + 1].sp = D3DXVECTOR2(-NOTES_SP, 0.0f);
			Notes[i + 1].rot = 0.0f;
			Notes[i + 1].alpha = 1.0f;
			Notes[i + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - Notes[i + 1].alpha);
			Notes[i + 1].use = false;
			Notes[i + 1].num = 0;


			//テクスチャのロード
			Notes[i+1].texno = LoadTexture(g_TextureNameNotesRight);
			if (Notes[i+1].texno == -1)
			{//ロードエラー
				exit(999);
			}

			
	}
	//ノーツレーンの初期化
	NotesLane.pos = D3DXVECTOR2(NOTESLANE_POS_X, NOTESLANE_POS_Y);
	NotesLane.size = D3DXVECTOR2(NOTESLANE_SIZE_X, NOTESLANE_SIZE_Y);
	NotesLane.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	NotesLane.frame = 1;
	NotesLane.frameD = 1;

	//テクスチャのロード
	NotesLane.texno = LoadTexture(g_TextureNameNotesLane);
	if (NotesLane.texno == -1)
	{//ロードエラー
		exit(999);
	}
	NotesLane.texcent = LoadTexture(g_TextureNameNotesCenter);
	if (NotesLane.texcent == -1)
	{//ロードエラー
		exit(999);
	}

	//仮で固定のBGM
	NowBPM = BPM2;
	char	filename[] = "data\\BGM\\hoge.wav";
	GameSoundNo = LoadSound(filename);
	PlaySound(GameSoundNo, -1);
	Frame = 1;

	return	S_OK;
}

void UpdateRhythm()
{

	//ノーツのセット(BPM120の時は30フレームごと)
	if ((Frame) % 30 * NOTES_DIST == 0.0f)
	{
		SetNotes();
	}
	Frame++;
	NotesLane.frame++;

	for (int i = 0; i < NOTES_MAX; i++)
	{
		if (Notes[i].use)
		{
			Notes[i].pos.x += Notes[i].sp.x;
			Notes[i].alpha -= 0.005f * NOTES_DIST;
			if (i % 2 == 0)
			{
				//ノーツ左が真ん中に来た時消える
				if (Notes[i].pos.x + NOTES_SIZE_X / 2 > SCREEN_WIDTH / 2 - NOTES_SIZE_X / 2 + NOTES_SP * 2)
				{
					Notes[i].use = false;
					Notes[i + 1].use = false;
				}
				////ノーツ左が消えてる時右も消える
				//if (Notes[i + 1].use)
				//{
				//	
				//}
			}
			if (i % 2 == 1)
			{
				//ノーツ右が真ん中に来た時消える
				if (Notes[i].pos.x - NOTES_SIZE_X / 2 == 970 /*SCREEN_WIDTH / 2 + NOTES_SIZE_X / 2 - NOTES_SP * 2*/)
				{
					Notes[i].use = false;
				}
				////ノーツ右が消えてる時左も消える
				//if (Notes[i - 1].use)
				//{
				//	Notes[i - 1].use = false;
				//}
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

	//ノーツレーンの表示
	DrawSpriteColor(NotesLane.texno, NotesLane.pos.x, NotesLane.pos.y, NotesLane.size.x, NotesLane.size.y,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0));
	
	//ノーツ 中心
	DrawSpriteColor(NotesLane.texcent, NotesLane.pos.x, NotesLane.pos.y, NOTES_SIZE_X * 3 * 1.01f, NOTES_SIZE_Y*1.01f,
		0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 0.4, 1.0));
	for (int i = 0; i < NOTES_MAX; i++)
	{
		if (Notes[i].use)
		{
			DrawSpriteColor(Notes[i].texno, Notes[i].pos.x, Notes[i].pos.y, Notes[i].size.x, Notes[i].size.y,
				0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0, 1.0, 1.0, 1.0- Notes[i].alpha));
		}
	}


}

void SetNotes()
{
	for (int n = 0; n < NOTES_MAX; n+=2)
	{
		if (Notes[n].use==false) 
		{
			Notes[n].pos = D3DXVECTOR2(NOTES_POS_X_1, NOTES_POS_Y);
			Notes[n].use = true;
			Notes[n].num = NotesNum;
			Notes[n].alpha = 1.0f;
			NotesNum++;
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
{//リズムに合っているかの判定
	if (((Frame)  % 30 <= 4.0f) && ((Frame-4) % 30 >= 0.0f))
	{
		return true;
	}
	else
	{
		return	false;
	}
}

NOTES * GetNotes()
{
	return Notes;
}

NOTESLANE * GetNotesLane()
{
	return &NotesLane;
}

void ReleaseNotes()
{//一番真ん中に近いノーツを消す関数
	int		Max = Notes[0].num, Index = 0;

	for (int i = 1; i < NOTES_MAX; i++) {
		if (Notes[i].use) {
			if (Notes[i].num > Max) {
				Max = Notes[i].num;
				Index = i;
			}
		}
	}
	Notes[Index].use = false;
}

