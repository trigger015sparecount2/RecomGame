//=============================================================================
//
// UI���� [ui.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"
#include "scene.h"

//�}�N����`
#define MAX_UIDATA (52)

class CScene2D;
class CUi : public CScene
{
public:
	CUi(PRIORITY Priority = PRIORITY_UI);
	~CUi();
	HRESULT Init(float fWidth, float fHeight, D3DXVECTOR3 pos, float fTexSize);	//������
	void Uninit(void);						//�I��
	void Update(void);						//�X�V
	void Draw(void);						//�`��
	bool GetDamage(void) { return false; }	//�_���[�W�󂯂邩
	void Damage(int) { ; }					//�_���[�W����

	static void SetLife(int nLife) { m_nLife = nLife; }	//�̗͐ݒ�
	static void SetScore(int nScore);					//�X�R�A�ݒ�
	static int GetScore(void) { return m_nScore; }		//�X�R�A�擾
	static void SetKill(void);							//���Đ��ݒ�
	static int GetKill(void) { return m_nKill; }		//���Đ��擾
	static void SetFireGauge(int nFire);				//�Α����Q�[�W�ݒ�
	static void SetIceGauge(int nIce);					//�X�����Q�[�W�ݒ�
	static void SetThunderGauge(int nThunder);			//�������Q�[�W�ݒ�
	static void SetWaterGauge(int nWater);				//�������Q�[�W�ݒ�
	static void SetWindGauge(int nWind);				//�������Q�[�W�ݒ�
	static void ChangeMagic(bool bPlus);				//���@�ς���
	static void KillClear(D3DXVECTOR3 pos, float fWidth, float fHeight);	//���Đ����߂�����
	static void ScoreClear(D3DXVECTOR3 pos, float fWidth, float fHeight);	//�X�R�A���߂�����
	static void MagicClear(D3DXVECTOR3 pos, float fWidth, float fHeight);	//���@���߂�����
	static void DMGClear(D3DXVECTOR3 pos, float fWidth, float fHeight);		//�_���[�W���߂�����
	static void Damage(void);							//�_���[�W����
	static HRESULT Load(void);							//�e�N�X�`���ǂݍ���
	static void UnLoad(void);							//�e�N�X�`���j��
	static CUi *Create(void);							//�쐬

private:
	bool m_bClear;								//���@UI�̓_��
	int m_nClearTime;							//���@UI�̓_�ł̎���
	static int m_nDamageTime;					//�v���C���[���_���[�W������Ă���̎���
	static int m_nLife;							//�v���C���[�̗̑�
	static int m_nKill;							//���Đ�
	static int m_nScore;						//�X�R�A
	static int m_nType;							//�����̎��
	static float m_fClear[4];					//UI4��̓����x
	static D3DXVECTOR3 m_apos[5];				//�ꏊ
	static LPDIRECT3DTEXTURE9 m_pTexture[23];	//�e�N�X�`���ւ̃|�C���^
	static CScene2D *m_apScene[MAX_UIDATA];		//�V�[��
};

#endif