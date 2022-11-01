/*==============================================================================

   �T�E���h���� [sound.cpp]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/

#include "sound.h"


/*------------------------------------------------------------------------------
   �萔��`
------------------------------------------------------------------------------*/
#define MAX_SOUND_NUM 100


/*------------------------------------------------------------------------------
   �v���g�^�C�v�錾
------------------------------------------------------------------------------*/
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

/*------------------------------------------------------------------------------
   �O���[�o���ϐ��̒�`
------------------------------------------------------------------------------*/
static IXAudio2 *g_pXAudio2 = NULL;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
static IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
static IXAudio2SourceVoice *g_apSourceVoice[MAX_SOUND_NUM] = {};	// �\�[�X�{�C�X
static BYTE *g_apDataAudio[MAX_SOUND_NUM] = {};						// �I�[�f�B�I�f�[�^
static DWORD g_aSizeAudio[MAX_SOUND_NUM] = {};						// �I�[�f�B�I�f�[�^�T�C�Y

static char g_SoundName[MAX_SOUND_NUM][256] = {};					// �T�E���h���o�b�t�@
static DWORD g_SoundIndex = 0;										// �\�[�X�{�C�X�z��̖����������C���f�b�N�X

/*------------------------------------------------------------------------------
   �������֐�
------------------------------------------------------------------------------*/
bool InitSound(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&g_pXAudio2, 0);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return false;
	}
	
	// �}�X�^�[�{�C�X�̐���
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if(g_pXAudio2)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return false;
	}

	return true;
}

/*------------------------------------------------------------------------------
   �I������������֐�
------------------------------------------------------------------------------*/
void UninitSound(void)
{
	// �S�ẴT�E���h���~����
	for(int nCntSound = 0; nCntSound < (int)g_SoundIndex; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
	
			// �\�[�X�{�C�X�̔j��
			g_apSourceVoice[nCntSound]->DestroyVoice();
			g_apSourceVoice[nCntSound] = NULL;
	
			// �I�[�f�B�I�f�[�^�̊J��
			free(g_apDataAudio[nCntSound]);
			g_apDataAudio[nCntSound] = NULL;
		}
	}
	
	// �}�X�^�[�{�C�X�̔j��
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COM���C�u�����̏I������
	CoUninitialize();
}

/*------------------------------------------------------------------------------
   �T�E���h�t�@�C���̓ǂݍ���
------------------------------------------------------------------------------*/
int LoadSound(char* pFilename)
{
	HANDLE hFile;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	//�ǂݍ��܂�Ă���T�E���h���𒲂ׂāA�����̂��̂�
	//���łɓǂݍ��܂�Ă����炻�̔ԍ���Ԃ�
	for (unsigned int i = 0; i < g_SoundIndex; i++)
	{
		//�T�E���h�����r
		if (strcmp(g_SoundName[i], pFilename) == 0)
		{
			return i;
		}
	}

	if (g_SoundIndex == MAX_SOUND_NUM)
	{
		MessageBox(NULL, "�ő�ǂݍ��ݐ��𒴉�", "�x���I", MB_ICONWARNING);
		return -1;
	}

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		MessageBox(NULL, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return -1;
	}

	HRESULT hr;

	// WAVE�t�@�C���̃`�F�b�N
	hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	if (dwFiletype != 'EVAW')
	{
		MessageBox(NULL, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
		return -1;
	}

	// �t�H�[�}�b�g�`�F�b�N
	hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return -1;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[g_SoundIndex], &dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
		return -1;
	}
	g_apDataAudio[g_SoundIndex] = (BYTE*)malloc(g_aSizeAudio[g_SoundIndex]);
	hr = ReadChunkData(hFile, g_apDataAudio[g_SoundIndex], g_aSizeAudio[g_SoundIndex], dwChunkPosition);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
		return -1;
	}

	// �\�[�X�{�C�X�̐���
	hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[g_SoundIndex], &(wfx.Format));
	if (FAILED(hr))
	{
		MessageBox(NULL, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
		return -1;
	}

	//�ǂݍ��񂾃T�E���h����ۑ�����
	strcpy_s(g_SoundName[g_SoundIndex], 256, pFilename);

	int retIndex = g_SoundIndex;

	//�C���f�b�N�X����i�߂�
	g_SoundIndex++;

	return retIndex;
}

void SetVolume(int index, float vol)
{
	g_apSourceVoice[index]->SetVolume(vol);
}

/*------------------------------------------------------------------------------
   �����̍Đ�
------------------------------------------------------------------------------*/
void PlaySound(int index, int loopCount)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[index];
	buffer.pAudioData = g_apDataAudio[index];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	if (loopCount < 0)
		loopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopCount  = loopCount;

	// ��Ԏ擾
	g_apSourceVoice[index]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[index]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[index]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	g_apSourceVoice[index]->SubmitSourceBuffer(&buffer);

	// �Đ�
	g_apSourceVoice[index]->Start(0);
}

/*------------------------------------------------------------------------------
   �����̒�~
------------------------------------------------------------------------------*/
void StopSound(int index)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	g_apSourceVoice[index]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		g_apSourceVoice[index]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		g_apSourceVoice[index]->FlushSourceBuffers();
	}
}

/*------------------------------------------------------------------------------
   �ǂݍ���ł��邷�ׂẲ������~
------------------------------------------------------------------------------*/
void StopSoundAll(void)
{
	// �ꎞ��~
	for(int nCntSound = 0; nCntSound < (int)g_SoundIndex; nCntSound++)
	{
		if(g_apSourceVoice[nCntSound])
		{
			// �ꎞ��~
			g_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

/*------------------------------------------------------------------------------
   WAVE�t�H�[�}�b�g�̃`�F�b�N
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
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
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
   WAVE�t�H�[�}�b�g�̓ǂݍ���
------------------------------------------------------------------------------*/
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

