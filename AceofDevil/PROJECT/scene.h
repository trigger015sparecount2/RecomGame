//=============================================================================
//
// �V�[������ [scene.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"
#define POLYGON_WIDTH (60.0f)
#define POLYGON_HEIGHT (70.0f)
#define MAX_POLYGON (256)
class CScene
{
public:
	//�I�u�W�F�N�g�^�C�v
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_BULLET,
		OBJTYPE_EXPLOSION,
		OBJTYPE_LIFE,
		OBJTYPE_SHADOW,
		OBJTYPE_PRIZE,
		OBJTYPE_MAX
	}OBJTYPE;

	//�`�揇
	typedef enum
	{
		PRIORITY_BG = 0,
		PRIORITY_EFFECT,
		PRIORITY_BULLET,
		PRIORITY_CHARA,
		PRIORITY_UI,
		PRIORITY_MAX
	} PRIORITY;

	//����
	typedef enum
	{
		ELEMENT_FIRE = 0,
		ELEMENT_ICE,
		ELEMENT_THUNDER,
		ELEMENT_WATER,
		ELEMENT_WIND,
		ELEMENT_MAX
	} ELEMENT;

	//�e�̎��
	typedef enum
	{
		SHADOW_F_15S_MTD = 0,
		SHADOW_F_14,
		SHADOW_MIG_31,
		SHADOW_F_35,
		SHADOW_F_2,
		SHADOW_RAFALE,
		MAX_SHADOW
	}SHADOW;


	CScene(PRIORITY Priority);
	virtual ~CScene();
	virtual HRESULT Init(float fWidth, float fHeight, D3DXVECTOR3 pos, float fTexSize) = 0;	//������
	virtual void Uninit(void) = 0;			//�I��
	virtual void Update(void) = 0;			//�X�V
	virtual void Draw(void) = 0;			//�`��
	virtual bool GetDamage(void) = 0;		//�_���[�W�󂯂邩
	virtual void Damage(int nDamage) = 0;	//�_���[�W����

	void SetElement(ELEMENT element) { m_Element = element; }
	ELEMENT GetElement(void) { return m_Element; }
	void SetObjType(OBJTYPE objType) { m_objType = objType; }
	OBJTYPE GetObjType(void) { return m_objType; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetEnemy(bool bEnemy) { m_bEnemy = bEnemy; }
	bool GetEnemy(void) { return m_bEnemy; }
	CScene *GetNext(void) { return m_pNext; }

	static bool GetbEnemy(int nEnemy);	//�G�����݂��Ă邩�_���[�W���󂯂�
	static D3DXVECTOR3 *GetPointerPos(int nCntScene) { return &m_apScene[PRIORITY_CHARA][nCntScene]->m_pos; }	//pos�̃|�C���^�Ԃ�
	static D3DXVECTOR3 *GetPlayerPos(void);	//�v���C���[��pos�̃|�C���^�Ԃ�
	static CScene *GetScene(PRIORITY Priority, int nCntScene) { return m_apScene[Priority][nCntScene]; }
	//static CScene *GetScene(PRIORITY Priority) { return m_apScene[Priority][0]; }
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

private:
	static CScene *m_apScene[PRIORITY_MAX][MAX_POLYGON];	//�V�[���S��
	static CScene *m_pTop[PRIORITY_MAX];	//�擪�̃I�u�W�F�N�g�̃|�C���^
	static CScene *m_pCur[PRIORITY_MAX];	//����(��Ԍ��)�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev;		//�O�̃I�u�W�F�N�g�̃|�C���^
	CScene *m_pNext;		//���̃I�u�W�F�N�g�̃|�C���^
	static int m_nNumAll;	//�I�u�W�F�N�g���ǂꂾ�����邩
	OBJTYPE m_objType;		//�I�u�W�F�N�g�̎��
	D3DXVECTOR3 m_pos;		//�ꏊ
	int m_nID;				//ID
	int m_nPriority;		//�`�揇
	bool m_bEnemy;			//�G���ۂ�
	bool m_bDeath;			//���ʂ�
	ELEMENT m_Element;		//����

protected:
	void Release(void);		//�폜
};

#endif