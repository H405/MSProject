//==============================================================================
//
// File   : DebugProc.h
// Brief  : デバッグ表示
// Author : Taiga Shirakawa
// Date   : 2015/10/09 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DEBUG_PROC_H
#define MY_DEBUG_PROC_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"
#include <windows.h>
#include <tchar.h>

//******************************************************************************
// ライブラリ
//******************************************************************************
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "d3d9.lib" )

//******************************************************************************
// マクロ定義
//******************************************************************************
#ifdef _DEBUG
#define PrintDebug( pFormat, ... )	DebugProc::Print( pFormat, __VA_ARGS__ )
#else
#define PrintDebug( pFormat, ... )	static_cast< void >( 0 )
#endif

//******************************************************************************
// クラス前方宣言
//******************************************************************************

//******************************************************************************
// クラス定義
//******************************************************************************
class DebugProc
{
public:
	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	//==============================================================================
	static int Initialize( IDirect3DDevice9* pDevice );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	static int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	//==============================================================================
	static int Reinitialize( IDirect3DDevice9* pDevice );

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	static void Update( void );

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	static void Draw( void );

	//==============================================================================
	// Brief  : バッファのクリア
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	static void ClearBuffer( void );

	//==============================================================================
	// Brief  : デバッグ文字列の表示
	// Return : void								: なし
	// Arg    : const TCHAR *pFormat				: 文字フォーマット
	//==============================================================================
	static void Print( const TCHAR *pFormat, ... );

	//==============================================================================
	// アクセサ
	//==============================================================================
	static void SetIsVisible( bool value );
	static bool GetIsVisible( void );
	static bool IsVisible( void );
	static void SetRectDisplay( const RECT& value );
	static void GetRectDisplay( RECT* pOut );
	static void SetColorCharacter( const D3DXCOLOR& value );
	static void SetColorCharacter( float r, float g, float b, float a );
	static void SetColorCharacter( float r, float g, float b );
	static void SetColorCharacterR( float r );
	static void SetColorCharacterG( float g );
	static void SetColorCharacterB( float b );
	static void SetColorCharacterA( float a );
	static void SetColorCharacterAlpha( float alpha );
	static void GetColorCharacter( D3DXCOLOR* pOut );
	static float GetColorCharacterR( void );
	static float GetColorCharacterG( void );
	static float GetColorCharacterB( void );
	static float GetColorCharacterA( void );

protected:

private:
	static void InitializeSelf( void );

	DebugProc( void );
	~DebugProc( void );
	DebugProc( const DebugProc& );
	DebugProc operator=( const DebugProc& );

	static const unsigned int	MAXIMUM_SIZE_BUFFER = 32768;		// バッファの最大サイズ

	static ID3DXFont*	pFont_;					// フォント
	static TCHAR*		pBuffer_;				// 文字列格納用バッファ
	static bool			isVisible_;				// 表示するか
	static RECT			rectDisplay_;			// 表示する領域
	static D3DXCOLOR	colorCharacter_;		// 文字の色
};

#endif	// MY_DEBUG_PROC_H
