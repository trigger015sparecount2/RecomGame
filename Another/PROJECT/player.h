//=============================================================================
//
// �V�[������ [player.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene3d.h"
#include "model.h"

//�O���錾
class CKeyboard;
class CGamePad;
class CMouse;
class CCamera;
class CShadow;
class COrbit;
class CRockon;
class CUI;
class CPauseUI;

class CPlayer : public CScene3D
{
	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,	//�j���[�g����
		MOTIONTYPE_AIRNEUTRAL,	//�󒆃j���[�g����
		MOTIONTYPE_RUN,			//����
		MOTIONTYPE_JUMP,		//�W�����v
		MOTIONTYPE_SLAP,		//���ߋ����U��
		MOTIONTYPE_RUSH,		//�ːi�U��
		MOTIONTYPE_ROUND,		//���ӍU��
		MOTIONTYPE_ARIAL,		//�΋�U��
		MOTIONTYPE_DIVE,		//�Βn�U��
		MOTIONTYPE_FINISH,		//�t�B�j�b�V���U��
		MOTIONTYPE_LANDING,		//���n
		MOTIONTYPE_GROUNDDODGE,	//�n����
		MOTIONTYPE_AIRDODGE,	//�󒆉��
		MOTIONTYPE_GUARD,		//�K�[�h
		MOTIONTYPE_COUNTER,		//�J�E���^�[
		MOTIONTYPE_DAMAGEFRONT,	//�O������_���[�W
		MOTIONTYPE_DAMAGEBACK,	//��납��_���[�W
		MOTIONTYPE_DEATH,		//���ꂽ
		MOTIONTYPE_CLEAR,		//�N���A
		MOTIONTYPE_RETURN,		//�j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
		MOTIONTYPE_AIRRETURN,	//�󒆃j���[�g�������[�V�����ɖ߂�ۂ̃��[�V�����Btxt�t�@�C���ɏ����K�v�͂Ȃ�
		MAX_MOTION
	} MOTIONTYPE;

	//���[�V�����̏㉺������
	typedef enum
	{
		MOTIONUPDN_NONE = 0,
		MOTIONUPDN_UNDER,
		MOTIONUPDN_UPPER,
		MOTIONUPDN_UPDN,
		MAX_MOTIONUPDN
	} MOTIONUPDN;

	//�L�[�̍\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
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
		D3DXMATRIX TipmtxWorld;	//�O�Ղ̃}�g���b�N�X
		float fDis;				//�����鑬��
		D3DXCOLOR col1;			//�F��[
		D3DXCOLOR col2;			//�F���{
		int nStartTime;			//�������鎞��
		int nFinishTime;		//�I���̎���
		int nIdxParent;			//�e���f���̔ԍ�
	} Orbit;

	//���[�V�������̍\����
	typedef struct
	{
		bool bLoop;				//���[�v���邩�ǂ���
		bool bHoming;			//�ːi�͂Ȃǂɒǔ��������邩(�r���Ŏ~�܂邩)
		bool bGravity;			//�d�͂�������
		int nNumKey;			//�L�[�̑���
		Collision Collision[8];	//�����蔻��
		int nNumCol;			//�����蔻��̋��̐�
		int nComboTime;			//�R���{�P�\����
		Damage Damage[8];		//�_���[�W
		int nNumDmg;			//�_���[�W�̐�
		Orbit Orbit[4];			//�O��
		int nNumOrbit;			//�O�Ղ̐�
		int nNonOpe;			//����s�\����
		KEY_INFO aKeyInfo[16];	//�L�[��� []���̓L�[�̍ő吔
		int nNoDmg;				//���G��
		MOTIONUPDN MotionUpdn;	//���[�V�����㉺
	} MOTION_INFO;

public:
	CPlayer(PRIORITY Priority);
	~CPlayer();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);	//������
	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
	OBJTYPE GetObjType() { return OBJECTTYPE_PLAYER; }	//���
	float GetRadius() { return m_fRadius; }				//���a
	float GetHeight() { return m_fHeight; }				//����
	//COLLISION GetCollision() { return COLLISION_SPHERE; }
	//D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	//D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void Damage(int nDamage, D3DXVECTOR3 clash);								//�_���[�W����
	bool CollisionDamage(D3DXVECTOR3 pos, float fRadius, float fHeight);		//�U���̓����蔻��ɓ���������
	bool SetEnemy(CScene *pEnemy);												//�G�����X�g�Ɏ��߂�
	int Damage() { return m_MotionInfo.Damage[m_nDmgNumNow].nDamage; }			//�_���[�W��
	float HClash() { return m_MotionInfo.Damage[m_nDmgNumNow].fHClash; }		//���������̃m�b�N�o�b�N
	float VClash() { return m_MotionInfo.Damage[m_nDmgNumNow].fVClash; }		//���������̃m�b�N�o�b�N
	D3DXMATRIX GetMatrix(int nPart) { return m_pModel[nPart]->GetMatrix(); }	//���f���̃}�g���b�N�X
	void SetParticle();					//�U���q�b�g���A�p�[�e�B�N�����
	int GetHP() { return m_nHP; }		//���ݑ̗�
	int GetMaxHP() { return m_nMaxHP; }	//�ő�̗�
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *aFileName);	//�쐬

private:
	void Load(const char *aFileName);			//�t�@�C���ǂݍ���
	bool Move(float fRotY);						//�ړ�
	void MotionMove(float fRotY, float fMove);	//���[�V�����̈ړ��ʐ���
	void MotionStopMove();						//���[�V�����̈ړ��ʐ�������
	void MotionHeight(float fHeight);			//���[�V�����̈ړ��ʐ���
	void MotionStopHeight();					//���[�V�����̈ړ��ʐ�������
	bool Stop();								//�~�܂�
	void Jump();								//�W�����v
	void UnderSearch(D3DXVECTOR3 pos);			//�e�ݒ�
	void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);				//��Q���Ƃ̓����蔻��
	void CollisionPlane(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld);					//���ʂƂ̓����蔻��
	bool CollisionLand(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);	//�n�ʂƂ̓����蔻��
	void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 posOld, CScene *pScene);	//�ǂƂ̓����蔻��
	void Motion();								//���[�V����
	void HasteMotion();							//�������[�V����
	void MotionChange(MOTIONTYPE motionType);	//���[�V�����ύX
	void CollisionPos(int nCntCol);				//�U������̃��[�V����
	void CollisionEnemy(D3DXVECTOR3 *pPos);		//�G�Ƃ̓����蔻��
	void Orbit();								//�O��
	void Rockon();								//���b�N�I��
	void UnRockon();							//���b�N�I������
	void ResetEnemy();							//�G���X�g����
	void RockCameraMove(D3DXVECTOR3 pos);		//���b�N�I�����̃J�����ړ�
	MOTIONTYPE RockAttack(D3DXVECTOR3 pos);		//���b�N�I�����̍U��
	bool AroundEnemy(D3DXVECTOR3 pos);			//���͂ɓG���邩
	void SearchRock(D3DXVECTOR3 pos);			//���b�N�I�����̓G�T�[�`
	MOTIONTYPE NoRockAttack();					//���b�N�I�����ĂȂ����̍U��
	void PlayerDamage(D3DXVECTOR3 pos, float fHeight, float fRadius);	//�v���C���[�̃_���[�W
	void PauseChange(int nAdd);	//�|�[�Y�I�����ύX
	void PauseSelect();			//�|�[�Y����
	void EndChange(int nAdd);	//�I�������̑I�����ύX
	void EndSelect();			//�I�������̑I��������
	void GameClear();			//�Q�[���N���A

	D3DXVECTOR3 m_PosOld;			//�ߋ��ʒu
	D3DXVECTOR3 m_move;				//�ړ�
	D3DXVECTOR3 m_rotDesh;			//�ړI�̌���
	D3DXVECTOR3 m_RestartPos;		//�ǂȂǂ𔲂����Ƃ��̖߂��Ă���ʒu
	float m_fMove;					//�ő吅���ړ���
	float m_fGravity;				//�d��
	float m_fJump;					//�W�����v��
	float m_fHeight;				//����
	float m_fRadius;				//���a
	bool m_bJump;					//���n���Ă邩
	bool m_bLandObject;				//�I�u�W�F�N�g�ɏ���Ă邩
	int m_nNumModel;				//���f����
	int m_nTotalTime;				//���[�V�����̃g�[�^���J�E���g
	MOTIONTYPE m_motionType;		//���݃��[�V����
	MOTIONTYPE m_motionTypeOld;		//�ߋ����[�V����
	int m_nCntMotion;				//�L�[���Ƃ̃J�E���g
	MOTION_INFO m_aMotionInfo[32];	//���[�V�����̏��S��
	MOTION_INFO m_MotionInfo;		//���݃��[�V�����̏��
	int m_nNeutralTime;				//�j���[�g�����̎���
	KEY m_aKeyDiff[32];				//�L�[�̍���
	int m_nKey;						//���݃L�[
	CModel *m_pModel[32];			//���f���i�p�[�c�j
	CKeyboard *m_pKeyboard;			//�L�[�{�[�h
	CGamePad *m_pGamePad;			//�Q�[���p�b�h
	CMouse *m_pMouse;				//�}�E�X
	CCamera *m_pCamera;				//�J����
	CShadow *m_pShadow;				//�e
	CRockon *m_pRockon;				//���b�N�I��
	CScene *m_pEnemy[16];			//�G�̃��X�g
	COrbit *m_pOrbit[4];			//�O��
	int m_nHP;						//����HP
	int m_nMaxHP;					//�ő�HP
	int m_nRunStop;					//����̂�߂��J�E���g
	int m_nCntDamage;				//�U�����[�V�����̃_���[�W�J�E���g
	int m_nDmgNumNow;				//�_���[�W��^�����Ƃ��̃_���[�W�̎��
	int m_nCombo;					//���݃R���{��
	int m_nNonOpe;					//����s�\�J�E���g
	int m_nComboTime;				//�R���{����܂ł̎���
	int m_nCntRun;					//�����Ă�J�E���g
	D3DXVECTOR3 m_MotionMove;		//���[�V�����̈ړ���
	bool m_bRockon;					//���b�N�I�����Ă邩
	bool m_bLanding;				//���n
	bool m_bHit;					//�U������������
	bool m_bAttack;					//�U������o�Ă��邩
	bool m_bCounter;				//�J�E���^�[�\��
	bool m_bGameClear;				//�N���A������
	bool m_bEndSelect;				//�I�����o�Ă��邩
	bool m_bPinch;					//�s���`��
	int m_nCntCol;					//���Ԗڂ̓����蔻��ɓ���������
	int m_nCntNoDmg;				//���G����
	int m_nPauseSelect;				//�|�[�Y���̑I�����ԍ�
	int m_nCntRoundChange;			//���E���h���ύX����Ă���ǂꂾ�������������J�E���g
	int m_nCntDeath;				//���ꂽ�J�E���g
	int m_nCntPinch;				//�s���`���̃J�E���g
	CUI *m_pCounterUI;				//�J�E���^�[UI
	CUI *m_pHPUI;					//HP�Q�[�W
	CUI *m_pEnemyHPUI[3];			//�G��HP
	CPauseUI *m_pPauseUI[3];		//�|�[�Y�̑I����UI
	CUI *m_pRoundUI[4];				//���E���h�������UI
	CUI *m_pEndUI[2];				//�I�������̑I����UI
};
#endif