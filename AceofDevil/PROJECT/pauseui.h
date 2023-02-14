//=============================================================================
//
// �|�[�Y��UI���� [pauseui.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _PAUSEUI_H_
#define _PAUSEUI_H_

#include "main.h"
#include "scene.h"

#define MAX_PAUSEDATA (7)

class CScene2D;
class CInputGamePad;
class CInputKeyboard;

class CPauseUi : public CScene
{
public:
	CPauseUi(PRIORITY Priority = PRIORITY_UI);
	~CPauseUi();
	HRESULT Init(float, float, D3DXVECTOR3, float);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��

	bool GetDamage(void) { return false; }
	void Damage(int) { ; }
	void Pause(void);		//�|�[�Y����
	void PauseLift(void);	//�|�[�Y����

	static HRESULT Load(void);		//�e�N�X�`���ǂݍ���
	static void UnLoad(void);		//�e�N�X�`���j��
	static CPauseUi *Create(void);	//�쐬
	static void SetPause(bool bPause) { m_bUse = bPause; }	//�|�[�Y���邩
	static bool GetPause(void) { return m_bUse; }			//�|�[�Y����

private:
	CInputGamePad *m_pInputGamePad;				//�Q�[���p�b�h�̃|�C���^
	CInputKeyboard *m_pInputKeyboard;			//�L�[�{�[�h�̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[6];	//�e�N�X�`���ւ̃|�C���^
	static CScene2D *m_apScene[MAX_PAUSEDATA];	//UI���̃V�[��
	static bool m_bUse;							//�|�[�Y����
	int m_nSelect;								//���I��ł邩
};

#endif