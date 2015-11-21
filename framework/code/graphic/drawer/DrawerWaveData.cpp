//==============================================================================
//
// File   : DrawerWaveData.cpp
// Brief  : 波情報描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerWaveData.h"
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
DrawerWaveData::DrawerWaveData( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerWaveData::~DrawerWaveData( void )
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
// Arg    : IDirect3DTexture9* pTextureHeight0	: 高さテクスチャ0
// Arg    : IDirect3DTexture9* pTextureHeight1	: 高さテクスチャ1
//==============================================================================
int DrawerWaveData::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 )
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
	pTextureHeight0_ = pTextureHeight0;
	pTextureHeight1_ = pTextureHeight1;
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
int DrawerWaveData::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureHeight0	: 高さテクスチャ0
// Arg    : IDirect3DTexture9* pTextureHeight1	: 高さテクスチャ1
//==============================================================================
int DrawerWaveData::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pPolygon, pTextureHeight0, pTextureHeight1 );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerWaveData* pOut				: コピー先アドレス
//==============================================================================
int DrawerWaveData::Copy( DrawerWaveData* pOut ) const
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
void DrawerWaveData::Draw( const D3DXMATRIX& matrixWorld )
{
	// 頂点シェーダ用パラメータ
	D3DXMATRIX	matrixWorldSet;			// 設定するワールドマトリクス
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 -= 0.5f;
	matrixWorldSet._42 += 0.5f;
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );

	// テクスチャ
	isTexture0_ = !isTexture0_;
	pEffect_->SetTexture( PARAMETER_TEXTURE_HEIGHT, (isTexture0_ ? pTextureHeight0_ : pTextureHeight1_) );

	// 追加波
	float	pWaveAdd[ 3 ];		// 追加する波
	pWaveAdd[ 0 ] = static_cast< float >( rand() ) / RAND_MAX;
	pWaveAdd[ 1 ] = static_cast< float >( rand() ) / RAND_MAX;
	pWaveAdd[ 2 ] = 0.2f * (static_cast< float >( rand() ) / RAND_MAX - 0.5f);
	pEffect_->SetFloatArray( PARAMETER_WAVE_ADD, pWaveAdd, 3 );

	// 描画
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerWaveData::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTextureHeight0_ = nullptr;
	pTextureHeight1_ = nullptr;
	pPolygon_ = nullptr;
	isTexture0_ = true;
}
