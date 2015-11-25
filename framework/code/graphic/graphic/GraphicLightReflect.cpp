//==============================================================================
//
// File   : GraphicLightReflect.cpp
// Brief  : 反射ライト描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/22 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicLightReflect.h"
#include "../drawer/DrawerLightReflect.h"
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
GraphicLightReflect::GraphicLightReflect( void ) : GraphicMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
GraphicLightReflect::~GraphicLightReflect( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
//==============================================================================
int GraphicLightReflect::Initialize( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
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
	pDrawerLight_ = new DrawerLightReflect[ GraphicMain::LIGHT_POINT_MAX + 1 ];
	if( pDrawerLight_ == nullptr )
	{
		return 1;
	}
	for( int counterDrawer = 0; counterDrawer <= GraphicMain::LIGHT_POINT_MAX; ++counterDrawer )
	{
		result = pDrawerLight_[ counterDrawer ].Initialize( pParameter, ppEffectGeneral[ counterDrawer ], pPolygon2D_, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth );
		if( result != 0 )
		{
			return result;
		}
	}
	ppDraw_[ GraphicMain::PASS_LIGHT_REFLECT ] = &pDrawerLight_[ 0 ];

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int GraphicLightReflect::Finalize( void )
{
	// 格納領域の開放
	delete[] pDrawerLight_;
	pDrawerLight_ = nullptr;
	ppDraw_[ GraphicMain::PASS_LIGHT_REFLECT ] = nullptr;

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
// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
//==============================================================================
int GraphicLightReflect::Reinitialize( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
	IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority, pParameter, ppEffectGeneral, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : GraphicLightReflect* pOut			: コピー先アドレス
//==============================================================================
int GraphicLightReflect::Copy( GraphicLightReflect* pOut ) const
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
void GraphicLightReflect::Draw( int index )
{
	// ライトの数に応じて描画クラスを変更
	ppDraw_[ GraphicMain::PASS_LIGHT_REFLECT ] = &pDrawerLight_[ pParameter_->GetCountLightPoint() ];

	// 基本クラスの処理
	Graphic::Draw( index );
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void GraphicLightReflect::InitializeSelf( void )
{
	// メンバ変数の初期化
	pParameter_ = nullptr;
	pDrawerLight_ = nullptr;
}
