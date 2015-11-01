//==============================================================================
//
// File   : RenderPass.cpp
// Brief  : パスクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "RenderPass.h"
#include "RenderPassParameter.h"
#include "RenderTarget.h"
#include "../develop/Debug.h"

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
RenderPass::RenderPass( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
RenderPass::~RenderPass( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int countRenderTarget				: レンダーターゲットの数
// Arg    : const RenderPassParameter* pParameter	: 描画対象パラメータ
//==============================================================================
int RenderPass::Initialize( IDirect3DDevice9* pDevice, int countRenderTarget, const RenderPassParameter* pParameter )
{
	// サイズの決定
	if( pParameter == nullptr || pParameter->width_ < 0 || pParameter->height_ < 0 )
	{
		IDirect3DSurface9*	pSurfaceDepthCurrent = nullptr;		// 現在のレンダーターゲット
		D3DSURFACE_DESC		descSurfaceDepth;					// サーフェイス情報
		pDevice->GetRenderTarget( 0, &pSurfaceDepthCurrent );
		pSurfaceDepthCurrent->GetDesc( &descSurfaceDepth );
		width_ = descSurfaceDepth.Width;
		height_ = descSurfaceDepth.Height;
		pSurfaceDepthCurrent->Release();
		pSurfaceDepthCurrent = nullptr;
	}

	// メンバ変数の設定
	int		result;		// 実行結果
	pDevice_ = pDevice;
	countRenderTarget_ = countRenderTarget;
	ppRenderTarget_ = new RenderTarget*[ countRenderTarget ];
	if( ppRenderTarget_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countRenderTarget; ++counterItem )
	{
		ppRenderTarget_[ counterItem ] = new RenderTarget();
		if( ppRenderTarget_[ counterItem ] == nullptr )
		{
			return 1;
		}
		result = ppRenderTarget_[ counterItem ]->Initialize( pDevice, width_, height_, (pParameter == nullptr ? D3DFMT_A8R8G8B8 : pParameter->pFormat_[ counterItem ]) );
		if( result != 0 )
		{
			return result;
		}
	}
	if( pParameter != nullptr )
	{
		width_ = static_cast< unsigned int >( pParameter->width_ );
		height_ = static_cast< unsigned int >( pParameter->height_ );
		flagClear_ = pParameter->flagClear_;
		clearTarget_ = pParameter->clearTarget_;
		clearZBuffer_ = pParameter->clearZBuffer_;
		clearStencil_ = pParameter->clearStencil_;
	}

	// 深度バッファの生成
	IDirect3DSurface9*	pSurface = nullptr;		// サーフェイス
	D3DSURFACE_DESC		descSurfaceTexture;		// サーフェイス情報
	unsigned int		widthTexture;			// サーフェイスの幅
	unsigned int		heightTexture;			// サーフェイスの高さ
	ppRenderTarget_[ 0 ]->GetTexture()->GetSurfaceLevel( 0, &pSurface );
	pSurface->GetDesc( &descSurfaceTexture );
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
int RenderPass::Finalize( void )
{
	// 深度バッファの開放
	if( pSurfaceDepth_ != nullptr )
	{
		pSurfaceDepth_->Release();
		pSurfaceDepth_ = nullptr;
	}

	// レンダーターゲットの開放
	if( ppRenderTarget_ != nullptr )
	{
		for( int counterItem = 0; counterItem < countRenderTarget_; ++counterItem )
		{
			delete ppRenderTarget_[ counterItem ];
			ppRenderTarget_[ counterItem ] = nullptr;
		}
	}
	delete[] ppRenderTarget_;
	ppRenderTarget_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int countRenderTarget				: レンダーターゲットの数
// Arg    : const RenderPassParameter* pParameter	: 描画対象パラメータ
//==============================================================================
int RenderPass::Reinitialize( IDirect3DDevice9* pDevice, int countRenderTarget, const RenderPassParameter* pParameter )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, countRenderTarget, pParameter );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : RenderPass* pOut					: コピー先アドレス
//==============================================================================
int RenderPass::Copy( RenderPass* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画対象に設定
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void RenderPass::Set( void )
{
	// デバイスにレンダーターゲットを設定
	for( int counterRenderTarget = 0; counterRenderTarget < countRenderTarget_; ++counterRenderTarget )
	{
		ppRenderTarget_[ counterRenderTarget ]->Set( counterRenderTarget );
	}
	pDevice_->SetDepthStencilSurface( pSurfaceDepth_ );
}

//==============================================================================
// Brief  : レンダーターゲット数の取得
// Return : int									: 返却値
// Arg    : void								: なし
//==============================================================================
int RenderPass::GetCountRenderTarget( void ) const
{
	// 値の返却
	return countRenderTarget_;
}

//==============================================================================
// Brief  : テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : int index							: レンダーターゲットの番号
//==============================================================================
IDirect3DTexture9* RenderPass::GetTexture( int index ) const
{
	// エラーチェック
	Assert( index >= 0 && index < countRenderTarget_, _T( "レンダーターゲットの番号が不正です。" ) );
	Assert( ppRenderTarget_[ index ] != nullptr, _T( "レンダーターゲットの番号が不正です。" ) );

	// 値の返却
	return ppRenderTarget_[ index ]->GetTexture();
}

//==============================================================================
// Brief  : 深度バッファの取得
// Return : IDirect3DSurface9*					: 返却する値
// Arg    : void								: なし
//==============================================================================
IDirect3DSurface9* RenderPass::GetSurfaceDepth( void ) const
{
	// 値の返却
	return pSurfaceDepth_;
}

//==============================================================================
// Brief  : 幅の取得
// Return : unsigned int						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned int RenderPass::GetWidth( void ) const
{
	// 値の返却
	return width_;
}

//==============================================================================
// Brief  : 高さの取得
// Return : unsigned int						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned int RenderPass::GetHeight( void ) const
{
	// 値の返却
	return height_;
}

//==============================================================================
// Brief  : クリアフラグの設定
// Return : void								: なし
// Arg    : const DWORD& value					: 設定する値
//==============================================================================
void RenderPass::SetFlagClear( const DWORD& value )
{
	// 値の設定
	flagClear_ = value;
}

//==============================================================================
// Brief  : クリアフラグの取得
// Return : DWORD								: 返却する値
// Arg    : void								: なし
//==============================================================================
DWORD RenderPass::GetFlagClear( void ) const
{
	// 値の返却
	return flagClear_;
}

//==============================================================================
// Brief  : レンダーターゲットのクリア値の設定
// Return : void								: なし
// Arg    : const D3DCOLOR& value				: 設定する値
//==============================================================================
void RenderPass::SetClearTarget( const D3DCOLOR& value )
{
	// 値の設定
	clearTarget_ = value;
}

//==============================================================================
// Brief  : レンダーターゲットのクリア値の取得
// Return : DWORD								: 返却する値
// Arg    : void								: なし
//==============================================================================
D3DCOLOR RenderPass::GetClearTarget( void ) const
{
	// 値の返却
	return clearTarget_;
}

//==============================================================================
// Brief  : Zバッファのクリア値の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void RenderPass::SetClearZBuffer( float value )
{
	// 値の設定
	clearZBuffer_ = value;
}

//==============================================================================
// Brief  : Zバッファのクリア値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float RenderPass::GetClearZBuffer( void ) const
{
	// 値の返却
	return clearZBuffer_;
}

//==============================================================================
// Brief  : ステンシルバッファのクリア値の設定
// Return : void								: なし
// Arg    : const DWORD& value					: 設定する値
//==============================================================================
void RenderPass::SetClearStencil( const DWORD& value )
{
	// 値の設定
	clearStencil_ = value;
}

//==============================================================================
// Brief  : ステンシルバッファのクリア値の取得
// Return : DWORD								: 返却する値
// Arg    : void								: なし
//==============================================================================
DWORD RenderPass::GetClearStencil( void ) const
{
	// 値の返却
	return clearStencil_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void RenderPass::InitializeSelf( void )
{
	// メンバ変数の初期化
	pDevice_ = nullptr;
	countRenderTarget_ = 0;
	ppRenderTarget_ = nullptr;
	pSurfaceDepth_ = nullptr;
	width_ = 0;
	height_ = 0;
	flagClear_ = (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
	clearTarget_ = D3DCOLOR_RGBA( 0, 0, 0, 0 );
	clearZBuffer_ = 1.0f;
	clearStencil_ = 0;
}
