//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"

class CFade
{
public:
	//�t�F�[�h�̎��
	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	} FADE;

	CFade();			//�R���X�g���N�^
	~CFade();			//�f�X�g���N�^
	HRESULT Init(void);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��

	static FADE GetFade(void) { return m_fade; }	//�t�F�[�h�̎�ނ�Ԃ�
	static void SetFade(CManager::MODE modenext);	//�t�F�[�h�J�n

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_FadeColor;						//�F

	static CManager::MODE m_mode;				//���̃��[�h
	static FADE m_fade;							//�t�F�[�h�̎��

};
#endif