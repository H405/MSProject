//==============================================================================
//
// File   : ObjectGrass.cpp
// Brief  : 草オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/12/11 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectGrass.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicGrass.h"
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
ObjectGrass::ObjectGrass( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectGrass::~ObjectGrass( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectGrass::Initialize( int priority )
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
int ObjectGrass::Finalize( void )
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
int ObjectGrass::Reinitialize( int priority )
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
// Arg    : ObjectGrass* pOut				: コピー先アドレス
//==============================================================================
int ObjectGrass::Copy( ObjectGrass* pOut ) const
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
void ObjectGrass::Update( void )
{
	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Texture* pTexture					: テクスチャ
//==============================================================================
int ObjectGrass::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// グラフィックの生成
	int					result;				// 実行結果
	IDirect3DTexture9*	pTextureSet;		// 設定するテクスチャ
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new GraphicGrass();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, pTextureSet, 0.2f * static_cast< float >( rand() ) / RAND_MAX + 0.1f );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// 拡縮の設定
	if( pTexture != nullptr )
	{
		scale_.x = static_cast< float >( pTexture->width_ );
		scale_.y = static_cast< float >( pTexture->height_ );
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : GraphicGrass* pValue						: 設定する値
//==============================================================================
void ObjectGrass::SetGraphic( GraphicGrass* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicGrass*							: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicGrass* ObjectGrass::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectGrass::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
}
