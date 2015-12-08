//==============================================================================
//
// File   : GraphicBlurShadow.cpp
// Brief  : 影用ブラー描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/12/08 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicBlurShadow.h"
#include "../drawer/DrawerBlurShadow.h"
#include "../../framework/resource/Effect.h"
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
GraphicBlurShadow::GraphicBlurShadow( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicBlurShadow::~GraphicBlurShadow( void )
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
// Arg    : IDirect3DTexture9* pTexture			: ブラーを掛けるテクスチャ
//==============================================================================
int GraphicBlurShadow::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTexture )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 通常描画クラスの生成
	DrawerBlurShadow*	pDrawerBlurShadow = nullptr;		// 描画クラス
	pDrawerBlurShadow = new DrawerBlurShadow();
	if( pDrawerBlurShadow == nullptr )
	{
		return 1;
	}
	result = pDrawerBlurShadow->Initialize( pParameter, pEffectGeneral, pPolygon2D_, pTexture );
	ppDraw_[ GraphicMain::PASS_BLUR_SHADOW ] = pDrawerBlurShadow;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicBlurShadow::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTexture			: ブラーを掛けるテクスチャ
//==============================================================================
int GraphicBlurShadow::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicBlurShadow* pOut				: コピー先アドレス
//==============================================================================
int GraphicBlurShadow::Copy( GraphicBlurShadow* pOut ) const
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
void GraphicBlurShadow::InitializeSelf( void )
{
	// メンバ変数の初期化
}
