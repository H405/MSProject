//==============================================================================
//
// File   : FrameCount.cpp
// Brief  : フレームカウントクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <time.h>
#include "FrameCount.h"
#include "Manager.h"
#include "../develop/Debug.h"

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
FrameCount::FrameCount( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
FrameCount::~FrameCount( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
// Arg    : int typeShow						: 表示の種類
// Arg    : Manager* pManager					: マネージャ
// Arg    : int intervalUpdateFps				: FPS更新間隔
// Arg    : int destinationFps					: 目標FPS
//==============================================================================
int FrameCount::Initialize( HINSTANCE instanceHandle, int typeShow, Manager* pManager, int intervalUpdateFps, int destinationFps )
{
	// メンバ変数の設定
	instanceHandle_ = instanceHandle;
	typeShow_ = typeShow;
	pManager_ = pManager;
	intervalUpdateFps_ = intervalUpdateFps;
	destinationFps_ = destinationFps;
	intervalUpdateFps_ = 500;
	destinationFps_ = 60;
	for( int counterItem = 0; counterItem < TYPE_FRAME_COUNT_MAX; ++counterItem )
	{
		ppFunctionCountFrame_[ counterItem ] = nullptr;
	}
	ppFunctionCountFrame_[ TYPE_FRAME_COUNT_DRAW ] = CountFrameDraw;
	ppFunctionCountFrame_[ TYPE_FRAME_COUNT_UPDATE ] = CountFrameUpdate;
	pManager_ = pManager;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int FrameCount::Finalize( void )
{
	// 格納領域の開放
	for( int counterItem = 0; counterItem < TYPE_FRAME_COUNT_MAX; ++counterItem )
	{
		ppFunctionCountFrame_[ counterItem ] = nullptr;
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
// Arg    : int cmdShow							: 表示の種類
// Arg    : Manager* pManager					: マネージャ
//==============================================================================
int FrameCount::Reinitialize( HINSTANCE instanceHandle, int cmdShow, Manager* pManager )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( instanceHandle, cmdShow, pManager, intervalUpdateFps_, destinationFps_ );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : FrameCount* pOut					: コピー先アドレス
//==============================================================================
int FrameCount::Copy( FrameCount* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 実行
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int FrameCount::Execute( void )
{
	// 分解能を設定
	timeBeginPeriod( 1 );

	// リセットループ
	MSG		message;		// メッセージ識別子
	while( isLoopingReset_ )
	{
		// 変数の初期化
		isLoopingMain_ = true;
		isLoopingReset_ = false;
		timeLastExecute_ =
		timeLastUpdate_ =
		timeBeginGame_ = timeGetTime();
		countFrameTotal_ =
		countFrameUpdate_ = 
		countFrameDraw_ = 0;
		typeCountFrame_ = TYPE_FRAME_COUNT_DRAW;
#ifdef _DEVELOP
		fpsUpdate_ = 0;
		fpsDraw_ = 0;
#endif

		// 乱数の初期化
		srand( (unsigned int)time( NULL ) );

		// 初期化処理
		if( pManager_->Initialize( instanceHandle_, typeShow_  ) )
		{
			isLoopingMain_ = false;
		}

		// メッセージループ
		while( isLoopingMain_ )
		{
			if( PeekMessage( &message, NULL, 0, 0, PM_REMOVE ) )
			{
				if( message.message == WM_QUIT )
				{	// PostQuitMessage()が呼ばれたらループ終了
					break;
				}
				else
				{
					// メッセージの翻訳とディスパッチ
					TranslateMessage( &message );
					DispatchMessage( &message );
				}
			}
			else
			{
				// 終了判定
				if( pManager_->IsEnd() )
				{
					isLoopingMain_ = false;
					break;
				}

				// フレームカウント
				(*ppFunctionCountFrame_[ typeCountFrame_ ])( this );
			}
		}
	}

	// 分解能を戻す
	timeEndPeriod( 1 );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void FrameCount::End( void )
{
}

//==============================================================================
// Brief  : 再起動
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void FrameCount::Restart( void )
{
}

//==============================================================================
// Brief  : FPSの更新間隔の設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void FrameCount::SetIntervalUpdateFps( int value )
{
	// 値の設定
	intervalUpdateFps_ = value;
}

//==============================================================================
// Brief  : FPSの更新間隔の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int FrameCount::GetIntervalUpdateFps( void ) const
{
	// 値の返却
	return intervalUpdateFps_;
}

//==============================================================================
// Brief  : 目標FPSの設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void FrameCount::SetDestinationFps( int value )
{
	// 値の設定
	destinationFps_ = value;
}

//==============================================================================
// Brief  : 目標FPSの取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int FrameCount::GetDestinationFps( void ) const
{
	// 値の返却
	return destinationFps_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void FrameCount::InitializeSelf( void )
{
	// メンバ変数の初期化
	instanceHandle_ = NULL;
	typeShow_ = 0;
	isLoopingMain_ = true;
	isLoopingReset_ = true;
	intervalUpdateFps_ = 0;
	destinationFps_ = 0;
	timeLastExecute_ = 0;
	countFrameTotal_ = 0;
	timeBeginGame_ = 0;
	timeLastUpdate_ = 0;
	countFrameUpdate_ = 0;
	countFrameDraw_ = 0;
	typeCountFrame_ = 0;
	for( int counterItem = 0; counterItem < TYPE_FRAME_COUNT_MAX; ++counterItem )
	{
		ppFunctionCountFrame_[ counterItem ] = nullptr;
	}
	pManager_ = nullptr;
#ifdef _DEVELOP
	fpsUpdate_ = 0;
	fpsDraw_ = 0;
#endif
}

//==============================================================================
// Brief  : フレームカウント描画優先処理
// Return : void								: なし
// Arg    : FrameCount* pThis					: 処理するクラス
//==============================================================================
void FrameCount::CountFrameDraw( FrameCount* pThis )
{
	// FPSの更新
	unsigned long	timeCurrent = timeGetTime();
	timeCurrent = timeGetTime();
	if( (timeCurrent - pThis->timeLastUpdate_) >= static_cast< unsigned int >( pThis->intervalUpdateFps_ ) )
	{
#ifdef _DEVELOP
		pThis->fpsUpdate_ = pThis->countFrameUpdate_ * 1000 / (timeCurrent - pThis->timeLastUpdate_);
		pThis->fpsDraw_ = pThis->countFrameDraw_ * 1000 / (timeCurrent - pThis->timeLastUpdate_);
#endif
		pThis->timeLastUpdate_ = timeCurrent;
		pThis->countFrameUpdate_ = 0;
		pThis->countFrameDraw_ = 0;
	}

	// フレームの処理
	if( (timeCurrent - pThis->timeLastExecute_) >= (1000 / 60) )
	{
		// 最終実行時間を更新
		pThis->timeLastExecute_ = timeCurrent;

		// FPSの通知
#ifdef _DEVELOP
		pThis->pManager_->SetFpsUpdate( pThis->fpsUpdate_ );
		pThis->pManager_->SetFpsDraw( pThis->fpsDraw_ );
#endif

		// 更新処理
		pThis->pManager_->Update();

		// 描画処理
		pThis->pManager_->Draw();

		// 更新フレーム数加算
		pThis->countFrameUpdate_++;

		// 描画フレーム数加算
		pThis->countFrameDraw_++;

		// 総フレーム数加算
		pThis->countFrameTotal_++;
	}
}

//==============================================================================
// Brief  : フレームカウント更新優先処理
// Return : void								: なし
// Arg    : FrameCount* pThis					: 処理するクラス
//==============================================================================
void FrameCount::CountFrameUpdate( FrameCount* pThis )
{
	// FPSの更新
	unsigned long	timeCurrent = timeGetTime();
	timeCurrent = timeGetTime();
	if( (timeCurrent - pThis->timeLastUpdate_) >= static_cast< unsigned int >( pThis->intervalUpdateFps_ ) )
	{
#ifdef _DEVELOP
		pThis->fpsUpdate_ = pThis->countFrameUpdate_ * 1000 / (timeCurrent - pThis->timeLastUpdate_);
		pThis->fpsDraw_ = pThis->countFrameDraw_ * 1000 / (timeCurrent - pThis->timeLastUpdate_);
#endif
		pThis->timeLastUpdate_ = timeCurrent;
		pThis->countFrameUpdate_ = 0;
		pThis->countFrameDraw_ = 0;
	}

	// フレームの処理
	if( (timeCurrent - pThis->timeBeginGame_) >= (1000.0f / pThis->destinationFps_) * pThis->countFrameTotal_ )
	{
		// FPSの通知
#ifdef _DEVELOP
		pThis->pManager_->SetFpsUpdate( pThis->fpsUpdate_ );
		pThis->pManager_->SetFpsDraw( pThis->fpsDraw_ );
#endif

		// 更新処理
		pThis->pManager_->Update();

		// 更新フレーム数加算
		pThis->countFrameUpdate_++;

		// 描画処理
		if( (timeCurrent - pThis->timeBeginGame_) <= (1000.0f / pThis->destinationFps_) * (pThis->countFrameTotal_ + 1) )
		{
			// 描画処理
			pThis->pManager_->Draw();

			// 描画フレーム数加算
			pThis->countFrameDraw_++;
		}
		else
		{
			PrintDebugWnd( _T( "処理落ちが発生(%4dミリ秒)\n" ), timeCurrent - pThis->timeBeginGame_ - static_cast< DWORD >( (1000.0f / pThis->destinationFps_) * (pThis->countFrameTotal_ + 1) ) );
		}

		// 総フレーム数加算
		pThis->countFrameTotal_++;
	}
}
