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
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/graphic/Material.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/LightDirection.h"
#include "../framework/object/Object.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../framework/system/Fade.h"
#include "../system/EffectParameter.h"
#include "../system/ManagerSceneMain.h"
#include "../system/SceneArgumentMain.h"

#include "../graphic/graphic/Graphic2D.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/Object3D.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectMesh.h"
#include "../framework/polygon/PolygonMesh.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

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

	titleLogo = nullptr;
	startGame = nullptr;
	startTutorial = nullptr;
	pushAKey = nullptr;
	finger = nullptr;

	player = nullptr;

	chooseObject = nullptr;

	pushAKeyFlashingCount = -1;
	pushChooseObjectFlashingCount = -1;

	chooseFlag = false;

	fpUpdate = nullptr;
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
	pCamera_ = new CameraObject();
	if( pCamera_ == nullptr )
	{
		return 1;
	}
	result = pCamera_->Initialize(
		D3DX_PI / 4.0f,
		1280,
		720,
		0.1f,
		1000.0f,
		D3DXVECTOR3( 0.0f, 30.0f, -100.0f ),
		D3DXVECTOR3( 0.0f, 30.0f, 10.0f ),
		D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
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

	//	オブジェクトの生成開始
	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
	Model*		pModel = nullptr;

	//	プレイヤー生成
	pEffect = pArgument_->pEffect_->Get( _T( "Model.fx" ) );
	pModel = pArgument->pModel_->Get( _T( "head.x" ) );

	player = new ObjectModel;
	player->Initialize(0);
	player->CreateGraphic(
		0,
		pModel,
		pArgument->pEffectParameter_,
		pEffect );

	player->SetPositionZ(-30.0f);

	//	家の生成
	pModel = pArgument->pModel_->Get( _T( "kuma.x" ) );

	for(int count = 0;count < 3;count++)
	{
		house[count] = new ObjectModel;
		house[count]->Initialize(0);
		house[count]->CreateGraphic(
			0,
			pModel,
			pArgument->pEffectParameter_,
			pEffect);
	}

	house[0]->SetPositionX(-50.0f);
	house[2]->SetPositionX(50.0f);

	house[0]->SetPositionZ(100.0f);
	house[1]->SetPositionZ(100.0f);
	house[2]->SetPositionZ(100.0f);

	//	仮のフィールド
	pTexture = pArgument_->pTexture_->Get( _T( "titlelogo.png" ) );
	field = new ObjectMesh();
	field->Initialize( 0, pArgument->pDevice_, 10, 20, 40.0f, 40.0f, 1.0f, 1.0f );
	field->CreateGraphic( 0, pArgument->pEffectParameter_, pEffect, pTexture );


	//	タイトルロゴ
	titleLogo = new Object2D;
	titleLogo->Initialize(0);
	pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pTexture = pArgument_->pTexture_->Get( _T( "titlelogo.png" ) );

	titleLogo->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	titleLogo->SetPosition(350.0f, 100.0f, 0.0f);


	//	Aボタンを押してね
	pTexture = pArgument_->pTexture_->Get( _T( "pressAKey.png" ) );
	pushAKey = new Object2D;
	pushAKey->Initialize(0);

	pushAKey->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

	pushAKey->SetPosition(0.0f, -200.0f, 0.0f);

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
	if(finger != nullptr)
		delete finger;
	finger = nullptr;

	if(field != nullptr)
		delete field;
	field = nullptr;

	if(house[0] != nullptr)
		delete house[0];
	house[0] = nullptr;

	if(house[1] != nullptr)
		delete house[1];
	house[1] = nullptr;

	if(house[2] != nullptr)
		delete house[2];
	house[2] = nullptr;

	if(player != nullptr)
		delete player;
	player = nullptr;

	if(startGame != nullptr)
		delete startGame;
	startGame = nullptr;

	if(startTutorial != nullptr)
		delete startTutorial;
	startTutorial = nullptr;

	if(pushAKey != nullptr)
		delete pushAKey;
	pushAKey = nullptr;

	if(titleLogo != nullptr)
		delete titleLogo;
	titleLogo = nullptr;

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
	PrintDebug( _T( "タイトル\n" ) );

	//	カメラ更新
	pCamera_->Update();

	//	wiiリモコンが生成されていれば指の移動
	if(finger != nullptr)
	{
		D3DXVECTOR2 IRBuff = pArgument_->pWiiController_->getIRScreen();

		finger->SetPosition(IRBuff.x, IRBuff.y, 0.0f);
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
	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}

	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	「Aボタンを押してね」を消して、「演舞開始」と「練習開始」をそれぞれ生成
		delete pushAKey;
		pushAKey = nullptr;

		startGame = new Object2D;
		startGame->Initialize(0);

		startTutorial = new Object2D;
		startTutorial->Initialize(0);

		Effect*		pEffect = nullptr;
		Texture*	pTexture = nullptr;
		pEffect = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
		pTexture = pArgument_->pTexture_->Get( _T( "startGame.png" ) );

		startGame->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		startGame->SetPosition(-300.0f, -100.0f, 0.0f);
		startGame->SetScaleX(startXX_NormalSizeX);
		startGame->SetScaleY(startXX_NormalSizeY);




		pTexture = pArgument_->pTexture_->Get( _T( "startTutorial.png" ) );

		startTutorial->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		startTutorial->SetPosition(300.0f, -100.0f, 0.0f);
		startTutorial->SetScaleX(startXX_NormalSizeX);
		startTutorial->SetScaleY(startXX_NormalSizeY);



		//	wiiリモコンが接続されていれば
		//	指の初期化
		if(pArgument_->pWiiController_->getIsConnect() == true)
		{
			pTexture = pArgument_->pTexture_->Get( _T( "finger.png" ) );
			finger = new Object2D;
			finger->Initialize(0);

			finger->CreateGraphic(
			0,
			pArgument_->pEffectParameter_,
			pEffect,
			pTexture);

			finger->SetScale(50.0f, 50.0f, 0.1f);

			//	IRで選択に変更
			chooseFlag = true;
		}


		//	デフォルトの選択肢を「演舞開始」に設定
		chooseObject = startGame;

		//	wiiリモコンが登録されてる場合は登録しない
		if(pArgument_->pWiiController_->getIsConnect() == true)
			chooseObject = nullptr;

		//	点滅カウント初期化
		pushAKeyFlashingCount = 0;

		//	次の更新関数へ
		fpUpdate = &SceneTitle::secondUpdate;
	}

	//	「Aボタンを押してね」の点滅処理
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			pushAKey->SetColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			pushAKey->SetColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}
//==============================================================================
// Brief  : 更新処理2(ゲーム開始・チュートリアル開始の選択処理)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::secondUpdate( void )
{
	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}

	//	１フレーム前の登録オブジェクトを保存
	chooseObjectPrev = chooseObject;

	//	決定キー押されたら
	if( pArgument_->pVirtualController_->IsTrigger(VC_DESIDE) )
	{
		//	点滅カウント初期化
		pushAKeyFlashingCount = 0;

		//	現在のオブジェクトをA1.0fで表示
		chooseObject->SetColorA(1.0f);

		//	次の更新関数へ
		(chooseObject == startGame) ? fpUpdate = &SceneTitle::thirdUpdate : fpUpdate = &SceneTitle::forthUpdate;

		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
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
				//	登録解除
				chooseObject = nullptr;
				pushAKeyFlashingCount = 0;
			}
		}
	}


	//	選択項目の点滅処理
	if(chooseObject != nullptr)
	{
		chooseObject->SetScaleX(startXX_NormalSizeX * 1.3f);
		chooseObject->SetScaleY(startXX_NormalSizeY * 1.3f);

		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			chooseObject->SetColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			chooseObject->SetColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}

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
// Brief  : 更新処理3(決定キー押された後の点滅処理-ゲームへ遷移)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::thirdUpdate( void )
{
	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}

	//	選択項目の点滅処理
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			chooseObject->SetColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			chooseObject->SetColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}
//==============================================================================
// Brief  : 更新処理4(決定キー押された後の点滅処理-チュートリアルへ遷移)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::forthUpdate( void )
{
	// シーン遷移
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		//SetSceneNext( ManagerSceneMain::TYPE_TUTORIAL );
		SetSceneNext( ManagerSceneMain::TYPE_GAME );
		SetIsEnd( true );
	}

	//	選択項目の点滅処理
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			chooseObject->SetColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			chooseObject->SetColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}