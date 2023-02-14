//=============================================================================
//
// �^�C�g����UI���� [titleui.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _TITLEUI_H_
#define _TITLEUI_H_
#include "main.h"
#include "scene.h"

class CScene2D;
class CTitleUi : public CScene
{
public:
	CTitleUi(PRIORITY Priority = PRIORITY_UI);
	~CTitleUi();
	HRESULT Init(float fWidth, float fHeight, D3DXVECTOR3 pos, float fTexSize);		//������
	void Uninit(void);						//�I��
	void Update(void);						//�X�V
	void Draw(void);						//�`��
	bool GetDamage(void) { return false; }	//�_���[�W�󂯂邩
	void Damage(int) { ; }					//�_���[�W����

	static HRESULT Load(void);		//�e�N�X�`���ǂݍ���
	static void UnLoad(void);		//�e�N�X�`���j��
	static CTitleUi *Create(void);	//�쐬

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[2];	//�e�N�X�`���ւ̃|�C���^
	static CScene2D *m_apScene[2];				//�V�[��
	bool m_bClear;								//�_���邩������
	float m_fClear;								//UI�̓����x
};

#endif