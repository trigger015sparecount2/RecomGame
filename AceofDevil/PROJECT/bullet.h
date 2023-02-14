//=============================================================================
//
// �e�ۏ��� [bullet.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2d.h"

#define BULLET_SIZE (10.0f)

class CBullet : public CScene2D
{
public:
	CBullet(PRIORITY Priority = PRIORITY_BULLET);
	~CBullet();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, bool bEnemy, CScene::ELEMENT element);	//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��
	bool GetDamage(void) { return false; }	//�������Ȃ�
	void Damage(int) { ; }					//�������Ȃ�

	static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
	static void UnLoad(void);	//�e�N�X�`���̔j��
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, bool bEnemy, CScene::ELEMENT element);	//�쐬

private:
	D3DXVECTOR3 m_move;						//�ړ����x
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	int m_nEffect;							//�G�t�F�N�g�̔���
	bool m_bUninit;							//�폜���邩
};

#endif