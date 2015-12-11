//==============================================================================
//
// File   : GraphicGrass.cpp
// Brief  : 草描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/12/11 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicGrass.h"
#include "../drawer/DrawerGrass.h"

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
GraphicGrass::GraphicGrass( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicGrass::~GraphicGrass( void )
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
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
// Arg    : float hardness						: 硬さ
//==============================================================================
int GraphicGrass::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTexture, float hardness )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	DrawerGrass*	pDrawerGrass = nullptr;		// 描画クラス
	pDrawerGrass = new DrawerGrass();
	if( pDrawerGrass == nullptr )
	{
		return 1;
	}
	result = pDrawerGrass->Initialize( pParameter, pEffectGeneral, pPolygonSignboard_, pTexture, hardness );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerGrass;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicGrass::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
// Arg    : float hardness						: 硬さ
//==============================================================================
int GraphicGrass::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTexture, float hardness )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pTexture, hardness );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicGrass* pOut				: コピー先アドレス
//==============================================================================
int GraphicGrass::Copy( GraphicGrass* pOut ) const
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
void GraphicGrass::InitializeSelf( void )
{
	// メンバ変数の初期化
}
