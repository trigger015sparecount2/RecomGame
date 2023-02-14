//=============================================================================
//
// �v���C�Y���� [prize.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _PRIZE_H_
#define _PRIZE_H_

#include "main.h"
#include "scene2d.h"

#define PRIZE_SIZE (12.0f)

class CPrize : public CScene2D
{
public:
	CPrize(PRIORITY Priority = PRIORITY_BG);
	~CPrize();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, ELEMENT element, int nHeal);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool GetDamage(void) { return false; }
	void Damage(int) { ; }

	static HRESULT Load(void);
	static void UnLoad(void);
	static CPrize *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, ELEMENT element, int nHeal);

private:
	D3DXVECTOR3 m_move;		//�ړ����x
	D3DXVECTOR3 *m_pPos;	//�v���C���[�̏ꏊ�̃|�C���^
	float m_fRotY;			//�ŏ���юU�����
	float m_fSize;			//�傫��
	ELEMENT m_Element;		//����
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	int m_nTime;			//��������Ă���̎���
	int m_nHeal;			//�ǂꂾ�����͂��񕜂����邩
	bool m_bUninit;			//�폜���邩
};

#endif