//=============================================================================
//
// ���͏��� [input.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	virtual void Uninit();		//�I��
	virtual void Update() = 0;	//�X�V

protected:
	static LPDIRECTINPUT8 m_pInput;	//DirectInput�I�u�W�F�N�g�̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
};
#endif