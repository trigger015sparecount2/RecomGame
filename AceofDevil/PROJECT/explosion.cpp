//=============================================================================
//
// �������� [explosion.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "explosion.h"
#include "renderer.h"
#include "pauseui.h"

//�}�N����`
#define EXPLOSION_SIZE (50.0f)

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//�R���X�g���N�^
CExplosion::CExplosion(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

//�f�X�g���N�^
CExplosion::~CExplosion(void)
{

}

//������
HRESULT CExplosion::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(EXPLOSION_SIZE, EXPLOSION_SIZE, pos, 0.125f);
	CScene2D::SetObjType(CScene::OBJTYPE_EXPLOSION);
	m_nPatternAnim = 0;
	m_nCounterAnim = 0;
	return S_OK;
}

//�I������
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V
void CExplosion::Update(void)
{
	//�|�[�Y���łȂ�������
	if (CPauseUi::GetPause() == false)
	{
		//�A�j���[�V�����J�E���g����
		m_nCounterAnim++;
		if (m_nCounterAnim >= 4)
		{
			//�J�E���g�����Z�b�g���A�j���[�V������i�߂�
			m_nCounterAnim = 0;
			m_nPatternAnim++;
			SetTexture(m_nPatternAnim, 8);

			//�A�j���[�V������1�����������
			if (m_nPatternAnim >= 8)
			{
				Uninit();
			}
		}
	}
}

//�`��
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion(PRIORITY_EFFECT);
	if (pExplosion != NULL)
	{
		pExplosion->Init(pos);
		pExplosion->BindTexture(m_pTexture);
	}
	return pExplosion;
}

//�e�N�X�`���ǂݍ���
HRESULT CExplosion::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/explosion000.png",
		&m_pTexture);
	return S_OK;
}

//�e�N�X�`���j��
void CExplosion::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}