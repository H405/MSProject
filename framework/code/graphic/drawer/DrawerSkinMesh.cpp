//==============================================================================
//
// File   : DrawerSkinMesh.cpp
// Brief  : スキンメッシュ描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerSkinMesh.h"
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
DrawerSkinMesh::DrawerSkinMesh( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerSkinMesh::~DrawerSkinMesh( void )
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
int DrawerSkinMesh::Initialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame )
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
int DrawerSkinMesh::Finalize( void )
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
int DrawerSkinMesh::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone, int* pIndexFrame )
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
// Arg    : DrawerSkinMesh* pOut				: コピー先アドレス
//==============================================================================
int DrawerSkinMesh::Copy( DrawerSkinMesh* pOut ) const
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
void DrawerSkinMesh::Draw( const D3DXMATRIX& matrixWorld )
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

	// ボーン変換行列
	pEffect_->SetMatrixArray( PARAMETER_MATRIX_BONE, pMatrixBone_, countBone_ );
	pEffect_->SetInteger( PARAMETER_COUNT_BONE, countBone_ );

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
void DrawerSkinMesh::SetModel( Model* pValue )
{
	// 値の設定
	pModel_ = pValue;
}

//==============================================================================
// Brief  : モデルの取得
// Return : Model*								: 返却する値
// Arg    : void								: なし
//==============================================================================
Model* DrawerSkinMesh::GetModel( void ) const
{
	// 値の返却
	return pModel_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerSkinMesh::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
	countBone_ = 0;
	pMatrixBone_ = nullptr;
	pIndexFrame_ = nullptr;
}
