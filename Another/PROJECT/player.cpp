//---------------------------
//Author:�O��q��
//���f��(player.cpp)
//---------------------------
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "mouse.h"
#include "keyboard.h"
#include "model.h"
#include "camera.h"
#include "fade.h"
#include "shadow.h"
#include "gamepad.h"
#include "game.h"
#include "sound.h"
#include "orbit.h"
#include "particle.h"
#include "rockon.h"
#include "ui.h"
#include "pauseui.h"
#include "enemy.h"

//=============================================================================
//�ÓI
//=============================================================================

//=============================================================================
//�}�N��
//=============================================================================
#define RAND_COLOR (int(rand()%255) + 30)	//�F�����_��
#define RAND_MOVE ((int(rand() % 3) + 1 )- (int (rand()%3) + 1))	//�ړ��l�����_��
#define RAND_MOVE_2 ((int(rand() % 3) + 1 ))	//�ړ��l�����_��

CPlayer::CPlayer(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{

}

CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName)
{
	Load(aFileName);
	SetPos(pos);
	SetRot(rot);
	m_nMaxHP = m_nHP;
	m_rotDesh = rot;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_RestartPos = pos;
	m_PosOld = pos;
	m_pKeyboard = CManager::GetKeyboard();
	m_pGamePad = CManager::GetGamepad();
	m_pMouse = CManager::GetMouse();
	m_pCamera = CManager::GetRenderer()->GetCamera();
	m_pRockon = CRockon::Create();
	m_pCamera->ResetRot();
	m_pCamera->SetPlayer(this);
	m_bJump = true;
	m_bLandObject = false;
	m_bHit = false;
	m_bCounter = false;
	m_nComboTime = 0;
	m_nNonOpe = 0;
	m_motionTypeOld = MOTIONTYPE_NEUTRAL;
	m_nRunStop = 0;
	m_nCntDamage = 0;
	m_nCntCol = 0;
	m_bRockon = false;
	m_nCntNoDmg = 0;
	m_nCntRun = 0;
	m_nPauseSelect = 0;
	m_nCntDeath = 0;
	m_nCntRoundChange = -1;
	m_bGameClear = false;
	m_bEndSelect = false;
	m_bPinch = false;
	D3DXVECTOR3 size;
	size.x = GetRadius();
	size.y = 0.0f;
	size.z = GetRadius();
	m_pShadow = CShadow::Create(size, D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));
	MotionChange(MOTIONTYPE_RETURN);
	m_bLanding = true;
	int nCntOrbit;
	for (nCntOrbit = 0; nCntOrbit < 4; nCntOrbit++)
	{
		m_pOrbit[nCntOrbit] = COrbit::Create();
	}
	if (m_pGamePad != NULL)
	{
		m_pCounterUI = CUI::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), 300.0f, 80.0f, 6, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//�J�E���^�[�Q�[���p�b�h
	}
	else
	{
		m_pCounterUI = CUI::Create(D3DXVECTOR3(640.0f, 600.0f, 0.0f), 300.0f, 80.0f, 5, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//�J�E���^�[�L�[�{�[�h
	}
	m_pHPUI = CUI::Create(D3DXVECTOR3(1037.5f, 620.0f, 0.0), 298.0f, 58.0f, 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//HP�Q�[�W

	//�G��HPUI
	m_pEnemyHPUI[0] = CUI::Create(D3DXVECTOR3(1230.0f, 60.0f, 0.0), 16.0f, 40.0f, 1, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
	m_pEnemyHPUI[1] = CUI::Create(D3DXVECTOR3(1097.0f, 60.0f, 0.0), 250.0f, 40.0f, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pEnemyHPUI[2] = CUI::Create(D3DXVECTOR3(1097.0f, 60.0f, 0.0), 248.0f, 38.0f, 7, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	
	//�|�[�YUI
	m_pPauseUI[0] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.0f, 0.0f), 240.0f, 60.0f, 9, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pPauseUI[1] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 190.0f, 60.0f, 10, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f));
	m_pPauseUI[2] = CPauseUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100.0f, 0.0f), 150.0f, 60.0f, 11, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f));
	
	//���E���h��UI
	m_pRoundUI[0] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), 200.0f, 60.0f, 14, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pRoundUI[1] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 30.0f, 100.0f, 0.0f), 50.0f, 65.0f, 12, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pRoundUI[2] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 110.0f, 0.0f), 20.0f, 50.0f, 13, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pRoundUI[3] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 20.0f, 120.0f, 0.0f), 30.0f, 40.0f, 12, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pRoundUI[1]->SetTex(1, 0.1f);
	m_pRoundUI[3]->SetTex(MAX_ROUND, 0.1f);
	return S_OK;
}

//�I������
void CPlayer::Uninit()
{
	if (m_pCamera != NULL)
	{
		m_pCamera = NULL;
	}
	if (m_pGamePad != NULL)
	{
		m_pGamePad = NULL;
	}
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard = NULL;
	}
	int nCnt;
	for (nCnt = 0; nCnt < 32; nCnt++)
	{
		if (m_pModel[nCnt] != NULL)
		{
			m_pModel[nCnt]->Uninit();
			m_pModel[nCnt] = NULL;
		}
	}
	if (m_pMouse != NULL)
	{
		m_pMouse = NULL;
	}
	if (m_pShadow != NULL)
	{
		m_pShadow->SetDeath(true);
		m_pShadow = NULL;
	}
	for (nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_pOrbit[nCnt] != NULL)
		{
			m_pOrbit[nCnt] = NULL;
		}
	}
	for (nCnt = 0; nCnt < 16; nCnt++)
	{
		if (m_pEnemy[nCnt] != NULL)
		{
			m_pEnemy[nCnt] = NULL;
		}
	}
	if (m_pCounterUI != NULL)
	{
		m_pCounterUI = NULL;
	}
	if (m_pHPUI != NULL)
	{
		m_pHPUI = NULL;
	}
	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_pEnemyHPUI[nCnt] != NULL)
		{
			m_pEnemyHPUI[nCnt] = NULL;
		}
	}
	for (nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_pPauseUI[nCnt] != NULL)
		{
			m_pPauseUI[nCnt] = NULL;
		}
	}
	for (nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_pRoundUI[nCnt] != NULL)
		{
			m_pRoundUI[nCnt] = NULL;
		}
	}
	for (nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pEndUI[nCnt] != NULL)
		{
			m_pEndUI[nCnt] = NULL;
		}
	}
	CScene3D::Uninit();
}

//�X�V����
void CPlayer::Update()
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	m_PosOld = pos;
	bool bRun = false;
	bool bCamera = false;
	if (m_bLandObject == true && m_bJump == false)
	{
		//���n���Ă�
		m_bJump = true;
	}
	if (m_bJump == false && m_bLanding == true)
	{
		//���n���ĂȂ�
		m_bLanding = false;
	}
	if (CManager::GetGameClear() == true && m_bGameClear == false)
	{
		//�Q�[���N���A
		GameClear();
		pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	if (m_bRockon == true)
	{
		//���b�N�I���̓G��NULL�Ȃ烍�b�N�I������
		if (m_pRockon->GetRockEnemy() == NULL)
		{
			m_bRockon = false;
		}
	}

	//���[�V���������ꂽ��ł��N���A�ł��Ȃ�
	if (m_motionType != MOTIONTYPE_DEATH && m_motionType != MOTIONTYPE_CLEAR)
	{
		//�|�[�Y������Ȃ��A�J�E���g�_�E�����ĂȂ��A�I����ĂȂ�
		if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetEnd() == false)
		{
			//�R���{�̃J�E���g�i�߂�
			if (m_nComboTime > 0)
			{
				m_nComboTime--;
			}

			//����֎~�J�E���g�i�߂�
			if (m_nNonOpe > 0)
			{
				m_nNonOpe--;
			}

			//���G�J�E���g�i�߂�
			if (m_nCntNoDmg > 0)
			{
				m_nCntNoDmg--;
			}

			//�s���`�Ȃ�
			if (m_bPinch == true)
			{
				//�s���`�J�E���g�i�߂�
				m_nCntPinch--;
				if (m_nCntPinch <= 0)
				{
					//�F����A�J�E���g���Z�b�g
					m_pHPUI->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					m_nCntPinch = 20;
				}
				else if (m_nCntPinch % 10 == 0)
				{
					//�����ɂ���
					m_pHPUI->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
			}

			//���[�V������������
			if (m_motionType == MOTIONTYPE_RUN && m_nCntRun > 0)
			{
				//����J�E���g�i�߂�
				m_nCntRun--;
				if (m_nCntRun <= 0)
				{
					//�J�E���g���Z�b�g�A�����炷
					m_nCntRun = 12;
					CSound::Play(CSound::SOUND_LABEL_FOOTSTEP);
				}
			}

			//���E���h�ύX�J�E���g�i�߂�
			if (m_nCntRoundChange > 0)
			{
				m_nCntRoundChange--;
				if (m_nCntRoundChange % 10 == 0)
				{
					//�_����
					m_pRoundUI[1]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
				}
				else if (m_nCntRoundChange % 5 == 0)
				{
					//����
					m_pRoundUI[1]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
				}
			}

			//�Q�[���p�b�h�q�����Ă�
			if (m_pGamePad != NULL)
			{
				//����s�\�J�E���g0�ȉ�
				if (m_nNonOpe <= 0)
				{
					//����
					if (fabsf(m_pGamePad->LeftStickX()) >= 0.3f || fabsf(m_pGamePad->LeftStickY()) >= 0.3f)
					{
						bRun = Move(atan2f(m_pGamePad->LeftStickX(), -m_pGamePad->LeftStickY()) / D3DX_PI);
					}
					else
					{
						bRun = Stop();
					}

					//���邩�W�����v�\�����[�V����������ȊO
					if (bRun == true && m_bJump == true && m_motionType != MOTIONTYPE_RUN)
					{
						//���点��
						MotionChange(MOTIONTYPE_RUN);
						m_nCombo = 0;
						m_nCntRun = 6;
					}

					//�����ĂȂ������郂�[�V����
					if (bRun == false && m_motionType == MOTIONTYPE_RUN)
					{
						//�����ĂȂ��J�E���g�i�߂�B�J�E���g�i�񂾂�
						m_nRunStop++;
						if (m_nRunStop > 10)
						{
							//���[�V�����߂�
							MotionChange(MOTIONTYPE_RETURN);
							m_nRunStop = 0;
							m_nCntRun = -1;
						}
					}

					//�W�����v
					if (m_pGamePad->GetButton(CGamePad::DIP_A) == true)
					{
						Jump();
					}
				}
				else
				{
					//�ړ��ʌ���
					bRun = Stop();
				}

				//����s�\�J�E���g0�ȉ��܂��͍U�����������Ă�
				if (m_nNonOpe <= 0 || m_bHit == true)
				{
					//�R���{�����J�E���g
					if (m_nComboTime <= 0)
					{
						//�U��
						if (m_pGamePad->GetButton(CGamePad::DIP_B) == true)
						{
							if (m_bRockon == true)
							{
								//���b�N�I�����Ă�
								MotionChange(RockAttack(pos));
							}
							else
							{
								//�m�[���b�N
								MotionChange(NoRockAttack());
							}
						}
					}

					//�K�[�h�E���
					if (m_pGamePad->GetButton(CGamePad::DIP_X) == true)
					{
						//�R���{����0�ɖ߂�
						m_nCombo = 0;
						//���X�e�B�b�N�X���Ă�
						if (sqrtf(m_pGamePad->LeftStickX()) >= 0.3f || sqrtf(m_pGamePad->LeftStickY()) >= 0.3f)
						{
							//���X�e�B�b�N�A�J�������ꂼ��̕���
							float fRotY = atan2f(m_pGamePad->LeftStickX(), -m_pGamePad->LeftStickY());
							float fCameraRotY = m_pCamera->GetRotY();
							m_rotDesh.y = fCameraRotY + fRotY + D3DX_PI;
							//���n���Ă�
							if (m_bJump == false)
							{
								//�󒆉��
								MotionChange(MOTIONTYPE_AIRDODGE);
								CSound::Play(CSound::SOUND_LABEL_DODGE);
							}
							//���n���ĂȂ�
							else
							{
								//�n����
								MotionChange(MOTIONTYPE_GROUNDDODGE);
								CSound::Play(CSound::SOUND_LABEL_DODGE);
							}
						}
						//���X�e�B�b�N�X���ĂȂ�
						else
						{
							//�K�[�h
							MotionChange(MOTIONTYPE_GUARD);
						}
					}
				}

				//���b�N�I��
				if (m_pGamePad->GetButton(CGamePad::DIP_R1) == true)
				{
					//���b�N�I�����ĂȂ�������
					if (m_bRockon == false)
					{
						//���b�N�I������
						Rockon();
					}
					else
					{
						//���b�N�I������
						UnRockon();
					}
				}

				//�E�X�e�B�b�N�E�ɌX����
				if (sqrtf(m_pGamePad->RightStickX()) >= 0.3f)
				{
					//�J�����E��]
					m_pCamera->AddRotY(m_pGamePad->RightStickX() * 0.03f);
					bCamera = true;
				}

				//�E�X�e�B�b�N���ɌX����
				if (sqrtf(m_pGamePad->RightStickY()) >= 0.3f)
				{
					//�J��������]
					m_pCamera->AddRotX(m_pGamePad->RightStickY() * -0.03f);
					bCamera = true;
				}
				//�J������]���邩�ݒ�
				m_pCamera->SetAdd(bCamera);

				//�|�[�Y
				if (m_pGamePad->GetButton(CGamePad::DIP_START) == true)
				{
					CManager::SetPause(true);
					CSound::Play(CSound::SOUND_LABEL_PAUSE);
				}
			}
			//�L�[�{�[�h�q�����Ă�
			else if (m_pKeyboard != NULL)
			{
				//����s�\�J�E���g0�ȉ�
				if (m_nNonOpe <= 0)
				{
					//�ړ�
					if (m_pKeyboard->GetPress(DIK_A) == true)
					{
						if (m_pKeyboard->GetPress(DIK_S) == true)
						{
							bRun = Move(-0.75f);
						}
						else if (m_pKeyboard->GetPress(DIK_W) == true)
						{
							bRun = Move(-0.25f);
						}
						else
						{
							bRun = Move(-0.5f);
						}
					}
					else if (m_pKeyboard->GetPress(DIK_D) == true)
					{
						if (m_pKeyboard->GetPress(DIK_S) == true)
						{
							bRun = Move(0.75f);
						}
						else if (m_pKeyboard->GetPress(DIK_W) == true)
						{
							bRun = Move(0.25f);
						}
						else
						{
							bRun = Move(0.5f);
						}
					}
					else if (m_pKeyboard->GetPress(DIK_W) == true)
					{
						bRun = Move(0.0f);
					}
					else if (m_pKeyboard->GetPress(DIK_S) == true)
					{
						bRun = Move(1.0f);
					}
					else
					{
						bRun = Stop();
					}

					//�����Ă邩���n���Ă邩����ȊO�̃��[�V����
					if (bRun == true && m_bJump == true && m_motionType != MOTIONTYPE_RUN)
					{
						//���郂�[�V����
						MotionChange(MOTIONTYPE_RUN);
						m_nCombo = 0;
						m_nCntRun = 6;
					}

					//�����ĂȂ������郂�[�V����
					if (bRun == false && m_motionType == MOTIONTYPE_RUN)
					{
						//�����ĂȂ��J�E���g�i�߂�B�J�E���g�i�񂾂�
						m_nRunStop++;
						if (m_nRunStop > 10)
						{
							//�߂�
							MotionChange(MOTIONTYPE_RETURN);
							m_nRunStop = 0;
							m_nCntRun = -1;
						}
					}
					//�W�����v
					if (m_pKeyboard->GetKey(DIK_SPACE) == true && m_bJump == true)
					{
						Jump();
					}
				}
				else
				{
					//��~
					Stop();
				}

				//����s�\�J�E���g0�ȉ��܂��͍U���������Ă�
				if (m_nNonOpe <= 0 || m_bHit == true)
				{
					//�R���{�J�E���g0�ȉ�
					if (m_nComboTime <= 0)
					{
						//�U��
						if (m_pKeyboard->GetKey(DIK_J) == true)
						{
							if (m_bRockon == true)
							{
								//���b�N�I�����Ă�
								MotionChange(RockAttack(pos));
							}
							else
							{
								//�m�[���b�N
								MotionChange(NoRockAttack());
							}
						}
					}

					//�K�[�h�E���
					if (m_pKeyboard->GetKey(DIK_I) == true)
					{
						//�R���{0�ɖ߂�
						m_nCombo = 0;
						//�ړ�
						if (m_pKeyboard->GetPress(DIK_W) == true || m_pKeyboard->GetPress(DIK_S) == true ||
							m_pKeyboard->GetPress(DIK_A) == true || m_pKeyboard->GetPress(DIK_D) == true)
						{
							float fRotY = 1.0f;
							if (m_pKeyboard->GetPress(DIK_A) == true)
							{
								if (m_pKeyboard->GetPress(DIK_S) == true)
								{
									fRotY = -0.75f;
								}
								else if (m_pKeyboard->GetPress(DIK_W) == true)
								{
									fRotY = -0.25f;
								}
								else
								{
									fRotY = -0.5f;
								}
							}
							else if (m_pKeyboard->GetPress(DIK_D) == true)
							{
								if (m_pKeyboard->GetPress(DIK_S) == true)
								{
									fRotY = 0.75f;
								}
								else if (m_pKeyboard->GetPress(DIK_W) == true)
								{
									fRotY = 0.25f;
								}
								else
								{
									fRotY = 0.5f;
								}
							}
							else if (m_pKeyboard->GetPress(DIK_W) == true)
							{
								fRotY = 0.0f;
							}
							else if (m_pKeyboard->GetPress(DIK_S) == true)
							{
								fRotY = 1.0f;
							}

							//�J�����̕����擾�A��������
							float fCameraRotY = m_pCamera->GetRotY();
							m_rotDesh.y = fCameraRotY + D3DX_PI * fRotY + D3DX_PI;
							if (m_rotDesh.y >= D3DX_PI)
							{
								m_rotDesh.y -= D3DX_PI * 2;
							}
							if (m_rotDesh.y < -D3DX_PI)
							{
								m_rotDesh.y += D3DX_PI * 2;
							}
							rot.y = m_rotDesh.y;

							//���n���ĂȂ�
							if (m_bJump == false)
							{
								//�󒆉��
								MotionChange(MOTIONTYPE_AIRDODGE);
								CSound::Play(CSound::SOUND_LABEL_DODGE);
							}
							//���n���Ă�
							else
							{
								//�n����
								MotionChange(MOTIONTYPE_GROUNDDODGE);
								CSound::Play(CSound::SOUND_LABEL_DODGE);
							}
						}
						//�ړ����Ȃ�
						else
						{
							//�K�[�h
							MotionChange(MOTIONTYPE_GUARD);
						}	
					}
				}

				//���b�N�I��
				if (m_pKeyboard->GetKey(DIK_R) == true)
				{
					//���b�N�I�����ĂȂ�
					if (m_bRockon == false)
					{
						//���b�N�I������
						Rockon();
					}
					//���b�N�I�����Ă�
					else
					{
						//���b�N�I���O��
						UnRockon();
					}
				}

				//�|�[�Y
				if (m_pKeyboard->GetKey(DIK_ESCAPE) == true)
				{
					CManager::SetPause(true);
					CSound::Play(CSound::SOUND_LABEL_PAUSE);
				}

				//�}�E�X�q�����Ă�
				if (m_pMouse != NULL)
				{
					//�}�E�X�������Ă�
					if (m_pMouse->MouseX() != 0.0f || m_pMouse->MouseY() != 0.0f)
					{
						//�J�����̉�]
						m_pCamera->AddRotY(m_pMouse->MouseX() * 0.001f);
						m_pCamera->AddRotX(m_pMouse->MouseY() * -0.002f);
					}
					else
					{
						//��]�����Ȃ�
						m_pCamera->SetAdd(false);
					}
				}
			}
		}
		//�|�[�Y���Ă邩�J�E���g�_�E�����ĂȂ�
		else if(CManager::GetPause() == true && CManager::GetCountdown() == false)
		{
			//�Q�[���p�b�h�q�����Ă�
			if (m_pGamePad != NULL)
			{
				//�|�[�Y����
				if (m_pGamePad->GetButton(CGamePad::DIP_START) == true)
				{
					CManager::SetPause(false);
					CSound::Play(CSound::SOUND_LABEL_CANCEL);
				}

				//�I�����I��
				if (m_pGamePad->TriggerCrossKey() == 0.0f)
				{
					PauseChange(-1);
				}
				else if (m_pGamePad->TriggerCrossKey() == 18000.0f)
				{
					PauseChange(1);
				}

				//����
				if (m_pGamePad->GetButton(CGamePad::DIP_B) == true)
				{
					PauseSelect();
				}
			}
			//�L�[�{�[�h
			else if (m_pKeyboard != NULL)
			{
				//�|�[�Y
				if (m_pKeyboard->GetKey(DIK_ESCAPE) == true)
				{
					CManager::SetPause(false);
					CSound::Play(CSound::SOUND_LABEL_CANCEL);
				}

				//�I��
				if (m_pKeyboard->GetKey(DIK_W) == true || m_pKeyboard->GetKey(DIK_UP) == true)
				{
					PauseChange(-1);
				}
				else if (m_pKeyboard->GetKey(DIK_S) == true || m_pKeyboard->GetKey(DIK_DOWN) == true)
				{
					PauseChange(1);
				}

				//�I��
				if (m_pKeyboard->GetKey(DIK_RETURN) == true)
				{
					PauseSelect();
				}
			}
		}

		//���b�N�I�����Ă�
		if (m_bRockon == true)
		{
			//���b�N�I�����Ă�G���T�[�`����
			SearchRock(pos);
		}
		else
		{
			//���[�V�����̈ړ���0
			if (m_MotionInfo.aKeyInfo[m_nKey].fMove == 0.0f)
			{
				//��~
				MotionStopMove();
			}
			//�ǔ����Ȃ�
			else if (m_MotionInfo.bHoming == false)
			{
				//���[�V�����̈ړ�
				MotionMove(m_rotDesh.y, m_MotionInfo.aKeyInfo[m_nKey].fMove);
			}
			else
			{
				//���[�V�����̈ړ�����
				MotionMove(m_rotDesh.y, m_MotionInfo.aKeyInfo[m_nKey].fMove * 0.5f);
			}
		}

		//�|�[�Y���ĂȂ����J�E���g�_�E�����ĂȂ����I����ĂȂ�
		if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetEnd() == false)
		{
			//�ꏊ���Z
			pos += m_move + m_MotionMove;
			
			//�G�A�I�u�W�F�N�g�A�ǂƏ��A�_���[�W����Ƃ̓����蔻��
			CollisionEnemy(&pos);
			CollisionObject(&pos, m_PosOld);
			CollisionPlane(&pos, m_PosOld);
			PlayerDamage(pos, m_fHeight, m_fRadius);

			//�󒆂ɂ���A�d�͓���
			if (m_bJump == false && m_MotionInfo.bGravity == true)
			{
				//�������̈ړ��ʉ��Z
				if (m_move.y > -25.0f)
				{
					m_move.y -= m_fGravity;
				}
				else
				{
					m_move.y = -25.0f;
				}
			}

			//�󒆂ɋ�����A�e�ݒ�
			if (m_bJump == false)
			{
				UnderSearch(pos);
			}

			//�󒆂ɂ��邩�j���[�g�������[�V�����܂��͑��郂�[�V����
			if (m_bJump == false && m_motionType == MOTIONTYPE_NEUTRAL || m_bJump == false && m_motionType == MOTIONTYPE_RUN)
			{
				//�󒆃��^�[�����[�V����
				MotionChange(MOTIONTYPE_AIRRETURN);
			}

			//�d�͓����Ȃ�����Y���ړ��ʂ�0�ȊO�A0�ɂ���
			if (m_MotionInfo.bGravity == false && m_move.y != 0.0f)
			{
				m_move.y = 0.0f;
			}

			//�e�ړ�
			m_pShadow->Move(pos.y);

			//���b�N�I�����Ă�
			if (m_bRockon == true)
			{
				//���b�N�I�����Ă�G�̈ʒu�ɂ��A�J������]
				RockCameraMove(pos);
			}
		}
	}
	//���[�V���������ꂽ����N���A�������
	else
	{
		//�I��������Ƃ̑I�����o�Ă�����
		if (m_bEndSelect == true)
		{
			//�Q�[���p�b�h�q�����Ă�
			if (m_pGamePad != NULL)
			{
				//�I��
				if (m_pGamePad->TriggerCrossKey() == 0.0f)
				{
					EndChange(-1);
				}
				else if (m_pGamePad->TriggerCrossKey() == 18000.0f)
				{
					EndChange(1);
				}

				//����
				if (m_pGamePad->GetButton(CGamePad::DIP_B) == true)
				{
					EndSelect();
				}
			}
			//�L�[�{�[�h�q�����Ă�
			else if (m_pKeyboard != NULL)
			{
				//�I��
				if (m_pKeyboard->GetKey(DIK_W) == true || m_pKeyboard->GetKey(DIK_UP) == true)
				{
					EndChange(-1);
				}
				else if (m_pKeyboard->GetKey(DIK_S) == true || m_pKeyboard->GetKey(DIK_DOWN) == true)
				{
					EndChange(1);
				}

				//����
				if (m_pKeyboard->GetKey(DIK_RETURN) == true)
				{
					EndSelect();
				}
			}
		}
		//�I����Ă��玞�Ԍo��
		else if (m_nCntDeath > 150)
		{
			//�������ɂ���A���ۂ�UI����A�I��������UI����
			m_bEndSelect = true;
			CManager::SetEnd(true);
			CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, -1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.6f));
			if (m_nHP <= 0)
			{
				CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 120.0f, 0.0f), 270.0f, 80.0f, 20, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 120.0f, 0.0f), 280.0f, 80.0f, 21, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			m_pEndUI[0] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 500.0f, 0.0f), 220.0f, 80.0f, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pEndUI[1] = CUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 600.0f, 0.0f), 170.0f, 80.0f, 11, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
			m_nPauseSelect = 0;
			CSound::Play(CSound::SOUND_LABEL_SELECT);
		}
		else
		{
			//�I������J�E���g�i�߂�
			m_nCntDeath++;
		}
	}

	//��������Ȃ��悤�ɂ���
	if (rot.y >= D3DX_PI)
	{
		rot.y -= D3DX_PI * 2;
	}
	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	//�������Ă�����ƖړI�̕������������A�����Ă���
	if (rot.y != m_rotDesh.y)
	{
		if (m_rotDesh.y - rot.y < -D3DX_PI)
		{
			rot.y += (m_rotDesh.y - rot.y + D3DX_PI * 2) * 0.14f;
		}
		else if (m_rotDesh.y - rot.y > D3DX_PI)
		{
			rot.y += (m_rotDesh.y - rot.y - D3DX_PI * 2) * 0.14f;
		}
		else
		{
			rot.y += (m_rotDesh.y - rot.y) * 0.14f;
		}
	}

	//�|�[�Y���ĂȂ����I����ĂȂ�
	if (CManager::GetPause() == false && CManager::GetEnd() == false)
	{
		//���[�V��������A�����ݒ�
		Motion();
		SetRot(rot);

		//���ɍs���߂�����ʒu�߂��A�ʒu�ݒ�
		if (pos.y < -1000.0f)
		{
			pos = m_RestartPos;
		}
		SetPos(pos);

		//���E���h�ύX��������A���E���hUI�ς���
		if (CGame::GetRoundChange() == true)
		{
			m_pRoundUI[1]->SetTex(CGame::GetRound(), 0.1f);
			m_nCntRoundChange = 60;
		}
		////�`�[�g����
		//if (m_pKeyboard != NULL)
		//{
		//	//���X�|�[���n�_�ɖ߂�
		//	if (m_pKeyboard->GetKey(DIK_RETURN) == true)
		//	{
		//		m_MotionMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//		m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//		SetPos(m_RestartPos);
		//		m_pCamera->ResetRot();
		//	}
		//	//���X�|�[���n�_�̐ݒ�
		//	if (m_pKeyboard->GetKey(DIK_LSHIFT) == true)
		//	{
		//		m_RestartPos = pos;
		//	}
		//}
	}
}

//�`�揈��
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxPlayer, mtxRot, mtxTrans;
	pDevice = CManager::GetRenderer()->GetDevice();		 //�f�o�C�X���擾����
	
	//�v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxPlayer);

	//�v���C���[�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxRot);

	//�v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxPlayer, &mtxPlayer, &mtxTrans);

	//�v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxPlayer);
	SetMatrix(mtxPlayer);

	int nCntModel;
	for (nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw();
		}
	}
	//CollisionPos();
	//�O��
	Orbit();
}

//�t�@�C���ǂݍ���
void CPlayer::Load(const char *aFileName)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	D3DXVECTOR3 rot;
	D3DXVECTOR3 pos;
	int nParent;
	CModel *paModel[32];

	int nCntParts = 0;
	int nCntMotion = 0;
	int nCntKey = 0;
	int nCntCol = 0;
	int nCntObt = 0;
	int nCntDmg = 0;
	char aFile[256];
	int nLoop = 0;
	int nHorming = 0;
	int nUpdn = 0;
	int nGravity = 0;

	bool bChara = false;
	bool bParts = false;
	bool bMotion = false;
	bool bOrbit = false;
	bool bOrbitSet = false;
	bool bKey = false;
	bool bKeySet = false;
	bool bColSet = false;
	bool bCol = false;
	bool bDmgSet = false;
	bool bDmg = false;
	int nIndex;

	FILE *pFile;
	pFile = fopen(aFileName, "r");
	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]); //fscanf���J��Ԃ��ăt�@�C����ǂݎ���Ă���
			if (strcmp(&aFile[0], "#") == 0) //���f���t�@�C���ǂݍ���
			{
				fscanf(pFile, "%s", &aFile[0]);
			}
			if (strcmp(&aFile[0], "MODEL_FILENAME") == 0) //���f���t�@�C���ǂݍ���
			{
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%s", &aFile[0]);
				paModel[nCntParts] = CModel::Create(&aFile[0]);
				nCntParts++;
			}
			if (bChara == true) //CHARACTERSET��
			{
				if (strcmp(&aFile[0], "NUM_PARTS") == 0) //�p�[�c��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_nNumModel);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //�ړ����x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0) //�W�����v��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fJump);
				}
				if (strcmp(&aFile[0], "GRAVITY") == 0) //�d��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fGravity);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0) //���a
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_fHeight);
				}
				if (strcmp(&aFile[0], "HP") == 0) //�̗�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_nHP);
				}
				if (strcmp(&aFile[0], "PARTSSET") == 0)
				{
					bParts = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)
				{
					bParts = false;
					nCntParts++;
				}
				if (bParts == true) //PARTSSET��
				{
					//if (strcmp(&aFile[0], "MOVEPARTS") == 0) //���ꂪ������g_player��pos�������i����Ȃ������j
					//{
					//	g_player.nMoveParts = nCntParts;
					//}
					if (strcmp(&aFile[0], "INDEX") == 0) //���f���t�@�C���ǂݍ��݂̎��́A���Ԗڂ̃��f�����Ăяo����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nIndex);
						m_pModel[nCntParts] = paModel[nIndex];
					}
					if (strcmp(&aFile[0], "PARENT") == 0) //�e���f��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);
						if (nParent != -1)
						{
							m_pModel[nCntParts]->SetParent(m_pModel[nParent]);
						}
					}
					if (strcmp(&aFile[0], "POS") == 0) //�e�p�[�c�̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_pModel[nCntParts]->SetOriPos(pos);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //�e�p�[�c�̊p�x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_pModel[nCntParts]->SetOriRot(rot);
					}
				}
			}
			if (bMotion == true && nCntMotion < MOTIONTYPE_RETURN) //MOTIONSET��
			{
				if (strcmp(&aFile[0], "LOOP") == 0) //���̃��[�V���������[�v���邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);
					if (nLoop == 0)
					{
						m_aMotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						m_aMotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "HORMING") == 0) //�ړ��ʂ����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nHorming);
					if (nHorming == 0)
					{
						m_aMotionInfo[nCntMotion].bHoming = false;
					}
					else
					{
						m_aMotionInfo[nCntMotion].bHoming = true;
					}
				}
				if (strcmp(&aFile[0], "GRAVITY") == 0) //�d�͂�������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nGravity);
					if (nGravity == 0)
					{
						m_aMotionInfo[nCntMotion].bGravity = false;
					}
					else
					{
						m_aMotionInfo[nCntMotion].bGravity = true;
					}
				}
				if (strcmp(&aFile[0], "UPDN") == 0) //�㉺�ɂǂ�������
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nUpdn);
					switch (nUpdn)
					{
					case 0:
						m_aMotionInfo[nCntMotion].MotionUpdn = CPlayer::MOTIONUPDN_NONE;
						break;
					case 1:
						m_aMotionInfo[nCntMotion].MotionUpdn = CPlayer::MOTIONUPDN_UNDER;
						break;
					case 2:
						m_aMotionInfo[nCntMotion].MotionUpdn = CPlayer::MOTIONUPDN_UPPER;
						break;
					case 3:
						m_aMotionInfo[nCntMotion].MotionUpdn = CPlayer::MOTIONUPDN_UPDN;
						break;
					default:
						break;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0) //�����L�[�����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNumKey);
				}
				if (strcmp(&aFile[0], "NON_OPE") == 0) //����s�\����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNonOpe);
				}
				if (strcmp(&aFile[0], "COMBO_TIME") == 0) //�R���{���ł���܂ł̎���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nComboTime);
				}
				if (strcmp(&aFile[0], "NO_DAMAGE") == 0) //���G����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].nNoDmg);
				}
				if (strcmp(&aFile[0], "NO_ATTACK") == 0) //�U�����Ȃ����[�V����
				{
					m_aMotionInfo[nCntMotion].Damage[0].nStartTime = 1;
					m_aMotionInfo[nCntMotion].Damage[0].nFinishTime = 0;
				}
				if (strcmp(&aFile[0], "KEYSET") == 0)	//�L�[�ݒ�J�n
				{
					bKeySet = true;
					m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove = 0.0f;
					m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fHeight = 0.0f;
					nCntParts = 0;
				}
				if (strcmp(&aFile[0], "END_KEYSET") == 0)	//�L�[�ݒ�I��
				{
					bKeySet = false;
					nCntKey++;
				}
				if (strcmp(&aFile[0], "ORBITSET") == 0)	//�O�Րݒ�J�n
				{
					bOrbitSet = true;
					nCntObt = 0;
				}
				if (strcmp(&aFile[0], "END_ORBITSET") == 0)	//�O�Րݒ�I��
				{
					bOrbitSet = false;
					m_aMotionInfo[nCntMotion].nNumOrbit = nCntObt;
				}
				if (bColSet == true) //COLLISIONSET��
				{
					if (strcmp(&aFile[0], "COLLISION") == 0)	//�����蔻��ݒ�J�n
					{
						bCol = true;
					}
					if (strcmp(&aFile[0], "END_COLLISION") == 0)	//�����蔻��ݒ�I��
					{
						bCol = false;
						nCntCol++;
					}
					if (bCol == true)
					{
						if (strcmp(&aFile[0], "COL") == 0) //�����蔻��i�e�̃C���f�b�N�X�A�ꏊ�A�傫���j
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%d %f %f %f %f", &m_aMotionInfo[nCntMotion].Collision[nCntCol].nIdxModelParent, &m_aMotionInfo[nCntMotion].Collision[nCntCol].pos.x,
								&m_aMotionInfo[nCntMotion].Collision[nCntCol].pos.y, &m_aMotionInfo[nCntMotion].Collision[nCntCol].pos.z, &m_aMotionInfo[nCntMotion].Collision[nCntCol].fRadius);
						}
					}
				}
				if (bOrbitSet == true)
				{
					if (strcmp(&aFile[0], "ORBIT") == 0)	//�O�Րݒ�J�n
					{
						bOrbit = true;
					}
					if (strcmp(&aFile[0], "END_ORBIT") == 0)	//�O�Րݒ�I��
					{
						bOrbit = false;
						nCntObt++;
					}
					if (bOrbit == true)
					{
						if (strcmp(&aFile[0], "OBT") == 0) //�O�Ձi�e�̃C���f�b�N�X�A�ꏊ�A�\�����ԁA�������ԁj
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%d %f %f %f %f %d %d", &m_aMotionInfo[nCntMotion].Orbit[nCntObt].nIdxParent, &m_aMotionInfo[nCntMotion].Orbit[nCntObt].pos.x,
								&m_aMotionInfo[nCntMotion].Orbit[nCntObt].pos.y, &m_aMotionInfo[nCntMotion].Orbit[nCntObt].pos.z,
								&m_aMotionInfo[nCntMotion].Orbit[nCntObt].fDis, &m_aMotionInfo[nCntMotion].Orbit[nCntObt].nStartTime, &m_aMotionInfo[nCntMotion].Orbit[nCntObt].nFinishTime);
						}
						if (strcmp(&aFile[0], "COL1") == 0) //�F��[
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f %f", &m_aMotionInfo[nCntMotion].Orbit[nCntObt].col1.r, &m_aMotionInfo[nCntMotion].Orbit[nCntObt].col1.g,
								&m_aMotionInfo[nCntMotion].Orbit[nCntObt].col1.b, &m_aMotionInfo[nCntMotion].Orbit[nCntObt].col1.a);
						}
						if (strcmp(&aFile[0], "COL2") == 0) //�F���{
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f %f", &m_aMotionInfo[nCntMotion].Orbit[nCntObt].col2.r, &m_aMotionInfo[nCntMotion].Orbit[nCntObt].col2.g,
								&m_aMotionInfo[nCntMotion].Orbit[nCntObt].col2.b, &m_aMotionInfo[nCntMotion].Orbit[nCntObt].col2.a);
						}
					}
				}
				if (bDmgSet == true)
				{
					if (strcmp(&aFile[0], "DAMAGE") == 0)	//�_���[�W�ݒ�J�n
					{
						bDmg = true;
					}
					if (strcmp(&aFile[0], "END_DAMAGE") == 0)	//�_���[�W�ݒ�I��
					{
						bDmg = false;
						nCntDmg++;
					}
					if (bDmg == true)
					{
						if (strcmp(&aFile[0], "DMG") == 0) //�_���[�W�i����������΂��́A����������΂��́A�_���[�W�ʁA�q�b�g�Ԋu�j
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %d %d", &m_aMotionInfo[nCntMotion].Damage[nCntDmg].fHClash, &m_aMotionInfo[nCntMotion].Damage[nCntDmg].fVClash,
								&m_aMotionInfo[nCntMotion].Damage[nCntDmg].nDamage, &m_aMotionInfo[nCntMotion].Damage[nCntDmg].nDamageTime);
						}
						if (strcmp(&aFile[0], "DMG_TIME") == 0) //�_���[�W�̎���(�n�܂�A�I���)
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%d %d", &m_aMotionInfo[nCntMotion].Damage[nCntDmg].nStartTime, &m_aMotionInfo[nCntMotion].Damage[nCntDmg].nFinishTime);
						}
					}
				}
				if (bKeySet == true) //KEYSET��
				{
					if (strcmp(&aFile[0], "FRAME") == 0) //�t���[����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "MOVE") == 0) //�ړ���(��)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove);
					}
					if (strcmp(&aFile[0], "HEIGHT") == 0) //�ړ���(�c)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].fHeight);
					}
					if (strcmp(&aFile[0], "KEY") == 0)	//�L�[�ݒ�J�n
					{
						bKey = true;
					}
					if (strcmp(&aFile[0], "END_KEY") == 0)	//�L�[�ݒ�I��
					{
						bKey = false;
						nCntParts++;
					}
					if (bKey == true) //KEY��
					{
						if (strcmp(&aFile[0], "POS") == 0) //�ꏊ
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].pos.x,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].pos.y, &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].pos.z);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //�p�x
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].rot.x,
								&m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].rot.y, &m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].rot.z);
						}
					}
				}
			}
			if (strcmp(&aFile[0], "CHARACTERSET") == 0)	//�L�����ݒ�J�n
			{
				bChara = true;
				nCntParts = 0;
			}
			if (strcmp(&aFile[0], "END_CHARACTERSET") == 0)	//�L�����ݒ�I��
			{
				bChara = false;
			}
			if (strcmp(&aFile[0], "MOTIONSET") == 0)	//���[�V�����ݒ�J�n
			{
				bMotion = true;
				m_aMotionInfo[nCntMotion].nNumOrbit = nCntObt;
				nCntKey = 0;
				nCntCol = 0;
				nCntObt = 0;
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)	//���[�V�����ݒ�I��
			{
				bMotion = false;
				nCntMotion++;
			}
			if (strcmp(&aFile[0], "COLLISIONSET") == 0)	//�����蔻��ݒ�J�n
			{
				bColSet = true;
				nCntCol = 0;
			}
			if (strcmp(&aFile[0], "END_COLLISIONSET") == 0)	//�����蔻��ݒ�I��
			{
				bColSet = false;
				m_aMotionInfo[nCntMotion].nNumCol = nCntCol;
			}
			if (strcmp(&aFile[0], "DAMAGESET") == 0)	//�_���[�W�ݒ�J�n
			{
				bDmgSet = true;
				nCntDmg = 0;
			}
			if (strcmp(&aFile[0], "END_DAMAGESET") == 0)	//�_���[�W�ݒ�I��
			{
				bDmgSet = false;
				m_aMotionInfo[nCntMotion].nNumDmg = nCntDmg;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I����1��
			{
				break;
			}
		}
		fclose(pFile);
	}
	//�uMOTIONTYPE_RETURN�v�́A�j���[�g�������[�V�����ɖ߂�ۂɌo�R���郂�[�V����
	m_aMotionInfo[MOTIONTYPE_RETURN].bLoop = false;
	m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].nFrame = 14;
	m_aMotionInfo[MOTIONTYPE_RETURN].nNumKey = 1;
	m_aMotionInfo[MOTIONTYPE_RETURN].bGravity = true;
	m_aMotionInfo[MOTIONTYPE_RETURN].bHoming = false;
	m_aMotionInfo[MOTIONTYPE_RETURN].nNoDmg = 0;
	m_aMotionInfo[MOTIONTYPE_RETURN].nComboTime = 0;
	m_aMotionInfo[MOTIONTYPE_RETURN].nNonOpe = 0;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		m_aMotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts] = m_aMotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[m_aMotionInfo[MOTIONTYPE_NEUTRAL].nNumKey - 1].aKey[nCntParts];
	}
	m_aMotionInfo[MOTIONTYPE_RETURN].Damage[0].nStartTime = 1;
	m_aMotionInfo[MOTIONTYPE_RETURN].Damage[0].nFinishTime = 0;

	//�uMOTIONTYPE_AIRRETURN�v�́A�󒆃j���[�g�������[�V�����ɖ߂�ۂɌo�R���郂�[�V����
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].bLoop = false;
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].aKeyInfo[0].nFrame = 20;
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].nNumKey = 1;
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].bGravity = true;
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].bHoming = false;
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].nNoDmg = 0;
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].nComboTime = 0;
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].nNonOpe = 0;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		m_aMotionInfo[MOTIONTYPE_AIRRETURN].aKeyInfo[0].aKey[nCntParts] = m_aMotionInfo[MOTIONTYPE_AIRNEUTRAL].aKeyInfo[m_aMotionInfo[MOTIONTYPE_NEUTRAL].nNumKey - 1].aKey[nCntParts];
	}
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].Damage[0].nStartTime = 1;
	m_aMotionInfo[MOTIONTYPE_AIRRETURN].Damage[0].nFinishTime = 0;
}

//�ړ�
bool CPlayer::Move(float fRotY)
{
	//�J�����Ɗ|�����킹�ĕ������߂�
	float fCameraRotY = m_pCamera->GetRotY();
	m_move.x += (sinf(fCameraRotY + D3DX_PI * fRotY) * m_fMove - m_move.x) * 0.1f;
	m_move.z += (cosf(fCameraRotY + D3DX_PI * fRotY) * m_fMove - m_move.z) * 0.1f;
	m_rotDesh.y = fCameraRotY + D3DX_PI * fRotY + D3DX_PI;
	if (m_rotDesh.y >= D3DX_PI)
	{
		m_rotDesh.y -= D3DX_PI * 2;
	}
	if (m_rotDesh.y < -D3DX_PI)
	{
		m_rotDesh.y += D3DX_PI * 2;
	}

	//���b�N�I�����ĂȂ�
	if (m_bRockon == false)
	{
		//�E�����Ă�
		if (0.0f < fRotY && fRotY < 1.0f)
		{
			//���X�ɉE�Ɍ���
			m_pCamera->AddRotY(0.01f);
		}
		//�������Ă�
		else if (-1.0f < fRotY && fRotY < 0.0f)
		{
			//���X�ɍ��Ɍ���
			m_pCamera->AddRotY(-0.01f);
		}
	}

	//�����ĂȂ��J�E���g���Z�b�g
	if (m_nRunStop > 0)
	{
		m_nRunStop = 0;
	}
	return true;
}

//���[�V�����̈ړ�
void CPlayer::MotionMove(float fRotY, float fMove)
{
	m_MotionMove.x -= (sinf(fRotY) * fMove + m_MotionMove.x) * 0.1f;
	m_MotionMove.z -= (cosf(fRotY) * fMove + m_MotionMove.z) * 0.1f;
	//m_MotionMove.x = -sinf(fRotY) * fMove;
	//m_MotionMove.z = -cosf(fRotY) * fMove;
}

//���[�V�����̈ړ��ʌ��炷
void CPlayer::MotionStopMove()
{
	m_MotionMove.x -= m_MotionMove.x * 0.2f;
	m_MotionMove.z -= m_MotionMove.z * 0.2f;
	//m_MotionMove.x = 0.0f;
	//m_MotionMove.z = 0.0f;
}

//���[�V������Y�ړ�
void CPlayer::MotionHeight(float fHeight)
{
	m_MotionMove.y += (fHeight - m_MotionMove.y) * 0.1f;
	//m_MotionMove.y = fHeight;
}

//���[�V������Y�ړ��ʌ��炷
void CPlayer::MotionStopHeight()
{
	m_MotionMove.y -= m_MotionMove.y * 0.2f;
	//m_MotionMove.y = 0.0f;
}

//��~
bool CPlayer::Stop()
{
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;
	return false;
}

//�W�����v
void CPlayer::Jump()
{
	if (m_bJump == true)
	{
		//�R���{�����Z�b�g�AY�ړ��ʑ����A�󒆂ɂ���悤�ɂ���A�W�����v���[�V����
		m_nCombo = 0;
		m_move.y = m_fJump;
		m_bJump = false;
		m_bLanding = false;
		m_bLandObject = false;
		MotionChange(MOTIONTYPE_JUMP);
	}
}

//�I�u�W�F�N�g�Ƃ̓����蔻��
void CPlayer::CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	pScene = GetScene(PRIORITY_OBJECT);
	bool bLand = false;
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�I�u�W�F�N�g��������
		if (pScene->GetObjType() == CScene::OBJECTTYPE_BLOCK)
		{
			//�����蔻�肪����
			if (pScene->GetCollision() == CScene::COLLISION_SPHERE)
			{
				D3DXVECTOR3 pos = pScene->GetPos();
				float fRadius = pScene->GetRadius();
				float fRotY;
				float fLengthX = pPos->x - pos.x;
				float fLengthY = (pPos->y + (m_fHeight / 2)) - pos.y;
				float fLengthZ = pPos->z - pos.z;
				fLengthX = powf(fLengthX, 2);
				fLengthY = powf(fLengthY, 2);
				fLengthZ = powf(fLengthZ, 2);
				//�����v�Z�A�Z��������
				if (fLengthX + fLengthY + fLengthZ <= powf((m_fHeight / 2) + fRadius, 2))
				{
					//�ړ�������
					fRotY = atan2f(pos.x - pPos->x, pos.z - pPos->z);
					pPos->x = pos.x - sinf(fRotY) * ((m_fHeight / 2) + fRadius);
					pPos->z = pos.z - cosf(fRotY) * ((m_fHeight / 2) + fRadius);
				}
			}

			//���󂾂�����
			if (pScene->GetCollision() == CScene::COLLISION_SQUARE)
			{
				D3DXVECTOR3 pos = pScene->GetPos();
				D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
				D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
				float fPRadius = GetRadius();
				//XZ���������Ă�
				if (pos.x + VtxMin.x <= pPos->x + fPRadius && pPos->x - fPRadius <= pos.x + VtxMax.x &&
					pos.z + VtxMin.z <= pPos->z + fPRadius && pPos->z - fPRadius <= pos.z + VtxMax.z)
				{
					//��ɏ������
					if (posOld.y >= pos.y + VtxMax.y && pPos->y <= pos.y + VtxMax.y)
					{
						//���n������
						pPos->y = pos.y + VtxMax.y;
						m_move.y = 0.0f;
						bLand = true;
						m_pShadow->MoveY(*pPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

						if (m_bLanding == false)
						{
							CSound::Play(CSound::SOUND_LABEL_LANDING);
							MotionChange(MOTIONTYPE_LANDING);
							m_bLanding = true;
						}
					}
					//�����瓖��������
					else if (posOld.y + m_fHeight <= pos.y + VtxMin.y && pPos->y + m_fHeight >= pos.y + VtxMin.y)
					{
						pPos->y = pos.y + VtxMin.y - m_fHeight;
						m_move.y = 0.0f;
					}
					//Y�������Ă�
					else if (pos.y + VtxMin.y <= pPos->y + m_fHeight && pPos->y <= pos.y + VtxMax.y)
					{
						bool bIn = false;
						//�����ɓ������Ă�
						if (pos.x + VtxMin.x <= pPos->x + fPRadius && posOld.x + fPRadius <= pos.x + VtxMin.x)
						{
							pPos->x = pos.x + VtxMin.x - fPRadius;
							bIn = true;
						}
						//�E���ɓ������Ă�
						else if (pos.x + VtxMax.x >= pPos->x - fPRadius && posOld.x - fPRadius >= pos.x + VtxMax.x)
						{
							pPos->x = pos.x + VtxMax.x + fPRadius + 0.1f;
							bIn = true;
						}
						//��O�ɓ������Ă�
						if (pos.z + VtxMin.z <= pPos->z + fPRadius && posOld.z + fPRadius <= pos.z + VtxMin.z)
						{
							pPos->z = pos.z + VtxMin.z - fPRadius;
							bIn = true;
						}
						//���ɓ������Ă�
						else if (pos.z + VtxMax.z >= pPos->z - fPRadius && posOld.z - fPRadius >= pos.z + VtxMax.z)
						{
							pPos->z = pos.z + VtxMax.z + fPRadius + 0.1f;
							bIn = true;
						}
						//�������ĂȂ�
						if (bIn == false)
						{
							float fMinDistance = 100000.0f;
							//�l�����Ƃ̋����v�Z
							float fDistance[4];
							fDistance[0] = pos.x + VtxMax.x - pPos->x;
							fDistance[1] = pos.x + VtxMin.x - pPos->x;
							fDistance[2] = pos.z + VtxMax.z - pPos->z;
							fDistance[3] = pos.z + VtxMin.z - pPos->z;
							int nCnt;
							int nDistance;
							for (nCnt = 0; nCnt < 4; nCnt++)
							{
								if (fabsf(fMinDistance) > fabsf(fDistance[nCnt]))
								{
									//��ԒZ����X�V
									fMinDistance = fDistance[nCnt];
									nDistance = nCnt;
								}
							}

							//��ԒZ�������ɂ��A�ړ�����ʒu���قȂ�
							switch (nDistance)
							{
							case 0:
								pPos->x = pos.x + VtxMax.x + fPRadius + 0.1f;
								break;
							case 1:
								pPos->x = pos.x + VtxMin.x - fPRadius;
								break;
							case 2:
								pPos->z = pos.z + VtxMax.z + fPRadius + 0.1f;
								break;
							case 3:
								pPos->z = pos.z + VtxMin.z - fPRadius;
								break;
							default:
								break;
							}
						}
					}
				}
			}
		}
		pScene = pSceneNext;
	}
	m_bLandObject = bLand;
}

//�����蔻��̏ꏊ
void CPlayer::CollisionPos(int nCntCol)
{
	D3DXMATRIX mtxTrans; //�p�[�c�p�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X

	//�����蔻��̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_MotionInfo.Collision[nCntCol].mtxWorld);

	//�����蔻��̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_MotionInfo.Collision[nCntCol].pos.x, m_MotionInfo.Collision[nCntCol].pos.y, m_MotionInfo.Collision[nCntCol].pos.z);

	D3DXMatrixMultiply(&m_MotionInfo.Collision[nCntCol].mtxWorld, &m_MotionInfo.Collision[nCntCol].mtxWorld, &mtxTrans);
	//�e�̃}�g���b�N�X�擾
	mtxParent = m_pModel[m_MotionInfo.Collision[nCntCol].nIdxModelParent]->GetMatrix();
	
	//�Z�o�����e�����蔻��̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_MotionInfo.Collision[nCntCol].mtxWorld,
		&m_MotionInfo.Collision[nCntCol].mtxWorld,
		&mtxParent);
}

//�_���[�W����̓����蔻��
bool CPlayer::CollisionDamage(D3DXVECTOR3 pos, float fRadius, float fHeight)
{
	//�U����
	if (m_bAttack == true)
	{
		int nCntCol;
		float fLengthX;		//�����蔻��ƓG��X�����̒���
		float fLengthY;		//�����蔻��ƓG��Y�����̒���
		float fLengthZ;		//�����蔻��ƓG��Z�����̒���
		float fHDistance;	//�����蔻��ƓG�̐��������̋���
		for (nCntCol = 0; nCntCol < m_MotionInfo.nNumCol; nCntCol++)
		{
			//�����蔻��̏ꏊ�v�Z
			CollisionPos(nCntCol);
			fLengthX = powf(pos.x - m_MotionInfo.Collision[nCntCol].mtxWorld._41, 2);
			fLengthY = pos.y + (fHeight / 2) - m_MotionInfo.Collision[nCntCol].mtxWorld._42;
			fLengthZ = powf(pos.z - m_MotionInfo.Collision[nCntCol].mtxWorld._43, 2);
			fHDistance = sqrtf(fLengthX + fLengthZ);
			
			//�����v�Z�A�Z��������
			if (fHDistance <= fRadius + m_MotionInfo.Collision[nCntCol].fRadius && fabsf(fLengthY) <= fHeight + m_MotionInfo.Collision[nCntCol].fRadius)
			{
				/*CParticle::Create(D3DXVECTOR3(m_MotionInfo.Collision[nCntCol].mtxWorld._41, m_MotionInfo.Collision[nCntCol].mtxWorld._42, m_MotionInfo.Collision[nCntCol].mtxWorld._43),
					D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 40, -1, D3DXVECTOR3(4.0f, 0.0f, 0.0f));*/
				//���������ԍ��L������A�����������������
				m_nCntCol = nCntCol;
				if (m_bHit == false)
				{
					m_bHit = true;
				}
				return true;
			}
		}
	}
	return false;
}

//�G�Ɠ�����
void CPlayer::CollisionEnemy(D3DXVECTOR3 *pPos)
{
	CScene *pScene;
	pScene = GetScene(PRIORITY_CHARA);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�G��������
		if (pScene->GetObjType() == CScene::OBJECTTYPE_ENEMY)
		{
			D3DXVECTOR3 pos = pScene->GetPos();
			float fRadius = pScene->GetRadius() * 0.8f;
			float fHeight = pScene->GetHeight();
			float fRotY;
			float fLengthX = pPos->x - pos.x;
			//float fLengthY = (pPos->y + (m_fHeight / 2)) - (pos.y + (fHeight / 2));
			float fLengthZ = pPos->z - pos.z;
			fLengthX = powf(fLengthX, 2);
			//fLengthY = powf(fLengthY, 2);
			fLengthZ = powf(fLengthZ, 2);
			
			//���������̋�����������Y�����������Ă�
			if (fLengthX + fLengthZ <= powf(m_fRadius * 0.8f + fRadius, 2.0f) && pos.y < pPos->y + m_fHeight && pPos->y < pos.y + fHeight)
			{
				fRotY = atan2f(pos.x - pPos->x, pos.z - pPos->z);
				pPos->x = pos.x - sinf(fRotY) * (m_fRadius * 0.8f + fRadius);
				pPos->z = pos.z - cosf(fRotY) * (m_fRadius * 0.8f + fRadius);
			}
		}
		pScene = pSceneNext;
	}
}

//�O��
void CPlayer::Orbit()
{
	int nCntObt;
	for (nCntObt = 0; nCntObt < m_MotionInfo.nNumOrbit; nCntObt++)
	{
		if (m_MotionInfo.Orbit[nCntObt].nStartTime <= m_nTotalTime && m_nTotalTime < m_MotionInfo.Orbit[nCntObt].nFinishTime)
		{
			D3DXMATRIX mtxTrans; //�p�[�c�p�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent; //�e�̃}�g���b�N�X

			//�����蔻��̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_MotionInfo.Orbit[nCntObt].TipmtxWorld);
			
			//�����蔻��̈ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, m_MotionInfo.Orbit[nCntObt].pos.x, m_MotionInfo.Orbit[nCntObt].pos.y, m_MotionInfo.Orbit[nCntObt].pos.z);
			D3DXMatrixMultiply(&m_MotionInfo.Orbit[nCntObt].TipmtxWorld, &m_MotionInfo.Orbit[nCntObt].TipmtxWorld, &mtxTrans);
			
			//�e�̃}�g���b�N�X�擾
			mtxParent = m_pModel[m_MotionInfo.Orbit[nCntObt].nIdxParent]->GetMatrix();
			
			//�Z�o�����e�O�Ղ̐�[�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(&m_MotionInfo.Orbit[nCntObt].TipmtxWorld,
				&m_MotionInfo.Orbit[nCntObt].TipmtxWorld,
				&mtxParent);
			
			m_pOrbit[nCntObt]->SetOrbit(D3DXVECTOR3(mtxParent._41, mtxParent._42, mtxParent._43),
				D3DXVECTOR3(m_MotionInfo.Orbit[nCntObt].TipmtxWorld._41, m_MotionInfo.Orbit[nCntObt].TipmtxWorld._42, m_MotionInfo.Orbit[nCntObt].TipmtxWorld._43),
				m_MotionInfo.Orbit[nCntObt].fDis, m_MotionInfo.Orbit[nCntObt].col1, m_MotionInfo.Orbit[nCntObt].col2);
		}
	}
}

//���[�V�����̓���
void CPlayer::Motion()
{
	int nCntParts;
	m_nTotalTime++;
	m_nCntMotion++;
	//�g�[�^���̃J�E���g���_���[�W����̎��Ԓ���������_���[�W����o��
	if (m_MotionInfo.Damage[m_nDmgNumNow].nStartTime <= m_nTotalTime && m_nTotalTime < m_MotionInfo.Damage[m_nDmgNumNow].nFinishTime)
	{
		m_nCntDamage++;
		if (m_bAttack == false)
		{
			m_bAttack = true;
		}
	}
	else if (m_bAttack == true)
	{
		m_bAttack = false;
	}

	//���f���̃p�[�c���Ƃɂ��
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		//�ʒu�A�����擾
		D3DXVECTOR3 posOld;
		posOld = m_pModel[nCntParts]->GetPos();
		D3DXVECTOR3 rotOld;
		rotOld = m_pModel[nCntParts]->GetRot();
		
		//���������߂�(�Ή�����L�[�̊e�p�[�c��pos(rot) - ���̊e�p�[�c��pos(rot))
		if (m_nCntMotion == 1)
		{
			m_aKeyDiff[nCntParts].pos.x = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].pos.x - posOld.x;
			m_aKeyDiff[nCntParts].pos.y = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].pos.y - posOld.y;
			m_aKeyDiff[nCntParts].pos.z = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].pos.z - posOld.z;
			m_aKeyDiff[nCntParts].rot.x = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].rot.x - rotOld.x;
			if (m_aKeyDiff[nCntParts].rot.x < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.x += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].rot.x > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.x -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].rot.y = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].rot.y - rotOld.y;
			if (m_aKeyDiff[nCntParts].rot.y < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.y += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].rot.y > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.y -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].rot.z = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].rot.z - rotOld.z;
			if (m_aKeyDiff[nCntParts].rot.z < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.z += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].rot.z > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.z -= D3DX_PI * 2;
			}
		}
		//�������t���[�����Ŋ���A���̕����Z����
		posOld.x += m_aKeyDiff[nCntParts].pos.x / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.y += m_aKeyDiff[nCntParts].pos.y / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.z += m_aKeyDiff[nCntParts].pos.z / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		m_pModel[nCntParts]->SetPos(posOld);

		rotOld.x += m_aKeyDiff[nCntParts].rot.x / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		rotOld.y += m_aKeyDiff[nCntParts].rot.y / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		rotOld.z += m_aKeyDiff[nCntParts].rot.z / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		m_pModel[nCntParts]->SetRot(rotOld);
	}

	//���̃L�[�̃��[�V�����J�E���g�����ɒB������
	if (m_nCntMotion == m_MotionInfo.aKeyInfo[m_nKey].nFrame)
	{
		//���[�V�����J�E���g���Z�b�g�A�L�[���Z
		m_nCntMotion = 0;
		m_nKey++;
		//�L�[�����ɒB������
		if (m_nKey == m_MotionInfo.nNumKey)
		{
			//���[�v���Ȃ�
			if (m_MotionInfo.bLoop == false)
			{
				//���n���Ă�
				if (m_bJump == true)
				{
					//�߂����[�V��������Ȃ�
					if (m_motionType != MOTIONTYPE_RETURN)
					{
						//�߂�
						MotionChange(MOTIONTYPE_RETURN);
					}
					else
					{
						//�j���[�g�������[�V����
						MotionChange(MOTIONTYPE_NEUTRAL);
						m_nCombo = 0;
					}
				}
				//�󒆂ɂ���
				else
				{
					//�󒆂̖߂����[�V��������Ȃ�
					if (m_motionType != MOTIONTYPE_AIRRETURN)
					{
						//�󒆂̖߂����[�V����
						MotionChange(MOTIONTYPE_AIRRETURN);
					}
					else
					{
						//�󒆃j���[�g����
						MotionChange(MOTIONTYPE_AIRNEUTRAL);
						m_nCombo = 0;
					}
				}
			}
			m_nKey = 0;
		}
	}

	//�_���[�W���蒆�̃J�E���g���q�b�g�Ԋu�ɒB������A�G�ɓ��Ă��������Z�b�g����A�J�E���g���Z�b�g
	if (m_nCntDamage > m_MotionInfo.Damage[m_nDmgNumNow].nDamageTime)
	{
		ResetEnemy();
		m_nCntDamage = 0;
	}

	//���[�V�����̊e�_���[�W���ԂɒB������A�G�ɓ��Ă��������Z�b�g����A
	if (m_nTotalTime >= m_MotionInfo.Damage[m_nDmgNumNow].nFinishTime)
	{
		ResetEnemy();

		//���̃_���[�W������Q�Ƃ���
		m_nCntDamage = 0;
		if (m_nDmgNumNow < 7)
		{
			m_nDmgNumNow++;
		}
		else
		{
			m_nDmgNumNow = 0;
		}
	}
}

//���[�V�����̓���(����)
void CPlayer::HasteMotion()
{
	int nCntParts;
	//2�{���̂��߁A2�����₷
	m_nTotalTime += 2;
	m_nCntMotion += 2;
	for (nCntParts = 0; nCntParts < m_nNumModel; nCntParts++)
	{
		//���������߂�(�Ή�����L�[�̊e�p�[�c��pos(rot) - ���̊e�p�[�c��pos(rot))
		if (m_nCntMotion == 2)
		{
			m_aKeyDiff[nCntParts].pos.x = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].pos.x - m_pModel[nCntParts]->GetPos().x;
			m_aKeyDiff[nCntParts].pos.y = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].pos.y - m_pModel[nCntParts]->GetPos().y;
			m_aKeyDiff[nCntParts].pos.z = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].pos.z - m_pModel[nCntParts]->GetPos().z;
			m_aKeyDiff[nCntParts].rot.x = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].rot.x - m_pModel[nCntParts]->GetRot().x;
			if (m_aKeyDiff[nCntParts].rot.x < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.x += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].rot.x > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.x -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].rot.y = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].rot.y - m_pModel[nCntParts]->GetRot().y;
			if (m_aKeyDiff[nCntParts].rot.y < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.y += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].rot.y > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.y -= D3DX_PI * 2;
			}
			m_aKeyDiff[nCntParts].rot.z = m_MotionInfo.aKeyInfo[m_nKey].aKey[nCntParts].rot.z - m_pModel[nCntParts]->GetRot().z;
			if (m_aKeyDiff[nCntParts].rot.z < -D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.z += D3DX_PI * 2;
			}
			else if (m_aKeyDiff[nCntParts].rot.z > D3DX_PI)
			{
				m_aKeyDiff[nCntParts].rot.z -= D3DX_PI * 2;
			}
		}
		//�ʒu�A�����ɉ��Z
		D3DXVECTOR3 posOld;
		posOld = m_pModel[nCntParts]->GetPos();
		posOld.x += m_aKeyDiff[nCntParts].pos.x / (m_MotionInfo.aKeyInfo[m_nKey].nFrame / 2);
		posOld.y += m_aKeyDiff[nCntParts].pos.y / (m_MotionInfo.aKeyInfo[m_nKey].nFrame / 2);
		posOld.z += m_aKeyDiff[nCntParts].pos.z / (m_MotionInfo.aKeyInfo[m_nKey].nFrame / 2);
		m_pModel[nCntParts]->SetPos(posOld);

		D3DXVECTOR3 rotOld;
		rotOld = m_pModel[nCntParts]->GetRot();
		rotOld.x += m_aKeyDiff[nCntParts].rot.x / (m_MotionInfo.aKeyInfo[m_nKey].nFrame / 2);
		rotOld.y += m_aKeyDiff[nCntParts].rot.y / (m_MotionInfo.aKeyInfo[m_nKey].nFrame / 2);
		rotOld.z += m_aKeyDiff[nCntParts].rot.z / (m_MotionInfo.aKeyInfo[m_nKey].nFrame / 2);
		m_pModel[nCntParts]->SetRot(rotOld);
	}

	//���̃L�[�̃��[�V�����J�E���g�����ɒB������
	if (m_nCntMotion >= m_MotionInfo.aKeyInfo[m_nKey].nFrame)
	{
		//���[�V�����J�E���g���Z�b�g�A�L�[���Z
		m_nCntMotion = 0;
		m_nKey++;
		//�L�[�����ɒB������
		if (m_nKey == m_MotionInfo.nNumKey)
		{
			//���[�v���Ȃ�
			if (m_MotionInfo.bLoop == false)
			{
				//�߂����[�V��������Ȃ�
				if (m_motionType != MOTIONTYPE_RETURN)
				{
					//�߂�
					MotionChange(MOTIONTYPE_RETURN);
				}
				else
				{
					//�j���[�g�������[�V����
					MotionChange(MOTIONTYPE_NEUTRAL);
				}
			}
			m_nKey = 0;
		}
	}
}

//���[�V�����ύX
void CPlayer::MotionChange(MOTIONTYPE motionType)
{
	//�ύX��ɍ��킹��
	m_motionTypeOld = m_motionType;
	m_motionType = motionType;
	m_MotionInfo = m_aMotionInfo[motionType];

	//���Z�b�g
	m_nCntMotion = 0;
	m_nTotalTime = 0;
	m_nKey = 0;
	ResetEnemy();
	m_nCntDamage = 0;
	m_nDmgNumNow = 0;

	//�߂����[�V��������Ȃ�
	if (motionType != MOTIONTYPE_RETURN && motionType != MOTIONTYPE_AIRRETURN)
	{
		//���l���킹��
		m_nComboTime = m_MotionInfo.nComboTime;
		m_nNonOpe = m_MotionInfo.nNonOpe;
	}

	m_nCntNoDmg = m_MotionInfo.nNoDmg;
	m_bHit = false;

	//�J�E���^�[�\��������A���Z�b�g����UI����
	if (m_bCounter == true)
	{
		m_bCounter = false;
		m_pCounterUI->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

//���Ƃ̓����蔻��
bool CPlayer::CollisionLand(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene)
{
	D3DXVECTOR3 pos = pScene->GetPos();
	D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
	D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
	D3DXVECTOR3 aPoint[4];
	D3DXVECTOR3 rot = pScene->GetRot();

	//4���_�擾
	aPoint[0] = D3DXVECTOR3(pos.x + VtxMin.x * cosf(-rot.y), pos.y + VtxMax.y, pos.z + VtxMax.z * cosf(-rot.y));
	aPoint[1] = D3DXVECTOR3(pos.x + VtxMax.x * cosf(-rot.y), pos.y + VtxMin.y, pos.z + VtxMax.z * cosf(-rot.y));
	aPoint[2] = D3DXVECTOR3(pos.x + VtxMin.x * cosf(-rot.y), pos.y + VtxMax.y, pos.z + VtxMin.z * cosf(-rot.y));
	aPoint[3] = D3DXVECTOR3(pos.x + VtxMax.x * cosf(-rot.y), pos.y + VtxMin.y, pos.z + VtxMin.z * cosf(-rot.y));

	D3DXVECTOR3 Cross[3];
	D3DXVec3Cross(&Cross[0], &(aPoint[2] - aPoint[1]), &(aPoint[1] - aPoint[0]));
	float fLength = powf((Cross[0].x * Cross[0].x) + (Cross[0].y * Cross[0].y) + (Cross[0].z * Cross[0].z), 0.5f);
	Cross[0].x /= fLength;
	Cross[0].y /= fLength;
	Cross[0].z /= fLength; //�����܂Ŗ@���x�N�g��

	Cross[1] = *pPos - aPoint[0]; //�v���C���[��pos�ƕǂ̔C�ӂ̓_�̃x�N�g��
	Cross[2] = posOld - aPoint[0]; //�v���C���[��Oldpos�ƕǂ̔C�ӂ̓_�̃x�N�g��

	float fDistance = Cross[0].x * Cross[1].x + Cross[0].y * Cross[1].y + Cross[0].z * Cross[1].z; //�ʂƂ̋��� �}�C�i�X�̎��A�\���ɂ���
	float fOldDistance = Cross[0].x * Cross[2].x + Cross[0].y * Cross[2].y + Cross[0].z * Cross[2].z; //�ʂƂ̋����@�}�C�i�X�̎��A�\���ɂ���
	D3DXVECTOR3 Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fDistance), pPos->y - (Cross[0].y * fDistance), pPos->z - (Cross[0].z * fDistance)); //�ǖʏ�̃v���C���[�̈ʒu
	D3DXVECTOR3 OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fOldDistance), posOld.y - (Cross[0].y * fOldDistance), posOld.z - (Cross[0].z * fOldDistance)); //�ǖʏ��1�t���[���O�̃v���C���[�̈ʒu
	//X�������Ă�
	if ((aPoint[0].x < Point.x + m_fRadius && Point.x - m_fRadius < aPoint[1].x || aPoint[1].x < Point.x + m_fRadius && Point.x - m_fRadius < aPoint[0].x) ||
		(aPoint[0].x < OldPoint.x + m_fRadius && OldPoint.x - m_fRadius < aPoint[1].x || aPoint[1].x < OldPoint.x + m_fRadius && OldPoint.x - m_fRadius < aPoint[0].x))
	{
		//Z�������Ă�
		if ((aPoint[0].z < Point.z + m_fRadius && Point.z - m_fRadius < aPoint[2].z || aPoint[2].z < Point.z + m_fRadius && Point.z - m_fRadius < aPoint[0].z) ||
			(aPoint[0].z < OldPoint.z + m_fRadius && OldPoint.z - m_fRadius < aPoint[2].z || aPoint[2].z < OldPoint.z + m_fRadius && OldPoint.z - m_fRadius < aPoint[0].z))
		{
			//���ʏ�Ƃ̋������Z��
			if (fOldDistance - 3.0f <= 0.0f && fDistance + 3.0f >= 0.0f)
			{
				//���n������
				pPos->y += fDistance;
				m_pShadow->MoveY(*pPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_move.y = 0.0f;
				if (m_bLanding == false && m_motionType != MOTIONTYPE_DIVE)
				{
					CSound::Play(CSound::SOUND_LABEL_LANDING);
					MotionChange(MOTIONTYPE_LANDING);
				}
				return true;
			}
		}
	}
	return false;
}

//�ǂƂ̓����蔻��
void CPlayer::CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene)
{
	D3DXVECTOR3 rot = pScene->GetRot();
	D3DXVECTOR3 aPoint[4]; //�ǂ�4���_
	D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
	D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
	D3DXVECTOR3 pos = pScene->GetPos();

	//�ǂ�4���_�擾
	aPoint[0] = D3DXVECTOR3(pos.x + VtxMin.x * cosf(-rot.y), pos.y + VtxMax.y, pos.z + VtxMin.x * sinf(-rot.y));
	aPoint[1] = D3DXVECTOR3(pos.x + VtxMax.x * cosf(-rot.y), pos.y + VtxMax.y, pos.z + VtxMax.x * sinf(-rot.y));
	aPoint[2] = D3DXVECTOR3(pos.x + VtxMin.x * cosf(-rot.y), pos.y + VtxMin.y, pos.z + VtxMin.x * sinf(-rot.y));
	aPoint[3] = D3DXVECTOR3(pos.x + VtxMax.x * cosf(-rot.y), pos.y + VtxMin.y, pos.z + VtxMax.x * sinf(-rot.y));

	D3DXVECTOR3 Cross[3];
	D3DXVec3Cross(&Cross[0], &(aPoint[2] - aPoint[1]), &(aPoint[1] - aPoint[0]));
	float fLength = powf((Cross[0].x * Cross[0].x) + (Cross[0].y * Cross[0].y) + (Cross[0].z * Cross[0].z), 0.5f);
	Cross[0].x /= fLength;
	Cross[0].y /= fLength;
	Cross[0].z /= fLength; //�����܂Ŗ@���x�N�g��
			
	Cross[1] = *pPos - aPoint[0]; //�v���C���[��pos�ƕǂ̔C�ӂ̓_�̃x�N�g��
	Cross[2] = posOld - aPoint[0]; //�v���C���[��Oldpos�ƕǂ̔C�ӂ̓_�̃x�N�g��

	float fDistance = Cross[0].x * Cross[1].x + Cross[0].y * Cross[1].y + Cross[0].z * Cross[1].z; //�ǖʂƂ̋��� �}�C�i�X�̎��A�\���ɂ���
	float fOldDistance = Cross[0].x * Cross[2].x + Cross[0].y * Cross[2].y + Cross[0].z * Cross[2].z; //�ǖʂƂ̋����@�}�C�i�X�̎��A�\���ɂ���
	D3DXVECTOR3 Point = D3DXVECTOR3(pPos->x - (Cross[0].x * fDistance), pPos->y - (Cross[0].y * fDistance), pPos->z - (Cross[0].z * fDistance)); //�ǖʏ�̃v���C���[�̈ʒu
	D3DXVECTOR3 OldPoint = D3DXVECTOR3(posOld.x - (Cross[0].x * fOldDistance), posOld.y - (Cross[0].y * fOldDistance), posOld.z - (Cross[0].z * fOldDistance)); //�ǖʏ��1�t���[���O�̃v���C���[�̈ʒu

	/*D3DXVECTOR3 SubVector[12];
	SubVector[0] = D3DXVECTOR3(aPoint[1].x - aPoint[0].x, aPoint[1].y - aPoint[0].y, aPoint[1].z - aPoint[0].z);
	SubVector[1] = D3DXVECTOR3(aPoint[0].x - Point.x, aPoint[0].y - Point.y, aPoint[0].z - Point.z);
	SubVector[2] = D3DXVECTOR3(aPoint[0].x - OldPoint.x, aPoint[0].y - OldPoint.y, aPoint[0].z - OldPoint.z);
	SubVector[3] = D3DXVECTOR3(aPoint[3].x - aPoint[1].x, aPoint[3].y - aPoint[1].y, aPoint[3].z - aPoint[1].z);
	SubVector[4] = D3DXVECTOR3(aPoint[1].x - Point.x, aPoint[1].y - Point.y, aPoint[1].z - Point.z);
	SubVector[5] = D3DXVECTOR3(aPoint[1].x - OldPoint.x, aPoint[1].y - OldPoint.y, aPoint[1].z - OldPoint.z);
	SubVector[6] = D3DXVECTOR3(aPoint[2].x - aPoint[3].x, aPoint[2].y - aPoint[3].y, aPoint[2].z - aPoint[3].z);
	SubVector[7] = D3DXVECTOR3(aPoint[3].x - Point.x, aPoint[3].y - Point.y, aPoint[3].z - Point.z);
	SubVector[8] = D3DXVECTOR3(aPoint[3].x - OldPoint.x, aPoint[3].y - OldPoint.y, aPoint[3].z - OldPoint.z);
	SubVector[9] = D3DXVECTOR3(aPoint[0].x - aPoint[2].x, aPoint[0].y - aPoint[2].y, aPoint[0].z - aPoint[2].z);
	SubVector[10] = D3DXVECTOR3(aPoint[2].x - Point.x, aPoint[2].y - Point.y, aPoint[2].z - Point.z);
	SubVector[11] = D3DXVECTOR3(aPoint[2].x - OldPoint.x, aPoint[2].y - OldPoint.y, aPoint[2].z - OldPoint.z);

	D3DXVECTOR3 CrossVector[8];
	CrossVector[0] = D3DXVECTOR3(SubVector[0].y * SubVector[1].z - SubVector[1].y * SubVector[0].z, SubVector[0].z * SubVector[1].x - SubVector[1].z * SubVector[0].x, SubVector[0].x * SubVector[1].y - SubVector[1].x * SubVector[0].y);
	CrossVector[1] = D3DXVECTOR3(SubVector[0].y * SubVector[2].z - SubVector[2].y * SubVector[0].z, SubVector[0].z * SubVector[2].x - SubVector[2].z * SubVector[0].x, SubVector[0].x * SubVector[2].y - SubVector[2].x * SubVector[0].y);
	CrossVector[2] = D3DXVECTOR3(SubVector[3].y * SubVector[4].z - SubVector[4].y * SubVector[3].z, SubVector[3].z * SubVector[4].x - SubVector[4].z * SubVector[3].x, SubVector[3].x * SubVector[4].y - SubVector[4].x * SubVector[3].y);
	CrossVector[3] = D3DXVECTOR3(SubVector[3].y * SubVector[5].z - SubVector[5].y * SubVector[3].z, SubVector[3].z * SubVector[5].x - SubVector[5].z * SubVector[3].x, SubVector[3].x * SubVector[5].y - SubVector[5].x * SubVector[3].y);
	CrossVector[4] = D3DXVECTOR3(SubVector[6].y * SubVector[7].z - SubVector[7].y * SubVector[6].z, SubVector[6].z * SubVector[7].x - SubVector[7].z * SubVector[6].x, SubVector[6].x * SubVector[7].y - SubVector[7].x * SubVector[6].y);
	CrossVector[5] = D3DXVECTOR3(SubVector[6].y * SubVector[8].z - SubVector[8].y * SubVector[6].z, SubVector[6].z * SubVector[8].x - SubVector[8].z * SubVector[6].x, SubVector[6].x * SubVector[8].y - SubVector[8].x * SubVector[6].y);
	CrossVector[6] = D3DXVECTOR3(SubVector[9].y * SubVector[10].z - SubVector[10].y * SubVector[9].z, SubVector[9].z * SubVector[10].x - SubVector[10].z * SubVector[9].x, SubVector[9].x * SubVector[10].y - SubVector[10].x * SubVector[9].y);
	CrossVector[7] = D3DXVECTOR3(SubVector[9].y * SubVector[11].z - SubVector[11].y * SubVector[9].z, SubVector[9].z * SubVector[11].x - SubVector[11].z * SubVector[9].x, SubVector[9].x * SubVector[11].y - SubVector[11].x * SubVector[9].y);
	
	float fDot[8];
	fDot[0] = CrossVector[0].x * CrossVector[2].x + CrossVector[0].y * CrossVector[2].y + CrossVector[0].z * CrossVector[2].z;
	fDot[1] = CrossVector[2].x * CrossVector[4].x + CrossVector[2].y * CrossVector[4].y + CrossVector[2].z * CrossVector[4].z;
	fDot[2] = CrossVector[4].x * CrossVector[6].x + CrossVector[4].y * CrossVector[6].y + CrossVector[4].z * CrossVector[6].z;
	fDot[3] = CrossVector[6].x * CrossVector[0].x + CrossVector[6].y * CrossVector[0].y + CrossVector[6].z * CrossVector[0].z;
	fDot[4] = CrossVector[0].x * CrossVector[1].x + CrossVector[0].y * CrossVector[1].y + CrossVector[0].z * CrossVector[1].z;
	fDot[5] = CrossVector[2].x * CrossVector[3].x + CrossVector[2].y * CrossVector[3].y + CrossVector[2].z * CrossVector[3].z;
	fDot[6] = CrossVector[4].x * CrossVector[5].x + CrossVector[4].y * CrossVector[5].y + CrossVector[4].z * CrossVector[5].z;
	fDot[7] = CrossVector[6].x * CrossVector[7].x + CrossVector[6].y * CrossVector[7].y + CrossVector[6].z * CrossVector[7].z;
	if (fDot[0] > 0.0f && fDot[1] > 0.0f && fDot[2] > 0.0f && fDot[3] > 0.0f || fDot[4] > 0.0f && fDot[5] > 0.0f && fDot[6] > 0.0f && fDot[7] > 0.0f)
	{
		if (fabsf(fDistance) <= m_fRadius || fOldDistance <= -m_fRadius && fDistance >= -m_fRadius)
		{
			pPos->x -= sinf(rot.y) * (m_fRadius + fDistance);
			pPos->z -= cosf(rot.y) * (m_fRadius + fDistance);
		}
	}
	*/

	//Y�������Ă�
	if (aPoint[2].y < Point.y + m_fHeight && Point.y < aPoint[0].y || aPoint[2].y < OldPoint.y + m_fHeight && OldPoint.y < aPoint[0].y)
	{
		//X�������Ă�
		if ((aPoint[0].x < Point.x + m_fRadius && Point.x - m_fRadius < aPoint[1].x || aPoint[1].x < Point.x + m_fRadius && Point.x - m_fRadius < aPoint[0].x) ||
			(aPoint[0].x < OldPoint.x + m_fRadius && OldPoint.x - m_fRadius < aPoint[1].x || aPoint[1].x < OldPoint.x + m_fRadius && OldPoint.x - m_fRadius < aPoint[0].x))
		{
			//Z�������Ă�
			if ((aPoint[0].z < Point.z + m_fRadius && Point.z - m_fRadius < aPoint[1].z || aPoint[1].z < Point.z + m_fRadius && Point.z - m_fRadius < aPoint[0].z) ||
				(aPoint[0].z < OldPoint.z + m_fRadius && OldPoint.z - m_fRadius < aPoint[1].z || aPoint[1].z < OldPoint.z + m_fRadius && OldPoint.z - m_fRadius < aPoint[0].z))
			{
				//�������Z��
				if (fabsf(fDistance) <= m_fRadius || fOldDistance <= -m_fRadius && fDistance >= -m_fRadius)
				{
					//�ǂɓ�����Ȃ��悤�ړ�������
					pPos->x -= sinf(rot.y) * (m_fRadius + fDistance);
					pPos->z -= cosf(rot.y) * (m_fRadius + fDistance);
				}
			}
		}
	}
}

//���ʂƂ̓����蔻��
void CPlayer::CollisionPlane(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	pScene = CScene::GetScene(CScene::PRIORITY_PLANE);
	CScene *pSceneNext;
	bool bLand = false;
	while (pScene)
	{
		pSceneNext = pScene->GetNext();
		//�ǂ̏ꍇ�A�ǂ̓����蔻�������
		if (pScene->GetObjType() == CScene::OBJECTTYPE_WALL)
		{
			CollisionWall(pPos, posOld, pScene);
		}
		//���̏ꍇ���܂����n���ĂȂ��ꍇ�A���̓����蔻�������
		else if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD && bLand == false)
		{
			bLand = CollisionLand(pPos, posOld, pScene);
		}
		pScene = pSceneNext;
	}
	m_bJump = bLand;
	m_bLanding = bLand;
}

//�󒆂ɋ���Ƃ��̉e�̈ʒu
void CPlayer::UnderSearch(D3DXVECTOR3 pos)
{
	CScene *pScene;
	int nCntScene;
	bool bUnder = false;
	bool bObject = false;
	float fUnderPosY = -100000.0f;
	float fFieldY;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 UnderRot;
	for (nCntScene = 0; nCntScene < PRIORITY_MAX; nCntScene++)
	{
		pScene = GetScene((CScene::PRIORITY)nCntScene);
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->GetNext();
			//�����I�u�W�F�N�g��������
			if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD || pScene->GetObjType() == CScene::OBJECTTYPE_BLOCK)
			{
				D3DXVECTOR3 Scenepos = pScene->GetPos();
				D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
				D3DXVECTOR3 VtxMin = pScene->GetVtxMin();

				//XZ�Ƃ��ɓ������Ă�
				if (pos.x - GetRadius() < Scenepos.x + VtxMax.x && Scenepos.x + VtxMin.x < pos.x + GetRadius() &&
					pos.z - GetRadius() < Scenepos.z + VtxMax.z && Scenepos.z + VtxMin.z < pos.z + GetRadius())
				{
					//����������
					if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD)
					{
						//����4���_�擾
						D3DXVECTOR3 VtxPos[4];

						//X�����ɌX���Ȃ�
						if (pScene->GetRotX() == false)
						{
							VtxPos[0] = D3DXVECTOR3(VtxMin.x, VtxMax.y, VtxMax.z);
							VtxPos[1] = D3DXVECTOR3(VtxMax.x, VtxMax.y, VtxMax.z);
							VtxPos[2] = D3DXVECTOR3(VtxMin.x, VtxMin.y, VtxMin.z);
							VtxPos[3] = D3DXVECTOR3(VtxMax.x, VtxMin.y, VtxMin.z);
						}
						else
						{
							VtxPos[0] = D3DXVECTOR3(VtxMin.x, VtxMax.y, VtxMax.z);
							VtxPos[1] = D3DXVECTOR3(VtxMax.x, VtxMin.y, VtxMax.z);
							VtxPos[2] = D3DXVECTOR3(VtxMin.x, VtxMax.y, VtxMin.z);
							VtxPos[3] = D3DXVECTOR3(VtxMax.x, VtxMin.y, VtxMin.z);
						}

						//XZ�̌X�����擾
						rot.x = atan2f(VtxPos[2].y - VtxPos[0].y, VtxPos[2].z - VtxPos[0].z);
						rot.z = atan2f(VtxPos[1].y - VtxPos[0].y, VtxPos[1].x - VtxPos[0].x);

						//�v���C���[�̐^���̏��̍������v�Z
						fFieldY = (pos.z - Scenepos.z) * tanf(rot.x) + (pos.x - Scenepos.x) * tanf(rot.z) + Scenepos.y;
						rot.x = D3DX_PI - rot.x;

						//�������ł��Ⴂ�ʒu�����̈ʒu��荂�����v���C���[�̈ʒu���Ⴂ
						if (fUnderPosY < fFieldY && pos.y > fFieldY)
						{
							//�ł��Ⴂ�ʒu�X�V
							fUnderPosY = fFieldY;
							bObject = false;
							bUnder = true;
							UnderRot = rot;
						}
					}
					//�I�u�W�F�N�g��������
					else
					{
						//�I�u�W�F�N�g��pos�ɍł�����Y���W�𑫂�
						fFieldY = Scenepos.y + VtxMax.y;

						//�������ł��Ⴂ�ʒu�����̈ʒu��荂�����v���C���[�̈ʒu���Ⴂ
						if (fUnderPosY < fFieldY && pos.y > fFieldY)
						{
							//�ł��Ⴂ�ʒu�X�V
							fUnderPosY = fFieldY;
							bObject = true;
							bUnder = true;
						}
					}
				}
			}
			pScene = pSceneNext;
		}
	}

	//�ł��Ⴂ�ʒu�����Ă�
	if (bUnder == true)
	{
		//�I�u�W�F�N�g��������
		if (bObject == true)
		{
			//�X���l�����Ȃ�
			m_pShadow->MoveY(D3DXVECTOR3(pos.x, fUnderPosY, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		else
		{
			//�X���l������
			m_pShadow->MoveY(D3DXVECTOR3(pos.x, fUnderPosY, pos.z), UnderRot);
		}
	}
	else
	{
		//��\��
		m_pShadow->MoveY(D3DXVECTOR3(pos.x, pos.y - 100000.0f, pos.z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}
}

//�쐬
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName)
{
	CPlayer *pPlayer;
	pPlayer = new CPlayer(PRIORITY_CHARA);
	if (pPlayer != NULL)
	{
		pPlayer->Init(pos, rot, aFileName);
	}
	return pPlayer;
}

//�_���[�W����
void CPlayer::Damage(int nDamage, D3DXVECTOR3 clash)
{
	//�̗͌��炷
	m_nHP -= nDamage;

	//���ꂽ
	if (m_nHP <= 0)
	{
		MotionChange(MOTIONTYPE_DEATH);
		m_nCntNoDmg = 1600;

		//HPUI����
		m_pHPUI->SetSize(D3DXVECTOR2(0.0f, 58.0f));
		m_pHPUI->SetPos(D3DXVECTOR3(0.0f, 620.0f, 0.0f));
		
		//�J���������Œ�
		m_pCamera->SetRockon(true);
		m_pCamera->SetPosR(D3DXVECTOR3(GetPos().x, GetPos().y + (m_fHeight * 0.3f), GetPos().z));
		m_pCamera->SetPosV(D3DXVECTOR3(GetPos().x - 180.0f * sinf(GetRot().y - 0.3f), GetPos().y + (m_fHeight * 0.8f), GetPos().z - 180.0f * cosf(GetRot().y - 0.3f)));
		
		//���b�N�I���O��
		UnRockon();

		//�����ݒ�A�I���A�Ȓ�~�A���Đ�
		m_rotDesh = GetRot();
		CManager::SetGameEnd(true);
		CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
		CSound::Play(CSound::SOUND_LABEL_PLAYERDEATH);
	}
	else
	{
		//HP�������Ă������s���`����Ȃ��Ȃ�
		if ((m_nMaxHP / 4) >= m_nHP && m_bPinch == false)
		{
			//�s���`�ɂ��ĉ��炷
			m_bPinch = true;
			m_nCntPinch = 20;
			CSound::Play(CSound::SOUND_LABEL_PINCH);
		}

		//���G�ݒ�A�m�b�N�o�b�N������AHPUI�ݒ�
		m_nCntNoDmg = 35;
		m_move = clash;
		m_pHPUI->SetSize(D3DXVECTOR2((float)m_nHP / (float)m_nMaxHP * 298.0f, 58.0f));
		m_pHPUI->SetPos(D3DXVECTOR3(1186.5f - ((float)m_nHP / (float)m_nMaxHP * 149.0f), 620.0f, 0.0f));
		CSound::Play(CSound::SOUND_LABEL_DAMAGE);
	}
}

//�G�̃��X�g�ݒ�
bool CPlayer::SetEnemy(CScene *pEnemy)
{
	int nMax = -1;
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		//���X�g���ɓ����G��������
		if (m_pEnemy[nCntEnemy] == pEnemy)
		{
			//�ݒ肵�Ȃ�
			return false;
		}
		//�܂��G�����X�g�ɓ���ĂȂ������X�g���ɋ���ۂ̂�������
		else if (nMax == -1 && m_pEnemy[nCntEnemy] == NULL)
		{
			//���X�g�̉��Ԗڂɂ���邩�ݒ�
			nMax = nCntEnemy;
		}
	}

	//���X�g�̉��Ԗڂɂ���邩�ݒ肳��Ă��邩
	if (nMax > -1)
	{
		//���X�g���ɓG�����
		m_pEnemy[nMax] = pEnemy;

		//���b�N�I�����Ă邩
		if (m_bRockon == true)
		{
			//���b�N�I�����̓G�ƃ��X�g�ɓ��ꂽ�G��������������
			if (pEnemy == m_pRockon->GetRockEnemy())
			{
				//�̗�
				int nHP = pEnemy->GetHP() - Damage();
				
				//�܂������Ă�
				if (nHP > 0)
				{
					//HPUI�ݒ�
					m_pEnemyHPUI[2]->SetSize(D3DXVECTOR2((float)nHP / (float)pEnemy->GetMaxHP() * 248.0f, 38.0f));
					m_pEnemyHPUI[2]->SetPos(D3DXVECTOR3(1221.0f - ((float)nHP / (float)pEnemy->GetMaxHP() * 124.0f), 60.0f, 0.0f));
				}
				else
				{
					//HPUI����
					int nCntUI;
					for (nCntUI = 0; nCntUI < 3; nCntUI++)
					{
						m_pEnemyHPUI[nCntUI]->FadeColorChange(0);
					}

					//���b�N�I������
					UnRockon();
				}
			}
		}
		return true;
	}
	return false;
}

//�G���X�g���Z�b�g
void CPlayer::ResetEnemy()
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < 16; nCntEnemy++)
	{
		if (m_pEnemy[nCntEnemy] != NULL)
		{
			m_pEnemy[nCntEnemy] = NULL;
		}
	}
}

//���b�N�I������
void CPlayer::Rockon()
{
	D3DXVECTOR3 CameraPos = CManager::GetRenderer()->GetCamera()->GetPosV();
	CScene *pScene;
	CScene *pRockScene = NULL;
	pScene = GetScene(PRIORITY_CHARA);
	float fMaxDistance = 100000.0f;
	bool bFront = false;
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		
		//�G��������
		if (pScene->GetObjType() == CScene::OBJECTTYPE_ENEMY)
		{
			D3DXVECTOR3 EPos = pScene->GetPos();
			float fRotY = m_pCamera->GetRotY() - atan2f(CameraPos.x - EPos.x, CameraPos.z - EPos.z);
			
			//�G�̌����ƃJ�����̌������قƂ�Ǎ����Ă�����
			if (D3DX_PI * (160.0f / 180.0f) < fabsf(fRotY))
			{
				float fLengthX = powf(CameraPos.x - EPos.x, 2.0f);
				float fLengthY = powf((CameraPos.y + m_fHeight / 2) - (EPos.y + pScene->GetHeight() / 2), 2.0f);
				float fLengthZ = powf(CameraPos.z - EPos.z, 2.0f);
				float fHDistance = powf(sqrtf(fLengthX + fLengthZ), 2.0f);
				float fDistance = sqrtf(fHDistance + fLengthY);
				
				//�ő�̋�����荡�̋����̂ق����Z���ꍇ
				if (fMaxDistance > fDistance)
				{
					fMaxDistance = fDistance;
					pRockScene = pScene;
					bFront = true;
				}
			}
			//�G�̌����ƃJ�����̌������قƂ�ǐ^�t���O�Ɍ����Ȃ��ꍇ
			else if (fabsf(fRotY) < D3DX_PI * (20.0f / 180.0f) && bFront == false)
			{
				float fLengthX = powf(CameraPos.x - EPos.x, 2.0f);
				float fLengthY = powf((CameraPos.y + m_fHeight / 2) - (EPos.y + pScene->GetHeight() / 2), 2.0f);
				float fLengthZ = powf(CameraPos.z - EPos.z, 2.0f);
				float fHDistance = powf(sqrtf(fLengthX + fLengthZ), 2.0f);
				float fDistance = sqrtf(fHDistance + fLengthY);

				//�ő�̋�����荡�̋����̂ق����Z���ꍇ
				if (fMaxDistance > fDistance)
				{
					fMaxDistance = fDistance;
					pRockScene = pScene;
				}
			}
		}
		pScene = pSceneNext;
	}

	//���b�N�I������G������ꍇ
	if (pRockScene != NULL)
	{
		//���b�N�I���J�n
		CSound::Play(CSound::SOUND_LABEL_SELECT);
		m_bRockon = true;
		m_pCamera->SetRockon(true);
		m_pRockon->SetRockon(pRockScene);

		//�G��HPUI�`��
		m_pEnemyHPUI[0]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_pEnemyHPUI[1]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		m_pEnemyHPUI[2]->FadeColorChange(255);
		m_pEnemyHPUI[2]->SetSize(D3DXVECTOR2((float)pRockScene->GetHP() / (float)pRockScene->GetMaxHP() * 248.0f, 38.0f));
		m_pEnemyHPUI[2]->SetPos(D3DXVECTOR3(1221.0f - ((float)pRockScene->GetHP() / (float)pRockScene->GetMaxHP() * 124.0f), 60.0f, 0.0f));
	}
}

//���b�N�I������
void CPlayer::UnRockon()
{
	m_bRockon = false;
	m_pCamera->SetRockon(false);
	m_pRockon->RemoveRockon();

	//�G��HPUI����
	m_pEnemyHPUI[0]->ColorChange(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
	m_pEnemyHPUI[1]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_pEnemyHPUI[2]->FadeColorChange(0);
}

//���b�N�I�����̃J�����ړ�
void CPlayer::RockCameraMove(D3DXVECTOR3 pos)
{
	//���b�N�I��UI�̏ꏊ�擾
	D3DXVECTOR3 RockPos = m_pRockon->GetPos();
	if (m_pRockon->GetRockon() == false)
	{
		//�G�̕�������
		D3DXVECTOR3 EPos = m_pRockon->GetRockEnemy()->GetPos();
		float fRotY = atan2f(pos.x - EPos.x, pos.z - EPos.z) + D3DX_PI;
		m_pCamera->SetRotDeshY(fRotY);
	}
	else
	{
		//���̉�ʒ[�ɍs��
		if (RockPos.x <= 50.0f || SCREEN_WIDTH - 50.0f <= RockPos.x)
		{
			//�G�̕�������
			D3DXVECTOR3 EPos = m_pRockon->GetRockEnemy()->GetPos();
			float fRotY = atan2f(pos.x - EPos.x, pos.z - EPos.z) + D3DX_PI;
			m_pCamera->SetRotDeshY(fRotY);
		}
		//�c�̉�ʒ[�ɍs��
		if (RockPos.y <= 50.0f || SCREEN_HEIGHT - 50.0f <= RockPos.y)
		{
			//�G�̕�������
			if (RockPos.y <= 50.0f)
			{
				m_pCamera->AddRotX(0.005f);
			}
			else if (SCREEN_HEIGHT - 50.0f <= RockPos.y)
			{
				m_pCamera->AddRotX(-0.01f);
			}
		}
	}
}

//���b�N�I�����̍U��
CPlayer::MOTIONTYPE CPlayer::RockAttack(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 Epos = m_pRockon->GetRockEnemy()->GetPos(); //�G�̏ꏊ
	float fRotY = atan2f(pos.x - Epos.x, pos.z - Epos.z);
	m_rotDesh.y = fRotY;
	SetRot(D3DXVECTOR3(0.0f, fRotY, 0.0f));

	//�J�E���^�[�\
	if (m_bCounter == true)
	{
		//�J�E���^�[����
		m_nCombo = 1;
		return MOTIONTYPE_COUNTER;
	}

	//�R���{��3�i��
	if (m_nCombo >= 2)
	{
		//�t�B�j�b�V������
		m_nCombo = 0;
		return MOTIONTYPE_FINISH;
	}

	//�R���{����
	m_nCombo++;
	if (Epos.y - pos.y > 140.0f) //�G���������ǂꂾ�������ʒu�ɂ��邩
	{
		return MOTIONTYPE_ARIAL;
	}
	else if (Epos.y - pos.y < -140.0f) //�G���������ǂꂾ���Ⴂ�ʒu�ɂ��邩
	{
		return MOTIONTYPE_DIVE;
	}
	else if (sqrtf(powf(Epos.x - pos.x, 2.0f) + powf(Epos.z - pos.z, 2.0f)) > 220.0f || 
		     m_motionType == MOTIONTYPE_SLAP || m_motionTypeOld == MOTIONTYPE_SLAP) //�G�Ǝ����Ƃ̋������������A�܂��͒��O�̍U�������ߋ����̂��������
	{
		return MOTIONTYPE_RUSH;
	}
	else if (AroundEnemy(pos) == true) //�����̎���ɓG�����邩
	{
		return MOTIONTYPE_ROUND;
	}
	else //��L�����ɊY�������i�G���ߋ�����1�̂����j
	{
		return MOTIONTYPE_SLAP;
	}
}

//���͂ɓG���邩
bool CPlayer::AroundEnemy(D3DXVECTOR3 pos)
{
	CScene *pScene = CScene::GetScene(CScene::PRIORITY_CHARA);
	CScene *pSceneNext;
	float fDistance;
	D3DXVECTOR3 Epos;
	while (pScene)
	{
		pSceneNext = pScene->GetNext();
		//�G��������
		if (pScene->GetObjType() == CScene::OBJECTTYPE_ENEMY)
		{
			//���b�N�I�����Ă�G����Ȃ�
			if (pScene != m_pRockon->GetRockEnemy())
			{
				Epos = pScene->GetPos();
				fDistance = sqrtf(powf(Epos.x - pos.x, 2.0f) + powf(Epos.z - pos.z, 2.0f));
				//�G���߂��ɂ���ꍇ
				if (fDistance - m_fRadius - pScene->GetRadius() < 100.0f)
				{
					return true;
				}
			}
		}
		pScene = pSceneNext;

	}
	return false;
}

//���b�N�I�����̓G�T�[�`
void CPlayer::SearchRock(D3DXVECTOR3 pos)
{
	//�����␳���Ȃ��ꍇ�AY�̈ړ��ʂ�0�ɂ���
	if (m_MotionInfo.aKeyInfo[m_nKey].fHeight != 0.0f)
	{
		m_move.y = 0.0f;
	}

	//�ǔ�����
	if (m_MotionInfo.bHoming == true)
	{
		D3DXVECTOR3 Epos = m_pRockon->GetRockEnemy()->GetPos();
		m_rotDesh.y = atan2f(pos.x - Epos.x, pos.z - Epos.z);
		float fERadius = m_pRockon->GetRockEnemy()->GetRadius();
		float fHDistance = sqrtf(powf(Epos.x - pos.x, 2.0f) + powf(Epos.z - pos.z, 2.0f)) - m_fRadius - fERadius;	//��������
		float fVDistance = Epos.y + (m_pRockon->GetRockEnemy()->GetHeight() / 2) - pos.y;	//��������
		if (fabsf(fHDistance) > fabsf(m_MotionInfo.aKeyInfo[m_nKey].fMove) * 0.8f)	//������������������ꍇ
		{
			//�ړ��ʂ��̂܂�
			MotionMove(m_rotDesh.y, m_MotionInfo.aKeyInfo[m_nKey].fMove);
		}
		else //�������߂��ꍇ
		{
			//�ړ��ʌ��炷
			MotionMove(m_rotDesh.y, m_MotionInfo.aKeyInfo[m_nKey].fMove * 0.3f);
		}
		switch (m_MotionInfo.MotionUpdn)
		{
		case MOTIONUPDN_NONE:	//�������Ȃ�
			break;
		case MOTIONUPDN_UNDER:	//�������Ɉړ�
			if (fVDistance < m_MotionInfo.aKeyInfo[m_nKey].fHeight * 0.8f)
			{
				MotionHeight(m_MotionInfo.aKeyInfo[m_nKey].fHeight);
			}
			else
			{
				MotionStopHeight();
			}
			break;
		case MOTIONUPDN_UPPER:	//������Ɉړ�
			if (fVDistance > m_MotionInfo.aKeyInfo[m_nKey].fHeight * 1.0f)
			{
				MotionHeight(m_MotionInfo.aKeyInfo[m_nKey].fHeight);
			}
			else
			{
				MotionStopHeight();
			}
			break;
		case MOTIONUPDN_UPDN:	//�㉺�ǂ����ł�
			if (fVDistance < -150.0f)
			{
				MotionHeight(-m_MotionInfo.aKeyInfo[m_nKey].fHeight);
			}
			else if (fVDistance > 150.0f)
			{
				MotionHeight(m_MotionInfo.aKeyInfo[m_nKey].fHeight);
			}
			else
			{
				MotionStopHeight();
			}
			break;
		default:
			break;
		}
	}
	//�ǔ����Ȃ�
	else
	{
		//�ړ��ʂ��̂܂�
		MotionMove(m_rotDesh.y, m_MotionInfo.aKeyInfo[m_nKey].fMove);
		MotionHeight(m_MotionInfo.aKeyInfo[m_nKey].fHeight);
	}
}

//�U���q�b�g���̃p�[�e�B�N�����
void CPlayer::SetParticle()
{
	int nCntPart;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;

	//�������������蔻��̏ꏊ
	pos = D3DXVECTOR3(m_MotionInfo.Collision[m_nCntCol].mtxWorld._41, m_MotionInfo.Collision[m_nCntCol].mtxWorld._42, m_MotionInfo.Collision[m_nCntCol].mtxWorld._43);
	float CameraRotY = m_pCamera->GetRotY();
	float fRand = 0.0f;
	float fRandX;
	for (nCntPart = 0; nCntPart < 3; nCntPart++)
	{
		fRandX = fRand + 1.0f;
		if (fRandX > 1.0f)
		{
			fRandX -= 2.0f;
		}
		switch (nCntPart)
		{
		case 0:
			move = D3DXVECTOR3(0.0f, 28.0f, 0.0f); //��
			rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 1:
			move = D3DXVECTOR3(sinf(fRand * D3DX_PI + CameraRotY) * 28.0f, cosf(D3DX_PI * fRand) * 28.0f, sinf(CameraRotY) * -28.0f); //�E��
			rot = D3DXVECTOR3(sinf(fRandX * D3DX_PI + CameraRotY) * 1.2f, 0.0f, cosf(fRand * D3DX_PI + CameraRotY) * -1.2f);
			break;
		case 2:
			move = D3DXVECTOR3(sinf(fRand * D3DX_PI + CameraRotY) * 28.0f, cosf(D3DX_PI * fRand) * 28.0f, sinf(CameraRotY) * 28.0f); //����
			rot = D3DXVECTOR3(sinf(fRandX * D3DX_PI + CameraRotY) * -1.2f, 0.0f, cosf(fRand * D3DX_PI + CameraRotY) * 1.2f);
			break;
		default:
			break;
		}

		//�p�[�e�B�N�����
		CParticle::Create(pos, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.02f), D3DXVECTOR3(3.0f, 35.0f, 0.0f), 50, 1, move, rot);
		fRand += 0.66f;
		if (fRand > 1.0f)
		{
			fRand -= 2.0f;
		}
	}
}

//���b�N�I�����Ȃ��ōU��
CPlayer::MOTIONTYPE CPlayer::NoRockAttack()
{
	//�J�E���^�[�\��������A�J�E���^�[����
	if (m_bCounter == true)
	{
		m_nCombo = 1;
		return MOTIONTYPE_COUNTER;
	}
	else if (m_nCombo >= 2) //�R���{�t�B�j�b�V���̕���
	{
		m_nCombo = 0;
		return MOTIONTYPE_FINISH;
	}
	else if (m_motionType == MOTIONTYPE_SLAP || m_motionTypeOld == MOTIONTYPE_SLAP) //���O�̍U�������ߋ����������ꍇ(�R���{2�i��)
	{
		m_nCombo++;
		return MOTIONTYPE_RUSH;
	}
	else //��L�Y������(�J�E���^�[�ł͂Ȃ��A�R���{���i)
	{
		m_nCombo++;
		return MOTIONTYPE_SLAP;
	}
}

//�v���C���[�ւ̃_���[�W
void CPlayer::PlayerDamage(D3DXVECTOR3 pos, float fHeight, float fRadius)
{
	CScene *pScene;
	pScene = GetScene(CScene::PRIORITY_CHARA);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		//�G��������
		if (pScene->GetObjType() == CScene::OBJECTTYPE_ENEMY)
		{
			//�_���[�W����Ƃ̓����蔻��
			if (pScene->CollisionDamage(pos, fRadius, fHeight) == true)
			{
				//�K�[�h����������
				if (m_motionType == MOTIONTYPE_GUARD)
				{
					//�K�[�h���[�V���������A�G�̑̐������A�J�E���^�[�\�ɂ���
					MotionChange(MOTIONTYPE_GUARD);
					pScene->Reflect();
					m_bCounter = true;
					m_bHit = true;
					m_pCounterUI->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					CSound::Play(CSound::SOUND_LABEL_GUARD);
				}
				//�K�[�h������Ȃ��A���G���Ԃ���Ȃ�
				else if (m_nCntNoDmg <= 0)
				{
					//�����蔻��̏ꏊ�̕���������o��
					float fRot = atan2f(pos.x - pScene->GetPos().x, pos.z - pScene->GetPos().z);
					float fVClash = pScene->VClash();
					float fHClash = pScene->HClash();
					
					//��̕����Ƀm�b�N�o�b�N������
					D3DXVECTOR3 clash;
					clash.x = fHClash * sinf(fRot);
					clash.y = fVClash;
					clash.z = fHClash * cosf(fRot);

					//��̕����ɍ��킹�āA�O����_���[�W�H��������[�V�����ɂ��邩�A��납��_���[�W�H��������[�V�����ɂ��邩
					if (fabsf(GetRot().y - fRot) < D3DX_PI * 0.5f)
					{
						//�O����_���[�W�H��������[�V����
						MotionChange(MOTIONTYPE_DAMAGEFRONT);
					}
					else
					{
						//��납��_���[�W�H��������[�V����
						MotionChange(MOTIONTYPE_DAMAGEBACK);
					}
					//�p�[�e�B�N�����A�v���C���[�̓_���[�W�H�炤
					pScene->SetParticle();
					Damage(pScene->Damage(), clash);
				}
			}
		}
		pScene = pSceneNext;
	}
}

//�|�[�Y���̑I�����ύX
void CPlayer::PauseChange(int nAdd)
{
	//���̑I������������
	m_pPauseUI[m_nPauseSelect]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f));

	//�I�����̐��l����
	m_nPauseSelect += nAdd;
	if (m_nPauseSelect < 0)
	{
		m_nPauseSelect = 2;
	}
	else if (m_nPauseSelect > 2)
	{
		m_nPauseSelect = 0;
	}

	//�I�񂾑I�����Z������
	m_pPauseUI[m_nPauseSelect]->ColorChange(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	CSound::Play(CSound::SOUND_LABEL_SELECT);
}

//�|�[�Y�I��������
void CPlayer::PauseSelect()
{
	switch (m_nPauseSelect)
	{
	case 0:	//�|�[�Y����
		CManager::SetPause(false);
		break;
	case 1:	//��蒼��
		CFade::SetFade(CManager::MODE_GAME);
		break;
	case 2:	//�^�C�g���Ɉڍs
		CFade::SetFade(CManager::MODE_TITLE);
		break;
	default:
		break;
	}
	CSound::Play(CSound::SOUND_LABEL_OK);
}

//�I�������̑I�����ύX
void CPlayer::EndChange(int nAdd)
{
	//���̑I������������
	m_pEndUI[m_nPauseSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));

	//�I�����̐��l����
	m_nPauseSelect += nAdd;
	if (m_nPauseSelect < 0)
	{
		m_nPauseSelect = 1;
	}
	else if (m_nPauseSelect > 1)
	{
		m_nPauseSelect = 0;
	}

	//�I�񂾑I�����Z������
	m_pEndUI[m_nPauseSelect]->ColorChange(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CSound::Play(CSound::SOUND_LABEL_SELECT);
}

//�I����I��������
void CPlayer::EndSelect()
{
	switch (m_nPauseSelect)
	{
	case 0:
		CFade::SetFade(CManager::MODE_GAME);
		break;
	case 1:
		CFade::SetFade(CManager::MODE_TITLE);
		break;
	default:
		break;
	}
	CSound::Play(CSound::SOUND_LABEL_OK);
}

//�Q�[���N���A
void CPlayer::GameClear()
{
	//���[�V�������N���A�ɂ���
	MotionChange(MOTIONTYPE_CLEAR);

	//���b�N�I���O��
	UnRockon();

	//�J�����̌����Œ�
	m_pCamera->SetRockon(true);
	m_pCamera->SetPosR(D3DXVECTOR3(0.0f, m_fHeight * 0.6f, 0.0f));
	m_pCamera->SetPosV(D3DXVECTOR3(90.0f, m_fHeight * 0.8f, -400.0f));
	m_pCamera->SetRot(D3DXVECTOR3(0.0f, GetRot().y - 0.3f, 0.0f));
	m_bGameClear = true;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDesh = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pShadow->MoveY(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	CManager::SetGameClear(true);

	//�ȗ���
	CSound::Stop(CSound::SOUND_LABEL_GAMEBGM);
	CSound::Play(CSound::SOUND_LABEL_CLEAR);
}