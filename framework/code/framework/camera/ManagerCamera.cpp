//==============================================================================
//
// File   : ManagerCamera.cpp
// Brief  : カメラ管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/20 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerCamera.h"
#include "CameraObject.h"
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
ManagerCamera::ManagerCamera( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerCamera::~ManagerCamera( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int countCamera						: カメラ数
//==============================================================================
int ManagerCamera::Initialize( int countCamera )
{
	// メンバ変数の設定
	countCamera_ = countCamera;
	if( countCamera_ > 0 )
	{
		pCamera_ = new CameraObject[ countCamera ];
		for( int counterItem = 0; counterItem < countCamera; ++counterItem )
		{
			pCamera_[ counterItem ].Initialize();
		}
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerCamera::Finalize( void )
{
	// 格納領域の開放
	delete[] pCamera_;
	pCamera_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int countCamera						: カメラ数
//==============================================================================
int ManagerCamera::Reinitialize( int countCamera )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( countCamera );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerCamera* pOut					: コピー先アドレス
//==============================================================================
int ManagerCamera::Copy( ManagerCamera* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerCamera::Update( void )
{
#ifdef _DEVELOP
	// デバッグ切替
	if( (GetKeyState( VK_F3 ) & 0x80) != 0 )
	{
		if( !isPressingKey_ )
		{
			pCamera_[ indexDebug_ ].ToggleDebug();
		}
		isPressingKey_ = true;
	}
	else
	{
		isPressingKey_ = false;
	}
#endif

	// カメラの更新
	for( int counterCamera = 0; counterCamera < countCamera_; ++counterCamera )
	{
		pCamera_[ counterCamera ].Update();
	}
}

//==============================================================================
// Brief  : カメラの取得
// Return : CameraObject*						: カメラ
// Arg    : int index							: 番号
//==============================================================================
CameraObject* ManagerCamera::GetCamera( int index )
{
	// カメラのアドレスを返す
	return &pCamera_[ index ];
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerCamera::InitializeSelf( void )
{
	// メンバ変数の初期化
	countCamera_ = 0;
	pCamera_ = nullptr;
#ifdef _DEVELOP
	indexDebug_ = 0;
	isPressingKey_ = false;
#endif
}
