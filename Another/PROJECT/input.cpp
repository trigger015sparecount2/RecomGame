//=============================================================================
//
// ���͏��� [input.h]
// Author : �O��q��
//
//=============================================================================
#include "input.h"
//�ÓI�����o�ϐ�
LPDIRECTINPUT8 CInput::m_pInput = NULL;

CInput::CInput()
{
	m_pDevice = NULL;
}

CInput::~CInput()
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
void CInput::Uninit()
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