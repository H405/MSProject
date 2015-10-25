//==============================================================================
//
// File   : DrawerModel.cpp
// Brief  : モデル描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerModel.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/graphic/Material.h"
#include "../../framework/light/LightDirection.h"
#include "../../framework/light/LightPoint.h"
#include "../../framework/render/RenderMatrix.h"
#include "../../framework/resource/Effect.h"
#include "../../framework/resource/Model.h"
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
DrawerModel::DrawerModel( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerModel::~DrawerModel( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : Model* pModel						: モデル
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: 描画エフェクト
//==============================================================================
int DrawerModel::Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect )
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
	pModel_ = pModel;

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
int DrawerModel::Finalize( void )
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
// Arg    : Model* pModel						: モデル
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: 描画エフェクト
//==============================================================================
int DrawerModel::Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pModel, pParameter, pEffect );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerModel* pOut					: コピー先アドレス
//==============================================================================
int DrawerModel::Copy( DrawerModel* pOut ) const
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
void DrawerModel::Draw( const D3DXMATRIX& matrixWorld )
{
	// 変換行列
	D3DXMATRIX		matrixTransform;				// 変換行列
	D3DXMATRIX		matrixViewProjection;			// ビュープロジェクション行列
	const Camera*	pCamera = nullptr;				// カメラ
	RenderMatrix*	pRenderMatrix = nullptr;		// レンダーマトリクス
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	D3DXMatrixMultiply( &matrixTransform, &matrixWorld, &matrixViewProjection );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );

	// ワールドマトリクス
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorld );

	// 視点座標
	D3DXVECTOR3	positionEye;		// 視点座標
	pCamera->GetPositionCamera( &positionEye );
	pEffect_->SetFloatArray( PARAMETER_POSITION_EYE, &positionEye.x, 3 );

	// 環境光色
	D3DXCOLOR	colorAmbient;		// 環境光色
	pEffectParameter_->GetColorAmbient( &colorAmbient );
	pEffect_->SetFloatArray( PARAMETER_COLOR_AMBIENT, &colorAmbient.r, 3 );

	// ディレクショナルライトのベクトル
	const LightDirection*	pLightDirection = nullptr;		// ディレクショナルライト
	D3DXVECTOR3				vectorLight;					// ディレクショナルライトベクトル
	pLightDirection = pEffectParameter_->GetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL );
	pLightDirection->GetVector( &vectorLight );
	pEffect_->SetFloatArray( PARAMETER_VECTOR_LIGHT_DIRECTION, &vectorLight.x, 3 );

	// ディレクショナルライトの色
	D3DXCOLOR	colorLightDirection;		// ディレクショナルライトの色
	pLightDirection->GetDiffuse( &colorLightDirection );
	pEffect_->SetFloatArray( PARAMETER_COLOR_LIGHT_DIRECTION, &colorLightDirection.r, 3 );

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
	pEffect_->SetFloatArray( PARAMETER_ATTEMUATION_LIGHT_POINT, pAttemuationPoint, 3 * countPoint );

	// ポイントライトの数
	pEffect_->SetInteger( PARAMETER_COUNT_LIGHT_POINT, countPoint );

	// 描画
	unsigned int		countMaterial;			// マテリアル数
	IDirect3DTexture9*	pTexture = nullptr;		// テクスチャ
	Material			material;				// マテリアル
	countMaterial = pModel_->GetCountMaterial();
	for( unsigned int counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
		// メッシュ情報の取得
		pTexture = pModel_->GetTexture( counterMaterial );
		pModel_->GetMaterial( counterMaterial, &material );

		// テクスチャ
		pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture );

		// スペキュラ色
		pEffect_->SetFloatArray( PARAMETER_COLOR_SPECULAR, &material.specular_.r, 3 );

		// 反射率
		pEffect_->SetFloat( PARAMETER_REFLECTION, material.reflection_ );

		// 反射の強さ
		pEffect_->SetFloat( PARAMETER_POWER, material.power_ );

		// 屈折率
		pEffect_->SetFloat( PARAMETER_REFLACTIVE, material.refractive_ );

		// モデルの描画
		pEffect_->Begin( 0 );
		pModel_->Draw( counterMaterial );
		pEffect_->End();
	}
}

//==============================================================================
// Brief  : モデルの設定
// Return : void								: なし
// Arg    : Model* pValue						: 設定する値
//==============================================================================
void DrawerModel::SetModel( Model* pValue )
{
	// 値の設定
	pModel_ = pValue;
}

//==============================================================================
// Brief  : モデルの取得
// Return : Model*								: 返却する値
// Arg    : void								: なし
//==============================================================================
Model* DrawerModel::GetModel( void ) const
{
	// 値の返却
	return pModel_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerModel::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
}
