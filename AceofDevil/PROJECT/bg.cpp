//=============================================================================
//
// �w�i���� [bg.h]
// Author : �O��q��
//
//=============================================================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "pauseui.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBg::m_pTexture = NULL;
bool CBg::m_bScroll = false;

//�R���X�g���N�^
CBg::CBg(PRIORITY Priority) : CScene::CScene(Priority)
{

}

//�f�X�g���N�^
CBg::~CBg(void)
{

}

//����������
HRESULT CBg::Init(float fWidth, float fHeight, D3DXVECTOR3 pos, float fTexSize)
{
	if (m_apScene == NULL)
	{
		m_apScene = CScene2D::Create(fWidth, fHeight, pos, PRIORITY_BG);
		m_apScene->ScrollTexture(0.0f);
		m_apScene->BindTexture(m_pTexture);
	}
	m_fTexY = 0.0f;
	return S_OK;
}

//�I������
void CBg::Uninit(void)
{
	if (m_apScene != NULL)
	{
		m_apScene->Uninit();
		m_apScene = NULL;
	}
	Release();
}

//�X�V����
void CBg::Update(void)
{
	//�X�N���[��������ꍇ
	if (m_bScroll == true)
	{
		//�|�[�Y������Ȃ�������
		if (CPauseUi::GetPause() == false)
		{
			//�X�N���[��������
			m_fTexY -= 0.1f;
			//�X�N���[�������������猳�ɖ߂�
			if (m_fTexY < -15.0f)
			{
				m_fTexY = 0.0f;
			}
			//�X�N���[��������
			m_apScene->ScrollTexture(m_fTexY);
		}
	}
}

//�`�揈��
void CBg::Draw(void)
{

}

//�e�N�X�`���ǂݍ���
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/sea.png",
		&m_pTexture);
	return S_OK;
}

//�e�N�X�`���j��
void CBg::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//�쐬
CBg *CBg::Create(bool bScroll)
{
	CBg *pBg;
	pBg = new CBg(PRIORITY_BG);
	if (pBg != NULL)
	{
		pBg->Init(SCREEN_WIDTH / 1.4f, SCREEN_HEIGHT / 1.4f , D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 1.0f);
		m_bScroll = bScroll;
	}
	return pBg;
}