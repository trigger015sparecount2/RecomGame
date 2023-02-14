//=============================================================================
//
// ���b�N�I������ [rockon.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _ROCKON_H_
#define _ROCKON_H_

#include "main.h"
#include "ui.h"

class CRockon : public CUI
{
public:
	CRockon(PRIORITY Priority);
	~CRockon();
	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	
	void SetRockon(CScene *pScene);			//���b�N�I������
	void RemoveRockon(void);				//���b�N�I������
	bool GetRockon() { return m_bScreen; }	//�f���Ă��邩

	CScene *GetRockEnemy() { return m_pScene; }	//���b�N�I�����Ă�G�擾

	static CRockon *Create();	//�쐬

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`��
	CScene *m_pScene;	//���b�N�I������G
	float m_fHeight;	//�G��pos����ǂ̂��炢�̍����ɕ`�悷�邩
	bool m_bUse;		//�g���Ă��邩
	bool m_bScreen;		//�f�邩
};

#endif