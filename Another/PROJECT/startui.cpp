//=============================================================================
//�X�^�[�gUI�Ǘ�[startui.cpp]
// Author : �O��@�q��
//=============================================================================
//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "startui.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CStartUI::CStartUI(PRIORITY Priority) : CUI::CUI(Priority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CStartUI::~CStartUI()
{

}

//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CStartUI::Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col, int nUIType)
{
	CUI::Init(pos, SizeX, SizeY, nType, col);
	size.x = SizeX;
	size.y = SizeY;
	m_nUIType = nUIType;
	m_nTime = 0;
	m_bStop = false;
	m_nFade = 255;
	if (nType == 0)
	{
		CSound::Play(CSound::SOUND_LABEL_READY);
	}
	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CStartUI::Uninit()
{
	CUI::Uninit();
}

//*****************************************************************************
// �X�V
//***************************************************************************** 
void CStartUI::Update()
{
	//UI�^�C�v�ɂ���ď�����ς���
	switch (m_nUIType)
	{
	case 0:	//�ŏ���READY
		//�~�܂�����
		if (m_bStop == true)
		{
			//�~�܂��Ă�Ԃ̃J�E���g
			m_nTime++;

			//�J�E���g���i�񂾂�
			if (m_nTime > 50)
			{
				//���̃p�^�[���𐶐����A�����͏�����
				CStartUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 100.0f, 0.0f), 200.0f, 80.0f, 16, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);
				SetDeath(true);
				CSound::Play(CSound::SOUND_LABEL_GO);
			}
		}
		else
		{
			//�T�C�Y�����������Ă���
			size.x -= 16.4f;
			size.y -= 4.5f;

			//���ȉ��̃T�C�Y�ɂȂ�����
			if (size.x < 200.0f || size.y < 50.0f)
			{
				size.x = 200.0f;
				size.y = 50.0f;
				m_bStop = true;
			}
			SetSize(size);
		}
		break;
	case 1:	//GO
		//�J�E���g�i�߂�A�J�E���g�_�E���t���O��false�ɂ���
		if (m_nTime <= 0)
		{
			m_nTime++;
			CManager::SetCountdown(false);
		}

		//�傫���Ȃ�̑���
		if (m_bStop == false)
		{
			//���X�ɑ傫������
			size.x += 14.0f;
			size.y += 9.0f;

			//���ȏ�̑傫���ɂȂ�����
			if (size.x > 600.0f || size.y > 250.0f)
			{
				//�傫������̒x������
				m_bStop = true;
			}
		}
		//�傫���Ȃ�̒x��
		else
		{
			//���X�ɑ傫������(�x��)
			size.x += 3.0f;
			size.y += 1.7f;

			//���X�ɐF��������
			m_nFade -= 10;

			//�����ɂȂ�
			if (m_nFade < 0)
			{
				//����
				SetDeath(true);
			}
			//�܂��F������
			else
			{
				//�t�F�[�h������
				FadeColorChange(m_nFade);
			}
		}
		//�傫���ύX
		SetSize(size);
		break;
	default:
		break;
	}
}

//*****************************************************************************
//�`��
//***************************************************************************** 
void CStartUI::Draw()
{
	CUI::Draw();
}

//*****************************************************************************
//�쐬
//***************************************************************************** 
CStartUI *CStartUI::Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col, int nUIType)
{
	CStartUI *pStartUI = NULL;
	pStartUI = new CStartUI(PRIORITY_UI);		//�������m��
													//NULL�`�F�b�N
	if (pStartUI != NULL)
	{
		pStartUI->Init(pos, SizeX, SizeY, nType, col, nUIType);
	}

	return pStartUI;
}