//=============================================================================
//
// �V�[������ [scene.h]
// Author : �O��q��
//
//=============================================================================
#include "scene.h"
#include "Game.h"

//�ÓI�����o�ϐ�
CScene *CScene::m_pTop[PRIORITY_MAX] = {};
CScene *CScene::m_pCur[PRIORITY_MAX] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(CScene::PRIORITY Priority)
{
	m_Priority = Priority;

	m_pNext = NULL;
	m_bDeath = false;
	if (m_pTop[m_Priority] == NULL && m_pCur[m_Priority] == NULL)
	{
		m_pPrev = NULL;
		m_pTop[m_Priority] = this;
		m_pCur[m_Priority] = this;
	}
	else if (m_pCur != NULL)
	{
		m_pCur[m_Priority]->m_pNext = this;
		m_pPrev = m_pCur[m_Priority];
		m_pCur[m_Priority] = this;
	}
	m_nNumAll++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
	//�G�t�F�N�g�ɕs����������ď���Ɏ����̂�ɕς��܂����A���܂�
	PRIORITY Priority = m_Priority;

	//�����Ώۂ�Top�ł���Cur�������ꍇ
	if (this == m_pTop[Priority] &&
		this == m_pCur[Priority])
	{
		m_pTop[Priority] = NULL;
		m_pNext = NULL;
		m_pCur[Priority] = NULL;
		m_pPrev = NULL;
	}
	//�����Ώۂ�Top
	else if (this == m_pTop[Priority])
	{
		m_pTop[Priority] = m_pNext;
		m_pPrev = NULL;
		m_pNext->m_pPrev = NULL;
	}
	//�����Ώۂ�Cur
	else if (this == m_pCur[Priority])
	{
		m_pCur[Priority] = m_pPrev;
		m_pNext = NULL;
		m_pPrev->m_pNext = NULL;
	}
	//����ȊO
	else
	{
		m_pNext->m_pPrev = m_pPrev;
		m_pPrev->m_pNext = m_pNext;
	}
}

//�S������
void CScene::ReleaseAll()
{
	//�`�揈�����𔻕�
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext;
			pScene->Uninit();
			pScene = pSceneNext;
		}
	}
}

//�X�V
void CScene::UpdateAll()
{
	//�`�揈�����𔻕�
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext;
			pScene->Update();
			if (pScene->m_bDeath == true)
			{
				pScene->Uninit();
			}
			pScene = pSceneNext;
		}
	}
}

//�`��
void CScene::DrawAll()
{
	//�`�揈�����𔻕�
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CScene *pScene;
		pScene = m_pTop[nCntPriority];
		while (pScene)
		{
			CScene *pSceneNext;
			pSceneNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pSceneNext;
		}
	}
}

//����
void CScene::Release()
{
	delete this;
	m_nNumAll--;
}