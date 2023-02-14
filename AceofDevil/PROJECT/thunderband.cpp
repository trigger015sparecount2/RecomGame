//=============================================================================
//
// ���̑я��� [thunderband.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "thunderband.h"
#include "renderer.h"
#include "enemy.h"
#include "effect.h"
#include "pauseui.h"

//�}�N����`
#define BAND_WIDTH (40.0f)

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CThunderBand::m_pTexture = NULL;

CThunderBand::CThunderBand(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CThunderBand::~CThunderBand(void)
{

}

//������
HRESULT CThunderBand::Init(D3DXVECTOR3 pos, float fRotY, float fLength)
{
	CScene2D::Init(fLength, 100.0f, pos, 1.0f);
	CScene::SetObjType(CScene::OBJTYPE_BULLET);
	SetSize(0.1f);
	SetRot(fRotY);
	Set(fLength, 100.0f, pos);
	m_nLife = 0;
	m_nTex = 0;
	SetTexture(m_nTex, 2);
	return S_OK;
}

//�I��
void CThunderBand::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V
void CThunderBand::Update(void)
{
	//�|�[�Y������Ȃ�������
	if (CPauseUi::GetPause() == false)
	{
		//�����J�E���g�i�߂�
		m_nLife++;
		if (m_nLife % 2 == 0)
		{
			//�e�N�X�`���J�E���g�i�߂�
			m_nTex++;
			if (m_nTex >= 2)
			{
				m_nTex = 0;
			}
			SetTexture(m_nTex, 2);
		}
		//�����؂�A����
		if (m_nLife >= 10)
		{
			Uninit();
		}
	}
}

//�`��
void CThunderBand::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CThunderBand *CThunderBand::Create(D3DXVECTOR3 pos, float fRotY, float fLength)
{
	CThunderBand *pThunderBand;
	pThunderBand = new CThunderBand(PRIORITY_CHARA);
	if (pThunderBand != NULL)
	{
		pThunderBand->Init(pos, fRotY, fLength);
		pThunderBand->BindTexture(m_pTexture);
	}
	return pThunderBand;
}

//�e�N�X�`���̓ǂݍ���
HRESULT CThunderBand::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/lightning.png",
		&m_pTexture);
	return S_OK;
}

//�e�N�X�`���̔j��
void CThunderBand::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}