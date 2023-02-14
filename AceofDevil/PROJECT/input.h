//=============================================================================
//
// ���͏��� [input.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//�}�N����`
#define NUM_KEY_MAX (256) //�L�[�̍ő吔

class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;	//DirectInput�I�u�W�F�N�g�̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevice;	//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
};

class CInputKeyboard : CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V

	bool GetPress(int nKey) { return (m_aKeyState[nKey] & 0x80) ? true : false; }			//������Ă��邩
	bool GetAnyKey(void);	//���������ꂽ��
	bool GetTrigger(int nKey) { return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false; }	//�����ꂽ�A�܂��͗����ꂽ��
	bool GetRelease(int nKey) { return (m_aKeyStateRelease[nKey] & 0x80) ? true : false; }	//�����ꂽ��
	bool GetKey(int nKey);	//�����ꂽ��

private:
	BYTE m_aKeyState[NUM_KEY_MAX];        //�L�[�{�[�h�̓��͏��(�v���X���)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];
};

class CInputGamePad : CInput
{
public:
	//�Q�[���p�b�h�̃{�^���̎��
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

	CInputGamePad();
	~CInputGamePad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V

	bool GetPress(PadButton Button) { return (m_aPadState.rgbButtons[Button] & 0x80) ? true : false; }			//�����ꂽ��
	bool GetAnyButton(void);			//���������ꂽ��
	bool GetTrigger(PadButton Button) { return (m_aPadStateTrigger.rgbButtons[Button] & 0x80) ? true : false; }	//�����ꂽ�A�܂��͗����ꂽ��
	bool GetRelease(PadButton Button) { return (m_aPadStateRelease.rgbButtons[Button] & 0x80) ? true : false; }	//�����ꂽ��
	bool GetButton(PadButton Button);	//�����ꂽ��
	float LeftStickX(void);				//���X�e�B�b�N��
	float LeftStickY(void);				//���X�e�B�b�N�c
	float TriggerCrossKey(void);		//�\���L�[�����ꂽ��
	float PressCrossKey(void);			//�\���L�[������Ă��邩
	float RightStickX(void);			//�E�X�e�B�b�N��
	float RightStickY(void);			//�E�X�e�B�b�N�c
	static bool GetGamePad(void) { return m_bGamePad; }		//�Q�[���p�b�h�q�����Ă��邩

private:
	static bool m_bGamePad;
	DIJOYSTATE m_aPadState;              //�Q�[���p�b�h�̓��͏��(�v���X���)
	DIJOYSTATE m_aPadStateTrigger;
	DIJOYSTATE m_aPadStateRelease;
	//BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);
};
#endif