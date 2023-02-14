//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2d.h"

class CEffect : public CScene2D
{
public:
	//�J���[�^�C�v
	typedef enum
	{
		COLORTYPE_WHITE = 0,
		COLORTYPE_RED,
		COLORTYPE_LIGHTBLUE,
		COLORTYPE_YELLOW,
		COLORTYPE_BLUE,
		COLORTYPE_GREEN,
		COLORTYPE_MAX
	} COLORTYPE;

	CEffect(PRIORITY Priority = PRIORITY_EFFECT);
	~CEffect();
	HRESULT Init(D3DXVECTOR3 pos, COLORTYPE colType);	//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	bool GetDamage(void) { return false; }
	void Damage(int) { ; }

	static HRESULT Load(void);									//�e�N�X�`���̓ǂݍ���
	static void UnLoad(void);									//�e�N�X�`���j��
	static CEffect *Create(D3DXVECTOR3 pos, COLORTYPE colType);	//�쐬

private:
	float m_fSize;							//�T�C�Y
	D3DXCOLOR m_col;						//�J���[
	COLORTYPE m_colType;					//�J���[�^�C�v
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
};

#endif