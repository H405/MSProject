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
#include "../system/EffectParameter.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

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
#include "../system/fire/Fire.h"

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



	//	タイトル用ステージ・３Dオブジェクト関係
	//----------------------------------------------------------
	pObjectSky_ = nullptr;
	field = nullptr;
	bridge = nullptr;
	managerPoint = nullptr;
	managerFireworks = nullptr;
	pObjectSkinMesh_[0] = nullptr;
	pObjectSkinMesh_[1] = nullptr;
	pObjectSkinMesh_[2] = nullptr;

	launchFlag = false;
	launchCount = 0;

	for(int count = 0;count < FIREWORKS_MAX;count++)
		fireworksTable[count] = -1;

	fireworksTableIndex = 0;
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
		1280,
		720,
		0.1f,
		10000.0f,
		D3DXVECTOR3( 0.0f, 120.0f, -2400.0f ),
		D3DXVECTOR3( 0.0f, 720.0f, 0.0f ),
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );

	// ライトの生成
	pLight_ = pArgument->pLight_->GetLightDirection();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	pLight_->Set( D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXCOLOR( 0.5f, 0.5f, 0.5f, 1.0f ), D3DXVECTOR3( 0.0f, -0.7f, 0.7f ) );

	//	オブジェクトの生成開始
	Effect*		pEffect = nullptr;
	Effect*		pEffectReflect = nullptr;
	Effect*		pEffectShadow = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;


	// スカイドームの生成
	Effect*	pEffectSky = pArgument->pEffect_->Get( _T( "Sky.fx" ) );
	Effect*	pEffectSkyReflect = pArgument->pEffect_->Get( _T( "SkyReflect.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "common/sky.jpg" ) );
	pObjectSky_ = new ObjectSky();
	pObjectSky_->Initialize( 0, pArgument->pDevice_, 32, 32, 5000.0f, 1.0f, 1.0f );
	pObjectSky_->CreateGraphic( 0, pArgument->pEffectParameter_, pEffectSky, pEffectSkyReflect, pTexture );



	//	仮のフィールド
	pModel = pArgument_->pModel_->Get( _T( "testfield_01_low.x" ) );
	pEffect = pArgument_->pEffect_->Get( _T( "Model.fx" ) );
	pEffectReflect = pArgument_->pEffect_->Get( _T( "ModelReflect.fx" ) );
	pEffectShadow = pArgument_->pEffect_->Get( _T( "ModelShadow.fx" ) );
	field = new ObjectModel();
	field->Initialize(0);
	field->CreateGraphic( 0, pModel,pArgument->pEffectParameter_, pEffect, pEffectReflect, pEffectShadow );
	field->SetScale(5.0f, 5.0f, 5.0f);
	field->AddPositionY(-300.0f);



	//	橋生成
	pEffect = pArgument->pEffect_->Get( _T( "ModelMaterial.fx" ) );
	pEffectReflect = pArgument->pEffect_->Get( _T( "ModelMaterialReflect.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "bridge.x" ) );
	bridge = new ObjectModelMaterial();
	bridge->Initialize(0);
	bridge->CreateGraphic( 0, pModel, pArgument->pEffectParameter_, pEffect, pEffectReflect);
	bridge->SetPosition(0.0f, 1000.0f, 2300.0f);
	bridge->SetScale(350.0f, 350.0f, 350.0f);
	bridge->SetRotationY(DEG_TO_RAD(90));








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
	result = managerPoint->Initialize( 10000, pArgument->pDevice_, pArgument->pEffectParameter_, pEffectPoint, pEffectPointReflect, pTexturePoint->pTexture_ );
	if( result != 0 )
	{
		//return result;
	}

	//	火花オブジェクトのステート初期化
	Fire::InitializeState();

	//	花火管理オブジェクト生成
	managerFireworks = new ManagerFireworks;
	managerFireworks->Initialize(managerPoint);




	// スキンメッシュの生成
	Effect*	pEffectSkinMesh = nullptr;				// エフェクト
	Effect*	pEffectSkinMeshReflect = nullptr;		// エフェクト
	Model*	pModelSkinMesh = nullptr;				// モデル
	pEffectSkinMesh = pArgument->pEffect_->Get( _T( "SkinMesh.fx" ) );
	pEffectSkinMeshReflect = pArgument->pEffect_->Get( _T( "SkinMeshReflect.fx" ) );
	pModelSkinMesh = pArgument_->pModel_->Get( _T( "test.model" ) );
	pObjectSkinMesh_[0] = new ObjectSkinMesh();
	pObjectSkinMesh_[0]->Initialize( 0, 1 );
	pObjectSkinMesh_[0]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh, pEffectSkinMeshReflect );
	pObjectSkinMesh_[0]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[0]->SetPosition( 300.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[1] = new ObjectSkinMesh();
	pObjectSkinMesh_[1]->Initialize( 0, 1 );
	pObjectSkinMesh_[1]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh, pEffectSkinMeshReflect );
	pObjectSkinMesh_[1]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[1]->SetPosition( 0.0f, 100.0f, 0.0f );

	pObjectSkinMesh_[2] = new ObjectSkinMesh();
	pObjectSkinMesh_[2]->Initialize( 0, 1 );
	pObjectSkinMesh_[2]->CreateGraphic( 0, pModelSkinMesh, pArgument->pEffectParameter_, pEffectSkinMesh, pEffectSkinMeshReflect );
	pObjectSkinMesh_[2]->SetTableMotion( 0, pArgument->pMotion_->Get( _T( "test.motion" ) ) );
	pObjectSkinMesh_[2]->SetPosition( -300.0f, 100.0f, 0.0f );




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
	pTexture = pArgument_->pTexture_->Get( _T( "title/pressAKey.png" ) );
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
	pTexture = pArgument_->pTexture_->Get( _T( "title/startGame.png" ) );

	startGame = new Object2D;
	startGame->Initialize(0);

	startGame->CreateGraphic(
	0,
	pArgument_->pEffectParameter_,
	pEffect,
	pTexture);

	startGame->SetPosition(-300.0f, -100.0f, 0.0f);
	startGame->SetScaleX(startXX_NormalSizeX);
	startGame->SetScaleY(startXX_NormalSizeY);
	startGame->SetEnableGraphic(false);


	//	「練習開始」文字オブジェクトの生成
	pTexture = pArgument_->pTexture_->Get( _T( "title/startTutorial.png" ) );

	startTutorial = new Object2D;
	startTutorial->Initialize(0);

	startTutorial->CreateGraphic(
	0,
	pArgument_->pEffectParameter_,
	pEffect,
	pTexture);

	startTutorial->SetPosition(300.0f, -100.0f, 0.0f);
	startTutorial->SetScaleX(startXX_NormalSizeX);
	startTutorial->SetScaleY(startXX_NormalSizeY);
	startTutorial->SetEnableGraphic(false);



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

	delete pObjectSkinMesh_[2];
	pObjectSkinMesh_[2] = nullptr;

	delete pObjectSkinMesh_[1];
	pObjectSkinMesh_[1] = nullptr;

	delete pObjectSkinMesh_[0];
	pObjectSkinMesh_[0] = nullptr;

	delete managerFireworks;
	managerFireworks = nullptr;

	Fire::FinalizeState();

	delete managerPoint;
	managerPoint = nullptr;

	delete bridge;
	bridge = nullptr;

	delete field;
	field = nullptr;

	delete pObjectSky_;
	pObjectSky_ = nullptr;

	// ライトの開放
	if( pLight_ != nullptr )
	{
		pLight_->Release();
		pLight_ = nullptr;
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

		return false;
	}

	return true;
}
