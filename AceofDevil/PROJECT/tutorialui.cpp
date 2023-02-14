//=============================================================================
//
// �`���[�g���A��UI���� [tutorialui.h]
// Author : �O��q��
//
//=============================================================================
#include "tutorialui.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "fade.h"

//�}�N����`
#define TEXTFILENAME "data/FILE/tutorial.txt"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CTutorialUi::m_pTexture[2] = {};
CScene2D *CTutorialUi::m_apScene[MAX_TUTOUI] = {};
int CTutorialUi::m_nTextClear = 0;
int CTutorialUi::m_nSquareClear = 0;
LPD3DXFONT CTutorialUi::m_pFont = NULL;
char CTutorialUi::m_Str[MAX_BYTE] = {};
CTutorialUi::TEXTMODE CTutorialUi::m_textmode = CTutorialUi::TEXTMODE_NONE;
bool CTutorialUi::m_bClear = false;

CTutorialUi::CTutorialUi(PRIORITY Priority) : CScene::CScene(Priority)
{

}

CTutorialUi::~CTutorialUi(void)
{

}

//������
HRESULT CTutorialUi::Init(float, float, D3DXVECTOR3, float)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//�`���[�g���A���t�@�C�����[�h
	FILE *pFile;
	int nCount;
	pFile = fopen(TEXTFILENAME, "r");
	if (pFile != NULL)
	{
		for (nCount = 0; nCount < 22; nCount++)
		{
			fgets(&m_aText[nCount][0], MAX_BYTE, pFile);
			//fscanf(pFile, "%s", &m_aText[nCount][0]);
		}
		fclose(pFile);
	}

	int nCntLife = 0;
	//���Đ��l�p
	//�[
	m_apScene[nCntLife] = CScene2D::Create(14.0f, 40.0f, D3DXVECTOR3(355.0f, 40.0f, 0.0f), PRIORITY_UI);
	m_apScene[nCntLife]->BindTexture(m_pTexture[0]);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	nCntLife++;
	//�^��
	m_apScene[nCntLife] = CScene2D::Create(390.0f, 40.0f, D3DXVECTOR3(640.0f, 40.0f, 0.0f), PRIORITY_UI);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	m_apScene[nCntLife]->BindTexture(m_pTexture[1]);
	nCntLife++;
	//�[
	m_apScene[nCntLife] = CScene2D::Create(14.0f, 40.0f, D3DXVECTOR3(925.0f, 40.0f, 0.0f), PRIORITY_UI);
	m_apScene[nCntLife]->BindTexture(m_pTexture[0]);
	m_apScene[nCntLife]->SetRot(1.0f);
	m_apScene[nCntLife]->ChangeColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	m_apScene[nCntLife]->Set(14.0f, 40.0f, D3DXVECTOR3(925.0f, 40.0f, 0.0f));
	nCntLife++;
	m_nTextClear = 255;
	m_nSquareClear = 255;
	m_nCntText = -1;
	m_textmode = TEXTMODE_NONE;
	m_bClear = false;

	TextChange();
	D3DXCreateFont(pDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "PixelMplus10", &m_pFont);
	
	return S_OK;
}

//�I��
void CTutorialUi::Uninit(void)
{
	int nCntScene;
	for (nCntScene = 0; nCntScene < MAX_TUTOUI; nCntScene++)
	{
		if (m_apScene[nCntScene] != NULL)
		{
			m_apScene[nCntScene] = NULL;
		}
	}
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
	Release();
}

//�X�V
void CTutorialUi::Update(void)
{
	if (m_textmode != TEXTMODE_NONE)
	{
		//�����̐F�����X�ɔZ������
		if (m_textmode == TEXTMODE_IN)
		{
			m_nTextClear += 25;
			if (m_nTextClear >= 255)
			{
				m_nTextClear = 255;
				m_textmode = TEXTMODE_NONE;
			}
		}
		//�����̐F�����X�ɔ�������
		else if (m_textmode == TEXTMODE_OUT)
		{
			m_nTextClear -= 25;
			if (m_nTextClear <= 0)
			{
				TextChange();
			}
		}
	}
}

//�`��
void CTutorialUi::Draw(void)
{
	
}

//�e�N�X�`���ǂݍ���
HRESULT CTutorialUi::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/squareside.png",
		&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/squarecenter.png",
		&m_pTexture[1]);
	return S_OK;
}

//�e�N�X�`���j��
void CTutorialUi::UnLoad(void)
{
	int nCntLife;
	for (nCntLife = 0; nCntLife < 2; nCntLife++)
	{
		if (m_pTexture[nCntLife] != NULL)
		{
			m_pTexture[nCntLife]->Release();
			m_pTexture[nCntLife] = NULL;
		}
	}
}

//�쐬
CTutorialUi *CTutorialUi::Create(void)
{
	CTutorialUi *pTutoUi;
	pTutoUi = new CTutorialUi(PRIORITY_UI);
	if (pTutoUi != NULL)
	{
		pTutoUi->Init(0.0f, 0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);
	}
	return pTutoUi;
}

//�`���[�g���A���̕��͕\��
void CTutorialUi::DrawTutoText(void)
{
	RECT rect = { SCREEN_WIDTH / 2 - 280, 20, SCREEN_WIDTH / 2 + 280, 60 };

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, &m_Str[0], -1, &rect, DT_WORDBREAK, D3DCOLOR_ARGB(CTutorialUi::Compare(), 0, 255, 0));
}

//�e�L�X�g�ς���
void CTutorialUi::TextChange(void)
{
	m_nCntText++;
	m_nTextClear = 0;
	if (m_nCntText < 11)
	{
		//�܂������񂪂���ꍇ�A������ύX
		m_textmode = TEXTMODE_IN;
		memset(&m_Str[0], 0, sizeof(m_Str));
		memcpy(&m_Str[0], &m_aText[m_nCntText * 2][0], strlen(m_aText[m_nCntText * 2]));
		memcpy(&m_Str[strlen(m_Str)], &m_aText[m_nCntText * 2 + 1][0], strlen(m_aText[m_nCntText * 2 + 1]));
	}
	else
	{
		//�����񂪂Ȃ��ꍇ�A�Q�[���ɑJ��
		m_textmode = TEXTMODE_NONE;
		CFade::SetFade(CManager::MODE_GAME);
	}
}

//�`���[�g���A���𓧖��ɂ���
void CTutorialUi::TutoClear(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�v���C���[���l�p�`�ɓ������Ă�����
	if (pos.x - fWidth <= 925.0f + 14.0f * sinf(0.25f * D3DX_PI) && 355.0f - 14.0f * sinf(0.25f * D3DX_PI) <= pos.x + fWidth &&
		pos.y - fHeight <= 40.0f + 40.0f * cosf(0.25f * D3DX_PI) && 40.0f - 40.0f * cosf(0.25f * D3DX_PI) <= pos.y + fHeight)
	{
		//UI�𔖂����Ă���
		if (m_bClear == false)
		{
			m_bClear = true;
		}
		if (m_nSquareClear > 75)
		{
			m_nSquareClear -= 25;
			if (m_nSquareClear <= 75)
			{
				m_nSquareClear = 75;
			}
			int nCntTuto;
			for (nCntTuto = 0; nCntTuto < 3; nCntTuto++)
			{
				m_apScene[nCntTuto]->ChangeColor(D3DCOLOR_RGBA(0, 255, 0, m_nSquareClear));
			}
		}
	}
	//�v���C���[���l�p�`�ɓ������Ă��Ȃ�������
	else
	{
		//UI��Z�����Ă���
		if (m_bClear == true)
		{
			m_bClear = false;
		}
		if (m_nSquareClear < 255)
		{
			m_nSquareClear += 25;
			if (m_nSquareClear >= 255)
			{
				m_nSquareClear = 255;
			}
			int nCntTuto;
			for (nCntTuto = 0; nCntTuto < 3; nCntTuto++)
			{
				m_apScene[nCntTuto]->ChangeColor(D3DCOLOR_RGBA(0, 255, 0, m_nSquareClear));
			}
		}
	}
}

//�e�L�X�g�̕����̔Z���Ǝl�p�`�̔Z���Ƃ��r�A�����ق���Ԃ�
int CTutorialUi::Compare(void)
{
	if (m_nSquareClear >= m_nTextClear)
	{
		return m_nTextClear;
	}
	return m_nSquareClear;
}