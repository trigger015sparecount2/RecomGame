//=============================================================================
//�Q�[���Ǘ�[Game.cpp]
// Author : �O��q��
//=============================================================================
//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#if 1
#include "game.h"
#include "pauseui.h"
#include "player.h"
#include "enemy.h"
#include "ui.h"
#include "keyboard.h"
#include "gamepad.h"
#include "sky.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "startui.h"
//#include "object.h"

#include "field.h"
#include "wall.h"
#include "light.h"

#include "load.h"
#include "sound.h"

#endif
//*****************************************************************************
//�ÓI
//*****************************************************************************
bool CGame::m_bCountFlag = false;
int CGame::m_SelectNum = 1;
int CGame::m_nRound = 1;
bool CGame::m_bRoundChange = false;

//*****************************************************************************
//�}�N��
//*****************************************************************************
//#define GAME_FILE "data/stage.txt"

#if 1
//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame(PRIORITY Priority) : CScene::CScene(Priority)
{

}

//*****************************************************************************
// �f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{

}
#endif

//*****************************************************************************
// ������
//***************************************************************************** 
HRESULT CGame::Init(D3DXVECTOR3 /*pos*/)
{
	CEnemy::Load("data/FILES/motion_bigshadow.txt");
	//CLoad::Load(GAME_FILE);
	
	//UI�쐬
	CUI::Create(D3DXVECTOR3(1200.0f, 620.0f, 0.0), 25.0f, 60.0f, 1, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));		//HP
	CUI::Create(D3DXVECTOR3(1037.5f, 620.0f, 0.0), 300.0f, 60.0f, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));	//HP�Q�[�W���n
	if (CManager::GetGamepad() != NULL)
	{
		CUI::Create(D3DXVECTOR3(120.0f, 550.0f, 0.0), 200.0f, 300.0f, 4, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//������@�Q�[���p�b�h
	}
	else
	{
		CUI::Create(D3DXVECTOR3(120.0f, 550.0f, 0.0), 200.0f, 300.0f, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//������@�L�[�{�[�h
	}
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));
	CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 300.0f, 400.0f, 8, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	//�ȗ���
	CSound::Play(CSound::SOUND_LABEL_GAMEBGM);
	
	//��
	CSky::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0001f, CPlane::GetTexture(2));
	
	//��
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0);
	CLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), 1);
	
	//�v���C���[����
	CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data/FILES/motion_DualPlayer.txt");
	
	//�����z�u�̓G
	CEnemy::Create(D3DXVECTOR3(-300.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CEnemy::Create(D3DXVECTOR3(300.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	//�ǐݒu
	CWall::Create(D3DXVECTOR3(1500.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 400.0f, 2000.0f), 0, D3DXVECTOR2(24.0f, 3.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));					//��
	CWall::Create(D3DXVECTOR3(1500.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 400.0f, -2000.0f), 0, D3DXVECTOR2(24.0f, 3.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));				//��O
	CWall::Create(D3DXVECTOR3(800.0f, 400.0f, 0.0f), D3DXVECTOR3(3000.0f, 400.0f, 0.0f), 0, D3DXVECTOR2(10.0f, 3.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));			//�E
	CWall::Create(D3DXVECTOR3(800.0f, 400.0f, 0.0f), D3DXVECTOR3(-3000.0f, 400.0f, 0.0f), 0, D3DXVECTOR2(10.0f, 3.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f));		//��
	CWall::Create(D3DXVECTOR3(1030.0f, 400.0f, 0.0f), D3DXVECTOR3(2250.0f, 400.0f, 1350.0f), 0, D3DXVECTOR2(10.0f, 3.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));				//�E��
	CWall::Create(D3DXVECTOR3(1030.0f, 400.0f, 0.0f), D3DXVECTOR3(-2250.0f, 400.0f, 1350.0f), 0, D3DXVECTOR2(10.0f, 3.0f), D3DXVECTOR3(0.0f, -0.7f, 0.0f));				//����
	CWall::Create(D3DXVECTOR3(1030.0f, 400.0f, 0.0f), D3DXVECTOR3(-2250.0f, 400.0f, -1350.0f), 0, D3DXVECTOR2(10.0f, 3.0f), D3DXVECTOR3(0.0f, -D3DX_PI + 0.7f, 0.0f));	//����O
	CWall::Create(D3DXVECTOR3(1030.0f, 400.0f, 0.0f), D3DXVECTOR3(2250.0f, 400.0f, -1350.0f), 0, D3DXVECTOR2(10.0f, 3.0f), D3DXVECTOR3(0.0f, D3DX_PI - 0.7f, 0.0f));	//�E��O
	
	//���ݒu
	CField::Create(D3DXVECTOR3(3000.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, D3DXVECTOR2(40.0f, 40.0f), true);
	
	//�X�^�[�gUI
	CStartUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 100.0f, 0.0f), SCREEN_WIDTH, 350.0f, 15, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
	
	//�F�X�ݒ�
	CManager::SetCountdown(true);
	CManager::SetGameClear(false);
	CManager::SetGameEnd(false);
	CManager::SetEnd(false);
	m_nRound = 1;
	return S_OK;
}

//*****************************************************************************
// �I��
//***************************************************************************** 
void CGame::Uninit()
{
	CEnemy::UnLoad();
	Release();
}

//*****************************************************************************
// �X�V
//***************************************************************************** 
void CGame::Update()
{
	//�G�����Ȃ������E���h9��菭�Ȃ�
	if (CEnemy::GetEnemies() <= 0 && m_nRound < 9)
	{
		//���E���h����
		m_nRound++;
		//���E���h�ɉ����ēG�𐶐�
		switch (m_nRound)
		{
		case 0:
			//CEnemy::Create(D3DXVECTOR3(30.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case 1:
			//CEnemy::Create(D3DXVECTOR3(30.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case 2:
			CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(300.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-300.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case 3:
			CEnemy::Create(D3DXVECTOR3(-600.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(600.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-600.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(600.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case 4:
			CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-500.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(500.0f, 0.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(200.0f, 0.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case 5:
			CEnemy::Create(D3DXVECTOR3(1000.0f, 0.0f, 1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, 1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(700.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-700.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(200.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-200.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case 6:
			CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-400.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(30.0f, 0.0f, -1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case 7:
			CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-400.0f, 0.0f, 7000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-400.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case 8:
			CEnemy::Create(D3DXVECTOR3(1000.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(1000.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-1000.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(2500.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(2500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-2500.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-2500.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(1850.0f, 0.0f, 1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(2650.0f, 0.0f, 1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-1850.0f, 0.0f, 1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-2650.0f, 0.0f, 1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(1850.0f, 0.0f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(2650.0f, 0.0f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-1850.0f, 0.0f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CEnemy::Create(D3DXVECTOR3(-2650.0f, 0.0f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			break;
		case 9:
			CManager::SetGameClear(true);
			m_nRound++;
			break;
		default:
			break;
		}
		if (m_nRound < 9)
		{
			m_bRoundChange = true;
		}
	}
}

//*****************************************************************************
//�`��
//***************************************************************************** 
void CGame::Draw()
{

}

//*****************************************************************************
//�쐬
//***************************************************************************** 
CGame *CGame::Create()
{
	CGame *pGame = NULL;
	pGame = new CGame(PRIORITY_ORBIT);		//�������m��
	//NULL�`�F�b�N
	if (pGame != NULL)
	{
		pGame->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pGame;
}

//���E���h���擾
int CGame::GetRound()
{
	m_bRoundChange = false;
	return m_nRound;
}