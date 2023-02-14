//=============================================================================
//
// �V�[������ [field.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"
#include "plane.h"

class CField : public CPlane
{
public:
	CField(PRIORITY Priority);
	~CField();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex, bool bRotX);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	OBJTYPE GetObjType() { return OBJECTTYPE_FIELD; }	//���
	//D3DXVECTOR3 GetPos() { return m_pos; }
	//float GetRadius() { return 0.0f; }
	//COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return m_VtxMax; }		//�ő�
	D3DXVECTOR3 GetVtxMin() { return m_VtxMin; }		//�ŏ�
	//void Damage(int, D3DXVECTOR3, float) { ; }
	bool GetRotX() { return m_bRotX; }					//�X������

	static CField *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, int nTex, D3DXVECTOR2 Tex, bool bRotX);	//�쐬

private:
	//D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_VtxMax;	//�ő�
	D3DXVECTOR3 m_VtxMin;	//�ŏ�
	bool m_bRotX;			//�X������
};

#endif