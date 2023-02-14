//=============================================================================
//
// �󏈗� [sky.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SKY_H_
#define _SKY_H_

#include "main.h"
#include "scene.h"

class CSky : public CScene
{
public:
	CSky(PRIORITY Priority);
	~CSky();
	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��

	//��--------�g��Ȃ�---------��
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	//void SetPos(D3DXVECTOR3) { ; }
	D3DXVECTOR3 GetPos() { return m_pos; }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	float GetRadius() { return 0.0f; }
	float GetHeight() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void Damage(int, D3DXVECTOR3) { ; }
	bool GetRotX() { return false; }
	bool CollisionDamage(D3DXVECTOR3, float, float) { return false; }
	bool SetEnemy(CScene *pEnemy) { return false; }
	int Damage() { return 0; }
	float HClash() { return 0.0f; }
	float VClash() { return 0.0f; }
	void SetParticle() { ; }
	bool GetAttack() { return false; }
	void Reflect() { ; }
	int GetHP() { return 0; }
	int GetMaxHP() { return 0; }
	D3DXMATRIX GetMatrix(int) { return m_mtxWorld; }
	//��--------�g��Ȃ�---------��

	void SetTexture(LPDIRECT3DTEXTURE9 *pTexture) { m_pTexture = *pTexture; }			//�e�N�X�`���i�[
	void SetScroll(float fScroll) { m_fScroll = fScroll; }								//�X�N���[���̑����i�[
	static CSky *Create(D3DXVECTOR3 pos, float fScroll, LPDIRECT3DTEXTURE9 *Texture);	//�쐬

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//�C���f�b�N�X�o�b�t�@
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;	//�ꏊ
	D3DXVECTOR3 m_rot;	//����
	float m_fScroll;	//�X�N���[���̑���
};

#endif