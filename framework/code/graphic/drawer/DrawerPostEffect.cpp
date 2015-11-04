//==============================================================================
//
// File   : DrawerPostEffect.cpp
// Brief  : 画面ポリゴン描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerPostEffect.h"
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
DrawerPostEffect::DrawerPostEffect( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerPostEffect::~DrawerPostEffect( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: 描画エフェクト
// Arg    : Polygon2D* pPolygon					: 画面ポリゴン
// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
// Arg    : IDirect3DTexture9* pTexture2D		: 2D描画テクスチャ
// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
// Arg    : const D3DXCOLOR* pColorFade			: フェードの色
// Arg    : const float* pProportionFade		: フェードの割合
//==============================================================================
int DrawerPostEffect::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture,
	const D3DXCOLOR* pColorFade, const float* pProportionFade )
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
	pTexture3D_ = pTexture3D;
	pTexture2D_ = pTexture2D;
	pTextureMask_ = pTextureMask;
	pPolygon_ = pPolygon;
	pColorFade_ = pColorFade;
	pProportionFade_ = pProportionFade;

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
int DrawerPostEffect::Finalize( void )
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
// Arg    : Polygon2D* pPolygon					: 画面ポリゴン
// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
// Arg    : IDirect3DTexture9* pTexture2D		: 2D描画テクスチャ
// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
// Arg    : const D3DXCOLOR* pColorFade			: フェードの色
// Arg    : const float* pProportionFade		: フェードの割合
//==============================================================================
int DrawerPostEffect::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture,
	const D3DXCOLOR* pColorFade, const float* pProportionFade )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pPolygon, pTexture, pTexture3D_, pTexture2D, pTextureMask, pColorFade, pProportionFade );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerPostEffect* pOut				: コピー先アドレス
//==============================================================================
int DrawerPostEffect::Copy( DrawerPostEffect* pOut ) const
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
void DrawerPostEffect::Draw( const D3DXMATRIX& matrixWorld )
{
	// パラメータの設定
	D3DXMATRIX	matrixWorldSet;		// 設定するワールドマトリクス
	D3DCOLOR	colorFade;			// フェード色
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 -= 0.5f;
	matrixWorldSet._42 -= 0.5f;
	colorFade = *pColorFade_;
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_3D, pTexture3D_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_2D, pTexture2D_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_MASK, pTextureMask_ );
	pEffect_->SetColor( PARAMETER_COLOR_FADE, colorFade );
	pEffect_->SetFloat( PARAMETER_WIDTH_SCREEN_HALF, pEffectParameter_->GetWidthScreen() * 0.5f );
	pEffect_->SetFloat( PARAMETER_HEIGHT_SCREEN_HALF, pEffectParameter_->GetHeightScreen() * 0.5f );
	pEffect_->SetFloat( PARAMETER_PROPORTION_FADE, *pProportionFade_ );

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
void DrawerPostEffect::SetTexture( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerPostEffect::GetTexture( void ) const
{
	// 値の返却
	return pTexture_;
}

//==============================================================================
// Brief  : ポリゴンの設定
// Return : void								: なし
// Arg    : Polygon2D* pValue					: 設定する値
//==============================================================================
void DrawerPostEffect::SetPolygon( Polygon2D* pValue )
{
	// 値の設定
	pPolygon_ = pValue;
}

//==============================================================================
// Brief  : ポリゴンの取得
// Return : Polygon2D*							: 返却する値
// Arg    : void								: なし
//==============================================================================
Polygon2D* DrawerPostEffect::GetPolygon( void ) const
{
	// 値の返却
	return pPolygon_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerPostEffect::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pTexture3D_ = nullptr;
	pTexture2D_ = nullptr;
	pTextureMask_ = nullptr;
	pPolygon_ = nullptr;
	pColorFade_ = nullptr;
	pProportionFade_ = nullptr;
}
