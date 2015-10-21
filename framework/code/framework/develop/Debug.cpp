//==============================================================================
// 
// File   : Debug.h
// Brief  : デバッグ処理
// Author : Taiga Shirakawa
// Date   : 2014/03/26 thr ： Taiga Shirakawa ： create
// 
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <stdarg.h>
#include <stdio.h>
#include "debug.h"

//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEBUG_OUTPUT_STRING_LEN		(256)		// 最大表示文字数

//******************************************************************************
// value
//******************************************************************************
#ifdef _DEBUG
DWORD	g_dwDebugMeasureStartTime = 0;			// 計測開始時間
BOOL	g_bWindowModeDebug = TRUE;				// ウィンドウモード
#endif
HWND	g_hWndDebug = NULL;						// メッセージボックス用ウィンドウハンドル

//==============================================================================
// Brief  ： メッセージ表示
// Return ： void							： なし
// Arg    ： TCHAR *pFormat					： 表示メッセージフォーマット
//==============================================================================
void PrintMessageToMessageBox( TCHAR *pFormat, ... )
{
	TCHAR	aStr[ DEBUG_OUTPUT_STRING_LEN ];		// 表示文字列
	va_list	args;									// 引数
	
	// 表示文字列作成
	va_start( args, pFormat );
	_vsntprintf_s( &aStr[ 0 ], DEBUG_OUTPUT_STRING_LEN, _TRUNCATE, pFormat, args );
	va_end( args );

	// メッセージボックスに出力
	MessageBox( g_hWndDebug, &aStr[ 0 ], _T( "Message" ), MB_OK );
}

#ifdef _DEBUG
//==============================================================================
// Brief  ： 初期化処理
// Return ： void							： なし
// Arg    ： HWND hWnd						： ウィンドウハンドル
// Arg    ： BOOL bWndMode					： ウィンドウモードフラグ
//==============================================================================
void DebugInitDebug( HWND hWnd, BOOL bWndMode )
{
	g_hWndDebug = hWnd;
	g_bWindowModeDebug = bWndMode;
}

//==============================================================================
// Brief  ： デバッグメッセージ表示
// Return ： void							： なし
// Arg    ： TCHAR *pFormat					： 表示メッセージフォーマット
//==============================================================================
void PrintMessageToDebugWindow( TCHAR *pFormat, ... )
{
	TCHAR	aStr[ DEBUG_OUTPUT_STRING_LEN ];		// 表示文字列
	va_list	args;									// 引数
	
	// 表示文字列作成
	va_start( args, pFormat );
	_vsntprintf_s( &aStr[ 0 ], DEBUG_OUTPUT_STRING_LEN, _TRUNCATE, pFormat, args );
	va_end( args );

	// デバッグウィンドウに出力
	OutputDebugString( &aStr[ 0 ] );
}

//==============================================================================
// Brief  ： 警告
// Return ： void							： なし
// Arg    ： TCHAR *pFileName				： ファイル名
// Arg    ： int *nLine						： 行番号
// Arg    ： TCHAR *pFormat					： 表示メッセージフォーマット
//==============================================================================
void DebugWarning( TCHAR *pFileName, int nLine, TCHAR *pFormat, ... )
{
	TCHAR	aStr[ DEBUG_OUTPUT_STRING_LEN ];		// 表示文字列
	va_list	args;									// 引数
	
	// 表示文字列作成
	va_start( args, pFormat );
	_vsntprintf_s( &aStr[ 0 ], DEBUG_OUTPUT_STRING_LEN, _TRUNCATE, pFormat, args );
	va_end( args );

	// エラーメッセージ出力
	PrintMessageToMessageBox( _T( "＊＊＊＊＊WARNING＊＊＊＊＊\n%sの%d行目\n%s\n" ), pFileName, nLine, &aStr[ 0 ] );
	PrintMessageToDebugWindow( _T( "＊＊＊＊＊WARNING＊＊＊＊＊\n%sの%d行目\n%s\n" ), pFileName, nLine, &aStr[ 0 ] );
}

//==============================================================================
// Brief  ： アサート
// Return ： void							： なし
// Arg    ： TCHAR *pExp					： 判定条件式文字列
// Arg    ： TCHAR *pFileName				： ファイル名
// Arg    ： int *nLine						： 行番号
// Arg    ： TCHAR *pFormat					： 表示メッセージフォーマット
//==============================================================================
void DebugAssert( TCHAR *pExp, TCHAR *pFileName, int nLine, TCHAR *pFormat, ... )
{
	TCHAR	aStr[ DEBUG_OUTPUT_STRING_LEN ];		// 表示文字列
	va_list	args;									// 引数
	
	// 表示文字列作成
	va_start( args, pFormat );
	_vsntprintf_s( &aStr[ 0 ], DEBUG_OUTPUT_STRING_LEN, _TRUNCATE, pFormat, args );
	va_end( args );

	// エラーメッセージ出力
	PrintMessageToMessageBox( _T( "＊＊＊＊＊ASSERT＊＊＊＊＊\n%sの%d行目\n%s\n%s\n" ), pFileName, nLine, pExp, &aStr[ 0 ] );
	PrintMessageToDebugWindow( _T( "\n＊＊＊＊＊ASSERT＊＊＊＊＊\n%sの%d行目\n%s\n%s\n\n" ), pFileName, nLine, pExp, &aStr[ 0 ] );

	// 終了
	if( !g_bWindowModeDebug )
	{	// フルスクリーンモードのときはブレークしない
		abort(  );
	}
	if( MessageBox( g_hWndDebug, _T( "デバッグを終了しますか？\n" ), _T( "確認" ), MB_YESNO ) == IDYES )
	{
		abort(  );
	}
}

//==============================================================================
// Brief  ： 時間計測開始
// Return ： void							： なし
// Arg    ： void							： なし
//==============================================================================
void DebugBeginMeasureTime( void )
{
	g_dwDebugMeasureStartTime = timeGetTime(  );
}

//==============================================================================
// Brief  ： 時間計測終了
// Return ： DWORD							： 計測結果
// Arg    ： DEBUG_MEASURE_DISP_TYPE type	： 計測結果表示方法
//==============================================================================
DWORD DebugEndMeasureTime( DEBUG_MEASURE_DISP_TYPE type )
{
	DWORD	dwMeasureTime = timeGetTime(  ) - g_dwDebugMeasureStartTime;		// 計測結果

	// 計測結果の表示
	switch( type )
	{
	case DEBUG_MEASURE_DISP_TYPE_MSGBOX:
		PrintMessageToMessageBox( _T( "計測結果 : %d ミリ秒\n" ), dwMeasureTime );
		break;
	case DEBUG_MEASURE_DISP_TYPE_DEBUGWND:
		PrintMessageToDebugWindow( _T( "計測結果 : %d ミリ秒\n" ), dwMeasureTime );
		break;
	default:
		break;
	}

	// 計測結果を返す
	return dwMeasureTime;
}
#endif	// _DEBUG
