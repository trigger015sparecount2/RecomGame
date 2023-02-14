//=============================================================================
//
// ���o���A���� [wind.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "wind.h"
#include "renderer.h"
#include "enemy.h"
#include "scene.h"
#include "bullet.h"
#include "pauseui.h"
#include "prize.h"
#include "ui.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CWind::m_pTexture = NULL;

CWind::CWind(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CWind::~CWind(void)
{

}

//������
HRESULT CWind::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(WIND_SIZE, WIND_SIZE, pos, 1.0f);
	CScene::SetObjType(CScene::OBJTYPE_BULLET);
	CScene::SetPos(pos);
	CScene2D::ChangeColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	Set(0.0f, 0.0f, pos);
	m_pPlayerpos = CScene::GetPlayerPos();
	m_fRotY = D3DX_PI;
	m_fSize = 0.0f;
	m_bSize = false;
	m_nListCnt = 0;
	m_bDraw = false;
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < WIND_MAX_ENEMY; nCntEnemy++)
	{
		m_aEnemies[nCntEnemy] = -1;
	}
	return S_OK;
}

//�I��
void CWind::Uninit(void)
{
	m_pPlayerpos = NULL;
	CScene2D::Uninit();
}

//�X�V
void CWind::Update(void)
{
	//�|�[�Y������Ȃ�
	if (CPauseUi::GetPause() == false)
	{
		//�傫������
		if (m_bSize == true)
		{
			if (WIND_SIZE > m_fSize)
			{
				m_fSize += 10.0f;
				m_bDraw = true;
			}
		}
		//����������
		else
		{
			if (m_fSize > 0.0f)
			{
				m_fSize -= 10.0f;
				if (m_fSize <= 10.0f)
				{
					m_fSize = 0.0f;
					m_bDraw = false;
				}
			}
		}

		//�`�悷��(�T�C�Y�����ȏ゠��Ȃ�)
		if (m_bDraw == true)
		{
			//�p�x�����Z�����Ă����A�ꏊ��傫����ݒ�
			SetRot(-0.06f);
			Set(m_fSize, m_fSize, *m_pPlayerpos);

			//��莞�Ԃ��ƂɃ��X�g����V����(���Ă邽��)
			if (m_nListCnt > 0)
			{
				m_nListCnt--;
				if (m_nListCnt <= 0)
				{
					int nCntEnemy;
					for (nCntEnemy = 0; nCntEnemy < WIND_MAX_ENEMY; nCntEnemy++)
					{
						m_aEnemies[nCntEnemy] = -1;
					}
					m_nListCnt = 10;
				}
			}

			int nCntScene;
			for (nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				//�G�ւ̃_���[�W
				CScene *pScene1;
				pScene1 = GetScene(PRIORITY_CHARA, nCntScene);
				if (pScene1 != NULL)
				{
					OBJTYPE objType;
					objType = pScene1->GetObjType();
					//�G�����X�g���ɂ��Ȃ�(�������ĂȂ�)�Ȃ�
					if (objType == OBJTYPE_ENEMY && EnemyList(nCntScene) == true)
					{
						D3DXVECTOR3 posEnemy;
						posEnemy = pScene1->GetPos();
						float fDistance;
						fDistance = sqrtf(powf(m_pPlayerpos->x - posEnemy.x, 2.0f) + powf(m_pPlayerpos->y - posEnemy.y, 2.0f));
						//�������v�Z�A�Z�������瓖�����Ă�
						if (fDistance <= ENEMY_SIZE * sinf(0.25f * D3DX_PI) + m_fSize * sinf(0.25f * D3DX_PI))
						{
							//�_���[�W��^���A���X�g�ɕۑ�
							if (pScene1->GetDamage() == true)
							{
								pScene1->Damage(2);
								ListPush(nCntScene);
							}
						}
					}
					pScene1 = NULL;
				}

				//�e�ۏ���
				CScene *pScene2;
				pScene2 = GetScene(PRIORITY_BULLET, nCntScene);
				if (pScene2 != NULL)
				{
					if (pScene2->GetEnemy() == true)
					{
						D3DXVECTOR3 posBullet;
						posBullet = pScene2->GetPos();
						float fDistance;
						fDistance = sqrtf(powf(m_pPlayerpos->x - posBullet.x, 2.0f) + powf(m_pPlayerpos->y - posBullet.y, 2.0f));
						//�������v�Z�A�Z�������瓖�����Ă�
						if (fDistance <= BULLET_SIZE * sinf(0.25f * D3DX_PI) + m_fSize * sinf(0.25f * D3DX_PI))
						{
							//�e�������A�X�R�A���Z�A�o������v���C�Y�͓G�e�̑����Ɠ���
							D3DXVECTOR3 pos;
							pos = pScene2->GetPos();
							CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), pScene2->GetElement(), 5);
							CUi::SetScore(50);
							pScene2->Uninit();
						}
					}
					pScene2 = NULL;
				}
			}
		}
	}
}

//�`��
void CWind::Draw(void)
{
	if (m_bDraw == true)
	{
		CScene2D::Draw();
	}
}

//�쐬
CWind *CWind::Create(D3DXVECTOR3 pos)
{
	CWind *pWind;
	pWind = new CWind(PRIORITY_BULLET);
	if (pWind != NULL)
	{
		pWind->Init(pos);
		pWind->BindTexture(m_pTexture);
	}
	return pWind;
}

//�e�N�X�`���ǂݍ���
HRESULT CWind::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wind.png",
		&m_pTexture);
	return S_OK;
}

//�e�N�X�`���j��
void CWind::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//�ǂ̓G�ɓ��������̂����X�g�����Q��
bool CWind::EnemyList(int nEnemy)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < WIND_MAX_ENEMY; nCntEnemy++)
	{
		if (m_aEnemies[nCntEnemy] == nEnemy)
		{
			return false;
		}
	}
	return true;
}

//���X�g���ɓG������
void CWind::ListPush(int nEnemy)
{
	m_aEnemies[m_nListCnt] = nEnemy;
	m_nListCnt++;
	if (m_nListCnt >= WIND_MAX_ENEMY)
	{
		m_nListCnt = 0;
	}
}