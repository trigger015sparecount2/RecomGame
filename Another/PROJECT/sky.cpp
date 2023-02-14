//---------------------------
// Author:�O��q��
// ��(sky.cpp)
//---------------------------
#include "sky.h"

#include "plane.h"
#include "manager.h"
#include "renderer.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CSky::m_pTexture = NULL;

CSky::CSky(PRIORITY Priority) : CScene::CScene(Priority)
{

}

CSky::~CSky(void)
{

}

//����������
HRESULT CSky::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 15,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = pos;
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 18000.0f, 0.0f); //�Ă��؂�
	pVtx[1].pos = D3DXVECTOR3(-12000.0f, 16000.0f, 8000.0f);
	pVtx[2].pos = D3DXVECTOR3(-12000.0f, 16000.0f, -8000.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 16000.0f, -14000.0f);
	pVtx[4].pos = D3DXVECTOR3(12000.0f, 16000.0f, -8000.0f);
	pVtx[5].pos = D3DXVECTOR3(12000.0f, 16000.0f, 8000.0f);
	pVtx[6].pos = D3DXVECTOR3(0.0f, 16000.0f, 14000.0f);
	pVtx[7].pos = D3DXVECTOR3(-12000.0f, 16000.0f, 8000.0f);//��
	pVtx[8].pos = D3DXVECTOR3(-12000.0f, -5000.0f, 8000.0f);
	pVtx[9].pos = D3DXVECTOR3(-12000.0f, -5000.0f, -8000.0f);
	pVtx[10].pos = D3DXVECTOR3(0.0f, -5000.0f, -14000.0f);
	pVtx[11].pos = D3DXVECTOR3(12000.0f, -5000.0f, -8000.0f);
	pVtx[12].pos = D3DXVECTOR3(12000.0f, -5000.0f, 8000.0f);
	pVtx[13].pos = D3DXVECTOR3(0.0f, -5000.0f, 14000.0f);
	pVtx[14].pos = D3DXVECTOR3(-12000.0f, -5000.0f, 8000.0f);//�^��

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[14].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[12].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[13].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[14].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(3.0f / 6.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f / 6.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / 6.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(2.0f / 6.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(3.0f / 6.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(4.0f / 6.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(5.0f / 6.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(6.0f / 6.0f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f / 6.0f, 1.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f / 6.0f, 1.0f);
	pVtx[10].tex = D3DXVECTOR2(2.0f / 6.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(3.0f / 6.0f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(4.0f / 6.0f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(5.0f / 6.0f, 1.0f);
	pVtx[14].tex = D3DXVECTOR2(6.0f / 6.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 38,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);
	WORD *pIdx; //�C���f�b�N�X���ւ̃|�C���^
	//�C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);
	pIdx[0] = 0;
	pIdx[1] = 1;
	pIdx[2] = 2;
	pIdx[3] = 0;
	pIdx[4] = 0;
	pIdx[5] = 2;
	pIdx[6] = 3;
	pIdx[7] = 0;
	pIdx[8] = 0;
	pIdx[9] = 3;
	pIdx[10] = 4;
	pIdx[11] = 0;
	pIdx[12] = 0;
	pIdx[13] = 4;
	pIdx[14] = 5;
	pIdx[15] = 0;
	pIdx[16] = 0;
	pIdx[17] = 5;
	pIdx[18] = 6;
	pIdx[19] = 0;
	pIdx[20] = 0;
	pIdx[21] = 6;
	pIdx[22] = 7;//��
	pIdx[23] = 1;
	pIdx[24] = 1;
	pIdx[25] = 8;
	pIdx[26] = 2;
	pIdx[27] = 9;
	pIdx[28] = 3;
	pIdx[29] = 10;
	pIdx[30] = 4;
	pIdx[31] = 11;
	pIdx[32] = 5;
	pIdx[33] = 12;
	pIdx[34] = 6;
	pIdx[35] = 13;
	pIdx[36] = 7;
	pIdx[37] = 14;//��
	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
	return S_OK;
}

//�I������
void CSky::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}
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
void CSky::Update(void)
{
	//�|�[�Y���ł��I����Ă��Ȃ�
	if (CManager::GetPause() == false && CManager::GetEnd() == false)
	{
		int nCntTex;
		VERTEX_3D *pVtx; //���_���ւ̃|�C���^
		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
		for (nCntTex = 0; nCntTex < 15; nCntTex++)
		{
			pVtx[nCntTex].tex.x += m_fScroll;
		}
		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//�`�揈��
void CSky::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);
	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);
	if (m_pTexture == NULL)
	{
		m_pTexture = *CPlane::GetTexture(2);
	}
	pDevice->SetTexture(0, m_pTexture);    //�e�N�X�`���̐ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		15, //���_�̐�
		0,
		36); //�`�悷��v���~�e�B�u��
}

//�쐬
CSky *CSky::Create(D3DXVECTOR3 pos, float fScroll, LPDIRECT3DTEXTURE9 *Texture)
{
	CSky *pSky;
	pSky = new CSky(PRIORITY_PLANE);
	if (pSky != NULL)
	{
		pSky->Init(pos);
		pSky->SetScroll(fScroll);
		pSky->SetTexture(Texture);
	}
	return pSky;
}