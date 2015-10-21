//==============================================================================
//
// File   : InputPad.cpp
// Brief  : ゲームパッド入力クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <tchar.h>
#include "InputPad.h"

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
InputPad::InputPad( void ) : Input()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
InputPad::~InputPad( void )
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
int InputPad::Initialize( IDirectInput8* pDirectInput, HWND windowHandle )
{
	// 基本クラスの処理
	HRESULT result;		// 実行結果
	result = Input::Initialize( pDirectInput, windowHandle );
	if( result != 0 )
	{
		return result;
	}

	// デバイスオブジェクトの列挙
	result = pDirectInput_->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumDevicesCallback, this, DIEDFL_ATTACHEDONLY );
	if( FAILED( result ) )
	{
		MessageBox(  nullptr, _T( "デバイスオブジェクトの作成に失敗しました" ), _T( "エラー" ), MB_OK );
		return 1;
	}

	// ジョイスティックの設定
	for( int counterJoystick = 0; counterJoystick < countDevice_; ++counterJoystick )
	{
		// エラーチェック
		if( pDevice_ == nullptr )
		{
			MessageBox( NULL, _T( "デバイスオブジェクトの作成に失敗しました" ), _T( "エラー" ), MB_OK );
			return 1;
		}

		// データフォーマットを設定
		result = pDevice_->SetDataFormat( &c_dfDIJoystick );
		if( FAILED( result ) )
		{
			MessageBox( NULL, _T( "データフォーマットの設定に失敗しました" ), _T( "エラー" ), MB_OK );
			return 1;
		}

		// 協調モードを設定（フォアグラウンド＆非排他モード）
		result = pDevice_->SetCooperativeLevel( windowHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) );
		if( FAILED( result ) )
		{
			MessageBox( NULL, _T( "協調モードの設定に失敗しました" ), _T( "エラー" ), MB_OK );
			return 1;
		}

		// 能力情報の取得
		DIDEVCAPS	deviceCpacity;		// デバイスの能力
		deviceCpacity.dwSize = sizeof( DIDEVCAPS );
		result = pDevice_->GetCapabilities( &deviceCpacity );
		if( FAILED( result ) )
		{
			MessageBox( NULL, _T( "能力情報の取得に失敗しました" ), _T( "エラー" ), MB_OK );
			return 1;
		}
		result = pDevice_->EnumObjects( EnumDeviceObjectsCallback, reinterpret_cast< void* >( this ), DIDFT_AXIS );
		if( FAILED( result ) )
		{
			MessageBox( NULL, _T( "動作の設定に失敗しました" ), _T( "エラー" ), MB_OK );
			return 1;
		}

		// ジョイスティックへのアクセス権を獲得
		result = pDevice_->Poll(); 
		if( FAILED( result ) ) 
		{
			result = pDevice_->Acquire();
			while(result == DIERR_INPUTLOST) 
			{
				result = pDevice_->Acquire();
			}
			return 0; 
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
int InputPad::Finalize( void )
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
int InputPad::Reinitialize( IDirectInput8* pDirectInput, HWND windowHandle )
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
// Arg    : InputPad* pOut						: コピー先アドレス
//==============================================================================
int InputPad::Copy( InputPad* pOut ) const
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
void InputPad::Update( void )
{
	// エラーチェック
	if( pDevice_ == nullptr )
	{
		return;
	}

	// 入力の受け取り
	DIJOYSTATE	stateJoystick;		// ジョイスティック状態受け取り用
	if( FAILED( pDevice_->Poll() ) )
	{
		pDevice_->Acquire();
		return;
	}
	pDevice_->GetDeviceState( sizeof( DIJOYSTATE ), &stateJoystick );

	// 入力情報のリセット
	for( int counterKey = 0; counterKey < TYPE_MAX; ++counterKey )
	{
		pTrigger_[ counterKey ] = false;
		pRelease_[ counterKey ] = false;
	}

	// 左スティック左入力情報の作成
	if( !(stateJoystick_.lX <= minimumThresholdLeft_) && (stateJoystick.lX <= minimumThresholdLeft_) )
	{
		pTrigger_[ TYPE_KEY_LEFT_LEFT ] = true;
	}
	if( (stateJoystick_.lX <= minimumThresholdLeft_) && !(stateJoystick.lX <= minimumThresholdLeft_) )
	{
		pRelease_[ TYPE_KEY_LEFT_LEFT ] = true;
	}
	if( (stateJoystick.lX <= minimumThresholdLeft_) )
	{
		++pRepeat_[ TYPE_KEY_LEFT_LEFT ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_LEFT_LEFT ] = 0;
	}
	
	// 左スティック右入力情報の作成
	if( !(stateJoystick_.lX >= maximumThresholdLeft_) && (stateJoystick.lX >= maximumThresholdLeft_) )
	{
		pTrigger_[ TYPE_KEY_LEFT_RIGHT ] = true;
	}
	if( (stateJoystick_.lX >= maximumThresholdLeft_) && !(stateJoystick.lX >= maximumThresholdLeft_) )
	{
		pRelease_[ TYPE_KEY_LEFT_RIGHT ] = true;
	}
	if( (stateJoystick.lX >= maximumThresholdLeft_) )
	{
		++pRepeat_[ TYPE_KEY_LEFT_RIGHT ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_LEFT_RIGHT ] = 0;
	}
	
	// 左スティック上入力情報の作成
	if( !(stateJoystick_.lY <= minimumThresholdLeft_) && (stateJoystick.lY <= minimumThresholdLeft_) )
	{
		pTrigger_[ TYPE_KEY_LEFT_UP ] = true;
	}
	if( (stateJoystick_.lY <= minimumThresholdLeft_) && !(stateJoystick.lY <= minimumThresholdLeft_) )
	{
		pRelease_[ TYPE_KEY_LEFT_UP ] = true;
	}
	if( (stateJoystick.lY <= minimumThresholdLeft_) )
	{
		++pRepeat_[ TYPE_KEY_LEFT_UP ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_LEFT_UP ] = 0;
	}
	
	// 左スティック下入力情報の作成
	if( !(stateJoystick_.lY >= maximumThresholdLeft_) && (stateJoystick.lY >= maximumThresholdLeft_) )
	{
		pTrigger_[ TYPE_KEY_LEFT_DOWN ] = true;
	}
	if( (stateJoystick_.lY >= maximumThresholdLeft_) && !(stateJoystick.lY >= maximumThresholdLeft_) )
	{
		pRelease_[ TYPE_KEY_LEFT_DOWN ] = true;
	}
	if( (stateJoystick.lY >= maximumThresholdLeft_) )
	{
		++pRepeat_[ TYPE_KEY_LEFT_DOWN ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_LEFT_DOWN ] = 0;
	}
	
	// 右スティック左入力情報の作成
	if( !(stateJoystick_.lZ <= minimumThresholdRight_) && (stateJoystick.lZ <= minimumThresholdRight_) )
	{
		pTrigger_[ TYPE_KEY_RIGHT_LEFT ] = true;
	}
	if( (stateJoystick_.lZ <= minimumThresholdRight_) && !(stateJoystick.lZ <= minimumThresholdRight_) )
	{
		pRelease_[ TYPE_KEY_RIGHT_LEFT ] = true;
	}
	if( (stateJoystick.lZ <= minimumThresholdRight_) )
	{
		++pRepeat_[ TYPE_KEY_RIGHT_LEFT ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_RIGHT_LEFT ] = 0;
	}
	
	// 右スティック右入力情報の作成
	if( !(stateJoystick_.lZ >= maximumThresholdRight_) && (stateJoystick.lZ >= maximumThresholdRight_) )
	{
		pTrigger_[ TYPE_KEY_RIGHT_RIGHT ] = true;
	}
	if( (stateJoystick_.lZ >= maximumThresholdRight_) && !(stateJoystick.lZ >= maximumThresholdRight_) )
	{
		pRelease_[ TYPE_KEY_RIGHT_RIGHT ] = true;
	}
	if( (stateJoystick.lZ >= maximumThresholdRight_) )
	{
		++pRepeat_[ TYPE_KEY_RIGHT_RIGHT ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_RIGHT_RIGHT ] = 0;
	}
	
	// 右スティック上入力情報の作成
	if( !(stateJoystick_.lRz <= minimumThresholdRight_) && (stateJoystick.lRz <= minimumThresholdRight_) )
	{
		pTrigger_[ TYPE_KEY_RIGHT_UP ] = true;
	}
	if( (stateJoystick_.lRz <= minimumThresholdRight_) && !(stateJoystick.lRz <= minimumThresholdRight_) )
	{
		pRelease_[ TYPE_KEY_RIGHT_UP ] = true;
	}
	if( (stateJoystick.lRz <= minimumThresholdRight_) )
	{
		++pRepeat_[ TYPE_KEY_RIGHT_UP ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_RIGHT_UP ] = 0;
	}
	
	// 右スティック下入力情報の作成
	if( !(stateJoystick_.lRz >= maximumThresholdRight_) && (stateJoystick.lRz >= maximumThresholdRight_) )
	{
		pTrigger_[ TYPE_KEY_RIGHT_DOWN ] = true;
	}
	if( (stateJoystick_.lRz >= maximumThresholdRight_) && !(stateJoystick.lRz >= maximumThresholdRight_) )
	{
		pRelease_[ TYPE_KEY_RIGHT_DOWN ] = true;
	}
	if( (stateJoystick.lRz >= maximumThresholdRight_) )
	{
		++pRepeat_[ TYPE_KEY_RIGHT_DOWN ];
	}
	else
	{
		pRepeat_[ TYPE_KEY_RIGHT_DOWN ] = 0;
	}
	
	// ボタン入力情報の作成
	for( int counterJoystick = 0; counterJoystick < TYPE_MAX - TYPE_BUTTON_00; ++counterJoystick )
	{
		// トリガ情報の更新
		if( !(stateJoystick_.rgbButtons[ counterJoystick] & 0x80) && (stateJoystick.rgbButtons[ counterJoystick] & 0x80) )
		{
			pTrigger_[ counterJoystick + TYPE_BUTTON_00 ] = true;
		}

		// リリース情報の更新
		if( (stateJoystick_.rgbButtons[ counterJoystick] & 0x80) && !(stateJoystick.rgbButtons[ counterJoystick] & 0x80) )
		{
			pRelease_[ counterJoystick + TYPE_BUTTON_00 ] = true;
		}

		// リピート情報の更新
		if( (stateJoystick.rgbButtons[ counterJoystick] & 0x80) )
		{
			++pRepeat_[ counterJoystick + TYPE_BUTTON_00 ];
		}
		else
		{
			pRepeat_[ counterJoystick + TYPE_BUTTON_00 ] = 0;
		}
	}

	// ジョイスティック状態の更新
	stateJoystick_ = stateJoystick;
}

//==============================================================================
// Brief  : プレス判定
// Return : bool								: プレス判定
// Arg    : int typeKey							: 判定するキーの種類
//==============================================================================
bool InputPad::IsPress( int typeKey ) const
{
	// プレス判定
	if( typeKey < TYPE_BUTTON_00 )
	{	// 方向キーの時
		switch( typeKey )
		{
		case TYPE_KEY_LEFT_UP:
			if(stateJoystick_.lY <= minimumThresholdLeft_)
			{
				return true;
			}
			break;
		case TYPE_KEY_LEFT_DOWN:
			if(stateJoystick_.lY >= maximumThresholdLeft_)
			{
				return true;
			}
			break;
		case TYPE_KEY_LEFT_LEFT:
			if(stateJoystick_.lX <= minimumThresholdLeft_)
			{
				return true;
			}
			break;
		case TYPE_KEY_LEFT_RIGHT:
			if(stateJoystick_.lX >= maximumThresholdLeft_)
			{
				return true;
			}
			break;
		case TYPE_KEY_RIGHT_UP:
			if(stateJoystick_.lRz <= minimumThresholdRight_)
			{
				return true;
			}
			break;
		case TYPE_KEY_RIGHT_DOWN:
			if(stateJoystick_.lRz >= maximumThresholdRight_)
			{
				return true;
			}
			break;
		case TYPE_KEY_RIGHT_LEFT:
			if(stateJoystick_.lZ <= minimumThresholdRight_)
			{
				return true;
			}
			break;
		case TYPE_KEY_RIGHT_RIGHT:
			if(stateJoystick_.lZ >= maximumThresholdRight_)
			{
				return true;
			}
			break;
		default:
			break;
		}
	}
	else
	{	// ボタンの時
		if( stateJoystick_.rgbButtons[ typeKey - TYPE_BUTTON_00 ] & 0x80 )
		{
			return true;
		}
	}

	// 値の返却
	return false;
}

//==============================================================================
// Brief  : トリガー判定
// Return : bool								: トリガー判定
// Arg    : int typeKey							: 判定するキーの種類
//==============================================================================
bool InputPad::IsTrigger( int typeKey ) const
{
	// 値の返却
	return pTrigger_[ typeKey ];
}

//==============================================================================
// Brief  : リリース判定
// Return : bool								: リリース判定
// Arg    : int typeKey							: 判定するキーの種類
//==============================================================================
bool InputPad::IsRelease( int typeKey ) const
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
bool InputPad::IsRepeat( int typeKey, int timeBegin, int timeInterval ) const
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
int InputPad::GetTimePress( int typeKey ) const
{
	// 値の返却
	return pRepeat_[ typeKey ];
}

//==============================================================================
// Brief  : 左スティックのX軸傾きの取得
// Return : float								: 傾き割合
// Arg    : void								: なし
//==============================================================================
float InputPad::GetAxisLeftX( void ) const
{
	// 値の返却
	return static_cast< float >( stateJoystick_.lX ) / maximumTiltStick_;
}

//==============================================================================
// Brief  : 左スティックのY軸傾きの取得
// Return : float								: 傾き割合
// Arg    : void								: なし
//==============================================================================
float InputPad::GetAxisLeftY( void ) const
{
	// 値の返却
	return static_cast< float >( stateJoystick_.lY ) / maximumTiltStick_;
}

//==============================================================================
// Brief  : 右スティックのX軸傾きの取得
// Return : float								: 傾き割合
// Arg    : void								: なし
//==============================================================================
float InputPad::GetAxisRightX( void ) const
{
	// 値の返却
	return static_cast< float >( stateJoystick_.lZ ) / maximumTiltStick_;
}

//==============================================================================
// Brief  : 右スティックのY軸傾きの取得
// Return : float								: 傾き割合
// Arg    : void								: なし
//==============================================================================
float InputPad::GetAxisRightY( void ) const
{
	// 値の返却
	return static_cast< float >( stateJoystick_.lRz ) / maximumTiltStick_;
}

//==============================================================================
// Brief  : ゲームパッド数の取得
// Return : int									: ゲームパッド数
// Arg    : void								: なし
//==============================================================================
int InputPad::GetCount( void ) const
{
	// 値の返却
	return countDevice_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void InputPad::InitializeSelf( void )
{
	// メンバ変数の初期化
	countDevice_ = 0;
	maximumDevice_ = 0;
	maximumTiltStick_ = 1000;
	minimumTiltStick_ = -1000;
	maximumThresholdLeft_ = 30;
	maximumThresholdRight_ = -30;
	minimumThresholdLeft_ = 30;
	minimumThresholdRight_ = -30;
	for( int counterKey = 0; counterKey < TYPE_MAX; ++counterKey )
	{
		pState_[ counterKey ] = false;
		pTrigger_[ counterKey ] = false;
		pRelease_[ counterKey ] = false;
		pRepeat_[ counterKey ] = 0;
	}
}

//==============================================================================
// Brief  : デバイスの列挙
// Return : BOOL CALLBACK						: 実行結果
// Arg    : const DIDEVICEINSTANCE* pDeviceInstance	: デバイスのインスタンス
// Arg    : VOID* pContext						: 値の受け取り用
//==============================================================================
BOOL CALLBACK InputPad::EnumDevicesCallback( const DIDEVICEINSTANCE* pDeviceInstance, VOID* pContext )
{
	// デバイスの作成
	HRESULT		result;					// 実行結果
	InputPad*	pThis = nullptr;		// クラスのポインタ
	pThis = reinterpret_cast< InputPad* >( pContext );
	result = pThis->pDirectInput_->CreateDevice(pDeviceInstance->guidInstance, &pThis->pDevice_, nullptr);
	if( FAILED( result ) )
	{
		return DIENUM_CONTINUE;
	}

	// 必要な数だけ続ける
	++pThis->countDevice_;
	if(pThis->countDevice_ < pThis->maximumDevice_)
	{
		return DIENUM_CONTINUE;
	}
	
	// 列挙の終了
	return DIENUM_STOP;
}

//==============================================================================
// Brief  : デバイスオブジェクトの列挙
// Return : BOOL CALLBACK						: 実行結果
// Arg    : const DIDEVICEOBJECTINSTANCE* pDeviceObjectInstance	: デバイスオブジェクトのインスタンス
// Arg    : VOID* pContext						: 値の受け取り用
//==============================================================================
BOOL CALLBACK InputPad::EnumDeviceObjectsCallback( const DIDEVICEOBJECTINSTANCE* pDeviceObjectInstance, VOID* pContext )
{
	// デバイスの設定を作成
	DIPROPRANGE propertyPad;			// デバイスの設定
	HRESULT		result;					// 実行結果
	InputPad*	pThis = nullptr;		// クラスのポインタ
	propertyPad.diph.dwSize = sizeof( DIPROPRANGE );
	propertyPad.diph.dwHeaderSize = sizeof( DIPROPHEADER );
	propertyPad.diph.dwHow = DIPH_BYID;
	propertyPad.diph.dwObj = pDeviceObjectInstance->dwType;
	propertyPad.lMin = (pThis)->minimumTiltStick_;
	propertyPad.lMax = (pThis)->maximumTiltStick_;
	
	// 作成途中
	result = pThis->pDevice_->SetProperty(DIPROP_RANGE, &propertyPad.diph);
	if( FAILED( result ) )
	{
		return DIENUM_STOP;
	}
	
	// 続行
	return DIENUM_CONTINUE;
}
