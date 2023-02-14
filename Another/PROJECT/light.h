//=============================================================================
//
// �V�[������ [light.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

class CLight
{
public:
	CLight();
	~CLight();
	HRESULT Init(D3DXCOLOR col, D3DXVECTOR3 vec, int nCntLight);	//������
	void Uninit();	//�I��
	void Update();	//�X�V

	static CLight *Create(D3DXCOLOR col, D3DXVECTOR3 vec, int nCntLight);	//�쐬

private:
	D3DLIGHT9 m_light[8];	//��
};

#endif