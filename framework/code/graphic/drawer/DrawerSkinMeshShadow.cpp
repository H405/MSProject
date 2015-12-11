//==============================================================================
//
// File   : DrawerSkinMeshShadow.cpp
// Brief  : モデル影描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/24 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "DrawerSkinMeshShadow.h"
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
DrawerSkinMeshShadow::DrawerSkinMeshShadow( void ) : Drawer()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DrawerSkinMeshShadow::~DrawerSkinMeshShadow( void )
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
// Arg    : int indexCamera						: カメラ番号
// Arg    : int countBone						: ボーン数
// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
//==============================================================================
int DrawerSkinMeshShadow::Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, int indexCamera,
	int countBone, D3DXMATRIX* pMatrixBone )
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
	indexCamera_ = indexCamera;
	countBone_ = countBone;
	pMatrixBone_ = pMatrixBone;

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
int DrawerSkinMeshShadow::Finalize( void )
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
// Arg    : int indexCamera						: カメラ番号
// Arg    : int countBone						: ボーン数
// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
//==============================================================================
int DrawerSkinMeshShadow::Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, int indexCamera,
	int countBone, D3DXMATRIX* pMatrixBone )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pModel, pParameter, pEffect, indexCamera, countBone, pMatrixBone );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DrawerSkinMeshShadow* pOut			: コピー先アドレス
//==============================================================================
int DrawerSkinMeshShadow::Copy( DrawerSkinMeshShadow* pOut ) const
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
void DrawerSkinMeshShadow::Draw( const D3DXMATRIX& matrixWorld )
{
	// 変換行列
	D3DXMATRIX		matrixTransform;				// 変換行列
	D3DXMATRIX		matrixViewProjection;			// ビュープロジェクション変換行列
	D3DXMATRIX		matrixWorldView;				// ワールドビュー変換行列
	D3DXMATRIX		matrixView;						// ビュー変換行列
	const Camera*	pCamera = nullptr;				// カメラ
	RenderMatrix*	pRenderMatrix = nullptr;		// レンダーマトリクス
	pCamera = pEffectParameter_->GetCamera( indexCamera_ );
	pRenderMatrix = pCamera->GetRenderMatrix();
	pRenderMatrix->GetMatrixViewProjection( &matrixViewProjection );
	pRenderMatrix->GetMatrixView( &matrixView );
	D3DXMatrixMultiply( &matrixTransform, &matrixWorld, &matrixViewProjection );
	D3DXMatrixMultiply( &matrixWorldView, &matrixWorld, &matrixView );
	pEffect_->SetMatrix( PARAMETER_MATRIX_TRANSFORM, matrixTransform );
	pEffect_->SetMatrix( PARAMETER_MATRIX_WORLD_VIEW, matrixWorldView );

	// ボーン変換行列
	pEffect_->SetMatrixArray( PARAMETER_MATRIX_BONE, pMatrixBone_, countBone_ );

	// ファークリップ面
	pEffect_->SetFloat( PARAMETER_CLIP_FAR, pCamera->GetClipFar() );

	// 描画
	unsigned int	countMaterial;		// マテリアル数
	countMaterial = pModel_->GetCountMaterial();
	for( unsigned int counterMaterial = 0; counterMaterial < countMaterial; ++counterMaterial )
	{
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
void DrawerSkinMeshShadow::SetModel( Model* pValue )
{
	// 値の設定
	pModel_ = pValue;
}

//==============================================================================
// Brief  : モデルの取得
// Return : Model*								: 返却する値
// Arg    : void								: なし
//==============================================================================
Model* DrawerSkinMeshShadow::GetModel( void ) const
{
	// 値の返却
	return pModel_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DrawerSkinMeshShadow::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffectParameter_ = nullptr;
	pEffect_ = nullptr;
	pModel_ = nullptr;
	indexCamera_ = 0;
	countBone_ = 0;
	pMatrixBone_ = nullptr;
}
