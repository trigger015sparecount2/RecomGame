//*****************************************************************************
// UI�֘A����(UI.h)
// Author : �����G��
//*****************************************************************************

#ifndef _UI_H_
#define _UI_H_

#include "Scene2D.h"

class CUI :public CScene2D
{
public:

	CUI(PRIORITY Priority);
	~CUI();

	HRESULT Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_UI; }	//���

	static CUI *Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col);	//�쐬
private:

	D3DXVECTOR3 m_pos;			//���݈ʒu
	D3DCOLORVALUE m_Color;		//�J���[
	bool m_bUninit;				//������


	//�傫�����
	float m_fSizeX;
	float m_fSizeY;

};
#endif