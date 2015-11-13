//==============================================================================
//
// File   : SceneGame2.cpp
// Brief  : ゲームシーンクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/11 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "SceneGame.h"
#include "../framework/camera/CameraObject.h"
#include "../framework/develop/Debug.h"
#include "../framework/develop/DebugProc.h"
#include "../framework/input/VirtualController.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../system/camera/CameraStateSpline.h"
#include "../system/SceneArgumentMain.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的変数
//******************************************************************************

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int SceneGame::Initialize2( void )
{
	// ゲーム開始前カメラ処理の生成
	int		result;		// 実行結果
	pStateCameraPrevious_ = new CameraStateSpline();
	if( pStateCameraPrevious_ == nullptr )
	{
		return 1;
	}
	result = pStateCameraPrevious_->Initialize( _T( "data/camera/PreviousGame.txt" ) );
	if( result != 0 )
	{
		return result;
	}

	// リザルト前カメラ処理の生成
	pStateCameraResult_ = new CameraStateSpline();
	if( pStateCameraResult_ == nullptr )
	{
		return 1;
	}
	result = pStateCameraResult_->Initialize( _T( "data/camera/PreviousResult.txt" ) );
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
int SceneGame::Finalize2( void )
{
	// リザルト前カメラ処理の開放
	delete pStateCameraResult_;
	pStateCameraResult_ = nullptr;

	// ゲーム開始前カメラ処理の開放
	delete pStateCameraPrevious_;
	pStateCameraPrevious_ = nullptr;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::InitializeSelf2( void )
{
	// メンバ変数の初期化
	pStateCameraPrevious_ = nullptr;
	pStateCameraResult_ = nullptr;
	timerSceneGame_ = 0;
}

//==============================================================================
// Brief  : ゲーム開始前更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::UpdatePreviousGame( void )
{
	// テスト
	PrintDebug( _T( "UpdatePreviousGame\n" ) );

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( pStateCameraPrevious_ );
	}

	// タイマーの経過
	++timerSceneGame_;

	// 更新処理の切り替え
	if( timerSceneGame_ >= pStateCameraPrevious_->GetCountFrame() )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdateCountDownGame;
	}
}

//==============================================================================
// Brief  : ゲーム開始前カウントダウン更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::UpdateCountDownGame( void )
{
	// テスト
	PrintDebug( _T( "UpdateCountDownGame\n" ) );
	PrintDebug( _T( "Timer : %05d\n" ), timerSceneGame_ );

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// タイマーの経過
	++timerSceneGame_;

	// 更新処理の切り替え
	if( timerSceneGame_ >= 240 )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::normalUpdate;
	}
}

//==============================================================================
// Brief  : リザルト待機更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::UpdateWaitResult( void )
{
	// テスト
	PrintDebug( _T( "UpdateWaitResult\n" ) );

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// タイマーの経過
	++timerSceneGame_;

	// 更新処理の切り替え
	if( pArgument_->pVirtualController_->IsTrigger( VC_DESIDE ) )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdatePreviousResult;
	}
}

//==============================================================================
// Brief  : リザルト前更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::UpdatePreviousResult( void )
{
	// テスト
	PrintDebug( _T( "UpdatePreviousResult\n" ) );

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( pStateCameraResult_ );
	}

	// タイマーの経過
	++timerSceneGame_;
}

//==============================================================================
// Brief  : リザルト更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::UpdateResult( void )
{
	// テスト
	PrintDebug( _T( "UpdateResult\n" ) );

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// タイマーの経過
	++timerSceneGame_;
}
