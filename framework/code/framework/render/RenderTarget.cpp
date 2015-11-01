//==============================================================================
//
// File   : RenderTarget.cpp
// Brief  : 描画対象
// Author : Taiga Shirakawa
// Date   : 2015/10/10 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "RenderTarget.h"

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
RenderTarget::RenderTarget( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
RenderTarget::~RenderTarget( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int width							: 幅
// Arg    : int height							: 高さ
// Arg    : D3DFORMAT format					: テクスチャフォーマット
//==============================================================================
int RenderTarget::Initialize( IDirect3DDevice9* pDevice, int width, int height, D3DFORMAT format )
{
	// メンバ変数の設定
	pDevice_ = pDevice;

	// テクスチャサーフェイスの生成
	int			result;		// 実行結果
	result = D3DXCreateTexture( pDevice_, width, height, 1, D3DUSAGE_RENDERTARGET, format, D3DPOOL_DEFAULT, &pTexture_ );
	if( result != 0 )
	{
		return 0;
	}
	pTexture_->GetSurfaceLevel( 0, &pSurfaceTexture_ );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int RenderTarget::Finalize( void )
{
	// テクスチャサーフェイスの開放
	if( pSurfaceTexture_ != nullptr )
	{
		pSurfaceTexture_->Release();
		pSurfaceTexture_ = nullptr;
	}

	// テクスチャの開放
	if( pTexture_ != nullptr )
	{
		pTexture_->Release();
		pTexture_ = nullptr;
	}

	// クラス内部の初期化
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int width							: 幅
// Arg    : int height							: 高さ
// Arg    : D3DFORMAT format					: テクスチャフォーマット
//==============================================================================
int RenderTarget::Reinitialize( IDirect3DDevice9* pDevice, int width, int height, D3DFORMAT format )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, width, height, format );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : RenderTarget* pOut					: コピー先アドレス
//==============================================================================
int RenderTarget::Copy( RenderTarget* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画対象に設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
//==============================================================================
void RenderTarget::Set( int index )
{
	// デバイスにレンダーターゲットを設定
	pDevice_->SetRenderTarget( index, pSurfaceTexture_ );
}

//==============================================================================
// Brief  : テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* RenderTarget::GetTexture( void ) const
{
	// 値の返却
	return pTexture_;
}

//==============================================================================
// Brief  : テクスチャサーフェイスの取得
// Return : IDirect3DSurface9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DSurface9* RenderTarget::GetSurfaceTexture( void ) const
{
	// 値の返却
	return pSurfaceTexture_;
}

//==============================================================================
// Brief  : 有効フラグの設定
// Return : void								: なし
// Arg    : bool value							: 設定する値
//==============================================================================
void RenderTarget::SetIsEnable( bool value )
{
	// 値の設定
	isEnable_ = value;
}

//==============================================================================
// Brief  : 有効フラグの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
bool RenderTarget::GetIsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : 有効フラグの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
bool RenderTarget::IsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void RenderTarget::InitializeSelf( void )
{
	// メンバ変数の初期化
	pDevice_ = nullptr;
	pTexture_ = nullptr;
	pSurfaceTexture_ = nullptr;
	isEnable_ = true;
}
