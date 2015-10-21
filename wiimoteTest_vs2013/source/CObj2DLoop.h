//*****************************************************************************
// ループアニメーション用2Dポリゴン [CObj2DLoop.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _COBJ2DLOOP_H_
#define _COBJ2DLOOP_H_

//*****************************************************************************
//	インクルード定義
//*****************************************************************************
#include "main.h"
#include "CObj2D.h"


//	※※※このファイルは
//	※※※Author以外の変更は禁止！！
//	※※※変更が必要な個所がある場合はAuthorに連絡すること

//*****************************************************************************
//	クラス定義
//
//	余計な頂点計算をしないように、毎フレーム頂点計算をしない
//	位置、回転、色　の値が変更された場合は、自分でsetVtxBuff関数を呼び出すこと
//	ループアニメーション処理のみを行う場合は自動的に呼ばれるので設定の必要なし
//*****************************************************************************
class CObj2DLoop:public CObj2D
{
public:
	CObj2DLoop(OBJTYPE _objType, int _priority);
	virtual ~CObj2DLoop();
	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//=============================================================================
	//	作成代理処理
	//
	//	サイズの指定はポリゴンの全長を指定する
	//	画面いっぱいのポリゴンを作りたいときは　SCREE_WIDTH(SCREEN_HEIGHT)　を指定する
	//
	//	loopRateX,loopRateYは、一度のループ更新処理でずらすUV値を設定
	//	loopCountMaxは、ループ更新処理を行うカウント数を設定
	//	※1以上を指定すること
	//
	//	posはデフォルトで画面の中心
	//	rot,colorはそれぞれ、0.0fと1.0fで初期化
	//	テクスチャUV値はデフォルト値 (L:0.0   T:0.0   R:1.0   B:1.0)
	//=============================================================================
	static CObj2DLoop* Create(LPDIRECT3DDEVICE9 _device,
		float _loopRateX,
		float _loopRateY,
		int _loopCountMax,
		D3DXVECTOR3 _size,
		int _priority,
		D3DXVECTOR3 _pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3 _rot = VEC3_0,
		D3DXCOLOR _color = COL4_1,
		TEXUV _texUV = UV_DEF);

	virtual void setVtxBuff();
	void checkTexUV();

	//	ゲッター
	//-------------------------------------------------
	bool getLoopFlag()
	{
		return loopFlag;
	}
	//-------------------------------------------------

	//	セッター
	//-------------------------------------------------
	void setLoopFlag(bool _setFlag)
	{
		loopFlag = _setFlag;
	}
	//-------------------------------------------------

private:
	float loopRateX;	//	ループフレームXの変更値レート
	float loopRateY;	//	ループフレームYの変更値レート
	int loopCountMax;	//	ループフレームの変更カウントの最大値
	int loopCount;		//	ループフレームカウント数

	bool loopFlag;		//	ループフラグがTRUEのときは、カウント数が加算される（ループする）
};

#endif

//-----------------------------------EOF---------------------------------------