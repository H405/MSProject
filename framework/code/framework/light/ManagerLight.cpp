//==============================================================================
//
// File   : ManagerLight.cpp
// Brief  : ライト管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/14 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerLight.h"
#include "LightDirection.h"
#include "LightPoint.h"
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
ManagerLight::ManagerLight( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerLight::~ManagerLight( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int maximumDirection				: 最大ディレクショナルライト数
// Arg    : int maximumPoint					: 最大ポイントライト数
//==============================================================================
int ManagerLight::Initialize( int maximumDirection, int maximumPoint )
{
	// メンバ変数の設定
	maximumDirection_ = maximumDirection;
	maximumPoint_ = maximumPoint;
	if( maximumDirection > 0 )
	{
		pLightDirection_ = new LightDirection[ maximumDirection ];
		for( int counterItem = 0; counterItem < maximumDirection; ++counterItem )
		{
			pLightDirection_[ counterItem ].Initialize();
		}
	}
	if( maximumPoint > 0 )
	{
		pLightPoint_ = new LightPoint[ maximumPoint ];
		for( int counterItem = 0; counterItem < maximumPoint; ++counterItem )
		{
			pLightPoint_[ counterItem ].Initialize();
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
int ManagerLight::Finalize( void )
{
	// 格納領域の開放
	delete[] pLightDirection_;
	pLightDirection_ = nullptr;

	delete[] pLightPoint_;
	pLightPoint_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int maximumDirection				: 最大ディレクショナルライト数
// Arg    : int maximumPoint					: 最大ポイントライト数
//==============================================================================
int ManagerLight::Reinitialize( int maximumDirection, int maximumPoint )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( maximumDirection, maximumPoint );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerLight* pOut					: コピー先アドレス
//==============================================================================
int ManagerLight::Copy( ManagerLight* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : ディレクショナルライトの取得
// Return : LightDirection*						: ディレクショナルライト
// Arg    : void								: なし
//==============================================================================
LightDirection* ManagerLight::GetLightDirection( void )
{
	// 空いているライトを検索
	for( int counterLight = 0; counterLight < maximumDirection_; ++counterLight )
	{
		if( !pLightDirection_[ counterLight ].IsUsed() )
		{
			pLightDirection_[ counterLight ].Reinitialize();
			pLightDirection_[ counterLight ].Use();
			return &pLightDirection_[ counterLight ];
		}
	}

	// 見つからなかった
	PrintDebugWnd( _T( "ディレクショナルライトの空きがありませんでした。\n" ) );
	return nullptr;
}

//==============================================================================
// Brief  : ポイントライトの取得
// Return : LightPoint*							: ポイントライト
// Arg    : void								: なし
//==============================================================================
LightPoint* ManagerLight::GetLightPoint( void )
{
	// 空いているライトを検索
	for( int counterLight = 0; counterLight < maximumPoint_; ++counterLight )
	{
		if( !pLightPoint_[ counterLight ].IsUsed() )
		{
			pLightPoint_[ counterLight ].Reinitialize();
			pLightPoint_[ counterLight ].Use();
			return &pLightPoint_[ counterLight ];
		}
	}

	// 見つからなかった
	PrintDebugWnd( _T( "ポイントライトの空きがありませんでした。\n" ) );
	return nullptr;
}

//==============================================================================
// Brief  : ディレクショナルライト数の取得
// Return : int									: ディレクショナルライト数
// Arg    : void								: なし
//==============================================================================
int ManagerLight::GetCountLightDirection( void )
{
	// 使用しているライトを検索
	int		countLight;		// ライトの数
	countLight = 0;
	for( int counterLight = 0; counterLight < maximumDirection_; ++counterLight )
	{
		if( pLightDirection_[ counterLight ].IsUsed() && pLightDirection_[ counterLight ].IsEnable() )
		{
			++countLight;
		}
	}

	// 値の返却
	return countLight;
}

//==============================================================================
// Brief  : ポイントライト数の取得
// Return : int									: ポイントライト数
// Arg    : void								: なし
//==============================================================================
int ManagerLight::GetCountLightPoint( void )
{
	// 使用しているライトを検索
	int		countLight;		// ライトの数
	countLight = 0;
	for( int counterLight = 0; counterLight < maximumPoint_; ++counterLight )
	{
		if( pLightPoint_[ counterLight ].IsUsed() && pLightPoint_[ counterLight ].IsEnable() )
		{
			++countLight;
		}
	}

	// 値の返却
	return countLight;
}

//==============================================================================
// Brief  : 有効なディレクショナルライトの取得
// Return : LightDirection*						: ディレクショナルライト
// Arg    : int index							: 番号
//==============================================================================
LightDirection* ManagerLight::GetLightDirectionEnable( int index )
{
	// 使用しているライトを検索
	int		countLight;		// ライトの個数
	countLight = 0;
	for( int counterLight = 0; counterLight < maximumDirection_; ++counterLight )
	{
		if( pLightDirection_[ counterLight ].IsUsed() && pLightDirection_[ counterLight ].IsEnable() )
		{
			if( countLight == index )
			{
				return &pLightDirection_[ counterLight ];
			}
			++countLight;
		}
	}

	// 見つからなかった
	PrintDebugWnd( _T( "有効なディレクショナルライトが見つかりませんでした。\n" ) );
	return nullptr;
}

//==============================================================================
// Brief  : 有効なポイントライトの取得
// Return : LightPoint*							: ポイントライト
// Arg    : int index							: 番号
//==============================================================================
LightPoint* ManagerLight::GetLightPointEnable( int index )
{
	// 使用しているライトを検索
	int		countLight;		// ライトの個数
	countLight = 0;
	for( int counterLight = 0; counterLight < maximumPoint_; ++counterLight )
	{
		if( pLightPoint_[ counterLight ].IsUsed() && pLightPoint_[ counterLight ].IsEnable() )
		{
			if( countLight == index )
			{
				return &pLightPoint_[ counterLight ];
			}
			++countLight;
		}
	}

	// 見つからなかった
	PrintDebugWnd( _T( "有効なポイントライトが見つかりませんでした。\n" ) );
	return nullptr;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerLight::InitializeSelf( void )
{
	// メンバ変数の初期化
	maximumDirection_ = 0;
	maximumPoint_ = 0;
	pLightDirection_ = nullptr;
	pLightPoint_ = nullptr;
}
