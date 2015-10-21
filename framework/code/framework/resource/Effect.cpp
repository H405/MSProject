//==============================================================================
//
// File   : Effect.cpp
// Brief  : エフェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/16 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Effect.h"
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
Effect::Effect( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Effect::~Effect( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : ID3DXEffect* pEffect				: エフェクト
//==============================================================================
int Effect::Initialize( ID3DXEffect* pEffect )
{
	// メンバ変数の設定
	pEffect_ = pEffect;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Effect::Finalize( void )
{
	// 格納領域の開放
	delete[] pHandleTechnique_;
	pHandleTechnique_ = nullptr;

	delete[] pHandleParameter_;
	pHandleParameter_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : ID3DXEffect* pEffect				: エフェクト
//==============================================================================
int Effect::Reinitialize( ID3DXEffect* pEffect )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pEffect );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Effect* pOut						: コピー先アドレス
//==============================================================================
int Effect::Copy( Effect* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : ハンドルの読み込み
// Return : int									: 実行結果
// Arg    : int countTechnique					: テクニック数
// Arg    : int countParameter					: パラメータ数
//==============================================================================
int Effect::LoadHandle( int countTechnique, int countParameter )
{
	// すでに読み込まれている場合は終了
	if( pHandleTechnique_ != nullptr )
	{
		return 0;
	}

	// エラーチェック
	Assert( countTechnique > 0, _T( "テクニック数が不正です。" ) );

	// メンバ変数の設定
	countTechnique_ = countTechnique;
	countParameter_ = countParameter;
	pHandleTechnique_ = new D3DXHANDLE[ countTechnique ];
	for( int counterItem = 0; counterItem < countTechnique; ++counterItem )
	{
		pHandleTechnique_[ counterItem ] = NULL;
	}
	if( countParameter > 0 )
	{
		pHandleParameter_ = new D3DXHANDLE[ countParameter ];
		for( int counterItem = 0; counterItem < countParameter; ++counterItem )
		{
			pHandleParameter_[ counterItem ] = NULL;
		}
	}

	// ハンドルの読み込み
	for( int counterTechnique = 0; counterTechnique < countTechnique; ++counterTechnique )
	{
		pHandleTechnique_[ counterTechnique ] = pEffect_->GetTechnique( counterTechnique );
	}
	for( int counterParameter = 0; counterParameter < countParameter; ++counterParameter )
	{
		pHandleParameter_[ counterParameter ] = pEffect_->GetParameter( NULL, counterParameter );
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 開始
// Return : void								: なし
// Arg    : int indexTechnique					: テクニック番号
//==============================================================================
void Effect::Begin( int indexTechnique )
{
	// エフェクト描画の開始
	unsigned int	countPass;		// 必要なパス数
	pEffect_->SetTechnique( pHandleTechnique_[ indexTechnique ] );
	pEffect_->Begin( &countPass, 0 );
	pEffect_->BeginPass( 0 );
}

//==============================================================================
// Brief  : 終了
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Effect::End( void )
{
	// エフェクト描画の終了
	pEffect_->EndPass();
	pEffect_->End();
}

//==============================================================================
// Brief  : テクスチャの設定
// Return : void								: なし
// Arg    : int indexParameter					: パラメータ番号
// Arg    : IDirect3DBaseTexture9* pTexture		: 設定するテクスチャ
//==============================================================================
void Effect::SetTexture( int indexParameter, IDirect3DBaseTexture9* pTexture )
{
	// エラーチェック
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "パラメータ番号が不正です。" ) );

	// テクスチャの設定
	pEffect_->SetTexture( pHandleParameter_[ indexParameter ], pTexture );
}

//==============================================================================
// Brief  : 行列の設定
// Return : void								: なし
// Arg    : int indexParameter					: パラメータ番号
// Arg    : const D3DXMATRIX& matrix			: 設定する行列
//==============================================================================
void Effect::SetMatrix( int indexParameter, const D3DXMATRIX& matrix )
{
	// エラーチェック
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "パラメータ番号が不正です。" ) );

	// 行列の設定
	pEffect_->SetMatrix( pHandleParameter_[ indexParameter ], &matrix );
}

//==============================================================================
// Brief  : 色の設定
// Return : void								: なし
// Arg    : int indexParameter					: パラメータ番号
// Arg    : const D3DXCOLOR& color				: 設定する色
//==============================================================================
void Effect::SetColor( int indexParameter, const D3DXCOLOR& color )
{
	// エラーチェック
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "パラメータ番号が不正です。" ) );

	// 色の設定
	pEffect_->SetFloatArray( pHandleParameter_[ indexParameter ], &color.r, 4 );
}

//==============================================================================
// Brief  : 実数の設定
// Return : void								: なし
// Arg    : int indexParameter					: パラメータ番号
// Arg    : float value							: 設定する値
//==============================================================================
void Effect::SetFloat( int indexParameter, float value )
{
	// エラーチェック
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "パラメータ番号が不正です。" ) );

	// 実数の設定
	pEffect_->SetFloat( pHandleParameter_[ indexParameter ], value );
}

//==============================================================================
// Brief  : 実数配列の設定
// Return : void								: なし
// Arg    : int indexParameter					: パラメータ番号
// Arg    : const float* pValue					: 設定する値
// Arg    : int count							: 設定する要素数
//==============================================================================
void Effect::SetFloatArray( int indexParameter, const float* pValue, int count )
{
	// エラーチェック
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "パラメータ番号が不正です。" ) );

	// 実数配列の設定
	pEffect_->SetFloatArray( pHandleParameter_[ indexParameter ], pValue, count );
}

//==============================================================================
// Brief  : 整数の設定
// Return : void								: なし
// Arg    : int indexParameter					: パラメータ番号
// Arg    : int value							: 設定する値
//==============================================================================
void Effect::SetInteger( int indexParameter, int value )
{
	// エラーチェック
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "パラメータ番号が不正です。" ) );

	// 整数の設定
	pEffect_->SetInt( pHandleParameter_[ indexParameter ], value );
}

//==============================================================================
// Brief  : 整数配列の設定
// Return : void								: なし
// Arg    : int indexParameter					: パラメータ番号
// Arg    : const int* pValue					: 設定する値
// Arg    : int count							: 設定する要素数
//==============================================================================
void Effect::SetIntegerArray( int indexParameter, const int* pValue, int count )
{
	// エラーチェック
	Assert( indexParameter >= 0 && indexParameter < countParameter_, _T( "パラメータ番号が不正です。" ) );

	// 整数配列の設定
	pEffect_->SetIntArray( pHandleParameter_[ indexParameter ], pValue, count );
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Effect::InitializeSelf( void )
{
	// メンバ変数の初期化
	pEffect_ = nullptr;
	countTechnique_ = 0;
	countParameter_ = 0;
	pHandleTechnique_ = nullptr;
	pHandleParameter_ = nullptr;
}
