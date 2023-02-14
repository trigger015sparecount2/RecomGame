//=============================================================================
//
// ���͏��� [input.h]
// Author : �O��q��
//
//=============================================================================
#include "input.h"

//�ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;
bool CInputGamePad::m_bGamePad = false;

//�R�[���o�b�N�֐�
BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);

CInput::CInput(void)
{
	m_pDevice = NULL;
}

CInput::~CInput(void)
{

}

//������
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr = S_FALSE;
	if (m_pInput == NULL)
	{
		//DirectInit�I�u�W�F�N�g�̐���
		hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pInput, NULL);
	}
	return hr;
}

//�I��
void CInput::Uninit(void)
{
	//���̓f�o�C�X�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

CInputKeyboard::CInputKeyboard(void)
{
	//�L�[���̃N���A
	memset(&m_aKeyState[0], 0, sizeof(m_aKeyState));
	memset(&m_aKeyStateRelease[0], 0, sizeof(m_aKeyStateRelease));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

CInputKeyboard::~CInputKeyboard(void)
{

}

//����������
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInit�I�u�W�F�N�g�̐���
	CInput::Init(hInstance, hWnd);
	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();
	return S_OK;
}

//�I������
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//�X�V����
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	//���̓f�o�C�X����f�[�^���擾����
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = m_aKeyState[nCntKey] ^ aKeyState[nCntKey] & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey]; //�L�[�{�[�h�̓��͏��ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//�����L�[�������ꂽ��
bool CInputKeyboard::GetAnyKey(void)
{
	int nCntKey;
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		if ((m_aKeyStateTrigger[nCntKey] & 0x80) != 0 && (m_aKeyStateRelease[nCntKey] & 0x80) == 0)
		{
			return true;
		}
	}
	return false;
}

//����̃L�[�������ꂽ��
bool CInputKeyboard::GetKey(int nKey)
{
	if ((m_aKeyStateTrigger[nKey] & 0x80) != 0 && (m_aKeyStateRelease[nKey] & 0x80) == 0)
	{
		return true;
	}
	return false;
}

CInputGamePad::CInputGamePad(void)
{
	m_pDevice = NULL;
	m_bGamePad = false;
}

CInputGamePad::~CInputGamePad(void)
{

}

//������
HRESULT CInputGamePad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInit�I�u�W�F�N�g�̐���
	CInput::Init(hInstance, hWnd);
	//�ڑ�����Ă�Q�[���p�b�h�̗�
	if (FAILED(m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, DeviceFindCallBack, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}
	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;

	// �����[�h��ύX
	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// X���̒l�͈̔͐ݒ�
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	if (FAILED(m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return E_FAIL;
	}

	// Y���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �Q�[���p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();
	//�����𓯊�������
	m_pDevice->Poll();
	m_bGamePad = true;
	return S_OK;
}

//�I��
void CInputGamePad::Uninit(void)
{
	CInput::Uninit();
}

//�X�V
void CInputGamePad::Update(void)
{
	DIJOYSTATE aPadState;
	int nCntPad;
	//���̓f�o�C�X����f�[�^���擾����
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aPadState), &aPadState)))
	{
		for (nCntPad = 0; nCntPad < DIP_MAX; nCntPad++)
		{
			m_aPadStateTrigger.rgbButtons[nCntPad] = m_aPadState.rgbButtons[nCntPad] ^ aPadState.rgbButtons[nCntPad] & aPadState.rgbButtons[nCntPad];
			m_aPadStateRelease.rgbButtons[nCntPad] = (m_aPadState.rgbButtons[nCntPad] ^ aPadState.rgbButtons[nCntPad]) & m_aPadState.rgbButtons[nCntPad];
			m_aPadState.rgbButtons[nCntPad] = aPadState.rgbButtons[nCntPad]; //�L�[�{�[�h�̓��͏��ۑ�
		}
		m_aPadState.lX = aPadState.lX;
		m_aPadState.lY = aPadState.lY;
		m_aPadState.lZ = aPadState.lZ;
		m_aPadState.lRz = aPadState.lRz;
		m_aPadStateTrigger.rgdwPOV[0] = m_aPadState.rgdwPOV[0];
		m_aPadState.rgdwPOV[0] = aPadState.rgdwPOV[0];
	}
	else
	{
		m_pDevice->Acquire();
	}
}

BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef)
{
	return DIENUM_CONTINUE;
}

//���������ꂽ��
bool CInputGamePad::GetAnyButton(void)
{
	int nCntPad;
	for (nCntPad = 0; nCntPad < DIP_MAX; nCntPad++)
	{
		if ((m_aPadStateTrigger.rgbButtons[nCntPad] & 0x80) != 0 && (m_aPadStateRelease.rgbButtons[nCntPad] & 0x80) == 0)
		{
			return true;
		}
	}
	return false;
}

//�{�^���������ꂽ��
bool CInputGamePad::GetButton(CInputGamePad::PadButton Button)
{
	if ((m_aPadStateTrigger.rgbButtons[Button] & 0x80) != 0 && (m_aPadStateRelease.rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}

//�Q�[���p�b�h�̓��͏��̎擾(�\���L�[)
float CInputGamePad::TriggerCrossKey(void)
{
	//�\���L�[�����͂���Ă邩
	if (m_aPadState.rgdwPOV[0] != 0xFFFFFFFF)
	{
		//���O�ɉ����ꂽ�����ƈႤ���i�����������疳������j
		if (m_aPadStateTrigger.rgdwPOV[0] != m_aPadState.rgdwPOV[0])
		{
			return m_aPadState.rgdwPOV[0];
		}
	}
	return 10.0f; //����������ĂȂ������Ƃ��p
}

//�Q�[���p�b�h�̓��͏��̎擾(�\���L�[)
float CInputGamePad::PressCrossKey(void)
{
	//�\���L�[�����͂���Ă邩
	if (m_aPadState.rgdwPOV[0] != 0xFFFFFFFF)
	{
		return m_aPadState.rgdwPOV[0];
	}
	return 10.0f; //����������ĂȂ������Ƃ��p
}

//�Q�[���p�b�h�̓��͏��̎擾(���X�e�B�b�N������)
float CInputGamePad::LeftStickX(void)
{
	float length = 1000.0f;
	float LeftX = 0.0f;
	if (m_aPadState.lX != 0)
	{
		LeftX = (float)m_aPadState.lX / length; //���̓}�C�i�X�A�E�̓v���X
	}
	return LeftX;
}

//�Q�[���p�b�h�̓��͏��̎擾(���X�e�B�b�N�c����)
float CInputGamePad::LeftStickY(void)
{
	float length = 1000.0f;
	float LeftY = 0.0f;
	if (m_aPadState.lY != 0)
	{
		LeftY = (float)m_aPadState.lY / length; //��̓}�C�i�X�A���̓v���X
	}
	return LeftY;
}

//�Q�[���p�b�h�̓��͏��̎擾(�E�X�e�B�b�N������)
float CInputGamePad::RightStickX(void)
{
	float length = 32767.0f;
	float RightX = 0.0f;
	if (m_aPadState.lZ != 32767)
	{
		RightX = (float)(m_aPadState.lZ - length) / length; //���̓}�C�i�X�A�E�̓v���X
	}
	return RightX;
}

//�Q�[���p�b�h�̓��͏��̎擾(�E�X�e�B�b�N�c����)
float CInputGamePad::RightStickY(void)
{
	float length = 32767.0f;
	float RightY = 0.0f;
	if (m_aPadState.lRz != 32767)
	{
		RightY = (float)(m_aPadState.lRz - length) / length; //��̓}�C�i�X�A���̓v���X
	}
	return RightY;
}