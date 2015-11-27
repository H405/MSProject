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

	// リザルト画像オブジェクトの生成
	Effect*	pEffect2D = nullptr;		// 2D描画エフェクト
	pEffect2D = pArgument_->pEffect_->Get( "Polygon2D.fx" );
	pObjectResult_ = new Object2D[ IMAGE_RESULT_MAXIMUM ];
	if( pObjectResult_ == nullptr )
	{
		return 1;
	}

	// リザルト背景
	Texture*	pTextureResultBack = nullptr;		// リザルト背景テクスチャ
	pTextureResultBack = pArgument_->pTexture_->Get( _T( "result/back.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_BACK ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_BACK ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureResultBack );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_BACK ].SetPosition( 320.0f, 0.0f, 0.0f );

	// リザルトロゴ
	Texture*	pTextureResultLogo = nullptr;		// ロゴテクスチャ
	pTextureResultLogo = pArgument_->pTexture_->Get( _T( "result/result_logo.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_LOGO ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_LOGO ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureResultLogo );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_LOGO ].SetPosition( 320.0f, 300.0f, 0.0f );

	// シンクロ率
	Texture*	pTextureSyncronize = nullptr;		// ロゴテクスチャ
	pTextureSyncronize = pArgument_->pTexture_->Get( _T( "result/synchronize.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureSyncronize );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].SetPosition( 280.0f, 100.0f, 0.0f );

	// 判定
	Texture*	pTextureJudge = nullptr;		// 判定テクスチャ
	float		heightJudge;					// 判定画像の高さ
	pTextureJudge = pArgument_->pTexture_->Get( _T( "result/judge.png" ) );
	for( int counterJudge = 0; counterJudge < 3; ++counterJudge )
	{
		result = pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].Initialize( 0 );
		if( result != 0 )
		{
			return result;
		}
		result = pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureJudge );
		if( result != 0 )
		{
			return result;
		}
		heightJudge = pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].GetScaleY();
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].SetScaleY( heightJudge / 4.0f );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].SetPositionTextureY( 0.25f * counterJudge );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].SetScaleTextureY( 4.0f );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 + counterJudge ].SetPosition( 200.0f, -100.0f * counterJudge, 0.0f );
	}

	// ランキングへ
	Texture*	pTextureToRanking = nullptr;		// ランキングへテクスチャ
	pTextureToRanking = pArgument_->pTexture_->Get( _T( "result/to_ranking.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_TO_RANKING ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_TO_RANKING ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureToRanking );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_TO_RANKING ].SetPosition( -500.0f, -305.0f, 0.0f );

	// タイトルへ
	Texture*	pTextureToTitle = nullptr;		// タイトルへテクスチャ
	pTextureToTitle = pArgument_->pTexture_->Get( _T( "result/to_title.png" ) );
	result = pObjectResult_[ IMAGE_RESULT_TO_TITLE ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_TO_TITLE ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureToTitle );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_TO_TITLE ].SetPosition( -220.0f, -305.0f, 0.0f );

	// ランキング画像オブジェクトの生成
	pObjectRanking_ = new Object2D[ IMAGE_RANKING_MAXIMUM ];
	if( pObjectRanking_ == nullptr )
	{
		return 1;
	}

	// ランキングロゴ
	Texture*	pTextureRankingLogo = nullptr;		// ロゴテクスチャ
	pTextureRankingLogo = pArgument_->pTexture_->Get( _T( "ranking/ranking_logo.png" ) );
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureRankingLogo );
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
		pObjectScoreRanking_[ counterRank ].SetEnableGraphic( false );
	}

	// リザルトオブジェクトの非表示
	DisableObjectResult();

	// ランキングオブジェクトの非表示
	DisableObjectRanking();

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

	// リザルト画像オブジェクトの開放
	delete[] pObjectResult_;
	pObjectResult_ = nullptr;

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
	PrintDebug( _T( "Timer : %05d\n" ), timerSceneGame_ );

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// 背景の表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_BACK )
	{
		pObjectResult_[ IMAGE_RESULT_BACK ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_BACK && timerSceneGame_ < TIME_RESULT_BEGIN_BACK + COUNT_RESULT_BEGIN_BACK )
	{
		float	proportion;		// 割合
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_BACK) ) / COUNT_RESULT_BEGIN_BACK;
		pObjectResult_[ IMAGE_RESULT_BACK ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
	}

	// ロゴの表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_LOGO )
	{
		pObjectResult_[ IMAGE_RESULT_LOGO ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_LOGO && timerSceneGame_ < TIME_RESULT_BEGIN_LOGO + COUNT_RESULT_BEGIN_LOGO )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_LOGO) ) / COUNT_RESULT_BEGIN_LOGO;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_LOGO ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_LOGO ].SetScale( pObjectResult_[ IMAGE_RESULT_LOGO ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_LOGO ].GetHeight() * scale, 1.0f );
	}

	// シンクロ率の表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_SYNCRONIZE )
	{
		pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_SYNCRONIZE && timerSceneGame_ < TIME_RESULT_BEGIN_SYNCRONIZE + COUNT_RESULT_BEGIN_SYNCRONIZE )
	{
		float	proportion;		// 割合
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_SYNCRONIZE) ) / COUNT_RESULT_BEGIN_SYNCRONIZE;
		pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_SYNCRONIZE ].SetPositionY( Utility::Easing( 90.0f, 100.0f, proportion ) );
	}

	// 判定0の表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_JUDGE_0 )
	{
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_JUDGE_0 && timerSceneGame_ < TIME_RESULT_BEGIN_JUDGE_0 + COUNT_RESULT_BEGIN_JUDGE_0 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_JUDGE_0) ) / COUNT_RESULT_BEGIN_JUDGE_0;
		scale = Utility::Easing( 1.5f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].SetScale( pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_JUDGE_0 ].GetHeight() / 4.0f * scale, 1.0f );
	}

	// 判定1の表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_JUDGE_1 )
	{
		pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_JUDGE_1 && timerSceneGame_ < TIME_RESULT_BEGIN_JUDGE_1 + COUNT_RESULT_BEGIN_JUDGE_1 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_JUDGE_1) ) / COUNT_RESULT_BEGIN_JUDGE_1;
		scale = Utility::Easing( 1.5f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].SetScale( pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_JUDGE_1 ].GetHeight() / 4.0f * scale, 1.0f );
	}

	// 判定2の表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_JUDGE_2 )
	{
		pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_JUDGE_2 && timerSceneGame_ < TIME_RESULT_BEGIN_JUDGE_2 + COUNT_RESULT_BEGIN_JUDGE_2 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_JUDGE_2) ) / COUNT_RESULT_BEGIN_JUDGE_2;
		scale = Utility::Easing( 1.25f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].SetScale( pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_JUDGE_2 ].GetHeight() / 4.0f * scale, 1.0f );
	}


	// ランキングへの表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_TO_RANKING )
	{
		pObjectResult_[ IMAGE_RESULT_TO_RANKING ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_TO_RANKING && timerSceneGame_ < TIME_RESULT_BEGIN_TO_RANKING + COUNT_RESULT_BEGIN_TO_RANKING )
	{
		float	proportion;		// 割合
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_TO_RANKING) ) / COUNT_RESULT_BEGIN_TO_RANKING;
		pObjectResult_[ IMAGE_RESULT_TO_RANKING ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
	}

	// タイトルへの表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_TO_TITLE )
	{
		pObjectResult_[ IMAGE_RESULT_TO_TITLE ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_TO_TITLE && timerSceneGame_ < TIME_RESULT_BEGIN_TO_TITLE + COUNT_RESULT_BEGIN_TO_TITLE )
	{
		float	proportion;		// 割合
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_TO_TITLE) ) / COUNT_RESULT_BEGIN_TO_TITLE;
		pObjectResult_[ IMAGE_RESULT_TO_TITLE ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
	}

	// ランキングへの点滅
	if( timerSceneGame_ >= TIME_RESULT_END )
	{
		float	proportion;		// 割合
		proportion = D3DX_PI * 2.0f * static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_TO_RANKING) % 120 ) / 120;
		pObjectResult_[ IMAGE_RESULT_TO_RANKING ].SetColorAlpha( 0.2f * cosf( proportion ) + 0.8f );
	}

	// タイトルへの点滅
	if( timerSceneGame_ >= TIME_RESULT_END )
	{
		float	proportion;		// 割合
		proportion = D3DX_PI * 2.0f * static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_TO_TITLE) % 120 ) / 120;
		pObjectResult_[ IMAGE_RESULT_TO_TITLE ].SetColorAlpha( 0.2f * cosf( proportion ) + 0.8f );
	}

	// タイマーの経過
	++timerSceneGame_;

	// 更新処理の切り替え
	if( pArgument_->pVirtualController_->IsTrigger( VC_DESIDE ) )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdateRanking;
	}
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

	// その他の画像を非表示にする
	if( timerSceneGame_ == 0 )
	{
		DisableObjectResult();
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
				break;
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
			pObjectScoreRanking_[ counterRank ].SetScoreFuture( pRankingScore_[ counterRank ] );
		}
	}

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_[ GraphicMain::CAMERA_GENERAL ].SetState( nullptr );
	}

	// ロゴの表示
	if( timerSceneGame_ == TIME_RANKING_BEGIN_LOGO )
	{
		pObjectRanking_[ IMAGE_RANKING_LOGO ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_LOGO && timerSceneGame_ < TIME_RANKING_BEGIN_LOGO + COUNT_RANKING_BEGIN_LOGO )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		float	width;			// 幅
		float	height;			// 高さ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_LOGO) ) / COUNT_RANKING_BEGIN_LOGO;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_LOGO ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_LOGO ].GetHeight() * scale;
		pObjectRanking_[ IMAGE_RANKING_LOGO ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_LOGO ].SetScale( width, height, 1.0f );
	}

	// ランク5の表示
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_5 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_5 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 4 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_5 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_5 + COUNT_RANKING_BEGIN_RANK_5 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		float	width;			// 幅
		float	height;			// 高さ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_5) ) / COUNT_RANKING_BEGIN_RANK_5;
		scale = Utility::Easing( 2.5f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_5 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_5 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_5 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_5 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 4 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 4 ].SetPos( -250.0f, 170.0f - 120.0f * 4, 0.0f );
	}

	// ランク4の表示
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_4 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_4 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 3 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_4 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_4 + COUNT_RANKING_BEGIN_RANK_4 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		float	width;			// 幅
		float	height;			// 高さ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_4) ) / COUNT_RANKING_BEGIN_RANK_4;
		scale = Utility::Easing( 2.5f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_4 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_4 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_4 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_4 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 3 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 3 ].SetPos( -250.0f, 170.0f - 120.0f * 3, 0.0f );
	}

	// ランク3の表示
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_3 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_3 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 2 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_3 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_3 + COUNT_RANKING_BEGIN_RANK_3 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		float	width;			// 幅
		float	height;			// 高さ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_3) ) / COUNT_RANKING_BEGIN_RANK_3;
		scale = Utility::Easing( 2.5f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_3 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_3 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_3 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_3 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 2 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 2 ].SetPos( -250.0f, 170.0f - 120.0f * 2, 0.0f );
	}

	// ランク2の表示
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_2 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_2 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 1 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_2 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_2 + COUNT_RANKING_BEGIN_RANK_2 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		float	width;			// 幅
		float	height;			// 高さ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_2) ) / COUNT_RANKING_BEGIN_RANK_2;
		scale = Utility::Easing( 2.5f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_2 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_2 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_2 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_2 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 1 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 1 ].SetPos( -250.0f, 170.0f - 120.0f * 1, 0.0f );
	}

	// ランク1の表示
	if( timerSceneGame_ == TIME_RANKING_BEGIN_RANK_1 )
	{
		pObjectRanking_[ IMAGE_RANKING_RANK_1 ].SetEnableGraphic( true );
		pObjectScoreRanking_[ 0 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RANKING_BEGIN_RANK_1 && timerSceneGame_ < TIME_RANKING_BEGIN_RANK_1 + COUNT_RANKING_BEGIN_RANK_1 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		float	width;			// 幅
		float	height;			// 高さ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RANKING_BEGIN_RANK_1) ) / COUNT_RANKING_BEGIN_RANK_1;
		scale = Utility::Easing( 4.0f, 1.0f, proportion );
		width = pObjectRanking_[ IMAGE_RANKING_RANK_1 ].GetWidth() * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_1 ].GetHeight() / 8.0f * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_1 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 0 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 0 ].SetPos( -250.0f, 170.0f - 120.0f * 0, 0.0f );
	}

	// タイマーの経過
	++timerSceneGame_;
}

//==============================================================================
// Brief  : リザルトオブジェクトを非表示にする
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::DisableObjectResult( void )
{
	// オブジェクトを非表示にする
	for( int counterObject = 0; counterObject < IMAGE_RESULT_MAXIMUM; ++counterObject )
	{
		pObjectResult_[ counterObject ].SetEnableGraphic( false );
	}
}

//==============================================================================
// Brief  : ランキングオブジェクトを非表示にする
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::DisableObjectRanking( void )
{
	// オブジェクトを非表示にする
	for( int counterObject = 0; counterObject < IMAGE_RANKING_MAXIMUM; ++counterObject )
	{
		pObjectRanking_[ counterObject ].SetEnableGraphic( false );
	}

	// スコアを非表示にする
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		pObjectScoreRanking_[ counterRank ].SetPos( 2500.0f, 170.0f - 120.0f * counterRank, 0.0f );
	}
}
