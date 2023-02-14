//---------------------------
// Author:�O��q��
// �O��(orbit.cpp)
//---------------------------
#include "orbit.h"
#include "manager.h"
#include "renderer.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 COrbit::m_pTexture = NULL;

COrbit::COrbit(PRIORITY Priority) : CScene::CScene(Priority)
{

}

COrbit::~COrbit(void)
{

}

//����������
HRESULT COrbit::Init(D3DXVECTOR3)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	m_nNumOrbit = 0;
	m_nCnt = 0;
	m_nStart = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_ORBIT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	int nCntOrbit;

	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	//���_���W�̐ݒ�
	for (nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		pVtx[nCntOrbit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[nCntOrbit].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntOrbit].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[nCntOrbit].tex = D3DXVECTOR2(0.0f, 0.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (MAX_ORBIT + 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx; //�C���f�b�N�X���ւ̃|�C���^
	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);
	for (nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		pIdx[nCntOrbit] = (WORD)nCntOrbit;
	}
	pIdx[MAX_ORBIT] = 0;
	pIdx[MAX_ORBIT + 1] = 1;
	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
	return S_OK;
}

//�I������
void COrbit::Uninit(void)
{
	/*if (m_pTexture != NULL)
	{
	m_pTexture->Release();
	m_pTexture = NULL;
	}*/
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	Release();
}

//�X�V����
void COrbit::Update(void)
{
	int nCntOrbit;
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
	for (nCntOrbit = 0; nCntOrbit < MAX_ORBIT; nCntOrbit++)
	{
		if (m_col[nCntOrbit].a > 0.0f)
		{
			m_col[nCntOrbit].a -= m_fDis[nCntOrbit];
			pVtx[nCntOrbit].col = m_col[nCntOrbit];
			if (m_col[nCntOrbit].a <= 0.0f)
			{
				//pVtx[nCntOrbit].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				m_nNumOrbit--;
				m_nStart++;
				if (m_nStart >= MAX_ORBIT)
				{
					m_nStart = 0;
				}
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//�`�揈��
void COrbit::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����

	//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//�J�����O�I�t
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);
	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, NULL);    //�e�N�X�`���̐ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		MAX_ORBIT, //���_�̐�
		m_nStart, //�ŏ��̒��_�ԍ�
		m_nNumOrbit - 2); //�`�悷��v���~�e�B�u��
	if (m_nNumOrbit > MAX_ORBIT - m_nStart)
	{
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			MAX_ORBIT, //���_�̐�
			0, //�ŏ��̒��_�ԍ�
			m_nNumOrbit - (MAX_ORBIT - m_nStart) - 2); //�`�悷��v���~�e�B�u��
	}

	//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�J�����O�I��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//�쐬
COrbit *COrbit::Create(void)
{
	COrbit *pOrbit;
	pOrbit = new COrbit(PRIORITY_ORBIT);
	if (pOrbit != NULL)
	{
		pOrbit->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	return pOrbit;
}

//�O�Րݒ�
void COrbit::SetOrbit(D3DXVECTOR3 pos, D3DXVECTOR3 Tippos, float fDis, D3DXCOLOR col1, D3DXCOLOR col2)
{
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[m_nCnt].pos = pos;
	pVtx[m_nCnt].col = col2;
	m_col[m_nCnt] = col2;
	m_fDis[m_nCnt] = fDis;
	m_nCnt++;
	pVtx[m_nCnt].pos = Tippos;
	pVtx[m_nCnt].col = col1;
	m_col[m_nCnt] = col1;
	m_fDis[m_nCnt] = fDis;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	m_nCnt++;
	if (m_nCnt >= MAX_ORBIT)
	{
		m_nCnt = 0;
	}
	m_nNumOrbit += 2;
}