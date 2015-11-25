//==============================================================================
//
// File   : GraphicMerge.cpp
// Brief  : 総合3D描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicMerge.h"
#include "../drawer/DrawerMerge.h"
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
GraphicMerge::GraphicMerge( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicMerge::~GraphicMerge( void )
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
// Arg    : IDirect3DTexture9* pTextureLight	: ライトありテクスチャ
// Arg    : IDirect3DTexture9* pTextureNotLight	: ライトなしテクスチャ
// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
// Arg    : IDirect3DTexture9* pTextureAdd		: 加算合成テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
//==============================================================================
int GraphicMerge::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask,
	IDirect3DTexture9* pTextureAdd, IDirect3DTexture9* pTextureDepth )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	DrawerMerge*	pDrawerMerge = nullptr;		// 描画クラス
	pDrawerMerge = new DrawerMerge();
	if( pDrawerMerge == nullptr )
	{
		return 1;
	}
	result = pDrawerMerge->Initialize( pParameter, pEffectGeneral, pPolygon2D_, pTextureLight, pTextureNotLight, pTextureMask, pTextureAdd, pTextureDepth );
	ppDraw_[ GraphicMain::PASS_3D_MERGE ] = pDrawerMerge;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicMerge::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureLight	: ライトありテクスチャ
// Arg    : IDirect3DTexture9* pTextureNotLight	: ライトなしテクスチャ
// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
// Arg    : IDirect3DTexture9* pTextureAdd		: 加算合成テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
//==============================================================================
int GraphicMerge::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask,
	IDirect3DTexture9* pTextureAdd, IDirect3DTexture9* pTextureDepth )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pTextureLight, pTextureNotLight, pTextureMask, pTextureAdd, pTextureDepth );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicMerge* pOut					: コピー先アドレス
//==============================================================================
int GraphicMerge::Copy( GraphicMerge* pOut ) const
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
void GraphicMerge::InitializeSelf( void )
{
	// メンバ変数の初期化
}
