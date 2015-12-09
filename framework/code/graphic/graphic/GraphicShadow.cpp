//==============================================================================
//
// File   : GraphicShadow.cpp
// Brief  : ライト描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicShadow.h"
#include "../drawer/DrawerShadow.h"
#include "../../system/EffectParameter.h"

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
GraphicShadow::GraphicShadow( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicShadow::~GraphicShadow( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightNear	: 平行光源(近)の深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightFar		: 平行光源(遠)の深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightPoint	: 点光源の深度情報テクスチャ
//==============================================================================
int GraphicShadow::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pParameter_ = pParameter;

	// 描画クラスの生成
	DrawerShadow*	pDrawerShadow = nullptr;		// 描画クラス
	pDrawerShadow = new DrawerShadow();
	if( pDrawerShadow == nullptr )
	{
		return 1;
	}
	result = pDrawerShadow->Initialize( pParameter, pEffectGeneral, pPolygon2D_, pTextureDepth, pTextureLightNear, pTextureLightFar, pTextureLightPoint );
	ppDraw_[ GraphicMain::PASS_SHADOW ] = pDrawerShadow;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicShadow::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Finalize();
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
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightNear	: 平行光源(近)の深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightFar		: 平行光源(遠)の深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightPoint	: 点光源の深度情報テクスチャ
//==============================================================================
int GraphicShadow::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pTextureDepth, pTextureLightNear, pTextureLightFar, pTextureLightPoint );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicShadow* pOut					: コピー先アドレス
//==============================================================================
int GraphicShadow::Copy( GraphicShadow* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void GraphicShadow::InitializeSelf( void )
{
	// メンバ変数の初期化
	pParameter_ = nullptr;
	pDrawerLight_ = nullptr;
}
