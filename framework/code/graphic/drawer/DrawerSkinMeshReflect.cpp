//==============================================================================
//
// File   : DrawerSkinMeshReflect.cpp
// Brief  : スキンメッシュ描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerSkinMeshReflect.h"
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
DrawerSkinMeshReflect::DrawerSkinMeshReflect( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerSkinMeshReflect::~DrawerSkinMeshReflect( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: 描画エフェクト
// Arg    : Model* pModel						: モデル
// Arg    : int countBone						: ボーン数
// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
// Arg    : int* pIndexFrame					: フレーム番号参照アドレス
//==============================================================================
int DrawerSkinMeshReflect::Initialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame )
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
	countBone_ = countBone;
	pMatrixBone_ = pMatrixBone;
	pIndexFrame_ = pIndexFrame;

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
int DrawerSkinMeshReflect::Finalize( void )
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
// Arg    : Model* pModel						: モデル
// Arg    : int countBone						: ボーン数
// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
// Arg    : int* pIndexFrame					: フレーム番号参照アドレス
//==============================================================================
int DrawerSkinMeshReflect::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pModel, countBone, pMatrixBone, pIndexFrame );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerSkinMeshReflect* pOut				: コピー先アドレス
//==============================================================================
int DrawerSkinMeshReflect::Copy( DrawerSkinMeshReflect* pOut ) const
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
void DrawerSkinMeshReflect::Draw( const D3DXMATRIX& matrixWorld )
{
	// 反射ワールド変換行列の作成
	D3DXMATRIX		matrixReflect;					// 反射行列
	D3DXMATRIX		matrixWorldReflect;				// 反射ワールド行列
	D3DXVECTOR3		positionReflect;				// 反射面座標
	D3DXVECTOR3		normalReflect;					// 反射面法線
	D3DXPLANE		planeReflect;					// 反射面
	positionReflect.x = positionReflect.z = normalReflect.x = normalReflect.z = 0.0f;
	positionReflect.y = pEffectParameter_->GetHeightReflect();
	normalReflect.y = 1.0f;
	D3DXPlaneFromPointNormal( &planeReflect, &positionReflect, &normalReflect );
	D3DXMatrixReflect( &matrixReflect, &planeReflect );
	D3DXMatrixMultiply( &matrixWorldReflect, &matrixWorld, &matrixReflect );

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
	D3DXMatrixMultiply( &matrixTransform, &matrixWorldReflect, &matrixViewProjection );
	D3DXMatrixMultiply( &matrixWorldView, &matrixWorldReflect, &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD, matrixWorldReflect );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD_VIEW, matrixWorldView );

	// 反射面の高さ
	pEffect_->SetFloat( PARAMETER_HEIGHT, positionReflect.y );

	// ボーン変換行列
	pEffect_->SetMatrixArray( PARAMETER_MATRIX_BONE, pMatrixBone_, countBone_ );

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
void DrawerSkinMeshReflect::SetModel( Model* pValue )
{
	// 値の設定
	pModel_ = pValue;
}

//==============================================================================
// Brief  : モデルの取得
// Return : Model*								: 返却する値
// Arg    : void								: なし
//==============================================================================
Model* DrawerSkinMeshReflect::GetModel( void ) const
{
	// 値の返却
	return pModel_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerSkinMeshReflect::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
	countBone_ = 0;
	pMatrixBone_ = nullptr;
	pIndexFrame_ = nullptr;
}
