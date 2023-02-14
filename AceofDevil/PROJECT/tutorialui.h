//=============================================================================
//
// UI���� [tutorialui.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _TUTORIALUI_H_
#define _TUTORIALUI_H_
#include "main.h"
#include "scene.h"

//�}�N����`
#define MAX_TUTOUI (3)
#define MAX_BYTE (256)

class CScene2D;

class CTutorialUi : public CScene
{
public:
	//�e�L�X�g�̃��[�h
	typedef enum
	{
		TEXTMODE_NONE = 0,
		TEXTMODE_IN,
		TEXTMODE_OUT,
		TEXTMODE_MAX
	} TEXTMODE;

	CTutorialUi(PRIORITY Priority = PRIORITY_UI);
	~CTutorialUi();
	HRESULT Init(float fWidth, float fHeight, D3DXVECTOR3 pos, float fTexSize);	//������
	void Uninit(void);						//�I��
	void Update(void);						//�X�V
	void Draw(void);						//�`��
	bool GetDamage(void) { return false; }	//�_���[�W�󂯂邩
	void Damage(int) { ; }					//�_���[�W����

	static bool GetClear(void) { return m_bClear; }							//���߂����邩
	static void NextText(void) { m_textmode = TEXTMODE_IN; }				//���̕��͂�\��������
	static void TutoClear(D3DXVECTOR3 pos, float fWidth, float fHeight);	//�`���[�g���A��UI�𓧉߂�����
	static void DrawTutoText(void);		//�`���[�g���A���̕��͂�\��������
	static HRESULT Load(void);			//�e�N�X�`���ǂݍ���
	static void UnLoad(void);			//�e�N�X�`���j��
	static CTutorialUi *Create(void);	//�쐬

private:
	void TextChange(void);						//���͂�ς���
	static int Compare(void);					//�e�L�X�g�̕����̔Z���Ǝl�p�`�̔Z���Ƃ��r�A�����ق���Ԃ�

	char m_aText[22][MAX_BYTE];					//�t�@�C������ǂݎ��������
	int m_nCntText;								//���Ԗڂ̕��͂�
	static bool m_bClear;						//UI��������
	static TEXTMODE m_textmode;					//���͂̃��[�h
	static char m_Str[MAX_BYTE];				//�\�������镶��
	static LPD3DXFONT m_pFont;					//�t�H���g
	static int m_nTextClear;					//�e�L�X�g�̓����x
	static int m_nSquareClear;					//�l�p�`�̓����x
	static LPDIRECT3DTEXTURE9 m_pTexture[2];	//�e�N�X�`���ւ̃|�C���^
	static CScene2D *m_apScene[MAX_TUTOUI];		//�V�[��
};

#endif