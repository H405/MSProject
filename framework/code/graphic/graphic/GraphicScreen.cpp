//==============================================================================
//
// File   : GraphicScreen.cpp
// Brief  : 画面ポリゴン描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicScreen.h"
#include "../drawer/DrawerScreen.h"

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
GraphicScreen::GraphicScreen( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicScreen::~GraphicScreen( void )
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
// Arg    : const float* pProportionFade		: フェード割合
// Arg    : IDirect3DTexture9* pTextureGeneral	: 通常描画テクスチャ
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicScreen::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
	IDirect3DTexture9* pTextureGeneral, IDirect3DTexture9* pTexture )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pTexture_ = pTexture;

	// 描画クラスの生成
	DrawerScreen*	pDrawerScreen = nullptr;		// 描画クラス
	pDrawerScreen = new DrawerScreen();
	if( pDrawerScreen == nullptr )
	{
		return 1;
	}
	result = pDrawerScreen->Initialize( pParameter, pEffectGeneral, pPolygon2D_, pTextureGeneral, pTexture, &colorFade_, pProportionFade );
	ppDraw_[ GraphicMain::PASS_SCREEN ] = pDrawerScreen;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicScreen::Finalize( void )
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
// Arg    : const float* pProportionFade		: フェード割合
// Arg    : IDirect3DTexture9* pTextureGeneral	: 通常描画テクスチャ
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicScreen::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
	IDirect3DTexture9* pTextureGeneral, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pProportionFade, pTextureGeneral, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicScreen* pOut						: コピー先アドレス
//==============================================================================
int GraphicScreen::Copy( GraphicScreen* pOut ) const
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
void GraphicScreen::InitializeSelf( void )
{
	// メンバ変数の初期化
	pTexture_ = nullptr;
	colorFade_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
}
