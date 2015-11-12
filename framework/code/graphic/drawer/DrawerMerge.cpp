//==============================================================================
//
// File   : DrawerMerge.cpp
// Brief  : 総合3D描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerMerge.h"
#include "../../framework/polygon/Polygon2D.h"
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
DrawerMerge::DrawerMerge( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerMerge::~DrawerMerge( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: 描画エフェクト
// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
// Arg    : IDirect3DTexture9* pTextureLight	: ライトありテクスチャ
// Arg    : IDirect3DTexture9* pTextureNotLight	: ライトなしテクスチャ
// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
// Arg    : IDirect3DTexture9* pTextureAdd		: 加算合成テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
//==============================================================================
int DrawerMerge::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
	IDirect3DTexture9* pTextureDepth )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Drawer::Initialize();
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pEffectParameter_ = pParameter;
	pEffect_ = pEffect;
	pTextureLight_ = pTextureLight;
	pTextureNotLight_ = pTextureNotLight;
	pTextureMask_ = pTextureMask;
	pTextureAdd_ = pTextureAdd;
	pTextureDepth_ = pTextureDepth;
	pPolygon_ = pPolygon;

	// ハンドルの読み込み
	result = pEffect_->LoadHandle( 1, PARAMETER_MAX );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int DrawerMerge::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Drawer::Finalize();
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
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: 描画エフェクト
// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
// Arg    : IDirect3DTexture9* pTextureLight	: ライトありテクスチャ
// Arg    : IDirect3DTexture9* pTextureNotLight	: ライトなしテクスチャ
// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
// Arg    : IDirect3DTexture9* pTextureAdd		: 加算合成テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
//==============================================================================
int DrawerMerge::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
	IDirect3DTexture9* pTextureDepth )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pPolygon, pTextureLight, pTextureNotLight, pTextureMask, pTextureAdd, pTextureDepth );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerMerge* pOut					: コピー先アドレス
//==============================================================================
int DrawerMerge::Copy( DrawerMerge* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Drawer::Copy( pOut );
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
// Arg    : const D3DXMATRIX& matrixWorld		: ワールドマトリクス
//==============================================================================
void DrawerMerge::Draw( const D3DXMATRIX& matrixWorld )
{
	// 頂点シェーダ用パラメータ
	D3DXMATRIX	matrixWorldSet;			// 設定するワールドマトリクス
	float		pSizeScreen[ 2 ];		// 画面のサイズ
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 -= 0.5f;
	matrixWorldSet._42 -= 0.5f;
	pSizeScreen[ 0 ] = 0.5f * pEffectParameter_->GetWidthScreen();
	pSizeScreen[ 1 ] = 0.5f * pEffectParameter_->GetHeightScreen();
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );
	pEffect_->SetFloatArray( PARAMETER_SIZE_SCREEN_HALF, pSizeScreen, 2 );

	// 焦点距離の設定
	pEffect_->SetFloat( PARAMETER_FORCUS, pEffectParameter_->GetForcus() );

	// 3D情報テクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE_LIGHT, pTextureLight_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_NOT_LIGHT, pTextureNotLight_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_MASK, pTextureMask_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_ADD, pTextureAdd_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH, pTextureDepth_ );

	// 描画
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : ライトありテクスチャの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void DrawerMerge::SetTextureLight( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTextureLight_ = pValue;
}

//==============================================================================
// Brief  : ライトありテクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerMerge::GetTextureLight( void ) const
{
	// 値の返却
	return pTextureLight_;
}

//==============================================================================
// Brief  : ライトなしテクスチャの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void DrawerMerge::SetTextureNotLight( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTextureNotLight_ = pValue;
}

//==============================================================================
// Brief  : ライトなしテクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerMerge::GetTextureNotLight( void ) const
{
	// 値の返却
	return pTextureNotLight_;
}

//==============================================================================
// Brief  : マスクテクスチャの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void DrawerMerge::SetTextureMask( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTextureMask_ = pValue;
}

//==============================================================================
// Brief  : マスクテクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerMerge::GetTextureMask( void ) const
{
	// 値の返却
	return pTextureMask_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerMerge::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTextureLight_ = nullptr;
	pTextureNotLight_ = nullptr;
	pTextureMask_ = nullptr;
	pTextureAdd_ = nullptr;
	pTextureDepth_ = nullptr;
	pPolygon_ = nullptr;
}
