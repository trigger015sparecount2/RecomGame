//=============================================================================
//
// �������e���� [wind.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _WIND_H_
#define _WIND_H_
#include "main.h"
#include "scene2d.h"

//�}�N����`
#define WIND_SIZE (200.0f)
#define WIND_MAX_ENEMY (16)

class CWind : public CScene2D
{
public:
	CWind(PRIORITY Priority = PRIORITY_BULLET);
	~CWind();
	HRESULT Init(D3DXVECTOR3 pos);					//������
	void Uninit(void);								//�I��
	void Update(void);								//�X�V
	void Draw(void);								//�`��
	bool GetDamage(void) { return false; }			//�_���[�W�󂯂邩
	void Damage(int) { ; }							//�_���[�W����
	void SetSize(bool bWind) { m_bSize = bWind; }	//�傫���ݒ�

	static HRESULT Load(void);				//�e�N�X�`���ǂݍ���
	static void UnLoad(void);				//�e�N�X�`���j��
	static CWind *Create(D3DXVECTOR3 pos);	//�쐬

private:
	bool EnemyList(int nEnemy);	//�ǂ̓G�ɓ��������̂����X�g�����Q��
	void ListPush(int nEnemy);	//���X�g�ɓ����

	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	D3DXVECTOR3 *m_pPlayerpos;				//�v���C���[��pos�̃|�C���^
	float m_fRotY;							//����
	float m_fSize;							//�傫��
	bool m_bSize;							//���������邩
	int m_nListCnt;							//���X�g�̉��Ԗڂɕۑ����邩
	int m_aEnemies[WIND_MAX_ENEMY];			//�G�̃��X�g
	bool m_bDraw;							//�`�悷�邩
};
#endif