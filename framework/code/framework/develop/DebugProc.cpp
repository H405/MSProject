//==============================================================================
//
// File   : DebugProc.cpp
// Brief  : デバッグ表示
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <stdio.h>
#include <stdarg.h>
#include "DebugProc.h"
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
ID3DXFont*	DebugProc::pFont_;				// フォント
TCHAR*		DebugProc::pBuffer_;			// 文字列格納用バッファ
bool		DebugProc::isVisible_;			// 表示するか
RECT		DebugProc::rectDisplay_;		// 表示する領域
D3DXCOLOR	DebugProc::colorCharacter_;		// 文字の色

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
//==============================================================================
int DebugProc::Initialize( IDirect3DDevice9* pDevice )
{
	// クラス内の初期化処理
	InitializeSelf();

	// メンバ変数の設定
	pBuffer_ = new TCHAR[ MAXIMUM_SIZE_BUFFER ];
	ZeroMemory( pBuffer_, sizeof( TCHAR ) * MAXIMUM_SIZE_BUFFER );
	rectDisplay_.left = 0;
	rectDisplay_.right = 1000;
	rectDisplay_.top = 0;
	rectDisplay_.bottom = 1000;

	// 情報表示用フォントを設定
	if( FAILED( D3DXCreateFont( pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T( "Terminal" ), &pFont_ ) ) )
	{
		return E_FAIL;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int DebugProc::Finalize( void )
{
	// 格納領域の開放
	if( pFont_ != nullptr )
	{
		pFont_->Release();
		pFont_ = nullptr;
	}

	delete[] pBuffer_;
	pBuffer_ = nullptr;

	// クラス内部の初期化
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
//==============================================================================
int DebugProc::Reinitialize( IDirect3DDevice9* pDevice )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice );
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DebugProc::Update( void )
{
}

//==============================================================================
// Brief  : 描画処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DebugProc::Draw( void )
{
	// デバッグ情報非表示
	if( !isVisible_ )
	{
		return;
	}

	// テキスト描画
	pFont_->DrawText( NULL, pBuffer_, -1, &rectDisplay_, DT_LEFT, colorCharacter_ );
}

//==============================================================================
// Brief  : バッファのクリア
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DebugProc::ClearBuffer( void )
{
	// バッファクリア
	ZeroMemory( pBuffer_, sizeof( TCHAR ) * MAXIMUM_SIZE_BUFFER );
}

//==============================================================================
// Brief  : デバッグ文字列の表示
// Return : void								: なし
// Arg    : const TCHAR *pFormat				: 文字フォーマット
//==============================================================================
void DebugProc::Print( const TCHAR *pFormat, ... )
{
	// エラーチェック
#ifndef _DEVELOP
	MessageBox( NULL, _T( "PrintDebug関数呼び出しエラー" ), _T( "エラー" ), MB_OK );
	abort();
#endif
	Assert( pFont_ != nullptr, _T( "フォントオブジェクトが作成されていません。" ) );

	// デバッグ情報非表示
	if( !isVisible_ )
	{
		return;
	}

	// 表示文字列作成
	TCHAR	pStringAdd[ 256 ] = {};		// 追加する文字列
	va_list	args;						// 引数
	va_start( args, pFormat );
	_vsntprintf_s( pStringAdd, 256, _TRUNCATE, pFormat, args );
	va_end( args );

	// 表示文字列記録
	_tcscat_s( pBuffer_, MAXIMUM_SIZE_BUFFER, pStringAdd );
}

//==============================================================================
// Brief  : 表示するかの設定
// Return : void								: なし
// Arg    : bool value							: 設定する値
//==============================================================================
void DebugProc::SetIsVisible( bool value )
{
	// 値の設定
	isVisible_ = value;
}

//==============================================================================
// Brief  : 表示するかの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
bool DebugProc::GetIsVisible( void )
{
	// 値の返却
	return isVisible_;
}

//==============================================================================
// Brief  : 表示するかの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
bool DebugProc::IsVisible( void )
{
	// 値の返却
	return isVisible_;
}

//==============================================================================
// Brief  : 表示する領域の設定
// Return : void								: なし
// Arg    : const RECT& value					: 設定する値
//==============================================================================
void DebugProc::SetRectDisplay( const RECT& value )
{
	// 値の設定
	rectDisplay_ = value;
}

//==============================================================================
// Brief  : 表示する領域の取得
// Return : void								: なし
// Arg    : RECT* pOut							: 値の格納アドレス
//==============================================================================
void DebugProc::GetRectDisplay( RECT* pOut )
{
	// 値の返却
	*pOut = rectDisplay_;
}

//==============================================================================
// Brief  : 文字の色の設定
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void DebugProc::SetColorCharacter( const D3DXCOLOR& value )
{
	// 値の設定
	colorCharacter_ = value;
}

//==============================================================================
// Brief  : 文字の色のRGBA値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void DebugProc::SetColorCharacter( float r, float g, float b, float a )
{
	// 値の設定
	colorCharacter_.r = r;
	colorCharacter_.g = g;
	colorCharacter_.b = b;
	colorCharacter_.a = a;
}

//==============================================================================
// Brief  : 文字の色のRGB値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
//==============================================================================
void DebugProc::SetColorCharacter( float r, float g, float b )
{
	// 値の設定
	colorCharacter_.r = r;
	colorCharacter_.g = g;
	colorCharacter_.b = b;
}

//==============================================================================
// Brief  : 文字の色のR値の設定
// Return : void								: なし
// Arg    : float r								: R値
//==============================================================================
void DebugProc::SetColorCharacterR( float r )
{
	// 値の設定
	colorCharacter_.r = r;
}

//==============================================================================
// Brief  : 文字の色のG値の設定
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void DebugProc::SetColorCharacterG( float g )
{
	// 値の設定
	colorCharacter_.g = g;
}

//==============================================================================
// Brief  : 文字の色のB値の設定
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void DebugProc::SetColorCharacterB( float b )
{
	// 値の設定
	colorCharacter_.b = b;
}

//==============================================================================
// Brief  : 文字の色のA値の設定
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void DebugProc::SetColorCharacterA( float a )
{
	// 値の設定
	colorCharacter_.a = a;
}

//==============================================================================
// Brief  : 文字の色のアルファ値の設定
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void DebugProc::SetColorCharacterAlpha( float alpha )
{
	// 値の設定
	colorCharacter_.a = alpha;
}

//==============================================================================
// Brief  : 文字の色の取得
// Return : void								: なし
// Arg    : D3DXCOLOR* pOut						: 値の格納アドレス
//==============================================================================
void DebugProc::GetColorCharacter( D3DXCOLOR* pOut )
{
	// 値の返却
	*pOut = colorCharacter_;
}

//==============================================================================
// Brief  : 文字の色のR値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float DebugProc::GetColorCharacterR( void )
{
	// 値の返却
	return colorCharacter_.r;
}

//==============================================================================
// Brief  : 文字の色のG値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float DebugProc::GetColorCharacterG( void )
{
	// 値の返却
	return colorCharacter_.g;
}

//==============================================================================
// Brief  : 文字の色のB値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float DebugProc::GetColorCharacterB( void )
{
	// 値の返却
	return colorCharacter_.b;
}

//==============================================================================
// Brief  : 文字の色のA値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float DebugProc::GetColorCharacterA( void )
{
	// 値の返却
	return colorCharacter_.a;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DebugProc::InitializeSelf( void )
{
	// メンバ変数の初期化
	pFont_ = nullptr;
	pBuffer_ = nullptr;
	isVisible_ = true;
	colorCharacter_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
}
