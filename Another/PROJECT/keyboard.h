//=============================================================================
//
// ���͏��� [keyboard.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include "main.h"
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

class CKeyboard : CInput
{
public:
	CKeyboard();
	~CKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	bool GetPress(int nKey) { return (m_aKeyState[nKey] & 0x80) ? true : false; }			//�L�[��������Ă邩
	bool GetAnyKey();		//�����L�[�������ꂽ��
	bool GetTrigger(int nKey) { return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false; }	//�L�[�̏�Ԃ��ς������
	bool GetRelease(int nKey) { return (m_aKeyStateRelease[nKey] & 0x80) ? true : false; }	//�L�[�������ꂽ��
	bool GetKey(int nKey);	//�L�[�������ꂽ��

private:
	BYTE m_aKeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��(�v���X���)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��(�g���K�[���)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏��(�����[�X���)
};
#endif