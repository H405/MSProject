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
//==============================================================================
int RenderTarget::Initialize( IDirect3DDevice9* pDevice )
{
	// メンバ変数の設定
	pDevice_ = pDevice;

	// テクスチャサーフェイスの生成
	IDirect3DSurface9*	pSurfaceDepthCurrent = nullptr;		// 現在のレンダーターゲット
	D3DSURFACE_DESC		descSurfaceDepth;					// サーフェイス情報
	unsigned int		widthSurface;						// サーフェイスの幅
	unsigned int		heightSurface;						// サーフェイスの高さ
	int					result;								// 実行結果
	pDevice_->GetRenderTarget( 0, &pSurfaceDepthCurrent );
	pSurfaceDepthCurrent->GetDesc( &descSurfaceDepth );
	widthSurface = descSurfaceDepth.Width;
	heightSurface = descSurfaceDepth.Height;
	pSurfaceDepthCurrent->Release();
	pSurfaceDepthCurrent = nullptr;
	result = D3DXCreateTexture( pDevice_, widthSurface, heightSurface, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pTexture_ );
	if( result != 0 )
	{
		return 0;
	}

	// 深度バッファの生成
	D3DSURFACE_DESC	descSurfaceTexture;		// サーフェイス情報
	unsigned int	widthTexture;			// サーフェイスの幅
	unsigned int	heightTexture;			// サーフェイスの高さ
	pTexture_->GetSurfaceLevel( 0, &pSurfaceTexture_ );
	pSurfaceTexture_->GetDesc( &descSurfaceTexture );
	widthTexture = descSurfaceTexture.Width;
	heightTexture = descSurfaceTexture.Height;
	result = pDevice_->CreateDepthStencilSurface( widthTexture, heightTexture, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, FALSE, &pSurfaceDepth_, nullptr );
	if( result != 0 )
	{
		return 0;
	}

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
	// テクスチャの開放
	if( pTexture_ != nullptr )
	{
		pTexture_->Release();
		pTexture_ = nullptr;
	}

	// テクスチャサーフェイスの開放
	if( pSurfaceTexture_ != nullptr )
	{
		pSurfaceTexture_->Release();
		pSurfaceTexture_ = nullptr;
	}

	// 深度バッファの開放
	if( pSurfaceDepth_ != nullptr )
	{
		pSurfaceDepth_->Release();
		pSurfaceDepth_ = nullptr;
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
//==============================================================================
int RenderTarget::Reinitialize( IDirect3DDevice9* pDevice )
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
	pDevice_->SetDepthStencilSurface( pSurfaceDepth_ );
}

//==============================================================================
// Brief  : 登録IDの設定
// Return : void								: なし
// Arg    : IDirect3DTexture9* pValue			: 設定する値
//==============================================================================
void RenderTarget::SetTexture( IDirect3DTexture9* pValue )
{
	// 値の設定
	pTexture_ = pValue;
}

//==============================================================================
// Brief  : 登録IDの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DTexture9* RenderTarget::GetTexture( void ) const
{
	// 値の返却
	return pTexture_;
}

//==============================================================================
// Brief  : テクスチャサーフェイスの設定
// Return : void								: なし
// Arg    : IDirect3DSurface9* pValue			: 設定する値
//==============================================================================
void RenderTarget::SetSurfaceTexture( IDirect3DSurface9* pValue )
{
	// 値の設定
	pSurfaceTexture_ = pValue;
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
// Brief  : 深度バッファの設定
// Return : void								: なし
// Arg    : IDirect3DSurface9* pValue			: 設定する値
//==============================================================================
void RenderTarget::SetSurfaceDepth( IDirect3DSurface9* pValue )
{
	// 値の設定
	pSurfaceDepth_ = pValue;
}

//==============================================================================
// Brief  : 深度バッファの取得
// Return : IDirect3DSurface9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DSurface9* RenderTarget::GetSurfaceDepth( void ) const
{
	// 値の返却
	return pSurfaceDepth_;
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
	pSurfaceDepth_ = nullptr;
	isEnable_ = true;
}
