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
		SOUND_LABEL_TUTORIALBGM,    // `[gA
		SOUND_LABEL_GAMEBGM,        // ¹
		SOUND_LABEL_BOSSBGM,        // {Xí
		SOUND_LABEL_RESULTBGM,      // UgæÊ
		SOUND_LABEL_SHATDOWNBGM,	// ©@©{XÄ
		SOUND_LABEL_PLAYERDAMAGE,	// ©@_[W
		SOUND_LABEL_CANCEL,         // LZ¹
		SOUND_LABEL_CHOICE,         // Ið¹
		SOUND_LABEL_ENEMYDAMAGE,    // GÌ_[W
		SOUND_LABEL_ENEMYSHATDOWN,  // G@Ä
		SOUND_LABEL_FIRE,           // ÎÌe
		SOUND_LABEL_GUN,            // Ge
		SOUND_LABEL_ICE,            // Xe
		SOUND_LABEL_LIGHTNING,      // d
		SOUND_LABEL_MAGICCHANGE,    // ®«ØèÖ¦
		SOUND_LABEL_PAUSE,          // |[Y¹
		SOUND_LABEL_PINCH,          // s`
		SOUND_LABEL_PRIZE,          // vCYæ¾¹
		SOUND_LABEL_THUNDER,        // e
		SOUND_LABEL_WATER,          // [U[
		SOUND_LABEL_WIND,           // ÌoA
		SOUND_LABEL_YES,            // è¹
		SOUND_LABEL_MAX
	} SOUND_LABEL;
	CSound();
	~CSound();
	static HRESULT Init(HWND hWnd);			//ú»
	static void Uninit(void);				//I¹
	static HRESULT Play(SOUND_LABEL label);	//Ä¶
	static void Stop(SOUND_LABEL label);	//â~
	static void Stop(void);					//Sâ~

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
