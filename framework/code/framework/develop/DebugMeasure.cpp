//==============================================================================
//
// File   : DebugMeasure.cpp
// Brief  : デバッグ計測処理
// Author : Taiga Shirakawa
// Date   : 2015/11/04 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <stdio.h>
#include <stdarg.h>
#include "DebugMeasure.h"
#include "Debug.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
TCHAR*	ManagerDebugMeasure::pBuffer_ = nullptr;		// 文字列格納用バッファ

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerDebugMeasure::Initialize( void )
{
	// バッファの確保
	pBuffer_ = nullptr;
	pBuffer_ = new TCHAR[ MAXIMUM_SIZE_BUFFER ];
	if( pBuffer_ == nullptr )
	{
		return 1;
	}
	ZeroMemory( pBuffer_, sizeof( TCHAR ) * MAXIMUM_SIZE_BUFFER );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerDebugMeasure::Finalize( void )
{
	// 格納了以域の開放
	delete[] pBuffer_;
	pBuffer_ = nullptr;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : ログの設定
// Return : int									: 実行結果
// Arg    : const TCHAR* pLog					: ログ
//==============================================================================
void ManagerDebugMeasure::SetLog( const TCHAR* pLog )
{
	// 文字列をバッファへ追加
	_tcscat_s( pBuffer_, MAXIMUM_SIZE_BUFFER, pLog );
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerDebugMeasure::Update( void )
{
	// ログの出力
	PrintDebug( pBuffer_ );

	// バッファを空にする
	ZeroMemory( pBuffer_, sizeof( TCHAR ) * MAXIMUM_SIZE_BUFFER );
}

//==============================================================================
// Brief  : コンストラクタ
// Return : int									: 実行結果
// Arg    : const TCHAR* pLog					: ログ
//==============================================================================
DebugMeasure::DebugMeasure( TCHAR* pFormat, ... )
{
	// バッファの確保
	pBuffer_ = nullptr;
	pBuffer_ = new TCHAR[ 256 ];
	if( pBuffer_ == nullptr )
	{
		return;
	}

	ZeroMemory( pBuffer_, sizeof( TCHAR ) * 256 );

	// 表示文字列作成
	TCHAR	pStringAdd[ 256 ] = {};		// 追加する文字列
	va_list	args;						// 引数
	va_start( args, pFormat );
	_vsntprintf_s( pStringAdd, 256, _TRUNCATE, pFormat, args );
	va_end( args );

	// 表示文字列記録
	_tcscat_s( pBuffer_, 256, pStringAdd );

	// 計測の開始
	timeBegin_ = timeGetTime();
}

//==============================================================================
// Brief  : デストラクタ
// Return : void								: 
// Arg    : void								: なし
//==============================================================================
DebugMeasure::~DebugMeasure( void )
{
	// 計測の終了
	DWORD	time;		// 時間
	time = timeGetTime() - timeBegin_;

	// ログの設定
	TCHAR	pLog[ 256 ] = {};			// ログ
	TCHAR	pMeasure[ 64 ] = {};		// 計測結果文字列
	_stprintf_s( pMeasure, 64, _T( " : %5dms\n" ), time );
	_tcscpy_s( pLog, 256, pBuffer_ );
	_tcscat_s( pLog, 256, pMeasure );
	ManagerDebugMeasure::SetLog( pLog );

	// バッファの開放
	delete[] pBuffer_;
	pBuffer_ = nullptr;
}
