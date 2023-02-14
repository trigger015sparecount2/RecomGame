//=============================================================================
//
// �w�i���� [bg.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_
#include "main.h"
#include "scene.h"
class CScene2D;
class CBg : public CScene
{
public:
	CBg(PRIORITY Priority = PRIORITY_BG);
	~CBg();
	HRESULT Init(float fWidth, float fHeight, D3DXVECTOR3 pos, float fTexSize);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool GetDamage(void) { return false; }
	void Damage(int) { ; }
	
	static HRESULT Load(void);			//�e�N�X�`���ǂݍ���
	static void UnLoad(void);			//�e�N�X�`���j��
	static CBg *Create(bool bScroll);	//�쐬

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	CScene2D *m_apScene;					//�V�[��
	float m_fTexY;							//�ǂꂾ���X�N���[�������Ă��邩
	static bool m_bScroll;					//�X�N���[�������邩
};

#endif