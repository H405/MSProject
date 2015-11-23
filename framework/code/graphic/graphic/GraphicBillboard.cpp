//==============================================================================
//
// File   : GraphicBillboard.cpp
// Brief  : ビルボードポリゴン描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/23 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicBillboard.h"
#include "../drawer/DrawerBillboard.h"

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
GraphicBillboard::GraphicBillboard( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicBillboard::~GraphicBillboard( void )
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
// Arg    : D3DXCOLOR* pColor					: 色
// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicBillboard::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	DrawerBillboard*	pDrawerBillboard = nullptr;		// 描画クラス
	pDrawerBillboard = new DrawerBillboard();
	if( pDrawerBillboard == nullptr )
	{
		return 1;
	}
	result = pDrawerBillboard->Initialize( pParameter, pEffectGeneral, pPolygonBillboard_, pColor, pPositionTexture, pScaleTexture, pTexture );
	ppDraw_[ GraphicMain::PASS_3D_NOT_LIGHT ] = pDrawerBillboard;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicBillboard::Finalize( void )
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
// Arg    : D3DXCOLOR* pColor					: 色
// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicBillboard::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pColor, pPositionTexture, pScaleTexture, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicBillboard* pOut				: コピー先アドレス
//==============================================================================
int GraphicBillboard::Copy( GraphicBillboard* pOut ) const
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
void GraphicBillboard::InitializeSelf( void )
{
	// メンバ変数の初期化
}
