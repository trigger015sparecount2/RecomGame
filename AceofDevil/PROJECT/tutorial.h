//=============================================================================
//
// �`���[�g���A���V�[�� [tutorial.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "scene.h"

class CInputKeyboard;
class CInputGamePad;

class CTutorial : public CScene
{
public:
	CTutorial(PRIORITY Priority = PRIORITY_BG);
	~CTutorial();

	HRESULT Init(float, float, D3DXVECTOR3, float);	//������
	void Uninit(void);						//�I��
	void Update(void);						//�X�V
	void Draw(void);						//�`��
	bool GetDamage(void) { return false; }	//�_���[�W�󂯂邩
	void Damage(int) { ; }					//�_���[�W����

private:
	int m_nTime;						//����
	CInputKeyboard *m_pInputKeyboard;	//�L�[�{�[�h�̃|�C���^
	CInputGamePad *m_pInputGamePad;		//�Q�[���p�b�h�̃|�C���^
};
#endif