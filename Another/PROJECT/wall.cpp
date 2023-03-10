//---------------------------
//Author:三上航世
//壁(wall.cpp)
//---------------------------
#include "wall.h"
#include "manager.h"
#include "renderer.h"

CWall::CWall(PRIORITY Priority) : CPlane::CPlane(Priority)
{

}

CWall::~CWall()
{

}

//初期化処理
HRESULT CWall::Init(D3DXVECTOR3 size, D3DXVECTOR3 pos, D3DXVECTOR2 Tex, D3DXVECTOR3 rot)
{
	CPlane::Init(size, pos, Tex, false);
	//SetPos(pos);
	SetRot(rot);
	m_VtxMax = size;
	m_VtxMin = -size;
	return S_OK;
}

//終了処理
void CWall::Uninit()
{
	CPlane::Uninit();
}

//更新処理
void CWall::Update()
{
	
}

//描画処理
void CWall::Draw()
{
	CPlane::Draw();
}

//作成
CWall *CWall::Create(D3DXVECTOR3 size, D3DXVECTOR3 pos, int nTex, D3DXVECTOR2 Tex, D3DXVECTOR3 rot)
{
	CWall *pWall;
	pWall = new CWall(PRIORITY_PLANE);
	if (pWall != NULL)
	{
		pWall->Init(size, pos, Tex, rot);
		pWall->SetTexture(nTex);
	}
	return pWall;
}
