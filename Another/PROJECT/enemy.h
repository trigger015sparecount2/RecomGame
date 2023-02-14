//=============================================================================
//
// �G���� [enemy.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene3d.h"
#include "model.h"

class CShadow;

class CEnemy : public CScene3D
{
	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,	//�j���[�g����
		MOTIONTYPE_RUN,			//����
		MOTIONTYPE_ACTION,		//�U��
		MOTIONTYPE_DAMAGEBACK,	//�������_���[�W
		MOTIONTYPE_DAMAGEFRONT,	//�O������_���[�W
		MOTIONTYPE_REFLECT,		//�h���ꂽ
		MOTIONTYPE_RETURN,		//�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
		MAX_MOTION
	} MOTIONTYPE;

	//�L�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;	//�ꏊ
		D3DXVECTOR3 rot;	//����
	} KEY;

	//�L�[���̍\����
	typedef struct
	{
		int nFrame;		//�t���[��
		float fMove;	//���̃L�[�̐����ړ���
		float fHeight;	//���̃L�[�̐����ړ���
		KEY aKey[32];	//�e���f���̃L�[�v�f []���̓p�[�c�̍ő吔
	} KEY_INFO;

	//�����蔻��̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;		//�ʒu
		D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
		int nIdxModelParent;	//�e���f���̃C���f�b�N�X
		float fRadius;			//�����蔻��̑傫���̔��a
	} Collision;

	//�_���[�W�֘A�̍\����
	typedef struct
	{
		int nDamageTime;	//�q�b�g�Ԋu
		int nStartTime;		//�����蔻�肪�������鎞��
		int nFinishTime;	//�����蔻�肪�����鎞��
		int nDamage;		//�_���[�W��
		float fHClash;		//���������̐�����΂���
		float fVClash;		//���������̐�����΂���
	} Damage;

	//�O�Ղ̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;		//�O�Ղ̐�[�̈ʒu
		D3DXVECTOR3 TipposOld;	//�O�Ղ̐�[�̑O��ʒu
		D3DXVECTOR3 posOld;		//�O�Ղ̍����̑O��ʒu
		D3DXMATRIX TipmtxWorld;	//�O�Ղ̐�[�̃}�g���b�N�X
		int nTime;				//������܂ł̎���
		int nStartTime;			//�������鎞��
		int nFinishTime;		//�I���̎���
		int nIdxParent;			//�e���f���̔ԍ�
		float fDis;				//�����鑬��
		D3DXCOLOR col1;			//�F��[
		D3DXCOLOR col2;			//�F���{
	} Orbit;

	//�X�e�[�^�X�̍\����
	typedef struct
	{
		int nNumModel;	//���f���̌�
		int nHP;		//�̗�
		int nMaxHP;		//�ő�̗�
		float fMove;	//�ő�ړ���
		float fGravity;	//�d��
		float fJump;	//�W�����v��
		float fHeight;	//�����蔻��̍���
		float fRadius;	//�����蔻��̔��a
	} Status;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;				//���[�v���邩�ǂ���
		bool bGravity;			//�d�͎󂯂邩
		int nNumKey;			//�L�[�̑���
		Collision Collision[8];	//�U���̓����蔻��
		int nNumCol;			//�����蔻��̋��̐�
		Damage Damage[8];		//�_���[�W
		int nNumDmg;			//�_���[�W�̎��
		Orbit Orbit[4];			//�O��
		int nNumOrbit;			//�O�Ղ̎��
		int nNonOpe;			//����s�\����
		KEY_INFO aKeyInfo[16];	//�L�[��� []���̓L�[�̍ő吔
	} MOTION_INFO;

	//�R�s�[�������
	typedef struct
	{
		MOTION_INFO amotionInfo[MAX_MOTION];	//���[�V�����̏��
		Status status;			//�X�e�[�^�X
		CModel *apModel[32];	//���f��
	} Copies;

public:
	CEnemy(PRIORITY Priority);
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��

	OBJTYPE GetObjType() { return OBJECTTYPE_ENEMY; }	//���
	float GetRadius() { return m_Status.fRadius; }		//�����蔻�蔼�a
	float GetHeight() { return m_Status.fHeight; }		//�����蔻�荂��
	/*COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return m_VtxMax; }
	D3DXVECTOR3 GetVtxMin() { return m_VtxMin; }*/
	void Damage(int nDamage, D3DXVECTOR3 clash);	//�_���[�W
	bool CollisionDamage(D3DXVECTOR3 pos, float fRadius, float fHeight);	//�����蔻�肭�炤��
	int Damage() { return m_MotionInfo.Damage[m_nDmgNumNow].nDamage; }		//�_���[�W��
	float HClash() { return m_MotionInfo.Damage[m_nDmgNumNow].fHClash; }	//�U���̃m�b�N�o�b�N����
	float VClash() { return m_MotionInfo.Damage[m_nDmgNumNow].fVClash; }	//�U���̃m�b�N�o�b�N����
	void SetParticle();							//�p�[�e�B�N�����
	bool GetAttack() { return m_bAttackMove; }	//�U�����悤�Ƃ��Ă邩�擾
	void Reflect();								//�U���e���ꂽ
	int GetHP() { return m_Status.nHP; }		//����HP
	int GetMaxHP() { return m_Status.nMaxHP; }	//�ő�HP
	D3DXMATRIX GetMatrix(int nPart) { return m_pModel[nPart]->GetMatrix(); }	//���f���p�[�c�̃}�g���b�N�X

	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	//�쐬
	static void Load(const char *aFileName);					//�t�@�C���ǂݍ���
	static void UnLoad();										//���f���j��
	static int GetEnemies() { return m_nEnemies; }				//�G�̐�

private:
	void Move(float fRotY);							//�ړ�
	void MotionMove(float fMove, float fHeight);	//���[�V�����̈ړ�
	void Stop();									//��~
	void UnderSearch(D3DXVECTOR3 pos);				//�e�̐ݒ�
	void CollisionPos(int nCntCol);					//�U���̓����蔻��ݒ�
	void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);				//��Q���Ƃ̓����蔻��
	void CollisionPlane(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);					//���ʂ̓����蔻��
	bool CollisionLand(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);	//�n�ʂƂ̓����蔻��
	void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);	//�ǂƂ̓����蔻��
	void CollisionEnemy(D3DXVECTOR3 *pPos);										//�G�Ƃ̓����蔻��
	void Motion();														//���[�V����
	void MotionChange(MOTIONTYPE motionType);							//���[�V�����ύX
	void EnemyDamage(D3DXVECTOR3 pos, float fRadius, float fHeight);	//�G�̃_���[�W
	void EnemyAI();					//�G��AI
	bool EnemyAttack();				//�G�������̍U�����邩
	void AttackAI(D3DXVECTOR3 pos);	//�U������AI
	D3DXVECTOR3 SearchPlayer(void);	//�v���C���[�T��
	void DataCopy();				//���f���Ȃǂ̃R�s�[

	D3DXVECTOR3 m_PosOld;		//�ߋ��ꏊ
	D3DXVECTOR3 m_move;			//�ړ�
	D3DXVECTOR3 m_motionMove;	//���[�V�����̈ړ���
	D3DXVECTOR3 m_rotDesh;		//�ړI�̌���
	Status m_Status;			//�X�e�[�^�X
	bool m_bJump;				//���n���Ă邩
	bool m_bLandObject;			//��Q���ɏ���Ă邩
	MOTIONTYPE m_motionType;	//���[�V�����̎��
	int m_nCntMotion;			//�L�[���Ƃ̃J�E���g
	MOTION_INFO m_aMotionInfo[MAX_MOTION];	//���[�V�����S��
	MOTION_INFO m_MotionInfo;	//���݃��[�V����
	KEY m_aKeyDiff[32];			//�L�[���Ƃ̍���
	int m_nKey;					//���̃L�[��
	int m_nCntThinkTime;		//�l���鎞��
	int m_nCntMoveTime;			//�ړ�����
	CModel *m_pModel[32];		//���f���i�p�[�c�j
	CShadow *m_pShadow;			//�e
	bool m_bLanding;			//���n
	bool m_bAttackMove;			//�U�����邽�߂Ɉړ����Ă邩
	bool m_bAttack;				//�U������
	bool m_bHit;				//����������
	int m_nDmgNumNow;			//�_���[�W�̎��
	int m_nTotalTime;			//���[�V�����̃g�[�^���J�E���g
	int m_nCntCol;				//�_���[�W��^���������蔻��̎��
	int m_nCntDamage;			//���[�V�����̓����蔻��̃J�E���g

	static Copies m_Copies;		//�R�s�[������
	static int m_nEnemies;		//�G�̐�
};
#endif