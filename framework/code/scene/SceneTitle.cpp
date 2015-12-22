//==============================================================================
//
// File   : SceneTitle.cpp
// Brief  : タイトルシーンクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "SceneTitle.h"
#include "../framework/camera/CameraObject.h"
#include "../framework/camera/ManagerCamera.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/LightPoint.h"
#include "../framework/light/ManagerLight.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/ManagerUpdate.h"
#include "../framework/system/Window.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"
#include "../object/ObjectRiver.h"

#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectSky.h"
#include "../object/ObjectSkinMesh.h"
#include "../framework/polygon/PolygonMesh.h"
#include "../system/point/ManagerPoint.h"
#include "../system/ManagerFireworks.h"
#include "../system/ManagerTarget.h"
#include "../system/fire/Fire.h"
#include "../object/ObjectWaterwheel.h"
#include "../system/player/Player.h"
#include "../framework/resource/ManagerSound.h"
#include "../framework/resource/Sound.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//******************************************************************************
// 静的変数
//******************************************************************************
//	点滅用カウント数
static const int flashingCountHirf = 20;
static const int flashingCountMax = 40;

//	○○開始　文字のサイズ
static const float startXX_NormalSizeX = 400.0f;
static const float startXX_NormalSizeY = 120.0f;

//	透明値加算値
static const float addFlashingAlpha = 0.02f;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
SceneTitle::SceneTitle( void ) : SceneMain()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::InitializeSelf( void )
{
	// メンバ変数の初期化
	pCamera_ = nullptr;
	pCameraShadowNear_ = nullptr;
	pCameraShadowFar_ = nullptr;
	ppCameraShadowPoint_ = nullptr;
	pLight_ = nullptr;

	//	タイトルUI関係
	//----------------------------------------------------------
	titleLogo = nullptr;
	pushAKey = nullptr;
	startGame = nullptr;
	startTutorial = nullptr;
	finger = nullptr;
	reConnectWiimote = nullptr;
	reConnectWiiboard = nullptr;

	chooseObject = nullptr;
	chooseObjectPrev = nullptr;

	pushAKeyFlashingCount = 0;
	pushChooseObjectFlashingCount = 0;

	chooseFlag = false;
	//----------------------------------------------------------



	//	ゲーム用ステージ・３Dオブジェクト関係
	//----------------------------------------------------------
	sky = nullptr;
	river = nullptr;
	field = nullptr;

	bridge = nullptr;
	waterwheel = nullptr;
	houses = nullptr;
	gate = nullptr;

//	markers = nullptr;

	player = nullptr;

	managerPoint = nullptr;
	managerFireworks = nullptr;

//	pObjectSkinMesh_[0] = nullptr;
//	pObjectSkinMesh_[1] = nullptr;
//	pObjectSkinMesh_[2] = nullptr;

	launchFlag = false;
	launchCount = 0;

	for(int count = 0;count < FIREWORKS_MAX;count++)
		fireworksTable[count] = -1;

	fireworksTableIndex = 0;
	//----------------------------------------------------------

	//	音関連
	//----------------------------------------------------------
	bgmSound = nullptr;
	desideSound = nullptr;
	selectSound = nullptr;
	cancelSound = nullptr;
	//----------------------------------------------------------



	fpUpdate = nullptr;
	fpUpdatePrev = nullptr;
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
SceneTitle::~SceneTitle( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : SceneArgumentMain* pArgument		: シーン引数
//==============================================================================
int SceneTitle::Initialize( SceneArgumentMain* pArgument )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = SceneMain::Initialize( pArgument );
	if( result != 0 )
	{
		return result;
	}

	// カメラの生成
	pCamera_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pCamera_->Set(
		D3DX_PI / 4.0f,
		pArgument->pWindow_->GetWidth(),
		pArgument->pWindow_->GetHeight(),
		0.1f,
		20000.0f,
		D3DXVECTOR3( 0.0f, 120.0f, -2400.0f ),
		D3DXVECTOR3( 0.0f, 720.0f, 0.0f ),
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	
	// ライトの生成
	pLight_ = pArgument->pLight_->GetLightDirection();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	pLight_->Set( D3DXCOLOR( 0.25f, 0.3f, 0.4f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( -1.0f, -1.0f, -1.0f ) );

	// 影用カメラ近の設定
	D3DXVECTOR3	vectorLight;		// ライトベクトル
	pLight_->GetVector( &vectorLight );
	vectorLight *= -3500.0f;
	pCameraShadowNear_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_SHADOW_NEAR );
	pCameraShadowNear_->Set( D3DX_PI / 4.0f, 8 * pArgument->pWindow_->GetWidth(), 8 * pArgument->pWindow_->GetHeight(), 0.1f, 7000.0f,
		vectorLight, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), false );

	// 影用カメラ遠の設定
	pLight_->GetVector( &vectorLight );
	vectorLight *= -10000.0f;
	pCameraShadowFar_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_SHADOW_FAR );
	pCameraShadowFar_->Set( D3DX_PI / 4.0f, 24 * pArgument->pWindow_->GetWidth(), 24 * pArgument->pWindow_->GetHeight(), 0.1f, 20000.0f,
		vectorLight, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), false );

	// 影用カメラ点の設定
	ppCameraShadowPoint_ = new CameraObject*[ GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW ];
	if( ppCameraShadowPoint_ == nullptr )
	{
		return 1;
	}
	for( int counterLightPoint = 0; counterLightPoint < GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW; ++ counterLightPoint )
	{
		ppCameraShadowPoint_[ counterLightPoint ] = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_SHADOW_POINT_0 + counterLightPoint );
		ppCameraShadowPoint_[ counterLightPoint ]->Set( D3DX_PI / 4.0f, pArgument->pWindow_->GetWidth(), pArgument->pWindow_->GetHeight(), 0.1f, 10000.0f,
			D3DXVECTOR3( 0.0f, 1000.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ), false );
	}

	// 環境光の設定
	pArgument->pEffectParameter_->SetColorAmbient( 0.1f, 0.15f, 0.2f );

	//	オブジェクトの生成開始
	Effect*		pEffect = nullptr;
	Effect*		pEffectReflect = nullptr;
	Effect*		pEffectShadow = nullptr;
	Effect*		pEffectParaboloid = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;

	// スカイドームの生成
	Texture*	pTextureSky = nullptr;				// テクスチャ
	Effect*		pEffectSkyGeneral = nullptr;		// 通常描画エフェクト
	Effect*		pEffectSkyReflect = nullptr;		// 反射描画エフェクト
	pTextureSky = pArgument_->pTexture_->Get( _T( "test/night.png" ) );
	pEffectSkyGeneral = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pEffectSkyReflect = pArgument->pEffect_->Get( _T( "SkyReflect.fx" ) );
	sky = new ObjectSky();
	sky->Initialize( 0, pArgument->pDevice_, 32, 32, 11500.0f, 1.0f, 1.0f );
	sky->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSkyGeneral, pEffectSkyReflect, pTextureSky );

	// 川の生成
	Model*	pModelRiver = nullptr;		// モデル
	Effect*	pEffectRiver = nullptr;		// エフェクト
	pModelRiver = pArgument->pModel_->Get( _T( "river_ver103_04.x" ), Vertex::ELEMENT_SET_NORMAL_MAP );
	pEffectRiver = pArgument->pEffect_->Get( "Water.fx" );
	river = new ObjectRiver();
	river->Initialize( 0 );
	river->CreateGraphic( 0, pModelRiver, pArgument->pEffectParameter_, pEffectRiver, pArgument->pTextureNormalWave_,
		pArgument->pTextureReflect_, pArgument->pTextureReflectNotLight_, pArgument->pTextureReflectAdd_, pArgument->pTexture3D_, pArgument->pTextureDepth_ );
	river->SetPositionY( -100.0f );
	pArgument->pEffectParameter_->SetHeightReflect( -100.0f );
	//pRiver_->SetIsEnable(false);

	// 地形の生成
	Model*	pModelField = nullptr;					// モデル
	Effect*	pEffectFieldGeneral = nullptr;			// 通常描画エフェクト
	Effect*	pEffectFieldReflect = nullptr;			// 反射エフェクト
	Effect*	pEffectFieldShadow = nullptr;			// 影エフェクト
	Effect*	pEffectFieldParaboloid = nullptr;		// 放物変換エフェクト
	pModelField = pArgument->pModel_->Get( _T( "Stagever.1.03.x" ) );
	pEffectFieldGeneral = pArgument->pEffect_->Get( "Model.fx" );
	pEffectFieldReflect = pArgument->pEffect_->Get( "ModelReflect.fx" );
	pEffectFieldShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectFieldParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	field = new ObjectModel();
	field->Initialize( 0 );
	field->CreateGraphic( 0, pModelField, pArgument->pEffectParameter_, pEffectFieldGeneral, pEffectFieldReflect, pEffectFieldShadow, pEffectFieldParaboloid );
	field->SetPositionY( -400.0f );
	field->SetScale( 2.0f, 2.0f, 2.0f );

	// 橋の生成
	Model*	pModelBridge = nullptr;					// モデル
	Effect*	pEffectBridgeGeneral = nullptr;			// 通常描画エフェクト
	Effect*	pEffectBridgeReflect = nullptr;			// 反射エフェクト
	Effect*	pEffectBridgeShadow = nullptr;			// 影エフェクト
	Effect*	pEffectBridgeParaboloid = nullptr;		// 放物変換エフェクト
	pModelBridge = pArgument->pModel_->Get( _T( "bridge_002.x" ) );
	pEffectBridgeGeneral = pArgument->pEffect_->Get( "ModelMaterial.fx" );
	pEffectBridgeReflect = pArgument->pEffect_->Get( "ModelMaterialReflect.fx" );
	pEffectBridgeShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectBridgeParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	bridge = new ObjectModelMaterial();
	bridge->Initialize( 0 );
	bridge->CreateGraphic( 0, pModelBridge, pArgument->pEffectParameter_, pEffectBridgeGeneral, pEffectBridgeReflect, pEffectBridgeShadow, pEffectBridgeParaboloid );
	bridge->SetPosition( 1558.0f, 460.0f, -2240.0f );
	bridge->SetRotationY( DEG_TO_RAD( 101.0f ) );
	bridge->SetScale( 285.0f, 285.0f, 285.0f );

	// 水車の生成
	waterwheel = new ObjectWaterwheel();
	waterwheel->Initialize( D3DXVECTOR3( 110.0f, 230.0f, 3780.0f ), DEG_TO_RAD( 74 ), -0.001f, pArgument );

	// 家の生成
	Model*	pModelHouse = nullptr;					// モデル
	Effect*	pEffectHouseGeneral = nullptr;			// 通常描画エフェクト
	Effect*	pEffectHouseReflect = nullptr;			// 反射エフェクト
	Effect*	pEffectHouseShadow = nullptr;			// 影エフェクト
	Effect*	pEffectHouseParaboloid = nullptr;		// 放物変換エフェクト
	pModelHouse = pArgument->pModel_->Get( _T( "house_002.x" ) );
	pEffectHouseGeneral = pArgument->pEffect_->Get( "ModelMaterial.fx" );
	pEffectHouseReflect = pArgument->pEffect_->Get( "ModelMaterialReflect.fx" );
	pEffectHouseShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectHouseParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	houses = new ObjectModelMaterial[ COUNT_HOUSE ];
	for( int counterHouse = 0; counterHouse < COUNT_HOUSE; ++counterHouse )
	{
		houses[ counterHouse ].Initialize( 0 );
		houses[ counterHouse ].CreateGraphic( 0, pModelHouse, pArgument->pEffectParameter_, pEffectHouseGeneral, pEffectHouseReflect, pEffectHouseShadow, pEffectHouseParaboloid );
		houses[ counterHouse ].SetScale( 300.0f, 300.0f, 300.0f );
	}
	houses[ 0 ].SetPosition( 640.0f, 0.0f, 3690.0f );
	houses[ 0 ].SetRotationY( DEG_TO_RAD( 254.0f ) );
	houses[ 0 ].SetScale( 150.0f, 150.0f, 150.0f );
	houses[ 1 ].SetPosition( -3700.0f, 0.0f, 2480.0f );
	houses[ 1 ].SetRotationY( DEG_TO_RAD( 252.0f ) );
	houses[ 2 ].SetPosition( -3120.0f, 0.0f, 1010.0f );
	houses[ 2 ].SetRotationY( DEG_TO_RAD( 243.0f ) );
	houses[ 3 ].SetPosition( -2030.0f, 0.0f, -750.0f );
	houses[ 3 ].SetRotationY( DEG_TO_RAD( 222.0f ) );
	houses[ 4 ].SetPosition( -1880.0f, 0.0f, 3160.0f );
	houses[ 4 ].SetRotationY( DEG_TO_RAD( 51.0f ) );
	houses[ 5 ].SetPosition( 3500.0f, 0.0f, 5500.0f );
	houses[ 5 ].SetRotationY( DEG_TO_RAD( 58.0f ) );
	houses[ 6 ].SetPosition( 4260.0f, 0.0f, 3650.0f );
	houses[ 6 ].SetRotationY( DEG_TO_RAD( 76.0f ) );
	houses[ 7 ].SetPosition( 4460.0f, 0.0f, 1610.0f );
	houses[ 7 ].SetRotationY( DEG_TO_RAD( 92.0f ) );
	houses[ 8 ].SetPosition( 1200.0f, 0.0f, 6400.0f );
	houses[ 8 ].SetRotationY( DEG_TO_RAD( 353.0f ) );
	houses[ 9 ].SetPosition( 4500.0f, 0.0f, -4500.0f );
	houses[ 9 ].SetRotationY( DEG_TO_RAD( 125.0f ) );
	houses[ 10 ].SetPosition( 2660.0f, 0.0f, -5720.0f );
	houses[ 10 ].SetRotationY( DEG_TO_RAD( 169.0f ) );

	// 鳥居の生成
	Model*	pModelGate = nullptr;					// モデル
	Effect*	pEffectGateGeneral = nullptr;			// 通常描画エフェクト
	Effect*	pEffectGateReflect = nullptr;			// 反射エフェクト
	Effect*	pEffectGateShadow = nullptr;			// 影エフェクト
	Effect*	pEffectGateParaboloid = nullptr;		// 放物変換エフェクト
	pModelGate = pArgument->pModel_->Get( _T( "torii.x" ) );
	pEffectGateGeneral = pArgument->pEffect_->Get( "ModelMaterial.fx" );
	pEffectGateReflect = pArgument->pEffect_->Get( "ModelMaterialReflect.fx" );
	pEffectGateShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectGateParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	gate = new ObjectModelMaterial();
	gate->Initialize( 0 );
	gate->CreateGraphic( 0, pModelGate, pArgument->pEffectParameter_, pEffectGateGeneral, pEffectGateReflect, pEffectGateShadow, pEffectGateParaboloid );
	gate->SetPosition( 5870.0f, 0.0f, -400.0f );
	gate->SetRotationY( DEG_TO_RAD( 90 ) );
	gate->SetScale( 1.0f, 1.0f, 1.0f );
/*
	// 場所の目印オブジェクトの生成
	Model*	pModelMarker = nullptr;					// モデル
	Effect*	pEffectMarkerGeneral = nullptr;			// 通常描画エフェクト
	Effect*	pEffectMarkerReflect = nullptr;			// 反射エフェクト
	Effect*	pEffectMarkerShadow = nullptr;			// 影エフェクト
	Effect*	pEffectMarkerParaboloid = nullptr;		// 放物変換エフェクト
	pModelMarker = pArgument->pModel_->Get( _T( "sizeTest.model" ) );
	pEffectMarkerGeneral = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectMarkerReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pEffectMarkerShadow = pArgument->pEffect_->Get( _T( "SkinMeshShadow.fx" ) );
	pEffectMarkerParaboloid = pArgument->pEffect_->Get( _T( "SkinMeshParaboloid.fx" ) );
	markers = new ObjectSkinMesh[ 4 ];
	for( int counterMarker = 0; counterMarker < 4; ++counterMarker )
	{
		markers[ counterMarker ].Initialize( 0, 0 );
		markers[ counterMarker ].CreateGraphic( 0, pModelMarker, pArgument->pEffectParameter_,
			pEffectMarkerGeneral, pEffectMarkerReflect, pEffectMarkerShadow, pEffectMarkerParaboloid );
	}
	markers[ 0 ].SetPosition( 620.0f, 0.0f, 4550.0f );
	markers[ 0 ].SetRotationY( 0.0f );
	markers[ 1 ].SetPosition( -1920.0f, 0.0f, 610.0f );
	markers[ 1 ].SetRotationY( 0.0f );
	markers[ 2 ].SetPosition( 1230.0f, 0.0f, 990.0f );
	markers[ 2 ].SetRotationY( 0.0f );
	markers[ 3 ].SetPosition( 490.0f, 0.0f, 470.0f );
	markers[ 3 ].SetRotationY( 0.0f );
*/
	//	ポイントスプライト管理オブジェクト生成
	Effect*		pEffectPoint = nullptr;				// ポイントエフェクト
	Effect*		pEffectPointReflect = nullptr;		// ポイントエフェクト
	Texture*	pTexturePoint = nullptr;			// ポイントテクスチャ
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pEffectPointReflect = pArgument->pEffect_->Get( _T( "PointReflect.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "common/effect000.jpg" ) );
	managerPoint = new ManagerPoint();
	if( managerPoint == nullptr )
	{
		//return 1;
	}
	result = managerPoint->Initialize( 25600, 17, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pEffectPointReflect, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		//return result;
	}

	//	火花オブジェクトのステート初期化
	Fire::InitializeState();

	//	花火管理オブジェクト生成
	managerFireworks = new ManagerFireworks;
	managerFireworks->Initialize(managerPoint);
	managerFireworks->loadSound(pArgument_);

	// ライトの生成
	managerFireworks->setManagerLight(pArgument->pLight_);


	//	プレイヤーオブジェクト(Posはカメラとの相対座標)
	player = new Player;
	player->Initialize(
		//D3DXVECTOR3(0.0f, 150.0f, -2000.0f),
		D3DXVECTOR3(0.0f, -100.0f, 400.0f),
		pArgument);

/*
	// スキンメッシュの生成
	Effect*	pEffectSkinMesh = nullptr;					// エフェクト
	Effect*	pEffectSkinMeshReflect = nullptr;			// エフェクト
	Effect*	pEffectSkinMeshShadow = nullptr;			// エフェクト
	Effect*	pEffectSkinMeshParaboloid = nullptr;		// エフェクト
	Model*	pModelSkinMesh = nullptr;					// モデル
	pEffectSkinMesh = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectSkinMeshReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pEffectSkinMeshShadow = pArgument->pEffect_->Get( _T( "SkinMeshShadow.fx" ) );
	pEffectSkinMeshParaboloid = pArgument->pEffect_->Get( _T( "SkinMeshParaboloid.fx" ) );
	pModelSkinMesh = pArgument_->pModel_->Get( _T( "test.model" ) );
	pObjectSkinMesh_[0] = new ObjectSkinMesh();
	pObjectSkinMesh_[0]->Initialize( 0, 1 );
	pObjectSkinMesh_[0]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_,
		pEffectSkinMesh, pEffectSkinMeshReflect, pEffectSkinMeshShadow, pEffectSkinMeshParaboloid );
	pObjectSkinMesh_[0]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[0]->SetPosition( 300.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[1] = new ObjectSkinMesh();
	pObjectSkinMesh_[1]->Initialize( 0, 1 );
	pObjectSkinMesh_[1]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_,
		pEffectSkinMesh, pEffectSkinMeshReflect, pEffectSkinMeshShadow, pEffectSkinMeshParaboloid );
	pObjectSkinMesh_[1]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[1]->SetPosition( 0.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[2] = new ObjectSkinMesh();
	pObjectSkinMesh_[2]->Initialize( 0, 1 );
	pObjectSkinMesh_[2]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_,
		pEffectSkinMesh, pEffectSkinMeshReflect, pEffectSkinMeshShadow, pEffectSkinMeshParaboloid );
	pObjectSkinMesh_[2]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[2]->SetPosition( -300.0f, 100.0f, 0.0f );
*/



	//	タイトルロゴ
	titleLogo = new Object2D;
	titleLogo->Initialize(0);
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "title/titlelogo.png" ) );

	titleLogo->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	titleLogo->SetPosition(350.0f, 100.0f, 0.0f);


	//	Aボタンを押してね
	pTexture = pArgument_->pTexture_->Get( _T( "title/pushAKey.png" ) );
	pushAKey = new Object2D;
	pushAKey->Initialize(0);

	pushAKey->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	pushAKey->SetPosition(0.0f, -200.0f, 0.0f);


	//	「演舞開始」文字オブジェクトの生成
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

	startGame = new Object2D;
	startGame->Initialize(0);

	startGame->CreateGraphic(
	0,
	pArgument_->pEffectParameter_,
	pEffect,
	pTexture);

	startGame->SetPosition(-300.0f, -212.0f, 0.0f);
	startGame->SetScaleX(startXX_NormalSizeX);
	startGame->SetScaleY(startXX_NormalSizeY);
	startGame->SetEnableGraphic(false);


	startGame->SetScaleTexture(4.0f, 16.0f);
	startGame->SetPositionTexture(0.0f, 1.0f / 16.0f * 2.0f);


	//	「練習開始」文字オブジェクトの生成
	pTexture = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

	startTutorial = new Object2D;
	startTutorial->Initialize(0);

	startTutorial->CreateGraphic(
	0,
	pArgument_->pEffectParameter_,
	pEffect,
	pTexture);

	startTutorial->SetPosition(300.0f, -212.0f, 0.0f);
	startTutorial->SetScaleX(startXX_NormalSizeX);
	startTutorial->SetScaleY(startXX_NormalSizeY);
	startTutorial->SetEnableGraphic(false);

	startTutorial->SetScaleTexture(4.0f, 16.0f);
	startTutorial->SetPositionTexture(0.0f, 1.0f / 16.0f * 3.0f);

	//	wiiリモコンが接続されていれば
	//	指の初期化
	if(pArgument_->pWiiController_->getIsConnectWiimote() == true)
	{
		pTexture = pArgument_->pTexture_->Get( _T( "common/finger.png" ) );
		finger = new Object2D;
		finger->Initialize(0);

		finger->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		finger->SetScale(50.0f, 50.0f, 0.1f);
		finger->SetEnableGraphic(false);

		//	IRで選択に変更
		chooseFlag = true;



		//	「wiiリモコン再接続要求」オブジェクト生成
		pTexture = pArgument_->pTexture_->Get( _T( "common/reConnectWiimote.png" ) );
		reConnectWiimote = new Object2D;
		reConnectWiimote->Initialize(1);

		reConnectWiimote->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		reConnectWiimote->SetEnableGraphic(false);



		//	「wiiボード再接続要求」オブジェクト生成
		pTexture = pArgument_->pTexture_->Get( _T( "common/reConnectWiiboard.png" ) );
		reConnectWiiboard = new Object2D;
		reConnectWiiboard->Initialize(1);

		reConnectWiiboard->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		reConnectWiiboard->SetEnableGraphic(false);
	}







	//	音関連の読み込み
	bgmSound = pArgument_->pSound_->Get("bgm/title.wav");
	bgmSound->Play(-1);

	desideSound = pArgument_->pSound_->Get("se/deside.wav");
	selectSound = pArgument_->pSound_->Get("se/select.wav");
	cancelSound = pArgument_->pSound_->Get("se/cancel.wav");


	DebugProc::SetIsVisible(false);


	//	更新関数セット
	fpUpdate = &SceneTitle::firstUpdate;

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
int SceneTitle::Finalize( void )
{
	bgmSound->Stop();
	desideSound->Stop();
	selectSound->Stop();
	cancelSound->Stop();

	delete reConnectWiiboard;
	reConnectWiiboard = nullptr;

	delete reConnectWiimote;
	reConnectWiimote = nullptr;

	delete finger;
	finger = nullptr;

	delete startTutorial;
	startTutorial = nullptr;

	delete startGame;
	startGame = nullptr;

	delete pushAKey;
	pushAKey = nullptr;

	delete titleLogo;
	titleLogo = nullptr;
/*
	delete pObjectSkinMesh_[2];
	delete pObjectSkinMesh_[1];
	delete pObjectSkinMesh_[0];
	pObjectSkinMesh_[2] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[0] = nullptr;
*/
	delete player;
	player = nullptr;

	delete managerFireworks;
	managerFireworks = nullptr;

	Fire::FinalizeState();

	delete managerPoint;
	managerPoint = nullptr;

	// 場所目印オブジェクトの開放
//	delete[] markers;
//	markers = nullptr;

	// 鳥居オブジェクトの開放
	delete gate;
	gate = nullptr;

	// 家オブジェクトの開放
	delete[] houses;
	houses = nullptr;

	// 水車オブジェクトの開放
	delete waterwheel;
	waterwheel = nullptr;

	// 橋オブジェクトの開放
	delete bridge;
	bridge = nullptr;

	// 地形オブジェクトの開放
	delete field;
	field = nullptr;

	// 川オブジェクトの開放
	delete river;
	river = nullptr;

	// 空オブジェクトの開放
	delete sky;
	sky = nullptr;

	// ライトの開放
	if( pLight_ != nullptr )
	{
		pLight_->Release();
		pLight_ = nullptr;
	}

	// 影用カメラ点の開放
	for( int counterLightPoint = 0; counterLightPoint < GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW; ++counterLightPoint )
	{
		if( ppCameraShadowPoint_[ counterLightPoint ] != nullptr )
		{
			ppCameraShadowPoint_[ counterLightPoint ]->SetState( nullptr );
			ppCameraShadowPoint_[ counterLightPoint ] = nullptr;
		}
	}
	delete[] ppCameraShadowPoint_;
	ppCameraShadowPoint_ = nullptr;

	// 影用カメラ遠の開放
	if( pCameraShadowFar_ != nullptr )
	{
		pCameraShadowFar_->SetState( nullptr );
		pCameraShadowFar_ = nullptr;
	}

	// 影用カメラ近の開放
	if( pCameraShadowNear_ != nullptr )
	{
		pCameraShadowNear_->SetState( nullptr );
		pCameraShadowNear_ = nullptr;
	}

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
int SceneTitle::Reinitialize( SceneArgumentMain* pArgument )
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
// Arg    : SceneTitle* pOut					: コピー先アドレス
//==============================================================================
int SceneTitle::Copy( SceneTitle* pOut ) const
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
void SceneTitle::Update( void )
{
	// テスト
	PrintDebug( _T( "kawashima\n" ) );

	// 焦点距離の更新
	D3DXVECTOR3	positionLookAt;		// 注視点
	pCamera_->GetPositionLookAt( &positionLookAt );
	pArgument_->pEffectParameter_->SetForcus( 2.5f * pCamera_->GetViewZ( positionLookAt ) );

	// 影用カメラ近の更新
	D3DXVECTOR3	vectorLight;		// ライトベクトル
	positionLookAt.y = 0.0f;
	pLight_->GetVector( &vectorLight );
	vectorLight *= -3500.0f;
	pCameraShadowNear_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadowNear_->SetPositionLookAt( positionLookAt );

	// 影用カメラ遠の更新
	pLight_->GetVector( &vectorLight );
	vectorLight *= -10000.0f;
	pCameraShadowFar_->SetPositionCamera( positionLookAt + vectorLight );
	pCameraShadowFar_->SetPositionLookAt( positionLookAt );

	// 影用カメラ点の更新
	const LightPoint*	pLightPoint = nullptr;		// 点光源
	for( int counterLightPoint = 0; counterLightPoint < GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW; ++counterLightPoint )
	{
		pLightPoint = pArgument_->pEffectParameter_->GetLightPointLightness( counterLightPoint );
		if( pLightPoint != nullptr )
		{
			D3DXVECTOR3	positionLightPointCamera;		// 点光源の視点座標
			D3DXVECTOR3	positionLightPointLookAt;		// 点光源の注視点座標
			pLightPoint->GetPosition( &positionLightPointCamera );
			positionLightPointLookAt = positionLightPointCamera;
			positionLightPointLookAt.y -= 1000.0f;
			ppCameraShadowPoint_[ counterLightPoint ]->SetPositionCamera( positionLightPointCamera );
			ppCameraShadowPoint_[ counterLightPoint ]->SetPositionLookAt( positionLightPointLookAt );
		}
	}

	//	設定された更新クラスへ
	(this->*fpUpdate)();
}

//==============================================================================
// Brief  : 更新処理1(「Aボタンを押してね」の点滅)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::firstUpdate( void )
{
	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}


	//	「Aボタンを押してね」の点滅処理
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount <= flashingCountHirf)
			pushAKey->AddColorA(-addFlashingAlpha);
		else if(pushAKeyFlashingCount <= flashingCountMax)
			pushAKey->AddColorA(addFlashingAlpha);
		else
			pushAKeyFlashingCount = 0;
	}

	//	デモへ移行
	/*ManagerSceneMain::demoCount++;
	//if(ManagerSceneMain::demoCount == ManagerSceneMain::demoCountMax / 2)
	if(ManagerSceneMain::demoCount == 60)
	{
		ManagerSceneMain::demoCount = 0;

		//	次の更新関数へ
		fpUpdate = &SceneTitle::fadeUpdateDemo;

		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}*/


	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	「Aボタンを押してね」を消して、「演舞開始」と「練習開始」と指オブジェクトを可視化
		pushAKey->SetEnableGraphic(false);
		startTutorial->SetEnableGraphic(true);
		startGame->SetEnableGraphic(true);

		//	wiiリモコンが登録されてる場合は登録しない
		if(pArgument_->pWiiController_->getIsConnectWiimote() == true)
		{
			chooseObject = nullptr;
			finger->SetEnableGraphic(true);
		}

		//	デフォルトの選択肢を「演舞開始」に設定
		chooseObject = startGame;

		//	点滅カウント初期化
		pushAKeyFlashingCount = 0;

		//	音再生
		desideSound->Play();

		//	次の更新関数へ
		fpUpdate = &SceneTitle::secondUpdate;
	}
}
//==============================================================================
// Brief  : 更新処理2(ゲーム開始・チュートリアル開始の選択処理)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::secondUpdate( void )
{
	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}

	//	１フレーム前の登録オブジェクトを保存
	chooseObjectPrev = chooseObject;


	//	wiiリモコンが生成されていれば指の移動
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		finger->SetPosition(IRBuff.x, IRBuff.y, 0.0f);
	}


	//	決定キー押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	選択されている場合
		if(chooseObject != nullptr)
		{
			//	点滅カウント初期化
			pushAKeyFlashingCount = 0;

			//	現在のオブジェクトをA1.0fで表示
			chooseObject->SetColorA(1.0f);

			//	音再生
			desideSound->Play();

			//	次の更新関数へ
			fpUpdate = &SceneTitle::fadeUpdate;

			if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
			{
				pArgument_->pFade_->FadeOut( 20 );
			}
		}
	}

	//	矢印キーで移動
	if(pArgument_->pVirtualController_->IsTrigger(VC_LEFT))
	{
		//	点滅カウント初期化
		pushAKeyFlashingCount = 0;

		//	音再生
		selectSound->Play();

		//	wiiリモコン接続時は違う処理
		if(chooseObject == nullptr)
		{
			//	方向キーに変更
			chooseFlag = false;

			//	オブジェクト登録
			chooseObject = startGame;
		}
		else
		{
			//	現在のオブジェクトをA1.0fで表示
			chooseObject->SetColorA(1.0f);

			//	選択肢移動
			(chooseObject == startGame) ? chooseObject = startTutorial : chooseObject = startGame;
		}
	}
	if(pArgument_->pVirtualController_->IsTrigger(VC_RIGHT))
	{
		//	点滅カウント初期化
		pushAKeyFlashingCount = 0;

		//	音再生
		selectSound->Play();

		//	wiiリモコン接続時は違う処理
		if(chooseObject == nullptr)
		{
			//	方向キーに変更
			chooseFlag = false;

			//	オブジェクト登録
			chooseObject = startTutorial;
		}
		else
		{
			//	現在のオブジェクトをA1.0fで表示
			chooseObject->SetColorA(1.0f);

			//	選択肢移動
			(chooseObject == startGame) ? chooseObject = startTutorial : chooseObject = startGame;
		}
	}


	//	wiiリモコンが生成されていれば指の移動
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		//	「演舞開始」に当たってれば
		if((IRBuff.x <= (startGame->GetPositionX() + (startGame->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (startGame->GetPositionX() - (startGame->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (startGame->GetPositionY() + (startGame->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (startGame->GetPositionY() - (startGame->GetScaleY() * 0.5f))) )
		{
			//	点滅オブジェクトとして登録
			chooseObject = startGame;

			//	選択方法をIRに変更
			chooseFlag = true;
		}
		//	「練習開始」に当たってれば
		else if((IRBuff.x <= (startTutorial->GetPositionX() + (startTutorial->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (startTutorial->GetPositionX() - (startTutorial->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (startTutorial->GetPositionY() + (startTutorial->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (startTutorial->GetPositionY() - (startTutorial->GetScaleY() * 0.5f))) )
		{
			//	点滅オブジェクトとして登録
			chooseObject = startTutorial;

			//	選択方法をIRに変更
			chooseFlag = true;
		}
		//	何にも当たってなければ
		else
		{
			//	選択方法がIRの場合のみ
			if(chooseFlag == true)
			{
				if(chooseObject != nullptr)
				{
					//	登録解除
					chooseObject->SetColorA(1.0f);
					chooseObject = nullptr;
					pushAKeyFlashingCount = 0;
				}
			}
		}
	}


	//	選択項目の点滅処理
	if(chooseObject != nullptr)
	{
		chooseObject->SetScaleX(startXX_NormalSizeX * 1.3f);
		chooseObject->SetScaleY(startXX_NormalSizeY * 1.3f);

		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount <= flashingCountHirf)
			chooseObject->AddColorA(-addFlashingAlpha);
		else if(pushAKeyFlashingCount <= flashingCountMax)
			chooseObject->AddColorA(addFlashingAlpha);
		else
			pushAKeyFlashingCount = 0;


		//	１フレーム前の選択オブジェクトのサイズを変更
		if((chooseObjectPrev != nullptr) &&
			(chooseObjectPrev != chooseObject))
		{
			chooseObjectPrev->SetScaleX(startXX_NormalSizeX);
			chooseObjectPrev->SetScaleY(startXX_NormalSizeY);
		}
	}
	else
	{
		startGame->SetScaleX(startXX_NormalSizeX);
		startGame->SetScaleY(startXX_NormalSizeY);

		startTutorial->SetScaleX(startXX_NormalSizeX);
		startTutorial->SetScaleY(startXX_NormalSizeY);
	}
}
//==============================================================================
// Brief  : 更新処理(決定キー押された後の遷移処理)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::fadeUpdate( void )
{
	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		if(chooseObject == startGame)
			SetSceneNext( ManagerSceneMain::TYPE_GAME );
		else
			SetSceneNext( ManagerSceneMain::TYPE_GAME );//ほんとはチュートリアル

		SetIsEnd( true );
	}
}
void SceneTitle::fadeUpdateDemo( void )
{
	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );//ほんとはチュートリアル
		ManagerSceneMain::demoFlag = true;

		SetIsEnd( true );
	}
}

//==============================================================================
// Brief  : 再接続要求時用の更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::reConnectWiimoteUpdate(void)
{
	//	再接続要求
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiimote();

	//	wiiリモコンが再接続が終了したら
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == false)
	{
		//	更新関数設定
		fpUpdate = fpUpdatePrev;
		fpUpdatePrev = nullptr;

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( true );

		//	描画やめる
		reConnectWiimote->SetEnableGraphic(false);

		//	音再生
		desideSound->Play();

		//	描画再開
		if(fpUpdate == &SceneTitle::secondUpdate)
			finger->SetEnableGraphic(true);
	}

	//	Objectクラスの更新が止まってるから、ここで更新処理
	reConnectWiimote->Update();
}
//==============================================================================
// Brief  : 再接続要求時用の更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::reConnectWiiboardUpdate(void)
{
	//	再接続要求
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiiboard();

	//	wiiリモコンが再接続が終了したら
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == false)
	{
		//	更新関数設定
		fpUpdate = fpUpdatePrev;
		fpUpdatePrev = nullptr;

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( true );

		//	描画やめる
		reConnectWiiboard->SetEnableGraphic(false);

		//	音再生
		desideSound->Play();

		//	描画再開
		if(fpUpdate == &SceneTitle::secondUpdate)
			finger->SetEnableGraphic(true);
	}

	//	Objectクラスの更新が止まってるから、ここで更新処理
	reConnectWiiboard->Update();
}
//==============================================================================
// Brief  : wiiリモコンのロストチェック処理
// Return : bool								: true = 問題無し false = ロスト
// Arg    : void								: なし
//==============================================================================
bool SceneTitle::wiiLostCheck(void)
{
	//	wiiリモコンが再接続要求をした場合
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == true)
	{
		//	更新関数設定
		fpUpdatePrev = fpUpdate;
		fpUpdate = &SceneTitle::reConnectWiimoteUpdate;

		//	再接続要求オブジェクト可視化
		reConnectWiimote->SetEnableGraphic(true);

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( false );

		//	音再生
		cancelSound->Play();

		return false;
	}

	//	wiiボードが再接続要求をした場合
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == true)
	{
		//	更新関数設定
		fpUpdatePrev = fpUpdate;
		fpUpdate = &SceneTitle::reConnectWiiboardUpdate;

		//	再接続要求オブジェクト可視化
		reConnectWiiboard->SetEnableGraphic(true);

		//	Objectの更新を止める
		pArgument_->pUpdate_->SetIsEnable( false );

		//	音再生
		cancelSound->Play();

		return false;
	}

	return true;
}
