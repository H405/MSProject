//==============================================================================
//
// File   : ManagerResource.cpp
// Brief  : リソース管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include <stdlib.h>
#include <string.h>
#include "ManagerResource.h"
#include "../develop/Debug.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// テンプレート宣言
//******************************************************************************
template class ManagerResource< class Effect >;
template class ManagerResource< class Model >;
template class ManagerResource< class Motion >;
template class ManagerResource< class Sound >;
template class ManagerResource< class Texture >;

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerResource< TypeItem >::ManagerResource( void )
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
ManagerResource< TypeItem >::~ManagerResource( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : TCHAR* pDirectory					: 基準ディレクトリ
// Arg    : int maximumItem						: 最大要素数
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem )
{
	// メンバ変数の設定
	maximumItem_ = maximumItem;

	// 文字列の格納領域を確保
	pDirectory_ = new TCHAR[ _MAX_PATH ];
	if( pDirectory_ == nullptr )
	{
		return 1;
	}
	memset( pDirectory_, 0x00, sizeof( TCHAR ) * _MAX_PATH );
	_tcscpy_s( pDirectory_, _MAX_PATH, pDirectory );

	// リソース格納領域の確保
	pBufferItem_ = new Item[ maximumItem ];
	if( pBufferItem_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < maximumItem; ++counterItem )
	{
		pBufferItem_[ counterItem ].Initialize();
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Finalize( void )
{
	// リソースの開放
	for( int counterItem = 0; counterItem < maximumItem_; ++counterItem )
	{
		ReleaseResource( counterItem );
	}

	// 格納領域の開放
	delete[] pDirectory_;
	pDirectory_ = nullptr;

	delete[] pBufferItem_;
	pBufferItem_ = nullptr;

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
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDirectory, maximumItem );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerResource* pOut				: コピー先アドレス
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Copy( ManagerResource* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : リソースの読み込み
// Return : int									: リソースID
// Arg    : TCHAR* pNameFile					: ファイル名
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Load( TCHAR* pNameFile )
{
	// エラーチェック
	Assert( pNameFile != nullptr, _T( "ファイルパスが不正です。" ) );

	// ファイルパスの作成
	TCHAR	pPath[ _MAX_PATH ] = {};		// ファイルパス
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// 既に作られていないか検索
	int		index;		// 要素番号
	index = GetId( pPath );
	if( index != -1 )
	{
		return index;
	}

	// 格納場所の決定
	for( index = 0; index < maximumItem_; ++index )
	{
		if( !pBufferItem_[ index ].isEnable_ )
		{
			break;
		}
	}
	if( index >= maximumItem_ )
	{
		PrintDebugWnd( _T( "リソースの格納領域に空きがありません。" ) );
		return -1;
	}

	// リソースの読み込み
	int		result;		// 実行結果
	result = LoadResource( pPath, index );
	if( result != 0 )
	{
		return -1;
	}

	// 要素に値を設定
	pBufferItem_[ index ].id_ = index;
	_tcscpy_s( pBufferItem_[ index ].pPath_, _MAX_PATH, pPath );
	pBufferItem_[ index ].isEnable_ = true;

	// リソースIDを返す
	return index;
}

//==============================================================================
// Brief  : リソースの取得
// Return : TypeItem*							: リソース
// Arg    : TCHAR* pNameFile					: ファイル名
//==============================================================================
template< class TypeItem >
TypeItem* ManagerResource< TypeItem >::Get( TCHAR* pNameFile )
{
	// エラーチェック
	Assert( pNameFile != nullptr, _T( "ファイルパスが不正です。" ) );

	// ファイルパスの作成
	TCHAR	pPath[ _MAX_PATH ] = {};		// ファイルパス
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// 既に作られていないか検索
	int		index;		// 要素番号
	index = GetId( pPath );
	if( index != -1 )
	{
		return pBufferItem_[ index ].pItem_;
	}

	// 作られていないとき読み込み
	index = Load( pNameFile );
	if( index == -1 )
	{
		return nullptr;
	}

	// リソースの返却
	return pBufferItem_[ index ].pItem_;
}

//==============================================================================
// Brief  : リソースの取得
// Return : TypeItem*							: リソース
// Arg    : int id								: リソースID
//==============================================================================
template< class TypeItem >
TypeItem* ManagerResource< TypeItem >::Get( int id )
{
	// エラーチェック
	Assert( id >= 0 && id < maximumItem_, _T( "指定したIDが不正です。" ) );

	// リソースを返す
	return pBufferItem_[ id ].pItem_;
}

//==============================================================================
// Brief  : リソースの開放
// Return : void								: なし
// Arg    : TCHAR* pNameFile					: ファイル名
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::Release( TCHAR* pNameFile )
{
	// ファイルパスの作成
	TCHAR	pPath[ _MAX_PATH ] = {};		// ファイルパス
	_tcscpy_s( pPath, _MAX_PATH, pDirectory_ );
	_tcscat_s( pPath, _MAX_PATH, pNameFile );

	// 存在しているか検索
	int		index;		// 要素番号
	index = GetId( pPath );
	if( index == -1 )
	{
		return;
	}

	// リソースの開放
	ReleaseResource( index );
	pBufferItem_[ index ].pItem_ = nullptr;
	pBufferItem_[ index ].Reinitialize();
}

//==============================================================================
// Brief  : リソースの開放
// Return : void								: なし
// Arg    : int id								: リソースID
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::Release( int id )
{
	// リソースがあるか確認
	if( !pBufferItem_[ id ].isEnable_ )
	{
		return;
	}

	// リソースの開放
	ReleaseResource( id );
	pBufferItem_[ id ].pItem_ = nullptr;
	pBufferItem_[ id ].Reinitialize();
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::InitializeSelf( void )
{
	// メンバ変数の初期化
	maximumItem_ = 0;
	pDirectory_ = nullptr;
	pBufferItem_ = nullptr;
}

//==============================================================================
// Brief  : すでに作成されているか検索
// Return : int									: リソースのID
// Arg    : TCHAR* pPath						: ファイルパス
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::GetId( TCHAR* pPath )
{
	// 作成されているか検索
	for( int counterItem = 0; counterItem < maximumItem_; ++counterItem )
	{
		if( !_tcscmp( pPath, pBufferItem_[ counterItem ].pPath_ ) )
		{
			return counterItem;
		}
	}

	// 作成されていなかった
	return -1;
}

//==============================================================================
// Brief  : リソースの読み込み
// Return : int									: 実行結果
// Arg    : TCHAR* pPath						: ファイルパス
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// 値を返す
	return 0;
}

//==============================================================================
// Brief  : リソースの開放
// Return : void								: なし
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::ReleaseResource( int index )
{
}

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerResource< TypeItem >::Item::Item( void )
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
ManagerResource< TypeItem >::Item::~Item( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Item::Initialize( void )
{
	// 文字列の格納領域を確保
	pPath_ = new TCHAR[ _MAX_PATH ];
	if( pPath_ == nullptr )
	{
		return 1;
	}
	memset( pPath_, 0x00, sizeof( TCHAR ) * _MAX_PATH );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Item::Finalize( void )
{
	// 格納領域の開放
	delete[] pPath_;
	pPath_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerResource< TypeItem >::Item::Reinitialize( void )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize();
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
void ManagerResource< TypeItem >::Item::InitializeSelf( void )
{
	// メンバ変数の初期化
	id_ = -1;
	pItem_ = nullptr;
	pPath_ = nullptr;
	isEnable_ = false;
}
