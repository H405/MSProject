//==============================================================================
//
// File   : Main.cpp
// Brief  : メイン関数
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
// メモリリーク検出
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "Main.h"
#include "ManagerMain.h"
#include "../framework/system/FrameCount.h"
#include "../framework/develop/Debug.h"

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// prototype
//******************************************************************************

//******************************************************************************
// global member
//******************************************************************************
ManagerMain	g_manager_;			// マネージャー
FrameCount	g_frameCount_;		// フレームカウント

//==============================================================================
// Brief  ： メイン関数
// Return ： int							： 実行結果
//        ： APIENTRY						： Win32AD3DX_PI関数を呼び出す時の規約
// Arg    ： HINSTANCE hInstance			： このアプリケーションのインスタンスハンドル
// Arg    ： HINSTANCE hPrevInstance		： 常にNULL（16bit時代の名残り）
// Arg    ： LPTSTR lpCmdLine				： コマンドラインから受け取った引数へのポインタ
// Arg    ： int nCmdShow					： アプリケーションの初期ウインドウ表示方法の指定
//==============================================================================
int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
#ifdef _DEBUG
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//	_CrtSetBreakAlloc( 99 );
#endif

	// 未使用宣言
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	// フレームカウントの初期化
	int		result;		// 実行結果
	result = g_frameCount_.Initialize( hInstance, nCmdShow, &g_manager_, MAIN_FPS_UPDATE_INTERVAL, MAIN_FPS_NUM_FRAME_DEST );
	if( result != 0 )
	{
		return result;
	}

	// フレームカウントの実行
	int		resultApplication;		// アプリケーションの実行結果
	resultApplication = g_frameCount_.Execute();

	// 終了処理
	result = g_frameCount_.Finalize();
	if( result != 0 )
	{
		return result;
	}

	result = g_manager_.Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return resultApplication;
}