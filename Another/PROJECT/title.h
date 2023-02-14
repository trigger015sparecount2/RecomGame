//=============================================================================
// �^�C�g���Ǘ�[Title.h]
// Author : �����G��
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "manager.h"
#include "Scene.h"

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CGamePad;
class CUI;

class CTitle : public CScene
{
public:
	CTitle(PRIORITY Priority);
	~CTitle();

	HRESULT Init(D3DXVECTOR3 pos);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	//��--------�g��Ȃ�---------��
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	//void SetPos(D3DXVECTOR3) { ; }
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
	D3DXMATRIX GetMatrix(int) { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }
	//��--------�g��Ȃ�---------��

	static CTitle *Create();	//�쐬
private:
	CKeyboard *m_pKeyboard;	//�L�[�{�[�h
	CGamePad *m_pGamePad;	//�Q�[���p�b�h
	CUI *m_pUI;				//UI
	float m_fClear;			//�����x
	bool m_bClear;			//�������邩�Z�����邩
	bool m_bButton;			//�{�^����������
	D3DXVECTOR2 m_size;		//�T�C�Y
};

#endif // _TITLE_H_
