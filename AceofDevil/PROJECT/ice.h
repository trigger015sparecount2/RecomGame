//=============================================================================
//
// �X�e���� [ice.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _ICE_H_
#define _ICE_H_
#include "main.h"
#include "scene2d.h"

//�}�N����`
#define ICE_MAX_ENEMY (16)

class CIce : public CScene2D
{
public:
	CIce(PRIORITY Priority = PRIORITY_BULLET);
	~CIce();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRotY);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool GetDamage(void) { return false; }
	void Damage(int) { ; }

	static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
	static void UnLoad(void);	//�e�N�X�`���j��
	static CIce *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRotY);	//�쐬

private:
	bool EnemyList(int nEnemy);	//���X�g���Ɣ�r�A�������Ă��邩
	void ListPush(int nEnemy);	//���X�g�ɓ����

	D3DXVECTOR3 m_move;	//�ړ����x
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	float m_fRotY;	//�����Ă����
	bool m_bUninit;	//�폜���邩
	int m_nListCnt;	//���X�g�̉��Ԗڂɓ���邩
	int m_nEffect;	//�G�t�F�N�g�J�E���g
	int m_aEnemies[ICE_MAX_ENEMY];	//���������G�̃��X�g
};

#endif