//*****************************************************************************
// シーン2D処理 [Scene2D.h]
// Author : 佐藤秀亮
//*****************************************************************************
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main.h"
#include "Scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define MAX_TEXTURE (64)		//最大で使える2D用の画像数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 頂点フォーマットに合わせた構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点処理
	float rhw;			// 1.0で固定
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャの座標
} VERTEX_2D;

//*****************************************************************************
//オブジェクトクラス
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(PRIORITY Priority);
	~CScene2D();

	HRESULT Init(D3DXVECTOR3 pos);	//初期化
	void Uninit();					//終了
	void Update();					//更新
	void Draw();					//描画

	//posの格納・取得
	D3DXVECTOR3 GetPos() { return m_pos; }
	void SetPos(D3DXVECTOR3 pos);

	//↓--------使わない---------↓
	D3DXVECTOR3 GetRot() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	OBJTYPE GetObjType() { return OBJECTTYPE_NONE; }
	float GetRadius() { return 0.0f; }
	COLLISION GetCollision() { return COLLISION_SPHERE; }
	D3DXVECTOR3 GetVtxMax() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	D3DXVECTOR3 GetVtxMin() { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void Damage(int, D3DXVECTOR3) { ; }
	bool GetRotX() { return false; }
	bool CollisionDamage(D3DXVECTOR3, float, float) { return false; }
	bool SetEnemy(CScene *pEnemy) { return false; }
	int Damage() { return 0; }
	float HClash() { return 0.0f; }
	float VClash() { return 0.0f; }
	void SetParticle() { ; }
	bool GetAttack() { return false; }
	void Reflect() { ; }
	int GetHP() { return 0; }
	int GetMaxHP() { return 0; }
	D3DXMATRIX GetMatrix(int) { return D3DXMATRIX(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f); }
	//↑--------使わない---------↑

	//テクスチャの破棄・読み込み
	static void UninitTexture();
	static void CreateTexture();

	float GetHeight() { return m_Size.x; }	//pos更新するためにゲット
	float GetWidth() { return m_Size.y; }	//pos更新するためにゲット
	void SetSize(D3DXVECTOR2 Size);			//大きさ更新
	void SetTexture(int nTex);				//テクスチャタイプ
	void ColorChange(D3DXCOLOR color);		//カラー変更
	void FadeColorChange(int Alpha);		//透明度変更
	void SetTex(int Texpos, float TexSize);			//テクスチャパターン番号、パターン１つのサイズ
	void TexMove(float TexMoveU, float TexMoveV);	//テクスチャ座標の更新
	void SetGaugeScele(float Width, float Height);	//ゲージタイプのスケール変更

private:
	static LPDIRECT3DTEXTURE9 m_Texture[MAX_TEXTURE];				//テクスチャーポインタ
	static int m_nMaxTex;											//使用する最大テクスチャ

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ

	D3DXVECTOR3 m_pos;		//位置

	D3DXVECTOR2 m_Size;		//大きさ

	int m_nType;			//種類

	int m_Texpos;			//テクスチャ座標
	float m_TexSize;		//テクスチャサイズ

	float m_TexMoveU;		//テクスチャ移動値
	float m_TexMoveV;		//テクスチャ移動値

	float m_PosTexU;		//テクスチャU座標
	float m_PosTexV;		//テクスチャV座標

	D3DCOLORVALUE m_color;	//カラー値
};
#endif
