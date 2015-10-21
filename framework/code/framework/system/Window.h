//==============================================================================
//
// File   : Window.h
// Brief  : ウィンドウクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_WINDOW_H
#define MY_WINDOW_H

//******************************************************************************
// インクルード
//******************************************************************************
#include <windows.h>
#include <stdio.h>

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************

//******************************************************************************
// クラス定義
//******************************************************************************
class Window
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Window( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	virtual ~Window( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
	// Arg    : int typeShow						: 表示の種類
	// Arg    : int width							: 幅
	// Arg    : int height							: 高さ
	// Arg    : TCHAR* pCaption						: キャプション
	// Arg    : TCHAR* pNameClass					: クラス名
	//==============================================================================
	virtual int Initialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : HINSTANCE instanceHandle			: インスタンスハンドル
	// Arg    : int typeShow						: 表示の種類
	// Arg    : int width							: 幅
	// Arg    : int height							: 高さ
	// Arg    : TCHAR* pCaption						: キャプション
	// Arg    : TCHAR* pNameClass					: クラス名
	//==============================================================================
	virtual int Reinitialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Window* pOut						: コピー先アドレス
	//==============================================================================
	virtual int Copy( Window* pOut ) const;

	//==============================================================================
	// Brief  : デフォルトのウィンドウプロシージャ
	// Return : LRESULT CALLBACK					: 実行結果
	// Arg    : HWND windowHandle					: ウィンドウハンドル
	// Arg    : UINT message						: メッセージの識別子
	// Arg    : WPARAM wParam						: パラメータ
	// Arg    : LPARAM lParam						: パラメータ
	//==============================================================================
	static LRESULT CALLBACK WindowProcedureDefault( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam );

	//==============================================================================
	// Brief  : ウィンドウプロシージャ
	// Return : LRESULT								: 実行結果
	// Arg    : HWND windowHandle					: ウィンドウハンドル
	// Arg    : UINT message						: メッセージの識別子
	// Arg    : WPARAM wParam						: パラメータ
	// Arg    : LPARAM lParam						: パラメータ
	//==============================================================================
	virtual LRESULT WindowProcedure( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetWindowHandle( HWND value );
	HWND GetWindowHandle( void ) const;
	void SetWindowHandleParent( const HWND& value );
	void GetWindowHandleParent( HWND* pOut ) const;
	void SetWidth( int value );
	int GetWidth( void ) const;
	void SetHeight( int value );
	int GetHeight( void ) const;

protected:
	static Window*	pThis_;						// 自身のアドレス
	WNDCLASSEX		windowClass_;				// ウィンドウクラス
	HWND			windowHandle_;				// ウィンドウハンドル
	HWND			windowHandleParent_;		// 親ウィンドウハンドル
	int				width_;						// 幅
	int				height_;					// 高さ

private:
	virtual void InitializeSelf( void );
	Window( const Window& );
	Window operator=( const Window& );
};

#endif	// MY_WINDOW_H
