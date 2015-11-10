//==============================================================================
//
// File   : GraphicBlur.cpp
// Brief  : ブラー基描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/10 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicBlur.h"
#include "../drawer/DrawerBlur.h"
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
GraphicBlur::GraphicBlur( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicBlur::~GraphicBlur( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectX					: X方向ブラーエフェクト
// Arg    : Effect* pEffectY					: Y方向ブラーエフェクト
// Arg    : IDirect3DTexture9* pTextureX		: X方向ブラーを掛けるテクスチャ
// Arg    : IDirect3DTexture9* pTextureY		: Y方向ブラーを掛けるテクスチャ
//==============================================================================
int GraphicBlur::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectX, Effect* pEffectY,
	IDirect3DTexture9* pTextureX, IDirect3DTexture9* pTextureY )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// X方向描画クラスの生成
	DrawerBlur*	pDrawerBlurX = nullptr;		// 描画クラス
	D3DXVECTOR2	offsetX;					// X方向オフセット
	offsetX.x = 32.0f / pParameter->GetWidthScreen();
	offsetX.y = 0.0f;
	pDrawerBlurX = new DrawerBlur();
	if( pDrawerBlurX == nullptr )
	{
		return 1;
	}
	result = pDrawerBlurX->Initialize( pParameter, pEffectX, pPolygon2D_, pTextureX, offsetX );
	ppDraw_[ GraphicMain::PASS_BLUR_X ] = pDrawerBlurX;

	// Y方向描画クラスの生成
	DrawerBlur*	pDrawerBlurY = nullptr;		// 描画クラス
	D3DXVECTOR2	offsetY;					// Y方向オフセット
	offsetY.x = 0.0f;
	offsetY.y = 32.0f / pParameter->GetHeightScreen();
	pDrawerBlurY = new DrawerBlur();
	if( pDrawerBlurY == nullptr )
	{
		return 1;
	}
	result = pDrawerBlurY->Initialize( pParameter, pEffectY, pPolygon2D_, pTextureY, offsetY );
	ppDraw_[ GraphicMain::PASS_BLUR_Y ] = pDrawerBlurY;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicBlur::Finalize( void )
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
// Arg    : Effect* pEffectX					: X方向ブラーエフェクト
// Arg    : Effect* pEffectY					: Y方向ブラーエフェクト
// Arg    : IDirect3DTexture9* pTextureX		: X方向ブラーを掛けるテクスチャ
// Arg    : IDirect3DTexture9* pTextureY		: Y方向ブラーを掛けるテクスチャ
//==============================================================================
int GraphicBlur::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectX, Effect* pEffectY,
	IDirect3DTexture9* pTextureX, IDirect3DTexture9* pTextureY )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectX, pEffectY, pTextureX, pTextureY );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicBlur* pOut					: コピー先アドレス
//==============================================================================
int GraphicBlur::Copy( GraphicBlur* pOut ) const
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
void GraphicBlur::InitializeSelf( void )
{
	// メンバ変数の初期化
}
