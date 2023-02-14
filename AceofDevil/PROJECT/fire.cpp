//=============================================================================
//
// �Ή��e���� [fire.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "fire.h"
#include "renderer.h"
#include "enemy.h"
#include "effect.h"
#include "pauseui.h"
#include "prize.h"
#include "ui.h"

//�}�N����`
#define FIRE_SIZE (20.0f)

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CFire::m_pTexture = NULL;

CFire::CFire(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CFire::~CFire(void)
{

}

//������
HRESULT CFire::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CScene2D::Init(FIRE_SIZE, FIRE_SIZE, pos, 1.0f);
	CScene::SetObjType(CScene::OBJTYPE_BULLET);
	CScene::SetPos(pos);
	CScene2D::SetSize(0.16f);
	Set(FIRE_SIZE, FIRE_SIZE, pos);

	m_nEnemy = 0;
	m_pPos = RockEnemy();
	m_move = move;
	m_fRotY = 0.0f;
	m_nEffect = 0;
	m_nLife = 240;
	m_bUninit = false;
	return S_OK;
}

//�I��
void CFire::Uninit(void)
{
	m_pPos = NULL;
	CScene2D::Uninit();
}

//�X�V
void CFire::Update(void)
{
	//�|�[�Y������Ȃ�
	if (CPauseUi::GetPause() == false)
	{
		//�܂��폜���Ȃ�
		if (m_bUninit == false)
		{
			D3DXVECTOR3 pos = GetPos();
			float fRotY;
			fRotY = m_fRotY;
			Homing(pos);
			m_nLife--;
			pos.x += sinf(m_fRotY) * m_move.x;
			pos.y -= cosf(m_fRotY) * m_move.y;
			Set(FIRE_SIZE, FIRE_SIZE, pos);
			SetRot((fRotY - m_fRotY) / D3DX_PI);

			//�G�t�F�N�g�J�E���g�i�߂�
			m_nEffect--;
			//�G�t�F�N�g�J�E���g���i�񂾂�
			if (m_nEffect <= 0)
			{
				//�G�t�F�N�g�쐬
				CEffect::Create(pos, CEffect::COLORTYPE_RED);
				//�J�E���g���Z�b�g
				m_nEffect = 2;
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
					//�G��������
					if (objType == OBJTYPE_ENEMY)
					{
						D3DXVECTOR3 posEnemy;
						posEnemy = pScene1->GetPos();
						//�������Ă�����
						if (posEnemy.x - ENEMY_SIZE * sinf(0.25f * D3DX_PI) <= pos.x + FIRE_SIZE && pos.x - FIRE_SIZE <= posEnemy.x + ENEMY_SIZE * sinf(0.25f * D3DX_PI) &&
							posEnemy.y - ENEMY_SIZE * cosf(0.25f * D3DX_PI) <= pos.y + FIRE_SIZE && pos.y - FIRE_SIZE <= posEnemy.y + ENEMY_SIZE * cosf(0.25f * D3DX_PI))
						{
							//�G�Ƀ_���[�W
							if (pScene1->GetDamage() == true)
							{
								pScene1->Damage(3);
							}
							m_bUninit = true;
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
						ELEMENT element;
						element = pScene2->GetElement();
						//�X������������
						if (element == ELEMENT_ICE)
						{
							D3DXVECTOR3 posBullet;
							posBullet = pScene2->GetPos();
							//�������Ă�����
							if (posBullet.x - ENEMY_SIZE * sinf(0.25f * D3DX_PI) <= pos.x + FIRE_SIZE && pos.x - FIRE_SIZE <= posBullet.x + ENEMY_SIZE * sinf(0.25f * D3DX_PI) &&
								posBullet.y - ENEMY_SIZE * cosf(0.25f * D3DX_PI) <= pos.y + FIRE_SIZE && pos.y - FIRE_SIZE <= posBullet.y + ENEMY_SIZE * cosf(0.25f * D3DX_PI))
							{
								CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_ICE, 5);
								CUi::SetScore(140);
								pScene2->Uninit();
							}
						}
					}
					pScene2 = NULL;
				}
			}
			//�����؂�
			if (m_nLife <= 0)
			{
				m_bUninit = true;
			}
		}
		else
		{
			//�폜
			Uninit();
		}
	}
}

//�`��
void CFire::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CFire *CFire::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CFire *pFire;
	pFire = new CFire(PRIORITY_BULLET);
	if (pFire != NULL)
	{
		pFire->Init(pos, move);
		pFire->BindTexture(m_pTexture);
	}
	return pFire;
}

//�e�N�X�`���ǂݍ���
HRESULT CFire::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/fire.png",
		&m_pTexture);
	return S_OK;
}

//�e�N�X�`���j��
void CFire::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//�G�����b�N�I������
D3DXVECTOR3 *CFire::RockEnemy(void)
{
	int nCntEnemy;
	int nEnemy = -1;
	D3DXVECTOR3 pos;
	float fRotMin = 10.0f;
	pos = GetPos();
	for (nCntEnemy = 0; nCntEnemy < MAX_POLYGON; nCntEnemy++)
	{
		CScene *pScene;
		pScene = GetScene(PRIORITY_CHARA, nCntEnemy);
		if (pScene != NULL)
		{
			if (pScene->GetDamage() == true)
			{
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//�G��������
				if (objType == OBJTYPE_ENEMY)
				{
					D3DXVECTOR3 posEnemy;
					posEnemy = pScene->GetPos();
					float fRotY;
					//�G�Ƃ̊p�x�v�Z
					fRotY = atan2f(posEnemy.x - pos.x, pos.y - posEnemy.y);
					//���ʕ����ɋ߂�������
					if (fabsf(fRotMin) > fabsf(fRotY))
					{
						fRotMin = fRotY;
						nEnemy = nCntEnemy;
					}
				}
			}
		}
	}

	//�G��������Ȃ�������I��
	if(nEnemy == -1)
	{
		return NULL;
	}

	D3DXVECTOR3 *pPos;

	//�G�̃|�C���^��n��
	pPos = GetPointerPos(nEnemy);

	//���Ԗڂ̓G���L������
	m_nEnemy = nEnemy;
	return pPos;
}

//�G�̕���������
void CFire::Homing(D3DXVECTOR3 pos)
{
	//�G��pos�̃|�C���^������
	if (m_pPos != NULL)
	{
		//�G�����݂��Ă��Ȃ�������I��
		if (CScene::GetbEnemy(m_nEnemy) == false)
		{
			m_pPos = NULL;
			return;
		}
		//�G�Ƃ̊p�x�v�Z
		float fRotY;
		fRotY = atan2f(m_pPos->x - pos.x, pos.y - m_pPos->y);

		//�p�x������Ȃ��悤�ɂ���
		if (m_fRotY >= D3DX_PI)
		{
			m_fRotY -= D3DX_PI * 2;
		}
		else if (m_fRotY <= -D3DX_PI)
		{
			m_fRotY += D3DX_PI * 2;
		}

		//�G�Ƃ̊p�x�ƍ������������Ă�p�x����������Ȃ�������
		if (m_fRotY != fRotY)
		{

			if (fRotY - m_fRotY < -D3DX_PI)
			{
				m_fRotY += 0.03f;
			}
			else if (fRotY - m_fRotY > D3DX_PI)
			{
				m_fRotY -= 0.03f;
			}
			else if(fRotY - m_fRotY < 0.0f)
			{
				if (fabsf(fRotY - m_fRotY) < 0.03f)
				{
					m_fRotY = fRotY;
				}
				else
				{
					m_fRotY -= 0.03f;
				}
			}
			else if (fRotY - m_fRotY > 0.0f)
			{
				if (fabsf(fRotY - m_fRotY) < 0.03f)
				{
					m_fRotY = fRotY;
				}
				else
				{
					m_fRotY += 0.03f;
				}
			}
		}
	}
}