//==============================================================================
//
// File   : DrawerRiver.cpp
// Brief  : 川描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerRiver.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/graphic/Material.h"
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
DrawerRiver::DrawerRiver( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerRiver::~DrawerRiver( void )
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
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
// Arg    : IDirect3DTexture9* pTextureReflect	: 反射テクスチャ
// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: 反射ライティングなしテクスチャ
// Arg    : IDirect3DTexture9* pTextureReflectAdd		: 反射加算合成テクスチャ
// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
//==============================================================================
int DrawerRiver::Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTextureNormal,
	IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth )
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
	pTextureNormal_ = pTextureNormal;
	pTextureReflect_ = pTextureReflect;
	pTextureReflectNotLight_ = pTextureReflectNotLight;
	pTextureReflectAdd_ = pTextureReflectAdd;
	pTexture3D_ = pTexture3D;
	pTextureDepth_ = pTextureDepth;

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
int DrawerRiver::Finalize( void )
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
// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
// Arg    : IDirect3DTexture9* pTextureReflect	: 反射テクスチャ
// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: 反射ライティングなしテクスチャ
// Arg    : IDirect3DTexture9* pTextureReflectAdd		: 反射加算合成テクスチャ
// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
//==============================================================================
int DrawerRiver::Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTextureNormal,
	IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
	IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pModel, pParameter, pEffect, pTextureNormal, pTextureReflect, pTextureReflectNotLight, pTextureReflectAdd,
		pTexture3D, pTextureDepth );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerRiver* pOut					: コピー先アドレス
//==============================================================================
int DrawerRiver::Copy( DrawerRiver* pOut ) const
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
void DrawerRiver::Draw( const D3DXMATRIX& matrixWorld )
{
	// 変換行列
	D3DXMATRIX		matrixTransform;				// 変換行列
	D3DXMATRIX		matrixViewProjection;			// ビュープロジェクション変換行列
	D3DXMATRIX		matrixWorldView;				// ワールドビュー変換行列
	D3DXMATRIX		matrixView;						// ビュー変換行列
	const Camera*	pCamera = nullptr;				// カメラ
	RenderMatrix*	pRenderMatrix = nullptr;		// レンダーマトリクス
	pCamera = pEffectParameter_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	pRenderMatrix->GetMatrixView( &matrixView );
	D3DXMatrixMultiply( &matrixTransform, &matrixWorld, &matrixViewProjection );
	D3DXMatrixMultiply( &matrixWorldView, &matrixWorld, &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorld );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD_VIEW, matrixWorldView );

	// テクスチャ座標変換行列
	D3DXMATRIX	matrixTransformTexture;			// テクスチャ座標変換行列
	D3DXMATRIX	matrixSaclingTexture;			// テクスチャ座標変換行列拡縮
	D3DXMATRIX	matrixTranslationTexture;		// テクスチャ座標変換行列移動
	matrixTransformTexture = matrixTransform;
	D3DXMatrixScaling( &matrixSaclingTexture, 0.5f, -0.5f, 1.0f );
	D3DXMatrixTranslation( &matrixTranslationTexture, 0.5f, 0.5f, 0.0f );
	matrixTransformTexture *= matrixSaclingTexture * matrixTranslationTexture;
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM_TEXTURE, matrixTransformTexture );

	// テクセルオフセット
	float	pOffset[ 2 ];		// オフセット
	pOffset[ 0 ] = 0.5f / pEffectParameter_->GetWidthScreen();
	pOffset[ 1 ] = 0.5f / pEffectParameter_->GetHeightScreen();
	pEffect_->SetFloatArray( PARAMETER_OFFET_TEXEL, pOffset, 2 );

	// ワールド逆転置行列
	D3DXMATRIX	matrixWorldInverse;					// ワールド逆行列
	D3DXMATRIX	matrixWorldInverseTranspose;		// ワールド逆転置行列
	D3DXMatrixInverse( &matrixWorldInverse, nullptr, &matrixWorld );
	matrixWorldInverseTranspose._11 = matrixWorldInverse._11;
	matrixWorldInverseTranspose._12 = matrixWorldInverse._21;
	matrixWorldInverseTranspose._13 = matrixWorldInverse._31;
	matrixWorldInverseTranspose._14 = matrixWorldInverse._41;
	matrixWorldInverseTranspose._21 = matrixWorldInverse._12;
	matrixWorldInverseTranspose._22 = matrixWorldInverse._22;
	matrixWorldInverseTranspose._23 = matrixWorldInverse._32;
	matrixWorldInverseTranspose._24 = matrixWorldInverse._42;
	matrixWorldInverseTranspose._31 = matrixWorldInverse._13;
	matrixWorldInverseTranspose._32 = matrixWorldInverse._23;
	matrixWorldInverseTranspose._33 = matrixWorldInverse._33;
	matrixWorldInverseTranspose._34 = matrixWorldInverse._43;
	matrixWorldInverseTranspose._41 = matrixWorldInverse._14;
	matrixWorldInverseTranspose._42 = matrixWorldInverse._24;
	matrixWorldInverseTranspose._43 = matrixWorldInverse._34;
	matrixWorldInverseTranspose._44 = matrixWorldInverse._44;
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD_INVERSE_TRANSPOSE, matrixWorldInverseTranspose );

	// 法線テクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE_NORMAL, pTextureNormal_ );

	// 環境テクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE_REFLECT, pTextureReflect_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_REFLECT_NOT_LIGHT, pTextureReflectNotLight_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_REFLECT_ADD, pTextureReflectAdd_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_3D, pTexture3D_ );
	pEffect_->SetTexture( PARAMETER_TEXTURE_DEPTH, pTextureDepth_ );

	// 視点座標
	D3DXVECTOR3	positionEye;		// 視点座標
	pCamera->GetPositionCamera( &positionEye );
	pEffect_->SetFloatArray( PARAMETER_POSITION_EYE, &positionEye.x, 3 );

	// カメラのクリップ値
	float	pClipCamera[ 2 ];		// カメラのクリップ値
	pClipCamera[ 0 ] = pCamera->GetClipNear();
	pClipCamera[ 1 ] = pCamera->GetClipFar();
	pEffect_->SetFloatArray( PARAMETER_CLIP_CAMERA, pClipCamera, 2 );

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

		// ディフューズ色
		pEffect_->SetFloatArray( PARAMETER_COLOR_DIFFUSE, &material.diffuse_.r, 3 );

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
void DrawerRiver::SetModel( Model* pValue )
{
	// 値の設定
	pModel_ = pValue;
}

//==============================================================================
// Brief  : モデルの取得
// Return : Model*								: 返却する値
// Arg    : void								: なし
//==============================================================================
Model* DrawerRiver::GetModel( void ) const
{
	// 値の返却
	return pModel_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerRiver::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
	pTextureNormal_ = nullptr;
	pTextureReflect_ = nullptr;
	pTextureReflectNotLight_ = nullptr;
	pTextureReflectAdd_ = nullptr;
	pTexture3D_ = nullptr;
	pTextureDepth_ = nullptr;

}
