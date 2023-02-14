//---------------------------
//Author:�O��q��
//�J����(camera.cpp)
//---------------------------
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "enemy.h"

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

//����������
HRESULT CCamera::Init(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	m_camera.posV = ref;
	m_camera.posVDest = ref;
	m_camera.posR = pos;
	m_camera.posRDest = pos;
	m_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_camera.rot = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_camera.rotDesh = m_camera.rot;
	m_camera.fLength = fDistance;		//����
	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxProjection);
	//�v���W�F�N�V�����}�g���b�N�X�쐬
	D3DXMatrixPerspectiveFovLH(&m_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 30000.0f);
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView, &m_camera.posV, &m_camera.posR, &m_camera.vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
	
	return S_OK;
}

//�I������
void CCamera::Uninit()
{

}

//�X�V����
void CCamera::Update()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	//�Q�[����
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		D3DXVECTOR3 pos = m_pPlayer->GetPos();
		if (m_bRockon == true)
		{
			if (m_camera.bRot[1] == true && m_camera.bAdd[1] == false)
			{
				//Y������]
				if (m_camera.rot.y != m_camera.rotDesh.y)
				{
					if (m_camera.rotDesh.y - m_camera.rot.y < -D3DX_PI)
					{
						m_camera.rot.y += (m_camera.rotDesh.y - m_camera.rot.y + D3DX_PI * 2) * 0.1f;
					}
					else if (m_camera.rotDesh.y - m_camera.rot.y > D3DX_PI)
					{
						m_camera.rot.y += (m_camera.rotDesh.y - m_camera.rot.y - D3DX_PI * 2) * 0.1f;
					}
					else
					{
						m_camera.rot.y += (m_camera.rotDesh.y - m_camera.rot.y) * 0.1f;
					}
				}
				//������x���������߂�
				if (fabsf(m_camera.rotDesh.y - m_camera.rot.y) < 0.3f)
				{
					m_camera.bRot[1] = false;
				}
			}
			if (m_camera.bRot[0] == true && m_camera.bAdd[0] == false)
			{
				//X������]
				if (m_camera.rot.x != m_camera.rotDesh.x)
				{
					if (m_camera.rotDesh.x - m_camera.rot.x < -D3DX_PI)
					{
						m_camera.rot.x += (m_camera.rotDesh.x - m_camera.rot.x + D3DX_PI * 2) * 0.1f;
					}
					else if (m_camera.rotDesh.x - m_camera.rot.x > D3DX_PI)
					{
						m_camera.rot.x += (m_camera.rotDesh.x - m_camera.rot.x - D3DX_PI * 2) * 0.1f;
					}
					else
					{
						m_camera.rot.x += (m_camera.rotDesh.x - m_camera.rot.x) * 0.1f;
					}
				}
				//������x���������߂�
				if (fabsf(m_camera.rotDesh.x - m_camera.rot.x) < 0.1f)
				{
					m_camera.bRot[0] = false;
				}
			}
		}

		//�Q�[���N���A�A�Q�[���I�[�o�[������Ȃ�
		if (CManager::GetGameClear() == false && CManager::GetGameEnd() == false)
		{
			//�J�����ړ�������
			m_camera.posR.x = pos.x;
			m_camera.posR.y = pos.y + m_pPlayer->GetHeight() * tanf(m_camera.rot.x);
			m_camera.posR.z = pos.z;
			m_camera.posV.x = pos.x - (sinf(m_camera.rot.y))/* * tanf(m_camera.rot.x))*/ * m_camera.fLength;
			m_camera.posV.y = pos.y + m_pPlayer->GetHeight() * 1.5f/* + m_camera.fLength * (1.0f - tanf(m_camera.rot.x))*/;
			m_camera.posV.z = pos.z - (cosf(m_camera.rot.y))/* * tanf(m_camera.rot.x))*/ * m_camera.fLength;
		}
	}
	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxView);
	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_camera.mtxView, &m_camera.posV, &m_camera.posR, &m_camera.vecU);
	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
}

//�ݒ菈��
CCamera *CCamera::Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos)
{
	CCamera *pCamera;
	pCamera = new CCamera;
	if (pCamera != NULL)
	{
		pCamera->Init(ref, fDistance, pos);
	}
	return pCamera;
}

//���_�ݒ�
void CCamera::SetPosV(D3DXVECTOR3 pos)
{
	m_camera.posVDest = pos;
	m_camera.posV = pos;
}

//�����_�ݒ�
void CCamera::SetPosR(D3DXVECTOR3 pos)
{
	m_camera.posRDest = pos;
	m_camera.posR = pos;
}

//���������Z
void CCamera::AddRotY(float fRotY)
{
	m_camera.rot.y += fRotY;
	if (m_camera.rot.y < -D3DX_PI)
	{
		m_camera.rot.y += D3DX_PI * 2.0f;
	}
	else if (m_camera.rot.y > D3DX_PI)
	{
		m_camera.rot.y -= D3DX_PI * 2.0f;
	}
	m_camera.bAdd[1] = true;
}

//�c�������Z
void CCamera::AddRotX(float fRotX)
{
	m_camera.rot.x += fRotX;
	//�J������������
	if (m_camera.rot.x > 1.0f)
	{
		m_camera.rot.x = 1.0f;
	}
	else if (m_camera.rot.x < 0.4f)
	{
		m_camera.rot.x = 0.4f;
	}
	m_camera.bAdd[0] = true;
}

//�J�����ړ�
void CCamera::MoveX(float fMove)
{
	m_camera.posR.x += sinf(m_camera.rot.y + D3DX_PI * 0.5f) * fMove;
	m_camera.posR.z += cosf(m_camera.rot.y + D3DX_PI * 0.5f) * fMove;
	m_camera.posV.x += sinf(m_camera.rot.y + D3DX_PI * 0.5f) * fMove;
	m_camera.posV.z += cosf(m_camera.rot.y + D3DX_PI * 0.5f) * fMove;
}

//�J�����ړ�
void CCamera::MoveZ(float fMove)
{
	m_camera.posR.x -= sinf(m_camera.rot.y) * fMove;
	m_camera.posR.z -= cosf(m_camera.rot.y) * fMove;
	m_camera.posV.x -= sinf(m_camera.rot.y) * fMove;
	m_camera.posV.z -= cosf(m_camera.rot.y) * fMove;
}

//�J�����������Z�b�g
void CCamera::ResetRot()
{
	m_camera.rot = D3DXVECTOR3(0.8f, 0.0f, 0.0f);
}

//�J������������������ݒ�X
void CCamera::SetRotDeshX(float fRotX)
{
	m_camera.rotDesh.x = fRotX;
	m_camera.bRot[0] = true;
	/*
	if (m_camera.rotDesh.x > 1.0f)
	{
		m_camera.rotDesh.x = 1.0f;
	}
	else if (m_camera.rotDesh.x < 0.4f)
	{
		m_camera.rotDesh.x = 0.4f;
	}
	*/
}

//�J������������������ݒ�Y
void CCamera::SetRotDeshY(float fRotY)
{
	m_camera.rotDesh.y = fRotY;
	m_camera.bRot[1] = true;
	if (m_camera.rotDesh.y >= D3DX_PI)
	{
		m_camera.rotDesh.y -= D3DX_PI * 2;
	}
	if (m_camera.rotDesh.y < -D3DX_PI)
	{
		m_camera.rotDesh.y += D3DX_PI * 2;
	}
}

//�J�����̌������Z������
void CCamera::SetAdd(bool bAdd)
{
	m_camera.bAdd[0] = bAdd;
	m_camera.bAdd[1] = bAdd;
}