//=============================================================================
//
// �J�������� [camera.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

class CKeyboard;
class CMouse;
class CScene;

class CCamera
{
public:
	//�J�����̍\����
	typedef struct
	{
		D3DXVECTOR3 posV;		//���݂̎��_
		D3DXVECTOR3 posVDest;	//�ړI�̎��_
		D3DXVECTOR3 posR;		//���݂̒����_
		D3DXVECTOR3 posRDest;	//�ړI�̒����_
		D3DXVECTOR3 vecU;		//������x�N�g��
		D3DXVECTOR3 rot;		//�J�����̌���
		D3DXVECTOR3 rotDesh;    //�J�����̖ړI����
		float fLength;
		D3DXMATRIX mtxProjection; //�v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView; //�r���[�}�g���b�N�X
		bool bRot[2];			//X��Y
		bool bAdd[2];			//X��Y
	} Camera;

	CCamera();
	~CCamera();
	HRESULT Init(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V

	float GetRotY() { return m_camera.rot.y; }	//Y�̌����擾
	float GetRotX() { return m_camera.rot.x; }	//X�̌����擾
	void SetPosV(D3DXVECTOR3 pos);	//���_�ݒ�
	void SetPosR(D3DXVECTOR3 pos);	//�����_�ݒ�
	void SetRot(D3DXVECTOR3 rot) { m_camera.rot = rot; }			//�����ݒ�
	void SetLength(float fLength) { m_camera.fLength = fLength; }	//�����ݒ�
	D3DXVECTOR3 GetPosR() { return m_camera.posR; }	//���݂̒����_�擾
	D3DXVECTOR3 GetPosV() { return m_camera.posV; }	//���݂̎��_�擾
	void AddRotY(float fRotY);	//Y�������Z
	void AddRotX(float fRotX);	//X�������Z
	void MoveX(float fMove);	//X�ړ�
	void MoveZ(float fMove);	//Y�ړ�
	void ResetRot();			//�������Z�b�g
	void SetRockon(bool bRock) { m_bRockon = bRock; }			//���b�N�I���ݒ�
	void SetPlayer(CScene *pPlayer) { m_pPlayer = pPlayer; }	//�v���C���[�̃|�C���^�ݒ�
	void SetEnemy(CScene *pEnemy) { m_pEnemy = pEnemy; }		//���b�N�I���̓G�̃|�C���^�ݒ�
	void SetRotDeshX(float fRotX);	//�ړI�̌���X�ݒ�
	void SetRotDeshY(float fRotY);	//�ړI�̌���Y�ݒ�
	void SetAdd(bool bAdd);			//�J�����̌������Z�����邩�ݒ�
	void AddLength(float fLength) { m_camera.fLength += fLength; }	//�������Z

	static CCamera *Create(D3DXVECTOR3 ref, float fDistance, D3DXVECTOR3 pos);	//�쐬

private:
	Camera m_camera;	//�J�����̏��
	bool m_bRockon;		//���b�N�I�����邩
	CScene *m_pPlayer;	//�v���C���[�̃|�C���^
	CScene *m_pEnemy;	//�G�̃|�C���^
};

#endif