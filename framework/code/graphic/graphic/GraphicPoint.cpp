//==============================================================================
//
// File   : GraphicPoint.cpp
// Brief  : ポイントスプライト描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicPoint.h"
#include "../drawer/DrawerPoint.h"

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
GraphicPoint::GraphicPoint( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicPoint::~GraphicPoint( void )
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
// Arg    : PolygonPoint* pPolygon				: ポイントスプライトポリゴン
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicPoint::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, PolygonPoint* pPolygon, IDirect3DTexture9* pTexture )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	DrawerPoint*	pDrawerPoint = nullptr;		// 描画クラス
	pDrawerPoint = new DrawerPoint();
	if( pDrawerPoint == nullptr )
	{
		return 1;
	}
	result = pDrawerPoint->Initialize( pParameter, pEffectGeneral, pPolygon, pTexture );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerPoint;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicPoint::Finalize( void )
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
// Arg    : PolygonPoint* pPolygon				: ポイントスプライトポリゴン
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicPoint::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, PolygonPoint* pPolygon, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pPolygon, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicPoint* pOut					: コピー先アドレス
//==============================================================================
int GraphicPoint::Copy( GraphicPoint* pOut ) const
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
void GraphicPoint::InitializeSelf( void )
{
	// メンバ変数の初期化
}
