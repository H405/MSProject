//==============================================================================
//
// File   : ObjectBlur.cpp
// Brief  : ブラー基描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/10 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectBlur.h"
#include "../framework/resource/Effect.h"
#include "../graphic/graphic/GraphicBlur.h"
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
ObjectBlur::ObjectBlur( void ) : Object()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectBlur::~ObjectBlur( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectBlur::Initialize( int priority )
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
int ObjectBlur::Finalize( void )
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
int ObjectBlur::Reinitialize( int priority )
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
// Arg    : ObjectBlur* pOut					: コピー先アドレス
//==============================================================================
int ObjectBlur::Copy( ObjectBlur* pOut ) const
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
void ObjectBlur::Update( void )
{
	// 基本クラスの処理
	Object::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectX					: X方向ブラーエフェクト
// Arg    : Effect* pEffectY					: Y方向ブラーエフェクト
// Arg    : IDirect3DTexture9* pTextureX		: X方向ブラーを掛けるテクスチャ
// Arg    : IDirect3DTexture9* pTextureY		: Y方向ブラーを掛けるテクスチャ
//==============================================================================
int ObjectBlur::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectX, Effect* pEffectY,
	IDirect3DTexture9* pTextureX, IDirect3DTexture9* pTextureY )
{
	// グラフィックの生成
	int		result;				// 実行結果
	pGraphic_ = new GraphicBlur();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectX, pEffectY, pTextureX, pTextureY );
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
// Arg    : GraphicBlur* pValue					: 設定する値
//==============================================================================
void ObjectBlur::SetGraphic( GraphicBlur* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicBlur*						: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicBlur* ObjectBlur::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectBlur::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
}
