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
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/ObjectScore.h"
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

	// ランキング画像オブジェクトの生成
	Effect*	pEffect2D = nullptr;		// 2D描画エフェクト
	pEffect2D = pArgument_->pEffect_->Get( "Polygon2D.fx" );
	pObjectRanking_ = new Object2D[ IMAGE_RANKING_MAXIMUM ];
	if( pObjectRanking_ == nullptr )
	{
		return 1;
	}

	// ロゴ
	Texture*	pTextureLogo = nullptr;		// ロゴテクスチャ
	pTextureLogo = pArgument_->pTexture_->Get( _T( "ranking/ranking_logo.png" ) );
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureLogo );
	if( result != 0 )
	{
		return result;
	}
	pObjectRanking_[ IMAGE_RANKING_LOGO ].SetPosition( 0.0f, 300.0f, 0.0f );

	// ランク
	Texture*	pTextureRank = nullptr;		// ロゴテクスチャ
	float		heightRank;					// ランキング画像高さ
	pTextureRank = pArgument_->pTexture_->Get( _T( "ranking/rank.png" ) );
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		result = pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].Initialize( 0 );
		if( result != 0 )
		{
			return result;
		}
		result = pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureRank );
		if( result != 0 )
		{
			return result;
		}
		heightRank = pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].GetScaleY();
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetPosition( -500.0f, 170.0f - 120.0f * counterRank, 0.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetScaleY( heightRank / 8.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetScaleTextureY( 8.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetPositionTextureY( 1.0f / 8.0f * counterRank );
	}

	// ランキングスコアオブジェクト
	Texture*	pTextureNumber = nullptr;		// 数字テクスチャ
	pTextureNumber = pArgument_->pTexture_->Get( _T( "common/number_white.png" ) );
	pObjectScoreRanking_ = new ObjectScore[ MAXIMUM_RANK ];
	if( pObjectScoreRanking_ == nullptr )
	{
		return 1;
	}
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		result = pObjectScoreRanking_[ counterRank ].Initialize( 0, 10 );
		if( result != 0 )
		{
			return result;
		}
		result = pObjectScoreRanking_[ counterRank ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureNumber );
		if( result != 0 )
		{
			return result;
		}
		pObjectScoreRanking_[ counterRank ].SetSizeX( static_cast< float >( pTextureNumber->width_ ) / 8.0f );
		pObjectScoreRanking_[ counterRank ].SetPos( -250.0f, 170.0f - 120.0f * counterRank, 0.0f );
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
	// ランキングスコアオブジェクトの開放
	delete[] pObjectScoreRanking_;
	pObjectScoreRanking_ = nullptr;

	// ランキング画像オブジェクトの開放
	delete[] pObjectRanking_;
	pObjectRanking_ = nullptr;

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
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		pRankingScore_[ counterRank ] = 0;
	}
	indexRank_ = 0;
	pObjectRanking_ = nullptr;
	pObjectScoreRanking_ = nullptr;
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

//==============================================================================
// Brief  : ランキング更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::UpdateRanking( void )
{
	// テスト
	PrintDebug( _T( "UpdateRanking\n" ) );
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		PrintDebug( _T( "Rank%d : %10d\n" ), counterRank, pRankingScore_[ counterRank ] );
	}

	// ランキングデータの読み込み
	if( timerSceneGame_ == 0 )
	{
		// ファイルを開く
		FILE*	pFile = nullptr;		// ファイル
		fopen_s( &pFile, _T( "data/ranking/ranking.txt" ), _T( "r+t" ) );

		// データの読み込み
		if( pFile != nullptr )
		{
			for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
			{
				if( _ftscanf_s( pFile, _T( "%d" ), &pRankingScore_[ counterRank ] ) == EOF )
				{
					break;
				}
			}
		}

		// ファイルを閉じる
		if( pFile != nullptr )
		{
			fclose( pFile );
			pFile = nullptr;
		}
	}

	// ランキングの更新
	if( timerSceneGame_ == 0 )
	{
		int		scoreCurrent;		// 現在のスコア
		scoreCurrent = score->GetScore();
		for( indexRank_ = 0; indexRank_ < MAXIMUM_RANK; ++indexRank_ )
		{
			if( scoreCurrent >= pRankingScore_[ indexRank_ ] )
			{
				for( int counterRank = MAXIMUM_RANK - 1; counterRank > indexRank_; --counterRank )
				{
					pRankingScore_[ counterRank ] = pRankingScore_[ counterRank - 1 ];
				}
				pRankingScore_[ indexRank_ ] = scoreCurrent;
			}
		}
	}

	// ランキングの書き込み
	if( timerSceneGame_ == 0 )
	{
		// ファイルを開く
		FILE*	pFile = nullptr;		// ファイル
		fopen_s( &pFile, _T( "data/ranking/ranking.txt" ), _T( "w+t" ) );
		if( pFile == nullptr )
		{
			return;
		}

		// データの書き込み
		for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
		{
			_ftprintf_s( pFile, _T( "%d\n" ), pRankingScore_[ counterRank ] );
		}

		// ファイルを閉じる
		fclose( pFile );
		pFile = nullptr;
	}

	// スコアオブジェクトに設定
	if( timerSceneGame_ == 0 )
	{
		for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
		{
			pObjectScoreRanking_[ counterRank ].SetScore( pRankingScore_[ counterRank ] );
		}
	}

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// タイマーの経過
	++timerSceneGame_;
}
