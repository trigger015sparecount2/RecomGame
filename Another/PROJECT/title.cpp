//=============================================================================
// �^�C�g���Ǘ�[Title.cpp]
// Author : �O��q��
//=============================================================================
//*****************************************************************************
//�C���N���[�h
//*****************************************************************************
#if 1
#include "Title.h"
#include "keyboard.h"
#include "UI.h"

#include "game.h"
#include "gamepad.h"
#include "fade.h"

//#include "player.h"
//#include "light.h"

#include "sound.h"
#endif

//*****************************************************************************
//�ÓI
//*****************************************************************************
//int CTitle::m_SerectNam = 1;

//*****************************************************************************
//�}�N��
//*****************************************************************************
//#define MAX_TITLESERECT (4)

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CTitle::CTitle(PRIORITY Priority) : CScene(Priority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CTitle::~CTitle()
{
}
#endif

//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CTitle::Init(D3DXVECTOR3 /*pos*/)
{
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();

	//m_SerectNam = 1;
	//SetSerectNum(m_SerectNam);
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, 19, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 100.0f, 0.0f), 600.0f, 160.0f, 18, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pUI = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 560.0f, 0.0f), 660.0f, 70.0f, 17, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_fClear = 1.0f;
	m_bClear = true;
	m_bButton = false;
	CManager::SetPause(false);
	CSound::Play(CSound::SOUND_LABEL_TITLEBGM);
	m_size = D3DXVECTOR2(660.0f, 70.0f);
	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CTitle::Uninit()
{
	CScene::Release();
}

//*****************************************************************************
// kousinn
//***************************************************************************** 
void CTitle::Update()
{
	//�܂��{�^��������ĂȂ�
	if (m_bButton == false)
	{
		//�Q�[���p�b�h�q�����Ă�
		if (m_pGamePad != NULL)
		{
			//�����{�^�������ꂽ
			if (m_pGamePad->GetAnyButton() == true)
			{
				//�Q�[���Ɉڍs
				CFade::SetFade(CManager::MODE_GAME);
				CSound::Play(CSound::SOUND_LABEL_OK);
				m_bButton = true;
			}
		}
		//�L�[�{�[�h�q�����Ă�
		else if (m_pKeyboard != NULL)
		{
			//�����L�[�����ꂽ
			if (m_pKeyboard->GetAnyKey() == true)
			{
				CFade::SetFade(CManager::MODE_GAME);
				CSound::Play(CSound::SOUND_LABEL_OK);
				m_bButton = true;
			}
		}
	}
	//�{�^�������ꂽ
	else
	{
		//�T�C�Y�ύX
		m_size.x += 12.0f;
		m_size.y -= 5.0f;
		m_pUI->SetSize(m_size);
	}

	//�����ɂ���
	if (m_bClear == true)
	{
		//�F��������
		m_fClear -= 0.05f;
		if (m_fClear <= 0.0f)
		{
			//�Z�����Ă���
			m_fClear = 0.0f;
			m_bClear = false;
		}
	}
	//�F�Z������
	else
	{
		//�F�Z������
		m_fClear += 0.05f;
		if (m_fClear >= 1.0f)
		{
			//�������Ă���
			m_fClear = 1.0f;
			m_bClear = true;
		}
	}

	//�F�ւ�
	m_pUI->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_fClear));
}

#if 1
//*****************************************************************************
//�`��
//***************************************************************************** 
void CTitle::Draw()
{

}

//*****************************************************************************
//�`��
//***************************************************************************** 
CTitle *CTitle::Create()
{
	CTitle *pTitle = NULL;
	pTitle = new CTitle(PRIORITY_EFFECT);		//�������m��
								//NULL�`�F�b�N
	if (pTitle != NULL)
	{
		pTitle->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pTitle;
}
#endif
//
//#if 1
////*****************************************************************************
////�I��ԍ��擾
////***************************************************************************** 
//int CTitle::GetSerectNum()
//{
//	return m_SerectNam;
//}
//
////*****************************************************************************
////�I��ԍ��Z�b�g
////***************************************************************************** 
//void CTitle::SetSerectNum(int nNumSerect)
//{
//	m_SerectNam = nNumSerect;
//}
//#endif