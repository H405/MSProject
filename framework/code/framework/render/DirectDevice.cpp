//==============================================================================
//
// File   : DirectDevice.cpp
// Brief  : Direct3Dデバイスクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/16 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <tchar.h>
#include "DirectDevice.h"
#include "../develop/Debug.h"

//******************************************************************************
// ライブラリ
//******************************************************************************
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

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
DirectDevice::DirectDevice( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
DirectDevice::~DirectDevice( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : HWND windowHandle					: ウィンドウハンドル
// Arg    : int width							: ウィンドウ幅
// Arg    : int height							: ウィンドウ高さ
// Arg    : bool isWindowMode					: ウィンドウモードフラグ
//==============================================================================
int DirectDevice::Initialize( HWND windowHandle, int width, int height, bool isWindowMode )
{
	// Direct3Dの初期化
	IDirect3D9*				pDirect3D;					// Direct3Dオブジェクト
	D3DPRESENT_PARAMETERS	presentParameter;			// プレゼントパラメータ
	D3DDISPLAYMODE			displayMode;				// ディスプレイモード
	int						countDisplayMode = 0;		// ディスプレイモードの数

	// Direct3Dオブジェクトの生成
	pDirect3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( pDirect3D == nullptr )
	{
		PrintMsgBox( _T( "Direct3Dオブジェクトの生成に失敗しました。" ) );
		return 1;
	}

	// フルスクリーンの確認
	if( !isWindowMode )
	{	// ウィンドウモードの指定がされていないとき
		if( MessageBox( NULL, _T( "フルスクリーンで起動しますか？\n" ), _T( "フルスクリーンの確認" ), MB_YESNO ) == IDYES )
		{
			isWindowMode_ = false;
		}
		else
		{
			isWindowMode_ = true;
		}
	}
	else
	{
		isWindowMode_ = true;
	}

	// ディスプレイモードの列挙
	if( !isWindowMode_ )
	{	// ウィンドウモードの指定がされていないとき
		countDisplayMode = pDirect3D->GetAdapterModeCount( D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8 );
		for( int nCntDisp = 0; nCntDisp < countDisplayMode; ++nCntDisp )
		{
			// ディスプレイモードの取得
			if( FAILED( pDirect3D->EnumAdapterModes( D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, nCntDisp, &displayMode ) ) )
			{
				PrintMsgBox( _T( "ディスプレイモードの取得に失敗しました。" ), _T( "エラー" ) );
				return 1;
			}

			// ディスプレイモードの決定
			if( static_cast< int >( displayMode.Width ) == width && static_cast< int >( displayMode.Height ) == height )
			{
				break;
			}
		}
	}

	// デバイスのプレゼンテーションパラメータの設定
	BOOL	flagWindowed;		// ウィンドウモード
	flagWindowed = (isWindowMode_ ? TRUE : FALSE);
	ZeroMemory( &presentParameter, sizeof( presentParameter ) );		// ワークをゼロクリア
	presentParameter.BackBufferCount		= 1;						// バックバッファの数
	presentParameter.BackBufferWidth		= width;					// ゲーム画面サイズ(幅)
	presentParameter.BackBufferHeight		= height;					// ゲーム画面サイズ(高さ)
	presentParameter.BackBufferFormat		= D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	presentParameter.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	presentParameter.Windowed				= flagWindowed;				// ウィンドウモード
	presentParameter.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	presentParameter.AutoDepthStencilFormat	= D3DFMT_D24S8;				// デプスバッファとして16bitを使う( 対応しているか確認した方がよい ) D3DFMT_D24S8 が良い
	presentParameter.hDeviceWindow			= windowHandle;

	if( isWindowMode_ )
	{	// ウィンドウモード
		presentParameter.BackBufferFormat			= D3DFMT_UNKNOWN;					// バックバッファ
		presentParameter.FullScreen_RefreshRateInHz	= 0;								// リフレッシュレート
		presentParameter.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル( ティアリングが起きる )
	}
	else
	{	// フルスクリーンモード
		presentParameter.BackBufferFormat			= D3DFMT_R5G6B5;					// バックバッファ
		presentParameter.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		presentParameter.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if( FAILED( pDirect3D->CreateDevice(	D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
											D3DDEVTYPE_HAL,							// ディスプレイタイプ
											windowHandle,							// フォーカスするウインドウへのハンドル
											D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
											&presentParameter,						// デバイスのプレゼンテーションパラメータ
											&pDevice_ ) ) )							// デバイスインターフェースへのポインタ
	{
		// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
		presentParameter.AutoDepthStencilFormat	= D3DFMT_D16;
		if( FAILED( pDirect3D->CreateDevice(	D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
												D3DDEVTYPE_HAL,							// ディスプレイタイプ
												windowHandle,							// フォーカスするウインドウへのハンドル
												D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
												&presentParameter,						// デバイスのプレゼンテーションパラメータ
												&pDevice_ ) ) )							// デバイスインターフェースへのポインタ
		{
			MessageBox( NULL, _T( "低画質モードで起動します。" ), _T( "確認" ), MB_OK );
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
			if( FAILED( pDirect3D->CreateDevice(	D3DADAPTER_DEFAULT, 
													D3DDEVTYPE_HAL, 
													windowHandle, 
													D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
													&presentParameter,
													&pDevice_ ) ) )
			{
				// 上記の設定が失敗したら
				// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
				if( FAILED( pDirect3D->CreateDevice(	D3DADAPTER_DEFAULT, 
														D3DDEVTYPE_REF,
														windowHandle, 
														D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
														&presentParameter,
														&pDevice_ ) ) )
				{
					// 初期化失敗
					PrintMsgBox( _T( "デバイスオブジェクトの初期化に失敗しました。" ) );
					return 1;
				}
			}
		}
	}

	// フルスクリーン時のダイアログ設定
	if( !isWindowMode_ )
	{
		pDevice_->SetDialogBoxMode( TRUE );
	}

	// Direct3Dオブジェクトの開放
	if( pDirect3D != nullptr )
	{
		pDirect3D->Release();
		pDirect3D = nullptr;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int DirectDevice::Finalize( void )
{
	// Direct3Dデバイスオブジェクトの開放
	if( pDevice_ != nullptr )
	{
		pDevice_->Release();
		pDevice_ = nullptr;
	}

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : HWND windowHandle					: ウィンドウハンドル
// Arg    : int width							: ウィンドウ幅
// Arg    : int height							: ウィンドウ高さ
// Arg    : bool isWindowMode					: ウィンドウモードフラグ
//==============================================================================
int DirectDevice::Reinitialize( HWND windowHandle, int width, int height, bool isWindowMode )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( windowHandle, width, height, isWindowMode );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : DirectDevice* pOut					: コピー先アドレス
//==============================================================================
int DirectDevice::Copy( DirectDevice* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : Direct3Dデバイスの取得
// Return : IDirect3DDevice9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DDevice9* DirectDevice::GetDevice( void ) const
{
	// 値の返却
	return pDevice_;
}

//==============================================================================
// Brief  : ウィンドウモードフラグの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
bool DirectDevice::GetIsWindowMode( void ) const
{
	// 値の返却
	return isWindowMode_;
}

//==============================================================================
// Brief  : ウィンドウモードフラグの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
bool DirectDevice::IsWindowMode( void ) const
{
	// 値の返却
	return isWindowMode_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void DirectDevice::InitializeSelf( void )
{
	// メンバ変数の初期化
	pDevice_ = nullptr;
}
