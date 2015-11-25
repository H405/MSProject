//==============================================================================
//
// File   : GraphicWaveDataInitialize.cpp
// Brief  : 波情報描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicWaveDataInitialize.h"
#include "../drawer/DrawerWaveDataInitialize.h"
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
GraphicWaveDataInitialize::GraphicWaveDataInitialize( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicWaveDataInitialize::~GraphicWaveDataInitialize( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicWaveDataInitialize::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTexture )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	DrawerWaveDataInitialize*	pDrawerWaveDataInitialize = nullptr;		// 描画クラス
	pDrawerWaveDataInitialize = new DrawerWaveDataInitialize();
	if( pDrawerWaveDataInitialize == nullptr )
	{
		return 1;
	}
	result = pDrawerWaveDataInitialize->Initialize( pParameter, pEffect, pPolygon2D_, pTexture );
	ppDraw_[ GraphicMain::PASS_WAVE_DATA ] = pDrawerWaveDataInitialize;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicWaveDataInitialize::Finalize( void )
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
// Arg    : Effect* pEffect						: エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicWaveDataInitialize::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffect, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicWaveDataInitialize* pOut		: コピー先アドレス
//==============================================================================
int GraphicWaveDataInitialize::Copy( GraphicWaveDataInitialize* pOut ) const
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
void GraphicWaveDataInitialize::InitializeSelf( void )
{
	// メンバ変数の初期化
}
