//=============================================================================
//
// ���e���� [thunder.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _THUNDER_H_
#define _THUNDER_H_
#include "main.h"
#include "scene2d.h"

#define THUNDER_SIZE (25.0f)
#define BAND_LENGTH (300.0f)

class CThunder : public CScene2D
{
public:
	CThunder(PRIORITY Priority = PRIORITY_BULLET);
	~CThunder();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool GetDamage(void) { return false; }
	void Damage(int) { ; }

	static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
	static void UnLoad(void);	//�e�N�X�`���j��
	static CThunder *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//�쐬

private:
	void BandCreate(int nEnemy, D3DXVECTOR3 pos);	//���̑э쐬

	int m_nEffectTime;			//�G�t�F�N�g���܂ł̎���
	D3DXVECTOR3 m_move;			//�ړ����x
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	CScene2D *m_pThunderEffect;	//���G�t�F�N�g
	bool m_bUninit;				//�폜���邩
};

#endif