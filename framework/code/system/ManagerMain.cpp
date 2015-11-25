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
#include "../framework/camera/CameraObject.h"
#include "../framework/camera/CameraStateDebug.h"
#include "../framework/camera/ManagerCamera.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugMeasure.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/graphic/Graphic.h"
#include "../framework/input/DirectInput.h"
#include "../framework/input/CWiiController.h"
#include "../framework/input/InputKeyboard.h"
#include "../framework/input/InputMouse.h"
#include "../framework/input/InputPad.h"
#include "../framework/input/VirtualController.h"
#include "../framework/light/ManagerLight.h"
#include "../framework/object/Object.h"
#include "../framework/polygon/Polygon2D.h"
#include "../framework/polygon/Polygon3D.h"
#include "../framework/polygon/PolygonBillboard.h"
#include "../framework/render/DirectDevice.h"
#include "../framework/render/RenderPass.h"
#include "../framework/render/RenderPassParameter.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerModel.h"
#include "../framework/resource/ManagerMotion.h"
#include "../framework/resource/ManagerSound.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/sound/XAudio.h"
#include "../framework/system/Fade.h"
#include "../framework/system/ManagerDraw.h"
#include "../framework/system/ManagerUpdate.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/ObjectBlur.h"
#include "../object/ObjectLightEffect.h"
#include "../object/ObjectLightReflect.h"
#include "../object/ObjectMerge.h"
#include "../object/ObjectPostEffect.h"
#include "../object/ObjectShadow.h"
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
	// COMライブラリの初期化
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Manager::Initialize( instanceHandle, typeShow );
	if( result != 0 )
	{
		return result;
	}

	// ウィンドウの生成
	HWND	windowHandle;		// ウィンドウハンドル
	int		widthWindow;		// ウィンドウ幅
	int		heightWindow;		// ウィンドウ高さ
	pWindow_ = new WindowMain();
	if( pWindow_ == nullptr )
	{
		return 1;
	}
	result = pWindow_->Initialize( instanceHandle, typeShow, 1280, 720, _T( "花町風月" ), _T( "WindowClass" ) );
	if( result != 0 )
	{
		return result;
	}
	windowHandle = pWindow_->GetWindowHandle();
	widthWindow = pWindow_->GetWidth();
	heightWindow = pWindow_->GetHeight();

#ifdef _DEVELOP
	// デバッグ用計測クラスの初期化
	ManagerDebugMeasure::Initialize();
#endif

	// Direct3Dデバイスの生成
	IDirect3DDevice9*	pDevice = nullptr;			// Direct3Dデバイス
	bool				isWindowMode = false;		// ウィンドウモードフラグ
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

	// ライト管理クラスの生成
	pLight_ = new ManagerLight();
	if( pLight_ == nullptr )
	{
		return 1;
	}
	result = pLight_->Initialize( GraphicMain::LIGHT_DIRECTIONAL_MAX, GraphicMain::LIGHT_POINT_MAX );
	if( result != 0 )
	{
		return result;
	}
	
	// カメラ管理クラスの生成
	pCamera_ = new ManagerCamera();
	if( pCamera_ == nullptr )
	{
		return 1;
	}
	result = pCamera_->Initialize( GraphicMain::CAMERA_MAX );
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
#ifdef _DEVELOP
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

	// XAudioインターフェースの生成
	IXAudio2* pXAudio = nullptr;		// XAudio2インターフェース
	pXAudio_ = new XAudio();
	if( pXAudio_ == nullptr )
	{
		return 1;
	}
	result = pXAudio_->Initialize( windowHandle );
	if( result != 0 )
	{
		return result;
	}
	pXAudio = pXAudio_->GetXAudio();

	// パスクラスの生成
	RenderPassParameter	parameterPassWaveData;			// 波情報描画パスのパラメータ
	RenderPassParameter	parameterPass3D;				// 3D描画パスのパラメータ
	RenderPassParameter	parameterPassDepthShadow;		// 影用深度パスのパラメータ
	RenderPassParameter	parameterPassShadow;			// 影パスのパラメータ
	RenderPassParameter	parameterPassReflect;			// 反射パスのパラメータ
	RenderPassParameter	parameterPassReflectLight;		// 反射ライティングパスのパラメータ
	RenderPassParameter	parameterPassReflectAdd;		// 反射加算合成パスのパラメータ
	RenderPassParameter	parameterPassWater;				// 水描画パスのパラメータ
	RenderPassParameter	parameterPassNotLight;			// ライティングなし3D描画パスのパラメータ
	RenderPassParameter	parameterPassLightEffect;		// ライティングパスのパラメータ
	RenderPassParameter	parameterPassMerge;				// 総合3D描画パスのパラメータ
	RenderPassParameter	parameterPassBlur;				// ブラーパスのパラメータ
	pRenderPass_ = new RenderPass[ GraphicMain::PASS_MAX ];
	if( pRenderPass_ == nullptr )
	{
		return 1;
	}
	parameterPassWaveData.width_ = 256;
	parameterPassWaveData.height_ = 256;
	parameterPassWaveData.pFormat_[ GraphicMain::RENDER_PASS_WAVE_DATA_HEIGHT ] = D3DFMT_A16B16G16R16F;
	parameterPassWaveData.pCountMultiple_[ GraphicMain::RENDER_PASS_WAVE_DATA_HEIGHT ] = 2;
	result = pRenderPass_[ GraphicMain::PASS_WAVE_DATA ].Initialize( pDevice, GraphicMain::RENDER_PASS_WAVE_DATA_MAX, &parameterPassWaveData );
	if( result != 0 )
	{
		return result;
	}
	parameterPass3D.pFormat_[ GraphicMain::RENDER_PASS_3D_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_3D ].Initialize( pDevice, GraphicMain::RENDER_PASS_3D_MAX, &parameterPass3D );
	if( result != 0 )
	{
		return result;
	}
	parameterPassDepthShadow.pFormat_[ GraphicMain::RENDER_PASS_DEPTH_SHADOW_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_DEPTH_SHADOW ].Initialize( pDevice, GraphicMain::RENDER_PASS_DEPTH_SHADOW_MAX, &parameterPassDepthShadow );
	if( result != 0 )
	{
		return result;
	}
	parameterPassShadow.pFormat_[ GraphicMain::RENDER_PASS_SHADOW_COLOR ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_SHADOW ].Initialize( pDevice, GraphicMain::RENDER_PASS_SHADOW_MAX, &parameterPassShadow );
	if( result != 0 )
	{
		return result;
	}
	parameterPassReflect.width_ = widthWindow / 4;
	parameterPassReflect.height_ = heightWindow / 4;
	parameterPassReflect.pFormat_[ GraphicMain::RENDER_PASS_REFLECT_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_REFLECT ].Initialize( pDevice, GraphicMain::RENDER_PASS_REFLECT_MAX, &parameterPassReflect );
	if( result != 0 )
	{
		return result;
	}
	parameterPassReflectLight.width_ = widthWindow / 4;
	parameterPassReflectLight.height_ = heightWindow / 4;
	result = pRenderPass_[ GraphicMain::PASS_LIGHT_REFLECT ].Initialize( pDevice, GraphicMain::RENDER_PASS_LIGHT_REFLECT_MAX, &parameterPassReflectLight );
	if( result != 0 )
	{
		return result;
	}
	parameterPassReflectAdd.width_ = widthWindow / 4;
	parameterPassReflectAdd.height_ = heightWindow / 4;
	parameterPassReflectAdd.flagClear_ = D3DCLEAR_TARGET;
	parameterPassReflectAdd.pSurfaceDepth_ = pRenderPass_[ GraphicMain::PASS_REFLECT ].GetSurfaceDepth();
	result = pRenderPass_[ GraphicMain::PASS_REFLECT_NOT_LIGHT ].Initialize( pDevice, GraphicMain::RENDER_PASS_REFLECT_NOT_LIGHT_MAX, &parameterPassReflectAdd );
	if( result != 0 )
	{
		return result;
	}
	parameterPassWater.flagClear_ = D3DCLEAR_TARGET;
	parameterPassWater.pSurfaceDepth_ = pRenderPass_[ GraphicMain::PASS_3D ].GetSurfaceDepth();
	parameterPassWater.pFormat_[ GraphicMain::RENDER_PASS_WATER_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_WATER ].Initialize( pDevice, GraphicMain::RENDER_PASS_WATER_MAX, &parameterPassWater );
	if( result != 0 )
	{
		return result;
	}
	parameterPassNotLight.flagClear_ = D3DCLEAR_TARGET;
	parameterPassNotLight.pSurfaceDepth_ = pRenderPass_[ GraphicMain::PASS_3D ].GetSurfaceDepth();
	result = pRenderPass_[ GraphicMain::PASS_3D_NOT_LIGHT ].Initialize( pDevice, GraphicMain::RENDER_PASS_3D_NOT_LIGHT_MAX, &parameterPassNotLight );
	if( result != 0 )
	{
		return result;
	}
	parameterPassLightEffect.pFormat_[ GraphicMain::RENDER_PASS_LIGHT_EFFECT_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_LIGHT_EFFECT ].Initialize( pDevice, GraphicMain::RENDER_PASS_LIGHT_EFFECT_MAX, &parameterPassLightEffect );
	if( result != 0 )
	{
		return result;
	}
	parameterPassMerge.pFormat_[ GraphicMain::RENDER_PASS_3D_MERGE_DEPTH ] = D3DFMT_R32F;
	result = pRenderPass_[ GraphicMain::PASS_3D_MERGE ].Initialize( pDevice, GraphicMain::RENDER_PASS_3D_MERGE_MAX, &parameterPassMerge );
	if( result != 0 )
	{
		return result;
	}
	parameterPassBlur.width_ = widthWindow / 4;
	parameterPassBlur.height_ = heightWindow / 4;
	result = pRenderPass_[ GraphicMain::PASS_BLUR_X ].Initialize( pDevice, GraphicMain::RENDER_PASS_BLUR_X_MAX, &parameterPassBlur );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_BLUR_Y ].Initialize( pDevice, GraphicMain::RENDER_PASS_BLUR_Y_MAX, &parameterPassBlur );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_2D ].Initialize( pDevice, GraphicMain::RENDER_PASS_2D_MAX );
	if( result != 0 )
	{
		return result;
	}
	result = pRenderPass_[ GraphicMain::PASS_POST_EFFECT ].Initialize( pDevice, GraphicMain::RENDER_PASS_POST_EFFECT_MAX );
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
	result = pDraw_->Initialize( 1024, pDevice, GraphicMain::PASS_MAX, pRenderPass_ );
	if( result != 0 )
	{
		return result;
	}
	Graphic::SetManagerDraw( pDraw_ );

	// 描画表示クラスの初期化
#ifdef _DEVELOP
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
	result = pUpdate_->Initialize( 1024 );
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
	result = pTexture_->Initialize( _T( "data/texture/" ), 64, pDevice );
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
	result = pModel_->Initialize( _T( "data/model/" ), _T( "model/" ), 32, pDevice, pTexture_ );
	if( result != 0 )
	{
		return result;
	}

	// モーション管理クラスの生成
	pMotion_ = new ManagerMotion< Motion >();
	if( pMotion_ == nullptr )
	{
		return 1;
	}
	result = pMotion_->Initialize( _T( "data/Motion/" ), 32 );
	if( result != 0 )
	{
		return result;
	}
	pMotion_->Get( _T( "test.motion" ) );

	// エフェクト管理クラスの生成
#ifdef _DEBUG
	TCHAR	pPathEffect[] = _T( "code/effect/" );
#else
	TCHAR	pPathEffect[] = _T( "data/effect/" );
#endif
	pEffect_ = new ManagerEffect< Effect >();
	if( pEffect_ == nullptr )
	{
		return 1;
	}
	result = pEffect_->Initialize( pPathEffect, 64, pDevice );
	if( result != 0 )
	{
		return result;
	}

	// サウンド管理クラスの生成
	pSound_ = new ManagerSound< Sound >();
	if( pSound_ == nullptr )
	{
		return 1;
	}
	result = pSound_->Initialize( _T( "data/sound/" ), 32, pXAudio );
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
	pEffectParameter_->SetWidthScreen( static_cast< float >( widthWindow ) );
	pEffectParameter_->SetHeightScreen( static_cast< float >( heightWindow ) );

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

	// ビルボードポリゴンの生成
	pPolygonBillboard_ = new PolygonBillboard();
	if( pPolygonBillboard_ == nullptr )
	{
		return 1;
	}
	result = pPolygonBillboard_->Initialize( pDevice );
	if( result != 0 )
	{
		return result;
	}
	GraphicMain::SetPolygonBillboard( pPolygonBillboard_ );

	// 影オブジェクトの生成
	Effect*	pEffectShadow = nullptr;		// 影エフェクト
	pObjectShadow_ = new ObjectShadow();
	if( pObjectShadow_ == nullptr )
	{
		return 1;
	}
	result = pObjectShadow_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	pEffectShadow = pEffect_->Get( _T( "Shadow.fx" ) );
	result = pObjectShadow_->CreateGraphic( 0, pEffectParameter_, pEffectShadow,
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DEPTH ),
		pRenderPass_[ GraphicMain::PASS_DEPTH_SHADOW ].GetTexture( GraphicMain::RENDER_PASS_DEPTH_SHADOW_DEPTH ) );
	if( result != 0 )
	{
		return result;
	}

	// 反射ライティングオブジェクトの生成
	Effect*	ppEffectLightReflect[ GraphicMain::LIGHT_POINT_MAX + 1 ];		// ライティングエフェクト
	TCHAR	pNameFileEffectLight[ _MAX_PATH ];								// ライティングエフェクトファイル名
	pObjectLightReflect_ = new ObjectLightReflect();
	if( pObjectLightReflect_ == nullptr )
	{
		return 1;
	}
	result = pObjectLightReflect_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	for( int counterEffect = 0; counterEffect <= GraphicMain::LIGHT_POINT_MAX; ++counterEffect )
	{
		_stprintf_s( pNameFileEffectLight, _MAX_PATH, _T( "LightReflect_%02d.fx" ), counterEffect );
		ppEffectLightReflect[ counterEffect ] = pEffect_->Get( pNameFileEffectLight );
	}
	result = pObjectLightReflect_->CreateGraphic( 0, pEffectParameter_, ppEffectLightReflect,
		pRenderPass_[ GraphicMain::PASS_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_DIFFUSE ),
		pRenderPass_[ GraphicMain::PASS_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_SPECULAR ),
		pRenderPass_[ GraphicMain::PASS_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_NORMAL ),
		pRenderPass_[ GraphicMain::PASS_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_DEPTH ) );
	if( result != 0 )
	{
		return result;
	}

	// ライティングオブジェクトの生成
	Effect*	ppEffectLightEffect[ GraphicMain::LIGHT_POINT_MAX + 1 ];		// ライティングエフェクト
	pObjectLightEffect_ = new ObjectLightEffect();
	if( pObjectLightEffect_ == nullptr )
	{
		return 1;
	}
	result = pObjectLightEffect_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	for( int counterEffect = 0; counterEffect <= GraphicMain::LIGHT_POINT_MAX; ++counterEffect )
	{
		_stprintf_s( pNameFileEffectLight, _MAX_PATH, _T( "LightEffect_%02d.fx" ), counterEffect );
		ppEffectLightEffect[ counterEffect ] = pEffect_->Get( pNameFileEffectLight );
	}
	result = pObjectLightEffect_->CreateGraphic( 0, pEffectParameter_, ppEffectLightEffect,
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DIFFUSE ),
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_SPECULAR ),
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_NORMAL ),
		pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DEPTH ),
		pRenderPass_[ GraphicMain::PASS_WATER ].GetTexture( GraphicMain::RENDER_PASS_WATER_DIFFUSE ),
		pRenderPass_[ GraphicMain::PASS_WATER ].GetTexture( GraphicMain::RENDER_PASS_WATER_SPECULAR ),
		pRenderPass_[ GraphicMain::PASS_WATER ].GetTexture( GraphicMain::RENDER_PASS_WATER_NORMAL ),
		pRenderPass_[ GraphicMain::PASS_WATER ].GetTexture( GraphicMain::RENDER_PASS_WATER_DEPTH ),
		pRenderPass_[ GraphicMain::PASS_SHADOW ].GetTexture( GraphicMain::RENDER_PASS_SHADOW_COLOR ) );
	if( result != 0 )
	{
		return result;
	}

	// 総合3D描画オブジェクトの生成
	Effect*	pEffectMerge = nullptr;		// 総合3D描画エフェクト
	pObjectMerge_ = new ObjectMerge();
	if( pObjectMerge_ == nullptr )
	{
		return 1;
	}
	result = pObjectMerge_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	pEffectMerge = pEffect_->Get( _T( "Merge.fx" ) );
	result = pObjectMerge_->CreateGraphic( 0, pEffectParameter_, pEffectMerge,
		pRenderPass_[ GraphicMain::PASS_LIGHT_EFFECT ].GetTexture( GraphicMain::RENDER_PASS_LIGHT_EFFECT_COLOR ),
		pRenderPass_[ GraphicMain::PASS_3D_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_3D_NOT_LIGHT_COLOR ),
		pRenderPass_[ GraphicMain::PASS_3D_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_3D_NOT_LIGHT_MASK ),
		pRenderPass_[ GraphicMain::PASS_3D_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_3D_NOT_LIGHT_ADD ),
		pRenderPass_[ GraphicMain::PASS_LIGHT_EFFECT ].GetTexture( GraphicMain::RENDER_PASS_LIGHT_EFFECT_DEPTH ) );
	if( result != 0 )
	{
		return result;
	}

	// ブラーオブジェクトの生成
	Effect*	pBlurX = nullptr;		// X方向ブラーエフェクト
	Effect*	pBlurY = nullptr;		// Y方向ブラーエフェクト
	pObjectBlur_ = new ObjectBlur();
	if( pObjectBlur_ == nullptr )
	{
		return 1;
	}
	result = pObjectBlur_->Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	pBlurX = pEffect_->Get( _T( "BlurX.fx" ) );
	pBlurY = pEffect_->Get( _T( "BlurY.fx" ) );
	result = pObjectBlur_->CreateGraphic( 0, pEffectParameter_, pBlurX, pBlurY,
		pRenderPass_[ GraphicMain::PASS_3D_MERGE ].GetTexture( GraphicMain::RENDER_PASS_3D_MERGE_COLOR ),
		pRenderPass_[ GraphicMain::PASS_BLUR_X ].GetTexture( GraphicMain::RENDER_PASS_BLUR_X_COLOR ) );
	if( result != 0 )
	{
		return result;
	}

	// ポストエフェクトオブジェクトの生成
	Effect*	pEffectPostEffect = nullptr;		// ポストエフェクト
	pObjectPostEffect_ = new ObjectPostEffect();
	if( pObjectPostEffect_ == nullptr )
	{
		return 1;
	}
	result = pObjectPostEffect_->Initialize( 0, pFade_ );
	if( result != 0 )
	{
		return result;
	}
	pEffectPostEffect = pEffect_->Get( _T( "PostEffect.fx" ) );
	result = pObjectPostEffect_->CreateGraphic( 0, pEffectParameter_, pEffectPostEffect,
		pRenderPass_[ GraphicMain::PASS_3D_MERGE ].GetTexture( GraphicMain::RENDER_PASS_3D_MERGE_COLOR ),
		pRenderPass_[ GraphicMain::PASS_BLUR_Y ].GetTexture( GraphicMain::RENDER_PASS_BLUR_Y_LUMINANCE ),
		pRenderPass_[ GraphicMain::PASS_BLUR_Y ].GetTexture( GraphicMain::RENDER_PASS_BLUR_Y_COLOR ),
		pRenderPass_[ GraphicMain::PASS_3D_MERGE ].GetTexture( GraphicMain::RENDER_PASS_3D_MERGE_DEPTH ),
		pRenderPass_[ GraphicMain::PASS_2D ].GetTexture( GraphicMain::RENDER_PASS_2D_COLOR ),
		pRenderPass_[ GraphicMain::PASS_2D ].GetTexture( GraphicMain::RENDER_PASS_2D_MASK ) );
	if( result != 0 )
	{
		return result;
	}

	// シーン引数クラスの生成
	pArgument_ = new SceneArgumentMain();
	if( pArgument_ == nullptr )
	{
		return 1;
	}
	pArgument_->pWindow_ = pWindow_;
	pArgument_->pDevice_ = pDevice;
	pArgument_->pFade_ = pFade_;
	pArgument_->pLight_ = pLight_;
	pArgument_->pCamera_ = pCamera_;
	pArgument_->pEffectParameter_ = pEffectParameter_;
	pArgument_->pWiiController_ = pWiiController_;
	pArgument_->pKeyboard_ = pKeyboard_;
	pArgument_->pMouse_ = pMouse_;
	pArgument_->pPad_ = pPad_;
	pArgument_->pVirtualController_ = pVirtualController_;
	pArgument_->pTexture_ = pTexture_;
	pArgument_->pModel_ = pModel_;
	pArgument_->pMotion_ = pMotion_;
	pArgument_->pEffect_ = pEffect_;
	pArgument_->pSound_ = pSound_;
	pArgument_->pDraw_ = pDraw_;
	pArgument_->pUpdate_ = pUpdate_;
	pArgument_->pTextureHeightWave0_ = pRenderPass_[ GraphicMain::PASS_WAVE_DATA ].GetTexture( GraphicMain::RENDER_PASS_WAVE_DATA_HEIGHT, 0 );
	pArgument_->pTextureHeightWave1_ = pRenderPass_[ GraphicMain::PASS_WAVE_DATA ].GetTexture( GraphicMain::RENDER_PASS_WAVE_DATA_HEIGHT, 1 );
	pArgument_->pTextureNormalWave_ = pRenderPass_[ GraphicMain::PASS_WAVE_DATA ].GetTexture( GraphicMain::RENDER_PASS_WAVE_DATA_NORMAL );
	pArgument_->pTextureReflect_ = pRenderPass_[ GraphicMain::PASS_LIGHT_REFLECT ].GetTexture( GraphicMain::RENDER_PASS_LIGHT_REFLECT_COLOR );
	pArgument_->pTextureReflectNotLight_ = pRenderPass_[ GraphicMain::PASS_REFLECT_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_NOT_LIGHT_COLOR );
	pArgument_->pTextureReflectAdd_ = pRenderPass_[ GraphicMain::PASS_REFLECT_NOT_LIGHT ].GetTexture( GraphicMain::RENDER_PASS_REFLECT_NOT_LIGHT_ADD );
	pArgument_->pTexture3D_ = pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DIFFUSE );
	pArgument_->pTextureDepth_ = pRenderPass_[ GraphicMain::PASS_3D ].GetTexture( GraphicMain::RENDER_PASS_3D_DEPTH );
	pArgument_->pTextureTest_ = pRenderPass_[ GraphicMain::PASS_SHADOW ].GetTexture( GraphicMain::RENDER_PASS_SHADOW_COLOR );

	// シーン管理クラスの生成
	pScene_ = new ManagerSceneMain();
	if( pScene_ == nullptr )
	{
		return 1;
	}
#ifdef _DEBUG
	result = pScene_->Initialize( ManagerSceneMain::TYPE_GAME, pArgument_ );
#else
	result = pScene_->Initialize( ManagerSceneMain::TYPE_TITLE, pArgument_ );
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

	// 影オブジェクトの開放
	delete pObjectShadow_;
	pObjectShadow_ = nullptr;

	// ポストエフェクトオブジェクトの開放
	delete pObjectPostEffect_;
	pObjectPostEffect_ = nullptr;

	// ブラーオブジェクトの開放
	delete pObjectBlur_;
	pObjectBlur_ = nullptr;

	// 総合3D描画オブジェクトの開放
	delete pObjectMerge_;
	pObjectMerge_ = nullptr;

	// ライティングオブジェクトの開放
	delete pObjectLightEffect_;
	pObjectLightEffect_ = nullptr;

	// 反射ライティングオブジェクトの開放
	delete pObjectLightReflect_;
	pObjectLightReflect_ = nullptr;

	// ビルボードポリゴンの開放
	delete pPolygonBillboard_;
	pPolygonBillboard_ = nullptr;

	// 3Dポリゴンの開放
	delete pPolygon3D_;
	pPolygon3D_ = nullptr;

	// 2Dポリゴンの開放
	delete pPolygon2D_;
	pPolygon2D_ = nullptr;

	// エフェクトパラメータの開放
	delete pEffectParameter_;
	pEffectParameter_ = nullptr;

	// サウンド管理クラスの開放
	delete pSound_;
	pSound_ = nullptr;

	// エフェクト管理クラスの開放
	delete pEffect_;
	pEffect_ = nullptr;

	// モーション管理クラスの開放
	delete pMotion_;
	pMotion_ = nullptr;

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
#ifdef _DEVELOP
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

	// カメラ管理クラスの開放
	delete pCamera_;
	pCamera_ = nullptr;

	// ライト管理クラスの開放
	delete pLight_;
	pLight_ = nullptr;

	// フェードクラスの開放
	delete pFade_;
	pFade_ = nullptr;

	// XAudio2インターフェスの開放
	delete pXAudio_;
	pXAudio_ = nullptr;

	// Direct3Dデバイスの開放
	delete pDevice_;
	pDevice_ = nullptr;

#ifdef _DEVELOP
	// デバッグ用計測クラスの終了
	ManagerDebugMeasure::Finalize();
#endif

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Manager::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// COMライブラリの終了処理
	CoUninitialize();

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

#ifdef _DEVELOP
	// FPSの表示
	DebugProc::Print( _T( "FPS : %2d\n" ), fpsUpdate_ );

	// デバッグ用計測クラスの更新
	ManagerDebugMeasure::Update();
#endif

	// 入力の更新
	//pKeyboard_->Update();
	//pMouse_->Update();
	//pPad_->Update();
	pVirtualController_->update();

	// デバッグポーズ
#ifdef _DEVELOP
	if(pKeyboard_->IsTrigger(DIK_F2))
	{
		pDraw_->screenShotON();
	}
	if( pKeyboard_->IsTrigger( DIK_F11 ) )
	{
		isPausing_ = !isPausing_;
	}
	if( !pKeyboard_->IsTrigger( DIK_F12 ) && isPausing_ )
	{
		return;
	}
	if(isPausing_)
	{
		DebugProc::Print( _T( "ポーズ解除：F11\n１コマ進めるF12\n" ));
	}
#endif

	// フェードの更新
	pFade_->Update();

	// シーンの更新
	{ MeasureTime( _T( "シーンの更新" ) );
		pScene_->Update();
	}
	if( pScene_->IsEnd() )
	{
		isEnd_ = true;
	}

	// オブジェクトの更新
	if( pUpdate_->IsEnable() )
	{
		pUpdate_->Execute();
	}

	// エフェクトパラメータにライトを設定
	int		countLightDirection;		// ディレクショナルライト数
	int		countLightPoint;			// ポイントライト数
	countLightDirection = pLight_->GetCountLightDirection();
	countLightPoint = pLight_->GetCountLightPoint();
	pEffectParameter_->SetCountLightDirection( countLightDirection );
	for( int counterLight = 0; counterLight < countLightDirection; ++counterLight )
	{
		pEffectParameter_->SetLightDirection( counterLight, pLight_->GetLightDirectionEnable( counterLight ) );
	}
	pEffectParameter_->SetCountLightPoint( countLightPoint );
	for( int counterLight = 0; counterLight < countLightPoint; ++counterLight )
	{
		pEffectParameter_->SetLightPoint( counterLight, pLight_->GetLightPointEnable( counterLight ) );
	}

	// カメラの更新
	pCamera_->Update();
	for( int counterCamera = 0; counterCamera < GraphicMain::CAMERA_MAX; ++ counterCamera )
	{
		pEffectParameter_->SetCamera( counterCamera, pCamera_->GetCamera( counterCamera ) );
	}
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
	{
		MeasureTime( _T( "描画" ) );
		pDraw_->Execute();
	}
}

//==============================================================================
// Brief  : スクリーンショット撮影
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerMain::screenShotON()
{
	pDraw_->screenShotON();
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
	pXAudio_ = nullptr;
	pFade_ = nullptr;
	pLight_ = nullptr;
	pCamera_ = nullptr;
	pEffectParameter_ = nullptr;
	pObjectBlur_ = nullptr;
	pObjectLightEffect_ = nullptr;
	pObjectLightReflect_ = nullptr;
	pObjectMerge_ = nullptr;
	pObjectPostEffect_ = nullptr;
	pObjectShadow_ = nullptr;
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
	pMotion_ = nullptr;
	pEffect_ = nullptr;
	pPolygon2D_ = nullptr;
	pPolygon3D_ = nullptr;
	pPolygonBillboard_ = nullptr;

#ifdef _DEVELOP
	isPausing_ = false;
#endif
}
