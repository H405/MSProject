//==============================================================================
//
// File   : GraphicModelMaterial.cpp
// Brief  : モデル描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicModelMaterial.h"
#include "../drawer/DrawerModelMaterial.h"
#include "../drawer/DrawerModelMaterialReflect.h"
#include "../drawer/DrawerModelParaboloid.h"
#include "../drawer/DrawerModelShadow.h"

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
GraphicModelMaterial::GraphicModelMaterial( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicModelMaterial::~GraphicModelMaterial( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : Model* pModel						: モデル
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
// Arg    : Effect* pEffectShadow				: 影描画エフェクト
// Arg    : Effect* pEffectParaboloid			: 放物変換描画エフェクト
//==============================================================================
int GraphicModelMaterial::Initialize( int priority, Model* pModel, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// 通常描画クラスの生成
	DrawerModelMaterial*	pDrawerModelMaterial = nullptr;		// 描画クラス
	pDrawerModelMaterial = new DrawerModelMaterial();
	if( pDrawerModelMaterial == nullptr )
	{
		return 1;
	}
	result = pDrawerModelMaterial->Initialize( pModel, pParameter, pEffectGeneral );
	ppDraw_[ GraphicMain::PASS_3D ] = pDrawerModelMaterial;

	// 反射描画クラスの生成
	DrawerModelMaterialReflect*	pDrawerModelMaterialReflect = nullptr;		// 描画クラス
	pDrawerModelMaterialReflect = new DrawerModelMaterialReflect();
	if( pDrawerModelMaterialReflect == nullptr )
	{
		return 1;
	}
	result = pDrawerModelMaterialReflect->Initialize( pModel, pParameter, pEffectReflect );
	ppDraw_[ GraphicMain::PASS_REFLECT ] = pDrawerModelMaterialReflect;

	// 影(近)描画クラスの生成
	DrawerModelShadow*	pDrawerModelShadowNear = nullptr;		// 描画クラス
	pDrawerModelShadowNear = new DrawerModelShadow();
	if( pDrawerModelShadowNear == nullptr )
	{
		return 1;
	}
	result = pDrawerModelShadowNear->Initialize( pModel, pParameter, pEffectShadow, GraphicMain::CAMERA_SHADOW_NEAR );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_NEAR ] = pDrawerModelShadowNear;

	// 影(遠)描画クラスの生成
	DrawerModelShadow*	pDrawerModelShadowFar = nullptr;		// 描画クラス
	pDrawerModelShadowFar = new DrawerModelShadow();
	if( pDrawerModelShadowFar == nullptr )
	{
		return 1;
	}
	result = pDrawerModelShadowFar->Initialize( pModel, pParameter, pEffectShadow, GraphicMain::CAMERA_SHADOW_FAR );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_FAR ] = pDrawerModelShadowFar;

	// 影(点0)描画クラスの生成
	DrawerModelParaboloid*	pDrawerModelParaboloid0 = nullptr;		// 描画クラス
	pDrawerModelParaboloid0 = new DrawerModelParaboloid();
	if( pDrawerModelParaboloid0 == nullptr )
	{
		return 1;
	}
	result = pDrawerModelParaboloid0->Initialize( pModel, pParameter, pEffectParaboloid, GraphicMain::CAMERA_SHADOW_POINT_0 );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_POINT_0 ] = pDrawerModelParaboloid0;

	// 影(点1)描画クラスの生成
	DrawerModelParaboloid*	pDrawerModelParaboloid1 = nullptr;		// 描画クラス
	pDrawerModelParaboloid1 = new DrawerModelParaboloid();
	if( pDrawerModelParaboloid1 == nullptr )
	{
		return 1;
	}
	result = pDrawerModelParaboloid1->Initialize( pModel, pParameter, pEffectParaboloid, GraphicMain::CAMERA_SHADOW_POINT_1 );
	ppDraw_[ GraphicMain::PASS_DEPTH_SHADOW_POINT_1 ] = pDrawerModelParaboloid1;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicModelMaterial::Finalize( void )
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
// Arg    : Model* pModel						: モデル
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
// Arg    : Effect* pEffectShadow				: 影描画エフェクト
// Arg    : Effect* pEffectParaboloid			: 放物変換描画エフェクト
//==============================================================================
int GraphicModelMaterial::Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pModel, pParameter, pEffectGeneral, pEffectReflect, pEffectShadow, pEffectParaboloid );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicModelMaterial* pOut			: コピー先アドレス
//==============================================================================
int GraphicModelMaterial::Copy( GraphicModelMaterial* pOut ) const
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
void GraphicModelMaterial::InitializeSelf( void )
{
	// メンバ変数の初期化
}
