//=============================================================================
//�|�[�YUI�Ǘ�[pauseui.h]
// Author : �O��@�q��
//=============================================================================
#ifndef _PAUSEUI_H_
#define _PAUSEUI_H_

#include "ui.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CPauseUI : public CUI
{
public:
	CPauseUI(PRIORITY Priority);
	~CPauseUI();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	static CPauseUI *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col);	//�쐬

private:
	
};

#endif
