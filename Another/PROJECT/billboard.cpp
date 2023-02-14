//---------------------------
//Author:�O��q��
//�r���{�[�h(billboard.cpp)
//---------------------------
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

CBillboard::CBillboard(PRIORITY Priority) : CPlane::CPlane(Priority)
{

}

CBillboard::~CBillboard()
{

}


//����������
HRESULT CBillboard::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CPlane::Init(size, pos, D3DXVECTOR2(1.0f, 1.0f), false);
	return S_OK;
}

//�I������
void CBillboard::Uninit()
{
	CPlane::Uninit();
}

//�X�V����
void CBillboard::Update()
{

}

//�`�揈��
void CBillboard::Draw()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans, mtxWorld; //�v�Z�p�}�g���b�N�X
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
														//���C���e�B���O�𖳎�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//��ɕ\�������悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_Billboard[nCntBoard].mtxWorld);
	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);
	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&mtxWorld, NULL, &mtxView); //�t�s������߂�
	mtxWorld._41 = 0.0f;
	mtxWorld._42 = 0.0f;
	mtxWorld._43 = 0.0f;
	/*										���ӂ̂���
	g_mtxWorldBillboard._11 = mtxView._11;
	g_mtxWorldBillboard._12 = mtxView._21;
	g_mtxWorldBillboard._13 = mtxView._31;
	g_mtxWorldBillboard._14 = mtxView._41;
	g_mtxWorldBillboard._21 = mtxView._12;
	g_mtxWorldBillboard._22 = mtxView._22;
	g_mtxWorldBillboard._23 = mtxView._32;
	g_mtxWorldBillboard._24 = mtxView._42;
	g_mtxWorldBillboard._31 = mtxView._13;
	g_mtxWorldBillboard._32 = mtxView._23;
	g_mtxWorldBillboard._33 = mtxView._33;
	g_mtxWorldBillboard._34 = mtxView._43;
	g_mtxWorldBillboard._41 = mtxView._14;	x��Pos
	g_mtxWorldBillboard._42 = mtxView._24;	y��Pos
	g_mtxWorldBillboard._43 = mtxView._34;	z��Pos
	g_mtxWorldBillboard._44 = mtxView._44;
	*/
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	SetMatrix(mtxWorld);
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, GetVtx(), 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, NULL);    //�e�N�X�`���̐ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
			//���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//�ʒu�ɂ���Ă͉f��Ȃ��悤�ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//�쐬
CBillboard *CBillboard::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos)
{
	CBillboard *pBillboard;
	pBillboard = new CBillboard(PRIORITY_PLANE);
	if (pBillboard != NULL)
	{
		pBillboard->Init(size, pos);
	}
	return pBillboard;
}