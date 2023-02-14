//=============================================================================
//
// �}�l�[�W�� [Manager.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
//�O���錾
class CRenderer;
class CInputKeyboard;
class CInputGamePad;
class CTitle;
class CTutorial;
class CGame;
class CResult;
class CFade;
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	//����������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	static void SetMode(MODE mode);				//���[�h�ݒ�
	static MODE GetMode() { return m_mode; }	//���[�h��Ԃ�
	static CRenderer *GetRenderer(void) { return m_pRenderer; }					//�����_���[�̃|�C���^
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }	//�L�[�{�[�h�̃|�C���^
	static CInputGamePad *GetInputGamePad(void);								//�Q�[���p�b�h�̃|�C���^

private:
	static CRenderer *m_pRenderer;				//�����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	//�L�[�{�[�h�̃|�C���^
	static CInputGamePad *m_pInputGamePad;		//�Q�[���p�b�h�̃|�C���^
	static CTitle *m_pTitle;					//�^�C�g��
	static CTutorial *m_pTutorial;				//�`���[�g���A��
	static CGame *m_pGame;						//�Q�[��
	static CResult *m_pResult;					//���U���g
	static MODE m_mode;							//���[�h
};

#endif