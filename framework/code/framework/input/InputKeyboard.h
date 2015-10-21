//==============================================================================
//
// File   : InputKeyboard.h
// Brief  : キーボード入力クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_INPUT_KEYBOARD_H
#define MY_INPUT_KEYBOARD_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "Input.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************

//******************************************************************************
// クラス定義
//******************************************************************************
class InputKeyboard : public Input
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	InputKeyboard( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~InputKeyboard( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirectInput8* pDirectInput			: DirectInputオブジェクト
	// Arg    : HWND windowHandle					: ウィンドウハンドル
	//==============================================================================
	int Initialize( IDirectInput8* pDirectInput, HWND windowHandle );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirectInput8* pDirectInput			: DirectInputオブジェクト
	// Arg    : HWND windowHandle					: ウィンドウハンドル
	//==============================================================================
	int Reinitialize( IDirectInput8* pDirectInput, HWND windowHandle );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : InputKeyboard* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( InputKeyboard* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : プレス判定
	// Return : bool								: プレス判定
	// Arg    : int typeKey							: 判定するキーの種類
	//==============================================================================
	bool IsPress( int typeKey ) const;

	//==============================================================================
	// Brief  : トリガー判定
	// Return : bool								: トリガー判定
	// Arg    : int typeKey							: 判定するキーの種類
	//==============================================================================
	bool IsTrigger( int typeKey ) const;

	//==============================================================================
	// Brief  : リリース判定
	// Return : bool								: リリース判定
	// Arg    : int typeKey							: 判定するキーの種類
	//==============================================================================
	bool IsRelease( int typeKey ) const;

	//==============================================================================
	// Brief  : リピート判定
	// Return : bool								: リピート判定
	// Arg    : int typeKey							: 判定するキーの種類
	// Arg    : int timeBegin						: ONになるまでの時間
	// Arg    : int timeInterval					: ONになる間隔
	//==============================================================================
	bool IsRepeat( int typeKey, int timeBegin, int timeInterval ) const;

	//==============================================================================
	// Brief  : プレス時間の取得
	// Return : int									: プレス時間
	// Arg    : int typeKey							: 判定するキーの種類
	//==============================================================================
	int GetTimePress( int typeKey ) const;

	static const int	MAXIMUM_STATE = 256;;		// ステートの最大数

protected:

private:
	void InitializeSelf( void );
	InputKeyboard( const InputKeyboard& );
	InputKeyboard operator=( const InputKeyboard& );

	BYTE	pState_[ MAXIMUM_STATE ];		// キーの状態
	bool	pTrigger_[ MAXIMUM_STATE ];		// トリガーの状態
	bool	pRelease_[ MAXIMUM_STATE ];		// リリースの状態
	int		pRepeat_[ MAXIMUM_STATE ];		// リピートの状態
};

#endif	// MY_INPUT_KEYBOARD_H
