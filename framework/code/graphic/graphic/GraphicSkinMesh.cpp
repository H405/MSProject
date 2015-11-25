//==============================================================================
//
// File   : GraphicSkinMesh.cpp
// Brief  : スキンメッシュ描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicSkinMesh.h"
#include "../drawer/DrawerSkinMesh.h"
#include "../drawer/DrawerSkinMeshReflect.h"

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
GraphicSkinMesh::GraphicSkinMesh( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicSkinMesh::~GraphicSkinMesh( void )
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
// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
// Arg    : Model* pModel						: モデル
// Arg    : int countBone						: ボーン数
// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
// Arg    : int* pIndexFrame					: フレーム番号参照アドレス
//==============================================================================
int GraphicSkinMesh::Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Effect* pEffectReflect,
	Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 通常描画クラスの生成
	DrawerSkinMesh*	pDrawerSkinMesh = nullptr;		// 描画クラス
	pDrawerSkinMesh = new DrawerSkinMesh();
	if( pDrawerSkinMesh == nullptr )
	{
		return 1;
	}
	result = pDrawerSkinMesh->Initialize( pParameter, pEffectGeneral, pModel, countBone, pMatrixBone, pIndexFrame );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerSkinMesh;

	// 反射描画クラスの生成
	DrawerSkinMeshReflect*	pDrawerSkinMeshReflect = nullptr;		// 描画クラス
	pDrawerSkinMeshReflect = new DrawerSkinMeshReflect();
	if( pDrawerSkinMeshReflect == nullptr )
	{
		return 1;
	}
	result = pDrawerSkinMeshReflect->Initialize( pParameter, pEffectReflect, pModel, countBone, pMatrixBone, pIndexFrame );
	ppDraw_[ GraphicMain::PASS_REFLECT ] = pDrawerSkinMeshReflect;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicSkinMesh::Finalize( void )
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
// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
// Arg    : Model* pModel						: モデル
// Arg    : int countBone						: ボーン数
// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
// Arg    : int* pIndexFrame					: フレーム番号参照アドレス
//==============================================================================
int GraphicSkinMesh::Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Effect* pEffectReflect,
	Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, pEffectGeneral, pEffectReflect, pModel, countBone, pMatrixBone, pIndexFrame );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicSkinMesh* pOut				: コピー先アドレス
//==============================================================================
int GraphicSkinMesh::Copy( GraphicSkinMesh* pOut ) const
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
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : GraphicSkinMesh* pValue				: 設定する値
//==============================================================================
void GraphicSkinMesh::SetGraphic( GraphicSkinMesh* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicSkinMesh*					: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicSkinMesh* GraphicSkinMesh::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void GraphicSkinMesh::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
}
