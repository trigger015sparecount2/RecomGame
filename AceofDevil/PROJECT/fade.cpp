//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : �O��q��
//
//=============================================================================
#include "fade.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"
#include "sound.h"

//�ÓI�����o�ϐ�
CManager::MODE CFade::m_mode = CManager::MODE_TITLE;
CFade::FADE CFade::m_fade = CFade::FADE_IN;

CFade::CFade(void)
{

}

CFade::~CFade(void)
{

}

//������
HRESULT CFade::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// ���_����ݒ�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	m_FadeColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = m_FadeColor;
	pVtx[1].col = m_FadeColor;
	pVtx[2].col = m_FadeColor;
	pVtx[3].col = m_FadeColor;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//�I��
void CFade::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//�X�V
void CFade::Update(void)
{
	//�t�F�[�h�𓮂����Ă�����
	if (m_fade != FADE_NONE)
	{
		//�t�F�[�h�C����������
		if (m_fade == FADE_IN)
		{
			//��������
			m_FadeColor.a -= 0.04f;
			if (m_FadeColor.a <= 0.0f)
			{
				m_FadeColor.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		//�t�F�[�h�A�E�g��������
		else if (m_fade == FADE_OUT)
		{
			//�Z������
			m_FadeColor.a += 0.04f;
			if (m_FadeColor.a >= 1.0f)
			{
				m_FadeColor.a = 1.0f;
				m_fade = FADE_IN;
				//���[�h�̐ݒ�
				CSound::Stop();
				CManager::SetMode(m_mode);
			}
		}

		VERTEX_2D *pVtx; //���_���ւ̃|�C���^
		m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);
		pVtx[0].col = m_FadeColor;
		pVtx[1].col = m_FadeColor;
		pVtx[2].col = m_FadeColor;
		pVtx[3].col = m_FadeColor;
		m_pVtxBuff->Unlock();
	}
}

//�`��
void CFade::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);  //���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetTexture(0, NULL);    //�e�N�X�`���̐ݒ�

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,  //�J�n����n�_�̃C���f�b�N�X
		2); //�`�悷��v���~�e�B�u��
}

//�t�F�[�h�J�n
void CFade::SetFade(CManager::MODE modenext)
{
	m_fade = FADE_OUT;
	m_mode = modenext;
}