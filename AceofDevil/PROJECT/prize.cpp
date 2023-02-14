//=============================================================================
//
// �v���C�Y���� [prize.h]
// Author : �O��q��
//
//=============================================================================
#include "manager.h"
#include "prize.h"
#include "renderer.h"
#include "pauseui.h"
#include "player.h"
#include "sound.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CPrize::m_pTexture = NULL;

CPrize::CPrize(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CPrize::~CPrize(void)
{

}

//������
HRESULT CPrize::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, ELEMENT element, int nHeal)
{
	CScene2D::Init(PRIZE_SIZE, PRIZE_SIZE, pos, 1.0f);
	CScene::SetObjType(CScene::OBJTYPE_PRIZE);
	m_move = move;
	m_nHeal = nHeal;
	m_fSize = PRIZE_SIZE;
	m_pPos = GetPlayerPos();
	m_bUninit = false;
	m_nTime = 0;
	m_Element = element;

	//�����ɂ���ĐF�ւ�
	switch (element)
	{
	case ELEMENT_FIRE:
		ChangeColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.7f));
		break;
	case ELEMENT_ICE:
		ChangeColor(D3DXCOLOR(0.5f, 0.5f, 1.0f, 0.7f));
		break;
	case ELEMENT_THUNDER:
		ChangeColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f));
		break;
	case ELEMENT_WATER:
		ChangeColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.7f));
		break;
	case ELEMENT_WIND:
		ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.7f));
		break;
	default:
		break;
	}

	//�����̓����_��
	m_fRotY = (float)(rand() % 628) / 100.0f - D3DX_PI;
	return S_OK;
}

//�I��
void CPrize::Uninit(void)
{
	CScene2D::Uninit();
}

//�X�V
void CPrize::Update(void)
{
	if (CPauseUi::GetPause() == false)
	{
		D3DXVECTOR3 pos;
		pos = GetPos();
		//�����Ȃ�
		if (m_bUninit == false)
		{
			//�o�Ă��Ă����A�����_���̕����ɔ�΂�
			if (m_nTime < 15)
			{
				m_nTime++;
				pos.x += 4.0f * sinf(m_fRotY);
				pos.y += 4.0f * cosf(m_fRotY);
				Set(m_fSize, m_fSize, pos);
			}
			//�����ړ������̂��A��~
			else if (m_nTime < 25)
			{
				m_nTime++;
				if (m_nTime >= 25)
				{
					CSound::Play(CSound::SOUND_LABEL_PRIZE);
				}
			}
			//������~�A�v���C���[�̕����Ɉړ�������������
			else
			{
				float fDistance;
				m_fRotY = atan2f(m_pPos->x - pos.x, pos.y - m_pPos->y);
				pos.x += m_move.x * sinf(m_fRotY);
				pos.y -= m_move.y * cosf(m_fRotY);
				fDistance = sqrtf(powf(m_pPos->x - pos.x, 2.0f) + powf(m_pPos->y - pos.y, 2.0f));
				if (fDistance < 180.0f)
				{
					m_fSize -= 0.9f;
				}
				Set(m_fSize, m_fSize, pos);

				//�������Ȃ�Ə�����
				if (m_fSize <= 0.0f)
				{
					m_bUninit = true;
				}
			}
		}
		else
		{
			//�v���C���[�̑����̖��͂��񕜂�����
			switch (m_Element)
			{
			case ELEMENT_FIRE:
				CPlayer::GetPrize(0, m_nHeal);
				break;
			case ELEMENT_ICE:
				CPlayer::GetPrize(1, m_nHeal);
				break;
			case ELEMENT_THUNDER:
				CPlayer::GetPrize(2, m_nHeal);
				break;
			case ELEMENT_WATER:
				CPlayer::GetPrize(3, m_nHeal);
				break;
			case ELEMENT_WIND:
				CPlayer::GetPrize(4, m_nHeal);
				break;
			default:
				break;
			}
			Uninit();
		}
	}
}

//�`��
void CPrize::Draw(void)
{
	CScene2D::Draw();
}

//�쐬
CPrize *CPrize::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ELEMENT element, int nHeal)
{
	CPrize *pPrize;
	pPrize = new CPrize(PRIORITY_BG);
	if (pPrize != NULL)
	{
		pPrize->Init(pos, move, element, nHeal);
		pPrize->BindTexture(m_pTexture);
	}
	return pPrize;
}

//�e�N�X�`���ǂݍ���
HRESULT CPrize::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/particle.png",
		&m_pTexture);
	return S_OK;
}

//�e�N�X�`���j��
void CPrize::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}