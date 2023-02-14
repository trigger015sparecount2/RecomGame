//=============================================================================
//
// �Q�[���V�[�� [game.h]
// Author : �O��q��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"

class CGame : public CScene
{
public:
	CGame(PRIORITY Priority = PRIORITY_BG);
	~CGame();

	HRESULT Init(float, float, D3DXVECTOR3, float);	//������
	void Uninit(void);	//�I��
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool GetDamage(void) { return false; }
	void Damage(int) { ; }

private:
	int m_nTime;	//����
};
#endif