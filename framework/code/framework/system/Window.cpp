//==============================================================================
//
// File   : Window.cpp
// Brief  : ウィンドウクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Window.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
Window* Window::pThis_;		// 自身のアドレス

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Window::Window( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Window::~Window( void )
{
	// 終了処理
	Finalize();
}

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
int Window::Initialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass )
{
	// 未使用宣言
	UNREFERENCED_PARAMETER( instanceHandle );
	UNREFERENCED_PARAMETER( typeShow );
	UNREFERENCED_PARAMETER( width );
	UNREFERENCED_PARAMETER( height );
	UNREFERENCED_PARAMETER( pCaption );
	UNREFERENCED_PARAMETER( pNameClass );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Window::Finalize( void )
{
	// 登録の解除
	UnregisterClass( windowClass_.lpszClassName, windowClass_.hInstance );

	// ウィンドウの破棄
	if( windowHandle_ != NULL )
	{
		DestroyWindow( windowHandle_ );
		windowHandle_ = NULL;
	}

	// 格納領域の開放
	delete[] pThis_;
	pThis_ = nullptr;

	// クラス内部の初期化
	InitializeSelf();

	// 正常終了
	return 0;
}

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
int Window::Reinitialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( instanceHandle, typeShow, width, height, pCaption, pNameClass );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Window* pOut						: コピー先アドレス
//==============================================================================
int Window::Copy( Window* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : デフォルトのウィンドウプロシージャ
// Return : LRESULT CALLBACK					: 実行結果
// Arg    : HWND windowHandle					: ウィンドウハンドル
// Arg    : UINT message						: メッセージの識別子
// Arg    : WPARAM wParam						: パラメータ
// Arg    : LPARAM lParam						: パラメータ
//==============================================================================
LRESULT CALLBACK Window::WindowProcedureDefault( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam )
{
	// 処理分岐
	Window*	pWindow = reinterpret_cast< Window* >( GetWindowLong( windowHandle, GWL_USERDATA ) );		// 送られてきたウィンドウのポインタ
	if( pWindow != nullptr )
	{
		// 個別の処理
		LRESULT	ret = pWindow->WindowProcedure( windowHandle, message, wParam, lParam );
		return ret;
	}
	else
	{
		// 自身のポインタを登録
		if( message == WM_CREATE || message == WM_INITDIALOG )
		{
			SetWindowLong( windowHandle, GWL_USERDATA, (LONG)pThis_ );
			SendMessage( windowHandle, message, wParam, lParam );
			pThis_ = nullptr;
		}
	}

	// 既定の処理を提供
	return DefWindowProc( windowHandle, message, wParam, lParam );
}

//==============================================================================
// Brief  : ウィンドウプロシージャ
// Return : LRESULT								: 実行結果
// Arg    : HWND windowHandle					: ウィンドウハンドル
// Arg    : UINT message						: メッセージの識別子
// Arg    : WPARAM wParam						: パラメータ
// Arg    : LPARAM lParam						: パラメータ
//==============================================================================
LRESULT Window::WindowProcedure( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam )
{
	// メッセージごとの処理
	switch( message )
	{
	// ウィンドウが作成されたとき
	case WM_CREATE:
		break;

	// ウィンドウが破棄されるとき
	case WM_DESTROY:
		break;

	// キー入力があったとき
	case WM_KEYDOWN:
		break;

	// マウスの左ボタンが押されたとき
	case WM_LBUTTONDOWN:
		SetFocus( windowHandle );
		break;

	// その他
	default:
		break;
	}

	// 既定の処理を提供
	return DefWindowProc( windowHandle, message, wParam, lParam );
}

//==============================================================================
// Brief  : ウィンドウハンドルの設定
// Return : void								: なし
// Arg    : HWND value							: 設定する値
//==============================================================================
void Window::SetWindowHandle( HWND value )
{
	// 値の設定
	windowHandle_ = value;
}

//==============================================================================
// Brief  : ウィンドウハンドルの取得
// Return : HWND								: 取得する値
// Arg    : void								: なし
//==============================================================================
HWND Window::GetWindowHandle( void ) const
{
	// 値の返却
	return windowHandle_;
}

//==============================================================================
// Brief  : 親ウィンドウハンドルの設定
// Return : void								: なし
// Arg    : const HWND& value					: 設定する値
//==============================================================================
void Window::SetWindowHandleParent( const HWND& value )
{
	// 値の設定
	windowHandleParent_ = value;
}

//==============================================================================
// Brief  : 親ウィンドウハンドルの取得
// Return : void								: なし
// Arg    : HWND* pOut							: 値の格納アドレス
//==============================================================================
void Window::GetWindowHandleParent( HWND* pOut ) const
{
	// 値の返却
	*pOut = windowHandleParent_;
}

//==============================================================================
// Brief  : 幅の設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void Window::SetWidth( int value )
{
	// 値の設定
	width_ = value;
}

//==============================================================================
// Brief  : 幅の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int Window::GetWidth( void ) const
{
	// 値の返却
	return width_;
}

//==============================================================================
// Brief  : 高さの設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void Window::SetHeight( int value )
{
	// 値の設定
	height_ = value;
}

//==============================================================================
// Brief  : 高さの取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int Window::GetHeight( void ) const
{
	// 値の返却
	return height_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Window::InitializeSelf( void )
{
	// メンバ変数の初期化
	pThis_ = nullptr;
	ZeroMemory( &windowClass_, sizeof( WNDCLASSEX ) );
	windowHandle_ = NULL;
	windowHandleParent_ = NULL;
	width_ = 0;
	height_ = 0;
}
