//=============================================================================
//
// �e���� [shadow.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"
#include "scene2d.h"

class CShadow : public CScene2D
{
public:
	CShadow(PRIORITY Priority = PRIORITY_BG);
	~CShadow();
	HRESULT Init(D3DXVECTOR3 pos, float fWidth, float fHeight);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool GetDamage(void) { return false; }	//�_���[�W�󂯂邩
	void Damage(int) { ; }			//�_���[�W����

	static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
	static void UnLoad(void);	//�e�N�X�`���j��
	static CShadow *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, SHADOW shadow);	//�쐬

private:
	float m_fWidth;		//����
	float m_fHeight;	//�c��
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_SHADOW];	//�e�N�X�`��
	bool m_bUninit;		//������
};

#endif