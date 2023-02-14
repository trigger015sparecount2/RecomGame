//=============================================================================
//
// �^�C�g���V�[�� [title.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"

//�O���錾
class CInputKeyboard;
class CInputGamePad;
class CScene2D;

class CTitle : public CScene
{
public:
	CTitle(PRIORITY Priority = PRIORITY_BG);
	~CTitle();

	HRESULT Init(float fWidth, float fHeight, D3DXVECTOR3 pos, float fTexSize);	//������
	void Uninit(void);						//�I��
	void Update(void);						//�X�V
	void Draw(void);						//�`��
	bool GetDamage(void) { return false; }	//�_���[�W�󂯂邩
	void Damage(int) { ; }					//�_���[�W����

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	static CScene2D *m_pScene2D;			//�V�[��
	CInputKeyboard *m_pInputKeyboard;		//�L�[�{�[�h�̃|�C���^
	CInputGamePad *m_pInputGamePad;			//�Q�[���p�b�h�̃|�C���^
};
#endif