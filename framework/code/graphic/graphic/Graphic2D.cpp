//==============================================================================
//
// File   : Graphic2D.cpp
// Brief  : 2Dポリゴン描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Graphic2D.h"
#include "../drawer/Drawer2D.h"

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
Graphic2D::Graphic2D( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Graphic2D::~Graphic2D( void )
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
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int Graphic2D::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, D3DXCOLOR* pColor, IDirect3DTexture9* pTexture )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	Drawer2D*	pDrawer2D = nullptr;		// 描画クラス
	pDrawer2D = new Drawer2D();
	if( pDrawer2D == nullptr )
	{
		return 1;
	}
	result = pDrawer2D->Initialize( pParameter, pEffectGeneral, pPolygon2D_, pColor, pTexture );
	ppDraw_[ GraphicMain::PASS_GENERAL ] = pDrawer2D;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Graphic2D::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int Graphic2D::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, D3DXCOLOR* pColor, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pColor, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Graphic2D* pOut						: コピー先アドレス
//==============================================================================
int Graphic2D::Copy( Graphic2D* pOut ) const
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
void Graphic2D::InitializeSelf( void )
{
	// メンバ変数の初期化
}
