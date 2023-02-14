//=============================================================================
//
// ���e�̃G�t�F�N�g���� [thundereffect.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "thundereffect.h"
#include "renderer.h"
#include "player.h"
#include "pauseui.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CThundereffect::m_pTexture = NULL;

CThundereffect::CThundereffect(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CThundereffect::~CThundereffect(void)
{

}

//������
HRESULT CThundereffect::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(THUNDEREFFECT_SIZE, THUNDEREFFECT_SIZE, pos, 1.0f);
	CScene::SetObjType(CScene::OBJTYPE_NONE);
	return S_OK;
}

//�I��
void CThundereffect::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V
void CThundereffect::Update(void)
{
	if (CPauseUi::GetPause() == false)
	{
		SetRot(0.9f);
	}
}

//�`��
void CThundereffect::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CThundereffect *CThundereffect::Create(D3DXVECTOR3 pos)
{
	CThundereffect *pThundereffect;
	pThundereffect = new CThundereffect(PRIORITY_BG);
	if (pThundereffect != NULL)
	{
		pThundereffect->Init(pos);
		pThundereffect->BindTexture(m_pTexture);
		pThundereffect->ChangeColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
	}
	return pThundereffect;
}

//�e�N�X�`���ǂݍ���
HRESULT CThundereffect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/thundereffect.png",
		&m_pTexture);
	return S_OK;
}

//�e�N�X�`���j��
void CThundereffect::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}