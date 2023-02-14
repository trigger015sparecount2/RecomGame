//---------------------------
//Author:�O��q��
//�G(enemy.cpp)
//---------------------------
#include "enemy.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "shadow.h"
#include "sound.h"
#include "keyboard.h"
#include "particle.h"

//=============================================================================
//�ÓI
//=============================================================================
CEnemy::Copies CEnemy::m_Copies = {};
int CEnemy::m_nEnemies = 0;

//=============================================================================
//�}�N��
//=============================================================================
#define RAND_COLOR (int(rand()%255) + 30)	//�F�����_��
#define RAND_MOVE ((int(rand() % 3) + 1 )- (int (rand()%3) + 1))	//�ړ��l�����_��
#define RAND_MOVE_2 ((int(rand() % 3) + 1 ))	//�ړ��l�����_��

CEnemy::CEnemy(PRIORITY Priority) : CScene3D::CScene3D(Priority)
{

}

CEnemy::~CEnemy()
{

}

//����������
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//���O�ɓǂݍ��񂾃f�[�^���R�s�[����
	DataCopy();
	SetPos(pos);
	SetRot(rot);
	m_rotDesh = rot;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_motionMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntThinkTime = 30;
	m_nCntMoveTime = 0;
	m_PosOld = pos;
	m_bJump = true;
	m_bLandObject = false;
	D3DXVECTOR3 size;
	size.x = GetRadius();
	size.y = 0.0f;
	size.z = GetRadius();
	m_pShadow = CShadow::Create(size, D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));
	MotionChange(MOTIONTYPE_RETURN);
	m_bLanding = true;
	m_bAttack = false;
	m_bAttackMove = false;
	m_nEnemies++;
	float CameraRotY = CManager::GetRenderer()->GetCamera()->GetRotY();
	int nCnt;
	D3DXVECTOR3 move;
	
	//�p�[�e�B�N���o��
	for (nCnt = 0; nCnt < 8; nCnt++)
	{
		switch (nCnt)
		{
		case 0:
			move = D3DXVECTOR3(0.0f, 8.0f, 0.0f); //��
			break;
		case 1:
			move = D3DXVECTOR3(sinf(D3DX_PI * 0.5f + CameraRotY) * 8.0f, cosf(D3DX_PI * 0.25f) * 8.0f, sinf(-CameraRotY) * 8.0f);
			break;
		case 2:
			move = D3DXVECTOR3(sinf(D3DX_PI * 0.5f + CameraRotY) * 10.0f, cosf(D3DX_PI * 0.5f) * 8.0f, sinf(-CameraRotY) * 10.0f);
			break;
		case 3:
			move = D3DXVECTOR3(sinf(D3DX_PI * 0.5f + CameraRotY) * 8.0f, cosf(D3DX_PI * 0.75f) * 8.0f, sinf(-CameraRotY) * 8.0f);
			break;
		case 4:
			move = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
			break;
		case 5:
			move = D3DXVECTOR3(sinf(D3DX_PI * -0.5f + CameraRotY) * 8.0f, cosf(D3DX_PI * -0.75f) * 8.0f, sinf(CameraRotY) * 8.0f);
			break;
		case 6:
			move = D3DXVECTOR3(sinf(D3DX_PI * -0.5f + CameraRotY) * 10.0f, cosf(D3DX_PI * -0.5f) * 8.0f, sinf(CameraRotY) * 10.0f);
			break;
		case 7:
			move = D3DXVECTOR3(sinf(D3DX_PI * -0.5f + CameraRotY) * 8.0f, cosf(D3DX_PI * -0.25f) * 8.0f, sinf(CameraRotY) * 8.0f);
			break;
		default:
			break;
		}
		CParticle::Create(D3DXVECTOR3(pos.x, pos.y + (m_Status.fHeight * 0.5f), pos.z), D3DXCOLOR(0.2f, 0.0f, 0.2f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.01f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), 100, 1, move, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	CSound::Play(CSound::SOUND_LABEL_ENEMYAPP);
	return S_OK;
}

//�I������
void CEnemy::Uninit()
{
	if (m_pShadow != NULL)
	{
		m_pShadow->SetDeath(true);
		m_pShadow = NULL;
	}
	int nCntModel; 
	for (nCntModel = 0; nCntModel < 32; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel] = NULL;
		}
	}
	m_nEnemies--;
	CScene3D::Uninit();
}

//�X�V����
void CEnemy::Update()
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	pos = GetPos();
	posOld = pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotOld;
	rot = GetRot();
	rotOld = rot;
	//���n���Ă邩
	if (m_bJump == true && m_bLandObject == false)
	{
		m_bJump = false;
	}
	
	//�|�[�Y���ł��J�E���g�_�E���ł��I����Ă����Ȃ�
	if (CManager::GetPause() == false && CManager::GetCountdown() == false && CManager::GetGameEnd() == false)
	{
		//�U�����邽�߂Ɉړ�����
		if (m_bAttackMove == false)
		{
			//�v�l����
			if (m_nCntThinkTime > 0)
			{
				//�v�l���ԃJ�E���g���炷
				m_nCntThinkTime--;
				//�ړ�����
				if (m_nCntMoveTime > 0)
				{
					//�J�E���g���炵�Ȃ���ړ�������
					m_nCntMoveTime--;
					Move(m_rotDesh.y);
					if (m_nCntMoveTime <= 0)
					{
						MotionChange(MOTIONTYPE_RETURN);
					}
				}
				else
				{
					//�~�܂�
					Stop();
				}

				//���[�V�����ɍ��킹���ړ�������
				MotionMove(m_MotionInfo.aKeyInfo[m_nKey].fMove, m_MotionInfo.aKeyInfo[m_nKey].fHeight);
			}
			else
			{
				//�󋵂ɍ��킹�čU���Ȃǂ���
				EnemyAI();
			}
		}
		//�U�����邽�߂̈ړ���
		else
		{
			//�J�E���g�i�߂�A�J�E���g���傫���Ȃ�����܂��l����
			m_nCntThinkTime++;
			if (m_nCntThinkTime > 800)
			{
				MotionChange(MOTIONTYPE_RETURN);
				m_bAttackMove = false;
				m_nCntThinkTime = 120;
			}
			else
			{
				//�U���܂ōl����
				AttackAI(pos);
			}
		}

		//�_���[�W����
		EnemyDamage(pos, m_Status.fRadius, m_Status.fHeight);
		pos += m_move + m_motionMove;

		//�G�A�I�u�W�F�N�g�A���ʂƂ̓����蔻��
		CollisionEnemy(&pos);
		CollisionObject(&pos, posOld);
		CollisionPlane(&pos, posOld);

		//�󒆂ɂ��邩�d�͓���
		if (m_bJump == false && m_MotionInfo.bGravity == true)
		{
			//�d�͓�������
			if (m_move.y > -15.0f)
			{
				m_move.y -= m_Status.fGravity;
				if (m_move.y >= -15.0f)
				{
					m_move.y = -15.0f;
				}
			}
		}

		//�󒆂ɂ���
		if (m_bJump == false)
		{
			//���ɉ����邩���ׂ�
			UnderSearch(pos);
		}
	}

	//����������Ȃ��悤�ɂ���
	if (m_rotDesh.y >= D3DX_PI)
	{
		m_rotDesh.y -= D3DX_PI * 2;
	}
	if (m_rotDesh.y < -D3DX_PI)
	{
		m_rotDesh.y += D3DX_PI * 2;
	}
	if (rot.y >= D3DX_PI)
	{
		rot.y -= D3DX_PI * 2;
	}
	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	//������������Ǝ��ۂ̕��������킹��
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

	//�|�[�Y���ł��I����Ă����Ȃ�
	if (CManager::GetPause() == false && CManager::GetGameEnd() == false)
	{
		//���[�V��������A�ʒu������̐ݒ�
		Motion();
		if (pos.y < -300.0f)
		{
			pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		SetPos(pos);
		SetRot(rot);
	}
}

//�`�揈��
void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxEnemy, mtxRot, mtxTrans;
	pDevice = CManager::GetRenderer()->GetDevice();		 //�f�o�C�X���擾����

	//�G�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxEnemy);

	//�G�̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxRot);

	//�G�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxEnemy, &mtxEnemy, &mtxTrans);

	//�G�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxEnemy);
	SetMatrix(mtxEnemy);

	int nCntModel;
	for (nCntModel = 0; nCntModel < m_Status.nNumModel; nCntModel++)
	{
		if (m_pModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel]->Draw();
		}
	}
}

void CEnemy::Load(const char *aFileName)
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
			if (strcmp(&aFile[0], "#") == 0) //�R�����g�͖���
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
					fscanf(pFile, "%d", &m_Copies.status.nNumModel);
				}
				if (strcmp(&aFile[0], "MOVE") == 0) //�ړ����x
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_Copies.status.fMove);
				}
				if (strcmp(&aFile[0], "JUMP") == 0) //�W�����v��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_Copies.status.fJump);
				}
				if (strcmp(&aFile[0], "GRAVITY") == 0) //�d��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_Copies.status.fGravity);
				}
				if (strcmp(&aFile[0], "RADIUS") == 0) //���a
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_Copies.status.fRadius);
				}
				if (strcmp(&aFile[0], "HEIGHT") == 0) //�g��
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%f", &m_Copies.status.fHeight);
				}
				if (strcmp(&aFile[0], "HP") == 0) //�̗�
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_Copies.status.nHP);
					m_Copies.status.nMaxHP = m_Copies.status.nHP;
				}
				if (strcmp(&aFile[0], "PARTSSET") == 0)	//�p�[�c�ݒ�J�n
				{
					bParts = true;
				}
				if (strcmp(&aFile[0], "END_PARTSSET") == 0)	//�p�[�c�ݒ�I��
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
						m_Copies.apModel[nCntParts] = paModel[nIndex];
					}
					if (strcmp(&aFile[0], "PARENT") == 0) //�e���f��
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &nParent);
						/*if (nParent != -1)
						{
							m_Copies.m_pModel[nCntParts]->SetParent(m_Copies.m_pModel[nParent]);
						}*/
						m_Copies.apModel[nCntParts]->SetIdxParent(nParent);
					}
					if (strcmp(&aFile[0], "POS") == 0) //�e�p�[�c�̏ꏊ
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &pos.x, &pos.y, &pos.z);
						m_Copies.apModel[nCntParts]->SetOriPos(pos);
					}
					if (strcmp(&aFile[0], "ROT") == 0) //�e�p�[�c�̊p�x
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f %f %f", &rot.x, &rot.y, &rot.z);
						m_Copies.apModel[nCntParts]->SetOriRot(rot);
					}
				}
			}
			if (bMotion == true && nCntMotion < MOTIONTYPE_RETURN) //MOTIONSET��
			{
				if (strcmp(&aFile[0], "LOOP") == 0) //���̃��[�V���������[�v���邩0���ƃ��[�v���Ȃ�1���ƃ��[�v����
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nLoop);
					if (nLoop == 0)
					{
						m_Copies.amotionInfo[nCntMotion].bLoop = false;
					}
					else
					{
						m_Copies.amotionInfo[nCntMotion].bLoop = true;
					}
				}
				if (strcmp(&aFile[0], "GRAVITY") == 0) //�d�͂�������0���Ɠ����Ȃ�1���Ɠ���
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &nGravity);
					if (nGravity == 0)
					{
						m_Copies.amotionInfo[nCntMotion].bGravity = false;
					}
					else
					{
						m_Copies.amotionInfo[nCntMotion].bGravity = true;
					}
				}
				if (strcmp(&aFile[0], "NUM_KEY") == 0) //�����L�[�����邩
				{
					fscanf(pFile, "%s", &aFile[0]);
					fscanf(pFile, "%d", &m_Copies.amotionInfo[nCntMotion].nNumKey);
				}
				if (strcmp(&aFile[0], "NO_ATTACK") == 0) //�U�����Ȃ����[�V����
				{
					m_Copies.amotionInfo[nCntMotion].Damage[0].nStartTime = 1;
					m_Copies.amotionInfo[nCntMotion].Damage[0].nFinishTime = 0;
				}
				if (strcmp(&aFile[0], "KEYSET") == 0)	//�L�[�̐ݒ�J�n
				{
					bKeySet = true;
					m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove = 0.0f;
					m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].fHeight = 0.0f;
					nCntParts = 0;
				}
				if (strcmp(&aFile[0], "END_KEYSET") == 0)	//�L�[�̐ݒ�I��
				{
					bKeySet = false;
					nCntKey++;
				}
				if (strcmp(&aFile[0], "ORBITSET") == 0)	//�O�Ղ̐ݒ�J�n
				{
					bOrbitSet = true;
					nCntObt = 0;
				}
				if (strcmp(&aFile[0], "END_ORBITSET") == 0)	//�O�Ղ̐ݒ�I��
				{
					bOrbitSet = false;
					m_Copies.amotionInfo[nCntMotion].nNumOrbit = nCntObt;
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
							fscanf(pFile, "%d %f %f %f %f", &m_Copies.amotionInfo[nCntMotion].Collision[nCntCol].nIdxModelParent, &m_Copies.amotionInfo[nCntMotion].Collision[nCntCol].pos.x,
								&m_Copies.amotionInfo[nCntMotion].Collision[nCntCol].pos.y, &m_Copies.amotionInfo[nCntMotion].Collision[nCntCol].pos.z,
								&m_Copies.amotionInfo[nCntMotion].Collision[nCntCol].fRadius);
						}
					}
				}
				if (bOrbitSet == true)	//�O�Ղ̐ݒ�
				{
					if (strcmp(&aFile[0], "ORBIT") == 0)	//�O�Ղ̐ݒ�J�n
					{
						bOrbit = true;
					}
					if (strcmp(&aFile[0], "END_ORBIT") == 0)	//�O�Ղ̐ݒ�I��
					{
						bOrbit = false;
						nCntObt++;
					}
					if (bOrbit == true)
					{
						if (strcmp(&aFile[0], "OBT") == 0) //�O�Ձi�e�̃C���f�b�N�X�A�ꏊ�A�\�����ԁA�������ԁj
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%d %f %f %f %f %d %d", &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].nIdxParent, &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].pos.x,
								&m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].pos.y, &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].pos.z,
								&m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].fDis, &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].nStartTime, &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].nFinishTime);
						}
						if (strcmp(&aFile[0], "COL1") == 0) //�F��[
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f %f", &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].col1.r, &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].col1.g,
								&m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].col1.b, &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].col1.a);
						}
						if (strcmp(&aFile[0], "COL2") == 0) //�F���{
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f %f", &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].col2.r, &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].col2.g,
								&m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].col2.b, &m_Copies.amotionInfo[nCntMotion].Orbit[nCntObt].col2.a);
						}
					}
				}
				if (bDmgSet == true)	//�_���[�W�ݒ�
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
							fscanf(pFile, "%f %f %d %d", &m_Copies.amotionInfo[nCntMotion].Damage[nCntDmg].fHClash, &m_Copies.amotionInfo[nCntMotion].Damage[nCntDmg].fVClash,
								&m_Copies.amotionInfo[nCntMotion].Damage[nCntDmg].nDamage, &m_Copies.amotionInfo[nCntMotion].Damage[nCntDmg].nDamageTime);
						}
						if (strcmp(&aFile[0], "DMG_TIME") == 0) //�_���[�W�̎���(�n�܂�A�I���)
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%d %d", &m_Copies.amotionInfo[nCntMotion].Damage[nCntDmg].nStartTime, &m_Copies.amotionInfo[nCntMotion].Damage[nCntDmg].nFinishTime);
						}
					}
				}
				if (bKeySet == true) //KEYSET��
				{
					if (strcmp(&aFile[0], "FRAME") == 0) //�t���[����
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%d", &m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					}
					if (strcmp(&aFile[0], "MOVE") == 0) //�ړ���(��)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].fMove);
					}
					if (strcmp(&aFile[0], "HEIGHT") == 0) //�ړ���(�c)
					{
						fscanf(pFile, "%s", &aFile[0]);
						fscanf(pFile, "%f", &m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].fHeight);
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
							fscanf(pFile, "%f %f %f", &m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].pos.x,
								&m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].pos.y, &m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].pos.z);
						}
						if (strcmp(&aFile[0], "ROT") == 0) //�p�x
						{
							fscanf(pFile, "%s", &aFile[0]);
							fscanf(pFile, "%f %f %f", &m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].rot.x,
								&m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].rot.y, &m_Copies.amotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntParts].rot.z);
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
				m_Copies.amotionInfo[nCntMotion].nNumOrbit = nCntObt;
				nCntKey = 0;
				nCntCol = 0;
				nCntObt = 0;
			}
			if (strcmp(&aFile[0], "END_MOTIONSET") == 0)	//���[�V�����ݒ�I��
			{
				bMotion = false;
				nCntMotion++;
			}
			if (strcmp(&aFile[0], "COLLISIONSET") == 0)	//�����蔻��J�n
			{
				bColSet = true;
				nCntCol = 0;
			}
			if (strcmp(&aFile[0], "END_COLLISIONSET") == 0)	//�����蔻��I��
			{
				bColSet = false;
				m_Copies.amotionInfo[nCntMotion].nNumCol = nCntCol;
			}
			if (strcmp(&aFile[0], "DAMAGESET") == 0)	//�_���[�W�ݒ�J�n
			{
				bDmgSet = true;
				nCntDmg = 0;
			}
			if (strcmp(&aFile[0], "END_DAMAGESET") == 0)	//�_���[�W�ݒ�I��
			{
				bDmgSet = false;
				m_Copies.amotionInfo[nCntMotion].nNumDmg = nCntDmg;
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0) //�I����1��
			{
				break;
			}
		}
		fclose(pFile);
	}
	//�uMOTIONTYPE_RETURN�v�́A�j���[�g�������[�V�����ɖ߂�ۂɌo�R���郂�[�V����
	m_Copies.amotionInfo[MOTIONTYPE_RETURN].bLoop = false;
	m_Copies.amotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].nFrame = 10;
	m_Copies.amotionInfo[MOTIONTYPE_RETURN].nNumKey = 1;
	m_Copies.amotionInfo[MOTIONTYPE_RETURN].bGravity = true;
	for (nCntParts = 0; nCntParts < m_Copies.status.nNumModel; nCntParts++)
	{
		m_Copies.amotionInfo[MOTIONTYPE_RETURN].aKeyInfo[0].aKey[nCntParts] = m_Copies.amotionInfo[MOTIONTYPE_NEUTRAL].aKeyInfo[m_Copies.amotionInfo[MOTIONTYPE_NEUTRAL].nNumKey - 1].aKey[nCntParts];
	}
	m_Copies.amotionInfo[MOTIONTYPE_RETURN].Damage[0].nStartTime = 1;
	m_Copies.amotionInfo[MOTIONTYPE_RETURN].Damage[0].nFinishTime = 0;
}

//���f���j��
void CEnemy::UnLoad()
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < 32; nCntModel++)
	{
		if (m_Copies.apModel[nCntModel] != NULL)
		{
			m_Copies.apModel[nCntModel]->Uninit();
			m_Copies.apModel[nCntModel] = NULL;
		}
	}
}

//�ړ�
void CEnemy::Move(float fRotY)
{
	m_move.x -= (sinf(fRotY) * m_Status.fMove + m_move.x) * 0.1f;
	m_move.z -= (cosf(fRotY) * m_Status.fMove + m_move.z) * 0.1f;
	//m_rotDesh.y = D3DX_PI * fRotY + D3DX_PI;
}

//��~
void CEnemy::Stop()
{
	m_move.x -= m_move.x * 0.2f;
	m_move.z -= m_move.z * 0.2f;
}

//���[�V�����ɂ��ړ���
void CEnemy::MotionMove(float fMove, float fHeight)
{
	m_motionMove.x = -sinf(m_rotDesh.y) * fMove;
	m_motionMove.y = fHeight;
	m_motionMove.z = -cosf(m_rotDesh.y) * fMove;
}

//�I�u�W�F�N�g�Ƃ̓����蔻��
void CEnemy::CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	pScene = GetScene(PRIORITY_CHARA);
	bool bLand = false;
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		if (pScene->GetObjType() == CScene::OBJECTTYPE_BLOCK)
		{
			if (pScene->GetCollision() == CScene::COLLISION_SPHERE)
			{
				D3DXVECTOR3 pos = pScene->GetPos();
				float fRadius = pScene->GetRadius();
				float fRotY;
				float fLengthX = pPos->x - pos.x;
				float fLengthY = (pPos->y + (m_Status.fHeight / 2)) - pos.y;
				float fLengthZ = pPos->z - pos.z;
				fLengthX = powf(fLengthX, 2.0f);
				fLengthY = powf(fLengthY, 2.0f);
				fLengthZ = powf(fLengthZ, 2.0f);
				if (fLengthX + fLengthY + fLengthZ <= powf((m_Status.fHeight / 2) + fRadius, 2))
				{
					fRotY = atan2f(pos.x - pPos->x, pos.z - pPos->z);
					pPos->x = pos.x - sinf(fRotY) * ((m_Status.fHeight / 2) + fRadius);
					pPos->z = pos.z - cosf(fRotY) * ((m_Status.fHeight / 2) + fRadius);
				}
			}
			if (pScene->GetCollision() == CScene::COLLISION_SQUARE)
			{
				D3DXVECTOR3 pos = pScene->GetPos();
				D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
				D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
				float fPRadius = GetRadius();
				if (pos.x + VtxMin.x <= pPos->x + fPRadius && pPos->x - fPRadius <= pos.x + VtxMax.x &&
					pos.z + VtxMin.z <= pPos->z + fPRadius && pPos->z - fPRadius <= pos.z + VtxMax.z)
				{
					if (posOld.y >= pos.y + VtxMax.y && pPos->y <= pos.y + VtxMax.y)
					{
						pPos->y = pos.y + VtxMax.y;
						m_move.y = 0.0f;
						bLand = true;
						m_pShadow->MoveY(*pPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

						if (m_bLanding == false)
						{
							CSound::Play(CSound::SOUND_LABEL_LANDING);
							MotionChange(MOTIONTYPE_ACTION);
							m_bLanding = true;
						}
					}
					else if (posOld.y + m_Status.fHeight <= pos.y + VtxMin.y && pPos->y + m_Status.fHeight >= pos.y + VtxMin.y)
					{
						pPos->y = pos.y + VtxMin.y - m_Status.fHeight;
						m_move.y = 0.0f;
					}
					else if (pos.y + VtxMin.y <= pPos->y + m_Status.fHeight && pPos->y <= pos.y + VtxMax.y)
					{
						bool bIn = false;
						if (pos.x + VtxMin.x <= pPos->x + fPRadius && posOld.x + fPRadius <= pos.x + VtxMin.x)
						{
							pPos->x = pos.x + VtxMin.x - fPRadius;
							bIn = true;
						}
						else if (pos.x + VtxMax.x >= pPos->x - fPRadius && posOld.x - fPRadius >= pos.x + VtxMax.x)
						{
							pPos->x = pos.x + VtxMax.x + fPRadius + 0.1f;
							bIn = true;
						}
						if (pos.z + VtxMin.z <= pPos->z + fPRadius && posOld.z + fPRadius <= pos.z + VtxMin.z)
						{
							pPos->z = pos.z + VtxMin.z - fPRadius;
							bIn = true;
						}
						else if (pos.z + VtxMax.z >= pPos->z - fPRadius && posOld.z - fPRadius >= pos.z + VtxMax.z)
						{
							pPos->z = pos.z + VtxMax.z + fPRadius + 0.1f;
							bIn = true;
						}
						if (bIn == false)
						{
							float fMinDistance = 100000.0f;
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
									fMinDistance = fDistance[nCnt];
									nDistance = nCnt;
								}
							}
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

//�U���̓����蔻��̏ꏊ
void CEnemy::CollisionPos(int nCntCol)
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

//���Ƃ̓����蔻��
bool CEnemy::CollisionLand(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene)
{
	D3DXVECTOR3 pos = pScene->GetPos();
	D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
	D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
	D3DXVECTOR3 aPoint[4];
	D3DXVECTOR3 rot = pScene->GetRot();
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
	if ((aPoint[0].x < Point.x + m_Status.fRadius && Point.x - m_Status.fRadius < aPoint[1].x || aPoint[1].x < Point.x + m_Status.fRadius && Point.x - m_Status.fRadius < aPoint[0].x) ||
		(aPoint[0].x < OldPoint.x + m_Status.fRadius && OldPoint.x - m_Status.fRadius < aPoint[1].x || aPoint[1].x < OldPoint.x + m_Status.fRadius && OldPoint.x - m_Status.fRadius < aPoint[0].x))
	{
		if ((aPoint[0].z < Point.z + m_Status.fRadius && Point.z - m_Status.fRadius < aPoint[2].z || aPoint[2].z < Point.z + m_Status.fRadius && Point.z - m_Status.fRadius < aPoint[0].z) ||
			(aPoint[0].z < OldPoint.z + m_Status.fRadius && OldPoint.z - m_Status.fRadius < aPoint[2].z || aPoint[2].z < OldPoint.z + m_Status.fRadius && OldPoint.z - m_Status.fRadius < aPoint[0].z))
		{
			if (fOldDistance - 3.0f <= 0.0f && fDistance + 3.0f >= 0.0f)
			{
				pPos->y += fDistance;
				m_pShadow->MoveY(*pPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_move.y = 0.0f;
				if (m_bLanding == false)
				{
					CSound::Play(CSound::SOUND_LABEL_LANDING);
				}
				return true;
			}
		}
	}
	return false;
}

//�ǂƂ̓����蔻��
void CEnemy::CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene)
{
	D3DXVECTOR3 rot = pScene->GetRot();
	D3DXVECTOR3 aPoint[4];
	D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
	D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
	D3DXVECTOR3 pos = pScene->GetPos();
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
	if (aPoint[2].y < Point.y + m_Status.fHeight && Point.y < aPoint[0].y || aPoint[2].y < OldPoint.y + m_Status.fHeight && OldPoint.y < aPoint[0].y)
	{
		if ((aPoint[0].x < Point.x + m_Status.fRadius && Point.x - m_Status.fRadius < aPoint[1].x || aPoint[1].x < Point.x + m_Status.fRadius && Point.x - m_Status.fRadius < aPoint[0].x) ||
			(aPoint[0].x < OldPoint.x + m_Status.fRadius && OldPoint.x - m_Status.fRadius < aPoint[1].x || aPoint[1].x < OldPoint.x + m_Status.fRadius && OldPoint.x - m_Status.fRadius < aPoint[0].x))
		{
			if ((aPoint[0].z < Point.z + m_Status.fRadius && Point.z - m_Status.fRadius < aPoint[1].z || aPoint[1].z < Point.z + m_Status.fRadius && Point.z - m_Status.fRadius < aPoint[0].z) ||
				(aPoint[0].z < OldPoint.z + m_Status.fRadius && OldPoint.z - m_Status.fRadius < aPoint[1].z || aPoint[1].z < OldPoint.z + m_Status.fRadius && OldPoint.z - m_Status.fRadius < aPoint[0].z))
			{
				if (fabsf(fDistance) < m_Status.fRadius || fOldDistance < -m_Status.fRadius && fDistance > -m_Status.fRadius)
				{
					pPos->x -= sinf(rot.y) * (m_Status.fRadius + fDistance);
					pPos->z -= cosf(rot.y) * (m_Status.fRadius + fDistance);
					m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					if (rot.y <= 0.0f)
					{
						m_rotDesh.y += D3DX_PI * 0.7f;
					}
					else
					{
						m_rotDesh.y -= D3DX_PI * 0.7f;
					}
					if (m_rotDesh.y >= D3DX_PI)
					{
						m_rotDesh.y -= D3DX_PI * 2;
					}
					if (m_rotDesh.y < -D3DX_PI)
					{
						m_rotDesh.y += D3DX_PI * 2;
					}
				}
			}
		}
	}
}

//���ʂƂ̓����蔻��
void CEnemy::CollisionPlane(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld)
{
	CScene *pScene;
	pScene = CScene::GetScene(CScene::PRIORITY_PLANE);
	CScene *pSceneNext;
	bool bLand = false;
	while (pScene)
	{
		pSceneNext = pScene->GetNext();
		if (pScene->GetObjType() == CScene::OBJECTTYPE_WALL)
		{
			CollisionWall(pPos, posOld, pScene);
		}
		else if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD && bLand == false)
		{
			bLand = CollisionLand(pPos, posOld, pScene);
		}
		pScene = pSceneNext;
	}
	m_bJump = bLand;
	m_bLanding = bLand;
}

//�G���m�̓����蔻��
void CEnemy::CollisionEnemy(D3DXVECTOR3 *pPos)
{
	CScene *pScene;
	pScene = GetScene(PRIORITY_CHARA);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		if (pScene->GetObjType() == CScene::OBJECTTYPE_ENEMY && pScene != this)
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
			if (fLengthX + fLengthZ <= powf(m_Status.fRadius + fRadius, 2.0f) && pos.y < pPos->y + m_Status.fHeight && pPos->y < pos.y + fHeight)
			{
				fRotY = atan2f(pos.x - pPos->x, pos.z - pPos->z);
				pPos->x = pos.x - sinf(fRotY) * (m_Status.fRadius + fRadius);
				pPos->z = pos.z - cosf(fRotY) * (m_Status.fRadius + fRadius);
			}
		}
		pScene = pSceneNext;
	}
}

//���[�V�����ɂ��̂̃p�[�c�̉�]
void CEnemy::Motion() //���[�V�����̓���
{
	int nCntParts;
	m_nTotalTime++;
	m_nCntMotion++;
	if (m_MotionInfo.Damage[m_nDmgNumNow].nStartTime <= m_nTotalTime && m_nTotalTime < m_MotionInfo.Damage[m_nDmgNumNow].nFinishTime)
	{
		if (m_bAttack == false)
		{
			m_bAttack = true;
		}
		m_nCntDamage++;
	}
	else if (m_bAttack == true)
	{
		m_bAttack = false;
	}
	for (nCntParts = 0; nCntParts < m_Status.nNumModel; nCntParts++)
	{
		if (m_nCntMotion == 1) //���������߂�(�Ή�����L�[�̊e�p�[�c��pos(rot) - ���̊e�p�[�c��pos(rot))
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
		D3DXVECTOR3 posOld;
		posOld = m_pModel[nCntParts]->GetPos();
		posOld.x += m_aKeyDiff[nCntParts].pos.x / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.y += m_aKeyDiff[nCntParts].pos.y / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		posOld.z += m_aKeyDiff[nCntParts].pos.z / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		m_pModel[nCntParts]->SetPos(posOld);

		D3DXVECTOR3 rotOld;
		rotOld = m_pModel[nCntParts]->GetRot();
		rotOld.x += m_aKeyDiff[nCntParts].rot.x / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		rotOld.y += m_aKeyDiff[nCntParts].rot.y / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		rotOld.z += m_aKeyDiff[nCntParts].rot.z / m_MotionInfo.aKeyInfo[m_nKey].nFrame;
		m_pModel[nCntParts]->SetRot(rotOld);
	}
	if (m_nCntMotion == m_MotionInfo.aKeyInfo[m_nKey].nFrame)
	{
		m_nCntMotion = 0;
		m_nKey++;
		if (m_nKey == m_MotionInfo.nNumKey)
		{
			if (m_MotionInfo.bLoop == false)
			{
				if (m_motionType != MOTIONTYPE_RETURN)
				{
					MotionChange(MOTIONTYPE_RETURN);
				}
				else
				{
					MotionChange(MOTIONTYPE_NEUTRAL);
				}
			}
			m_nKey = 0;
		}
	}
	if (m_nCntDamage > m_MotionInfo.Damage[m_nDmgNumNow].nDamageTime)
	{
		m_bHit = false;
		m_nCntDamage = 0;
	}
	if (m_nTotalTime >= m_MotionInfo.Damage[m_nDmgNumNow].nFinishTime)
	{
		m_bHit = false;
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

//���[�V�����؂�ւ�
void CEnemy::MotionChange(MOTIONTYPE motionType)
{
	m_motionType = motionType;
	m_MotionInfo = m_aMotionInfo[motionType];
	m_nCntMotion = 0;
	m_nCntDamage = 0;
	m_nTotalTime = 0;
	m_nKey = 0;
	m_nDmgNumNow = 0;
	if (m_bAttack == true)
	{
		m_bAttack = false;
	}
	if (m_bHit == true)
	{
		m_bHit = false;
	}
}

//���𒲂ׂ�
void CEnemy::UnderSearch(D3DXVECTOR3 pos)
{
	CScene *pScene;
	int nCntScene;
	bool bUnder = false;
	bool bRotX = false;
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
			if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD || pScene->GetObjType() == CScene::OBJECTTYPE_BLOCK)
			{
				D3DXVECTOR3 Scenepos = pScene->GetPos();
				D3DXVECTOR3 VtxMax = pScene->GetVtxMax();
				D3DXVECTOR3 VtxMin = pScene->GetVtxMin();
				if (pos.x - GetRadius() < Scenepos.x + VtxMax.x && Scenepos.x + VtxMin.x < pos.x + GetRadius() &&
					pos.z - GetRadius() < Scenepos.z + VtxMax.z && Scenepos.z + VtxMin.z < pos.z + GetRadius())
				{
					if (pScene->GetObjType() == CScene::OBJECTTYPE_FIELD)
					{
						D3DXVECTOR3 VtxPos[4];
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
						rot.x = atan2f(VtxPos[2].y - VtxPos[0].y, VtxPos[2].z - VtxPos[0].z);
						rot.z = atan2f(VtxPos[1].y - VtxPos[0].y, VtxPos[1].x - VtxPos[0].x);
						fFieldY = (pos.z - Scenepos.z) * tanf(rot.x) + (pos.x - Scenepos.x) * tanf(rot.z) + Scenepos.y;
						rot.x = D3DX_PI - rot.x;
						if (fUnderPosY < fFieldY && pos.y > fFieldY)
						{
							fUnderPosY = fFieldY;
							bObject = false;
							bUnder = true;
							UnderRot = rot;
						}
					}
					else
					{
						fFieldY = Scenepos.y + VtxMax.y;
						if (fUnderPosY < fFieldY && pos.y > fFieldY)
						{
							fUnderPosY = fFieldY;
							bObject = true;
							bUnder = true;
						}
						//m_pShadow->MoveXY(D3DXVECTOR3(pos.x, fFieldY, pos.z), -fRotX);
					}
				}
			}
			pScene = pSceneNext;
		}
	}
	if (bUnder == true)
	{
		if (bObject == true)
		{
			m_pShadow->MoveY(D3DXVECTOR3(pos.x, fUnderPosY, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		else
		{
			if (bRotX == true)
			{
				m_pShadow->MoveY(D3DXVECTOR3(pos.x, fUnderPosY, pos.z), rot);
			}
			else
			{
				m_pShadow->MoveY(D3DXVECTOR3(pos.x, fUnderPosY, pos.z), rot);
			}
		}
	}
	else
	{
		m_pShadow->MoveY(D3DXVECTOR3(pos.x, pos.y - 100000.0f, pos.z), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}
}

//�_���[�W����
void CEnemy::Damage(int nDamage, D3DXVECTOR3 clash)
{
	m_Status.nHP -= nDamage;
	if (m_Status.nHP <= 0)
	{
		CSound::Play(CSound::SOUND_LABEL_ENEMYDEATH);
		SetDeath(true);
	}
	else
	{
		m_bAttack = false;
		m_nCntMoveTime = 0;
		m_nCntThinkTime = 80;
		m_move = clash;
		if (clash.y > 0.0f)
		{
			m_bJump = false;
			m_bLanding = false;
			m_bLandObject = false;
		}
		CSound::Play(CSound::SOUND_LABEL_ATTACK);
	}
}

//�_���[�W�Ƃ̓����蔻��
bool CEnemy::CollisionDamage(D3DXVECTOR3 pos, float fRadius, float fHeight)
{
	if (m_bAttack == true)
	{
		int nCntCol;
		float fLengthX;		//�����蔻��ƓG��X�����̒���
		float fLengthY;		//�����蔻��ƓG��Y�����̒���
		float fLengthZ;		//�����蔻��ƓG��Z�����̒���
		float fHDistance;	//�����蔻��ƓG�̐��������̋���
		for (nCntCol = 0; nCntCol < m_MotionInfo.nNumCol; nCntCol++)
		{
			CollisionPos(nCntCol);
			fLengthX = powf(pos.x - m_MotionInfo.Collision[nCntCol].mtxWorld._41, 2);
			fLengthY = pos.y + (fHeight / 2) - m_MotionInfo.Collision[nCntCol].mtxWorld._42;
			fLengthZ = powf(pos.z - m_MotionInfo.Collision[nCntCol].mtxWorld._43, 2);
			fHDistance = sqrtf(fLengthX + fLengthZ);
			if (fHDistance <= fRadius + m_MotionInfo.Collision[nCntCol].fRadius
				&& fabsf(fLengthY) <= fHeight + m_MotionInfo.Collision[nCntCol].fRadius && m_bHit == false)
			{
				m_bHit = true;
				m_nCntCol = nCntCol;
				return true;
			}
		}
	}
	return false;
}

//�v���C���[����G�ւ̃_���[�W
void CEnemy::EnemyDamage(D3DXVECTOR3 pos, float fRadius, float fHeight)
{
	CScene *pScene;
	pScene = GetScene(CScene::PRIORITY_CHARA);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		if (pScene->GetObjType() == CScene::OBJECTTYPE_PLAYER)
		{
			if (pScene->CollisionDamage(pos, fRadius, fHeight) == true)
			{
				if (pScene->SetEnemy(this) == true)
				{
					float fRot = atan2f(pos.x - pScene->GetPos().x, pos.z - pScene->GetPos().z);
					float fVClash = pScene->VClash();
					float fHClash = pScene->HClash();
					D3DXVECTOR3 clash;
					clash.x = fHClash * sinf(fRot);
					clash.y = fVClash;
					clash.z = fHClash * cosf(fRot);
					if (fabsf(GetRot().y - fRot) < D3DX_PI * 0.5f)
					{
						MotionChange(MOTIONTYPE_DAMAGEFRONT);
					}
					else
					{
						MotionChange(MOTIONTYPE_DAMAGEBACK);
					}
					pScene->SetParticle();
					Damage(pScene->Damage(), clash);
				}
			}
			break;
		}
		pScene = pSceneNext;
	}
}

//�G��AI
void CEnemy::EnemyAI()
{
	if (EnemyAttack() == true) //�G�����ȏ�U�����悤�Ƃ��Ė���������
	{
		int nRand = rand() % 5;
		if (nRand < 2) //�K���ȕ����Ɉړ�
		{
			m_nCntMoveTime = 150 + (rand() % 10) * 30;
			m_nCntThinkTime = m_nCntMoveTime + 180;
			m_rotDesh.y = D3DX_PI * ((float)(rand() % 360) / 180.0f) - D3DX_PI;
			MotionChange(MOTIONTYPE_RUN);
		}
		else //�U��
		{
			m_bAttackMove = true;
		}
	}
	else //�K���ȕ����ֈړ�
	{
		m_nCntMoveTime = 150 + (rand() % 10) * 30;
		m_nCntThinkTime = m_nCntMoveTime + 180;
		m_rotDesh.y = D3DX_PI * (float)((rand() % 360) / 180.0f) - D3DX_PI;
		MotionChange(MOTIONTYPE_RUN);
	}
}

//�G�����̍U�����Ă邩
bool CEnemy::EnemyAttack()
{
	int nCntEnemy = 0;
	CScene *pScene;
	pScene = GetScene(CScene::PRIORITY_CHARA);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		if (pScene->GetObjType() == CScene::OBJECTTYPE_ENEMY)
		{
			if (pScene->GetAttack() == true)
			{
				nCntEnemy++;
				if (nCntEnemy > 3)
				{
					return false;
				}
			}
		}
		pScene = pSceneNext;
	}
	return true;
}

//�v���C���[�T��
D3DXVECTOR3 CEnemy::SearchPlayer(void)
{
	CScene *pScene;
	pScene = GetScene(CScene::PRIORITY_CHARA);
	while (pScene)
	{
		CScene *pSceneNext;
		pSceneNext = pScene->GetNext();
		if (pScene->GetObjType() == CScene::OBJECTTYPE_PLAYER)
		{
			return pScene->GetPos();
		}
		pScene = pSceneNext;
	}
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//�U������AI
void CEnemy::AttackAI(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 PlayerPos = SearchPlayer();
	float fLengthX = pos.x - PlayerPos.x;
	float fLengthZ = pos.z - PlayerPos.z;
	float fDistance = sqrtf(powf(fLengthX, 2.0f) + powf(fLengthZ, 2.0f));
	if (fDistance < 200.0f + m_Status.fRadius)
	{
		m_bAttackMove = false;
		m_nCntMoveTime = 0;
		m_nCntThinkTime = 120 + (rand() % 5) * 30;
		m_rotDesh.y = atan2f(fLengthX, fLengthZ);
		MotionChange(MOTIONTYPE_ACTION);
	}
	else
	{
		m_rotDesh.y = atan2f(fLengthX, fLengthZ);
		Move(m_rotDesh.y);
		if (m_motionType != MOTIONTYPE_RUN)
		{
			MotionChange(MOTIONTYPE_RUN);
		}
	}
}

//�p�[�e�B�N�����
void CEnemy::SetParticle()
{
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();
	int nCntPart;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	pos = D3DXVECTOR3(m_MotionInfo.Collision[m_nCntCol].mtxWorld._41, m_MotionInfo.Collision[m_nCntCol].mtxWorld._42, m_MotionInfo.Collision[m_nCntCol].mtxWorld._43);
	float CameraRotY = pCamera->GetRotY();
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
			move = D3DXVECTOR3(0.0f, 6.0f, 0.0f); //��
			rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			break;
		case 1:
			move = D3DXVECTOR3(sinf(fRand * D3DX_PI + CameraRotY) * 6.0f, cosf(D3DX_PI * fRand) * 6.0f, sinf(CameraRotY) * -6.0f); //�E��
			rot = D3DXVECTOR3(sinf(fRandX * D3DX_PI + CameraRotY) * 1.2f, 0.0f, cosf(fRand * D3DX_PI + CameraRotY) * -1.2f);
			break;
		case 2:
			move = D3DXVECTOR3(sinf(fRand * D3DX_PI + CameraRotY) * 6.0f, cosf(D3DX_PI * fRand) * 6.0f, sinf(CameraRotY) * 6.0f); //����
			rot = D3DXVECTOR3(sinf(fRandX * D3DX_PI + CameraRotY) * -1.2f, 0.0f, cosf(fRand * D3DX_PI + CameraRotY) * 1.2f);
			break;
		default:
			break;
		}
		CParticle::Create(pos, D3DXCOLOR(0.2f, 0.0f, 0.2f, 1.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.01f), D3DXVECTOR3(5.0f, 35.0f, 0.0f), 100, 1, move, rot);
		fRand += 0.66f;
		if (fRand > 1.0f)
		{
			fRand -= 2.0f;
		}
	}
}

//�U�����h���ꂽ
void CEnemy::Reflect()
{
	MotionChange(MOTIONTYPE_REFLECT);
	m_nCntThinkTime = 300;
	m_nCntMoveTime = 0;
}

//���f���⃂�[�V�������R�s�[����
void CEnemy::DataCopy()
{
	int nCntModel;
	for (nCntModel = 0; nCntModel < m_Copies.status.nNumModel; nCntModel++)
	{
		if (m_Copies.apModel[nCntModel] != NULL)
		{
			m_pModel[nCntModel] = new CModel;
			m_pModel[nCntModel]->Copy(m_Copies.apModel[nCntModel]);
			if (m_Copies.apModel[nCntModel]->GetIdxParent() != -1)
			{
				m_pModel[nCntModel]->SetParent(m_pModel[m_Copies.apModel[nCntModel]->GetIdxParent()]);
			}
		}
	}
	for (nCntModel = 0; nCntModel < MAX_MOTION; nCntModel++)
	{
		m_aMotionInfo[nCntModel] = m_Copies.amotionInfo[nCntModel];
	}
	m_Status = m_Copies.status;
}

//�쐬
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemy;
	pEnemy = new CEnemy(PRIORITY_CHARA);
	if (pEnemy != NULL)
	{
		pEnemy->Init(pos, rot);
	}
	return pEnemy;
}