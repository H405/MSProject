//*****************************************************************************
// キーフレームアニメーション用2Dポリゴン [CObj2DKeyFrame.h]
//	Author : KOTARO NAGASAKI
//*****************************************************************************
#ifndef _COBJ2DKEYFRAME_H_
#define _COBJ2DKEYFRAME_H_

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
//*****************************************************************************
class CObj2DKeyFrame : public CObj2D
{
public:
	CObj2DKeyFrame(OBJTYPE _objType, int _priority);
	virtual ~CObj2DKeyFrame();
	virtual void Init();
	virtual void Update();
	virtual void Draw();

	//=============================================================================
	//	作成代理処理
	//
	//	サイズの指定はポリゴンの全長を指定する
	//	画面いっぱいのポリゴンを作りたいときは　SCREE_WIDTH(SCREEN_HEIGHT)　を指定する
	//
	//	keyMaxはキーフレームのコマ数
	//	keyCountMaxは、キーフレーム更新処理を行うカウント数を設定
	//	※1以上を指定
	//
	//	posはデフォルトで画面の中心
	//	rot,colorはそれぞれ、0.0fと1.0fで初期化
	//	テクスチャUV値はデフォルト値 (L:0.0   T:0.0   R:1.0   B:1.0)
	//=============================================================================
	static CObj2DKeyFrame* Create(LPDIRECT3DDEVICE9 _device,
		int _keyMax,
		int _keyCountMax,
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
	bool getKeyFlag()
	{
		return keyFlag;
	}
	//-------------------------------------------------

	//	セッター
	//-------------------------------------------------
	void setKeyFlag(bool _setFlag)
	{
		keyFlag = _setFlag;
	}
	//-------------------------------------------------

protected:

	float keyRate;	//	キーフレームの変更値レート
	int keyMax;	//	キーフレーム数の最大値
	int keyNum;	//	現在のコマ数
	int keyCountMax;	//	キーフレームの変更カウントの最大値
	int keyCount;	//	キーフレームカウント数

	bool keyFlag;	//	キーフラグがTRUEのときは、カウント数が加算される（キーフレームアニメーションする）
};

#endif

//-----------------------------------EOF---------------------------------------