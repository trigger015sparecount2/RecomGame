//=============================================================================
//
// �|�[�Y��UI���� [pauseui.h]
// Author : �O��q��
//
//=============================================================================
#include "pauseui.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "player.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CPauseUi::m_pTexture[6] = {};
CScene2D *CPauseUi::m_apScene[MAX_PAUSEDATA] = {};
bool CPauseUi::m_bUse = false;

CPauseUi::CPauseUi(PRIORITY Priority) : CScene::CScene(Priority)
{

}

CPauseUi::~CPauseUi(void)
{

}

//������
HRESULT CPauseUi::Init(float, float, D3DXVECTOR3, float)
{
	int nCntLife = 0;
	//�Q�[����ʔ��Â�
	m_apScene[nCntLife] = CScene2D::Create(SCREEN_WIDTH, SCREEN_HEIGHT, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), PRIORITY_UI);
	m_apScene[nCntLife]->BindTexture(m_pTexture[2]);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	nCntLife++;

	//���j���[�l�p
	//��[
	m_apScene[nCntLife] = CScene2D::Create(190.0f, 50.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 184.0f, 0.0f), PRIORITY_UI);
	m_apScene[nCntLife]->BindTexture(m_pTexture[0]);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));
	nCntLife++;
	//���[
	m_apScene[nCntLife] = CScene2D::Create(190.0f, 50.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 536.0f, 0.0f), PRIORITY_UI);
	m_apScene[nCntLife]->BindTexture(m_pTexture[0]);
	m_apScene[nCntLife]->SetRot(1.0f);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));
	m_apScene[nCntLife]->Set(190.0f, 50.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 536.0f, 0.0f));
	nCntLife++;
	//�^��
	m_apScene[nCntLife] = CScene2D::Create(190.0f, 200.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), PRIORITY_UI);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));
	m_apScene[nCntLife]->BindTexture(m_pTexture[1]);
	nCntLife++;

	//play
	m_apScene[nCntLife] = CScene2D::Create(115.0f, 50.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 240.0f, 0.0f), PRIORITY_UI);//2.3
	m_apScene[nCntLife]->BindTexture(m_pTexture[3]);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));
	nCntLife++;
	//retry
	m_apScene[nCntLife] = CScene2D::Create(150.0f, 50.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), PRIORITY_UI);//3
	m_apScene[nCntLife]->BindTexture(m_pTexture[4]);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));
	nCntLife++;
	//quit
	m_apScene[nCntLife] = CScene2D::Create(110.0f, 50.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 480.0f, 0.0f), PRIORITY_UI);//2.2
	m_apScene[nCntLife]->BindTexture(m_pTexture[5]);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));
	nCntLife++;
	m_pInputGamePad = CManager::GetInputGamePad();
	m_pInputKeyboard = CManager::GetInputKeyboard();
	m_bUse = false;
	m_nSelect = 0;
	return S_OK;
}

//�I��
void CPauseUi::Uninit(void)
{
	int nCntScene;
	for (nCntScene = 0; nCntScene < MAX_PAUSEDATA; nCntScene++)
	{
		if (m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene] = NULL;
		}
	}
	Release();
}

//�X�V
void CPauseUi::Update(void)
{
	//�Q�[���p�b�h���q�����Ă邩�t�F�[�h�������Ă��Ȃ�
	if (m_pInputGamePad != NULL && CFade::GetFade() == CFade::FADE_NONE)
	{
		//�X�^�[�g�{�^�����������Q�[���I�[�o�[����Ȃ�
		if (m_pInputGamePad->GetButton(CInputGamePad::DIP_START) == true && CPlayer::GetGameOver() == false)
		{
			//�|�[�Y��
			if (m_bUse == true)
			{
				//�|�[�Y����
				PauseLift();
				CSound::Play(CSound::SOUND_LABEL_CANCEL);
			}
			else
			{
				//�|�[�Y����
				Pause();
			}
		}

		//�|�[�Y��
		if (m_bUse == true)
		{
			//�\���L�[����
			if (m_pInputGamePad->TriggerCrossKey() == 0.0f)
			{
				m_apScene[m_nSelect + 4]->ChangeColor(D3DXCOLOR(0.0f, 0.4f, 0.0f, 1.0f));
				m_nSelect--;
				if (m_nSelect < 0)
				{
					m_nSelect = 2;
				}
				m_apScene[m_nSelect + 4]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				CSound::Play(CSound::SOUND_LABEL_CHOICE);
			}
			else if (m_pInputGamePad->TriggerCrossKey() == 18000.0f)
			{
				m_apScene[m_nSelect + 4]->ChangeColor(D3DXCOLOR(0.0f, 0.4f, 0.0f, 1.0f));
				m_nSelect = (m_nSelect + 1) % 3;
				m_apScene[m_nSelect + 4]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				CSound::Play(CSound::SOUND_LABEL_CHOICE);
			}

			//����
			if (m_pInputGamePad->GetButton(CInputGamePad::DIP_B) == true)
			{
				switch (m_nSelect)
				{
				case 0:
					PauseLift();
					break;
				case 1:
					CFade::SetFade(CManager::MODE_GAME);
					break;
				case 2:
					CFade::SetFade(CManager::MODE_TITLE);
					break;
				default:
					break;
				}
				CSound::Play(CSound::SOUND_LABEL_YES);
			}
		}
	}
	//�L�[�{�[�h���q�����Ă�
	else if (m_pInputKeyboard != NULL && CFade::GetFade() == CFade::FADE_NONE)
	{
		//ENTER�������Q�[���I�[�o�[����Ȃ�
		if (m_pInputKeyboard->GetKey(DIK_RETURN) == true && CPlayer::GetGameOver() == false)
		{
			//�|�[�Y��
			if (m_bUse == true)
			{
				//�|�[�Y����
				PauseLift();
				CSound::Play(CSound::SOUND_LABEL_CANCEL);
			}
			else
			{
				//�|�[�Y����
				Pause();
			}
		}

		//�|�[�Y��
		if (m_bUse == true)
		{
			//�I��
			if (m_pInputKeyboard->GetKey(DIK_UP) == true || m_pInputKeyboard->GetKey(DIK_W) == true)
			{
				m_apScene[m_nSelect + 4]->ChangeColor(D3DXCOLOR(0.0f, 0.4f, 0.0f, 1.0f));
				m_nSelect--;
				if (m_nSelect < 0)
				{
					m_nSelect = 2;
				}
				m_apScene[m_nSelect + 4]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				CSound::Play(CSound::SOUND_LABEL_CHOICE);
			}
			else if (m_pInputKeyboard->GetKey(DIK_DOWN) == true || m_pInputKeyboard->GetKey(DIK_S) == true)
			{
				m_apScene[m_nSelect + 4]->ChangeColor(D3DXCOLOR(0.0f, 0.4f, 0.0f, 1.0f));
				m_nSelect = (m_nSelect + 1) % 3;
				m_apScene[m_nSelect + 4]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				CSound::Play(CSound::SOUND_LABEL_CHOICE);
			}

			//����
			if (m_pInputKeyboard->GetKey(DIK_RSHIFT) == true)
			{
				switch (m_nSelect)
				{
				case 0:
					PauseLift();
					break;
				case 1:
					CFade::SetFade(CManager::MODE_GAME);
					break;
				case 2:
					CFade::SetFade(CManager::MODE_TITLE);
					break;
				default:
					break;
				}
				CSound::Play(CSound::SOUND_LABEL_YES);
			}
		}
	}
}

//�`��
void CPauseUi::Draw(void)
{
	
}

//�e�N�X�`���ǂݍ���
HRESULT CPauseUi::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bigsquareside.png",
		&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bigsquarecenter.png",
		&m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/whitebg.png",
		&m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/play.png",
		&m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/retry.png",
		&m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/quit.png",
		&m_pTexture[5]);
	return S_OK;
}

//�e�N�X�`���j��
void CPauseUi::UnLoad(void)
{
	int nCntLife;
	for (nCntLife = 0; nCntLife < 6; nCntLife++)
	{
		if (m_pTexture[nCntLife] != NULL)
		{
			m_pTexture[nCntLife]->Release();
			m_pTexture[nCntLife] = NULL;
		}
	}
}

//�쐬
CPauseUi *CPauseUi::Create(void)
{
	CPauseUi *pPauseUi;
	pPauseUi = new CPauseUi(PRIORITY_UI);
	if (pPauseUi != NULL)
	{
		pPauseUi->Init(0.0f, 0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}
	return pPauseUi;
}

//�|�[�Y����
void CPauseUi::Pause(void)
{
	m_bUse = true;
	int nCntScene;
	for (nCntScene = 0; nCntScene < MAX_PAUSEDATA; nCntScene++)
	{
		if (m_apScene[nCntScene] != NULL)
		{
			if (nCntScene == 0)
			{
				m_apScene[nCntScene]->ChangeColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));
			}
			else if(nCntScene > 4)
			{
				m_apScene[nCntScene]->ChangeColor(D3DXCOLOR(0.0f, 0.4f, 0.0f, 1.0f));
			}
			else
			{
				m_apScene[nCntScene]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
		}
	}
	CSound::Play(CSound::SOUND_LABEL_PAUSE);
}

//�|�[�Y����
void CPauseUi::PauseLift(void)
{
	m_bUse = false;
	int nCntScene;
	for (nCntScene = 0; nCntScene < MAX_PAUSEDATA; nCntScene++)
	{
		if (m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f));
		}
	}
	m_nSelect = 0;
}

