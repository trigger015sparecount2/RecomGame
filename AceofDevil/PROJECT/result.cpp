//=============================================================================
//
// ���U���g [result.h]
// Author : �O��q��
//
//=============================================================================
#include "scene2d.h"
#include "sound.h"
#include "result.h"
#include "manager.h"
#include "fade.h"
#include "resultui.h"

CResult::CResult(PRIORITY Priority) : CScene::CScene(Priority)
{

}

CResult::~CResult(void)
{

}

//������
HRESULT CResult::Init(float, float, D3DXVECTOR3, float)
{
	CScene::SetObjType(CScene::OBJTYPE_NONE);
	CResultUi::Load();
	CResultUi::Create();
	CSound::Play(CSound::SOUND_LABEL_RESULTBGM);
	return S_OK;
}

//�I��
void CResult::Uninit(void)
{
	CResultUi::UnLoad();
	Release();
}

//�X�V
void CResult::Update(void)
{
	
}

//�`��
void CResult::Draw(void)
{

}