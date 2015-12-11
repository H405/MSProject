//==============================================================================
//
// File   : DrawerGrass.cpp
// Brief  : 草描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/12/11 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerGrass.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/polygon/PolygonSignboard.h"
#include "../../framework/render/RenderMatrix.h"
#include "../../framework/resource/Effect.h"
#include "../../graphic/graphic/GraphicMain.h"
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
DrawerGrass::DrawerGrass( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerGrass::~DrawerGrass( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: 描画エフェクト
// Arg    : PolygonSignboard* pPolygon			: ビルボードポリゴン
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
// Arg    : float hardness						: 硬さ
//==============================================================================
int DrawerGrass::Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonSignboard* pPolygon,
	IDirect3DTexture9* pTexture, float hardness )
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
	hardness_ = hardness;

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
int DrawerGrass::Finalize( void )
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
// Arg    : PolygonSignboard* pPolygon			: ビルボードポリゴン
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
// Arg    : float hardness						: 硬さ
//==============================================================================
int DrawerGrass::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonSignboard* pPolygon,
	IDirect3DTexture9* pTexture, float hardness )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pPolygon, pTexture, hardness );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerGrass* pOut				: コピー先アドレス
//==============================================================================
int DrawerGrass::Copy( DrawerGrass* pOut ) const
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
void DrawerGrass::Draw( const D3DXMATRIX& matrixWorld )
{
	// 必要な情報を取得
	D3DXMATRIX		matrixTransform;				// 変換行列
	D3DXMATRIX		matrixViewProjection;			// ビュープロジェクション行列
	const Camera*	pCamera = nullptr;				// カメラ
	RenderMatrix*	pRenderMatrix = nullptr;		// レンダーマトリクス
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );

	// 転置ビュー行列を求める
	D3DXMATRIX	matrixView;				// ビュー行列
	D3DXMATRIX	matrixViewInverse;		// 転置ビュー行列
	pRenderMatrix->GetMatrixView( &matrixView );
	matrixViewInverse._11 = matrixView._11;
	matrixViewInverse._22 = matrixView._22;
	matrixViewInverse._33 = matrixView._33;
	matrixViewInverse._44 = matrixView._44;
	matrixViewInverse._12 = matrixView._21;
	matrixViewInverse._13 = matrixView._31;
	matrixViewInverse._21 = matrixView._12;
	matrixViewInverse._23 = matrixView._32;
	matrixViewInverse._31 = matrixView._13;
	matrixViewInverse._32 = matrixView._23;
	matrixViewInverse._14 = matrixViewInverse._24 = matrixViewInverse._34 = matrixViewInverse._41 = matrixViewInverse._42 = matrixViewInverse._43 = 0.0f;

	// 変換行列
	D3DXVECTOR3	translate;		// 平行移動
	matrixTransform = matrixWorld;
	translate.x = matrixWorld._41;
	translate.y = matrixWorld._42;
	translate.z = matrixWorld._43;
	matrixTransform._41 = matrixTransform._42 = matrixTransform._43 = 0.0f;
	D3DXMatrixMultiply( &matrixTransform, &matrixTransform, &matrixViewInverse );
	matrixTransform._41 = translate.x;
	matrixTransform._42 = translate.y;
	matrixTransform._43 = translate.z;
	D3DXMatrixMultiply( &matrixTransform, &matrixTransform, &matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );

	// テクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );

	// 風向き
	D3DXVECTOR3	vectorWind;					// 風向き
	D3DXVECTOR3	vectorTransformCoord;		// 頂点の変化ベクトル
	pEffectParameter_->GetVectorWind( &vectorWind );
	velocityTransform_ += vectorWind;
	velocityTransform_ -= vectorTransform_ * hardness_;
	vectorTransform_ += velocityTransform_;
	D3DXVec3TransformNormal( &vectorTransformCoord, &vectorTransform_, &matrixViewProjection );
	pEffect_->SetFloatArray( PARAMETER_VECTOR_WIND, &vectorTransformCoord.x, 2 );

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
void DrawerGrass::SetTexture( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerGrass::GetTexture( void ) const
{
	// 値の返却
	return pTexture_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerGrass::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pPolygon_ = nullptr;
	vectorTransform_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	velocityTransform_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}
