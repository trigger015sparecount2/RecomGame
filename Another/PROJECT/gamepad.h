//=============================================================================
//
// ���͏��� [gamepad.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
#include "main.h"
#include "input.h"

class CGamePad : CInput
{
public:
	//�Q�[���p�b�h�{�^��
	typedef enum
	{
		DIP_X = 0,
		DIP_Y,
		DIP_A,
		DIP_B,
		DIP_L1,
		DIP_R1,
		DIP_L2,
		DIP_R2,
		DIP_LS,
		DIP_RS,
		DIP_BACK,
		DIP_START,
		DIP_GUIDE,
		DIP_MAX
	} PadButton;

	CGamePad();
	~CGamePad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	bool GetPress(PadButton Button) { return (m_aPadState.rgbButtons[Button] & 0x80) ? true : false; }			//�{�^�������Ă邩
	bool GetAnyButton();				//�����{�^�������ꂽ��
	bool GetTrigger(PadButton Button) { return (m_aPadStateTrigger.rgbButtons[Button] & 0x80) ? true : false; }	//�{�^���̏�Ԃ��ς������
	bool GetRelease(PadButton Button) { return (m_aPadStateRelease.rgbButtons[Button] & 0x80) ? true : false; }	//
	bool GetButton(PadButton Button);	//�{�^�������ꂽ��
	float LeftStickX();					//���X�e�B�b�N��
	float LeftStickY();					//���X�e�B�b�N�c
	float TriggerCrossKey();			//�\���L�[�����ꂽ
	float PressCrossKey();				//�\���L�[������Ă邩
	float RightStickX();				//�E�X�e�B�b�N��
	float RightStickY();				//�E�X�e�B�b�N�c
	static bool GetGamePad() { return m_bGamePad; }	//�Q�[���p�b�h�q�����Ă�

private:
	static bool m_bGamePad;			//�Q�[���p�b�h�q�����Ă邩
	DIJOYSTATE m_aPadState;			//�Q�[���p�b�h�̓��͏��(�v���X���)
	DIJOYSTATE m_aPadStateTrigger;	//�Q�[���p�b�h�̓��͏��(�g���K�[���)
	DIJOYSTATE m_aPadStateRelease;	//�Q�[���p�b�h�̓��͏��(�����[�X���)
};
#endif