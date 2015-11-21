//==============================================================================
//
// File   : GraphicWaveData.cpp
// Brief  : 波情報描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicWaveData.h"
#include "../drawer/DrawerWaveData.h"
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
GraphicWaveData::GraphicWaveData( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicWaveData::~GraphicWaveData( void )
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
// Arg    : IDirect3DTexture9* pTextureHeight0	: 高さテクスチャ0
// Arg    : IDirect3DTexture9* pTextureHeight1	: 高さテクスチャ1
//==============================================================================
int GraphicWaveData::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffect,
	IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	DrawerWaveData*	pDrawerWaveData = nullptr;		// 描画クラス
	pDrawerWaveData = new DrawerWaveData();
	if( pDrawerWaveData == nullptr )
	{
		return 1;
	}
	result = pDrawerWaveData->Initialize( pParameter, pEffect, pPolygon2D_, pTextureHeight0, pTextureHeight1 );
	ppDraw_[ GraphicMain::PASS_WAVE_DATA ] = pDrawerWaveData;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicWaveData::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureHeight0	: 高さテクスチャ0
// Arg    : IDirect3DTexture9* pTextureHeight1	: 高さテクスチャ1
//==============================================================================
int GraphicWaveData::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffect,
	IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffect, pTextureHeight0, pTextureHeight1 );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicWaveData* pOut				: コピー先アドレス
//==============================================================================
int GraphicWaveData::Copy( GraphicWaveData* pOut ) const
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
void GraphicWaveData::InitializeSelf( void )
{
	// メンバ変数の初期化
}
