//=============================================================================
//
// �^�C�g����UI���� [titleui.h]
// Author : �O��q��
//
//=============================================================================
#include "titleui.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CTitleUi::m_pTexture[2] = {};
CScene2D *CTitleUi::m_apScene[2] = {};

CTitleUi::CTitleUi(PRIORITY Priority) : CScene::CScene(Priority)
{

}

CTitleUi::~CTitleUi(void)
{

}

//������
HRESULT CTitleUi::Init(float, float, D3DXVECTOR3, float)
{
	int nCntLife = 0;
	//�^�C�g������
	m_apScene[nCntLife] = CScene2D::Create(560.0f, 80.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f), PRIORITY_UI);
	m_apScene[nCntLife]->BindTexture(m_pTexture[0]);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	nCntLife++;
	//press
	m_apScene[nCntLife] = CScene2D::Create(340.0f, 40.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f), PRIORITY_UI);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_apScene[nCntLife]->BindTexture(m_pTexture[1]);
	nCntLife++;
	m_bClear = false;
	m_fClear = 1.0f;
	return S_OK;
}

//�I��
void CTitleUi::Uninit(void)
{
	int nCntScene;
	for (nCntScene = 0; nCntScene < 2; nCntScene++)
	{
		if (m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene] = NULL;
		}
	}
	Release();
}

//�X�V
void CTitleUi::Update(void)
{
	//Press��UI�̓_��
	if (m_bClear == true)
	{
		m_fClear -= 0.1f;
		if (m_fClear <= 0.0f)
		{
			m_fClear = 0.0f;
			m_bClear = false;
		}
	}
	else
	{
		m_fClear += 0.1f;
		if (m_fClear >= 1.0f)
		{
			m_fClear = 1.0f;
			m_bClear = true;
		}
	}
	m_apScene[1]->ChangeColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fClear));
}

//�`��
void CTitleUi::Draw(void)
{

}

//�e�N�X�`���̓ǂݍ���
HRESULT CTitleUi::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/aceofdevil.png",
		&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pressanybutton.png",
		&m_pTexture[1]);
	return S_OK;
}

//�e�N�X�`���j��
void CTitleUi::UnLoad(void)
{
	int nCntLife;
	for (nCntLife = 0; nCntLife < 2; nCntLife++)
	{
		if (m_pTexture[nCntLife] != NULL)
		{
			m_pTexture[nCntLife]->Release();
			m_pTexture[nCntLife] = NULL;
		}
	}
}

//�쐬
CTitleUi *CTitleUi::Create(void)
{
	CTitleUi *pUi;
	pUi = new CTitleUi(PRIORITY_UI);
	if (pUi != NULL)
	{
		pUi->Init(0.0f, 0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}
	return pUi;
}