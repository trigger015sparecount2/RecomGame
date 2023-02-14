//=============================================================================
//
// �������� [explosion.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2d.h"

class CExplosion : public CScene2D
{
public:
	CExplosion(PRIORITY Priority = PRIORITY_EFFECT);
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit(void);				//�I��
	void Update(void);				//�X�V
	void Draw(void);				//�`��
	bool GetDamage(void) { return false; }
	void Damage(int) { ; }

	static HRESULT Load(void);					//�e�N�X�`���ǂݍ���
	static void UnLoad(void);					//�e�N�X�`���j��
	static CExplosion *Create(D3DXVECTOR3 pos);	//�쐬

private:
	int m_nPatternAnim;	//�A�j���[�V�����p�^�[��
	int m_nCounterAnim;	//�A�j���[�V�����J�E���g
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
};

#endif