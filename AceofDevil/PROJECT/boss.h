//=============================================================================
//
// �{�X���� [boss.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"
#include "scene2d.h"

class CBoss : public CScene2D
{
public:
	CBoss(PRIORITY Priority = PRIORITY_CHARA);
	~CBoss();
	HRESULT Init(void);			//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����
	void Draw(void);			//�`�揈��
	bool GetDamage(void);		//�_���[�W���󂯂邩
	void Damage(int);			//�_���[�W����

	static HRESULT Load(void);	//�e�N�X�`���ǂݍ���
	static void UnLoad(void);	//�e�N�X�`���j��
	static CBoss *Create(void);	//�쐬

private:
	void Move(D3DXVECTOR3 pos);				//�ړ�����
	void Shot(D3DXVECTOR3 pos);				//�e����
	float SearchPlayer(D3DXVECTOR3 pos);	//�v���C���[��������

	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	D3DXVECTOR3 m_move;						//�ړ���
	CScene2D *m_pShadowScene;				//�e
	int m_nBullet;							//�e���˃J�E���g
	int m_nBulletInter;						//�e���˃J�E���g�̍ő�
	int m_nHP;								//�̗�
	int m_nDamageTime;						//�_���[�W��H����Ă���̎���
	bool m_bUninit;							//�폜���邩
	bool m_bSlide;							//���j��̍��E�̂Ԃ�
	bool m_bDrop;							//�o�ꎞ�̏ォ��o�Ă��邩
	bool m_bLeft;							//�Α����̒e�����Ƃ��A���E�ɐU��
	int m_nSlide;							//���j��̍��E�̂Ԃ�̃J�E���g
	int m_nScore;							//�X�R�A
	int m_nDTime;							//���j��̔����G�t�F�N�g
	int m_nCntBullet;						//�Α����̒e�����Ƃ��̃J�E���g
	int m_nCycle;							//�U�����̃T�C�N��(���������ŉ���e�𔭎˂��邩)
	int m_nBTime;							//�e���ˎ��̎��e���܂ł̃J�E���g
	int m_nType;							//�������̒e������
	float m_fScale;							//�傫��
	float m_fRotY;							//�v���C���[�̌���
};
#endif