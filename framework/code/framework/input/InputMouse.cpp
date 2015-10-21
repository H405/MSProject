//==============================================================================
//
// File   : InputMouse.cpp
// Brief  : マウス入力クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <tchar.h>
#include "InputMouse.h"

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
InputMouse::InputMouse( void ) : Input()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
InputMouse::~InputMouse( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirectInput8* pDirectInput			: DirectInputオブジェクト
// Arg    : HWND windowHandle					: ウィンドウハンドル
// Arg    : int widthScreen						: スクリーン幅
// Arg    : int heightScreen					: スクリーン高さ
//==============================================================================
int InputMouse::Initialize( IDirectInput8* pDirectInput, HWND windowHandle, int widthScreen, int heightScreen )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Input::Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	widthScreen_ = widthScreen;
	heightScreen_ = heightScreen;

	// デバイスオブジェクトを作成
	if( FAILED( pDirectInput->CreateDevice( GUID_SysMouse, &pDevice_, NULL ) ) )
	{
		MessageBox( NULL, _T( "デバイスオブジェクトの作成に失敗しました" ), _T( "エラー" ), MB_OK );
		return 1;
	}

	// データフォーマットを設定
	if( FAILED( pDevice_->SetDataFormat( &c_dfDIMouse2 ) ) )
	{
		MessageBox( NULL, _T( "データフォーマットの設定に失敗しました" ), _T( "エラー" ), MB_OK );
		return 1;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if( FAILED( pDevice_->SetCooperativeLevel( windowHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) ) ) )
	{
		MessageBox( NULL, _T( "協調モードの設定に失敗しました" ), _T( "エラー" ), MB_OK );
		return 1;
	}

	// 軸モードを設定（相対値モードに設定）
	DIPROPDWORD propertyMouse;
	propertyMouse.diph.dwSize		= sizeof( propertyMouse ); 
	propertyMouse.diph.dwHeaderSize	= sizeof( propertyMouse.diph ); 
	propertyMouse.diph.dwObj		= 0;
	propertyMouse.diph.dwHow		= DIPH_DEVICE;
	propertyMouse.dwData			= DIPROPAXISMODE_REL;
	if( FAILED( pDevice_->SetProperty( DIPROP_AXISMODE, &propertyMouse.diph ) ) )
	{
		MessageBox( NULL, _T( "軸モードの設定に失敗" ), _T( "Direct Input Error" ), MB_OK );
		return 1;
	}

	// マウスへのアクセス権を獲得(入力制御開始)
	pDevice_->Acquire();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int InputMouse::Finalize( void )
{
	// カーソルの表示
	Show();

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
// Arg    : int widthScreen						: スクリーン幅
// Arg    : int heightScreen					: スクリーン高さ
//==============================================================================
int InputMouse::Reinitialize( IDirectInput8* pDirectInput, HWND windowHandle, int widthScreen, int heightScreen )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDirectInput, windowHandle, widthScreen, heightScreen );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : InputMouse* pOut					: コピー先アドレス
//==============================================================================
int InputMouse::Copy( InputMouse* pOut ) const
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
void InputMouse::Update( void )
{
	// マウス座標の取得
	GetCursorPos( &positionWindow_ );
	ScreenToClient( windowHandle_, &positionWindow_ );
	position_ = positionWindow_;
	if( position_.x < 0 )
	{
		position_.x = 0;
	}
	else if( position_.x >= static_cast< LONG >( widthScreen_ ) )
	{
		position_.x = widthScreen_ - 1;
	}
	if( position_.y < 0 )
	{
		position_.y = 0;
	}
	else if( position_.y >= static_cast< LONG >( heightScreen_ ) )
	{
		position_.y = heightScreen_ - 1;
	}

	// マウス情報更新
	DIMOUSESTATE2	stateMouse;						// マウス情報取得
	BYTE			aMouseState[ TYPE_MAX ];		// マウス状態格納ワーク
	if( SUCCEEDED( pDevice_->GetDeviceState( sizeof( DIMOUSESTATE2 ), &stateMouse ) ) )
	{
		aMouseState[ TYPE_LEFT ] = (stateMouse.rgbButtons[ 0 ] & 0x80);
		aMouseState[ TYPE_RIGHT ] = (stateMouse.rgbButtons[ 1 ] & 0x80);
		aMouseState[ TYPE_MIDDLE ] = (stateMouse.rgbButtons[ 2 ] & 0x80);
		vectorMove_.x = stateMouse.lX;
		vectorMove_.y = stateMouse.lY;
		moveWheel_ = stateMouse.lZ;
		memset( &pTrigger_[ 0 ], 0x00, sizeof( pTrigger_ ) );
		memset( &pRelease_[ 0 ], 0x00, sizeof( pRelease_ ) );
		for( int nCntMouse = 0; nCntMouse < TYPE_MAX; ++nCntMouse )
		{
			// トリガ情報の更新
			if( !(pState_[ nCntMouse ] & 0x80) && (aMouseState[ nCntMouse ] & 0x80) )
			{
				pTrigger_[ nCntMouse ] = true;
			}

			// リリース情報の更新
			if( (pState_[ nCntMouse ] & 0x80) && !(aMouseState[ nCntMouse ] & 0x80) )
			{
				pRelease_[ nCntMouse ] = true;
			}

			// リピート情報の更新
			if( (aMouseState[ nCntMouse ] & 0x80) )
			{
				++pRepeat_[ nCntMouse ];
			}
			else
			{
				pRepeat_[ nCntMouse ] = 0;
			}

			// キーボード状態の更新
			pState_[ nCntMouse ] = aMouseState[ nCntMouse ];
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
bool InputMouse::IsPress( int typeKey ) const
{
	// 値の返却
	return (pState_[ typeKey ] & 0x80) != 0;
}

//==============================================================================
// Brief  : トリガー判定
// Return : bool								: トリガー判定
// Arg    : int typeKey							: 判定するキーの種類
//==============================================================================
bool InputMouse::IsTrigger( int typeKey ) const
{
	// 値の返却
	return pTrigger_[ typeKey ];
}

//==============================================================================
// Brief  : リリース判定
// Return : bool								: リリース判定
// Arg    : int typeKey							: 判定するキーの種類
//==============================================================================
bool InputMouse::IsRelease( int typeKey ) const
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
bool InputMouse::IsRepeat( int typeKey, int timeBegin, int timeInterval ) const
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
int InputMouse::GetTimePress( int typeKey ) const
{
	// 値の返却
	return pRepeat_[ typeKey ];
}

//==============================================================================
// Brief  : カーソルの表示
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void InputMouse::Show( void )
{
	// カーソルの表示
	while( ShowCursor( TRUE ) < 0 ) {}
}

//==============================================================================
// Brief  : カーソルの非表示
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void InputMouse::Hide( void )
{
	// カーソルの非表示
	while( ShowCursor( FALSE ) >= 0 ) {}
}

//==============================================================================
// Brief  : X座標の取得
// Return : int									: X座標
// Arg    : void								: なし
//==============================================================================
int InputMouse::GetPositionX( void ) const
{
	// 値の返却
	return position_.x;
}

//==============================================================================
// Brief  : Y座標の取得
// Return : int									: Y座標
// Arg    : void								: なし
//==============================================================================
int InputMouse::GetPositionY( void ) const
{
	// 値の返却
	return position_.y;
}

//==============================================================================
// Brief  : ウィンドウX座標の取得
// Return : int									: X座標
// Arg    : void								: なし
//==============================================================================
int InputMouse::GetPositionWindowX( void ) const
{
	// 値の返却
	return positionWindow_.x;
}

//==============================================================================
// Brief  : ウィンドウY座標の取得
// Return : int									: Y座標
// Arg    : void								: なし
//==============================================================================
int InputMouse::GetPositionWindowY( void ) const
{
	// 値の返却
	return positionWindow_.y;
}

//==============================================================================
// Brief  : X移動値の取得
// Return : int									: X移動値
// Arg    : void								: なし
//==============================================================================
int InputMouse::GetMoveX( void ) const
{
	// 値の返却
	return vectorMove_.x;
}

//==============================================================================
// Brief  : Y移動値の取得
// Return : int									: Y移動値
// Arg    : void								: なし
//==============================================================================
int InputMouse::GetMoveY( void ) const
{
	// 値の返却
	return vectorMove_.y;
}

//==============================================================================
// Brief  : ホイール移動値の取得
// Return : int									: ホイール移動値
// Arg    : void								: なし
//==============================================================================
int InputMouse::GetMoveWheel( void ) const
{
	// 値の返却
	return moveWheel_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void InputMouse::InitializeSelf( void )
{
	// メンバ変数の初期化
	windowHandle_ = NULL;
	widthScreen_ = 0;
	heightScreen_ = 0;
	moveWheel_ = 0;
	for( int counterKey = 0; counterKey < TYPE_MAX; ++counterKey )
	{
		pState_[ counterKey ] = false;
		pTrigger_[ counterKey ] = false;
		pRelease_[ counterKey ] = false;
		pRepeat_[ counterKey ] = 0;
	}
}
