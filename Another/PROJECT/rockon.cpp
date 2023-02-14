//---------------------------
// Author:�O��q��
// ���b�N�I��(rockon.cpp)
//---------------------------

#include "plane.h"
#include "manager.h"
#include "renderer.h"
#include "rockon.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CRockon::m_pTexture = NULL;

CRockon::CRockon(PRIORITY Priority) : CUI::CUI(Priority)
{

}

CRockon::~CRockon(void)
{

}

//����������
HRESULT CRockon::Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType)
{
	CUI::Init(pos, SizeX, SizeY, nType, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	m_bUse = false;
	m_bScreen = false;
	return S_OK;
}

//�I������
void CRockon::Uninit(void)
{
	if (m_pScene != NULL)
	{
		m_pScene = NULL;
	}
	CUI::Uninit();
}

//�X�V����
void CRockon::Update(void)
{	
	if (m_bUse == true)
	{
		if (m_pScene->GetDeath() == true)
		{
			m_pScene = NULL;
			m_bUse = false;
		}
		else
		{
			LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
			D3DXMATRIX mtxView, mtxProjection, mtxEnemy, mtxParent, mtxTrans;
			D3DXMATRIX mtxViewport =
			{ SCREEN_WIDTH / 2, 0, 0, 0, 0, -SCREEN_HEIGHT / 2, 0, 0, 0, 0, 1, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1 }; //�r���[�|�[�g�z��
			pDevice = CManager::GetRenderer()->GetDevice();		 //�f�o�C�X���擾����
			//�G�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxEnemy);
			//�G�̃��b�N�I���ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, 0.0f, m_fHeight, 0.0f);
			D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxTrans);
			//�G�̃p�[�c�}�g���b�N�X�̎擾�A���f
			mtxParent = m_pScene->GetMatrix(0);
			D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxParent);
			//D3DXMatrixTranslation(&mtxParent, m_pScene->GetPos().x, m_pScene->GetPos().y, m_pScene->GetPos().z);
			//D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxParent);
			//�r���[�ϊ�
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);
			D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxView);
			//�ˉe�ϊ�
			pDevice->GetTransform(D3DTS_PROJECTION, &mtxProjection);
			D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxProjection);
			//�r���[�|�[�g�ϊ�
			D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxViewport);
			mtxEnemy._41 /= mtxEnemy._44;
			mtxEnemy._42 /= mtxEnemy._44;
			//mtxEnemy._43 /= mtxEnemy._44;

			//��L�̏����ŉ�ʊO�ɂ����Ă�(_43���}�C�i�X�̎��A��ʂ̔��Α��ɂ���)
			if (mtxEnemy._41 <= 0.0f || SCREEN_WIDTH <= mtxEnemy._41 ||
				mtxEnemy._42 <= 0.0f || SCREEN_HEIGHT <= mtxEnemy._42 || mtxEnemy._43 < 0.0f)
			{
				//�`�悵�Ȃ�
				m_bScreen = false;
			}
			//��ʓ��ɂ���
			else
			{
				//�`�悷��
				SetPos(D3DXVECTOR3(mtxEnemy._41, mtxEnemy._42, 0.0f));
				m_bScreen = true;
				
			}
		}
	}
	
}

//�`�揈��
void CRockon::Draw(void)
{
	//�g���Ă��邩�`�悷��
	if (m_bUse == true && m_bScreen == true)
	{
		CUI::Draw();
	}
}

//���b�N�I������
void CRockon::SetRockon(CScene *pScene)
{
	m_pScene = pScene;
	
	m_fHeight = m_pScene->GetHeight() * 0.2f;
	m_bUse = true;
}

//���b�N�I���O��
void CRockon::RemoveRockon(void)
{
	m_pScene = NULL;
	m_bUse = false;
}

//�쐬
CRockon *CRockon::Create()
{
	CRockon *pRockon;
	pRockon = new CRockon(PRIORITY_UI);
	if (pRockon != NULL)
	{
		pRockon->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 35.0f, 35.0f, 0);
	}
	return pRockon;
}