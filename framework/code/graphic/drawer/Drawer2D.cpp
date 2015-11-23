//==============================================================================
//
// File   : Drawer2D.cpp
// Brief  : 2Dポリゴン描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Drawer2D.h"
#include "../../framework/resource/Effect.h"
#include "../../framework/polygon/Polygon2D.h"
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
Drawer2D::Drawer2D( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Drawer2D::~Drawer2D( void )
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
// Arg    : D3DXCOLOR* pColor					: 色
// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int Drawer2D::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture )
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
	pTexture_ = pTexture;
	pPolygon_ = pPolygon;
	pColor_ = pColor;
	pPositionTexture_ = pPositionTexture;
	pScaleTexture_ = pScaleTexture;

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
int Drawer2D::Finalize( void )
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
// Arg    : D3DXCOLOR* pColor					: 色
// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int Drawer2D::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pPolygon, pColor, pPositionTexture, pScaleTexture, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Drawer2D* pOut						: コピー先アドレス
//==============================================================================
int Drawer2D::Copy( Drawer2D* pOut ) const
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
void Drawer2D::Draw( const D3DXMATRIX& matrixWorld )
{
	// ワールド変換行列の設定
	D3DXMATRIX	matrixWorldSet;		// 設定するワールドマトリクス
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 *= 2.0f;
	matrixWorldSet._42 *= 2.0f;
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );

	// 画面サイズの設定
	float	pSizeScreen[ 2 ];		// 画面サイズ
	pSizeScreen[ 0 ] = pEffectParameter_->GetWidthScreen();
	pSizeScreen[ 1 ] = pEffectParameter_->GetHeightScreen();
	pEffect_->SetFloatArray( PARAMETER_SIZE_SCREEN, pSizeScreen, 2 );

	// テクスチャの設定
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );
	pEffect_->SetColor( PARAMETER_COLOR, *pColor_ );
	pEffect_->SetFloatArray( PARAMETER_POSITION_TEXTURE, &pPositionTexture_->x, 2 );
	pEffect_->SetFloatArray( PARAMETER_SCALE_TEXTURE, &pScaleTexture_->x, 2 );

	// 描画
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : テクスチャの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void Drawer2D::SetTexture( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* Drawer2D::GetTexture( void ) const
{
	// 値の返却
	return pTexture_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Drawer2D::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pPolygon_ = nullptr;
	pColor_ = nullptr;
	pPositionTexture_ = nullptr;
	pScaleTexture_ = nullptr;
}
