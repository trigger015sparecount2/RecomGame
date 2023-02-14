//=============================================================================
//
// ���̑я��� [thunderband.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _THUNDERBAND_H_
#define _THUNDERBAND_H_
#include "main.h"
#include "scene2d.h"

class CThunderBand : public CScene2D
{
public:
	CThunderBand(PRIORITY Priority = PRIORITY_CHARA);
	~CThunderBand();
	HRESULT Init(D3DXVECTOR3 pos, float fRotY, float fLength);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool GetDamage(void) { return false; }	//�_���[�W�󂯂邩
	void Damage(int) { ; }					//�_���[�W����

	static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
	static void UnLoad(void);	//�e�N�X�`���j��
	static CThunderBand *Create(D3DXVECTOR3 pos, float fRotY, float fLength);	//�쐬

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	int m_nLife;	//����
	int m_nTex;		//�A�j���[�V�����p�^�[��
};

#endif