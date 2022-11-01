/*==============================================================================

   サウンド処理 [sound.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "sound.h"


/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/
#define MAX_SOUND_NUM 100


/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
static IXAudio2 *g_pXAudio2 = NULL;									// XAudio2オブジェクトへのインターフェイス
static IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// マスターボイス
static IXAudio2SourceVoice *g_apSourceVoice[MAX_SOUND_NUM] = {};	// ソースボイス
static BYTE *g_apDataAudio[MAX_SOUND_NUM] = {};						// オーディオデータ
static DWORD g_aSizeAudio[MAX_SOUND_NUM] = {};						// オーディオデータサイズ

static char g_SoundName[MAX_SOUND_NUM][256] = {};					// サウンド名バッファ
static DWORD g_SoundIndex = 0;										// ソースボイス配列の末尾を示すインデックス

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
bool InitSound(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return false;
	}
	
	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return false;
	}

	return true;
}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitSound(void)
{
	// 全てのサウンドを停止する
	for(int nCntSound = 0; nCntSound < (int)g_SoundIndex; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// ソースボイスの破棄
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// オーディオデータの開放
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}

/*------------------------------------------------------------------------------
   サウンドファイルの読み込み
------------------------------------------------------------------------------*/
int LoadSound(char* pFilename)
{
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	//読み込まれているサウンド名を調べて、同名のものが
	//すでに読み込まれていたらその番号を返す
	for (unsigned int i = 0; i < g_SoundIndex; i++)
	{
		//サウンド名を比較
		if (strcmp(g_SoundName[i], pFilename) == 0)
		{
			return i;
		}
	}

	if (g_SoundIndex == MAX_SOUND_NUM)
	{
		MessageBox(NULL, "最大読み込み数を超過", "警告！", MB_ICONWARNING);
		return -1;
	}

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
		return -1;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		MessageBox(NULL, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
		return -1;
	}

	HRESULT hr;

	// WAVEファイルのチェック
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return -1;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return -1;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
		return -1;
	}

	// フォーマットチェック
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
		return -1;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
		return -1;
	}

	// オーディオデータ読み込み
	hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[g_SoundIndex], &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
		return -1;
	}
	g_apDataAudio[g_SoundIndex] = (BYTE*)malloc(g_aSizeAudio[g_SoundIndex]);
	hr = ReadChunkData(hFile, g_apDataAudio[g_SoundIndex], g_aSizeAudio[g_SoundIndex], dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
		return -1;
	}

	// ソースボイスの生成
	hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[g_SoundIndex], &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
		return -1;
	}

	//読み込んだサウンド名を保存する
	strcpy_s(g_SoundName[g_SoundIndex], 256, pFilename);

	int retIndex = g_SoundIndex;

	//インデックスを一つ進める
	g_SoundIndex++;

	return retIndex;
}

void SetVolume(int index, float vol)
{
	g_apSourceVoice[index]->SetVolume(vol);
}

/*------------------------------------------------------------------------------
   音声の再生
------------------------------------------------------------------------------*/
void PlaySound(int index, int loopCount)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[index];
	buffer.pAudioData = g_apDataAudio[index];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopCount  = loopCount;

	// 状態取得
	g_apSourceVoice[index]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[index]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[index]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	g_apSourceVoice[index]->SubmitSourceBuffer(&buffer);

	// 再生
	g_apSourceVoice[index]->Start(0);
}

/*------------------------------------------------------------------------------
   音声の停止
------------------------------------------------------------------------------*/
void StopSound(int index)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_apSourceVoice[index]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// 再生中
		// 一時停止
		g_apSourceVoice[index]->Stop(0);

		// オーディオバッファの削除
		g_apSourceVoice[index]->FlushSourceBuffers();
	}
}

/*------------------------------------------------------------------------------
   読み込んでいるすべての音声を停止
------------------------------------------------------------------------------*/
void StopSoundAll(void)
{
	// 一時停止
	for(int nCntSound = 0; nCntSound < (int)g_SoundIndex; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// 一時停止
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

/*------------------------------------------------------------------------------
   WAVEフォーマットのチェック
------------------------------------------------------------------------------*/
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

/*------------------------------------------------------------------------------
   WAVEフォーマットの読み込み
------------------------------------------------------------------------------*/
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

