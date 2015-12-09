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
#include "../framework/camera/ManagerCamera.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/develop/DebugMeasure.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/VirtualController.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/ManagerLight.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/Model.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Window.h"
#include "../system/EffectParameter.h"
#include "../system/point/ManagerPoint.h"
#include "../system/ManagerFireworks.h"
#include "../system/ManagerTarget.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"
#include "../system/fire/Fire.h"
#include "../object/ObjectRiver.h"

// テスト
#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectSky.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectScore.h"
#include "../system/gage/gage.h"
#include "../object/ObjectSkinMesh.h"
#include "../object/ObjectWaterwheel.h"
#include "../system/player/Player.h"

#include "../framework/system/ManagerDraw.h"
#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/polygon/PolygonPoint.h"

#include "../framework/radianTable/radianTable.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define RANDOM(value) (float)((rand() % value) - (rand() % value))
#define SQUARE(_value) (_value * _value)

//******************************************************************************
// 静的変数
//******************************************************************************
//	○○　文字のサイズ
static const float stringXX_NormalSizeX = 400.0f;
static const float stringXX_NormalSizeY = 120.0f;

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::InitializeSelf( void )
{
	// メンバ変数の初期化
	pCamera_ = nullptr;
	pCameraShadowNear_ = nullptr;
	pCameraShadowFar_ = nullptr;
	pCameraShadowPoint_ = nullptr;
	pLight_ = nullptr;

	//	ゲームUI関係
	//----------------------------------------------------------
	stringScore = nullptr;
	score = nullptr;
	gage = nullptr;
	pauseFrame = nullptr;
	stringReturn = nullptr;
	stringStop = nullptr;
	stringRetry = nullptr;
	stringNext = nullptr;
	reConnectWiimote = nullptr;
	reConnectWiiboard = nullptr;
	calibrationWiimote = nullptr;
	finger = nullptr;
	chooseObject = nullptr;
	chooseObjectPrev = nullptr;

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

	grasses = nullptr;

	markers = nullptr;

	player = nullptr;

	managerPoint = nullptr;
	managerFireworks = nullptr;
	managerTarget = nullptr;

	pObjectSkinMesh_[0] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[2] = nullptr;

	launchFlag = false;
	launchCount = 0;

	for(int count = 0;count < FIREWORKS_MAX;count++)
		fireworksTable[count] = -1;

	for(int count = 0;count < TARGET_MAX;count++)
		targetTable[count] = -1;

	fireworksTableIndex = 0;
	targetTableIndex = 0;
	//----------------------------------------------------------


	cameraState = CAMERA_STATE_FRONT;
	fpUpdate = nullptr;



	// SceneGame2のクラス内初期化
	InitializeSelf2();



	targetAppearCount = 0;
	buffWiiAccel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	buffWiiRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	//	自作ラジアンテーブル
	CRadianTable::Init();

	// カメラの生成
	pCamera_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_GENERAL );
	pCamera_->Set(
		D3DX_PI / 4.0f,
		pArgument->pWindow_->GetWidth(),
		pArgument->pWindow_->GetHeight(),
		0.1f,
		20000.0f,
		D3DXVECTOR3( 1000.0f, 590.0f, 5760.0f ),
		D3DXVECTOR3( 760.0f, -20.0f, 3380.0f ),
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f )
		);

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
	pCameraShadowPoint_ = pArgument->pCamera_->GetCamera( GraphicMain::CAMERA_SHADOW_POINT );
	pCameraShadowPoint_->Set( D3DX_PI / 4.0f, pArgument->pWindow_->GetWidth(), pArgument->pWindow_->GetHeight(), 0.1f, 10000.0f,
		D3DXVECTOR3( 260.0f, 1000.0f, 3540.0f ), D3DXVECTOR3( 260.0f, 0.0f, 3540.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ), false );

	// 環境光の設定
	pArgument->pEffectParameter_->SetColorAmbient( 0.1f, 0.15f, 0.2f );




	//	ステージオブジェクトの生成
	InitializeStage(pArgument);

	//	３Dオブジェクトの生成
	Initialize3DObject(pArgument);

	//	UI関連の初期化
	InitializeUI(pArgument);



	//	デフォルトの選択肢を「再開」に設定
	chooseObject = stringReturn;

	//	wiiリモコンが登録されてる場合は登録しない
	if(pArgument_->pWiiController_->getIsConnectWiimote() == true)
		chooseObject = nullptr;

	// SceneGame2の初期化
	result = Initialize2();
	if( result != 0 )
	{
		return result;
	}

	//	更新関数設定
	fpUpdate = &SceneGame::calibrationUpdate;

	// フェードイン
	pArgument->pFade_->FadeIn( 20 );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : ステージ関連の読み込み処理
// Return : void								: なし
// Arg    : SceneArgumentMain* pArgument		: シーン引数
//==============================================================================
void SceneGame::InitializeStage(SceneArgumentMain* pArgument)
{
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

	// 草の生成
	Texture*	pTextureGrass = nullptr;		// テクスチャ
	Effect*		pEffectGrass = nullptr;			// エフェクト
	pTextureGrass = pArgument->pTexture_->Get( _T( "common/grass.png" ) );
	pEffectGrass = pArgument->pEffect_->Get( "Billboard.fx" );
	grasses = new ObjectBillboard[ COUNT_GRASS ];
	for( int counterGrass = 0; counterGrass < COUNT_GRASS; ++counterGrass )
	{
		float	positionX;		// X座標
		float	positionZ;		// Z座標
		positionX = -2300.0f + 2000.0f * (static_cast< float >( rand() ) / RAND_MAX - 0.5f);
		positionZ = 6800.0f + 1000.0f * (static_cast< float >( rand() ) / RAND_MAX - 0.5f);
		grasses[ counterGrass ].Initialize( 0 );
		grasses[ counterGrass ].CreateGraphic( 0, pArgument->pEffectParameter_, pEffectGrass, pTextureGrass );
		grasses[ counterGrass ].SetPosition( positionX, 0.5f * pTextureGrass->height_, positionZ );
	}

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
}

//==============================================================================
// Brief  : その他３Dオブジェクトの読み込み処理
// Return : void								: なし
// Arg    : SceneArgumentMain* pArgument		: シーン引数
//==============================================================================
void SceneGame::Initialize3DObject(SceneArgumentMain* pArgument)
{
	//	オブジェクトの生成開始
	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;
	int		result;		// 実行結果


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

	// ライトの生成
	managerFireworks->setManagerLight(pArgument->pLight_);

	//	ターゲット管理オブジェクト生成
	Effect*		pEffectTarget = pArgument->pEffect_->Get( _T( "Billboard.fx" ) );
	Texture*	pTextureCross = pArgument->pTexture_->Get( _T( "game/targetCross.png" ) );
	Texture*	pTextureArrow = pArgument->pTexture_->Get( _T( "game/targetArrow.png" ) );
	Texture*	pTextureCircle = pArgument->pTexture_->Get( _T( "game/targetCircle.png" ) );
	managerTarget = new ManagerTarget;
	managerTarget->Initialize(
		pArgument->pDevice_,
		pArgument->pEffectParameter_,
		pEffectTarget,
		pTextureCross,
		pTextureArrow,
		pTextureCircle
		);
	managerTarget->ReadTargetScriptFromFile("data/script/script_test.txt");


	//	プレイヤーオブジェクト(Posはカメラとの相対座標)
	player = new Player;
	player->Initialize(
		//D3DXVECTOR3(0.0f, 150.0f, -2000.0f),
		D3DXVECTOR3(0.0f, -100.0f, 400.0f),
		pArgument);


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
}

//==============================================================================
// Brief  : UI関連の読み込み処理
// Return : void								: なし
// Arg    : SceneArgumentMain* pArgument		: シーン引数
//==============================================================================
void SceneGame::InitializeUI(SceneArgumentMain* pArgument)
{
	//	オブジェクトの生成開始
	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;


	//	「スコア」文字オブジェクト生成
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "game/stringScore.png" ) );

	stringScore = new Object2D;
	stringScore->Initialize(0);

	stringScore->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringScore->SetScale(150.0f, 80.0f, 0.0f);
	stringScore->SetPosition(-550.0f, 300.0f, 0.0f);



	//	スコアオブジェクト生成
	pTexture = pArgument_->pTexture_->Get( _T( "common/number_white.png" ) );

	score = new ObjectScore;
	score->Initialize(0, 10);

	score->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	score->SetSizeX(32.0f);
	score->SetSizeY(32.0f);
	score->SetPosX(-470.0f);
	score->SetPosY(300.0f);

	score->SetScoreFuture(123456789);



	//	ゲージオブジェクト生成
	gage = new Gage();
	gage->Initialize(
		pArgument_->pDevice_,
		pArgument_->pEffectParameter_,
		pEffect,
		pArgument_->pEffect_->Get( _T( "Polygon2DAdd.fx" ) ),
		pArgument_->pTexture_->Get(_T("game/gageBar.png")),
		pArgument_->pTexture_->Get(_T("game/gageBase.png")),
		pArgument_->pTexture_->Get(_T("game/effect.png")),
		pArgument_->pTexture_->Get( _T( "common/number.png" ) ));

	gage->setPosition(-540.0f, -270.0f, 0.0f);


	//	ポーズ時用背景オブジェクト生成
	pTexture = pArgument_->pTexture_->Get( _T( "common/fade.jpg" ) );

	pauseFrame = new Object2D;
	pauseFrame->Initialize(0);

	pauseFrame->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	pauseFrame->SetColor(1.0f, 1.0f, 1.0f,0.5f);
	pauseFrame->SetScale(1280.0f * 0.7f, 720.0f * 0.7f, 0.0f);
	pauseFrame->SetEnableGraphic(false);



	//	「再開」文字オブジェクトの生成
	pTexture = pArgument_->pTexture_->Get( _T( "game/pause/stringReturn.png" ) );

	stringReturn = new Object2D;
	stringReturn->Initialize(0);

	stringReturn->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringReturn->SetPosition(0.0f, 200.0f, 0.0f);
	stringReturn->SetScale(stringXX_NormalSizeX, stringXX_NormalSizeY, 0.0f);
	stringReturn->SetEnableGraphic(false);



	//	「中止」文字オブジェクトの生成
	pTexture = pArgument_->pTexture_->Get( _T( "game/pause/stringStop.png" ) );

	stringStop = new Object2D;
	stringStop->Initialize(0);

	stringStop->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringStop->SetPosition(0.0f, 0.0f, 0.0f);
	stringStop->SetScale(stringXX_NormalSizeX, stringXX_NormalSizeY, 0.0f);
	stringStop->SetEnableGraphic(false);



	//	「初めから」文字オブジェクトの生成
	pTexture = pArgument_->pTexture_->Get( _T( "game/pause/stringRetry.png" ) );

	stringRetry = new Object2D;
	stringRetry->Initialize(0);

	stringRetry->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringRetry->SetPosition(0.0f, -200.0f, 0.0f);
	stringRetry->SetScale(stringXX_NormalSizeX, stringXX_NormalSizeY, 0.0f);
	stringRetry->SetEnableGraphic(false);


	//	ゲーム開始前のキャリブレーションお願いオブジェクト
	pTexture = pArgument_->pTexture_->Get( _T( "game/pause/stringRetry.png" ) );

	calibrationWiimote = new Object2D;
	calibrationWiimote->Initialize(0);

	calibrationWiimote->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);
	//calibrationWiimote->SetEnableGraphic(false);


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
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int SceneGame::Finalize( void )
{
	// SceneGame2の終了
	int		result;		// 実行結果
	result = Finalize2();
	if( result != 0 )
	{
		return result;
	}

	delete stringScore;
	stringScore = nullptr;

	delete score;
	score = nullptr;

	delete gage;
	gage = nullptr;

	delete pauseFrame;
	pauseFrame = nullptr;

	delete stringReturn;
	stringReturn = nullptr;

	delete stringStop;
	stringStop = nullptr;

	delete stringRetry;
	stringRetry = nullptr;

	delete finger;
	finger = nullptr;

	delete calibrationWiimote;
	calibrationWiimote = nullptr;

	delete reConnectWiimote;
	reConnectWiimote = nullptr;

	delete reConnectWiiboard;
	reConnectWiiboard = nullptr;

	delete managerPoint;
	managerPoint = nullptr;

	Fire::FinalizeState();

	delete managerFireworks;
	managerFireworks = nullptr;

	delete managerTarget;
	managerTarget = nullptr;

	delete player;
	player = nullptr;

	delete pObjectSkinMesh_[2];
	delete pObjectSkinMesh_[1];
	delete pObjectSkinMesh_[0];
	pObjectSkinMesh_[2] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[0] = nullptr;

	// 場所目印オブジェクトの開放
	delete[] markers;
	markers = nullptr;

	// 草オブジェクトの開放
	delete[] grasses;
	grasses = nullptr;

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
	if( pCameraShadowPoint_ != nullptr )
	{
		pCameraShadowPoint_->SetState( nullptr );
		pCameraShadowPoint_ = nullptr;
	}

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

	// カメラの開放
	if( pCamera_ != nullptr )
	{
		pCamera_->SetState( nullptr );
		pCamera_ = nullptr;
	}

	// 基本クラスの処理
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
