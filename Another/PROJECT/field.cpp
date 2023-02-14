//---------------------------
//Author:�O��q��
//�t�B�[���h(field.cpp)
//---------------------------
#include "field.h"
#include "manager.h"
#include "renderer.h"

CField::CField(PRIORITY Priority) : CPlane::CPlane(Priority)
{

}

CField::~CField()
{

}

//����������
HRESULT CField::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex, bool bRotX)
{
	CPlane::Init(size, pos, Tex, bRotX);
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//SetPos(pos);
	m_VtxMax = size;
	m_VtxMin = -size;
	m_bRotX = bRotX;
	return S_OK;
}

//�I������
void CField::Uninit()
{
	CPlane::Uninit();
}

//�X�V����
void CField::Update()
{

}

//�`�揈��
void CField::Draw()
{
	CPlane::Draw();
}

CField *CField::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, int nTex, D3DXVECTOR2 Tex, bool bRotX)
{
	CField *pField;
	pField = new CField(PRIORITY_PLANE);
	if (pField != NULL)
	{
		pField->Init(size, pos, Tex, bRotX);
		pField->SetTexture(nTex);
	}
	return pField;
}