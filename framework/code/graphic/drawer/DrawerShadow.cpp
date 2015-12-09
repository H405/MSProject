//==============================================================================
//
// File   : DrawerShadow.cpp
// Brief  : ライト描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerShadow.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/develop/DebugMeasure.h"
#include "../../framework/graphic/Material.h"
#include "../../framework/light/LightDirection.h"
#include "../../framework/light/LightPoint.h"
#include "../../framework/render/RenderMatrix.h"
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
DrawerShadow::DrawerShadow( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerShadow::~DrawerShadow( void )
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
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightNear	: 平行光源(近)の深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightFar		: 平行光源(遠)の深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightPoint	: 点光源の深度情報テクスチャ
//==============================================================================
int DrawerShadow::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint )
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
	pTextureDepth_ = pTextureDepth;
	pTextureLightNear_ = pTextureLightNear;
	pTextureLightFar_ = pTextureLightFar;
	pTextureLightPoint_ = pTextureLightPoint;
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
int DrawerShadow::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightNear	: 平行光源(近)の深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightFar		: 平行光源(遠)の深度情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureLightPoint	: 点光源の深度情報テクスチャ
//==============================================================================
int DrawerShadow::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
	IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pPolygon, pTextureDepth, pTextureLightNear, pTextureLightFar, pTextureLightPoint );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerShadow* pOut					: コピー先アドレス
//==============================================================================
int DrawerShadow::Copy( DrawerShadow* pOut ) const
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
void DrawerShadow::Draw( const D3DXMATRIX& matrixWorld )
{
	// 頂点シェーダ用パラメータ
	float	pOffset[ 2 ];		// オフセット
	pOffset[ 0 ] = 0.5f / pEffectParameter_->GetWidthScreen();
	pOffset[ 1 ] = 0.5f / pEffectParameter_->GetHeightScreen();
	pEffect_->SetFloatArray( PARAMETER_OFFET_TEXEL, pOffset, 2 );

	// プロジェクション変換逆行列
	const Camera*	pCamera = nullptr;				// カメラ
	RenderMatrix*	pRenderMatrix = nullptr;		// 描画変換行列
	D3DXMATRIX		matrixProjectionInverse;		// プロジェクション変換逆行列
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixProjection( &matrixProjectionInverse );
	D3DXMatrixInverse( &matrixProjectionInverse, nullptr, &matrixProjectionInverse );
	pEffect_->SetMatrix( PARAMETER_MATRIX_PROJECTION_INVERSE, matrixProjectionInverse );

	// ビュー変換逆行列
	D3DXMATRIX	matrixViewInverse;		// ビュー変換逆行列
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixView( &matrixViewInverse );
	D3DXMatrixInverse( &matrixViewInverse, nullptr, &matrixViewInverse );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_INVERSE, matrixViewInverse );

	// 深度テクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH, pTextureDepth_ );

	// 平行光源の注視点
	const Camera*	pCameraShadowNear = nullptr;		// カメラ
	D3DXVECTOR3		positionLookAtLight;				// 平行光源の注視点
	pCameraShadowNear = pEffectParameter_->GetCamera( GraphicMain::CAMERA_SHADOW_NEAR );
	pCameraShadowNear->GetPositionLookAt( &positionLookAtLight );
	pEffect_->SetFloatArray( PARAMETER_POSITION_LOOK_AT_LIGHT, &positionLookAtLight.x, 3 );

	// 平行光源(近)の変換行列
	D3DXMATRIX	matrixViewProjection;		// ビュープロジェクション変換行列
	D3DXMATRIX	matrixView;					// ビュー変換行列
	pRenderMatrix = pCameraShadowNear->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	pRenderMatrix->GetMatrixView( &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM_LIGHT_NEAR, matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_LIGHT_NEAR, matrixView );

	// 平行光源(近)のテクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH_LIGHT_NEAR, pTextureLightNear_ );

	// 平行光源(近)のファークリップ面
	pEffect_->SetFloat( PARAMETER_CLIP_FAR_LIGHT_NEAR, pCameraShadowNear->GetClipFar() );

	// 平行光源(遠)の変換行列
	const Camera*	pCameraShadowFar = nullptr;		// カメラ
	pCameraShadowFar = pEffectParameter_->GetCamera( GraphicMain::CAMERA_SHADOW_FAR );
	pRenderMatrix = pCameraShadowFar->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	pRenderMatrix->GetMatrixView( &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM_LIGHT_FAR, matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_LIGHT_FAR, matrixView );

	// 平行光源(遠)のテクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH_LIGHT_FAR, pTextureLightFar_ );

	// 平行光源(遠)のファークリップ面
	pEffect_->SetFloat( PARAMETER_CLIP_FAR_LIGHT_FAR, pCameraShadowFar->GetClipFar() );

	// 点光源の変換行列
	const Camera*	pCameraShadowPoint = nullptr;		// カメラ
	pCameraShadowPoint = pEffectParameter_->GetCamera( GraphicMain::CAMERA_SHADOW_POINT );
	pRenderMatrix = pCameraShadowPoint->GetRenderMatrix();
	pRenderMatrix->GetMatrixView( &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_VIEW_LIGHT_POINT, matrixView );

	// 点光源のテクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH_LIGHT_POINT, pTextureLightPoint_ );

	// 点光源のファークリップ面
	pEffect_->SetFloat( PARAMETER_CLIP_FAR_LIGHT_POINT, pCameraShadowPoint->GetClipFar() );

	// 点光源の減衰率
	const LightPoint*	pLightPoint = nullptr;		// ポイントライト
	D3DXVECTOR3			attenuationLightPoint;		// 点光源の減衰率
	if( pEffectParameter_->GetCountLightPoint() > 0 )
	{
		pLightPoint = pEffectParameter_->GetLightPoint( 0 );
		pLightPoint->GetAttenuation( &attenuationLightPoint );
	}
	else
	{
		attenuationLightPoint.x = attenuationLightPoint.y = attenuationLightPoint.z = 10000.0f;
	}
	pEffect_->SetFloatArray( PARAMETER_ATTENUATION_LIGHT_POINT, &attenuationLightPoint.x, 3 );

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
void DrawerShadow::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTextureDepth_ = nullptr;
	pTextureLightNear_ = nullptr;
	pTextureLightFar_ = nullptr;
	pTextureLightPoint_ = nullptr;
	pPolygon_ = nullptr;
}
