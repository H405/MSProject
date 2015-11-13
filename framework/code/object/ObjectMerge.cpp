//==============================================================================
//
// File   : ObjectMerge.cpp
// Brief  : 総合3D描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectMerge.h"
#include "../graphic/graphic/GraphicMerge.h"
#include "../system/EffectParameter.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectMerge::ObjectMerge( void ) : Object()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectMerge::~ObjectMerge( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectMerge::Initialize( int priority )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ObjectMerge::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectMerge::Reinitialize( int priority )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ObjectMerge* pOut					: コピー先アドレス
//==============================================================================
int ObjectMerge::Copy( ObjectMerge* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectMerge::Update( void )
{
	// 基本クラスの処理
	Object::Update();
}

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
//==============================================================================
int ObjectMerge::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
	IDirect3DTexture9* pTextureDepth )
{
	// グラフィックの生成
	int		result;				// 実行結果
	pGraphic_ = new GraphicMerge();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pTextureLight, pTextureNotLight, pTextureMask, pTextureAdd, pTextureDepth );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// 拡縮の設定
	if( pParameter != nullptr )
	{
		scale_.x = pParameter->GetWidthScreen();
		scale_.y = pParameter->GetHeightScreen();
	}

	// 値の返却
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : GraphicMerge* pValue			: 設定する値
//==============================================================================
void ObjectMerge::SetGraphic( GraphicMerge* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicMerge*					: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicMerge* ObjectMerge::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectMerge::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
}
