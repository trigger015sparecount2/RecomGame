//*****************************************************************************
// UI関連処理(UI.cpp)
// Author : 三上航世
//*****************************************************************************
//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "UI.h"
#include "Scene2D.h"
#include "manager.h"


//*****************************************************************************
//静的
//*****************************************************************************

//*****************************************************************************
//マクロ
//*****************************************************************************
//#define MAX_SPEED (4.0f)

#if 1
//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CUI::CUI(CScene::PRIORITY Priority) : CScene2D(Priority)
{
	m_bUninit = false;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
CUI::~CUI()
{

}
#endif

//*****************************************************************************
//初期化
//*****************************************************************************
HRESULT CUI::Init(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col)
{
	CScene2D::Init(pos);

	m_pos = pos;
	m_bUninit = false;

	//m_nLife = nLife;

	CScene2D::SetTexture(nType);	//選択した番号のテクスチャを貼る
	CScene2D::SetSize(D3DXVECTOR2(SizeX, SizeY));
	CScene2D::ColorChange(col);
	return S_OK;
}

//*****************************************************************************
//終了
//*****************************************************************************
void CUI::Uninit()
{
	CScene2D::Uninit();
}

//*****************************************************************************
//更新
//*****************************************************************************
void CUI::Update()
{
	/*
	m_Color.r = 255;
	m_Color.g = 255;
	m_Color.b = 255;
	m_Color.a = 255;
	CScene2D::ColorChange(m_Color);

	CScene2D::SetPos(m_pos);
	*/

	//削除
	if (m_bUninit == true)
	{
		SetDeath(true);
	}
}

//描画・作成
#if 1
//*****************************************************************************
//描画
//*****************************************************************************
void CUI::Draw()
{
	CScene2D::Draw();
}

//*****************************************************************************
//作成
//*****************************************************************************
CUI *CUI::Create(D3DXVECTOR3 pos, float SizeX, float SizeY, int nType, D3DXCOLOR col)
{
	CUI *pUI = NULL;
	pUI = new CUI(PRIORITY_UI);
	if (pUI != NULL)
	{
		pUI->Init(pos, SizeX, SizeY, nType, col);
	}
	return pUI;
}
#endif
