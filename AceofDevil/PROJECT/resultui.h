//=============================================================================
//
// ���U���g��UI���� [resultui.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _RESULTUI_H_
#define _RESULTUI_H_
#include "main.h"
#include "scene.h"

class CScene2D;
class CInputKeyboard;
class CInputGamePad;

class CResultUi : public CScene
{
public:
	CResultUi(PRIORITY Priority = PRIORITY_UI);
	~CResultUi();
	HRESULT Init(float, float, D3DXVECTOR3, float);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool GetDamage(void) { return false; }
	void Damage(int) { ; }

	static HRESULT Load(void);			//�e�N�X�`���ǂݍ���
	static void UnLoad(void);			//�e�N�X�`���j��
	static CResultUi *Create(void);		//�쐬

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[12];	//�e�N�X�`���ւ̃|�C���^
	static CScene2D *m_apScene[100];			//�V�[��
	CInputKeyboard *m_pInputKeyboard;			//�L�[�{�[�h�̃|�C���^
	CInputGamePad *m_pInputGamePad;				//�Q�[���p�b�h�̃|�C���^
	int m_nTime;		//����
	bool m_bClear;		//�_�Ŏ��A���_���邩������
	float m_fClear;		//������̔Z��
	int m_nClearTime;	//���ʂ̓_�ł̎���
	int m_nKillRank;	//����̌��Đ��̃����L���O����
	int m_nScoreRank;	//����̃X�R�A�̃����L���O����
	bool m_bRankClear;	//���ʂ̓_�ŁA���_���邩������
};

#endif