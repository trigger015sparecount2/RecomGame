//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

class CFade;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);	//������
	void Uninit(void);						//�I��
	void Update(void);						//�X�V
	void Draw(void);						//�`��
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
#ifdef _DEBUG
	void DrawFPS(void);	//�t���[�����[�g����
#endif

private:
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
	static CFade *m_pFade;							// �t�F�[�h�̃|�C���^
};

#endif