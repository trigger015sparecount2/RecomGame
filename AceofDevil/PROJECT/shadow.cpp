//=============================================================================
//
// �e���� [shadow.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "shadow.h"
#include "pauseui.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CShadow::m_pTexture[CShadow::MAX_SHADOW] = {};

CShadow::CShadow(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CShadow::~CShadow(void)
{

}

//������
HRESULT CShadow::Init(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CScene2D::Init(fWidth, fHeight, pos, 1.0f);
	CScene::SetObjType(CScene::OBJTYPE_SHADOW);
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	return S_OK;
}

//�I��
void CShadow::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V
void CShadow::Update(void)
{
	
}

//�`��
void CShadow::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CShadow *CShadow::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, SHADOW shadow)
{
	CShadow *pShadow;
	pShadow = new CShadow(PRIORITY_BG);
	if (pShadow != NULL)
	{
		pShadow->Init(pos, fWidth, fHeight);
		pShadow->BindTexture(m_pTexture[shadow]);
		pShadow->ChangeColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	}
	return pShadow;
}

//�e�N�X�`���̓ǂݍ���
HRESULT CShadow::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/F-15S_MTDShadow.png",
		&m_pTexture[SHADOW_F_15S_MTD]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/F-14Shadow.png",
		&m_pTexture[SHADOW_F_14]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MIG-31Shadow.png",
		&m_pTexture[SHADOW_MIG_31]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/F-35Shadow.png",
		&m_pTexture[SHADOW_F_35]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/F-2Shadow.png",
		&m_pTexture[SHADOW_F_2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RAFALEShadow.png",
		&m_pTexture[SHADOW_RAFALE]);
	return S_OK;
}

//�e�N�X�`���̔j��
void CShadow::UnLoad(void)
{
	int nCntTex;
	for (nCntTex = 0; nCntTex < MAX_SHADOW; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}