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
// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: 正面環境マップテクスチャ
// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: 背面環境マップテクスチャ
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: 正面加算環境マップテクスチャ
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: 背面加算環境マップテクスチャ
//==============================================================================
int GraphicRiver::Initialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
	IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack )
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
	pDrawerRiver_ = new DrawerRiver[ GraphicMain::LIGHT_POINT_MAX + 1 ];
	if( pDrawerRiver_ == nullptr )
	{
		return 1;
	}
	for( int counterDrawer = 0; counterDrawer <= GraphicMain::LIGHT_POINT_MAX; ++counterDrawer )
	{
		result = pDrawerRiver_[ counterDrawer ].Initialize( pModel, pParameter, ppEffectGeneral[ counterDrawer ], pTextureNormal,
			pTextureEnvironmentFront, pTextureEnvironmentBack, pTextureEnvironmentAddFront, pTextureEnvironmentAddBack );
		if( result != 0 )
		{
			return result;
		}
	}
	ppDraw_[ GraphicMain::PASS_WATER ] = &pDrawerRiver_[ 0 ];

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
// Arg    : Effect** ppEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: 正面環境マップテクスチャ
// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: 背面環境マップテクスチャ
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: 正面加算環境マップテクスチャ
// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: 背面加算環境マップテクスチャ
//==============================================================================
int GraphicRiver::Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
	IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pModel, pParameter, ppEffectGeneral, pTextureNormal,
		pTextureEnvironmentFront, pTextureEnvironmentBack, pTextureEnvironmentAddFront, pTextureEnvironmentAddBack );
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
// Brief  : 描画処理
// Return : void								: なし
// Arg    : int index							: 描画番号
//==============================================================================
void GraphicRiver::Draw( int index )
{
	// ライトの数に応じて描画クラスを変更
	ppDraw_[ GraphicMain::PASS_WATER ] = &pDrawerRiver_[ pParameter_->GetCountLightPoint() ];

	// 基本クラスの処理
	Graphic::Draw( index );
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
