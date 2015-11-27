//==============================================================================
//
// File   : GraphicDrawTexture.cpp
// Brief  :デバッグテクスチャ描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicDrawTexture.h"
#include "../drawer/DrawerDrawTexture.h"
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
GraphicDrawTexture::GraphicDrawTexture( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicDrawTexture::~GraphicDrawTexture( void )
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
// Arg    : IDirect3DTexture9** pTexture		: テクスチャ
// Arg    : float* pMultiply					: 色の倍率
//==============================================================================
int GraphicDrawTexture::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9** ppTexture, float* pMultiply )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	DrawerDrawTexture*	pDrawerDrawTexture = nullptr;		// 描画クラス
	pDrawerDrawTexture = new DrawerDrawTexture();
	if( pDrawerDrawTexture == nullptr )
	{
		return 1;
	}
	result = pDrawerDrawTexture->Initialize( pParameter, pEffectGeneral, pPolygon2D_, ppTexture, pMultiply );
	ppDraw_[ GraphicMain::PASS_POST_EFFECT ] = pDrawerDrawTexture;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicDrawTexture::Finalize( void )
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
// Arg    : IDirect3DTexture9** pTexture		: テクスチャ
// Arg    : float* pMultiply					: 色の倍率
//==============================================================================
int GraphicDrawTexture::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9** ppTexture, float* pMultiply )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, ppTexture, pMultiply );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicDrawTexture* pOut					: コピー先アドレス
//==============================================================================
int GraphicDrawTexture::Copy( GraphicDrawTexture* pOut ) const
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
void GraphicDrawTexture::InitializeSelf( void )
{
	// メンバ変数の初期化
}
