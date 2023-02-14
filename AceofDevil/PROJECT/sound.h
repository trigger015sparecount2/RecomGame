//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
// �T�E���h���� [sound.h]
// Author :�O��q��
//�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{�{
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_TITLEBGM = 0,	// �^�C�g��BGM
		SOUND_LABEL_TUTORIALBGM,    // �`���[�g���A��
		SOUND_LABEL_GAMEBGM,        // ����
		SOUND_LABEL_BOSSBGM,        // �{�X��
		SOUND_LABEL_RESULTBGM,      // ���U���g���
		SOUND_LABEL_SHATDOWNBGM,	// ���@���{�X����
		SOUND_LABEL_PLAYERDAMAGE,	// ���@�_���[�W
		SOUND_LABEL_CANCEL,         // �L�����Z����
		SOUND_LABEL_CHOICE,         // �I����
		SOUND_LABEL_ENEMYDAMAGE,    // �G�̃_���[�W
		SOUND_LABEL_ENEMYSHATDOWN,  // �G�@����
		SOUND_LABEL_FIRE,           // �΂̒e
		SOUND_LABEL_GUN,            // �G�e
		SOUND_LABEL_ICE,            // �X�e
		SOUND_LABEL_LIGHTNING,      // �d��
		SOUND_LABEL_MAGICCHANGE,    // �����؂�ւ�
		SOUND_LABEL_PAUSE,          // �|�[�Y��
		SOUND_LABEL_PINCH,          // �s���`
		SOUND_LABEL_PRIZE,          // �v���C�Y�擾��
		SOUND_LABEL_THUNDER,        // ���e
		SOUND_LABEL_WATER,          // �����[�U�[
		SOUND_LABEL_WIND,           // ���̃o���A
		SOUND_LABEL_YES,            // ���艹
		SOUND_LABEL_MAX
	} SOUND_LABEL;
	CSound();
	~CSound();
	static HRESULT Init(HWND hWnd);			//������
	static void Uninit(void);				//�I��
	static HRESULT Play(SOUND_LABEL label);	//�Đ�
	static void Stop(SOUND_LABEL label);	//��~
	static void Stop(void);					//�S��~

private:
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;
	static HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	static HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	static IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y

																	// �e���f�ނ̃p�����[�^
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif
