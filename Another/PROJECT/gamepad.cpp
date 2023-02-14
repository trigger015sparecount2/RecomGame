//=============================================================================
// ���͏��� [gamepad.h]
// Author : �O��q��
//=============================================================================
#include "gamepad.h"

bool CGamePad::m_bGamePad = false;

BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);

CGamePad::CGamePad()
{
	m_pDevice = NULL;
	m_bGamePad = false;
}

CGamePad::~CGamePad()
{

}

//������
HRESULT CGamePad::Init(HINSTANCE hInstance, HWND hWnd)
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
void CGamePad::Uninit()
{
	CInput::Uninit();
}

//�X�V
void CGamePad::Update()
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

//�R�[���o�b�N
BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef)
{
	return DIENUM_CONTINUE;
}

//������������
bool CGamePad::GetAnyButton()
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

//�{�^����������
bool CGamePad::GetButton(CGamePad::PadButton Button)
{
	if ((m_aPadStateTrigger.rgbButtons[Button] & 0x80) != 0 && (m_aPadStateRelease.rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}

//�\���L�[�����ꂽ��
float CGamePad::TriggerCrossKey()
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

//�\���L�[������Ă邩
float CGamePad::PressCrossKey()
{
	//�\���L�[�����͂���Ă邩
	if (m_aPadState.rgdwPOV[0] != 0xFFFFFFFF)
	{
		return m_aPadState.rgdwPOV[0];
	}
	return 10.0f; //����������ĂȂ������Ƃ��p
}

//���X�e�B�b�N��
float CGamePad::LeftStickX()
{
	float length = 1000.0f;
	float LeftX = 0.0f;
	if (m_aPadState.lX != 0)
	{
		LeftX = (float)m_aPadState.lX / length; //���̓}�C�i�X�A�E�̓v���X
	}
	return LeftX;
}

//���X�e�B�b�N�c
float CGamePad::LeftStickY()
{
	float length = 1000.0f;
	float LeftY = 0.0f;
	if (m_aPadState.lY != 0)
	{
		LeftY = (float)m_aPadState.lY / length; //��̓}�C�i�X�A���̓v���X
	}
	return LeftY;
}

//�E�X�e�B�b�N��
float CGamePad::RightStickX()
{
	float length = 32767.0f;
	float RightX = 0.0f;
	if (m_aPadState.lZ != 32767)
	{
		RightX = (float)(m_aPadState.lZ - length) / length; //���̓}�C�i�X�A�E�̓v���X
	}
	return RightX;
}

//�E�X�e�B�b�N�c
float CGamePad::RightStickY()
{
	float length = 32767.0f;
	float RightY = 0.0f;
	if (m_aPadState.lRz != 32767)
	{
		RightY = (float)(m_aPadState.lRz - length) / length; //��̓}�C�i�X�A���̓v���X
	}
	return RightY;
}