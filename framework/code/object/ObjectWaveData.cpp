//==============================================================================
//
// File   : ObjectWaveData.cpp
// Brief  : 波情報描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectWaveData.h"
#include "../framework/resource/Effect.h"
#include "../graphic/graphic/GraphicWaveData.h"
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
ObjectWaveData::ObjectWaveData( void ) : Object()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectWaveData::~ObjectWaveData( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectWaveData::Initialize( int priority )
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
int ObjectWaveData::Finalize( void )
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
int ObjectWaveData::Reinitialize( int priority )
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
// Arg    : ObjectWaveData* pOut					: コピー先アドレス
//==============================================================================
int ObjectWaveData::Copy( ObjectWaveData* pOut ) const
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
void ObjectWaveData::Update( void )
{
	// 基本クラスの処理
	Object::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: エフェクト
// Arg    : IDirect3DTexture9* pTextureHeight0	: 高さテクスチャ0
// Arg    : IDirect3DTexture9* pTextureHeight1	: 高さテクスチャ1
//==============================================================================
int ObjectWaveData::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffect,
	IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 )
{
	// グラフィックの生成
	int		result;				// 実行結果
	pGraphic_ = new GraphicWaveData();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffect, pTextureHeight0, pTextureHeight1 );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// 拡縮の設定
	if( pParameter != nullptr )
	{
		scale_.x = 256.0f;
		scale_.y = 256.0f;
	}

	// 値の返却
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : GraphicWaveData* pValue				: 設定する値
//==============================================================================
void ObjectWaveData::SetGraphic( GraphicWaveData* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicWaveData*						: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicWaveData* ObjectWaveData::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectWaveData::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
}
