//---------------------------
//Author:�O��q��
//���C�g(light.cpp)
//---------------------------
#include "light.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"

CLight::CLight()
{

}

CLight::~CLight()
{

}

//����������
HRESULT CLight::Init(D3DXCOLOR col, D3DXVECTOR3 vec, int nCntLight)
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�̃|�C���^
	D3DXVECTOR3 vecDir; //�ݒ�p�����x�N�g��
	pDevice = CManager::GetRenderer()->GetDevice();     //�f�o�C�X���擾����
	//���C�g���N���A����
	ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));
	//���C�g�̎�ނ�ݒ�
	m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL; //�Ό�����
													//���C�g�̊g�U��i�F�j��ݒ�
	m_light[nCntLight].Diffuse = col;
	//���C�g�̕�����ݒ�
	vecDir = vec;
	D3DXVec3Normalize(&vecDir, &vecDir); //���K������
	m_light[nCntLight].Direction = vecDir;
	//���C�g��ݒ肷��
	pDevice->SetLight(nCntLight, &m_light[nCntLight]);
	//���C�g��L���ɂ���
	pDevice->LightEnable(nCntLight, TRUE);
	return S_OK;
}

//�I��
void CLight::Uninit()
{

}

//�X�V
void CLight::Update()
{

}

//�쐬
CLight *CLight::Create(D3DXCOLOR col, D3DXVECTOR3 vec, int nCntLight)
{
	CLight *pLight;
	pLight = new CLight;
	if (pLight != NULL)
	{
		pLight->Init(col, vec, nCntLight);
	}
	return pLight;
}