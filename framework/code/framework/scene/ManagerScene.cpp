//==============================================================================
//
// File   : ManagerScene.cpp
// Brief  : シーン管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerScene.h"
#include "Scene.h"
#include "SceneArgument.h"

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
ManagerScene::ManagerScene( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerScene::~ManagerScene( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int typeSceneBegin					: 開始シーン
// Arg    : SceneArgument* pArgument			: シーン引数
//==============================================================================
int ManagerScene::Initialize( int typeSceneBegin, SceneArgument* pArgument )
{
	// メンバ変数の設定
	pArgument_ = pArgument;

	// シーンの切り替え
	ShiftScene( typeSceneBegin );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerScene::Finalize( void )
{
	// シーンの削除
	delete pScene_;
	pScene_ = nullptr;

	// クラス内部の初期化
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int typeSceneBegin					: 開始シーン
// Arg    : SceneArgument* pArgument			: シーン引数
//==============================================================================
int ManagerScene::Reinitialize( int typeSceneBegin, SceneArgument* pArgument )
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
// Arg    : ManagerScene* pOut					: コピー先アドレス
//==============================================================================
int ManagerScene::Copy( ManagerScene* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerScene::Update( void )
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
		case 0:
			isEnd_ = true;
			break;

		// その他
		default:
			isEnd_ = true;
			break;
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
// Brief  : シーンの切り替え
// Return : void								: なし
// Arg    : int typeScene						: 切り替えるシーン
//==============================================================================
void ManagerScene::ShiftScene( int typeScene )
{
	// シーンの切り替え
	typeSceneNext_ = typeScene;
	isShifting_ = true;
}

//==============================================================================
// Brief  : 現在のシーンの取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int ManagerScene::GetTypeSceneCurrent( void ) const
{
	// 値の返却
	return typeSceneCurrent_;
}

//==============================================================================
// Brief  : 次のシーンの設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void ManagerScene::SetTypeSceneNext( int value )
{
	// 値の設定
	typeSceneNext_ = value;
}

//==============================================================================
// Brief  : シーン切り替え中フラグの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
bool ManagerScene::GetIsShifting( void ) const
{
	// 値の返却
	return isShifting_;
}

//==============================================================================
// Brief  : シーン切り替え中フラグの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
bool ManagerScene::IsShifting( void ) const
{
	// 値の返却
	return isShifting_;
}

//==============================================================================
// Brief  : シーン終了フラグの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
bool ManagerScene::GetIsEnd( void ) const
{
	// 値の返却
	return isEnd_;
}

//==============================================================================
// Brief  : シーン終了フラグの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
bool ManagerScene::IsEnd( void ) const
{
	// 値の返却
	return isEnd_;
}

//==============================================================================
// Brief  : シーン管理クラス破棄フラグの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
bool ManagerScene::GetNeedsDelete( void ) const
{
	// 値の返却
	return needsDelete_;
}

//==============================================================================
// Brief  : シーン管理クラス破棄フラグの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
bool ManagerScene::NeedsDelete( void ) const
{
	// 値の返却
	return needsDelete_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerScene::InitializeSelf( void )
{
	// メンバ変数の初期化
	pArgument_ = nullptr;
	pScene_ = nullptr;
	typeSceneCurrent_ = 0;
	typeSceneNext_ = 0;
	isShifting_ = false;
	isEnd_ = false;
	needsDelete_ = false;
}
