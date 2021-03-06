//==============================================================================
//
// File   : GraphicMesh.cpp
// Brief  : メッシュポリゴン描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicMesh.h"
#include "../drawer/DrawerMesh.h"

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
GraphicMesh::GraphicMesh( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicMesh::~GraphicMesh( void )
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
// Arg    : PolygonMesh* pPolygon				: メッシュポリゴン
// Arg    : Material* pMaterial					: マテリアル
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicMesh::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	DrawerMesh*	pDrawerMesh = nullptr;		// 描画クラス
	pDrawerMesh = new DrawerMesh();
	if( pDrawerMesh == nullptr )
	{
		return 1;
	}
	result = pDrawerMesh->Initialize( pParameter, pEffectGeneral, pPolygon, pMaterial, pTexture );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerMesh;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicMesh::Finalize( void )
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
// Arg    : PolygonMesh* pPolygon				: メッシュポリゴン
// Arg    : Material* pMaterial					: マテリアル
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int GraphicMesh::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
	PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pPolygon, pMaterial, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicMesh* pOut					: コピー先アドレス
//==============================================================================
int GraphicMesh::Copy( GraphicMesh* pOut ) const
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
void GraphicMesh::InitializeSelf( void )
{
	// メンバ変数の初期化
}
