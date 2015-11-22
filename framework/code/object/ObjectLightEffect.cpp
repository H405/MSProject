//==============================================================================
//
// File   : ObjectLightEffect.cpp
// Brief  : ライト描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectLightEffect.h"
#include "../framework/resource/Effect.h"
#include "../graphic/graphic/GraphicLightEffect.h"
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
ObjectLightEffect::ObjectLightEffect( void ) : Object()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectLightEffect::~ObjectLightEffect( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectLightEffect::Initialize( int priority )
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
int ObjectLightEffect::Finalize( void )
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
int ObjectLightEffect::Reinitialize( int priority )
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
// Arg    : ObjectLightEffect* pOut				: コピー先アドレス
//==============================================================================
int ObjectLightEffect::Copy( ObjectLightEffect* pOut ) const
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
void ObjectLightEffect::Update( void )
{
	// 基本クラスの処理
	Object::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureDiffuseRiver		: ディフューズ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureSpecularRiver	: スペキュラ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureNormalRiver		: 法線情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepthRiver		: 深度情報テクスチャ
//==============================================================================
int ObjectLightEffect::CreateGraphic( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth,
	IDirect3DTexture9* pTextureDiffuseRiver, IDirect3DTexture9* pTextureSpecularRiver, IDirect3DTexture9* pTextureNormalRiver, IDirect3DTexture9* pTextureDepthRiver )
{
	// グラフィックの生成
	int		result;				// 実行結果
	pGraphic_ = new GraphicLightEffect();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, ppEffectGeneral, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth,
		pTextureDiffuseRiver, pTextureSpecularRiver, pTextureNormalRiver, pTextureDepthRiver );
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

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : GraphicLightEffect* pValue			: 設定する値
//==============================================================================
void ObjectLightEffect::SetGraphic( GraphicLightEffect* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicLightEffect*					: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicLightEffect* ObjectLightEffect::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectLightEffect::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
}
