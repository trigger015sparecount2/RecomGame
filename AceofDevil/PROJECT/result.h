//=============================================================================
//
// ���U���g�V�[�� [result.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"

//�O���錾

class CScene2D;

class CResult : public CScene
{
public:
	CResult(PRIORITY Priority = PRIORITY_BG);
	~CResult();

	HRESULT Init(float, float, D3DXVECTOR3, float);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool GetDamage(void) { return false; }
	void Damage(int) { ; }
};
#endif