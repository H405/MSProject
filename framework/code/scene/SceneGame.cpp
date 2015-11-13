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
//	点滅用カウント数
static const int flashingCountHirf = 20;
static const int flashingCountMax = 40;

//	○○　文字のサイズ
static const float stringXX_NormalSizeX = 400.0f;
static const float stringXX_NormalSizeY = 120.0f;

//	透明値加算値
static const float addFlashingAlpha = 0.02f;

//	打ち上げ間隔
static const int launchCountMax = 120;

static const D3DXVECTOR3 targetAppearPos[CAMERA_STATE_MAX] =
{
	D3DXVECTOR3(0.0f, 0.0f, -2000.0f),
	D3DXVECTOR3(0.0f, 0.0f, -2000.0f),
	D3DXVECTOR3(0.0f, 0.0f, -2000.0f),
	D3DXVECTOR3(0.0f, 0.0f, -2000.0f),
};

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
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int SceneGame::Finalize( void )
{
	delete waterWheel[0];
	delete waterWheel[1];
	delete waterWheel[2];

	waterWheel[0] = nullptr;
	waterWheel[1] = nullptr;
	waterWheel[2] = nullptr;

	delete house[0];
	delete house[1];
	delete house[2];

	house[0] = nullptr;
	house[1] = nullptr;
	house[2] = nullptr;

	delete bridge;
	bridge = nullptr;;

	// スカイドームの開放
	delete pObjectSky_;
	pObjectSky_ = nullptr;

	//	スキンメッシュの解放
	delete pObjectSkinMesh_[0];
	delete pObjectSkinMesh_[1];
	delete pObjectSkinMesh_[2];
	pObjectSkinMesh_[0] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[2] = nullptr;

	// 仮フィールドの開放
	delete field;
	field = nullptr;

	//	テストオブジェクトの解放
	delete playerArm;
	playerArm = nullptr;

	//	ターゲット管理クラスの解放
	delete managerTarget;
	managerTarget = nullptr;

	//	花火管理クラスの解放
	delete managerFireworks;
	managerFireworks = nullptr;

	// ポイントスプライト管理クラスの開放
	delete managerPoint;
	managerPoint = nullptr;

	// ポーズ用背景の開放
	delete pauseFrame;
	pauseFrame = nullptr;

	//	スコアオブジェクトの解放
	delete score;
	score = nullptr;

	// 「スコア」文字オブジェクトの開放
	delete stringScore;
	stringScore = nullptr;

	// 「再開」文字オブジェクトの開放
	delete stringReturn;
	stringReturn = nullptr;

	// 「中止」文字オブジェクトの開放
	delete stringStop;
	stringStop = nullptr;

	// 「初めから」文字オブジェクトの開放
	delete stringRetry;
	stringRetry = nullptr;

	// 指オブジェクトの開放
	delete finger;
	finger = nullptr;

	//	「wiiリモコン再接続要求」オブジェクト解放
	delete reConnectWiimote;
	reConnectWiimote = nullptr;

	//	「wiiボード再接続要求」オブジェクトの解放
	delete reConnectWiiboard;
	reConnectWiiboard = nullptr;

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

	// テスト
	PrintDebug( _T( "ゲームシーン\n" ) );

	//	設定された更新関数へ
	(this->*fpUpdate)();

	//	スクリーンショット撮影
	if(pArgument_->pKeyboard_->IsTrigger(DIK_F2))
		pArgument_->pDraw_->screenShotON();
}
//==============================================================================
// Brief  : 通常更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::normalUpdate(void)
{
	PrintDebug( _T( "normalUpdate\n" ) );

	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	{
		//	花火管理クラスの更新
		MeasureTime("managerFireworksUpdate");
		managerFireworks->Update(fireworksTable, &fireworksTableIndex);
	}


	{
		//	ターゲット管理クラスの更新
		MeasureTime("managerTargetUpdate");
		managerTarget->Update(targetTable, &targetTableIndex);
	}

	{
		// ポイントスプライト管理クラスの更新
		MeasureTime("managerPoint");
		managerPoint->Update();
	}

	//	スコアクラスの更新
	score->Update();

	//	水車の更新
	waterWheel[0]->Update();
	waterWheel[1]->Update();
	waterWheel[2]->Update();


	//for(int count = 0;count < TARGET_MAX;count++)
	//	PrintDebug( _T( "index[%d] = %d\n"), count, targetTable[count] );
	//
	//PrintDebug( _T( "\ntargetTableIndex = %d\n\n"), targetTableIndex );

	//	テスト用ここから
	//---------------------------------------------------------------------------------------------------------
	/*if(launchFlag == false)
	{
		if(pArgument_->pWiiController_->getAccelerationY() >= 2.5f)
		{
			int buff;
			D3DXVECTOR3 buffPos;
			playerArm->GetPosition(&buffPos);

			buff = managerFireworks->Add(
				ManagerFireworks::STATE_NORMAL,
				managerPoint,
				buffPos,
				D3DXVECTOR3(0.1f, 0.1f, 0.0f),
				DEG_TO_RAD(5.0f),
				DEG_TO_RAD(1.0f)
				);
			if(buff != -1)
			{
				fireworksTable[fireworksTableIndex] = buff;
				fireworksTableIndex++;
			}

			launchFlag = true;
		}
	}
	else
	{
		launchCount++;
		if(launchCount >= launchCountMax)
		{
			launchCount = 0;
			launchFlag = false;
		}
	}*/

	if(pArgument_->pKeyboard_->IsTrigger(DIK_A) == true)
	{
		if(fireworksTableIndex < FIREWORKS_MAX)
		{
			int buff;
			D3DXVECTOR3 buffPos;
			playerArm->GetPosition(&buffPos);

			buff = managerFireworks->Add(
				ManagerFireworks::STATE_NORMAL,
				managerPoint,
				buffPos,
				D3DXVECTOR3(0.1f, 0.1f, 0.0f),
				DEG_TO_RAD(5.0f),
				DEG_TO_RAD(1.0f)
				);
			if(buff != -1)
			{
				fireworksTable[fireworksTableIndex] = buff;
				fireworksTableIndex++;
			}
		}
	}

	if(pArgument_->pWiiController_->getPress(WC_PLUS) && pArgument_->pWiiController_->getPress(WC_MINUS))
		pArgument_->pWiiController_->rotReset();


	D3DXVECTOR3 buffRot = pArgument_->pWiiController_->getRot();
	playerArm->SetRotation(DEG_TO_RAD(buffRot.x), DEG_TO_RAD(-buffRot.y), DEG_TO_RAD(buffRot.z));


	/*targetAppearCount++;
	if(targetAppearCount == 50)
	{
		int buff;
		buff = managerTarget->Add(
			D3DXVECTOR3(RANDOM(500), (float)(rand() % 100) + 250.0f, targetAppearPos[cameraState].z)
			);
		if(buff != -1)
		{
			targetTable[targetTableIndex] = buff;
			targetTableIndex++;
		}

		targetAppearCount = 0;
	}*/
	if(pArgument_->pKeyboard_->IsTrigger(DIK_R) == true)
	{
		int buff;
		buff = managerTarget->Add(
			D3DXVECTOR3(40.0f, 300.0f, targetAppearPos[cameraState].z)
			);

		if(buff != -1)
		{
			targetTable[targetTableIndex] = buff;
			targetTableIndex++;
		}
	}
	//---------------------------------------------------------------------------------------------------------
	//	テスト用ここまで

	//	Aボタン押されたら
	if(pArgument_->pWiiController_->getTrigger(WC_A) == true)
	{
		//	ターゲットと花火の当たり判定
		collision_fireworks_target();
	}

	//	ポーズキーが押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		//	更新関数設定
		fpUpdate = &SceneGame::pauseUpdate;

		//	Objectの更新を止める
		updateFlag = false;

		//	描画再開
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);

		if(finger != nullptr)
			finger->SetEnableGraphic(true);
	}
}
//==============================================================================
// Brief  : ポーズ更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::pauseUpdate(void)
{
	PrintDebug( _T( "pauseUpdate\n" ) );

	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	//	wiiリモコンが生成されていれば指の移動
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();
		finger->SetPosition(IRBuff.x, IRBuff.y, 0.0f);
	}

	//	１フレーム前の登録オブジェクトを保存
	chooseObjectPrev = chooseObject;


	//	決定キー押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	選択されている場合
		if(chooseObject != nullptr)
		{
			//	点滅カウント初期化
			pushChooseObjectFlashingCount = 0;

			//	現在のオブジェクトをA1.0fで表示
			chooseObject->SetColorA(1.0f);

			//	再開が押されたら
			if(chooseObject == stringReturn)
			{
				//	更新関数設定
				fpUpdate = &SceneGame::normalUpdate;

				//	Objectの更新を再開
				updateFlag = true;

				//	描画停止
				pauseFrame->SetEnableGraphic(false);
				stringReturn->SetEnableGraphic(false);
				stringStop->SetEnableGraphic(false);
				stringRetry->SetEnableGraphic(false);

				if(finger != nullptr)
					finger->SetEnableGraphic(false);
			}
			else
			{
				//	更新関数設定
				fpUpdate = &SceneGame::pauseFadeUpdate;

				if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
				{
					pArgument_->pFade_->FadeOut( 20 );
				}
			}
		}
	}


	//	矢印キーで移動
	if(pArgument_->pVirtualController_->IsTrigger(VC_UP))
	{
		//	点滅カウント初期化
		pushChooseObjectFlashingCount = 0;

		//	wiiリモコン接続時は違う処理
		if(chooseObject == nullptr)
		{
			//	方向キーに変更
			chooseFlag = false;

			//	オブジェクト登録
			chooseObject = stringReturn;
		}
		else
		{
			//	現在のオブジェクトをA1.0fで表示
			chooseObject->SetColorA(1.0f);

			//	選択肢移動
			if(chooseObject == stringReturn)
				chooseObject = stringRetry;
			else if(chooseObject == stringRetry)
				chooseObject = stringStop;
			else
				chooseObject = stringReturn;
		}
	}
	if(pArgument_->pVirtualController_->IsTrigger(VC_DOWN))
	{
		//	点滅カウント初期化
		pushChooseObjectFlashingCount = 0;

		//	wiiリモコン接続時は違う処理
		if(chooseObject == nullptr)
		{
			//	方向キーに変更
			chooseFlag = false;

			//	オブジェクト登録
			chooseObject = stringRetry;
		}
		else
		{
			//	現在のオブジェクトをA1.0fで表示
			chooseObject->SetColorA(1.0f);

			//	選択肢移動
			if(chooseObject == stringReturn)
				chooseObject = stringStop;
			else if(chooseObject == stringStop)
				chooseObject = stringRetry;
			else
				chooseObject = stringReturn;
		}
	}


	//	wiiリモコンが生成されていれば指の移動
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		//	「再開」に当たってれば
		if((IRBuff.x <= (stringReturn->GetPositionX() + (stringReturn->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringReturn->GetPositionX() - (stringReturn->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringReturn->GetPositionY() + (stringReturn->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringReturn->GetPositionY() - (stringReturn->GetScaleY() * 0.5f))) )
		{
			//	点滅オブジェクトとして登録
			chooseObject = stringReturn;

			//	選択方法をIRに変更
			chooseFlag = true;
		}
		//	「中止」に当たってれば
		else if((IRBuff.x <= (stringStop->GetPositionX() + (stringStop->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringStop->GetPositionX() - (stringStop->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringStop->GetPositionY() + (stringStop->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringStop->GetPositionY() - (stringStop->GetScaleY() * 0.5f))) )
		{
			//	点滅オブジェクトとして登録
			chooseObject = stringStop;

			//	選択方法をIRに変更
			chooseFlag = true;
		}
		//	「初めから」に当たってれば
		else if((IRBuff.x <= (stringRetry->GetPositionX() + (stringRetry->GetScaleX() * 0.5f))) &&
			(IRBuff.x >= (stringRetry->GetPositionX() - (stringRetry->GetScaleX() * 0.5f))) &&
			(IRBuff.y <= (stringRetry->GetPositionY() + (stringRetry->GetScaleY() * 0.5f))) &&
			(IRBuff.y >= (stringRetry->GetPositionY() - (stringRetry->GetScaleY() * 0.5f))) )
		{
			//	点滅オブジェクトとして登録
			chooseObject = stringRetry;

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
					pushChooseObjectFlashingCount = 0;
				}
			}
		}
	}


	//	PAUSEキーが押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_PAUSE))
	{
		//	更新関数設定
		fpUpdate = &SceneGame::normalUpdate;

		//	Objectの更新を再開
		updateFlag = true;

		//	描画停止
		pauseFrame->SetEnableGraphic(false);
		stringReturn->SetEnableGraphic(false);
		stringStop->SetEnableGraphic(false);
		stringRetry->SetEnableGraphic(false);

		if(finger != nullptr)
			finger->SetEnableGraphic(false);
	}


	//	選択項目の点滅処理
	if(chooseObject != nullptr)
	{
		chooseObject->SetScaleX(stringXX_NormalSizeX * 1.3f);
		chooseObject->SetScaleY(stringXX_NormalSizeY * 1.3f);

		pushChooseObjectFlashingCount++;

		if(pushChooseObjectFlashingCount <= flashingCountHirf)
			chooseObject->AddColorA(-addFlashingAlpha);
		else if(pushChooseObjectFlashingCount <= flashingCountMax)
			chooseObject->AddColorA(addFlashingAlpha);
		else
			pushChooseObjectFlashingCount = 0;

		//	１フレーム前の選択オブジェクトのサイズを変更
		if((chooseObjectPrev != nullptr) &&
			(chooseObjectPrev != chooseObject))
		{
			chooseObjectPrev->SetScaleX(stringXX_NormalSizeX);
			chooseObjectPrev->SetScaleY(stringXX_NormalSizeY);
		}
	}
	else
	{
		stringReturn->SetScaleX(stringXX_NormalSizeX);
		stringReturn->SetScaleY(stringXX_NormalSizeY);

		stringStop->SetScaleX(stringXX_NormalSizeX);
		stringStop->SetScaleY(stringXX_NormalSizeY);

		stringRetry->SetScaleX(stringXX_NormalSizeX);
		stringRetry->SetScaleY(stringXX_NormalSizeY);
	}



	//	Objectクラスの更新が止まってるから、ここで更新処理
	if(finger != nullptr)
		finger->Update();

	stringRetry->Update();
	stringReturn->Update();
	stringStop->Update();
}
//==============================================================================
// Brief  : ポーズ更新処理(フェード用)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::pauseFadeUpdate(void)
{
	//	接続切れ確認
	if(wiiLostCheck() == false)
		return;

	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		if(chooseObject == stringStop)
			SetSceneNext( ManagerSceneMain::TYPE_TITLE );
		else
			SetSceneNext( ManagerSceneMain::TYPE_GAME );

		SetIsEnd( true );
	}
}
//==============================================================================
// Brief  : 再接続要求時用の更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::reConnectWiimoteUpdate(void)
{
	//	再接続要求
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiimote();

	//	wiiリモコンが再接続が終了したら
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == false)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::pauseUpdate;

		//	Objectの更新を止める
		updateFlag = false;

		//	描画やめる
		reConnectWiimote->SetEnableGraphic(false);

		//	描画再開
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);
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
void SceneGame::reConnectWiiboardUpdate(void)
{
	//	再接続要求
	if(pArgument_->pVirtualController_->IsTrigger(VC_DESIDE))
		pArgument_->pWiiController_->reConnectWiiboard();

	//	wiiリモコンが再接続が終了したら
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == false)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::pauseUpdate;

		//	Objectの更新を止める
		updateFlag = false;

		//	描画やめる
		reConnectWiiboard->SetEnableGraphic(false);

		//	描画再開
		pauseFrame->SetEnableGraphic(true);
		stringReturn->SetEnableGraphic(true);
		stringStop->SetEnableGraphic(true);
		stringRetry->SetEnableGraphic(true);
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
bool SceneGame::wiiLostCheck(void)
{
	//	wiiリモコンが再接続要求をした場合
	if(pArgument_->pWiiController_->getIsReConnectWiimote() == true)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::reConnectWiimoteUpdate;

		//	再接続要求オブジェクト可視化
		reConnectWiimote->SetEnableGraphic(true);

		//	Objectの更新を止める
		updateFlag = false;

		return false;
	}

	//	wiiボードが再接続要求をした場合
	if(pArgument_->pWiiController_->getIsReConnectWiiboard() == true)
	{
		//	更新関数設定
		fpUpdate = &SceneGame::reConnectWiiboardUpdate;

		//	再接続要求オブジェクト可視化
		reConnectWiiboard->SetEnableGraphic(true);

		//	Objectの更新を止める
		updateFlag = false;

		return false;
	}

	return true;
}
//==============================================================================
// Brief  : 花火とターゲットの当たり判定処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::collision_fireworks_target()
{
	float hitPosLength = 0.0f;

	//	存在する花火の数分ループ
	for(int fireworksCount = 0;fireworksCount < fireworksTableIndex;fireworksCount++)
	{
		//	花火の情報取得
		Fireworks* buffFireworks = managerFireworks->getFireworks(fireworksTable[fireworksCount]);
		if(buffFireworks->IsBurnFlag())
			continue;

		//	花火の位置情報取得
		D3DXVECTOR3 buffFireworksPos = buffFireworks->getPosition();

		//	存在するターゲットの数分ループ
		for(int targetCount = 0;targetCount < targetTableIndex;targetCount++)
		{
			//	ターゲットの位置情報取得
			Target* buffTarget = managerTarget->getTarget(targetTable[targetCount]);
			D3DXVECTOR3 buffTargetPos = buffTarget->getPosition();

			//	ターゲットのサイズ取得
			float buffTargetSize = (managerTarget->getTarget(targetCount)->getScale() * 0.5f);

			//	当たり判定
			if(hitCheckPointCircle(buffFireworksPos, buffTargetPos, buffTargetSize, &hitPosLength) == true)
			{
				//	破裂
				buffFireworks->burn(buffTargetSize * buffTargetSize, hitPosLength);

				//	ターゲット消去
				buffTarget->Dissappear();

				//	次の花火との当たり判定へ移行
				break;
			}
		}
	}
}

//==============================================================================
// Brief  : 点と円の当たり判定処理
// Return : bool								: 当たったか当たってないか
// Arg    : D3DXVECTOR3							: 点の位置
// Arg    : D3DXVECTOR3							: 円の位置
// Arg    : D3DXVECTOR3							: 当たってると判定する最大距離
// Arg    : float								: 円の中心から点への距離
//==============================================================================
bool SceneGame::hitCheckPointCircle(D3DXVECTOR3 _pointPos, D3DXVECTOR3 _circlePos, float _hitCheckOffset, float* _hitPosLength)
{
	//	位置関係計算
	float lengthX = _pointPos.x - _circlePos.x;
	float lengthY = _pointPos.y - _circlePos.y;

	float returnLength = SQUARE(lengthX) + SQUARE(lengthY);

	//	判定
	if(returnLength <= (_hitCheckOffset * _hitCheckOffset))
	{
		//	どのくらい離れたかを保存
		*_hitPosLength = returnLength;

		return true;
	}

	return false;
}
