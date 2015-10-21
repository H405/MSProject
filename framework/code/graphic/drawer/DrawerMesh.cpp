//==============================================================================
//
// File   : DrawerMesh.cpp
// Brief  : メッシュポリゴン描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerMesh.h"
#include "../graphic/GraphicMain.h"
#include "../../framework/camera/Camera.h"
#include "../../framework/graphic/Material.h"
#include "../../framework/light/LightDirection.h"
#include "../../framework/polygon/PolygonMesh.h"
#include "../../framework/render/RenderMatrix.h"
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
DrawerMesh::DrawerMesh( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerMesh::~DrawerMesh( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffect						: 描画エフェクト
// Arg    : PolygonMesh* pPolygon				: メッシュポリゴン
// Arg    : Material* pMaterial					: マテリアル
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int DrawerMesh::Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture )
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
	pMaterial_ = pMaterial;

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
int DrawerMesh::Finalize( void )
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
// Arg    : PolygonMesh* pPolygon				: メッシュポリゴン
// Arg    : Material* pMaterial					: マテリアル
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int DrawerMesh::Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pParameter, pEffect, pPolygon, pMaterial, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerMesh* pOut					: コピー先アドレス
//==============================================================================
int DrawerMesh::Copy( DrawerMesh* pOut ) const
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
void DrawerMesh::Draw( const D3DXMATRIX& matrixWorld )
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

	// ライトベクトル
	const LightDirection*	pLight = nullptr;		// ライト
	D3DXVECTOR3				vectorLightWorld;		// ライトベクトル
	pLight = pEffectParameter_->GetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL );
	pLight->GetVector( &vectorLightWorld );
	pEffect_->SetFloatArray( PARAMETER_VECTOR_LIGHT, &vectorLightWorld.x, 3 );

	// 視点座標
	D3DXVECTOR3	positionEye;		// 視点座標
	pCamera->GetPositionCamera( &positionEye );
	pEffect_->SetFloatArray( PARAMETER_POSITION_EYE, &positionEye.x, 3 );

	// テクスチャ
	pEffect_->SetTexture( PARAMETER_TEXTURE, pTexture_ );

	// アンビエント色
	D3DXCOLOR	colorAmbient;		// アンビエント色
	pEffectParameter_->GetColorAmbient( &colorAmbient );
	pEffect_->SetColor( PARAMETER_COLOR_AMBIENT, colorAmbient );

	// ライトの色
	D3DXCOLOR	colorLight;		// ライトの色
	pLight->GetDiffuse( &colorLight );
	pEffect_->SetColor( PARAMETER_COLOR_LIGHT, colorLight );

	// ディフューズ色
	pEffect_->SetColor( PARAMETER_COLOR_DIFFUSE, pMaterial_->diffuse_ );

	// スペキュラ色
	pEffect_->SetColor( PARAMETER_COLOR_SPECULAR, pMaterial_->specular_ );

	// 反射率
	pEffect_->SetFloat( PARAMETER_REFLECTION, pMaterial_->reflection_ );

	// 反射の強さ
	pEffect_->SetFloat( PARAMETER_POWER, pMaterial_->power_ );

	// 屈折率
	pEffect_->SetFloat( PARAMETER_REFLACTIVE, pMaterial_->refractive_ );

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
void DrawerMesh::SetTexture( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* DrawerMesh::GetTexture( void ) const
{
	// 値の返却
	return pTexture_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerMesh::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pTexture_ = nullptr;
	pPolygon_ = nullptr;
	pMaterial_ = nullptr;
}
