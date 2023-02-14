//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

class CCamera;
class CFade;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);		//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }	//�f�o�C�X�擾
	CCamera *GetCamera() { return m_pCamera; }	//�J�����擾

#ifdef _DEBUG
	void DrawFPS();
#endif

private:
	LPDIRECT3D9				m_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT				m_pFont = NULL;			// �t�H���g�ւ̃|�C���^
	static CCamera *m_pCamera;						//�J����
	static CFade *m_pFade;							//�t�F�[�h
};

#endif