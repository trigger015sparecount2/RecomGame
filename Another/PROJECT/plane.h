//=============================================================================
//
// �V�[������ [field.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _PLANE_H_
#define _PLANE_H_

#include "main.h"
#include "scene3d.h"

//�}�N����`
#define MAX_TEXTURE_FILED (16)

class CPlane : public CScene3D
{
public:
	CPlane(PRIORITY Priority);
	~CPlane();
	HRESULT Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex, bool bRotX);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	//OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	//void SetPos(D3DXVECTOR3 pos);
	//D3DXVECTOR3 GetPos() { return m_pos; }
	/*float GetRadius() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }*/
	//void Damage(int, D3DXVECTOR3, float);

	//�T�C�Y�i�[�E�擾
	D3DXVECTOR3 GetSize() { return m_size; }
	void SetSize(D3DXVECTOR3 size);
	
	LPDIRECT3DVERTEXBUFFER9 GetVtx() { return m_pVtxBuff; }	//���_�o�b�t�@�ւ̃|�C���^�擾
	void SetTexture(int nTex) { m_nTexType = nTex; }		//�w�肳�ꂽ�ԍ��̃e�N�X�`����\���悤��
	void ChangeColor(D3DXCOLOR col);						//�F�ς���

	//�G�t�F�N�g�p�֐�
	void ColorChange(D3DXCOLOR color);	//�F�ύX
	void ChangeSize(D3DXVECTOR3 size);	//�T�C�Y�ύX
	static CPlane *Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex, bool bRotX);	//�쐬
	static void CreateTextureFiled();	//�e�N�X�`���ǂݍ���

	static LPDIRECT3DTEXTURE9 *GetTexture(int nTex) { return &m_pTexture[nTex]; }	//�e�N�X�`���擾

	//�e�N�X�`���j��
	static void UninitTexture();

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_size;							//�T�C�Y
	static int m_nMaxTex;						//�g�p����ő�e�N�X�`��

protected:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE_FILED];	//�e�N�X�`���ւ̃|�C���^
	int m_nTexType;												//�\��e�N�X�`��
};

#endif