//==============================================================================
//
// File   : Texture.cpp
// Brief  : テクスチャクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Texture.h"

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
Texture::Texture( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Texture::~Texture( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
// Arg    : unsigned int width					: 幅
// Arg    : unsigned int height					: 高さ
//==============================================================================
int Texture::Initialize( IDirect3DTexture9* pTexture, unsigned int width, unsigned int height )
{
	// メンバ変数の設定
	pTexture_ = pTexture;
	width_ = width;
	height_ = height;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Texture::Finalize( void )
{
	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
// Arg    : unsigned int width					: 幅
// Arg    : unsigned int height					: 高さ
//==============================================================================
int Texture::Reinitialize( IDirect3DTexture9* pTexture, unsigned int width, unsigned int height )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pTexture, width, height );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Texture* pOut						: コピー先アドレス
//==============================================================================
int Texture::Copy( Texture* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Texture::InitializeSelf( void )
{
	// メンバ変数の初期化
	pTexture_ = nullptr;
	width_ = 0;
	height_ = 0;
}
