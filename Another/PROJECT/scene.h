//=============================================================================
//
// �V�[������ [scene.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//�}�N����`
//#define POLYGON_SIZE (70.0f)
//#define PRIORITY (7)
//#define CIRCLE (float(rand() % 324) / 100.0f - float(rand() % 324) / 100.0f) //�~

class CScene
{
public:

	//�I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJECTTYPE_NONE = 0,
		OBJECTTYPE_UI,
		OBJECTTYPE_PLAYER,
		OBJECTTYPE_ENEMY,
		OBJECTTYPE_FIELD,
		OBJECTTYPE_WALL,
		OBJECTTYPE_BLOCK,
		OBJECTTYPE_MAX
	} OBJTYPE;

	//�����蔻��̎��
	typedef enum
	{
		COLLISION_SPHERE = 0,
		COLLISION_PALL,
		COLLISION_SQUARE,
		COLLISION_MAX
	} COLLISION;

	//�D�揇��
	typedef enum
	{
		PRIORITY_PLANE = 0,
		PRIORITY_OBJECT,
		PRIORITY_CHARA,
		PRIORITY_EFFECT,
		PRIORITY_ORBIT,
		PRIORITY_UIEFFECT,
		PRIORITY_UI,
		PRIORITY_PAUSEUI,
		PRIORITY_MAX
	} PRIORITY;

	CScene(PRIORITY Priority);
	virtual ~CScene();
	virtual HRESULT Init(D3DXVECTOR3 pos) = 0;	//������
	virtual void Uninit() = 0;				//�I��
	virtual void Update() = 0;				//�X�V
	virtual void Draw() = 0;				//�`��

	virtual OBJTYPE GetObjType() = 0;		//���
	virtual D3DXVECTOR3 GetPos() = 0;		//�ꏊ�擾
	virtual D3DXVECTOR3 GetRot() = 0;		//�����擾
	virtual float GetRadius() = 0;			//���a�擾
	virtual float GetHeight() = 0;			//�����擾
	virtual COLLISION GetCollision() = 0;	//�����蔻��̎�ގ擾
	virtual D3DXVECTOR3 GetVtxMax() = 0;	//�ő�̑傫���擾
	virtual D3DXVECTOR3 GetVtxMin() = 0;	//�ŏ��̑傫���擾
	virtual void Damage(int nDamage, D3DXVECTOR3 clash) = 0;	//�_���[�W����
	virtual bool GetRotX() = 0;	//�����ǂ̕����ɌX���Ă��邩
	virtual bool CollisionDamage(D3DXVECTOR3 pos, float fRadius, float fHeight) = 0;	//�_���[�W����Ƃ̓����蔻��
	virtual bool SetEnemy(CScene *pEnemy) = 0;	//�G�����X�g���ɓ����
	virtual int Damage() = 0;		//�_���[�W��
	virtual float VClash() = 0;		//���������̃m�b�N�o�b�N
	virtual float HClash() = 0;		//���������̃m�b�N�o�b�N
	virtual D3DXMATRIX GetMatrix(int nPart) = 0;	//���f���p�[�c�̃}�g���b�N�X
	virtual void SetParticle() = 0;	//�p�[�e�B�N�����
	virtual bool GetAttack() = 0;	//�U������
	virtual void Reflect() = 0;		//�K�[�h���ꂽ
	virtual int GetHP() = 0;		//����HP�擾
	virtual int GetMaxHP() = 0;		//�ő�HP�擾
	virtual CScene *GetNext() { return m_pNext; }	//���̃V�[���擾

	static CScene *GetScene(PRIORITY Priority) { return m_pTop[Priority]; }	//�ŏ��̃V�[���擾
	static void ReleaseAll();	//�S���폜
	static void UpdateAll();	//�X�V
	static void DrawAll();		//�`��

	//�폜�̊i�[�E�擾
	void SetDeath(bool bDeath) { m_bDeath = bDeath; }
	bool GetDeath() { return m_bDeath; }

private:
	static CScene *m_pTop[PRIORITY_MAX]; //�擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene *m_pCur[PRIORITY_MAX]; //����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev;       //�O�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pNext;       //���̃I�u�W�F�N�g�̃|�C���^

	static int m_nNumAll;	//�������I�u�W�F�N�g���邩
	bool m_bDeath;			//�폜���邩

	PRIORITY m_Priority;	//�D�揇��

protected:
	void Release();
};
#endif