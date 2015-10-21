//==============================================================================
//
// File   : Graphic3D.cpp
// Brief  : 3Dポリゴン描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Graphic3D.h"
#include "../drawer/Drawer3D.h"

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
Graphic3D::Graphic3D( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Graphic3D::~Graphic3D( void )
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
// Arg    : Material* pMaterial					: マテリアル
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int Graphic3D::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	Drawer3D*	pDrawer3D = nullptr;		// 描画クラス
	pDrawer3D = new Drawer3D();
	if( pDrawer3D == nullptr )
	{
		return 1;
	}
	result = pDrawer3D->Initialize( pParameter, pEffectGeneral, pPolygon3D_, pMaterial, pTexture );
	ppDraw_[ GraphicMain::PASS_GENERAL ] = pDrawer3D;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Graphic3D::Finalize( void )
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
// Arg    : Material* pMaterial					: マテリアル
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int Graphic3D::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pMaterial, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Graphic3D* pOut						: コピー先アドレス
//==============================================================================
int Graphic3D::Copy( Graphic3D* pOut ) const
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
void Graphic3D::InitializeSelf( void )
{
	// メンバ変数の初期化
}
