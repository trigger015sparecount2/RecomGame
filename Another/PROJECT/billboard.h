//=============================================================================
//
// �r���{�[�h���� [billboard.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "plane.h"

class CBillboard : public CPlane
{
public:
	CBillboard(PRIORITY Priority);
	~CBillboard();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	static CBillboard *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos);	//�쐬

private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//�摜
};

#endif