//==============================================================================
//
// File   : InputKeyboard.cpp
// Brief  : キーボード入力クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <tchar.h>
#include "InputKeyboard.h"

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
InputKeyboard::InputKeyboard( void ) : Input()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
InputKeyboard::~InputKeyboard( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirectInput8* pDirectInput			: DirectInputオブジェクト
// Arg    : HWND windowHandle					: ウィンドウハンドル
//==============================================================================
int InputKeyboard::Initialize( IDirectInput8* pDirectInput, HWND windowHandle )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Input::Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	// デバイスオブジェクトを作成
	if( FAILED( pDirectInput_->CreateDevice( GUID_SysKeyboard, &pDevice_, NULL ) ) )
	{
		MessageBox( NULL, _T( "デバイスオブジェクトの作成に失敗しました" ), _T( "エラー" ), MB_OK );
		return E_FAIL;
	}

	// データフォーマットを設定
	if( FAILED( pDevice_->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		MessageBox( NULL, _T( "データフォーマットの設定に失敗しました" ), _T( "エラー" ), MB_OK );
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if( FAILED( pDevice_->SetCooperativeLevel( windowHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) ) ) )
	{
		MessageBox( NULL, _T( "協調モードの設定に失敗しました" ), _T( "エラー" ), MB_OK );
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	pDevice_->Acquire();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int InputKeyboard::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Input::Finalize();
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
// Arg    : IDirectInput8* pDirectInput			: DirectInputオブジェクト
// Arg    : HWND windowHandle					: ウィンドウハンドル
//==============================================================================
int InputKeyboard::Reinitialize( IDirectInput8* pDirectInput, HWND windowHandle )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDirectInput, windowHandle );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : InputKeyboard* pOut					: コピー先アドレス
//==============================================================================
int InputKeyboard::Copy( InputKeyboard* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Input::Copy( pOut );
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
void InputKeyboard::Update( void )
{
	// キーボードの状態を更新
	BYTE	pState[ MAXIMUM_STATE ];		// キーボード状態受け取り用
	if( SUCCEEDED( pDevice_->GetDeviceState( sizeof( pState ), &pState[ 0 ] ) ) )
	{
		memset( &pTrigger_[ 0 ], 0x00, sizeof( pTrigger_ ) );
		memset( &pRelease_[ 0 ], 0x00, sizeof( pRelease_ ) );
		for( int nCntMouse = 0; nCntMouse < MAXIMUM_STATE; ++nCntMouse )
		{
			// トリガ情報の更新
			if( !(pState_[ nCntMouse ] & 0x80) && (pState[ nCntMouse ] & 0x80) )
			{
				pTrigger_[ nCntMouse ] = true;
			}

			// リリース情報の更新
			if( (pState_[ nCntMouse ] & 0x80) && !(pState[ nCntMouse ] & 0x80) )
			{
				pRelease_[ nCntMouse ] = true;
			}

			// リピート情報の更新
			if( (pState[ nCntMouse ] & 0x80) )
			{
				++pRepeat_[ nCntMouse ];
			}
			else
			{
				pRepeat_[ nCntMouse ] = 0;
			}

			// キーボード状態の更新
			pState_[ nCntMouse ] = pState[ nCntMouse ];
		}
	}
	else
	{
		pDevice_->Acquire();
	}
}

//==============================================================================
// Brief  : プレス判定
// Return : bool								: プレス判定
// Arg    : int typeKey							: 判定するキーの種類
//==============================================================================
bool InputKeyboard::IsPress( int typeKey ) const
{
	// 値の返却
	return (pState_[ typeKey ] & 0x80) != 0;
}

//==============================================================================
// Brief  : トリガー判定
// Return : bool								: トリガー判定
// Arg    : int typeKey							: 判定するキーの種類
//==============================================================================
bool InputKeyboard::IsTrigger( int typeKey ) const
{
	// 値の返却
	return pTrigger_[ typeKey ];
}

//==============================================================================
// Brief  : リリース判定
// Return : bool								: リリース判定
// Arg    : int typeKey							: 判定するキーの種類
//==============================================================================
bool InputKeyboard::IsRelease( int typeKey ) const
{
	// 値の返却
	return pRelease_[ typeKey ];
}

//==============================================================================
// Brief  : リピート判定
// Return : bool								: リピート判定
// Arg    : int typeKey							: 判定するキーの種類
// Arg    : int timeBegin						: ONになるまでの時間
// Arg    : int timeInterval					: ONになる間隔
//==============================================================================
bool InputKeyboard::IsRepeat( int typeKey, int timeBegin, int timeInterval ) const
{
	// トリガ条件
	if( pRepeat_[ typeKey ] == 1 )
	{
		return true;
	}

	// リピート条件
	if( pRepeat_[ typeKey ] >= timeBegin )
	{
		if( (pRepeat_[ typeKey ] - timeBegin) % timeInterval == 0 )
		{
			return true;
		}
	}

	// 値の返却
	return false;
}

//==============================================================================
// Brief  : プレス時間の取得
// Return : int									: プレス時間
// Arg    : int typeKey							: 判定するキーの種類
//==============================================================================
int InputKeyboard::GetTimePress( int typeKey ) const
{
	// 値の返却
	return pRepeat_[ typeKey ];
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void InputKeyboard::InitializeSelf( void )
{
	// メンバ変数の初期化
	for( int counterKey = 0; counterKey < MAXIMUM_STATE; ++counterKey )
	{
		pState_[ counterKey ] = false;
		pTrigger_[ counterKey ] = false;
		pRelease_[ counterKey ] = false;
		pRepeat_[ counterKey ] = 0;
	}
}
