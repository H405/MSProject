//==============================================================================
//
// File   : WindowMain.cpp
// Brief  : メインウィンドウクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "WindowMain.h"

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
WindowMain::WindowMain( void ) : Window()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
WindowMain::~WindowMain( void )
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
int WindowMain::Initialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Window::Initialize( instanceHandle, typeShow, width, height, pCaption, pNameClass );
	if( result != 0 )
	{
		return result;
	}

	// 変数の設定
	pThis_ = this;
	width_ = width;
	height_ = height;

	// ウィンドウクラスの設定
	windowClass_.cbSize = sizeof( WNDCLASSEX );
	windowClass_.style = CS_CLASSDC;
	windowClass_.lpfnWndProc = WindowProcedureDefault;
	windowClass_.cbClsExtra = 0;
	windowClass_.cbWndExtra = 0;
	windowClass_.hInstance = instanceHandle;
	windowClass_.hIcon = NULL;
	windowClass_.hCursor = LoadCursor( NULL, IDC_ARROW );
	windowClass_.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	windowClass_.lpszMenuName = NULL;
	windowClass_.lpszClassName = pNameClass;
	windowClass_.hIconSm = NULL;

	// ウィンドウの登録
	RegisterClassEx( &windowClass_ );

	// ウィンドウの作成
	windowHandle_ = CreateWindowEx(	0,
									pNameClass,
									pCaption,
									WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
									CW_USEDEFAULT,
									CW_USEDEFAULT,
									width,
									height,
									windowHandleParent_,
									NULL,
									instanceHandle,
									NULL );
	if( windowHandle_ == NULL )
	{
		return 1;
	}

	// ウィンドウの表示
	ShowWindow( windowHandle_, typeShow );
	UpdateWindow( windowHandle_ );

	// ウィンドウの大きさを調整
	int		widthSet;		// クライアント領域調整用幅
	int		heightSet;		// クライアント領域調整用高さ
	RECT	rectWindow;		// ウィンドウ領域の大きさ
	RECT	rectClient;		// クライアント領域の大きさ
	GetClientRect( windowHandle_, &rectClient );
	GetWindowRect( windowHandle_, &rectWindow );
	GetClientRect( windowHandle_, &rectClient );
	widthSet = width + (rectWindow.right - rectWindow.left) - (rectClient.right - rectClient.left);
	heightSet = height + (rectWindow.bottom - rectWindow.top) - (rectClient.bottom - rectClient.top);
	SetWindowPos( windowHandle_, NULL, 0, 0, widthSet, heightSet, SWP_NOMOVE | SWP_NOZORDER );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int WindowMain::Finalize( void )
{
	// 格納領域の開放

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Window::Finalize();
	if( result != 0 )
	{
		return result;
	}

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
int WindowMain::Reinitialize( HINSTANCE instanceHandle, int typeShow, int width, int height, TCHAR* pCaption, TCHAR* pNameClass )
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
// Arg    : WindowMain* pOut					: コピー先アドレス
//==============================================================================
int WindowMain::Copy( WindowMain* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : ウィンドウプロシージャ
// Return : LRESULT								: 実行結果
// Arg    : HWND windowHandle					: ウィンドウハンドル
// Arg    : UINT message						: メッセージの識別子
// Arg    : WPARAM wParam						: パラメータ
// Arg    : LPARAM lParam						: パラメータ
//==============================================================================
LRESULT WindowMain::WindowProcedure( HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam )
{
	// メッセージごとの処理
	switch( message )
	{
	// ウィンドウが作成されたとき
	case WM_CREATE:
		break;

	// ウィンドウが破棄されるとき
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	// ウィンドウが閉じられるとき
	case WM_CLOSE:
		DestroyWindow( windowHandle_ );
		windowHandle_ = NULL;
		break;

	// キー入力があったとき
	case WM_KEYDOWN:
		switch( wParam )
		{
		case VK_ESCAPE:
			DestroyWindow( windowHandle_ );
			windowHandle_ = NULL;
			break;
		}
		break;

	// その他
	default:
		break;
	}

	// 既定の処理を提供
	return DefWindowProc( windowHandle, message, wParam, lParam );
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void WindowMain::InitializeSelf( void )
{
	// メンバ変数の初期化
}
