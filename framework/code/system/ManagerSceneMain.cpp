//==============================================================================
//
// File   : ManagerSceneMain.cpp
// Brief  : シーン管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerSceneMain.h"
#include "SceneMain.h"
#include "SceneArgumentMain.h"
#include "../scene/SceneGame.h"
#include "../scene/SceneRanking.h"
#include "../scene/SceneResult.h"
#include "../scene/SceneSplash.h"
#include "../scene/SceneTitle.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
bool ManagerSceneMain::demoFlag = false;
bool ManagerSceneMain::tutorialFlag = false;
bool ManagerSceneMain::reTutorialFlag = false;
int ManagerSceneMain::demoCount = 0;
int ManagerSceneMain::demoCountMax = 780;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerSceneMain::ManagerSceneMain( void ) : ManagerScene()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerSceneMain::~ManagerSceneMain( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int typeSceneBegin					: 開始シーン
// Arg    : SceneArgumentMain* pArgument		: シーン引数
//==============================================================================
int ManagerSceneMain::Initialize( int typeSceneBegin, SceneArgumentMain* pArgument )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerScene::Initialize( typeSceneBegin, pArgument );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pArgument_ = pArgument;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerSceneMain::Finalize( void )
{
	// シーンの破棄
	delete pScene_;
	pScene_ = nullptr;

	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerScene::Finalize();
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
// Arg    : int typeSceneBegin					: 開始シーン
// Arg    : SceneArgumentMain* pArgument		: シーン引数
//==============================================================================
int ManagerSceneMain::Reinitialize( int typeSceneBegin, SceneArgumentMain* pArgument )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( typeSceneBegin, pArgument );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerSceneMain* pOut				: コピー先アドレス
//==============================================================================
int ManagerSceneMain::Copy( ManagerSceneMain* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerScene::Copy( pOut );
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
void ManagerSceneMain::Update( void )
{
	// シーン削除フラグOFF
	needsDelete_ = false;

	// シーン切り替え要請受領
	if( pScene_ != nullptr )
	{
		if( pScene_->IsEnd() )
		{
			isShifting_ = true;
			typeSceneNext_ = pScene_->GetSceneNext();
		}
	}

	// シーン切替時
	if( isShifting_ )
	{
		// シーン切り替え
		if( pScene_ != nullptr )
		{
			needsDelete_ = true;
		}
		delete pScene_;
		pScene_ = nullptr;
		switch( typeSceneNext_ )
		{
		// シーンなし
		case TYPE_NONE:
			isEnd_ = true;
			break;

		// スプラッシュ
		case TYPE_SPLASH:
			pScene_ = new SceneSplash();
			break;

		// タイトル
		case TYPE_TITLE:
			pScene_ = new SceneTitle();
			break;

		// ゲーム
		case TYPE_GAME:
			pScene_ = new SceneGame();
			break;

		// リザルト
		case TYPE_RESULT:
			pScene_ = new SceneResult();
			break;

		// ランキング
		case TYPE_RANKING:
			pScene_ = new SceneRanking();
			break;

		// その他
		default:
			isEnd_ = true;
			break;
		}
		if( pScene_ == nullptr )
		{
			isEnd_ = true;
		}
		else
		{
			pScene_->Initialize( pArgument_ );
		}

		// フラグをOFFに戻す
		isShifting_ = false;
		if( isEnd_ )
		{
			return;
		}
	}

	// シーン更新処理
	if( pScene_ != nullptr )
	{
		pScene_->Update();
	}
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerSceneMain::InitializeSelf( void )
{
	// メンバ変数の初期化
	pArgument_ = nullptr;
	pScene_ = nullptr;
}
