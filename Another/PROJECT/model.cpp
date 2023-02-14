//---------------------------
//Author:�O��q��
//���f��(model.cpp)
//---------------------------
#include "model.h"
#include "manager.h"
#include "renderer.h"

CModel::CModel()
{

}

CModel::~CModel()
{

}

//����������
HRESULT CModel::Init(const char *aModelName)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	D3DXLoadMeshFromX(aModelName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);
	D3DXMATERIAL *pMat;
	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	int nCntTex = 0;
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_aTextureModel[nCntTex]);
			nCntTex++;
		}
	}
	m_rotOri = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOri = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pParent = NULL;
	m_nIdxModelParent = -1;
	return S_OK;
}

//�I������
void CModel::Uninit()
{
	//�e�N�X�`���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//�X�V����
void CModel::Update()
{

}

//�`�揈��
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans, mtxParent; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;		 //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			 //�}�e���A���f�[�^�ւ̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();		 //�f�o�C�X���擾����
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y + m_rotOri.y, m_rot.x + m_rotOri.x, m_rot.z + m_rotOri.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_posOri.x, m_pos.y + m_posOri.y, m_pos.z + m_posOri.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMatrix();
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//�p�[�c�̌��݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	//�p�[�c�̃}�e���A���f�[�^�ւ̃|�C���^�̔��f
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	int nCntMat;
	for (nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		int nCntTex = 0;
		//�v���C���[�̃}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_aTextureModel[nCntTex]);
			nCntTex++;
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}
		//�v���C���[�̃��f���i�p�[�c�j�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//�I�u�W�F�N�g�`��
void CModel::DrawObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice;   //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;		 //���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			 //�}�e���A���f�[�^�ւ̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();		 //�f�o�C�X���擾����
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//�p�[�c�̌��݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	//�p�[�c�̃}�e���A���f�[�^�ւ̃|�C���^�̔��f
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	int nCntMat;
	for (nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		int nCntTex = 0;
		//�I�u�W�F�N�g�̃}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_aTextureModel[nCntTex]);
			nCntTex++;
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}
		//�I�u�W�F�N�g�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//�쐬
CModel *CModel::Create(const char *aModelName)
{
	CModel *pModel;
	pModel = new CModel;
	if (pModel != NULL)
	{
		pModel->Init(aModelName);
	}
	return pModel;
}

//�T�C�Y�̍ŏ�
D3DXVECTOR3 CModel::GetMinSize()
{
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtxMinModel = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	//���_�����擾
	int nNumVtx = m_pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W�̑��
		if (vtxMinModel.x > vtx.x)
		{
			vtxMinModel.x = vtx.x;
		}
		if (vtxMinModel.y > vtx.y)
		{
			vtxMinModel.y = vtx.y;
		}
		if (vtxMinModel.z > vtx.z)
		{
			vtxMinModel.z = vtx.z;
		}
		pVtxBuff += sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();
	return vtxMinModel;
}

//�T�C�Y�̍ő�
D3DXVECTOR3 CModel::GetMaxSize()
{
	DWORD sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtxMaxModel = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	//���_�����擾
	int nNumVtx = m_pMesh->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());
	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff; //���_���W�̑��
		if (vtxMaxModel.x < vtx.x)
		{
			vtxMaxModel.x = vtx.x;
		}
		if (vtxMaxModel.y < vtx.y)
		{
			vtxMaxModel.y = vtx.y;
		}
		if (vtxMaxModel.z < vtx.z)
		{
			vtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFVF; //���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();
	return vtxMaxModel;
}

//���f���̃R�s�[
void CModel::Copy(CModel *pModel)
{
	m_pMesh = pModel->m_pMesh;
	m_pBuffMat = pModel->m_pBuffMat;
	m_nNumMat = pModel->m_nNumMat;
	m_pParent = NULL;
	m_posOri = pModel->m_posOri;
	m_rotOri = pModel->m_rotOri;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nCntTex;
	for (nCntTex = 0; nCntTex < 4; nCntTex++)
	{
		if (pModel->m_aTextureModel[nCntTex] != NULL)
		{
			m_aTextureModel[nCntTex] = pModel->m_aTextureModel[nCntTex];
		}
	}
}