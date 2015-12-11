//==============================================================================
//
// File   : GraphicMain.cpp
// Brief  : 描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicMain.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
Polygon2D*			GraphicMain::pPolygon2D_ = nullptr;				// 2Dポリゴンクラス
Polygon3D*			GraphicMain::pPolygon3D_ = nullptr;				// 3Dポリゴンクラス
PolygonBillboard*	GraphicMain::pPolygonBillboard_ = nullptr;		// ビルボードポリゴンクラス
PolygonSignboard*	GraphicMain::pPolygonSignboard_ = nullptr;		// 足元基準ビルボードポリゴンクラス

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicMain::GraphicMain( void ) : Graphic()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicMain::~GraphicMain( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
//==============================================================================
int GraphicMain::Initialize( int priority )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Graphic::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラス格納領域の確保
	countDraw_ = GraphicMain::PASS_MAX;
	ppDraw_ = new Drawer*[ GraphicMain::PASS_MAX ];
	if( ppDraw_ == nullptr )
	{
		return 1;
	}
	for( int counterDrawer = 0; counterDrawer < GraphicMain::PASS_MAX; ++counterDrawer )
	{
		ppDraw_[ counterDrawer ] = nullptr;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicMain::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Graphic::Finalize();
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
//==============================================================================
int GraphicMain::Reinitialize( int priority )
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
// Arg    : GraphicMain* pOut					: コピー先アドレス
//==============================================================================
int GraphicMain::Copy( GraphicMain* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Graphic::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 2Dポリゴンクラスの設定
// Return : void								: なし
// Arg    : Polygon2D* pValue					: 設定する値
//==============================================================================
void GraphicMain::SetPolygon2D( Polygon2D* pValue )
{
	// 値の設定
	pPolygon2D_ = pValue;
}

//==============================================================================
// Brief  : 3Dポリゴンクラスの設定
// Return : void								: なし
// Arg    : Polygon3D* pValue					: 設定する値
//==============================================================================
void GraphicMain::SetPolygon3D( Polygon3D* pValue )
{
	// 値の設定
	pPolygon3D_ = pValue;
}

//==============================================================================
// Brief  : ビルボードポリゴンクラスの設定
// Return : void								: なし
// Arg    : PolygonBillboard* pValue			: 設定する値
//==============================================================================
void GraphicMain::SetPolygonBillboard( PolygonBillboard* pValue )
{
	// 値の設定
	pPolygonBillboard_ = pValue;
}

//==============================================================================
// Brief  : 足元基準ビルボードポリゴンクラスの設定
// Return : void								: なし
// Arg    : PolygonSignboard* pValue			: 設定する値
//==============================================================================
void GraphicMain::SetPolygonSignboard( PolygonSignboard* pValue )
{
	// 値の設定
	pPolygonSignboard_ = pValue;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void GraphicMain::InitializeSelf( void )
{
	// メンバ変数の初期化
}
