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
#include "../framework/develop/DebugMeasure.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/VirtualController.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/light/LightDirection.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/Window.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerPoint.h"
#include "../system/ManagerFireworks.h"
#include "../system/ManagerTarget.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"
#include "../system/fire/Fire.h"

// テスト
#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../object/ObjectMesh.h"
#include "../object/ObjectSky.h"
#include "../object/ObjectBillboard.h"
#include "../object/ObjectScore.h"
#include "../object/ObjectSkinMesh.h"
#include "../object/ObjectWaterwheel.h"

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
	pLight_ = nullptr;
	pObjectSky_ = nullptr;
	pauseFrame = nullptr;
	stringScore = nullptr;
	stringReturn = nullptr;
	stringStop = nullptr;
	stringRetry = nullptr;
	stringNext = nullptr;

	playerArm = nullptr;
	managerFireworks = nullptr;
	managerTarget = nullptr;

	pObjectSkinMesh_[0] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[2] = nullptr;

	waterWheel[0] = nullptr;
	waterWheel[1] = nullptr;
	waterWheel[2] = nullptr;

	house[0] = nullptr;
	house[1] = nullptr;
	house[2] = nullptr;

	bridge = nullptr;

	fpUpdate = nullptr;
	finger = nullptr;
	reConnectWiimote = nullptr;
	reConnectWiiboard = nullptr;
	chooseObject = nullptr;
	pushChooseObjectFlashingCount = 0;
	chooseFlag = false;

	launchCount = 0;
	launchFlag = false;

	for(int count = 0;count < FIREWORKS_MAX;count++)
		fireworksTable[count] = -1;

	for(int count = 0;count < TARGET_MAX;count++)
		targetTable[count] = -1;

	fireworksTableIndex = 0;
	targetTableIndex = 0;

	cameraState = CAMERA_STATE_FRONT;
	targetAppearCount = 0;

	// SceneGame2のクラス内初期化
	InitializeSelf2();
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
		10000.0f,
		D3DXVECTOR3( 0.0f, 200.0f, -2400.0f ),
		D3DXVECTOR3( 0.0f, 200.0f, 0.0f ),
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
	result = pLight_->Initialize( D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( 0.0f, -0.7f, 0.7f ) );
	if( result != 0 )
	{
		return result;
	}
	pArgument->pEffectParameter_->SetLightDirection( GraphicMain::LIGHT_DIRECTIONAL_GENERAL, pLight_ );




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
	fpUpdate = &SceneGame::normalUpdate;

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
	//	オブジェクトの生成開始
	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;


	// スカイドームの生成
	Effect*	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "common/sky.jpg" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 5000.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pTexture );


	//	仮のフィールド
	pModel = pArgument_->pModel_->Get( _T( "testfield_01_low.x" ) );
	pEffect = pArgument_->pEffect_->Get( _T( "Model.fx" ) );
	field = new ObjectModel();
	field->Initialize(0);
	field->CreateGraphic( 0, pModel,pArgument->pEffectParameter_, pEffect);
	field->SetScale(5.0f, 5.0f, 5.0f);
	field->AddPositionY(-300.0f);

	//	水車オブジェクトの生成
	waterWheel[0] = new ObjectWaterwheel;
	waterWheel[0]->Initialize(
		D3DXVECTOR3(-2500.0f, 200.0f, -300.0f),
		DEG_TO_RAD(90),
		0.001f,
		pArgument);

	waterWheel[1] = new ObjectWaterwheel;
	waterWheel[1]->Initialize(
		D3DXVECTOR3(-2500.0f, 200.0f, -900.0f),
		DEG_TO_RAD(90),
		0.001f,
		pArgument);

	waterWheel[2] = new ObjectWaterwheel;
	waterWheel[2]->Initialize(
		D3DXVECTOR3(-2500.0f, 200.0f, -1500.0f),
		DEG_TO_RAD(90),
		0.001f,
		pArgument);


	//	家生成
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "head.x" ) );
	house[0] = new ObjectModelMaterial();
	house[0]->Initialize(0);
	house[0]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	house[0]->SetPosition(3200.0f, 100.0f, -700.0f);
	house[0]->SetScale(30.0f, 30.0f, 30.0f);
	
	house[1] = new ObjectModelMaterial();
	house[1]->Initialize(0);
	house[1]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	house[1]->SetPosition(3200.0f, 100.0f, -1300.0f);
	house[1]->SetScale(30.0f, 30.0f, 30.0f);
	
	house[2] = new ObjectModelMaterial();
	house[2]->Initialize(0);
	house[2]->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	house[2]->SetPosition(3200.0f, 100.0f, -1900.0f);
	house[2]->SetScale(30.0f, 30.0f, 30.0f);

	//	橋生成
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "bridge.x" ) );
	bridge = new ObjectModelMaterial();
	bridge->Initialize(0);
	bridge->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);
	bridge->SetPosition(0.0f, 1000.0f, 2300.0f);
	bridge->SetScale(350.0f, 350.0f, 350.0f);
	bridge->SetRotationY(DEG_TO_RAD(90));
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
	Effect*		pEffectPoint = nullptr;			// ポイントエフェクト
	Texture*	pTexturePoint = nullptr;		// ポイントテクスチャ
	pEffectPoint = pArgument->pEffect_->Get( _T( "Point.fx" ) );
	pTexturePoint = pArgument->pTexture_->Get( _T( "common/effect000.jpg" ) );
	managerPoint = new ManagerPoint();
	if( managerPoint == nullptr )
	{
		//return 1;
	}
	result = managerPoint->Initialize( 10000, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		//return result;
	}

	//	火花オブジェクトのステート初期化
	Fire::InitializeState();

	//	花火管理オブジェクト生成
	managerFireworks = new ManagerFireworks;
	managerFireworks->Initialize(managerPoint);

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


	//	プレイヤーオブジェクト
	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument_->pModel_->Get( _T( "kuma.x" ) );
	player = new ObjectModelMaterial();
	player->Initialize(0);
	player->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);

	pEffect = pArgument->pEffect_->Get( _T( "ModelMat.fx" ) );
	pModel = pArgument_->pModel_->Get( _T( "arm_r.x" ) );
	playerArm = new ObjectModelMaterial();
	playerArm->Initialize(0);
	playerArm->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect);

	playerArm->SetPositionY(150.0f);
	playerArm->SetPositionX(30.0f);
	playerArm->SetPositionZ(-2000.0f);
	playerArm->SetScale(3.0f, 3.0f, 3.0f);

	player->SetPositionY(100.0f);
	player->SetPositionZ(-2000.0f);
	player->SetScale(2.0f, 2.0f, 2.0f);


	// スキンメッシュの生成
	Effect*	pEffectSkinMesh = nullptr;		// エフェクト
	Model*	pModelSkinMesh = nullptr;		// モデル
	pEffectSkinMesh = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pModelSkinMesh = pArgument_->pModel_->Get( _T( "test.model" ) );
	pObjectSkinMesh_[0] = new ObjectSkinMesh();
	pObjectSkinMesh_[0]->Initialize( 0, 1 );
	pObjectSkinMesh_[0]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh );
	pObjectSkinMesh_[0]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[0]->SetPosition( 300.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[1] = new ObjectSkinMesh();
	pObjectSkinMesh_[1]->Initialize( 0, 1 );
	pObjectSkinMesh_[1]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh );
	pObjectSkinMesh_[1]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[1]->SetPosition( 0.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[2] = new ObjectSkinMesh();
	pObjectSkinMesh_[2]->Initialize( 0, 1 );
	pObjectSkinMesh_[2]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh );
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
	pTexture = pArgument_->pTexture_->Get( _T( "common/number.png" ) );

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
