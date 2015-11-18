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
// Arg    : int countMultiple					: 順番描画数
//==============================================================================
int RenderTarget::Initialize( IDirect3DDevice9* pDevice, int width, int height, D3DFORMAT format, int countMultiple )
{
	// メンバ変数の設定
	pDevice_ = pDevice;
	countMultiple_ = countMultiple;

	// 格納領域の確保
	if( countMultiple <= 0 )
	{
		return 0;
	}
	ppTexture_ = new IDirect3DTexture9*[ countMultiple ];
	if( ppTexture_ == nullptr )
	{
		return 1;
	}
	ppSurfaceTexture_ = new IDirect3DSurface9*[ countMultiple ];
	if( ppSurfaceTexture_ == nullptr )
	{
		return 1;
	}

	// テクスチャサーフェイスの生成
	int		result;		// 実行結果
	for( int counterMultiple = 0; counterMultiple < countMultiple; ++counterMultiple )
	{
		result = D3DXCreateTexture( pDevice_, width, height, 1, D3DUSAGE_RENDERTARGET, format, D3DPOOL_DEFAULT, &ppTexture_[ counterMultiple ] );
		if( result != 0 )
		{
			return 0;
		}
		ppTexture_[ counterMultiple ]->GetSurfaceLevel( 0, &ppSurfaceTexture_[ counterMultiple ] );
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
	// リソースの開放
	for( int counterMultiple = 0; counterMultiple < countMultiple_; ++counterMultiple )
	{
		// テクスチャサーフェイスの開放
		if( ppSurfaceTexture_[ counterMultiple ] != nullptr )
		{
			ppSurfaceTexture_[ counterMultiple ]->Release();
			ppSurfaceTexture_[ counterMultiple ] = nullptr;
		}

		// テクスチャの開放
		if( ppTexture_[ counterMultiple ] != nullptr )
		{
			ppTexture_[ counterMultiple ]->Release();
			ppTexture_[ counterMultiple ] = nullptr;
		}
	}
	delete[] ppSurfaceTexture_;
	delete[] ppTexture_;

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
// Arg    : int countMultiple					: 順番描画数
//==============================================================================
int RenderTarget::Reinitialize( IDirect3DDevice9* pDevice, int width, int height, D3DFORMAT format, int countMultiple )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, width, height, format, countMultiple );
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
	pDevice_->SetRenderTarget( index, ppSurfaceTexture_[ indexMultiple_ ] );

	// 番号を進める
	++indexMultiple_;
	if( indexMultiple_ >= countMultiple_ )
	{
		indexMultiple_ = 0;
	}
}

//==============================================================================
// Brief  : テクスチャの取得
// Return : IDirect3DTexture9*					: 返却する値
// Arg    : int index							: 順番番号
//==============================================================================
IDirect3DTexture9* RenderTarget::GetTexture( int index ) const
{
	// 値の返却
	return ppTexture_[ index ];
}

//==============================================================================
// Brief  : テクスチャサーフェイスの取得
// Return : IDirect3DSurface9*					: 返却する値
// Arg    : int index							: 順番番号
//==============================================================================
IDirect3DSurface9* RenderTarget::GetSurfaceTexture( int index ) const
{
	// 値の返却
	return ppSurfaceTexture_[ index ];
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
	countMultiple_ = 0;
	indexMultiple_ = 0;
	ppTexture_ = nullptr;
	ppSurfaceTexture_ = nullptr;
	isEnable_ = true;
}
