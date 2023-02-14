//=============================================================================
//
// �Α����e���� [fire.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _FIRE_H_
#define _FIRE_H_
#include "main.h"
#include "scene2d.h"

class CFire : public CScene2D
{
public:
	CFire(PRIORITY Priority = PRIORITY_BULLET);
	~CFire();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//������
	void Uninit(void);									//�I��
	void Update(void);									//�X�V
	void Draw(void);									//�`��
	bool GetDamage(void) { return false; }				//�_���[�W�󂯂邩
	void Damage(int) { ; }						//�_���[�W����

	static HRESULT Load(void);		//�e�N�X�`���ǂݍ���
	static void UnLoad(void);		//�e�N�X�`���j��
	static CFire *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//�쐬
	D3DXVECTOR3 *RockEnemy(void);	//�G�����b�N�I������
	void Homing(D3DXVECTOR3 pos);	//�ǔ�

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	D3DXVECTOR3 *m_pPos;					//�G��pos�̃|�C���^
	int m_nEnemy;							//���Ԗڂ̓G�����b�N�I�����邩
	int m_nEffect;							//�G�t�F�N�g�J�E���g
	float m_fRotY;							//�����Ă����
	bool m_bUninit;							//�폜���邩
	D3DXVECTOR3 m_move;						//�ړ����x
	int m_nLife;							//����
};

#endif