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
#include "../framework/system/Fade.h"
#include "../graphic/graphic/GraphicMain.h"
#include "../object/Object2D.h"
#include "../object/ObjectScore.h"
#include "../object/ObjectSkinMesh.h"
#include "../system/camera/CameraStateSpline.h"
#include "../system/combo/combo.h"
#include "../system/gage/gage.h"
#include "../system/SceneArgumentMain.h"
#include "../system/gage/gage.h"

// テスト用
#include "../framework/light/LightPoint.h"
#include "../framework/light/ManagerLight.h"
#include "../framework/resource/ManagerModel.h"
#include "../object/ObjectModel.h"
#include "../object/ObjectModelMaterial.h"
#include "../system/point/ManagerPoint.h"
#include "../system/ManagerSceneMain.h"
#include "../system/fireworksUI/fireworksUI.h"

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

	// ゲームセクション間カメラ処理の生成
	TCHAR	pNameFileState[ SECTION_MAXIMUM - 1 ][ _MAX_PATH ] =
	{
		_T( "data/camera/Section12.txt" ),
		_T( "data/camera/Section23.txt" )
	};
	pStateCameraBetween_ = new CameraStateSpline[ SECTION_MAXIMUM - 1 ];
	if( pStateCameraBetween_ == nullptr )
	{
		return 1;
	}
	for( int counterState = 0; counterState < SECTION_MAXIMUM - 1; ++counterState )
	{
		result = pStateCameraBetween_[ counterState ].Initialize( &pNameFileState[ counterState ][ 0 ] );
		if( result != 0 )
		{
			return result;
		}
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

	// フォントテクスチャの読み込み
	Texture*	pTextureFont = nullptr;		// フォントテクスチャ
	pTextureFont = pArgument_->pTexture_->Get( _T( "common/font_edge.png" ) );

	// 枠付き数字テクスチャの読み込み
	Texture*	pTextureNumberEdge = nullptr;		// 数字テクスチャ
	pTextureNumberEdge = pArgument_->pTexture_->Get( _T( "common/numberEdge.png" ) );

	// カウントダウン画像オブジェクトの生成
	TCHAR	pNameFileTextureCount[][ _MAX_PATH ] =
	{
		_T( "game/count3.png" ),
		_T( "game/count2.png" ),
		_T( "game/count1.png" )
	};
	Effect*	pEffect2D = nullptr;		// 2D描画エフェクト
	pEffect2D = pArgument_->pEffect_->Get( "Polygon2D.fx" );
	pObjectCount_ = new Object2D[ IMAGE_COUNT_MAXIMUM ];
	if( pObjectCount_ == nullptr )
	{
		return 1;
	}
	for( int counterCount = 0; counterCount < IMAGE_COUNT_MAXIMUM - 1; ++counterCount )
	{
		Texture*	pTextureCount = nullptr;		// テクスチャ
		pTextureCount = pArgument_->pTexture_->Get( &pNameFileTextureCount[ counterCount ][ 0 ] );
		result = pObjectCount_[ counterCount ].Initialize( 0 );
		if( result != 0 )
		{
			return result;
		}
		result = pObjectCount_[ counterCount ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureCount );
		if( result != 0 )
		{
			return result;
		}
	}

	// 演武開始
	result = pObjectCount_[ IMAGE_COUNT_START ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectCount_[ IMAGE_COUNT_START ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureFont );
	if( result != 0 )
	{
		return result;
	}
	pObjectCount_[ IMAGE_COUNT_START ].SetPosition( 0.0f, 0.0f, 0.0f );
	pObjectCount_[ IMAGE_COUNT_START ].SetScale( 4.0f * 256.0f, 1.0f * 256.0f, 1.0f );
	pObjectCount_[ IMAGE_COUNT_START ].SetWidth( 4.0f * 256.0f );
	pObjectCount_[ IMAGE_COUNT_START ].SetHeight( 1.0f * 256.0f );
	pObjectCount_[ IMAGE_COUNT_START ].SetScaleTexture( 16.0f / 4.0f, 16.0f / 1.0f );
	pObjectCount_[ IMAGE_COUNT_START ].SetPositionTexture( 0.0f / 16.0f, 2.0f / 16.0f );

	// リザルト画像オブジェクトの生成
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

	// リザルトゲージオブジェクト生成
	Texture*	pTextureGageBar = nullptr;			// テクスチャ
	Texture*	pTextureGageBase = nullptr;			// テクスチャ
	Texture*	pTextureGageEffect = nullptr;		// テクスチャ
	Texture*	pTextureGageNumber = nullptr;		// テクスチャ
	Effect*		pEffectGage = nullptr;				// エフェクト
	Effect*		pEffectGageAdd = nullptr;			// エフェクト
	pTextureGageBar = pArgument_->pTexture_->Get( _T( "game/gageBar.png" ) );
	pTextureGageBase = pArgument_->pTexture_->Get( _T( "game/gageBase.png" ) );
	pTextureGageEffect = pArgument_->pTexture_->Get( _T( "game/effect.png" ) );
	pTextureGageNumber = pArgument_->pTexture_->Get( _T( "common/number.png" ) );
	pEffectGage = pArgument_->pEffect_->Get( _T( "Polygon2D.fx" ) );
	pEffectGageAdd = pArgument_->pEffect_->Get( _T( "Polygon2DAdd.fx" ) );
	pObjectGageResult_ = new Gage();
	pObjectGageResult_->Initialize( pArgument_->pDevice_, pArgument_->pEffectParameter_, pEffectGage, pEffectGageAdd,
		pTextureGageBar, pTextureGageBase, pTextureGageEffect, pTextureGageNumber );
	pObjectGageResult_->setPosition( 195.0f, -50.0f, 0.0f );
	pObjectGageResult_->SetEnableGraphicPercent( false );

	// リザルトロゴ
	result = pObjectResult_[ IMAGE_RESULT_LOGO ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_LOGO ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureFont );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_LOGO ].SetPosition( 320.0f, 55.0f, 0.0f );
	pObjectResult_[ IMAGE_RESULT_LOGO ].SetScale( 4.0f * 64.0f, 1.0f * 64.0f, 1.0f );
	pObjectResult_[ IMAGE_RESULT_LOGO ].SetWidth( 4.0f * 64.0f );
	pObjectResult_[ IMAGE_RESULT_LOGO ].SetHeight( 1.0f * 64.0f );
	pObjectResult_[ IMAGE_RESULT_LOGO ].SetScaleTexture( 16.0f / 4.0f, 16.0f / 1.0f );
	pObjectResult_[ IMAGE_RESULT_LOGO ].SetPositionTexture( 0.0f / 16.0f, 4.0f / 16.0f );

	// パーセント
	result = pObjectResult_[ IMAGE_RESULT_PERCENT ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_PERCENT ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureFont );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_PERCENT ].SetPosition( 490.0f, -15.0f, 0.0f );
	pObjectResult_[ IMAGE_RESULT_PERCENT ].SetScale( 1.0f * 64.0f, 1.0f * 64.0f, 1.0f );
	pObjectResult_[ IMAGE_RESULT_PERCENT ].SetWidth( 1.0f * 64.0f );
	pObjectResult_[ IMAGE_RESULT_PERCENT ].SetHeight( 1.0f * 64.0f );
	pObjectResult_[ IMAGE_RESULT_PERCENT ].SetScaleTexture( 16.0f / 1.0f, 16.0f / 1.0f );
	pObjectResult_[ IMAGE_RESULT_PERCENT ].SetPositionTexture( 0.0f / 16.0f, 3.0f / 16.0f );

	// 連発
	result = pObjectResult_[ IMAGE_RESULT_COMBO ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_COMBO ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureFont );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_COMBO ].SetPosition( 470.0f, -85.0f, 0.0f );
	pObjectResult_[ IMAGE_RESULT_COMBO ].SetScale( 2.0f * 64.0f, 1.0f * 64.0f, 1.0f );
	pObjectResult_[ IMAGE_RESULT_COMBO ].SetWidth( 2.0f * 64.0f );
	pObjectResult_[ IMAGE_RESULT_COMBO ].SetHeight( 1.0f * 64.0f );
	pObjectResult_[ IMAGE_RESULT_COMBO ].SetScaleTexture( 16.0f / 2.0f, 16.0f / 1.0f );
	pObjectResult_[ IMAGE_RESULT_COMBO ].SetPositionTexture( 4.0f / 16.0f, 4.0f / 16.0f );

	// スコア
	result = pObjectResult_[ IMAGE_RESULT_SCORE ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectResult_[ IMAGE_RESULT_SCORE ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureFont );
	if( result != 0 )
	{
		return result;
	}
	pObjectResult_[ IMAGE_RESULT_SCORE ].SetPosition( 210.0f, -145.0f, 0.0f );
	pObjectResult_[ IMAGE_RESULT_SCORE ].SetScale( 4.0f * 48.0f, 1.0f * 48.0f, 1.0f );
	pObjectResult_[ IMAGE_RESULT_SCORE ].SetWidth( 4.0f * 48.0f );
	pObjectResult_[ IMAGE_RESULT_SCORE ].SetHeight( 1.0f * 48.0f );
	pObjectResult_[ IMAGE_RESULT_SCORE ].SetScaleTexture( 16.0f / 4.0f, 16.0f / 1.0f );
	pObjectResult_[ IMAGE_RESULT_SCORE ].SetPositionTexture( 0.0f / 16.0f, 0.0f / 16.0f );

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

	// リザルトシンクロ率オブジェクト
	pObjectSynchronizeResult_ = new ObjectScore();
	if( pObjectSynchronizeResult_ == nullptr )
	{
		return 1;
	}
	result = pObjectSynchronizeResult_->Initialize( 0, 3 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectSynchronizeResult_->CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureNumberEdge );
	if( result != 0 )
	{
		return result;
	}
	pObjectSynchronizeResult_->SetPos( 340.0f, -15.0f, 0.0f );
	pObjectSynchronizeResult_->SetSizeX( static_cast< float >( pTextureNumberEdge->width_ ) / 16.0f );
	pObjectSynchronizeResult_->SetSizeY( static_cast< float >( pTextureNumberEdge->height_ ) / 2.0f );

	// リザルトコンボオブジェクト
	pObjectComboResult_ = new ObjectScore();
	if( pObjectComboResult_ == nullptr )
	{
		return 1;
	}
	result = pObjectComboResult_->Initialize( 0, 3 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectComboResult_->CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureNumberEdge );
	if( result != 0 )
	{
		return result;
	}
	pObjectComboResult_->SetPos( 290.0f, -85.0f, 0.0f );
	pObjectComboResult_->SetSizeX( 36.0f );
	pObjectComboResult_->SetSizeY( 36.0f );

	// リザルトスコアオブジェクト
	pObjectScoreResult_ = new ObjectScore();
	if( pObjectScoreResult_ == nullptr )
	{
		return 1;
	}
	result = pObjectScoreResult_->Initialize( 0, 10 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectScoreResult_->CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureNumberEdge );
	if( result != 0 )
	{
		return result;
	}
	pObjectScoreResult_->SetPos( 175.0f, -195.0f, 0.0f );
	pObjectScoreResult_->SetSizeX( 24.0f );
	pObjectScoreResult_->SetSizeY( 24.0f );

	// ランキング画像オブジェクトの生成
	pObjectRanking_ = new Object2D[ IMAGE_RANKING_MAXIMUM ];
	if( pObjectRanking_ == nullptr )
	{
		return 1;
	}

	// ランキングロゴ
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}
	result = pObjectRanking_[ IMAGE_RANKING_LOGO ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureFont );
	if( result != 0 )
	{
		return result;
	}
	pObjectRanking_[ IMAGE_RANKING_LOGO ].SetPosition( 0.0f, 300.0f, 0.0f );
	pObjectRanking_[ IMAGE_RANKING_LOGO ].SetScale( 4.0f * 64.0f, 1.0f * 64.0f, 1.0f );
	pObjectRanking_[ IMAGE_RANKING_LOGO ].SetWidth( 4.0f * 64.0f );
	pObjectRanking_[ IMAGE_RANKING_LOGO ].SetHeight( 1.0f * 64.0f );
	pObjectRanking_[ IMAGE_RANKING_LOGO ].SetScaleTexture( 16.0f / 4.0f, 16.0f / 1.0f );
	pObjectRanking_[ IMAGE_RANKING_LOGO ].SetPositionTexture( 0.0f / 16.0f, 4.0f / 16.0f );

	// ランク
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		result = pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].Initialize( 0 );
		if( result != 0 )
		{
			return result;
		}
		result = pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].CreateGraphic( 0, pArgument_->pEffectParameter_, pEffect2D, pTextureNumberEdge );
		if( result != 0 )
		{
			return result;
		}
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetPosition( -500.0f, 190.0f - 120.0f * counterRank, 0.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetScaleX( 128.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetScaleY( 128.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetScaleTextureX( 10.0f );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 + counterRank ].SetPositionTextureX( 1.0f / 10.0f * (counterRank + 1) );
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
		pObjectScoreRanking_[ counterRank ].SetSizeX( static_cast< float >( pTextureNumber->width_ ) / 10.0f );
		pObjectScoreRanking_[ counterRank ].SetEnableGraphic( false );
	}

	// カウントダウンオブジェクトの非表示
	DisableObjectCount();

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

	// リザルトスコアオブジェクトの開放
	delete pObjectScoreResult_;
	pObjectScoreResult_ = nullptr;

	// リザルトコンボオブジェクトの開放
	delete pObjectComboResult_;
	pObjectComboResult_ = nullptr;

	// リザルトシンクロ率オブジェクトの開放
	delete pObjectSynchronizeResult_;
	pObjectSynchronizeResult_ = nullptr;

	// リザルトゲージオブジェクトの開放
	delete pObjectGageResult_;
	pObjectGageResult_ = nullptr;

	// リザルト画像オブジェクトの開放
	delete[] pObjectResult_;
	pObjectResult_ = nullptr;

	// カウントダウン画像オブジェクトの開放
	delete[] pObjectCount_;
	pObjectCount_ = nullptr;

	// リザルト前カメラ処理の開放
	delete pStateCameraResult_;
	pStateCameraResult_ = nullptr;

	// ゲームセクション間カメラ処理の開放
	delete[] pStateCameraBetween_;
	pStateCameraBetween_ = nullptr;

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
	pStateCameraBetween_ = nullptr;
	pStateCameraResult_ = nullptr;
	timerSceneGame_ = 0;
	pObjectCount_ = nullptr;
	pObjectResult_ = nullptr;
	pObjectGageResult_ = nullptr;
	pObjectSynchronizeResult_ = nullptr;
	pObjectComboResult_ = nullptr;
	pObjectScoreResult_ = nullptr;
	for( int counterRank = 0; counterRank < MAXIMUM_RANK; ++counterRank )
	{
		pRankingScore_[ counterRank ] = 0;
	}
	indexRank_ = 0;
	pObjectRanking_ = nullptr;
	pObjectScoreRanking_ = nullptr;
	indexSection_ = 0;
	maximumCombo_ = 0;
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
		pCamera_->SetState( pStateCameraPrevious_ );
	}

	// タイマーの経過
	++timerSceneGame_;

	// 更新処理の切り替え
	if( timerSceneGame_ >= pStateCameraPrevious_->GetCountFrame() )
	{
		timerSceneGame_ = 0;
		pCamera_->SetState( NULL );


		fpUpdate = &SceneGame::calibrationUpdate;

		//	UI関係を可視化する
		calibrationWiimoteIllust->SetEnableGraphic(true);
		calibrationWiimote->SetEnableGraphic(true);

		fireworksUI->SetEnableGraphic(true);
		stringScore->SetEnableGraphic(true);
		score->SetEnableGraphic(true);
		gage->SetEnableGraphic(true);
		//	UI関係を可視化する
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
		pCamera_->SetState( nullptr );
	}

	// 3
	if( timerSceneGame_ == 0 )
	{
		pObjectCount_[ IMAGE_COUNT_3 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= 0 && timerSceneGame_ <= 60 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - 0) ) / 60;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectCount_[ IMAGE_COUNT_3 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectCount_[ IMAGE_COUNT_3 ].SetScale( pObjectCount_[ IMAGE_COUNT_3 ].GetWidth() * scale, pObjectCount_[ IMAGE_COUNT_3 ].GetHeight() * scale, 1.0f );
	}
	if( timerSceneGame_ >= 80 && timerSceneGame_ <= 100 )
	{
		float	proportion;		// 割合
		proportion = static_cast< float >( (timerSceneGame_ - 80) ) / 20;
		pObjectCount_[ IMAGE_COUNT_3 ].SetColorAlpha( Utility::Easing( 1.0f, 0.0f, proportion ) );
	}

	// 2
	if( timerSceneGame_ == 60 )
	{
		pObjectCount_[ IMAGE_COUNT_2 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= 60 && timerSceneGame_ <= 120 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - 60) ) / 60;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectCount_[ IMAGE_COUNT_2 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectCount_[ IMAGE_COUNT_2 ].SetScale( pObjectCount_[ IMAGE_COUNT_2 ].GetWidth() * scale, pObjectCount_[ IMAGE_COUNT_2 ].GetHeight() * scale, 1.0f );
	}
	if( timerSceneGame_ >= 140 && timerSceneGame_ <= 160 )
	{
		float	proportion;		// 割合
		proportion = static_cast< float >( (timerSceneGame_ - 140) ) / 20;
		pObjectCount_[ IMAGE_COUNT_2 ].SetColorAlpha( Utility::Easing( 1.0f, 0.0f, proportion ) );
	}

	// 1
	if( timerSceneGame_ == 120 )
	{
		pObjectCount_[ IMAGE_COUNT_1 ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= 120 && timerSceneGame_ <= 180 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - 120) ) / 60;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectCount_[ IMAGE_COUNT_1 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectCount_[ IMAGE_COUNT_1 ].SetScale( pObjectCount_[ IMAGE_COUNT_1 ].GetWidth() * scale, pObjectCount_[ IMAGE_COUNT_1 ].GetHeight() * scale, 1.0f );
	}
	if( timerSceneGame_ >= 200 && timerSceneGame_ <= 220 )
	{
		float	proportion;		// 割合
		proportion = static_cast< float >( (timerSceneGame_ - 200) ) / 20;
		pObjectCount_[ IMAGE_COUNT_1 ].SetColorAlpha( Utility::Easing( 1.0f, 0.0f, proportion ) );
	}

	// 演武開始
	if( timerSceneGame_ == 180 )
	{
		pObjectCount_[ IMAGE_COUNT_START ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= 180 && timerSceneGame_ <= 240 )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - 180) ) / 60;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectCount_[ IMAGE_COUNT_START ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectCount_[ IMAGE_COUNT_START ].SetScale( pObjectCount_[ IMAGE_COUNT_START ].GetWidth() * scale, pObjectCount_[ IMAGE_COUNT_START ].GetHeight() * scale, 1.0f );
	}
	if( timerSceneGame_ >= 260 && timerSceneGame_ <= 290 )
	{
		float	proportion;		// 割合
		proportion = static_cast< float >( (timerSceneGame_ - 260) ) / 30;
		pObjectCount_[ IMAGE_COUNT_START ].SetColorAlpha( Utility::Easing( 1.0f, 0.0f, proportion ) );
	}

	// タイマーの経過
	++timerSceneGame_;

	// 更新処理の切り替え
	if( timerSceneGame_ >= 290 )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::normalUpdate;
	}
}

//==============================================================================
// Brief  : ゲームセクション間更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::UpdateBetweenSection( void )
{
	// テスト
	PrintDebug( _T( "UpdateBetweenSection\n" ) );
	PrintDebug( _T( "Timer        : %05d\n" ), timerSceneGame_ );
	PrintDebug( _T( "IndexSection : %05d\n" ), indexSection_ );

	// エラー処理
	if( indexSection_ >= SECTION_MAXIMUM - 1 )
	{
		indexSection_ = 0;
	}

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_->SetState( &pStateCameraBetween_[ indexSection_ ] );
	}

	// セクション番号を進める
	if( timerSceneGame_ == 0 )
	{
		++indexSection_;
	}

	// タイマーの経過
	++timerSceneGame_;

	// 更新処理の切り替え
	int		indexCameraState;		// カメラ処理番号
	indexCameraState = indexSection_ - 1;
	if( indexCameraState < 0 )
	{
		indexCameraState = SECTION_MAXIMUM - 2;
	}
	if( timerSceneGame_ >= pStateCameraBetween_[ indexCameraState ].GetCountFrame() )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::normalUpdate;
		pCamera_->SetState( nullptr );
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
		pCamera_->SetState( nullptr );
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
		pCamera_->SetState( pStateCameraResult_ );
	}

	// タイマーの経過
	++timerSceneGame_;

	// 更新処理の切り替え
	if( timerSceneGame_ >= pStateCameraResult_->GetCountFrame() )
	{
		timerSceneGame_ = 0;
		fpUpdate = &SceneGame::UpdateResult;
	}
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

#ifdef _DEBUG
	// オブジェクトの移動
	Object*	pObject = nullptr;		// 移動対象オブジェクト
	float	velocity;				// 移動速度
	pObject = pObjectScoreResult_;
	if( pArgument_->pKeyboard_->IsPress( DIK_LCONTROL ) )
	{
		velocity = 10.0f;
	}
	else if( pArgument_->pKeyboard_->IsPress( DIK_LSHIFT ) )
	{
		velocity = 100.0f;
	}
	else
	{
		velocity = 1.0f;
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_W, 30, 1 ) )
	{
		pObject->AddPositionY( velocity );
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_S, 30, 1 ) )
	{
		pObject->AddPositionY( -velocity );
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_A, 30, 1 ) )
	{
		pObject->AddPositionX( -velocity );
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_D, 30, 1 ) )
	{
		pObject->AddPositionX( velocity );
	}
	PrintDebug( _T( "*--------------------------------------*\n" ) );
	PrintDebug( _T( "| デバッグオブジェクト                 |\n" ) );
	PrintDebug( _T( "*--------------------------------------*\n" ) );
	PrintDebug( _T( "座標 ： ( %11.6f, %11.6f, %11.6f )\n" ), pObject->GetPositionX(), pObject->GetPositionY(), pObject->GetPositionZ() );
	PrintDebug( _T( "回転 ： ( %11.6f, %11.6f, %11.6f )\n" ), 180.0f / D3DX_PI * pObject->GetRotationX(), 180.0f / D3DX_PI * pObject->GetRotationY(), 180.0f / D3DX_PI * pObject->GetRotationZ() );
	PrintDebug( _T( "拡縮 ： ( %11.6f, %11.6f, %11.6f )\n" ), pObject->GetScaleX(), pObject->GetScaleY(), pObject->GetScaleZ() );
#endif

	// カメラの処理を設定
	if( timerSceneGame_ == 0 )
	{
		pCamera_->SetState( nullptr );
	}

	// 背景の表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_BACK )
	{
		pObjectResult_[ IMAGE_RESULT_BACK ].SetEnableGraphic( true );
		pObjectResult_[ IMAGE_RESULT_PERCENT ].SetEnableGraphic( true );
		pObjectResult_[ IMAGE_RESULT_COMBO ].SetEnableGraphic( true );
		pObjectGageResult_->SetEnableGraphic2( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_BACK && timerSceneGame_ <= TIME_RESULT_BEGIN_BACK + COUNT_RESULT_BEGIN_BACK )
	{
		// 透明度の決定
		float	proportion;		// 割合
		float	alpha;			// 透明度
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_BACK) ) / COUNT_RESULT_BEGIN_BACK;
		alpha = Utility::Easing( 0.0f, 1.0f, proportion );

		// 看板
		pObjectResult_[ IMAGE_RESULT_BACK ].SetColorAlpha( alpha );

		// ゲージ
		pObjectGageResult_->SetColorAlpha( alpha );

		// シンクロ率
		pObjectResult_[ IMAGE_RESULT_PERCENT ].SetColorAlpha( alpha );
		pObjectSynchronizeResult_->SetColorAlpha( alpha );

		// コンボ
		pObjectResult_[ IMAGE_RESULT_COMBO ].SetColorAlpha( alpha );
		pObjectComboResult_->SetColorAlpha( alpha );

		// スコア
		pObjectScoreResult_->SetColorAlpha( alpha );
	}

	// ロゴの表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_LOGO )
	{
		pObjectResult_[ IMAGE_RESULT_LOGO ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_LOGO && timerSceneGame_ <= TIME_RESULT_BEGIN_LOGO + COUNT_RESULT_BEGIN_LOGO )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_LOGO) ) / COUNT_RESULT_BEGIN_LOGO;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_LOGO ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_LOGO ].SetScale( pObjectResult_[ IMAGE_RESULT_LOGO ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_LOGO ].GetHeight() * scale, 1.0f );
	}

	// シンクロ率の表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_GAGE )
	{
		pObjectSynchronizeResult_->SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_GAGE && timerSceneGame_ <= TIME_RESULT_BEGIN_GAGE + COUNT_RESULT_BEGIN_GAGE )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_GAGE) ) / COUNT_RESULT_BEGIN_GAGE;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectGageResult_->setPercent( proportion * gage->getPercent() );
		pObjectGageResult_->setPercentFuture( proportion * gage->getPercent() );
		pObjectSynchronizeResult_->SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectSynchronizeResult_->SetScore( static_cast< int >( proportion * gage->getPercent() ) );
		pObjectSynchronizeResult_->SetScoreFuture( static_cast< int >( proportion * gage->getPercent() ) );
		pObjectSynchronizeResult_->SetSize( 48.0f * scale, 48.0f * scale, 1.0f );
		pObjectSynchronizeResult_->SetPos( 407.0f - 1.5f * 48.0f * scale, -39.0f + 24.0f * scale, 0.0f );
	}

	// コンボの表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_COMBO )
	{
		pObjectComboResult_->SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_COMBO && timerSceneGame_ <= TIME_RESULT_BEGIN_COMBO + COUNT_RESULT_BEGIN_COMBO )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_COMBO) ) / COUNT_RESULT_BEGIN_COMBO;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectComboResult_->SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectComboResult_->SetScore( static_cast< int >( proportion * maximumCombo_ ) );
		pObjectComboResult_->SetScoreFuture( static_cast< int >( proportion * maximumCombo_ ) );
		pObjectComboResult_->SetSize( 48.0f * scale, 48.0f * scale, 1.0f );
		pObjectComboResult_->SetPos( 357.0f - 1.5f * 48.0f * scale, -109.0f + 24.0f * scale, 0.0f );
	}

	// スコア文字の表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_SCORE_STRING )
	{
		pObjectResult_[ IMAGE_RESULT_SCORE ].SetEnableGraphic( true );
		pObjectScoreResult_->SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_SCORE_STRING && timerSceneGame_ <= TIME_RESULT_BEGIN_SCORE_STRING + COUNT_RESULT_BEGIN_SCORE_STRING )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_SCORE_STRING) ) / COUNT_RESULT_BEGIN_SCORE_STRING;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectResult_[ IMAGE_RESULT_SCORE ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectResult_[ IMAGE_RESULT_SCORE ].SetScale( pObjectResult_[ IMAGE_RESULT_SCORE ].GetWidth() * scale, pObjectResult_[ IMAGE_RESULT_SCORE ].GetHeight() * scale, 1.0f );
	}

	// スコアの表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_SCORE )
	{
		pObjectResult_[ IMAGE_RESULT_SCORE ].SetEnableGraphic( true );
		pObjectScoreResult_->SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_SCORE && timerSceneGame_ <= TIME_RESULT_BEGIN_SCORE + COUNT_RESULT_BEGIN_SCORE )
	{
		float	proportion;		// 割合
		float	scale;			// 大きさ
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_SCORE) ) / COUNT_RESULT_BEGIN_SCORE;
		scale = Utility::Easing( 2.0f, 1.0f, proportion );
		pObjectScoreResult_->SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreResult_->SetScore( static_cast< int >( proportion * score->GetScore() ) );
		pObjectScoreResult_->SetScoreFuture( static_cast< int >( proportion * score->GetScore() ) );
		pObjectScoreResult_->SetSize( 36.0f * scale, 36.0f * scale, 1.0f );
		pObjectScoreResult_->SetPos( 355.0f - 5.0f * 36.0f * scale, -213.0f + 18.0f * scale, 0.0f );
	}

	// ランキングへの表示
	if( timerSceneGame_ == TIME_RESULT_BEGIN_TO_RANKING )
	{
		pObjectResult_[ IMAGE_RESULT_TO_RANKING ].SetEnableGraphic( true );
	}
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_TO_RANKING && timerSceneGame_ <= TIME_RESULT_BEGIN_TO_RANKING + COUNT_RESULT_BEGIN_TO_RANKING )
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
	if( timerSceneGame_ >= TIME_RESULT_BEGIN_TO_TITLE && timerSceneGame_ <= TIME_RESULT_BEGIN_TO_TITLE + COUNT_RESULT_BEGIN_TO_TITLE )
	{
		float	proportion;		// 割合
		proportion = static_cast< float >( (timerSceneGame_ - TIME_RESULT_BEGIN_TO_TITLE) ) / COUNT_RESULT_BEGIN_TO_TITLE;
		pObjectResult_[ IMAGE_RESULT_TO_TITLE ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
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
		pCamera_->SetState( nullptr );
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
		width = pObjectRanking_[ IMAGE_RANKING_RANK_5 ].GetWidth() / 10.0f * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_5 ].GetHeight() * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_5 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_5 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 4 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 4 ].SetPos( -250.0f, 190.0f - 120.0f * 4, 0.0f );
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
		width = pObjectRanking_[ IMAGE_RANKING_RANK_4 ].GetWidth() / 10.0f * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_4 ].GetHeight() * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_4 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_4 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 3 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 3 ].SetPos( -250.0f, 190.0f - 120.0f * 3, 0.0f );
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
		width = pObjectRanking_[ IMAGE_RANKING_RANK_3 ].GetWidth() / 10.0f * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_3 ].GetHeight() * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_3 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_3 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 2 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 2 ].SetPos( -250.0f, 190.0f - 120.0f * 2, 0.0f );
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
		width = pObjectRanking_[ IMAGE_RANKING_RANK_2 ].GetWidth() / 10.0f * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_2 ].GetHeight() * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_2 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_2 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 1 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 1 ].SetPos( -250.0f, 190.0f - 120.0f * 1, 0.0f );
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
		width = pObjectRanking_[ IMAGE_RANKING_RANK_1 ].GetWidth() / 10.0f * scale;
		height = pObjectRanking_[ IMAGE_RANKING_RANK_1 ].GetHeight() * scale;
		pObjectRanking_[ IMAGE_RANKING_RANK_1 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectRanking_[ IMAGE_RANKING_RANK_1 ].SetScale( width, height, 1.0f );
		pObjectScoreRanking_[ 0 ].SetColorAlpha( Utility::Easing( 0.0f, 1.0f, proportion ) );
		pObjectScoreRanking_[ 0 ].SetPos( -250.0f, 190.0f - 120.0f * 0, 0.0f );
	}

	// タイマーの経過
	++timerSceneGame_;

	// タイトルへ戻る
	if( pArgument_->pVirtualController_->IsTrigger( VC_DESIDE ) )
	{
		if( pArgument_->pFade_->GetState() != Fade::STATE_OUT_WHILE )
		{
			pArgument_->pFade_->FadeOut( 20 );
		}
	}
	if( pArgument_->pFade_->GetState() == Fade::STATE_OUT_END )
	{
		SetSceneNext( ManagerSceneMain::TYPE_TITLE );
		SetIsEnd( true );
	}
}

//==============================================================================
// Brief  : テスト更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::UpdateTest( void )
{
	// オブジェクトの移動
	Object*	pObject = nullptr;		// 移動対象オブジェクト
	float	velocity;				// 移動速度
	pObject = gate;
	if( pArgument_->pKeyboard_->IsPress( DIK_LCONTROL ) )
	{
		velocity = 10.0f;
	}
	else if( pArgument_->pKeyboard_->IsPress( DIK_LSHIFT ) )
	{
		velocity = 100.0f;
	}
	else
	{
		velocity = 1.0f;
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_W, 30, 1 ) )
	{
		pObject->AddPositionZ( velocity );
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_S, 30, 1 ) )
	{
		pObject->AddPositionZ( -velocity );
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_A, 30, 1 ) )
	{
		pObject->AddPositionX( velocity );
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_D, 30, 1 ) )
	{
		pObject->AddPositionX( -velocity );
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_Q, 30, 1 ) )
	{
		pObject->AddPositionY( velocity );
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_E, 30, 1 ) )
	{
		pObject->AddPositionY( -velocity );
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_Z, 30, 1 ) )
	{
		pObject->AddRotationY( 1.0f * D3DX_PI / 180.0f );
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_X, 30, 1 ) )
	{
		pObject->AddRotationY( -1.0f * D3DX_PI / 180.0f );
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_C, 30, 1 ) )
	{
		pObject->AddScale( 1.0f, 1.0f, 1.0f );
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_V, 30, 1 ) )
	{
		pObject->AddScale( -1.0f, -1.0f, -1.0f );
	}
	PrintDebug( _T( "*--------------------------------------*\n" ) );
	PrintDebug( _T( "| デバッグオブジェクト                 |\n" ) );
	PrintDebug( _T( "*--------------------------------------*\n" ) );
	PrintDebug( _T( "座標 ： ( %11.6f, %11.6f, %11.6f )\n" ), pObject->GetPositionX(), pObject->GetPositionY(), pObject->GetPositionZ() );
	PrintDebug( _T( "回転 ： ( %11.6f, %11.6f, %11.6f )\n" ), 180.0f / D3DX_PI * pObject->GetRotationX(), 180.0f / D3DX_PI * pObject->GetRotationY(), 180.0f / D3DX_PI * pObject->GetRotationZ() );
	PrintDebug( _T( "拡縮 ： ( %11.6f, %11.6f, %11.6f )\n" ), pObject->GetScaleX(), pObject->GetScaleY(), pObject->GetScaleZ() );

	// 点光源テスト
	D3DXVECTOR3	pPositionPointTest[ 3 ] =
	{
		//	水車
		D3DXVECTOR3( 260.0f, 1000.0f, 3540.0f ),

		//	家
		D3DXVECTOR3( -2700.0f, 1000.0f, 2570.0f ),

		//	橋
		D3DXVECTOR3( 1080.0f, 1000.0f, -2750.0f )
	};
	for( int counterPoint = 0; counterPoint < 3; ++counterPoint )
	{
		managerPoint->Add( 20, pPositionPointTest[ counterPoint ], D3DXCOLOR( 0.8f, 0.6f, 0.25f, 1.0f ), 50.0f,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ), -2.0f, 1 );
	}

	// 点光源テスト
	static LightPoint*	pLightTest = nullptr;		// ポイントライト
	static D3DXVECTOR3	attenuationTest;			// 減衰率
	bool				needsSetLight;				// ライト設定フラグ
	int					indexPoint;					// 場所番号
	needsSetLight = false;
	if( timerSceneGame_ <= 0 && pLightTest == nullptr )
	{
		for( int counterPoint = 0; counterPoint < 3; ++counterPoint )
		{
			if( pArgument_->pKeyboard_->IsTrigger( DIK_1 + counterPoint ) )
			{
				needsSetLight = true;
				indexPoint = counterPoint;
			}
		}
	}
	if( needsSetLight )
	{
		// タイマーの経過
		timerSceneGame_ = 0;

		// ライトの設定（減衰率の参考にするお）
		attenuationTest = D3DXVECTOR3( 0.0f, 0.00028f, 0.00000005f );
		pLightTest = pArgument_->pLight_->GetLightPoint();
		pLightTest->Set( D3DXCOLOR( 1.0f, 0.7f, 0.2f, 1.0f ), D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ), pPositionPointTest[ indexPoint ], D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );
	}

	// 減衰率の調整
	if( pArgument_->pKeyboard_->IsRepeat( DIK_K, 30, 1 ) )
	{
		attenuationTest.y -= 0.000001f;
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_L, 30, 1 ) )
	{
		attenuationTest.y += 0.000001f;
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_COMMA, 30, 1 ) )
	{
		attenuationTest.z -= 0.00000001f;
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_PERIOD, 30, 1 ) )
	{
		attenuationTest.z += 0.00000001f;
	}
	PrintDebug( "減衰率 ： ( %13.8f, %13.8f )\n", attenuationTest.y, attenuationTest.z );

	// 点光源の更新
	if( pLightTest != nullptr )
	{
		// 割合の決定
		float	proportion;		// 割合
		if( timerSceneGame_ < 15 )
		{
			proportion = Utility::Easing( 1.0f, 0.0f, static_cast< float >( timerSceneGame_ ) / 15.0f );
		}
		else if( timerSceneGame_ < 30 )
		{
			proportion = 0.0f;
		}
		else
		{
			proportion = Utility::Easing( 0.0f, 1.0f, static_cast< float >( timerSceneGame_ - 30 ) / 150.0f );
		}

		// 減衰率の設定
		D3DXVECTOR3	attenuation;		// 減衰率
		attenuation = attenuationTest + D3DXVECTOR3( 0.0f, 0.0005f * proportion, 0.00005f * proportion );
		pLightTest->SetAttenuation( attenuation );

		// 消滅
		if( timerSceneGame_ >= 180 )
		{
			timerSceneGame_ = -1;
			pLightTest->Release();
			pLightTest = nullptr;
		}
	}

	// ポイントスプライトの更新
	managerPoint->Update();

	// タイマーの経過
	if( timerSceneGame_ >= 0 )
	{
		++timerSceneGame_;
	}
}

//==============================================================================
// Brief  : カメラのテスト更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::UpdateTestCamera( void )
{
	// スプラインカメラ処理の取得
	CameraStateSpline*	pState = nullptr;		// カメラ処理
	pState = pStateCameraResult_;

	// セクション番号の変更
	static int	indexSectionTestStatic = 0;		// セクション番号
	int			countSection;					// セクション数
	countSection = pState->GetCountSection();
	if( pArgument_->pKeyboard_->IsTrigger( DIK_LEFT ) )
	{
		--indexSectionTestStatic;
		if( indexSectionTestStatic < 0 )
		{
			indexSectionTestStatic = countSection - 1;
		}
	}
	else if( pArgument_->pKeyboard_->IsTrigger( DIK_RIGHT ) )
	{
		++indexSectionTestStatic;
		if( indexSectionTestStatic >= countSection )
		{
			indexSectionTestStatic = 0;
		}
	}

	// フレーム数の変更
	int		countFrame;		// フレーム数
	countFrame = pState->GetCountFrame( indexSectionTestStatic );
	if( pArgument_->pKeyboard_->IsRepeat( DIK_COMMA, 30, 1 ) )
	{
		--countFrame;
		if( countFrame <= 0 )
		{
			countFrame = 1;
		}
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_PERIOD, 30, 1 ) )
	{
		++countFrame;
	}
	pState->SetCountFrame( indexSectionTestStatic, countFrame );

	// コントロールポイントの取得
	int			indexCameraBegin;			// 開始視点番号
	int			indexCameraEnd;				// 終了視点番号
	int			indexLookAtBegin;			// 開始注視点番号
	int			indexLookAtEnd;				// 終了注視点番号
	D3DXVECTOR3	positionCameraBegin;		// 開始視点座標
	D3DXVECTOR3	positionCameraEnd;			// 終了視点座標
	D3DXVECTOR3	positionLookAtBegin;		// 開始注視点座標
	D3DXVECTOR3	positionLookAtEnd;			// 終了注視点座標
	D3DXVECTOR3	vectorCameraBegin;			// 開始視点ベクトル
	D3DXVECTOR3	vectorCameraEnd;			// 終了視点ベクトル
	D3DXVECTOR3	vectorLookAtBegin;			// 開始注視点ベクトル
	D3DXVECTOR3	vectorLookAtEnd;			// 終了注視点ベクトル
	indexCameraBegin = pState->GetIndexCameraBegin( indexSectionTestStatic );
	indexCameraEnd = pState->GetIndexCameraEnd( indexSectionTestStatic );
	indexLookAtBegin = pState->GetIndexLookAtBegin( indexSectionTestStatic );
	indexLookAtEnd = pState->GetIndexLookAtEnd( indexSectionTestStatic );
	pState->GetControlPointCamera( indexCameraBegin, &positionCameraBegin, &vectorCameraBegin );
	pState->GetControlPointCamera( indexCameraEnd, &positionCameraEnd, &vectorCameraEnd );
	pState->GetControlPointLookAt( indexLookAtBegin, &positionLookAtBegin, &vectorLookAtBegin );
	pState->GetControlPointLookAt( indexLookAtEnd, &positionLookAtEnd, &vectorLookAtEnd );

	// 編集対象の決定
	static int		indexTargetTestStatic = 0;		// 対象情報番号
	D3DXVECTOR3*	pPositionTarget = nullptr;		// 対象情報座標
	D3DXVECTOR3*	pVectorTarget = nullptr;		// 対象情報ベクトル
	if( pArgument_->pKeyboard_->IsTrigger( DIK_UP ) )
	{
		--indexTargetTestStatic;
		if( indexTargetTestStatic < 0 )
		{
			indexTargetTestStatic = 4 - 1;
		}
	}
	else if( pArgument_->pKeyboard_->IsTrigger( DIK_DOWN ) )
	{
		++indexTargetTestStatic;
		if( indexTargetTestStatic >= 4 )
		{
			indexTargetTestStatic = 0;
		}
	}
	switch( indexTargetTestStatic )
	{
		case 0:
			pPositionTarget = &positionCameraBegin;
			pVectorTarget = &vectorCameraBegin;
			break;
		case 1:
			pPositionTarget = &positionCameraEnd;
			pVectorTarget = &vectorCameraEnd;
			break;
		case 2:
			pPositionTarget = &positionLookAtBegin;
			pVectorTarget = &vectorLookAtBegin;
			break;
		case 3:
			pPositionTarget = &positionLookAtEnd;
			pVectorTarget = &vectorLookAtEnd;
			break;
		default:
			break;
	}

	// コントロールポイント情報の変更
	float	velocity;		// 変更速度
	velocity = 1.0f;
	if( pArgument_->pKeyboard_->IsPress( DIK_BACKSLASH ) )
	{
		velocity *= 10.0f;
	}
	if( pArgument_->pKeyboard_->IsPress( DIK_RSHIFT ) )
	{
		velocity *= 100.0f;
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_Q, 30, 1 ) )
	{
		pPositionTarget->x -= velocity;
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_W, 30, 1 ) )
	{
		pPositionTarget->x += velocity;
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_A, 30, 1 ) )
	{
		pPositionTarget->y -= velocity;
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_S, 30, 1 ) )
	{
		pPositionTarget->y += velocity;
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_Z, 30, 1 ) )
	{
		pPositionTarget->z -= velocity;
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_X, 30, 1 ) )
	{
		pPositionTarget->z += velocity;
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_E, 30, 1 ) )
	{
		pVectorTarget->x -= velocity;
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_R, 30, 1 ) )
	{
		pVectorTarget->x += velocity;
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_D, 30, 1 ) )
	{
		pVectorTarget->y -= velocity;
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_F, 30, 1 ) )
	{
		pVectorTarget->y += velocity;
	}
	if( pArgument_->pKeyboard_->IsRepeat( DIK_C, 30, 1 ) )
	{
		pVectorTarget->z -= velocity;
	}
	else if( pArgument_->pKeyboard_->IsRepeat( DIK_V, 30, 1 ) )
	{
		pVectorTarget->z += velocity;
	}

	// コントロールポイントの設定
	pState->SetControlPointCamera( indexCameraBegin, positionCameraBegin, vectorCameraBegin );
	pState->SetControlPointCamera( indexCameraEnd, positionCameraEnd, vectorCameraEnd );
	pState->SetControlPointLookAt( indexLookAtBegin, positionLookAtBegin, vectorLookAtBegin );
	pState->SetControlPointLookAt( indexLookAtEnd, positionLookAtEnd, vectorLookAtEnd );

	// 情報の表示
	TCHAR	pStringNameTarget[ 4 ][ 32 ] =
	{
		_T( "開始視点" ),
		_T( "終了視点" ),
		_T( "開始注視点" ),
		_T( "終了注視点" )
	};
	PrintDebug( _T( "*--------------------------------------*\n" ) );
	PrintDebug( _T( "| カメラ処理                           |\n" ) );
	PrintDebug( _T( "*--------------------------------------*\n" ) );
	PrintDebug( _T( "フレーム数 : %d\n" ), countFrame );
	PrintDebug( _T( "開始視点座標       ( %9.2f, %9.2f, %9.2f )\n" ), positionCameraBegin.x, positionCameraBegin.y, positionCameraBegin.z );
	PrintDebug( _T( "開始視点ベクトル   ( %9.2f, %9.2f, %9.2f )\n" ), vectorCameraBegin.x, vectorCameraBegin.y, vectorCameraBegin.z );
	PrintDebug( _T( "終了視点座標       ( %9.2f, %9.2f, %9.2f )\n" ), positionCameraEnd.x, positionCameraEnd.y, positionCameraEnd.z );
	PrintDebug( _T( "終了視点ベクトル   ( %9.2f, %9.2f, %9.2f )\n" ), vectorCameraEnd.x, vectorCameraEnd.y, vectorCameraEnd.z );
	PrintDebug( _T( "開始注視点座標     ( %9.2f, %9.2f, %9.2f )\n" ), positionLookAtBegin.x, positionLookAtBegin.y, positionLookAtBegin.z );
	PrintDebug( _T( "開始注視点ベクトル ( %9.2f, %9.2f, %9.2f )\n" ), vectorLookAtBegin.x, vectorLookAtBegin.y, vectorLookAtBegin.z );
	PrintDebug( _T( "終了注視点座標     ( %9.2f, %9.2f, %9.2f )\n" ), positionLookAtEnd.x, positionLookAtEnd.y, positionLookAtEnd.z );
	PrintDebug( _T( "終了注視点ベクトル ( %9.2f, %9.2f, %9.2f )\n" ), vectorLookAtEnd.x, vectorLookAtEnd.y, vectorLookAtEnd.z );
	PrintDebug( _T( "編集対象 : %s\n" ), &pStringNameTarget[ indexTargetTestStatic ][ 0 ] );

	// 線の表示
	for( int counterFrame = 0; counterFrame < countFrame; ++counterFrame )
	{
		D3DXVECTOR3	position;		// 座標
		pState->GetPositionCamera( indexSectionTestStatic, counterFrame, &position );
		managerPoint->Add( 1, position, D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ), 50.0f,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, 0.0f ), 0.0f, 1 );
		pState->GetPositionLookAt( indexSectionTestStatic, counterFrame, &position );
		managerPoint->Add( 1, position, D3DXCOLOR( 1.0f, 0.5f, 0.5f, 1.0f ), 50.0f,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), D3DXCOLOR( 0.0f, 0.0f, 0.0f, 0.0f ), 0.0f, 1 );
	}

	// ポイントスプライトの更新
	managerPoint->Update();

	// タイマーの経過
	if( timerSceneGame_ >= 0 )
	{
		++timerSceneGame_;
	}
}

//==============================================================================
// Brief  : カウントダウンオブジェクトを非表示にする
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void SceneGame::DisableObjectCount( void )
{
	// オブジェクトを非表示にする
	for( int counterObject = 0; counterObject < IMAGE_COUNT_MAXIMUM; ++counterObject )
	{
		pObjectCount_[ counterObject ].SetEnableGraphic( false );
	}
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

	// シンクロ率を非表示にする
	pObjectSynchronizeResult_->SetEnableGraphic( false );

	// コンボを非表示にする
	pObjectComboResult_->SetEnableGraphic( false );

	// スコアを非表示にする
	pObjectScoreResult_->SetEnableGraphic( false );

	// ゲージを非表示にする
	pObjectGageResult_->SetEnableGraphic2( false );
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
		pObjectScoreRanking_[ counterRank ].SetEnableGraphic( false );
	}
}
