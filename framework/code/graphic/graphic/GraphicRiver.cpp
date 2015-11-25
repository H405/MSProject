//==============================================================================
//
// File   : GraphicRiver.cpp
// Brief  : 川描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicRiver.h"
#include "../drawer/DrawerRiver.h"
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
GraphicRiver::GraphicRiver( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicRiver::~GraphicRiver( void )
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
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
// Arg    : IDirect3DTexture9* pTextureReflect	: 反射テクスチャ
// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: 反射ライティングなしテクスチャ
// Arg    : IDirect3DTexture9* pTextureReflectAdd		: 反射加算合成テクスチャ
// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
//==============================================================================
int GraphicRiver::Initialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureNormal,
	IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = GraphicMain::Initialize( priority );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pParameter_ = pParameter;

	// 描画クラスの生成
	pDrawerRiver_ = new DrawerRiver();
	if( pDrawerRiver_ == nullptr )
	{
		return 1;
	}
	result = pDrawerRiver_->Initialize( pModel, pParameter, pEffectGeneral, pTextureNormal, pTextureReflect, pTextureReflectNotLight, pTextureReflectAdd,
		pTexture3D, pTextureDepth );
	if( result != 0 )
	{
		return result;
	}
	ppDraw_[ GraphicMain::PASS_WATER ] = pDrawerRiver_;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicRiver::Finalize( void )
{
	// 格納領域の開放
	delete[] pDrawerRiver_;
	pDrawerRiver_ = nullptr;
	ppDraw_[ GraphicMain::PASS_WATER ] = nullptr;

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
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
// Arg    : IDirect3DTexture9* pTextureReflect	: 反射テクスチャ
// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: 反射ライティングなしテクスチャ
// Arg    : IDirect3DTexture9* pTextureReflectAdd		: 反射加算合成テクスチャ
// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
//==============================================================================
int GraphicRiver::Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureNormal,
	IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pModel, pParameter, pEffectGeneral, pTextureNormal, pTextureReflect, pTextureReflectNotLight, pTextureReflectAdd,
		pTexture3D, pTextureDepth );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicRiver* pOut					: コピー先アドレス
//==============================================================================
int GraphicRiver::Copy( GraphicRiver* pOut ) const
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
void GraphicRiver::InitializeSelf( void )
{
	// メンバ変数の初期化
	pParameter_ = nullptr;
	pDrawerRiver_ = nullptr;
}
