//=============================================================================
//
// 風バリア処理 [wind.h]
// Author : 三上航世
//
//=============================================================================
#include "manager.h"
#include "wind.h"
#include "renderer.h"
#include "enemy.h"
#include "scene.h"
#include "bullet.h"
#include "pauseui.h"
#include "prize.h"
#include "ui.h"

//静的メンバ変数
LPDIRECT3DTEXTURE9 CWind::m_pTexture = NULL;

CWind::CWind(PRIORITY Priority) : CScene2D::CScene2D(Priority)
{

}

CWind::~CWind(void)
{

}

//初期化
HRESULT CWind::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(WIND_SIZE, WIND_SIZE, pos, 1.0f);
	CScene::SetObjType(CScene::OBJTYPE_BULLET);
	CScene::SetPos(pos);
	CScene2D::ChangeColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	Set(0.0f, 0.0f, pos);
	m_pPlayerpos = CScene::GetPlayerPos();
	m_fRotY = D3DX_PI;
	m_fSize = 0.0f;
	m_bSize = false;
	m_nListCnt = 0;
	m_bDraw = false;
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < WIND_MAX_ENEMY; nCntEnemy++)
	{
		m_aEnemies[nCntEnemy] = -1;
	}
	return S_OK;
}

//終了
void CWind::Uninit(void)
{
	m_pPlayerpos = NULL;
	CScene2D::Uninit();
}

//更新
void CWind::Update(void)
{
	//ポーズ中じゃない
	if (CPauseUi::GetPause() == false)
	{
		//大きくする
		if (m_bSize == true)
		{
			if (WIND_SIZE > m_fSize)
			{
				m_fSize += 10.0f;
				m_bDraw = true;
			}
		}
		//小さくする
		else
		{
			if (m_fSize > 0.0f)
			{
				m_fSize -= 10.0f;
				if (m_fSize <= 10.0f)
				{
					m_fSize = 0.0f;
					m_bDraw = false;
				}
			}
		}

		//描画する(サイズが一定以上あるなら)
		if (m_bDraw == true)
		{
			//角度を加算させていく、場所や大きさを設定
			SetRot(-0.06f);
			Set(m_fSize, m_fSize, *m_pPlayerpos);

			//一定時間ごとにリストを一新する(当てるため)
			if (m_nListCnt > 0)
			{
				m_nListCnt--;
				if (m_nListCnt <= 0)
				{
					int nCntEnemy;
					for (nCntEnemy = 0; nCntEnemy < WIND_MAX_ENEMY; nCntEnemy++)
					{
						m_aEnemies[nCntEnemy] = -1;
					}
					m_nListCnt = 10;
				}
			}

			int nCntScene;
			for (nCntScene = 0; nCntScene < MAX_POLYGON; nCntScene++)
			{
				//敵へのダメージ
				CScene *pScene1;
				pScene1 = GetScene(PRIORITY_CHARA, nCntScene);
				if (pScene1 != NULL)
				{
					OBJTYPE objType;
					objType = pScene1->GetObjType();
					//敵かつリスト内にいない(当たってない)なら
					if (objType == OBJTYPE_ENEMY && EnemyList(nCntScene) == true)
					{
						D3DXVECTOR3 posEnemy;
						posEnemy = pScene1->GetPos();
						float fDistance;
						fDistance = sqrtf(powf(m_pPlayerpos->x - posEnemy.x, 2.0f) + powf(m_pPlayerpos->y - posEnemy.y, 2.0f));
						//距離を計算、短かったら当たってる
						if (fDistance <= ENEMY_SIZE * sinf(0.25f * D3DX_PI) + m_fSize * sinf(0.25f * D3DX_PI))
						{
							//ダメージを与えつつ、リストに保存
							if (pScene1->GetDamage() == true)
							{
								pScene1->Damage(2);
								ListPush(nCntScene);
							}
						}
					}
					pScene1 = NULL;
				}

				//弾丸消し
				CScene *pScene2;
				pScene2 = GetScene(PRIORITY_BULLET, nCntScene);
				if (pScene2 != NULL)
				{
					if (pScene2->GetEnemy() == true)
					{
						D3DXVECTOR3 posBullet;
						posBullet = pScene2->GetPos();
						float fDistance;
						fDistance = sqrtf(powf(m_pPlayerpos->x - posBullet.x, 2.0f) + powf(m_pPlayerpos->y - posBullet.y, 2.0f));
						//距離を計算、短かったら当たってる
						if (fDistance <= BULLET_SIZE * sinf(0.25f * D3DX_PI) + m_fSize * sinf(0.25f * D3DX_PI))
						{
							//弾を消す、スコア加算、出現するプライズは敵弾の属性と同じ
							D3DXVECTOR3 pos;
							pos = pScene2->GetPos();
							CPrize::Create(pos, D3DXVECTOR3(20.0f, 20.0f, 0.0f), pScene2->GetElement(), 5);
							CUi::SetScore(50);
							pScene2->Uninit();
						}
					}
					pScene2 = NULL;
				}
			}
		}
	}
}

//描画
void CWind::Draw(void)
{
	if (m_bDraw == true)
	{
		CScene2D::Draw();
	}
}

//作成
CWind *CWind::Create(D3DXVECTOR3 pos)
{
	CWind *pWind;
	pWind = new CWind(PRIORITY_BULLET);
	if (pWind != NULL)
	{
		pWind->Init(pos);
		pWind->BindTexture(m_pTexture);
	}
	return pWind;
}

//テクスチャ読み込み
HRESULT CWind::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wind.png",
		&m_pTexture);
	return S_OK;
}

//テクスチャ破棄
void CWind::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//どの敵に当たったのかリスト内を参照
bool CWind::EnemyList(int nEnemy)
{
	int nCntEnemy;
	for (nCntEnemy = 0; nCntEnemy < WIND_MAX_ENEMY; nCntEnemy++)
	{
		if (m_aEnemies[nCntEnemy] == nEnemy)
		{
			return false;
		}
	}
	return true;
}

//リスト内に敵を入れる
void CWind::ListPush(int nEnemy)
{
	m_aEnemies[m_nListCnt] = nEnemy;
	m_nListCnt++;
	if (m_nListCnt >= WIND_MAX_ENEMY)
	{
		m_nListCnt = 0;
	}
}