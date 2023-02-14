//=============================================================================
//
// ���f�� [model.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

class CModel
{
public:
	CModel();
	~CModel();
	HRESULT Init(const char *aModelName);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	void DrawObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�I�u�W�F�N�g�̕`��

	//�e���f���̊i�[�E�擾
	void SetParent(CModel *model) { m_pParent = model; }
	CModel *GetParent() { return m_pParent; }

	//�e���f���̔ԍ��̊i�[�E�擾
	void SetIdxParent(int nIdx) { m_nIdxModelParent = nIdx; }
	int GetIdxParent() { return m_nIdxModelParent; }

	//�}�g���b�N�X�̊i�[�E�擾
	D3DXMATRIX GetMatrix() { return m_mtxWorld; }
	void SetMatrix(D3DXMATRIX Matrix) { m_mtxWorld = Matrix; }

	//pos�̊i�[�E�擾
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos() { return m_pos; }

	//�����̊i�[�E�擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot() { return m_rot; }

	void SetOriPos(D3DXVECTOR3 pos) { m_posOri = pos; }	//���X��pos�ݒ�
	void SetOriRot(D3DXVECTOR3 rot) { m_rotOri = rot; }	//���X�̕����ݒ�
	D3DXVECTOR3 GetMinSize();	//�ŏ��̃T�C�Y
	D3DXVECTOR3 GetMaxSize();	//�ő�̃T�C�Y
	void Copy(CModel *pModel);	//���f���̃R�s�[

	static CModel *Create(const char *aModelName);	//�쐬

private:
	LPD3DXMESH m_pMesh;							//���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;					//�}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD m_nNumMat;							//�}�e���A���̐�
	LPDIRECT3DTEXTURE9 m_aTextureModel[4] = {};	//�e�N�X�`��
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_posOri;						//���X�̈ʒu
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_rotOri;						//���X�̌���
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	int m_nIdxModelParent;						//�e���f���̃C���f�b�N�X

	CModel *m_pParent;
};

#endif