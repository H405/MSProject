//==============================================================================
// 
// File   : Debug.h
// Brief  : デバッグ処理
// Author : Taiga Shirakawa
// Date   : 2014/03/26 thr ： Taiga Shirakawa ： create
// 
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DEBUG_H
#define MY_DEBUG_H

//******************************************************************************
// インクルード
//******************************************************************************
#include <tchar.h>
#include <windows.h>

//******************************************************************************
// ライブラリ
//******************************************************************************
#pragma comment( lib, "winmm.lib" )

//******************************************************************************
// enumeration
//******************************************************************************
// 時間計測表示方法
typedef enum
{
	DEBUG_MEASURE_DISP_TYPE_NONE = 0,	// 表示なし
	DEBUG_MEASURE_DISP_TYPE_MSGBOX,		// メッセージボックス
	DEBUG_MEASURE_DISP_TYPE_DEBUGWND,	// デバッグウィンドウ
	DEBUG_MEASURE_DISP_TYPE_MAX			// 最大値
} DEBUG_MEASURE_DISP_TYPE;

//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEBUG_OUTPUT_DIRECTORY		"data/debug/"		// デバッグ書き出し用ディレクトリ

//******************************************************************************
// プロトタイプ宣言
//******************************************************************************
void PrintMessageToMessageBox( TCHAR *pFormat, ... );									// メッセージ表示
#ifdef _DEVELOP
void DebugInitDebug( HWND hWnd, BOOL bWndMode );										// 初期化処理
void PrintMessageToDebugWindow( TCHAR *pFormat, ... );									// デバッグメッセージ表示
void DebugWarning( TCHAR *pFileName, int nLine, TCHAR *pFormat, ... );					// 警告
void DebugAssert( TCHAR *pExp, TCHAR *pFileName, int nLine, TCHAR *pFormat, ... );		// アサート
void DebugBeginMeasureTime( void );														// 時間計測開始
DWORD DebugEndMeasureTime( DEBUG_MEASURE_DISP_TYPE type );								// 時間計測終了
#endif

//******************************************************************************
// 関数マクロ定義
//******************************************************************************
#define PrintMsgBox						PrintMessageToMessageBox

#ifdef _DEVELOP

#define InitDebug( hWnd, bWndMode )		DebugInitDebug( hWnd, bWndMode )
#define PrintDebugWnd( pFormat, ... )	PrintMessageToDebugWindow( pFormat, __VA_ARGS__ )
#define Warning( pFormat, ... )			DebugWarning( _T( __FILE__ ), __LINE__, pFormat, __VA_ARGS__ )
#define Assert( exp, pFormat, ... )		if( !( exp ) ){ DebugAssert( _T( #exp ), _T( __FILE__ ), __LINE__, pFormat, __VA_ARGS__ ); __asm int 3 }
#define BeginMeasureTime()				DebugBeginMeasureTime()
#define EndMeasureTime( type )			DebugEndMeasureTime( type )

#else

#define InitDebug( hWnd, bWndMode )		static_cast< void >( 0 )
#define PrintDebugWnd( format, ... )	static_cast< void >( 0 )
#define Warning( format, ... )			static_cast< void >( 0 )
#define Assert( exp, pFormat, ... )		static_cast< void >( 0 )
#define BeginMeasureTime(  )			static_cast< void >( 0 )
#define EndMeasureTime( type )			static_cast< void >( 0 )

#endif

#endif // MY_DEBUG_H
