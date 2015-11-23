//==============================================================================
//
// File   : DrawerLightReflect.cpp
// Brief  : 反射ライト描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/22 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerLightReflect.h"
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
DrawerLightReflect::DrawerLightReflect( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerLightReflect::~DrawerLightReflect( void )
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
// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
//==============================================================================
int DrawerLightReflect::Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
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
	pTextureDiffuse_ = pTextureDiffuse;
	pTextureSpecular_ = pTextureSpecular;
	pTextureNormal_ = pTextureNormal;
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
int DrawerLightReflect::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
//==============================================================================
int DrawerLightReflect::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pPolygon, pTextureDiffuse, pTextureSpecular, pTextureNormal, pTextureDepth );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerLightReflect* pOut				: コピー先アドレス
//==============================================================================
int DrawerLightReflect::Copy( DrawerLightReflect* pOut ) const
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
void DrawerLightReflect::Draw( const D3DXMATRIX& matrixWorld )
{
	// 反射変換行列の作成
	D3DXMATRIX		matrixReflect;					// 反射行列
	D3DXVECTOR3		positionReflect;				// 反射面座標
	D3DXVECTOR3		normalReflect;					// 反射面法線
	D3DXPLANE		planeReflect;					// 反射面
	positionReflect.x = positionReflect.z = normalReflect.x = normalReflect.z = 0.0f;
	positionReflect.y = pEffectParameter_->GetHeightReflect();
	normalReflect.y = 1.0f;
	D3DXPlaneFromPointNormal( &planeReflect, &positionReflect, &normalReflect );
	D3DXMatrixReflect( &matrixReflect, &planeReflect );

	// 頂点シェーダ用パラメータ
	D3DXMATRIX	matrixWorldSet;			// 設定するワールドマトリクス
	float		pSizeScreen[ 2 ];		// 画面のサイズ
	matrixWorldSet = matrixWorld;
	matrixWorldSet._41 -= 0.5f;
	matrixWorldSet._42 -= 0.5f;
	pSizeScreen[ 0 ] = pEffectParameter_->GetWidthScreen();
	pSizeScreen[ 1 ] = pEffectParameter_->GetHeightScreen();
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldSet );
	pEffect_->SetFloatArray( PARAMETER_SIZE_SCREEN, pSizeScreen, 2 );

	// 3D情報テクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE_DIFFUSE, pTextureDiffuse_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_SPECULAR, pTextureSpecular_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_NORMAL, pTextureNormal_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH, pTextureDepth_ );

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

	// 視点座標
	D3DXVECTOR3	positionEye;		// 視点座標
	pCamera->GetPositionCamera( &positionEye );
	D3DXVec3TransformCoord( &positionEye, &positionEye, &matrixReflect );
	pEffect_->SetFloatArray( PARAMETER_POSITION_EYE, &positionEye.x, 3 );

	// カメラのクリップ値
	float	pClipCamera[ 2 ];		// カメラのクリップ値
	pClipCamera[ 0 ] = pCamera->GetClipNear();
	pClipCamera[ 1 ] = pCamera->GetClipFar();
	pEffect_->SetFloatArray( PARAMETER_CLIP_CAMERA, pClipCamera, 2 );

	// 環境光色
	D3DXCOLOR	colorAmbient;		// 環境光色
	pEffectParameter_->GetColorAmbient( &colorAmbient );
	pEffect_->SetFloatArray( PARAMETER_COLOR_AMBIENT, &colorAmbient.r, 3 );

	// ディレクショナルライトのベクトル
	const LightDirection*	pLightDirection = nullptr;		// ディレクショナルライト
	D3DXVECTOR3				vectorLight;					// ディレクショナルライトベクトル
	pLightDirection = pEffectParameter_->GetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL );
	if( pLightDirection != nullptr )
	{
		pLightDirection->GetVector( &vectorLight );
		D3DXVec3TransformNormal( &vectorLight, &vectorLight, &matrixReflect );
		pEffect_->SetFloatArray( PARAMETER_VECTOR_LIGHT_DIRECTION, &vectorLight.x, 3 );
	}

	// ディレクショナルライトの色
	D3DXCOLOR	colorLightDirection;		// ディレクショナルライトの色
	if( pLightDirection != nullptr )
	{
		pLightDirection->GetDiffuse( &colorLightDirection );
		pEffect_->SetFloatArray( PARAMETER_COLOR_LIGHT_DIRECTION, &colorLightDirection.r, 3 );
	}

	// ポイントライトの設定
	int					countPoint;				// ポイントライトの数
	const LightPoint*	pLightPoint;			// ポイントライト
	D3DXVECTOR3			positionPoint;			// ポイントライトの座標
	D3DXCOLOR			colorPoint;				// ポイントライトの色
	D3DXVECTOR3			attemuationPoint;		// ポイントライトの減衰率
	float				pPositionPoint[ 3 * GraphicMain::LIGHT_POINT_MAX ];			// ポイントライトの座標
	float				pColorPoint[ 3 * GraphicMain::LIGHT_POINT_MAX ];			// ポイントライトの色
	float				pAttemuationPoint[ 3 * GraphicMain::LIGHT_POINT_MAX ];		// ポイントライトの減衰率
	countPoint = pEffectParameter_->GetCountLightPoint();
	for( int counterLight = 0; counterLight < countPoint; ++counterLight )
	{
		// ポイントライトの座標
		pLightPoint = pEffectParameter_->GetLightPoint( counterLight );
		pLightPoint->GetPosition( &positionPoint );
		D3DXVec3TransformCoord( &positionPoint, &positionPoint, &matrixReflect );
		pPositionPoint[ 3 * counterLight + 0 ] = positionPoint.x;
		pPositionPoint[ 3 * counterLight + 1 ] = positionPoint.y;
		pPositionPoint[ 3 * counterLight + 2 ] = positionPoint.z;

		// ポイントライトの色
		pLightPoint->GetDiffuse( &colorPoint );
		pColorPoint[ 3 * counterLight + 0 ] = colorPoint.r;
		pColorPoint[ 3 * counterLight + 1 ] = colorPoint.g;
		pColorPoint[ 3 * counterLight + 2 ] = colorPoint.b;

		// ポイントライトの減衰率
		pLightPoint->GetAttemuation( &attemuationPoint );
		pAttemuationPoint[ 3 * counterLight + 0 ] = attemuationPoint.x;
		pAttemuationPoint[ 3 * counterLight + 1 ] = attemuationPoint.y;
		pAttemuationPoint[ 3 * counterLight + 2 ] = attemuationPoint.z;
	}

	// ポイントライトの座標
	pEffect_->SetFloatArray( PARAMETER_POSITION_LIGHT_POINT, pPositionPoint, 3 * countPoint );

	// ポイントライトの色
	pEffect_->SetFloatArray( PARAMETER_COLOR_LIGHT_POINT, pColorPoint, 3 * countPoint );

	// ポイントライトの減衰率
	pEffect_->SetFloatArray( PARAMETER_ATTENUATION_LIGHT_POINT, pAttemuationPoint, 3 * countPoint );

	// 描画
	pEffect_->Begin( 0 );
	pPolygon_->Draw();
	pEffect_->End();
}

//==============================================================================
// Brief  : ディフューズ情報テクスチャの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void DrawerLightReflect::SetTextureDiffuse( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTextureDiffuse_ = pValue;
}

//==============================================================================
// Brief  : ディフューズ情報テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerLightReflect::GetTextureDiffuse( void ) const
{
	// 値の返却
	return pTextureDiffuse_;
}

//==============================================================================
// Brief  : スペキュラ情報テクスチャの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void DrawerLightReflect::SetTextureSpecular( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTextureSpecular_ = pValue;
}

//==============================================================================
// Brief  : スペキュラ情報テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerLightReflect::GetTextureSpecular( void ) const
{
	// 値の返却
	return pTextureSpecular_;
}

//==============================================================================
// Brief  : 法線情報テクスチャの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void DrawerLightReflect::SetTextureNormal( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTextureNormal_ = pValue;
}

//==============================================================================
// Brief  : 法線情報テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerLightReflect::GetTextureNormal( void ) const
{
	// 値の返却
	return pTextureNormal_;
}

//==============================================================================
// Brief  : 深度情報テクスチャの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void DrawerLightReflect::SetTextureDepth( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTextureDepth_ = pValue;
}

//==============================================================================
// Brief  : 深度情報テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerLightReflect::GetTextureDepth( void ) const
{
	// 値の返却
	return pTextureDepth_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerLightReflect::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTextureDiffuse_ = nullptr;
	pTextureSpecular_ = nullptr;
	pTextureNormal_ = nullptr;
	pTextureDepth_ = nullptr;
	pPolygon_ = nullptr;
}
