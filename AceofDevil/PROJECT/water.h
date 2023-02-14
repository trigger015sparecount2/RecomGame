//=============================================================================
//
// �������e���� [water.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _WATER_H_
#define _WATER_H_

#include "main.h"
#include "scene2d.h"

//�}�N����`
#define WATER_SIZE (240.0f)
#define WATER_MAX_ENEMY (16)

class CWater : public CScene2D
{
public:
	CWater(PRIORITY Priority = PRIORITY_BG);
	~CWater();
	HRESULT Init(D3DXVECTOR3 pos);				//������
	void Uninit(void);							//�I��
	void Update(void);							//�X�V
	void Draw(void);							//�`��
	bool GetDamage(void) { return false; }		//�_���[�W�󂯂邩
	void Damage(int) { ; }						//�_���[�W����
	void SetUninit(void) { m_bSize = false; }	//���������Ă���
	void SetRotDesh(float fRotDeshY);			//�����ݒ�
	
	static HRESULT Load(void);				//�e�N�X�`���ǂݍ���
	static void UnLoad(void);				//�e�N�X�`���j��
	static CWater *Create(D3DXVECTOR3 pos);	//�쐬

private:
	bool EnemyList(int nEnemy);	//�ǂ̓G�ɓ��������̂����X�g�����Q��
	void ListPush(int nEnemy);	//���X�g�ɓ����

	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	D3DXVECTOR3 *m_pPlayerpos;				//�v���C���[��pos�̃|�C���^
	float m_fRotY;							//����
	float m_fRotDeshY;						//�ړI�̌���
	float m_fSize;							//�傫��
	bool m_bSize;							//�傫�����邩
	int m_nListCnt;							//���X�g�̉��Ԗڂɕۑ����邩
	int m_aEnemies[WATER_MAX_ENEMY];		//�G�̃��X�g
	bool m_bDraw;							//�`�悷�邩
};

#endif