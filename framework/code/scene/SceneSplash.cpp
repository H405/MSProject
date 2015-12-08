//==============================================================================
//
// File   : SceneSplash.cpp
// Brief  : スプラッシュシーンクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "SceneSplash.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Utility.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

#include "../framework/camera/CameraObject.h"
#include "../framework/camera/ManagerCamera.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/LightPoint.h"
#include "../framework/light/ManagerLight.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Window.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../object/ObjectRiver.h"
#include "../object/ObjectSkinMesh.h"
#include "../object/ObjectSky.h"
#include "../system/camera/CameraStateSpline.h"
#include "../system/EffectParameter.h"
#include "../system/point/ManagerPoint.h"
#include "../system/point/PointMain.h"

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
SceneSplash::SceneSplash( void ) : SceneMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
SceneSplash::~SceneSplash( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : SceneArgumentMain* pArgument		: シーン引数
//==============================================================================
int SceneSplash::Initialize( SceneArgumentMain* pArgument )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = SceneMain::Initialize( pArgument );
	if( result != 0 )
	{
		return result;
	}

	// カメラ処理の生成
	pCameraState_ = new CameraStateSpline();
	if( pCameraState_ == nullptr )
	{
		return 1;
	}
	result = pCameraState_->Initialize( 2, 2, 2 );
	if( result != 0 )
	{
		return result;
	}
	pCameraState_->SetControlPointCamera( 0, D3DXVECTOR3( -50.0f, 20.0f, -50.0f ), D3DXVECTOR3( 150.0f, 150.0f, 0.0f ) );
	pCameraState_->SetControlPointCamera( 1, D3DXVECTOR3( 100.0f, 70.0f, 100.0f ), D3DXVECTOR3( 0.0f, 150.0f, 150.0f ) );
	pCameraState_->SetControlPointLookAt( 0, D3DXVECTOR3( 100.0f, 70.0f, 100.0f ), D3DXVECTOR3( 0.0f, 150.0f, 150.0f ) );
	pCameraState_->SetControlPointLookAt( 1, D3DXVECTOR3( -50.0f, 20.0f, -50.0f ), D3DXVECTOR3( 150.0f, 150.0f, 0.0f ) );
	pCameraState_->SetSection( 0, 60, 0, 1, 0, 1 );
	pCameraState_->SetSection( 1, 120, -1, 0, -1, 0 );

	// カメラの設定
	pCamera_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pCamera_->Set( D3DX_PI / 4.0f, pArgument->pWindow_->GetWidth(), pArgument->pWindow_->GetHeight(), 0.1f, 1000.0f,
		D3DXVECTOR3( 10.0f, 30.0f, -150.0f ), D3DXVECTOR3( 0.0f, 0.0f, 20.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	if( result != 0 )
	{
		return result;
	}
	pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( pCameraState_ );
	pArgument->pEffectParameter_->SetCamera( GraphicMain::CAMERA_GENERAL, &pCamera_[ GraphicMain::CAMERA_GENERAL ] );

	// ライトの設定
	pLight_ = pArgument->pLight_->GetLightDirection();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	pLight_->Set( D3DXCOLOR( 0.25f, 0.3f, 0.4f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( -1.0f, -1.0f, 1.0f ) );

	// ポイントライトの設定
	ppPointLight_ = new LightPoint*[ GraphicMain::LIGHT_POINT_MAX ];
	if( ppPointLight_ == nullptr )
	{
		return 1;
	}

	ppPointLight_[ 0 ] = pArgument->pLight_->GetLightPoint();
	ppPointLight_[ 0 ]->Set( D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( -20.0f, 10.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.02f, 0.001f ) );

	ppPointLight_[ 1 ] = pArgument->pLight_->GetLightPoint();
	ppPointLight_[ 1 ]->Set( D3DXCOLOR( 0.25f, 0.25f, 1.0f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 20.0f, 10.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.02f, 0.001f ) );

	ppPointLight_[ 2 ] = pArgument->pLight_->GetLightPoint();
	ppPointLight_[ 2 ]->Set( D3DXCOLOR( 0.25f, 1.0f, 0.25f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 0.0f, 10.0f, -100.0f ),  D3DXVECTOR3( 0.0f, 0.01f, 0.002f ) );

	for( int i = 3; i < GraphicMain::LIGHT_POINT_MAX; ++i )
	{
		ppPointLight_[ i ] = pArgument->pLight_->GetLightPoint();
		ppPointLight_[ i ]->Set( D3DXCOLOR( 1.0f, 1.0f, 0.5f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
			D3DXVECTOR3( 1.0f * (rand() % 100) - 50.0f - 100.0f, 10.0f, 1.0f * (rand() % 100) - 50.0f + 100.0f ),  D3DXVECTOR3( 0.0f, 0.01f, 0.002f ) );
		ppPointLight_[ i ]->SetIsEnable( false );
	}
	countLight_ = 3;

	// 影用カメラの設定
	D3DXVECTOR3	vectorLight;		// ライトベクトル
	pLight_->GetVector( &vectorLight );
	vectorLight *= -500.0f;
	pCameraShadow_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_SHADOW_NEAR );
	pCameraShadow_->Set( D3DX_PI / 4.0f, pArgument->pWindow_->GetWidth(), pArgument->pWindow_->GetHeight(), 0.1f, 1000.0f,
		vectorLight, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), false );

	// 環境光の設定
	pArgument->pEffectParameter_->SetColorAmbient( 0.1f, 0.15f, 0.2f );

	// ポイントスプライト管理クラスの生成
	Effect*		pEffectPoint = nullptr;				// ポイントエフェクト
	Effect*		pEffectPointReflect = nullptr;		// ポイントエフェクト
	Texture*	pTexturePoint = nullptr;			// ポイントテクスチャ
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pEffectPointReflect = pArgument->pEffect_->Get( _T( "PointReflect.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "common/effect000.jpg" ) );
	pPoint_ = new ManagerPoint();
	if( pPoint_ == nullptr )
	{
		return 1;
	}
	result = pPoint_->Initialize( 4096, 8, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pEffectPointReflect, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		return result;
	}

	// 2Dオブジェクトの生成
	Effect*		pEffect2D = nullptr;		// エフェクト
	Texture*	pTexture2D = nullptr;		// テクスチャ
	Texture		textureTest;				// テストテクスチャ
	pEffect2D = pArgument->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture2D = pArgument_->pTexture_->Get( _T( "test/title_logo.png" ) );
	textureTest.Initialize( pArgument->pTextureTest_, 320, 180 );
	pObject2D_ = new Object2D();
	pObject2D_->Initialize( 0 );
	pObject2D_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffect2D, &textureTest );
//	pObject2D_->SetPosition( 430.0f, 310.0f, 0.0f );
	pObject2D_->SetPosition( 480.0f, 270.0f, 0.0f );

	// メッシュの生成
	Effect*		pEffectMesh = nullptr;		// エフェクト
	Texture*	pTextureMesh = nullptr;		// メッシュ
	pEffectMesh = pArgument->pEffect_->Get( _T( "Mesh.fx" ) );
	pTextureMesh = pArgument_->pTexture_->Get( _T( "test/field001.jpg" ) );
	pObjectMesh_ = new ObjectMesh();
	pObjectMesh_->Initialize( 0, pArgument->pDevice_, 20, 20, 50.0f, 50.0f, 1.0f, 1.0f );
	pObjectMesh_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectMesh, pTextureMesh );

	// スカイドームの生成
	Effect*		pEffectSky = nullptr;				// エフェクト
	Effect*		pEffectSkyReflect = nullptr;		// エフェクト
	Texture*	pTextureSky = nullptr;				// テクスチャ
	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pEffectSkyReflect = pArgument->pEffect_->Get( _T( "SkyReflect.fx" ) );
	pTextureSky = pArgument_->pTexture_->Get( _T( "test/night.png" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 500.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pEffectSkyReflect, pTextureSky );

	// モデルの生成
	Effect*	pEffectModel = nullptr;				// エフェクト
	Effect*	pEffectModelReflect = nullptr;		// エフェクト
	Effect*	pEffectModelShadow = nullptr;		// エフェクト
	Model*	pModel = nullptr;					// モデル
	pEffectModel = pArgument->pEffect_->Get( _T( "Model.fx" ) );
	pEffectModelReflect = pArgument->pEffect_->Get( _T( "ModelReflect.fx" ) );
	pEffectModelShadow = pArgument->pEffect_->Get( _T( "ModelShadow.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );
	pObjectModel_ = new ObjectModel[ COUNT_MODEL ];
	pObjectModel_[ 0 ].Initialize( 0 );
	pObjectModel_[ 0 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel, pEffectModelReflect, pEffectModelShadow );
	pObjectModel_[ 1 ].Initialize( 0 );
	pObjectModel_[ 1 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel, pEffectModelReflect, pEffectModelShadow );
	pObjectModel_[ 1 ].SetPositionX( 50.0f );
	pObjectModel_[ 2 ].Initialize( 0 );
	pObjectModel_[ 2 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel, pEffectModelReflect, pEffectModelShadow );
	pObjectModel_[ 2 ].SetPositionX( -50.0f );
	pObjectModel_[ 2 ].SetPositionY( 20.0f );

	// テクスチャなしモデルの生成
	Effect*	pEffectModelMaterial = nullptr;				// エフェクト
	Effect*	pEffectModelMaterialReflect = nullptr;		// エフェクト
	Effect*	pEffectModelMaterialShadow = nullptr;		// エフェクト
	Model*	pModelModelMaterial = nullptr;				// モデル
	pEffectModelMaterial = pArgument->pEffect_->Get( _T( "ModelMaterial.fx" ) );
	pEffectModelMaterialReflect = pArgument->pEffect_->Get( _T( "ModelMaterialReflect.fx" ) );
	pEffectModelMaterialShadow = pArgument->pEffect_->Get( _T( "ModelShadow.fx" ) );
	pModelModelMaterial = pArgument_->pModel_->Get( _T( "head.x" ) );
	pObjectModelMaterial_ = new ObjectModelMaterial();
	pObjectModelMaterial_->Initialize( 0 );
	pObjectModelMaterial_->CreateGraphic( 0, pModelModelMaterial, pArgument->pEffectParameter_,
		pEffectModelMaterial, pEffectModelMaterialReflect, pEffectModelMaterialShadow );
	pObjectModelMaterial_->SetPosition( -10.0f, 30.0f, 40.0f );

	// ビルボードの生成
	Effect*		pEffectBillboard = nullptr;			// エフェクト
	Texture*	pTextureBillboard = nullptr;		// テクスチャ
	pEffectBillboard = pArgument->pEffect_->Get( _T( "Billboard.fx" ) );
	pTextureBillboard = pArgument_->pTexture_->Get( _T( "common/finger.png" ) );
	pObjectBoard_ = new ObjectBillboard();
	pObjectBoard_->Initialize( 0 );
	pObjectBoard_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectBillboard, pTextureBillboard );
	pObjectBoard_->SetScale( pObjectBoard_->GetScaleX() * 0.1f, pObjectBoard_->GetScaleY() * 0.1f, 1.0f );
	pObjectBoard_->SetPosition( -50.0f, 90.0f, 0.0f );

	// スキンメッシュの生成
	Effect*	pEffectSkinMesh = nullptr;				// エフェクト
	Effect*	pEffectSkinMeshReflect = nullptr;		// エフェクト
	Model*	pModelSkinMesh = nullptr;				// モデル
	pEffectSkinMesh = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectSkinMeshReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pModelSkinMesh = pArgument_->pModel_->Get( _T( "test.model" ) );
	pObjectSkinMesh_ = new ObjectSkinMesh();
	pObjectSkinMesh_->Initialize( 0, 1 );
	pObjectSkinMesh_->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh, pEffectSkinMeshReflect );
	pObjectSkinMesh_->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_->SetPosition( -100.0f, 0.0f, 100.0f );

	// 川の生成
	Effect*	pEffectRiver = nullptr;		// エフェクト
	Model*	pModelRiver = nullptr;		// モデル
	pEffectRiver = pArgument->pEffect_->Get( "water.fx" );
	pModelRiver = pArgument->pModel_->Get( _T( "river.x" ), Vertex::ELEMENT_SET_NORMAL_MAP );
	pObjectRiver_ = new ObjectRiver();
	result = pObjectRiver_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	pObjectRiver_->CreateGraphic( 0, pModelRiver, pArgument->pEffectParameter_, pEffectRiver, pArgument->pTextureNormalWave_,
		pArgument->pTextureReflect_, pArgument->pTextureReflectNotLight_, pArgument->pTextureReflectAdd_, pArgument->pTexture3D_, pArgument->pTextureDepth_ );
	pObjectRiver_->SetPositionY( 5.0f );
	pArgument->pEffectParameter_->SetHeightReflect( 5.0f );

	// フェードイン
	pArgument->pFade_->FadeIn( 20 );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int SceneSplash::Finalize( void )
{
	// 川の開放
	delete pObjectRiver_;
	pObjectRiver_ = nullptr;

	// スキンメッシュの開放
	delete pObjectSkinMesh_;
	pObjectSkinMesh_ = nullptr;

	// ビルボードの開放
	delete pObjectBoard_;
	pObjectBoard_ = nullptr;

	// テクスチャなしモデルの開放
	delete pObjectModelMaterial_;
	pObjectModelMaterial_ = nullptr;

	// モデルの開放
	delete[] pObjectModel_;
	pObjectModel_ = nullptr;

	// スカイドームの開放
	delete pObjectSky_;
	pObjectSky_ = nullptr;

	// メッシュの開放
	delete pObjectMesh_;
	pObjectMesh_ = nullptr;

	// 2Dオブジェクトの開放
	delete pObject2D_;
	pObject2D_ = nullptr;

	// ポイントスプライト管理クラスの開放
	delete pPoint_;
	pPoint_ = nullptr;

	// ポイントライトの開放
	for( int counterLight = 0; counterLight < GraphicMain::LIGHT_POINT_MAX; ++counterLight )
	{
		if( ppPointLight_[ counterLight ] != nullptr )
		{
			ppPointLight_[ counterLight ]->Release();
			ppPointLight_[ counterLight ] = nullptr;
		}
	}
	delete[] ppPointLight_;
	ppPointLight_ = nullptr;

	// ライトの開放
	if( pLight_ != nullptr )
	{
		pLight_->Release();
		pLight_ = nullptr;
	}

	// カメラ処理の開放
	pCamera_->SetState( nullptr );
	delete pCameraState_;
	pCameraState_ = nullptr;

	// 基本クラスの処理
	int		result;		// 実行結果
	result = SceneMain::Finalize();
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
// Arg    : SceneArgumentMain* pArgument		: シーン引数
//==============================================================================
int SceneSplash::Reinitialize( SceneArgumentMain* pArgument )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pArgument );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : SceneSplash* pOut					: コピー先アドレス
//==============================================================================
int SceneSplash::Copy( SceneSplash* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = SceneMain::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneSplash::Update( void )
{
	// テスト
	PrintDebug( _T( "スプラッシュ\n" ) );

	// ポイントスプライト管理クラスの更新
	pPoint_->Update();

	// 焦点距離の更新
	D3DXVECTOR3	positionLookAt;		// 注視点
	pCamera_[ GraphicMain::CAMERA_GENERAL ].GetPositionLookAt( &positionLookAt );
	pArgument_->pEffectParameter_->SetForcus( pCamera_[ GraphicMain::CAMERA_GENERAL ].GetViewZ( positionLookAt ) );

	// 影用カメラの更新
	D3DXVECTOR3	vectorLight;		// ライトベクトル
	pLight_->GetVector( &vectorLight );
	vectorLight *= -500.0f;
	pCameraShadow_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadow_->SetPositionLookAt( positionLookAt );

	// モデルの回転
	pObjectModel_[ 0 ].AddRotationY( 0.01f );
	pObjectBoard_->AddRotationZ( 0.1f );
#if 0
	// ライトの回転
	static float	rotL = 0.0f;
	D3DXVECTOR3		vecDir;
	vecDir.x = cosf( rotL );
	vecDir.y = -0.5f;
	vecDir.z = sinf( rotL );
	pLight_[ GraphicMain::LIGHT_DIRECTIONAL_GENERAL ].SetVector( vecDir );
	rotL += 0.01f;
	if( rotL > 2.0f * D3DX_PI )
	{
		rotL -= 2.0f * D3DX_PI;
	}
#endif

	// ライトの回転角度を決定
	float	angleLight;		// ライトの回転角度
	angleLight = D3DX_PI * timerLight_ / 120.0f;
	++timerLight_;

	// 赤ポイントライトの移動
	D3DXVECTOR3	positionPointR;		// ポイントライトの座標
	ppPointLight_[ 0 ]->GetPosition( &positionPointR );
	positionPointR.x = 30.0f * cosf( angleLight );
	positionPointR.z = 30.0f * sinf( angleLight );
	ppPointLight_[ 0 ]->SetPosition( positionPointR );

	// 青ポイントライトの移動
	D3DXVECTOR3	positionPointB;		// ポイントライトの座標
	ppPointLight_[ 1 ]->GetPosition( &positionPointB );
	positionPointB.x = 30.0f * cosf( angleLight + D3DX_PI );
	positionPointB.z = 30.0f * sinf( angleLight + D3DX_PI );
	if( timerLight_ % 240 < 120 )
	{
		Utility::SplineVector3( D3DXVECTOR3( -50.0f, 20.0f, -50.0f ), D3DXVECTOR3( 150.0f, 150.0f, 0.0f ), D3DXVECTOR3( 100.0f, 70.0f, 100.0f ), D3DXVECTOR3( 0.0f, 150.0f, 150.0f ),
			static_cast< float >( timerLight_ % 120 ) / 120.0f, &positionPointB );
	}
	else
	{
		Utility::SplineVector3( D3DXVECTOR3( 100.0f, 70.0f, 100.0f ), D3DXVECTOR3( 0.0f, 150.0f, 150.0f ), D3DXVECTOR3( -50.0f, 20.0f, -50.0f ), D3DXVECTOR3( 150.0f, 150.0f, 0.0f ),
			static_cast< float >( (timerLight_ % 240) - 120 ) / 120.0f, &positionPointB );
	}
	ppPointLight_[ 1 ]->SetPosition( positionPointB );

	// 緑ポイントライトの移動
	D3DXVECTOR3	positionPointG;		// ポイントライトの座標
	ppPointLight_[ 2 ]->GetPosition( &positionPointG );
	if( pArgument_->pVirtualController_->IsPress( VC_LEFT ) )
	{
		positionPointG.x -= 1.0f;
	}
	else if( pArgument_->pVirtualController_->IsPress( VC_RIGHT ) )
	{
		positionPointG.x += 1.0f;
	}
	if( pArgument_->pVirtualController_->IsPress( VC_DOWN ) )
	{
		positionPointG.z -= 1.0f;
	}
	else if( pArgument_->pVirtualController_->IsPress( VC_UP ) )
	{
		positionPointG.z += 1.0f;
	}
	if( pArgument_->pKeyboard_->IsPress( DIK_COMMA ) )
	{
		positionPointG.y -= 1.0f;
	}
	else if( pArgument_->pKeyboard_->IsPress( DIK_PERIOD ) )
	{
		positionPointG.y += 1.0f;
	}
	ppPointLight_[ 2 ]->SetPosition( positionPointG );

	// エフェクトの発生
	pPoint_->Add( 20, positionPointR, D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, PointMain::STATE_ADD );
	pPoint_->Add( 20, positionPointB, D3DXCOLOR( 0.25f, 0.25f, 1.0f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, PointMain::STATE_ADD );
	pPoint_->Add( 20, positionPointG, D3DXCOLOR( 0.25f, 1.0f, 0.25f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, PointMain::STATE_ADD );

	// 点光源を有効にする
	if( pArgument_->pKeyboard_->IsTrigger( DIK_LBRACKET ) )
	{
		ppPointLight_[ countLight_ ]->SetIsEnable( true );
		++countLight_;
		if( countLight_ >= GraphicMain::LIGHT_POINT_MAX )
		{
			countLight_ = GraphicMain::LIGHT_POINT_MAX - 1;
		}
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_RBRACKET ) )
	{
		ppPointLight_[ countLight_ ]->SetIsEnable( false );
		--countLight_;
		if( countLight_ < 0 )
		{
			countLight_ = 0;
		}
	}

	// オブジェクトの移動
	if( pArgument_->pKeyboard_->IsPress( DIK_A ) )
	{
		pObjectModel_[ 0 ].AddPositionX( -1.0f );
	}
	else if( pArgument_->pKeyboard_->IsPress( DIK_D ) )
	{
		pObjectModel_[ 0 ].AddPositionX( 1.0f );
	}
	if( pArgument_->pKeyboard_->IsPress( DIK_S ) )
	{
		pObjectModel_[ 0 ].AddPositionZ( -1.0f );
	}
	else if( pArgument_->pKeyboard_->IsPress( DIK_W ) )
	{
		pObjectModel_[ 0 ].AddPositionZ( 1.0f );
	}

	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_TITLE );
		SetIsEnd( true );
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_RETURN ) )
	{
		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneSplash::InitializeSelf( void )
{
	// メンバ変数の初期化
	pCamera_ = nullptr;
	pCameraShadow_ = nullptr;
	pLight_ = nullptr;
	ppPointLight_ = nullptr;
	pPoint_ = nullptr;
	pObject2D_ = nullptr;
	pObjectMesh_ = nullptr;
	pObjectSky_ = nullptr;
	pObjectModel_ = nullptr;
	pObjectModelMaterial_ = nullptr;
	pObjectBoard_ = nullptr;
	pObjectSkinMesh_ = nullptr;
	pObjectRiver_ = nullptr;
	timerLight_ = 0;
	countLight_ = 0;
	pCameraState_ = nullptr;
}
