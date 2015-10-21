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
//==============================================================================
int RenderPass::Initialize( IDirect3DDevice9* pDevice, int countRenderTarget )
{
	// メンバ変数の設定
	int		result;		// 実行結果
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
		result = ppRenderTarget_[ counterItem ]->Initialize( pDevice );
		if( result != 0 )
		{
			return result;
		}
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
//==============================================================================
int RenderPass::Reinitialize( IDirect3DDevice9* pDevice, int countRenderTarget )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, countRenderTarget );
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
// Brief  : レンダーターゲットの取得
// Return : RenderTarget*						: 取得する値
// Arg    : int index							: 設定する番号
//==============================================================================
RenderTarget* RenderPass::GetRenderTarget( int index ) const
{
	// 値の返却
	return ppRenderTarget_[ index ];
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void RenderPass::InitializeSelf( void )
{
	// メンバ変数の初期化
	countRenderTarget_ = 0;
	ppRenderTarget_ = nullptr;
}
