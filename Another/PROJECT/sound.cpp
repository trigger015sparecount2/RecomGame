//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
// TEh [sound.cpp]
// Author : Oã@q¢
//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
#include "sound.h"

//ÃIoÏ
IXAudio2 *CSound::m_pXAudio2 = NULL;								// XAudio2IuWFNgÖÌC^[tFCX
IXAudio2MasteringVoice *CSound::m_pMasteringVoice = NULL;			// }X^[{CX
IXAudio2SourceVoice *CSound::m_apSourceVoice[SOUND_LABEL_MAX] = {};	// \[X{CX
BYTE *CSound::m_apDataAudio[SOUND_LABEL_MAX] = {};					// I[fBIf[^
DWORD CSound::m_aSizeAudio[SOUND_LABEL_MAX] = {};					// I[fBIf[^TCY

																	// e¹fÞÌp[^
CSound::PARAM CSound::m_aParam[SOUND_LABEL_MAX] =
{
	{ "data/BGM/title.wav", -1 },		// ^CgBGM
	{ "data/BGM/game.wav", -1 },		// Q[
	{ "data/SE/attack.wav", 0 },		// a¹
	{ "data/SE/cancel.wav", 0 },		// LZ¹
	{ "data/SE/clear.wav", 0 },			// NA¹
	{ "data/SE/damage.wav", 0 },		// í_¹
	{ "data/SE/dodge.wav", 0 },			// ñð¹
	{ "data/SE/enemyapp.wav", 0 },		// GÁÅ¹
	{ "data/SE/enemydeath.wav", 0 },	// GÁÅ¹
	{ "data/SE/footstep.wav", 0 },		// «¹
	{ "data/SE/go.wav", 0 },			// GO
	{ "data/SE/guard.wav", 0 },			// K[h¹
	{ "data/SE/landing.wav", 0 },		// n
	{ "data/SE/ok.wav", 0 },			// OK
	{ "data/SE/pause.wav", 0 },			// |[Y
	{ "data/SE/pinch.wav", 0 },			// s`
	{ "data/SE/playerdeath.wav", 0 },	// vC[S
	{ "data/SE/ready.wav", 0 },			// READY
	{ "data/SE/select.wav", 0 }			// Ið¹
};

CSound::CSound()
{

}

CSound::~CSound()
{

}

//ú»
HRESULT CSound::Init(HWND /*hWnd*/)
{
	HRESULT hr;

	// COMCuÌú»
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2IuWFNgÌì¬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		// COMCuÌI¹
		CoUninitialize();
		return E_FAIL;
	}

	// }X^[{CXÌ¶¬
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		if (m_pXAudio2)
		{
			// XAudio2IuWFNgÌJú
			m_pXAudio2->Release();
		}

		// COMCuÌI¹
		CoUninitialize();
		return E_FAIL;
	}

	// TEhf[^Ìú»
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD filetype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// obt@ÌNA
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// TEhf[^t@CÌ¶¬
		hFile = CreateFile(m_aParam[nCntSound].filename, GENERIC_READ,
			FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEt@CÌ`FbN
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		if (filetype != 'EVAW')
		{
			return S_FALSE;
		}

		// tH[}bg`FbN
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		// I[fBIf[^ÇÝÝ
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

		// obt@ÌÝè
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aParam[nCntSound].nCntLoop;

		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// t@CðN[Y
		CloseHandle(hFile);
	}

	return S_OK;
}

//=============================================================================
// I¹
//=============================================================================
void CSound::Uninit()
{
	// êâ~
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// êâ~
			m_apSourceVoice[nCntSound]->Stop(0);

			// \[X{CXÌjü
			m_apSourceVoice[nCntSound]->DestroyVoice();

			// I[fBIf[^ÌJú
			free(m_apDataAudio[nCntSound]);
		}
	}

	// }X^[{CXÌjü
	m_pMasteringVoice->DestroyVoice();

	if (m_pXAudio2)
	{
		// XAudio2IuWFNgÌJú
		m_pXAudio2->Release();
	}

	// COMCuÌI¹
	CoUninitialize();
}

//=============================================================================
// ZOgÄ¶(â~)
//=============================================================================
HRESULT CSound::Play(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER       buffer;

	// obt@ÌÝè
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aParam[label].nCntLoop;

	// óÔæ¾
	m_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// Ä¶
	 // êâ~
		m_apSourceVoice[label]->Stop(0);

		// NA
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// o^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// Ä¶
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}

//=============================================================================
// ZOgâ~
//=============================================================================
void CSound::Stop(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// óÔæ¾
	m_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// Ä¶
	 // êâ~
		m_apSourceVoice[label]->Stop(0);

		// NA
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// ZOgâ~
//=============================================================================
void CSound::Stop()
{
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// êâ~
			m_apSourceVoice[nCntSound]->Stop(0);

			// NA
			m_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//=============================================================================
// `NÌ`FbN
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// t@C|C^ðæªÉÚ®
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// `NÌÇÝÝ
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// `Nf[^ÌÇÝÝ
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// t@C^CvÌÇÝÝ
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// t@C|C^ð`Nf[^ªÚ®
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// `Nf[^ÌÇÝÝ
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// t@C|C^ðwèÊuÜÅÚ®
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// f[^ÌÇÝÝ
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}