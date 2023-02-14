//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2d.h"

#define MAX_TYPE (5)

class CInputKeyboard;
class CInputGamePad;
class CWater;
class CWind;

class CPlayer : public CScene2D
{
public:
	CPlayer(PRIORITY Priority = PRIORITY_CHARA);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit(void);				//�I��
	void Update(void);				//�X�V
	void Draw(void);				//�`��
	bool GetDamage(void);			//�_���[�W���󂯂邩
	void Damage(int nDamage);		//�_���[�W����

	static HRESULT Load(void);								//�e�N�X�`���ǂݍ���
	static void UnLoad(void);								//�e�N�X�`���j��
	static CPlayer *Create(D3DXVECTOR3 pos);				//�쐬
	static void GetPrize(int nType, int nHeal);				//�v���C�Y�擾
	static bool GetGameOver(void) { return m_bDeath; }		//�Q�[���I�[�o�[��
	static void SetTuto(bool bTuto) { m_bTuto = bTuto; }	//�`���[�g���A�����ݒ�

private:
	void Move(float fRot);			//�ړ�
	void Stop(void);				//�~�܂�
	int SetBulletTime(int nType);	//���Ɍ��܂ł̃C���^�[�o���̐ݒ�
	void SetGauge(void);			//���͂̃Q�[�W�ݒ�
	void Shot(D3DXVECTOR3 pos);		//����

	CInputKeyboard *m_pInputKeyboard;		//�L�[�{�[�h�̃|�C���^
	CInputGamePad *m_pInputGamePad;			//�Q�[���p�b�h�̃|�C���^
	CWater *m_pWater;						//���̃|�C���^
	CWind *m_pWind;							//���̃|�C���^
	D3DXVECTOR3 m_move;						//�ړ����x
	D3DXVECTOR3 m_Maxmove;					//�ő�ړ����x
	CScene2D *m_pShadowScene;				//�e
	int m_nBullet;							//�e�����Ă���̃J�E���^
	int m_nBulletTime;						//���ˊԊu
	int m_nHP;								//�̗�
	int m_nDamageTime;						//���G����
	int m_nDTime;							//�_���[�W��H����Ă���̎���
	int m_nType;							//�U���̎��
	int m_nMagicTime;						//���͂̉񕜂̊Ԋu
	int m_nSlide;							//���ꂽ�Ƃ��A�U������J�E���g
	bool m_bSlide;							//���ꂽ�Ƃ��A���E�ǂ����ɐU�����邩
	float m_fScale;							//�傫��
	bool m_bUse;							//���������g���Ă邩
	static bool m_bDeath;					//�Q�[���I�[�o�[��
	static int m_aResource[MAX_TYPE];		//���͂̃��\�[�X
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	static bool m_bTuto;					//�`���[�g���A����
};

#endif