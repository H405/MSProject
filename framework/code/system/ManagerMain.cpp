//==============================================================================
//
// File   : ManagerMain.cpp
// Brief  : メインプログラム管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <tchar.h>
#include "ManagerMain.h"
#include "ManagerSceneMain.h"
#include "SceneArgumentMain.h"
#include "WindowMain.h"
#include "../framework/camera/CameraStateDebug.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/graphic/Graphic.h"
#include "../framework/input/DirectInput.h"
#include "../framework/input/CWiiController.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/InputMouse.h"
#include "../framework/input/InputPad.h"
#include "../framework/input/VirtualController.h"
#include "../framework/object/Object.h"
#include "../framework/polygon/Polygon2D.h"
#include "../framework/polygon/Polygon3D.h"
#include "../framework/render/DirectDevice.h"
#include "../framework/render/RenderPass.h"
#include "../framework/render/RenderTarget.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/system/Fade.h"
#include "../framework/system/ManagerDraw.h"
#include "../framework/system/ManagerUpdate.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/ObjectScreen.h"
#include "../system/EffectParameter.h"

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
ManagerMain::ManagerMain( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerMain::~ManagerMain( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
// Arg    : int typeShow						: 表示の種類
//==============================================================================
int ManagerMain::Initialize( HINSTANCE instanceHandle, int typeShow )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Manager::Initialize( instanceHandle, typeShow );
	if( result != 0 )
	{
		return result;
	}

	// ウィンドウの生成
	HWND	windowHandle;		// ウィンドウハンドル
	pWindow_ = new WindowMain();
	if( pWindow_ == nullptr )
	{
		return 1;
	}
	result = pWindow_->Initialize( instanceHandle, typeShow, 1280, 720, _T( "Framework" ), _T( "WindowClass" ) );
	if( result != 0 )
	{
		return result;
	}
	windowHandle = pWindow_->GetWindowHandle();

	// Direct3Dデバイスの生成
	IDirect3DDevice9*	pDevice = nullptr;			// Direct3Dデバイス
	bool				isWindowMode = true;		// ウィンドウモードフラグ
#ifdef _DEBUG
	isWindowMode = true;
#endif
	pDevice_ = new DirectDevice();
	if( pDevice_ == nullptr )
	{
		return 1;
	}
	result = pDevice_->Initialize( pWindow_->GetWindowHandle(), pWindow_->GetWidth(), pWindow_->GetHeight(), isWindowMode );
	if( result != 0 )
	{
		return result;
	}
	pDevice = pDevice_->GetDevice();

	// フェードクラスの生成
	pFade_ = new Fade();
	if( pFade_ == nullptr )
	{
		return 1;
	}
	result = pFade_->Initialize();
	if( result != 0 )
	{
		return result;
	}

	//	wiiリモコン入力クラスの生成（DirectInput生成前に行うこと！）
	pWiiController_ = new CWiiController;

	// DirectInputオブジェクトの生成
	IDirectInput8*	pDirectInput;		// DirectInputオブジェクト
	pDirectInput_ = new DirectInput();
	if( pDirectInput_ == nullptr )
	{
		return 1;
	}
	result = pDirectInput_->Initialize( instanceHandle );
	if( result != 0 )
	{
		return result;
	}
	pDirectInput = pDirectInput_->GetDirectInput();

	// キーボード入力クラスの生成
	pKeyboard_ = new InputKeyboard();
	if( pKeyboard_ == nullptr )
	{
		return 1;
	}
	result = pKeyboard_->Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	// マウス入力クラスの生成
	pMouse_ = new InputMouse();
	if( pMouse_ == nullptr )
	{
		return 1;
	}
	result = pMouse_->Initialize( pDirectInput, windowHandle, pWindow_->GetWidth(), pWindow_->GetHeight() );
	if( result != 0 )
	{
		return result;
	}
#ifdef _DEBUG
	CameraStateDebug::SetInputMouse( pMouse_ );
#endif

	// ゲームパッド入力クラスの生成
	pPad_ = new InputPad();
	if( pPad_ == nullptr )
	{
		return 1;
	}
	result = pPad_->Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	//	仮想コントローラ管理クラスの生成
	pVirtualController_ = new VirtualController;
	pVirtualController_->initialize(pWiiController_, pKeyboard_, pMouse_, pPad_);

	// パスクラスの生成
	pRenderPass_ = new RenderPass[ GraphicMain::PASS_MAX ];
	if( pRenderPass_ == nullptr )
	{
		return 1;
	}
	result = pRenderPass_[ GraphicMain::PASS_3D ].Initialize( pDevice, GraphicMain::PASS_3D_RENDER_MAX );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_2D ].Initialize( pDevice, GraphicMain::PASS_2D_RENDER_MAX );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_SCREEN ].Initialize( pDevice, GraphicMain::PASS_SCREEN_RENDER_MAX );
	if( result != 0 )
	{
		return result;
	}

	// 描画管理クラスの生成
	pDraw_ = new ManagerDraw< Graphic >();
	if( pDraw_ == nullptr )
	{
		return 1;
	}
	result = pDraw_->Initialize( 256, pDevice, GraphicMain::PASS_MAX, pRenderPass_ );
	if( result != 0 )
	{
		return result;
	}
	Graphic::SetManagerDraw( pDraw_ );

	// 描画表示クラスの初期化
#ifdef _DEBUG
	result = DebugProc::Initialize( pDevice );
#endif
	if( result != 0 )
	{
		return result;
	}

	// 更新管理クラスの生成
	pUpdate_ = new ManagerUpdate< Object >();
	if( pUpdate_ == nullptr )
	{
		return 1;
	}
	result = pUpdate_->Initialize( 256 );
	if( result != 0 )
	{
		return result;
	}
	Object::SetManagerUpdate( pUpdate_ );

	// テクスチャ管理クラスの生成
	pTexture_ = new ManagerTexture< Texture >();
	if( pTexture_ == nullptr )
	{
		return 1;
	}
	result = pTexture_->Initialize( _T( "data/texture/" ), 32, pDevice );
	if( result != 0 )
	{
		return result;
	}

	// モデル管理クラスの生成
	pModel_ = new ManagerModel< Model >();
	if( pModel_ == nullptr )
	{
		return 1;
	}
	result = pModel_->Initialize( _T( "data/model/" ), 32, pDevice, pTexture_ );
	if( result != 0 )
	{
		return result;
	}

	// エフェクト管理クラスの生成
	pEffect_ = new ManagerEffect< Effect >();
	if( pEffect_ == nullptr )
	{
		return 1;
	}
	result = pEffect_->Initialize( _T( "data/effect/" ), 32, pDevice );
	if( result != 0 )
	{
		return result;
	}

	// エフェクトパラメータの生成
	pEffectParameter_ = new EffectParameter();
	if( pEffectParameter_ == nullptr )
	{
		return 1;
	}
	result = pEffectParameter_->Initialize( GraphicMain::LIGHT_DIRECTIONAL_MAX, GraphicMain::LIGHT_POINT_MAX, GraphicMain::CAMERA_MAX );
	if( result != 0 )
	{
		return result;
	}
	pEffectParameter_->SetWidthScreen( static_cast< float >( pWindow_->GetWidth() ) );
	pEffectParameter_->SetHeightScreen( static_cast< float >( pWindow_->GetHeight() ) );

	// 環境光の設定
	pEffectParameter_->SetColorAmbient( 0.1f, 0.1f, 0.1f );

	// 2Dポリゴンの生成
	pPolygon2D_ = new Polygon2D();
	if( pPolygon2D_ == nullptr )
	{
		return 1;
	}
	result = pPolygon2D_->Initialize( pDevice );
	if( result != 0 )
	{
		return result;
	}
	GraphicMain::SetPolygon2D( pPolygon2D_ );

	// 3Dポリゴンの生成
	pPolygon3D_ = new Polygon3D();
	if( pPolygon3D_ == nullptr )
	{
		return 1;
	}
	result = pPolygon3D_->Initialize( pDevice );
	if( result != 0 )
	{
		return result;
	}
	GraphicMain::SetPolygon3D( pPolygon3D_ );

	// 画面オブジェクトの生成
	Effect*			pEffectScreen = nullptr;			// 画面エフェクト
	RenderTarget*	pRenderTarget3D = nullptr;			// 3D画面描画対象
	RenderTarget*	pRenderTarget2D = nullptr;			// 2D画面描画対象
	RenderTarget*	pRenderTargetMask = nullptr;		// マスク描画対象
	pObjectScreen_ = new ObjectScreen();
	if( pObjectScreen_ == nullptr )
	{
		return 1;
	}
	result = pObjectScreen_->Initialize( 0, pFade_ );
	if( result != 0 )
	{
		return result;
	}
	pEffectScreen = pEffect_->Get( _T( "Screen.fx" ) );
	pRenderTarget3D = pRenderPass_[ GraphicMain::PASS_3D ].GetRenderTarget( GraphicMain::PASS_3D_RENDER_COLOR );
	pRenderTarget2D = pRenderPass_[ GraphicMain::PASS_2D ].GetRenderTarget( GraphicMain::PASS_2D_RENDER_COLOR );
	pRenderTargetMask = pRenderPass_[ GraphicMain::PASS_2D ].GetRenderTarget( GraphicMain::PASS_2D_RENDER_MASK );
	result = pObjectScreen_->CreateGraphic( 0, pEffectParameter_, pEffectScreen,
		pRenderTarget3D->GetTexture(), pRenderTarget2D->GetTexture(), pRenderTargetMask->GetTexture() );
	if( result != 0 )
	{
		return result;
	}
	pObjectScreen_->SetPositionY( 1.0f );

	// シーン引数クラスの生成
	pArgument_ = new SceneArgumentMain();
	if( pArgument_ == nullptr )
	{
		return 1;
	}
	pArgument_->pDevice_ = pDevice;
	pArgument_->pFade_ = pFade_;
	pArgument_->pEffectParameter_ = pEffectParameter_;
	pArgument_->pObjectScreen_ = pObjectScreen_;
	pArgument_->pWiiController_ = pWiiController_;
	pArgument_->pKeyboard_ = pKeyboard_;
	pArgument_->pMouse_ = pMouse_;
	pArgument_->pPad_ = pPad_;
	pArgument_->pVirtualController_ = pVirtualController_;
	pArgument_->pTexture_ = pTexture_;
	pArgument_->pModel_ = pModel_;
	pArgument_->pEffect_ = pEffect_;

	// シーン管理クラスの生成
	pScene_ = new ManagerSceneMain();
	if( pScene_ == nullptr )
	{
		return 1;
	}
#ifdef _DEBUG
	result = pScene_->Initialize( ManagerSceneMain::TYPE_TITLE, pArgument_ );
#else
	result = pScene_->Initialize( ManagerSceneMain::TYPE_SPLASH, pArgument_ );
#endif
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerMain::Finalize( void )
{
	// シーン管理クラスの開放
	delete pScene_;
	pScene_ = nullptr;

	// シーン引数クラスの開放
	delete pArgument_;
	pArgument_ = nullptr;

	// 画面オブジェクトの開放
	delete pObjectScreen_;
	pObjectScreen_ = nullptr;

	// 3Dポリゴンの開放
	delete pPolygon3D_;
	pPolygon3D_ = nullptr;

	// 2Dポリゴンの開放
	delete pPolygon2D_;
	pPolygon2D_ = nullptr;

	// エフェクトパラメータの開放
	delete pEffectParameter_;
	pEffectParameter_ = nullptr;

	// エフェクト管理クラスの開放
	delete pEffect_;
	pEffect_ = nullptr;

	// モデル管理クラスの開放
	delete pModel_;
	pModel_ = nullptr;

	// テクスチャ管理クラスの開放
	delete pTexture_;
	pTexture_ = nullptr;

	// 更新管理クラスの終了
	delete pUpdate_;
	pUpdate_ = nullptr;

	// 描画表示クラスの終了
#ifdef _DEBUG
	DebugProc::Finalize();
#endif

	// 描画管理クラスの開放
	delete pDraw_;
	pDraw_ = nullptr;

	// パスクラスの破棄
	delete[] pRenderPass_;
	pRenderPass_ = nullptr;

	//	仮想コントローラ管理クラスの解放
	delete pVirtualController_;
	pVirtualController_ = nullptr;

	// ゲームパッド入力クラスの開放
	delete pPad_;
	pPad_ = nullptr;

	// マウス入力クラスの開放
	delete pMouse_;
	pMouse_ = nullptr;

	// キーボード入力クラスの開放
	delete pKeyboard_;
	pKeyboard_ = nullptr;

	// DirectInputオブジェクトの開放
	delete pDirectInput_;
	pDirectInput_ = nullptr;

	//	wiiリモコン入力クラスの解放
	delete pWiiController_;
	pWiiController_ = nullptr;

	// フェードクラスの開放
	delete pFade_;
	pFade_ = nullptr;

	// Direct3Dデバイスの開放
	delete pDevice_;
	pDevice_ = nullptr;

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Manager::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// クラス内部の初期化
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
// Arg    : int typeShow						: 表示の種類
//==============================================================================
int ManagerMain::Reinitialize( HINSTANCE instanceHandle, int typeShow )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( instanceHandle, typeShow );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerMain* pOut					: コピー先アドレス
//==============================================================================
int ManagerMain::Copy( ManagerMain* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerMain::Update( void )
{
	// エラーチェック
	Assert( pScene_ != nullptr, _T( "シーン管理クラスが生成されていません。" ) );

	// FPSの表示
#ifdef _DEBUG
	DebugProc::Print( _T( "FPS : %2d\n" ), fpsUpdate_ );
#endif

	// 入力の更新
	//pKeyboard_->Update();
	//pMouse_->Update();
	//pPad_->Update();
	pVirtualController_->update();

	// フェードの更新
	pFade_->Update();

	// シーンの更新
	pScene_->Update();
	if( pScene_->IsEnd() )
	{
		isEnd_ = true;
	}

	// オブジェクトの更新
	pUpdate_->Execute();
}

//==============================================================================
// Brief  : 描画処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerMain::Draw( void )
{
	// エラーチェック
	Assert( pDraw_ != nullptr, _T( "メンバ変数が不正です。" ) );

	// 描画処理
	pDraw_->Execute();
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerMain::InitializeSelf( void )
{
	// メンバ変数の初期化
	pScene_ = nullptr;
	pArgument_ = nullptr;
	pDevice_ = nullptr;
	pFade_ = nullptr;
	pEffectParameter_ = nullptr;
	pObjectScreen_ = nullptr;
	pDraw_ = nullptr;
	pUpdate_ = nullptr;
	pRenderPass_ = nullptr;
	pDirectInput_ = nullptr;
	pWiiController_ = nullptr;
	pKeyboard_ = nullptr;
	pMouse_ = nullptr;
	pPad_ = nullptr;
	pVirtualController_ = nullptr;
	pTexture_ = nullptr;
	pModel_ = nullptr;
	pEffect_ = nullptr;
	pPolygon2D_ = nullptr;
	pPolygon3D_ = nullptr;
}
