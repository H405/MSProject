//==============================================================================
//
// File   : DrawerBlur.cpp
// Brief  : ブラー描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/10 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerBlur.h"
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
DrawerBlur::DrawerBlur( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerBlur::~DrawerBlur( void )
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
// Arg    : IDirect3DTexture9* pTexture			: ブラーを掛けるテクスチャ
// Arg    : const D3DXVECTOR2& offset			: オフセット
//==============================================================================
int DrawerBlur::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTexture, const D3DXVECTOR2& offset )
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

	// ハンドルの読み込み
	result = pEffect_->LoadHandle( 1, PARAMETER_MAX );
	if( result != 0 )
	{
		return result;
	}

	// オフセットの設定
	pEffect->SetFloatArray( PARAMETER_OFFSET_BLUR, &offset.x, 2 );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int DrawerBlur::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTexture			: ブラーを掛けるテクスチャ
// Arg    : const D3DXVECTOR2& offset			: オフセット
//==============================================================================
int DrawerBlur::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTexture, const D3DXVECTOR2& offset )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pPolygon, pTexture, offset );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerBlur* pOut					: コピー先アドレス
//==============================================================================
int DrawerBlur::Copy( DrawerBlur* pOut ) const
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
void DrawerBlur::Draw( const D3DXMATRIX& matrixWorld )
{
	// 頂点シェーダ用パラメータ
	float	pOffset[ 2 ];		// オフセット
	pOffset[ 0 ] = 1.0f / pEffectParameter_->GetWidthScreen();
	pOffset[ 1 ] = 1.0f / pEffectParameter_->GetHeightScreen();
	pEffect_->SetFloatArray( PARAMETER_OFFSET, pOffset, 2 );

	// テクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );

	// 描画
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : ブラーを掛けるテクスチャの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void DrawerBlur::SetTexture( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : ブラーを掛けるテクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerBlur::GetTexture( void ) const
{
	// 値の返却
	return pTexture_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerBlur::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pPolygon_ = nullptr;
}
