//--------------------------------------
//Author:三上航世
//マウスの入力情報(mouse.cpp)
//---------------------------------------
#include "mouse.h"

CMouse::CMouse()
{
	m_pDevice = NULL;
}

CMouse::~CMouse()
{

}


//初期化処理
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInitオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	ShowCursor(FALSE);

	//処理を同期させる
	m_pDevice->Poll();
	// マウスへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();
	m_bMouse = true;
	return S_OK;
}

//終了処理
void CMouse::Uninit()
{
	CInput::Uninit();
}

//更新処理
void CMouse::Update()
{
	DIMOUSESTATE aMouseState;
	int nCntBut;
	//入力デバイスからデータを取得する
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aMouseState), &aMouseState)))
	{
		for (nCntBut = 0; nCntBut < DIM_MAX; nCntBut++)
		{
			m_MouseStateTrigger.rgbButtons[nCntBut] = m_MouseState.rgbButtons[nCntBut] ^ aMouseState.rgbButtons[nCntBut] & aMouseState.rgbButtons[nCntBut];
			m_MouseStateRelease.rgbButtons[nCntBut] = (m_MouseState.rgbButtons[nCntBut] ^ aMouseState.rgbButtons[nCntBut]) & m_MouseState.rgbButtons[nCntBut];
			m_MouseState.rgbButtons[nCntBut] = aMouseState.rgbButtons[nCntBut]; //マウスの入力情報保存
		}
		m_MouseState.lX = aMouseState.lX;
		m_MouseState.lY = aMouseState.lY;
		m_MouseState.lZ = aMouseState.lZ;
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//特定のボタンが押されたか
bool CMouse::GetMouseButton(MouseButton Button) const
{
	if ((m_MouseStateTrigger.rgbButtons[Button] & 0x80) != 0 && (m_MouseStateRelease.rgbButtons[Button] & 0x80) == 0)
	{
		return true;
	}
	return false;
}
