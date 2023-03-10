//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
// TEh [sound.h]
// Author :Oãq¢
//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,	// ^CgBGM
		SOUND_LABEL_GAMEBGM,		// ¹
		SOUND_LABEL_ATTACK,			// vC[ÌU
		SOUND_LABEL_CANCEL,			// LZ¹
		SOUND_LABEL_CLEAR,			// NA¹
		SOUND_LABEL_DAMAGE,			// GÌU
		SOUND_LABEL_DODGE,			// ñð
		SOUND_LABEL_ENEMYAPP,		// Go»
		SOUND_LABEL_ENEMYDEATH,		// GÁÅ
		SOUND_LABEL_FOOTSTEP,		// «¹
		SOUND_LABEL_GO,				// GOTC
		SOUND_LABEL_GUARD,			// K[h
		SOUND_LABEL_LANDING,		// n
		SOUND_LABEL_OK,				// è¹
		SOUND_LABEL_PAUSE,			// |[Y
		SOUND_LABEL_PINCH,			// s`
		SOUND_LABEL_PLAYERDEATH,	// vC[S
		SOUND_LABEL_READY,			// READYTC
		SOUND_LABEL_SELECT,			// Ið¹
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();
	~CSound();

	static HRESULT Init(HWND hWnd);			//ú»
	static void Uninit();					//I¹
	static HRESULT Play(SOUND_LABEL label);	//Ä¶
	static void Stop(SOUND_LABEL label);	//â~
	static void Stop();						//Sâ~

	//¹Ê²®
	static void ControlVoice(SOUND_LABEL label, float fVolume)
	{
		m_apSourceVoice[label]->SetVolume(fVolume);
	}

private:
	typedef struct
	{
		char *filename;		// t@C¼
		int nCntLoop;		// [vJEg
	} PARAM;
	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	static IXAudio2 *m_pXAudio2;									// XAudio2IuWFNgÖÌC^[tFCX
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// }X^[{CX
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// \[X{CX
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// I[fBIf[^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// I[fBIf[^TCY

	// e¹fÞÌp[^
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif
