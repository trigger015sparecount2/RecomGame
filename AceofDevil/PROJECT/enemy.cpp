//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "enemy.h"
#include "bullet.h"
#include "renderer.h"
#include "explosion.h"
#include "ui.h"
#include "pauseui.h"
#include "shadow.h"
#include "sound.h"
#include "prize.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[4] = {};

//�R���X�g���N�^
CEnemy::CEnemy(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

//�f�X�g���N�^
CEnemy::~CEnemy(void)
{

}

//����������
HRESULT CEnemy::Init(D3DXVECTOR3 pos, int nType, float fRotY, int nInterval, float fSpeed)
{
	CScene2D::Init(ENEMY_SIZE, ENEMY_SIZE, pos, 1.0f);
	CScene2D::SetObjType(CScene::OBJTYPE_ENEMY);
	m_pShadowScene = CShadow::Create(D3DXVECTOR3(pos.x + 60.0f, pos.y + 60.0f, 0.0f), ENEMY_SIZE / 2, ENEMY_SIZE / 2, (CShadow::SHADOW)(nType + 1));
	SetRot(fRotY);
	m_pShadowScene->SetRot(fRotY);
	m_fRot = fRotY;
	m_fSpeed = fSpeed;
	m_nBullet = 0;
	m_nBulletInter = nInterval;

	//�G�̎�ނɂ���đ̗́A�X�R�A��ݒ肷��
	switch (nType)
	{
	case 0:
		m_nHP = 14;
		m_nScore = 120;
		break;
	case 1:
		m_nHP = 24;
		m_nScore = 240;
		break;
	case 2:
		m_nHP = 20;
		m_nScore = 300;
		break;
	case 3:
		m_nHP = 16;
		m_nScore = 180;
		break;
	default:
		m_nHP = 10;
		m_nScore = 400;
		break;
	}
	m_bUninit = false;
	m_nType = nType;
	m_bShot = false;
	return S_OK;
}

//�I������
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V����
void CEnemy::Update(void)
{
	if (CPauseUi::GetPause() == false)
	{
		if (m_bUninit == false)
		{
			D3DXVECTOR3 pos;
			pos = GetPos();
			//�e����
			if (m_bShot == false)
			{
				m_nBullet++;
				//�e���˃J�E���g���������甭�˂���
				if (m_nBulletInter <= m_nBullet)
				{
					Shot(pos);
				}
			}
			
			//��e������
			if (m_nDamageTime > 0)
			{
				m_nDamageTime--;
				if (m_nDamageTime <= 0)
				{
					//�ʏ�̐F�ɖ߂�
					ChangeColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}

			//�ړ�����
			pos = Move(pos);

			//��ʊO�ɏo��Ə���
			if (pos.x < -ENEMY_SIZE * 3.0f)
			{
				m_bUninit = true;
			}
			else if (pos.x > SCREEN_WIDTH + ENEMY_SIZE * 3.0f)
			{
				m_bUninit = true;
			}
			if (pos.y < -ENEMY_SIZE * 3.0f)
			{
				m_bUninit = true;
			}
			else if (pos.y > SCREEN_HEIGHT + ENEMY_SIZE * 3.0f)
			{
				m_bUninit = true;
			}

			//�ꏊ�A�傫���̐ݒ�(�e�܂�)
			Set(ENEMY_SIZE, ENEMY_SIZE, pos);
			m_pShadowScene->Set(ENEMY_SIZE / 2, ENEMY_SIZE / 2, D3DXVECTOR3(pos.x + 60.0f, pos.y + 60.0f, 0.0f));
		}
		else
		{
			m_pShadowScene->Uninit();
			m_pShadowScene = NULL;
			Uninit();
		}
	}
}

//�`�揈��
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, int nTexType, float fRotY,int nInterval, float fSpeed)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy(PRIORITY_CHARA);
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, nTexType, fRotY, nInterval, fSpeed);
		pEnemy->BindTexture(m_pTexture[nTexType]);
	}
	return pEnemy;
}

//�e�N�X�`���ǂݍ���
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/F-14.png",
		&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MIG-31.png",
		&m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/F-35.png",
		&m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/F-2.png",
		&m_pTexture[3]);
	return S_OK;
}

//�e�N�X�`���j��
void CEnemy::UnLoad(void)
{
	int nCntBg;
	for (nCntBg = 0; nCntBg < 4; nCntBg++)
	{
		if (m_pTexture[nCntBg] != NULL)
		{
			m_pTexture[nCntBg]->Release();
			m_pTexture[nCntBg] = NULL;
		}
	}
}

//�_���[�W����
void CEnemy::Damage(int nDamage)
{
	m_nHP -= nDamage;
	m_nDamageTime = 5;
	if (m_nHP <= 0)
	{
		//���Ď�����
		D3DXVECTOR3 pos;
		pos = GetPos();
		//�v���C�Y�h���b�v
		CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_FIRE, 20);
		CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_ICE, 20);
		CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_THUNDER, 20);
		CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_WATER, 20);
		CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_WIND, 20);
		switch (m_nType)
		{
		case 0:
			CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_FIRE, 20);
			CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_FIRE, 20);
			break;
		case 1:
			CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_ICE, 20);
			CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_ICE, 20);
			break;
		case 2:
			CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_THUNDER, 20);
			CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_THUNDER, 20);
			break;
		case 3:
			CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_WATER, 20);
			CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), ELEMENT_WATER, 20);
			break;
		default:
			break;
		}
		//UI�֘A
		CUi::SetKill();
		CUi::SetScore(m_nScore * 10);
		CExplosion::Create(pos);
		CSound::Play(CSound::SOUND_LABEL_ENEMYSHATDOWN);
		m_pShadowScene->Uninit();
		m_pShadowScene = NULL;
		Uninit();
	}
	else
	{
		CUi::SetScore(m_nScore * nDamage);
		ChangeColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		CSound::Play(CSound::SOUND_LABEL_ENEMYDAMAGE);
	}
}

//�ړ�����
D3DXVECTOR3 CEnemy::Move(D3DXVECTOR3 pos)
{
	pos.x -= m_fSpeed * sinf(m_fRot * D3DX_PI);
	pos.y -= m_fSpeed * cosf(m_fRot * D3DX_PI);
	return pos;
}

//�U������
void CEnemy::Shot(D3DXVECTOR3 pos)
{
	float fRotY = 0.0f;
	int nCntScene;
	for (nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
	{
		CScene *pScene;
		pScene = GetScene(PRIORITY_CHARA, nCntScene);
		if (pScene != NULL)
		{
			OBJTYPE objType;
			objType = pScene->GetObjType();
			if (objType == OBJTYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer;
				posPlayer = pScene->GetPos();
				//�v���C���[�̊p�x���v�Z
				fRotY = atan2f(posPlayer.x - pos.x, pos.y - posPlayer.y);
				break;
			}
		}
	}

	switch (m_nType)
	{
	case 0: //�Α���
		//3��
		CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(fRotY - 0.2f * D3DX_PI), -3.0f * cosf(fRotY - 0.2f * D3DX_PI), 0.0f), true, CScene::ELEMENT_FIRE);
		CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(fRotY), -3.0f * cosf(fRotY), 0.0f), true, CScene::ELEMENT_FIRE);
		CBullet::Create(pos, D3DXVECTOR3(3.0f * sinf(fRotY + 0.2f * D3DX_PI), -3.0f * cosf(fRotY + 0.2f * D3DX_PI), 0.0f), true, CScene::ELEMENT_FIRE);
		break;
	case 1: //�X����
		//�U�e(�����e)
		CBullet::Create(pos, D3DXVECTOR3(4.0f * sinf(fRotY - D3DX_PI * 0.1f), -4.0f * cosf(fRotY - D3DX_PI * 0.1f), 0.0f), true, CScene::ELEMENT_ICE);
		CBullet::Create(pos, D3DXVECTOR3(4.0f * sinf(fRotY + D3DX_PI * 0.1f), -4.0f * cosf(fRotY + D3DX_PI * 0.1f), 0.0f), true, CScene::ELEMENT_ICE);
		break;
	case 2: //������
		//�~�`��
		int nCntBullet;
		for (nCntBullet = 0; nCntBullet < 30; nCntBullet++)
		{
			CBullet::Create(pos, D3DXVECTOR3(2.5f * sinf(fRotY + nCntBullet * (1.0f / 15.0f) * D3DX_PI), -2.5f * cosf(fRotY + nCntBullet * (1.0f / 15.0f) * D3DX_PI), 0.0f), true, CScene::ELEMENT_THUNDER);
		}
		
		break;
	case 3: //������
		//�����e1��
		CBullet::Create(pos, D3DXVECTOR3(5.0f * sinf(fRotY), -5.0f * cosf(fRotY), 0.0f), true, CScene::ELEMENT_WATER);
		break;
	default:
		break;
	}
	m_bShot = true;
	CSound::Play(CSound::SOUND_LABEL_GUN);
}