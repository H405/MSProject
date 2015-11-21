//==============================================================================
//
// File   : ObjectMerge.h
// Brief  : 総合3D描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_MERGE_H
#define MY_OBJECT_MERGE_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/object/object.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Effect;
class EffectParameter;
class GraphicMerge;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectMerge : public Object
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectMerge( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectMerge( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	//==============================================================================
	int Initialize( int priority );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	//==============================================================================
	int Reinitialize( int priority );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ObjectMerge* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( ObjectMerge* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : 描画クラスの生成
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureLight	: ライトありテクスチャ
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ライトなしテクスチャ
	// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
	// Arg    : IDirect3DTexture9* pTextureAdd		: 加算合成テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	// Arg    : IDirect3DTexture9* pTextureRiver	: 川テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepthRiver	: 川の深度テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureRiver, IDirect3DTexture9* pTextureDepthRiver );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicMerge* pValue );
	GraphicMerge* GetGraphic( void ) const;

protected:
	GraphicMerge*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	ObjectMerge( const ObjectMerge& );
	ObjectMerge operator=( const ObjectMerge& );

};

#endif	// MY_OBJECT_MERGE_H
