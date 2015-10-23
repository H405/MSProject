//==============================================================================
//
// File   : SceneGame.cpp
// Brief  : ゲームシーンクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "SceneGame.h"
#include "../framework/camera/CameraObject.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/light/LightDirection.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerPoint.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

// テスト
#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectSky.h"

#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/polygon/PolygonPoint.h"

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
SceneGame::SceneGame( void ) : SceneMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
SceneGame::~SceneGame( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : SceneArgumentMain* pArgument		: シーン引数
//==============================================================================
int SceneGame::Initialize( SceneArgumentMain* pArgument )
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
	result = pCamera_->Initialize( D3DX_PI / 4.0f, 1280, 720, 0.1f, 1000.0f,
		D3DXVECTOR3( 0.0f, 20.0f, -100.0f ), D3DXVECTOR3( 0.0f, 0.0f, 10.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
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
	result = pLight_->Initialize( D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( 0.0f, -0.7f, 0.7f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL, pLight_ );

	// ポイントスプライト管理クラスの生成
	Effect*		pEffectPoint = nullptr;			// ポイントエフェクト
	Texture*	pTexturePoint = nullptr;		// ポイントテクスチャ
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "effect000.jpg" ) );
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

	// テスト初期化
	Effect*		pEffect = pArgument->pEffect_->Get( _T( "Polygon3D.fx" ) );
	Texture*	pTexture = pArgument->pTexture_->Get( _T( "title_logo.png" ) );;
	pObject_ = new Object2D[ 100 ];
	countObject_ = 0;
	pObject3D_ = new Object3D();
	pObject3D_->Initialize( 0 );
	pObject3D_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffect, pTexture );
	pObject3D_->SetScale( 1000.0f, 1.0f, 1000.0f );
	pObject3D_->SetPositionY( -40.0f );

	Effect*	pEffectModel = pArgument->pEffect_->Get( _T( "Model.fx" ) );
	Model*	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );
	pObjectModel_ = new ObjectModel();
	pObjectModel_->Initialize( 0 );
	pObjectModel_->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffectModel );

	Effect*	pEffectMesh = pArgument->pEffect_->Get( _T( "Mesh.fx" ) );
	pObjectMesh_ = new ObjectMesh();
	pObjectMesh_->Initialize( 0, pArgument->pDevice_, 10, 10, 100.0f, 100.0f, 1.0f, 1.0f );
	pObjectMesh_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectMesh, pTexture );

	Effect*	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 500.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pTexture );
#if 0
	pPolygonPoint_ = new PolygonPoint();
	pPolygonPoint_->Initialize( 32, pArgument->pDevice_ );

	Effect*	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pGraphicPoint_ = new GraphicPoint();
	pGraphicPoint_->Initialize( 0, pArgument->pEffectParameter_, pEffectPoint, pPolygonPoint_, pTexture->pTexture_ );
#endif
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
int SceneGame::Finalize( void )
{
	// テスト終了
	delete pObjectSky_;
	pObjectSky_ = nullptr;
	delete pObjectMesh_;
	pObjectMesh_ = nullptr;
	delete pObjectModel_;
	pObjectModel_ = nullptr;
	delete pObject3D_;
	pObject3D_ = nullptr;
	delete[] pObject_;
	pObject_ = nullptr;

	// ポイントスプライト管理クラスの開放
	delete pPoint_;
	pPoint_ = nullptr;

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
int SceneGame::Reinitialize( SceneArgumentMain* pArgument )
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
// Arg    : SceneGame* pOut						: コピー先アドレス
//==============================================================================
int SceneGame::Copy( SceneGame* pOut ) const
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
void SceneGame::Update( void )
{
	// カメラの更新
	pCamera_->Update();

	// ポイントスプライト管理クラスの更新
	pPoint_->Update();

	// テスト
	for( int i = 0; i < 10; ++i )
	{
		D3DXVECTOR3	velocityPoint;
		float		angleY = 2.0f * D3DX_PI * (static_cast< float >( rand() ) / RAND_MAX);
		float		angleZ = 2.0f * D3DX_PI * (static_cast< float >( rand() ) / RAND_MAX);
		velocityPoint.x = cosf( angleY ) * sinf( angleZ );
		velocityPoint.y = cosf( angleZ );
		velocityPoint.z = sinf( angleY ) * sinf( angleZ );
		pPoint_->Add( 100, D3DXVECTOR3( 0.0f, 10.0f, 0.0f ), D3DXCOLOR( 1.0f, 0.2f, 0.2f, 0.9f ), 100.0f,
			velocityPoint, D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ), 0.0f, ManagerPoint::STATE_ADD );
	}

	// テスト
	PrintDebug( _T( "ゲームシーン\n" ) );
	if( pArgument_->pKeyboard_->IsTrigger( DIK_A ) && countObject_ < 100 )
	{
		Effect*		pEffect = nullptr;
		Texture*	pTexture = nullptr;
		pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
		pTexture = pArgument_->pTexture_->Get( _T( "title_logo.png" ) );
		pObject_[ countObject_ ].Initialize( 0 );
		pObject_[ countObject_ ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect, pTexture );
		pObject_[ countObject_ ].SetColor( 0.5f, 1.0f, 0.5f, 0.8f );
		++countObject_;
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_D ) && countObject_ > 0 )
	{
		pObject_[ countObject_ - 1 ].Finalize();
		--countObject_;
	}
	if( pArgument_->pKeyboard_->IsTrigger( DIK_C ) )
	{
		pCamera_->SetDebug( true );
	}
	pObjectModel_->AddRotationY( 0.1f );

	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_RESULT );
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
void SceneGame::InitializeSelf( void )
{
	// メンバ変数の初期化
	pCamera_ = nullptr;
	pLight_ = nullptr;
	pPoint_ = nullptr;
}
