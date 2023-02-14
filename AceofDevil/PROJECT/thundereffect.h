//=============================================================================
//
// ���G�t�F�N�g���� [thundereffect.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _THUNDEREFFECT_H_
#define _THUNDEREFFECT_H_
#include "main.h"
#include "scene2d.h"
#define THUNDEREFFECT_SIZE (60.0f)
class CThundereffect : public CScene2D
{
public:
	CThundereffect(PRIORITY Priority = PRIORITY_BG);
	~CThundereffect();
	HRESULT Init(D3DXVECTOR3 pos);			//������
	void Uninit(void);						//�I��
	void Update(void);						//�X�V
	void Draw(void);						//�`��
	bool GetDamage(void) { return false; }	//�_���[�W�󂯂邩
	void Damage(int) { ; }			//�_���[�W����

	static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
	static void UnLoad(void);	//�e�N�X�`���j��
	static CThundereffect *Create(D3DXVECTOR3 pos);	//�쐬

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
};

#endif