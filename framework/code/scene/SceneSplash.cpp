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
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

#include "../framework/camera/CameraObject.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/LightPoint.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Window.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectSky.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerPoint.h"

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

	// カメラの生成
	pCamera_ = new CameraObject();
	if( pCamera_ == nullptr )
	{
		return 1;
	}
	result = pCamera_->Initialize(
		D3DX_PI / 4.0f,
		pArgument->pWindow_->GetWidth(),
		pArgument->pWindow_->GetHeight(),
		0.1f,
		1000.0f,
		D3DXVECTOR3( 0.0f, 30.0f, -150.0f ),
		D3DXVECTOR3( 0.0f, 0.0f, 20.0f ),
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f )
		);

	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetCamera( GraphicMain::CAMERA_GENERAL, pCamera_ );

	// ライトの生成
	pLight_ = new LightDirection();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	result = pLight_->Initialize( D3DXCOLOR( 0.25f, 0.3f, 0.4f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( -1.0f, -1.0f, 1.0f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL, pLight_ );

	// ポイントライトの生成
	pPointLight_ = new LightPoint[ GraphicMain::LIGHT_POINT_MAX ];
	if( pPointLight_ == nullptr )
	{
		return 1;
	}

	result = pPointLight_[ 0 ].Initialize( D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( -20.0f, 10.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.02f, 0.001f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightPoint( 0, &pPointLight_[ 0 ] );

	result = pPointLight_[ 1 ].Initialize( D3DXCOLOR( 0.25f, 0.25f, 1.0f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 20.0f, 10.0f, 0.0f ),  D3DXVECTOR3( 0.0f, 0.02f, 0.001f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightPoint( 1, &pPointLight_[ 1 ] );

	result = pPointLight_[ 2 ].Initialize( D3DXCOLOR( 0.25f, 1.0f, 0.25f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		D3DXVECTOR3( 0.0f, 10.0f, -100.0f ),  D3DXVECTOR3( 0.0f, 0.01f, 0.002f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightPoint( 2, &pPointLight_[ 2 ] );

	// ポイントライトの個数を設定
	pArgument->pEffectParameter_->SetCountLightPoint( 3 );

	// 環境光の設定
	pArgument->pEffectParameter_->SetColorAmbient( 0.1f, 0.15f, 0.2f );

	// ポイントスプライト管理クラスの生成
	Effect*		pEffectPoint = nullptr;			// ポイントエフェクト
	Texture*	pTexturePoint = nullptr;		// ポイントテクスチャ
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "common/effect000.jpg" ) );
	pPoint_ = new ManagerPoint();
	if( pPoint_ == nullptr )
	{
		return 1;
	}
	result = pPoint_->Initialize( 4096, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		return result;
	}

	// 2Dオブジェクトの生成
	Effect*		pEffect2D = nullptr;		// エフェクト
	Texture*	pTexture2D = nullptr;		// テクスチャ
	pEffect2D = pArgument->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture2D = pArgument_->pTexture_->Get( _T( "test/title_logo.png" ) );
	pObject2D_ = new Object2D();
	pObject2D_->Initialize( 0 );
	pObject2D_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffect2D, pTexture2D );
	pObject2D_->SetPosition( 430.0f, 310.0f, 0.0f );

	// メッシュの生成
	Effect*		pEffectMesh = nullptr;		// エフェクト
	Texture*	pTextureMesh = nullptr;		// メッシュ
	pEffectMesh = pArgument->pEffect_->Get( _T( "Mesh.fx" ) );
	pTextureMesh = pArgument_->pTexture_->Get( _T( "test/field001.jpg" ) );
	pObjectMesh_ = new ObjectMesh();
	pObjectMesh_->Initialize( 0, pArgument->pDevice_, 20, 20, 50.0f, 50.0f, 1.0f, 1.0f );
	pObjectMesh_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectMesh, pTextureMesh );

	// スカイドームの生成
	Effect*		pEffectSky = nullptr;		// エフェクト
	Texture*	pTextureSky = nullptr;		// テクスチャ
	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pTextureSky = pArgument_->pTexture_->Get( _T( "test/night.png" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 500.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pTextureSky );

	// モデルの生成
	Effect*	pEffectModel = nullptr;		// エフェクト
	Model*	pModel = nullptr;			// モデル
	pEffectModel = pArgument->pEffect_->Get( _T( "Model.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );
	pObjectModel_ = new ObjectModel[ COUNT_MODEL ];
	pObjectModel_[ 0 ].Initialize( 0 );
	pObjectModel_[ 0 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel );
	pObjectModel_[ 1 ].Initialize( 0 );
	pObjectModel_[ 1 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel );
	pObjectModel_[ 1 ].SetPositionX( 50.0f );
	pObjectModel_[ 2 ].Initialize( 0 );
	pObjectModel_[ 2 ].CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel );
	pObjectModel_[ 2 ].SetPositionX( -50.0f );

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
	// ポイントライトの個数を設定
	pArgument_->pEffectParameter_->SetCountLightPoint( 0 );

	// モデルの破棄
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
	delete[] pPointLight_;
	pPointLight_ = nullptr;

	// ライトの開放
	delete pLight_;
	pLight_ = nullptr;
	pArgument_->pEffectParameter_->SetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL, nullptr );

	// カメラの開放
	delete pCamera_;
	pCamera_ = nullptr;
	pArgument_->pEffectParameter_->SetCamera( GraphicMain::CAMERA_GENERAL, pCamera_ );

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

	// カメラの更新
	pCamera_->Update();

	// ポイントスプライト管理クラスの更新
	pPoint_->Update();

	// モデルの回転
	pObjectModel_[ 0 ].AddRotationY( 0.01f );

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
	pPointLight_[ 0 ].GetPosition( &positionPointR );
	positionPointR.x = 30.0f * cosf( angleLight );
	positionPointR.z = 30.0f * sinf( angleLight );
	pPointLight_[ 0 ].SetPosition( positionPointR );

	// 青ポイントライトの移動
	D3DXVECTOR3	positionPointB;		// ポイントライトの座標
	pPointLight_[ 1 ].GetPosition( &positionPointB );
	positionPointB.x = 30.0f * cosf( angleLight + D3DX_PI );
	positionPointB.z = 30.0f * sinf( angleLight + D3DX_PI );
	pPointLight_[ 1 ].SetPosition( positionPointB );

	// 緑ポイントライトの移動
	D3DXVECTOR3	positionPointG;		// ポイントライトの座標
	pPointLight_[ 2 ].GetPosition( &positionPointG );
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
	pPointLight_[ 2 ].SetPosition( positionPointG );

	// エフェクトの発生
	pPoint_->Add( 20, positionPointR, D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, ManagerPoint::STATE_ADD );
	pPoint_->Add( 20, positionPointB, D3DXCOLOR( 0.25f, 0.25f, 1.0f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, ManagerPoint::STATE_ADD );
	pPoint_->Add( 20, positionPointG, D3DXCOLOR( 0.25f, 1.0f, 0.25f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, ManagerPoint::STATE_ADD );

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
	pLight_ = nullptr;
	pPointLight_ = nullptr;
	pPoint_ = nullptr;
	pObject2D_ = nullptr;
	pObjectMesh_ = nullptr;
	pObjectSky_ = nullptr;
	pObjectModel_ = nullptr;
	timerLight_ = 0;
}
