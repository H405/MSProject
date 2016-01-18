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
#include "../system/camera/CameraStateSpline.h"
#include "../system/EffectParameter.h"
#include "../system/point/ManagerPoint.h"
#include "../system/ManagerFireworks.h"
#include "../system/ManagerTarget.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"
#include "../system/fire/Fire.h"
#include "../object/ObjectRiver.h"
#include "../framework/resource/ManagerSound.h"
#include "../framework/resource/Sound.h"

// テスト
#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectGrass.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectSky.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectScore.h"
#include "../system/gage/gage.h"
#include "../system/combo/combo.h"
#include "../object/ObjectSkinMesh.h"
#include "../object/ObjectWaterwheel.h"
#include "../system/player/Player.h"

#include "../framework/system/ManagerDraw.h"
#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/polygon/PolygonPoint.h"

#include "../framework/radianTable/radianTable.h"
#include "../system/fireworksUI/fireworksUI.h"

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
static const float stringXX_NormalSizeX = 384.0f;
static const float stringXX_NormalSizeY = 128.0f;

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
	ppCameraShadowPoint_ = nullptr;
	pLight_ = nullptr;
	wiiContoroller = nullptr;

	//	ゲームUI関係
	//----------------------------------------------------------
	stringDemo = nullptr;
	stringManual = nullptr;
	stringScore = nullptr;
	score = nullptr;
	gage = nullptr;
	combo = nullptr;
	fireworksUI = nullptr;
	pauseFrame = nullptr;
	stringReturn = nullptr;
	stringStop = nullptr;
	stringRetry = nullptr;
	stringNext = nullptr;
	reConnectWiimote = nullptr;
	reConnectWiiboard = nullptr;
	calibrationWiimote = nullptr;
	calibrationWiimoteIllust = nullptr;
	finger = nullptr;
	chooseObject = nullptr;
	chooseObjectPrev = nullptr;

	pushChooseObjectFlashingCount = 0;
	chooseFlag = false;

	colorState = COLOR_STATE_R;
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

//	pObjectSkinMesh_[0] = nullptr;
//	pObjectSkinMesh_[1] = nullptr;
//	pObjectSkinMesh_[2] = nullptr;

	launchFlag = false;
	launchCount = 0;

	for(int count = 0;count < FIREWORKS_MAX;count++)
		fireworksTable[count] = -1;

	for(int count = 0;count < TARGET_MAX;count++)
		targetTable[count] = -1;

	fireworksTableIndex = 0;
	targetTableIndex = 0;
	//----------------------------------------------------------


	//	音関連
	//----------------------------------------------------------
	bgmSound = nullptr;
	desideSound = nullptr;
	selectSound = nullptr;
	cancelSound = nullptr;
	//----------------------------------------------------------


	cameraState = CAMERA_STATE_FRONT;
	fpUpdate = nullptr;



	// SceneGame2のクラス内初期化
	InitializeSelf2();



	targetAppearCount = 0;
	buffDiffWiiAccel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	buffDiffWiiRot   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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


	//	アドレス保存
	wiiContoroller = pArgument_->pWiiController_;


	//	ステージオブジェクトの生成
	InitializeStage(pArgument);

	//	３Dオブジェクトの生成
	Initialize3DObject(pArgument);

	//	UI関連の初期化
	InitializeUI(pArgument);



	//	デフォルトの選択肢を「再開」に設定
	chooseObject = stringReturn;

	//	wiiリモコンが登録されてる場合は登録しない
	if(wiiContoroller->getIsConnectWiimote() == true)
	{
		chooseObject = nullptr;
		pArgument_->pWiiController_->startGame();
	}

	// SceneGame2の初期化
	result = Initialize2();
	if( result != 0 )
	{
		return result;
	}



	//	音関連の読み込み
	bgmSound = pArgument_->pSound_->Get("bgm/game.wav");
	bgmSound->Play(-1);

	desideSound = pArgument_->pSound_->Get("se/deside.wav");
	selectSound = pArgument_->pSound_->Get("se/select.wav");
	cancelSound = pArgument_->pSound_->Get("se/cancel.wav");





	// 視点の初期位置を設定
	D3DXVECTOR3	positionCamera;		// 視点座標
	D3DXVECTOR3	positionLookAt;		// 視点座標
	pStateCameraPrevious_->GetPositionCamera( 0, 0, &positionCamera );
	pStateCameraPrevious_->GetPositionLookAt( 0, 0, &positionLookAt );
	pCamera_->SetPositionCamera( positionCamera );
	pCamera_->SetPositionLookAt( positionLookAt );


	fireAutoManulFlag = true;

	ManagerSceneMain::reTutorialFlag = false;

	//	更新関数設定
	if(ManagerSceneMain::demoFlag == false)
	{
		if(ManagerSceneMain::tutorialFlag == false)
		{
			fpUpdate = &SceneGame::UpdatePreviousGame;//::calibrationUpdate;
		}
		else
		{
/*			fpUpdate = &SceneGame::calibrationUpdate;

			calibrationWiimote->SetEnableGraphic(true);
			calibrationWiimoteIllust->SetEnableGraphic(true);
			combo->setStartFlag(true);

			fireworksUI->SetEnableGraphic(true);
			stringScore->SetEnableGraphic(true);
			score->SetEnableGraphic(true);
			gage->SetEnableGraphic(true);
*/
			fpUpdate = &SceneGame::UpdatePreviousGame;

#ifdef FIRE_KING
			fpUpdate = &SceneGame::calibrationUpdate;

			calibrationWiimote->SetEnableGraphic(true);
			calibrationWiimoteIllust->SetEnableGraphic(true);
			combo->setStartFlag(true);

			fireworksUI->SetEnableGraphic(true);
			stringScore->SetEnableGraphic(true);
			score->SetEnableGraphic(true);
			gage->SetEnableGraphic(true);

			pCamera_->SetPositionCamera(1680.0,   120.0,  1270.0);
			pCamera_->SetPositionLookAt(1640.0,   390.0, -1185.0);
#endif
		}
	}
	else
	{
		fpUpdate = &SceneGame::demoUpdate;
		calibrationWiimote->SetEnableGraphic(false);
		calibrationWiimoteIllust->SetEnableGraphic(false);
		combo->setStartFlag(true);

		fireworksUI->SetEnableGraphic(true);
		stringScore->SetEnableGraphic(true);
		score->SetEnableGraphic(true);
		gage->SetEnableGraphic(true);

		stringDemo->SetEnableGraphic(true);

		pCamera_->SetPositionCamera(1680.0,   120.0,  1270.0);
		pCamera_->SetPositionLookAt(1640.0,   390.0, -1185.0);
	}





	//	プレゼン直前の悪あがき
	for(int count = 0;count < TARGET_MAX;count++)
		autoLaunchTable[count] = false;

	selfLaunchFlag = false;
	//	プレゼン直前の悪あがき






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

	// 地形の生成
	Model*	pModelField = nullptr;					// モデル
	Effect*	pEffectFieldGeneral = nullptr;			// 通常描画エフェクト
	Effect*	pEffectFieldReflect = nullptr;			// 反射エフェクト
	Effect*	pEffectFieldShadow = nullptr;			// 影エフェクト
	Effect*	pEffectFieldParaboloid = nullptr;		// 放物変換エフェクト
	pModelField = pArgument->pModel_->Get( _T( "Stage_ver103.x" ) );
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
	pEffectBridgeGeneral = pArgument->pEffect_->Get( "Model.fx" );
	pEffectBridgeReflect = pArgument->pEffect_->Get( "ModelReflect.fx" );
	pEffectBridgeShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectBridgeParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	bridge = new ObjectModel();
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
	houses[ 1 ].SetPosition( -3840.0f, 0.0f, 2330.0f );
	houses[ 1 ].SetRotationY( DEG_TO_RAD( 257.0f ) );
	houses[ 2 ].SetPosition( -3230.0f, 0.0f, 660.0f );
	houses[ 2 ].SetRotationY( DEG_TO_RAD( 242.0f ) );
	houses[ 3 ].SetPosition( -1860.0f, 0.0f, -700.0f );
	houses[ 3 ].SetRotationY( DEG_TO_RAD( 211.0f ) );
	houses[ 4 ].SetPosition( -1810.0f, 0.0f, 3230.0f );
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
	pModelGate = pArgument->pModel_->Get( _T( "torii_002.x" ) );
	pEffectGateGeneral = pArgument->pEffect_->Get( "ModelMaterial.fx" );
	pEffectGateReflect = pArgument->pEffect_->Get( "ModelMaterialReflect.fx" );
	pEffectGateShadow = pArgument->pEffect_->Get( "ModelShadow.fx" );
	pEffectGateParaboloid = pArgument->pEffect_->Get( "ModelParaboloid.fx" );
	gate = new ObjectModelMaterial();
	gate->Initialize( 0 );
	gate->CreateGraphic( 0, pModelGate, pArgument->pEffectParameter_, pEffectGateGeneral, pEffectGateReflect, pEffectGateShadow, pEffectGateParaboloid );
	gate->SetPosition( 5870.0f, 0.0f, -400.0f );
	gate->SetRotationY( DEG_TO_RAD( 90 ) );
	gate->SetScale( 55.0f, 55.0f, 55.0f );

	// 草の生成
	Texture*	pTextureGrass = nullptr;		// テクスチャ
	Effect*		pEffectGrass = nullptr;			// エフェクト
	pTextureGrass = pArgument->pTexture_->Get( _T( "common/grass.png" ) );
	pEffectGrass = pArgument->pEffect_->Get( "Grass.fx" );
	grasses = new ObjectGrass[ COUNT_GRASS ];
	for( int counterGrass = 0; counterGrass < COUNT_GRASS; ++counterGrass )
	{
		float	positionX;		// X座標
		float	positionZ;		// Z座標
		positionX = -2300.0f + 2000.0f * (static_cast< float >( rand() ) / RAND_MAX - 0.5f);
		positionZ = 6800.0f + 1000.0f * (static_cast< float >( rand() ) / RAND_MAX - 0.5f);
		grasses[ counterGrass ].Initialize( 0 );
		grasses[ counterGrass ].CreateGraphic( -1, pArgument->pEffectParameter_, pEffectGrass, pTextureGrass );
		grasses[ counterGrass ].SetPosition( positionX, 0.0f, positionZ );
	}

	// 場所の目印オブジェクトの生成
	Model*	pModelMarker = nullptr;					// モデル
	Motion*	pMotionMarker = nullptr;				// モーション
	Effect*	pEffectMarkerGeneral = nullptr;			// 通常描画エフェクト
	Effect*	pEffectMarkerReflect = nullptr;			// 反射エフェクト
	Effect*	pEffectMarkerShadow = nullptr;			// 影エフェクト
	Effect*	pEffectMarkerParaboloid = nullptr;		// 放物変換エフェクト
	pModelMarker = pArgument->pModel_->Get( _T( "back_dancer.model" ) );
	pMotionMarker = pArgument->pMotion_->Get( _T( "back_dancer.motion" ) );
	pEffectMarkerGeneral = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectMarkerReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pEffectMarkerShadow = pArgument->pEffect_->Get( _T( "SkinMeshShadow.fx" ) );
	pEffectMarkerParaboloid = pArgument->pEffect_->Get( _T( "SkinMeshParaboloid.fx" ) );
	markers = new ObjectSkinMesh[ 4 ];
	for( int counterMarker = 0; counterMarker < 4; ++counterMarker )
	{
		markers[ counterMarker ].Initialize( 0, 1 );
		markers[ counterMarker ].CreateGraphic( 0, pModelMarker, pArgument->pEffectParameter_,
			pEffectMarkerGeneral, pEffectMarkerReflect, pEffectMarkerShadow, pEffectMarkerParaboloid );
		markers[ counterMarker ].SetTableMotion( 0, pMotionMarker );
	}
	markers[ 0 ].SetPosition( 620.0f, 0.0f, 4550.0f );
	markers[ 0 ].SetRotationY( 0.0f );
	markers[ 1 ].SetPosition( -1505.0f, 0.0f, 625.0f );
	markers[ 1 ].SetRotationY( 134.0f );
	markers[ 2 ].SetPosition( 1680.0f, 0.0f, 600.0f );
	markers[ 2 ].SetRotationY( 0.0f );
	markers[ 3 ].SetPosition( 5400.0f, 0.0f, -380.0f );
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
	result = managerPoint->Initialize( 256000, 17, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pEffectPointReflect, pTexturePoint->pTexture_ );
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

	autoFadeTable[2];
	autoFadeTable[0] = -1;
	autoFadeTable[1] = -1;
	autoFadeTableMax = 0;
	autoFadeTableNum = 0;
	autoFadeTableCount = 0;

	if(ManagerSceneMain::demoFlag == false)
		managerTarget->ReadTargetScriptFromFile("data/script/script_test.txt", autoFadeTable, &autoFadeTableMax);


	//	プレイヤーオブジェクト(Posはカメラとの相対座標)
	player = new Player;
	player->Initialize(
		//D3DXVECTOR3(0.0f, 150.0f, -2000.0f),
		D3DXVECTOR3(0.0f, -150.0f, 400.0f),
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

	targetAppearFlag = true;


	//	「マニュアル」文字オブジェクト生成
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "game/manual.png" ) );

	stringManual = new Object2D;
	stringManual->Initialize(0);

	stringManual->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringManual->SetScale(192.0f, 64.0f, 0.0f);
	stringManual->SetPosition(-500.0f, 332.0f, 0.0f);

	stringManual->SetEnableGraphic(false);


	//	「デモ」文字オブジェクト生成
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "game/demoPlay.png" ) );

	stringDemo = new Object2D;
	stringDemo->Initialize(0);

	stringDemo->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringDemo->SetScale(192.0f, 64.0f, 0.0f);
	stringDemo->SetPosition(-500.0f, 332.0f, 0.0f);

	stringDemo->SetEnableGraphic(false);


	//	「スコア」文字オブジェクト生成
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

	stringScore = new Object2D;
	stringScore->Initialize(0);

	stringScore->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringScore->SetScale(128.0f, 32.0f, 0.0f);
	stringScore->SetPosition(272.0f, 332.0f, 0.0f);

	stringScore->SetScaleTexture(4.0f, 16.0f);
	stringScore->SetPositionTexture(0.0f, 0.0f);


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
	score->SetPosX(332.0f);
	score->SetPosY(332.0f);

	score->SetScoreFuture(0);
	score->setAddScore(10);


	//	コンボオブジェクト生成
	combo = new Combo;
	combo->Initialize(
		pArgument_->pDevice_,
		pArgument_->pEffectParameter_,
		pEffect,
		pArgument_->pTexture_->Get( _T( "game/sya.png" )),
		pArgument_->pTexture_->Get( _T( "common/font_edge.png" )),
		pArgument_->pTexture_->Get( _T( "common/numberEdge.png" )));
	combo->setPosition(192.0f, -286.0f, 0.0f);
	combo->setColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	combo->firstUpdate();
	combo->setStartFlag(false);


	//	花火用UI生成
	fireworksUI = new FireworksUI;
	fireworksUI->Initialize(
		pArgument_->pDevice_,
		pArgument_->pEffectParameter_,
		pEffect,
		pArgument_->pTexture_->Get( _T( "game/ui3.png" )));
	fireworksUI->setPosition(595.61084f, -314.89725f, 0.0f);


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
	pTexture = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

	stringReturn = new Object2D;
	stringReturn->Initialize(0);

	stringReturn->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringReturn->SetPosition(0.0f, 176.0f, 0.0f);
	stringReturn->SetScale(stringXX_NormalSizeX, stringXX_NormalSizeY, 0.0f);
	stringReturn->SetEnableGraphic(false);

	stringReturn->SetScaleTexture(4.0f, 16.0f);
	stringReturn->SetPositionTexture(0.0f, 1.0f / 16.0f);



	//	「中止」文字オブジェクトの生成
	pTexture = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

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

	stringStop->SetScaleTexture(4.0f, 16.0f);
	stringStop->SetPositionTexture(1.0f / 4.0f * 2.0f, 1.0f / 16.0f);


	//	「初めから」文字オブジェクトの生成
	pTexture = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

	stringRetry = new Object2D;
	stringRetry->Initialize(0);

	stringRetry->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	stringRetry->SetPosition(0.0f, -176.0f, 0.0f);
	stringRetry->SetScale(stringXX_NormalSizeX, stringXX_NormalSizeY, 0.0f);
	stringRetry->SetEnableGraphic(false);

	stringRetry->SetScaleTexture(4.0f, 16.0f);
	stringRetry->SetPositionTexture(1.0f / 4.0f, 0.0f);



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

		finger->SetScale(150.0f, 150.0f, 0.1f);
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


	//	ゲーム開始前のキャリブレーションお願いイラスト
	pTexture = pArgument_->pTexture_->Get( _T( "common/tatie.png" ) );
	calibrationWiimoteIllust = new Object2D;
	calibrationWiimoteIllust->Initialize(0);

	calibrationWiimoteIllust->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);
	calibrationWiimoteIllust->SetEnableGraphic(false);


	//	ゲーム開始前のキャリブレーションお願いオブジェクト
	pTexture = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

	calibrationWiimote = new Object2D;
	calibrationWiimote->Initialize(0);

	calibrationWiimote->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);
	calibrationWiimote->SetEnableGraphic(false);

	calibrationWiimote->SetScale(stringXX_NormalSizeX * 2.0f, stringXX_NormalSizeY * 2.0f, 0.0f);
	calibrationWiimote->SetScaleTexture(4.0f, 16.0f);
	calibrationWiimote->SetPositionTexture(1.0f / 4.0f, 1.0f / 16.0f);


	fireworksUI->SetEnableGraphic(false);
	stringScore->SetEnableGraphic(false);
	score->SetEnableGraphic(false);
	gage->SetEnableGraphic(false);

	tutorialFadeCount = 0;
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
	bgmSound->Stop();
	desideSound->Stop();
	selectSound->Stop();
	cancelSound->Stop();

	// SceneGame2の終了
	int		result;		// 実行結果
	result = Finalize2();
	if( result != 0 )
	{
		return result;
	}

	delete stringDemo;
	stringDemo = nullptr;

	delete stringManual;
	stringManual = nullptr;

	delete stringScore;
	stringScore = nullptr;

	delete score;
	score = nullptr;

	delete combo;
	combo = nullptr;

	delete fireworksUI;
	fireworksUI = nullptr;

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

	delete calibrationWiimoteIllust;
	calibrationWiimoteIllust = nullptr;

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
/*
	delete pObjectSkinMesh_[2];
	delete pObjectSkinMesh_[1];
	delete pObjectSkinMesh_[0];
	pObjectSkinMesh_[2] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[0] = nullptr;
*/
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

	// カメラの開放
	if( pCamera_ != nullptr )
	{
		pCamera_->SetState( nullptr );
		pCamera_ = nullptr;
	}

	if(pArgument_->pWiiController_->getIsConnectWiimote() == true)
		pArgument_->pWiiController_->endGame();

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
