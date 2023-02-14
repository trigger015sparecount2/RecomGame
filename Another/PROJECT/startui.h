//=============================================================================
//�J�nUI�Ǘ�[startui.h]
// Author : �O��@�q��
//=============================================================================
#ifndef _STARTUI_H_
#define _STARTUI_H_

#include "ui.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CStartUI : public CUI
{
public:
	CStartUI(PRIORITY Priority);
	~CStartUI();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col, int nUIType);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CStartUI *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col, int nUIType);	//�쐬

private:
	int m_nUIType;		//UI�̎��
	int m_nTime;		//�쐬���Ă���̃J�E���g
	bool m_bStop;		//�~�߂�
	int m_nFade;		//�����x
	D3DXVECTOR2 size;	//�T�C�Y
};

#endif
