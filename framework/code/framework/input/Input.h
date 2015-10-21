//==============================================================================
//
// File   : Input.h
// Brief  : 入力クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/11 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_INPUT_H
#define MY_INPUT_H

//******************************************************************************
// インクルード
//******************************************************************************
#include <windows.h>
#define DIRECTINPUT_VERSION (0x0800)    // 警告対策用
#include "dinput.h"

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
class Input
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Input( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Input( void );

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
	// Arg    : Input* pOut							: コピー先アドレス
	//==============================================================================
	int Copy( Input* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

protected:
	IDirectInput8*			pDirectInput_;		// DirectInputオブジェクト
	IDirectInputDevice8*	pDevice_;			// DirectInputデバイス

private:
	void InitializeSelf( void );
	Input( const Input& );
	Input operator=( const Input& );

};

#endif	// MY_INPUT_H
