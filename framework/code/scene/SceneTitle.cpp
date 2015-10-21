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
static const int flashingCountHirf = 20;
static const int flashingCountMax = 40;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
SceneTitle::SceneTitle( void ) : SceneMain(),
pushAKeyFlashingCount(-1),
pushChooseObjectFlashingCount(-1),
chooseObject(nullptr)
{
	// クラス内の初期化処理
	InitializeSelf();
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

	//	タイトルロゴ
	titleLogo = new Object2D;
	titleLogo->Initialize(0);

	Effect*		pEffect = nullptr;
	Texture*	pTexture = nullptr;
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

	pushAKey->SetPosition(0.0f, -100.0f, 0.0f);

	//	更新関数セット
	fpUpdate = &SceneTitle::FirstUpdate;

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
	if(startGame != nullptr)
		delete startGame;
	startGame = nullptr;

	if(startTutorial != nullptr)
		delete startTutorial;
	startTutorial = nullptr;

	if(pushAKey != nullptr)
		delete pushAKey;
	pushAKey = nullptr;

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

	//	設定された更新クラスへ
	(this->*fpUpdate)();
}

//==============================================================================
// Brief  : 更新処理1(「Aボタンを押してね」の点滅)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::FirstUpdate( void )
{
	// テスト
	PrintDebug( _T( "タイトル\n" ) );

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

		startGame->SetPosition(-200.0f, -100.0f, 0.0f);

		pTexture = pArgument_->pTexture_->Get( _T( "startTutorial.png" ) );

		startTutorial->CreateGraphic(
		0,
		pArgument_->pEffectParameter_,
		pEffect,
		pTexture);

		startTutorial->SetPosition(200.0f, -100.0f, 0.0f);

		//	デフォルトの選択肢を「演舞開始」に設定
		chooseObject = startGame;

		//	次の更新関数へ
		fpUpdate = &SceneTitle::SecondUpdate;
	}

	//	「Aボタンを押してね」の点滅処理
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			//pushAKey->setColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			//pushAKey->setColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}
//==============================================================================
// Brief  : 更新処理2(ゲーム開始・チュートリアル開始の選択処理)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::SecondUpdate( void )
{
	// テスト
	PrintDebug( _T( "タイトル\n" ) );

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

	//	選択項目の点滅処理
	{
		pushAKeyFlashingCount++;

		if(pushAKeyFlashingCount == flashingCountHirf)
		{
			//chooseObject->setColorA(0.0f);
		}
		if(pushAKeyFlashingCount == flashingCountMax)
		{
			//chooseObject->setColorA(1.0f);

			pushAKeyFlashingCount = 0;
		}
	}
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneTitle::InitializeSelf( void )
{
	// メンバ変数の初期化
}
