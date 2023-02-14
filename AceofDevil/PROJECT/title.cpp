//=============================================================================
//
// �^�C�g�� [title.h]
// Author : �O��q��
//
//=============================================================================
#include "scene2d.h"
#include "input.h"
#include "sound.h"
#include "title.h"
#include "bg.h"
#include "manager.h"
#include "fade.h"
#include "titleui.h"

//�ÓI�����o�ϐ�
CScene2D *CTitle::m_pScene2D = NULL;
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;

CTitle::CTitle(PRIORITY Priority) : CScene::CScene(Priority)
{

}

CTitle::~CTitle(void)
{

}

//������
HRESULT CTitle::Init(float, float, D3DXVECTOR3, float)
{
	CScene::SetObjType(CScene::OBJTYPE_NONE);
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_pInputGamePad = CManager::GetInputGamePad();
	CBg::Load();
	CTitleUi::Load();
	CBg::Create(false);
	CTitleUi::Create();
	CSound::Play(CSound::SOUND_LABEL_TITLEBGM);
	return S_OK;
}

//�I��
void CTitle::Uninit(void)
{
	CBg::UnLoad();
	CTitleUi::UnLoad();
	if (m_pInputGamePad != NULL)
	{
		m_pInputGamePad = NULL;
	}
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard = NULL;
	}
	Release();
}

//�X�V
void CTitle::Update(void)
{
	//�Q�[���p�b�h���L�[�{�[�h�ŉ��������ꂽ��
	if (m_pInputGamePad != NULL)
	{
		if (m_pInputGamePad->GetAnyButton() == true)
		{
			CFade::SetFade(CManager::MODE_TUTORIAL);
			CSound::Play(CSound::SOUND_LABEL_YES);
		}
	}
	else if (m_pInputKeyboard != NULL)
	{
		if (m_pInputKeyboard->GetAnyKey() == true)
		{
			CFade::SetFade(CManager::MODE_TUTORIAL);
			CSound::Play(CSound::SOUND_LABEL_YES);
		}
	}
}

//�`��
void CTitle::Draw(void)
{

}