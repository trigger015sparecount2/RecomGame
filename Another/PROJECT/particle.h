//*****************************************************************************
// �G�t�F�N�g���� [particle.h]
// Author : �O��q��
//*****************************************************************************

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "plane.h"

class CParticle : public CPlane
{
public:
	CParticle(CScene::PRIORITY PRIORITY_EFFECT);
	~CParticle();

	HRESULT Init(D3DXVECTOR3 pos, D3DXCOLOR color, D3DXCOLOR Mincolor, D3DXVECTOR3 Size, int nLife, int nType, D3DXVECTOR3 Move, D3DXVECTOR3 Rot);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CParticle *Create(D3DXVECTOR3 pos, D3DXCOLOR color, D3DXCOLOR Mincolor, D3DXVECTOR3 Size, int nLife, int nType, D3DXVECTOR3 Move, D3DXVECTOR3 Rot);	//�쐬

protected:

private:
	//�J���[�l
	D3DXCOLOR m_Color;

	//���炷�J���[�l
	D3DXCOLOR m_MinColor;
	D3DXVECTOR3 m_Rot;	//����
	D3DXVECTOR3 m_Move;	//�ړ���
	int m_nLife;		//����
	int m_nType;		//���
};
#endif
