//==============================================================================
//
// File   : ManagerEffect.cpp
// Brief  : エフェクト管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/16 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerEffect.h"
#include "Effect.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// テンプレート宣言
//******************************************************************************
template class ManagerEffect< class Effect >;

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerEffect< TypeItem >::ManagerEffect( void ) : ManagerResource()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerEffect< TypeItem >::~ManagerEffect( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : TCHAR* pDirectory					: 基準ディレクトリ
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
//==============================================================================
template< class TypeItem >
int ManagerEffect< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Initialize( pDirectory, maximumItem );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	pDevice_ = pDevice;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerEffect< TypeItem >::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : TCHAR* pDirectory					: 基準ディレクトリ
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
//==============================================================================
template< class TypeItem >
int ManagerEffect< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem, IDirect3DDevice9* pDevice )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDirectory, maximumItem, pDevice );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerEffect* pOut					: コピー先アドレス
//==============================================================================
template< class TypeItem >
int ManagerEffect< TypeItem >::Copy( ManagerEffect* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
void ManagerEffect< TypeItem >::InitializeSelf( void )
{
	// メンバ変数の初期化
	pDevice_ = nullptr;
}

//==============================================================================
// Brief  : リソースの読み込み
// Return : int									: 実行結果
// Arg    : TCHAR* pPath						: ファイルパス
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
int ManagerEffect< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// エフェクトの読み込み
	int				result;					// 実行結果
	ID3DXEffect*	pEffect = nullptr;		// エフェクト
	DWORD			flagLoad;				// 読み込みフラグ
#ifdef _DEBUG
	flagLoad = 0;
#else
	flagLoad = D3DXSHADER_SKIPVALIDATION;
#endif
	result = D3DXCreateEffectFromFile( pDevice_, pPath, nullptr, nullptr, flagLoad, nullptr, &pEffect, nullptr );
	if( result != 0 )
	{
		TCHAR	pStringError[ 512 ] = {};		// エラー文字列
		sprintf_s( pStringError, 512, _T( "ファイル\"%s\"が見つかりません" ), pPath );
		MessageBox( NULL, pStringError, _T( "エラー" ), MB_OK );
		return 1;
	}

	// エフェクトの生成
	pBufferItem_[ index ].pItem_ = new Effect();
	if( pBufferItem_[ index ].pItem_ == nullptr )
	{
		return 1;
	}
	result = pBufferItem_[ index ].pItem_->Initialize( pEffect );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : リソースの開放
// Return : void								: なし
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
void ManagerEffect< TypeItem >::ReleaseResource( int index )
{
	// エフェクトの開放
	if( pBufferItem_[ index ].pItem_ != nullptr )
	{
		pBufferItem_[ index ].pItem_->pEffect_->Release();
		pBufferItem_[ index ].pItem_->pEffect_ = nullptr;
	}
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}
