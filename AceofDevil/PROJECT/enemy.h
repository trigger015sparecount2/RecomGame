//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene2d.h"

#define ENEMY_SIZE (50.0f)

class CEnemy : public CScene2D
{
public:
	CEnemy(PRIORITY Priority = PRIORITY_CHARA);
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, int nType, float fRotY, int ninterval, float fSpeed);	//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��
	bool GetDamage(void) { return true; }	//�_���[�W���󂯂邩
	void Damage(int nDamage);				//�_���[�W����

	static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
	static void UnLoad(void);	//�e�N�X�`���j��
	static CEnemy *Create(D3DXVECTOR3 pos, int nTexType, float fRotY, int nInterval, float fSpeed);	//�쐬

private:
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);			//�ړ�����
	void Shot(D3DXVECTOR3 pos);					//�e����

	static LPDIRECT3DTEXTURE9 m_pTexture[4];	//�e�N�X�`��
	CScene2D *m_pShadowScene;					//�e
	int m_nBullet;								//�e���˃J�E���g
	int m_nBulletInter;							//�e���˃J�E���g�̍ő�
	int m_nHP;									//�̗�
	int m_nDamageTime;							//�_���[�W��H����Ă���̎���
	bool m_bUninit;								//�폜���邩
	bool m_bShot;								//��������
	float m_fSpeed;								//�ړ����x
	float m_fRot;								//�����Ă����
	int m_nScore;								//�X�R�A
	int m_nType;								//����

};
#endif