//==============================================================================
//
// File   : ManagerExector.cpp
// Brief  : 実行クラスの基本クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/10 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerExector.h"
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
template class ManagerExector< class Graphic >;
template class ManagerExector< class Object >;

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerExector< TypeItem >::ManagerExector( void )
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
ManagerExector< TypeItem >::~ManagerExector( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int maximumItem						: 最大要素数
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Initialize( int maximumItem )
{
	// メンバ変数の設定
	countItem_ = maximumItem;
	pBufferItem_ = new Item[ maximumItem ];
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
int ManagerExector< TypeItem >::Finalize( void )
{
	// 格納領域の開放
	delete[] pBufferItem_;
	pBufferItem_ = nullptr;

	// クラス内部の初期化
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int maximumItem						: 最大要素数
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Reinitialize( int maximumItem )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( maximumItem );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerExector* pOut				: コピー先アドレス
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Copy( ManagerExector* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 実行
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Execute( void )
{
	// 登録解除フラグの立っている要素の登録を解除
	UnregisterNeed();

	// 値の返却
	return 0;
}

//==============================================================================
// Brief  : 登録
// Return : int									: 登録ID
// Arg    : TypeItem* pItem						: 登録する要素
// Arg    : int priority						: 優先度
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Register( TypeItem* pItem, int priority )
{
	// 空いている場所の検索
	int		id;		// 設定するID
	for( id = 0; id < countItem_; ++id )
	{
		if( !pBufferItem_[ id ].isEnable_ && !pBufferItem_[ id ].needsUnregister_ )
		{
			break;
		}
	}
	if( id >= countItem_ )
	{
		PrintDebugWnd( _T( "描画管理クラスの要素に空きがありません。" ) );
		return -1;
	}

	// 要素の並びを決定
	int		indexNext = -1;			// 次の要素番号
	int		indexPrevious = -1;		// 前の要素番号
	int		indexCurrent;			// 現在の番号
	for( indexCurrent = indexTop_; indexCurrent >= 0; indexCurrent = pBufferItem_[ indexCurrent ].indexNext_ )
	{
		if( pBufferItem_[ indexCurrent ].priority_ < priority )
		{
			indexPrevious = pBufferItem_[ indexCurrent ].indexPrevious_;
			indexNext = indexCurrent;
			break;
		}
		if( pBufferItem_[ indexCurrent ].indexNext_ < 0 )
		{
			indexPrevious = indexCurrent;
			indexNext = -1;
			break;
		}
	}

	// 端の設定
	if( indexPrevious < 0 )
	{
		indexTop_ = id;
	}
	if( indexNext < 0 )
	{
		indexTail_ = id;
	}

	// 要素の設定
	pBufferItem_[ id ].id_ = id;
	pBufferItem_[ id ].priority_ = priority;
	pBufferItem_[ id ].indexNext_ = indexNext;
	pBufferItem_[ id ].indexPrevious_ = indexPrevious;
	pBufferItem_[ id ].pItem_ = pItem;
	pBufferItem_[ id ].needsUnregister_ = false;
	pBufferItem_[ id ].isEnable_ = true;

	// 前後の要素の並びを設定
	if( indexNext != -1 )
	{
		pBufferItem_[ indexNext ].indexPrevious_ = id;
	}
	if( indexPrevious != -1 )
	{
		pBufferItem_[ indexPrevious ].indexNext_ = id;
	}

	// IDの返却
	return id;
}

//==============================================================================
// Brief  : 登録解除
// Return : void								: なし
// Arg    : int id								: 対象ID
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::Unregister( int id )
{
	// エラーチェック
	Assert( id >= -1 && id < countItem_, _T( "引数の値が不正です。" ) );
	if( id == -1 )
	{
		return;
	}

	// 登録解除フラグを立てる
	pBufferItem_[ id ].isEnable_ = false;
	pBufferItem_[ id ].needsUnregister_ = true;
}

//==============================================================================
// Brief  : 有効フラグの設定
// Return : void								: なし
// Arg    : bool value							: 設定する値
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::SetIsEnable( bool value )
{
	// 値の設定
	isEnable_ = value;
}

//==============================================================================
// Brief  : 有効フラグの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
bool ManagerExector< TypeItem >::GetIsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : 有効フラグの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
bool ManagerExector< TypeItem >::IsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::InitializeSelf( void )
{
	// メンバ変数の初期化
	pBufferItem_ = nullptr;
	indexTop_ = -1;
	indexTail_ = -1;
	isEnable_ = true;
}

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerExector< TypeItem >::Item::Item( void )
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
ManagerExector< TypeItem >::Item::~Item( void )
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
int ManagerExector< TypeItem >::Item::Initialize( void )
{
	// クラス内部の初期化
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Item::Finalize( void )
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerExector< TypeItem >::Item::Reinitialize( void )
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
void ManagerExector< TypeItem >::Item::InitializeSelf( void )
{
	// メンバ変数の初期化
	id_ = -1;
	priority_ = 0;
	indexNext_ = -1;
	indexPrevious_ = -1;
	pItem_ = nullptr;
	needsUnregister_ = false;
	isEnable_ = false;
}

//==============================================================================
// Brief  : 要素の登録解除
// Return : void								: なし
// Arg    : int id								: 対象ID
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::UnregisterItem( int id )
{
	// エラーチェック
	Assert( id >= 0 && id < countItem_, _T( "引数の値が不正です。" ) );

	// 端の設定
	if( id == indexTop_ )
	{
		indexTop_ = pBufferItem_[ id ].indexNext_;
	}
	if( id == indexTail_ )
	{
		indexTail_ = pBufferItem_[ id ].indexPrevious_;
	}

	// 前後の並びを設定
	if( pBufferItem_[ id ].indexNext_ != -1 )
	{
		pBufferItem_[ pBufferItem_[ id ].indexNext_ ].indexPrevious_ = pBufferItem_[ id ].indexPrevious_;
	}
	if( pBufferItem_[ id ].indexPrevious_ != -1 )
	{
		pBufferItem_[ pBufferItem_[ id ].indexPrevious_ ].indexNext_ = pBufferItem_[ id ].indexNext_;
	}

	// 要素の再初期化
	pBufferItem_[ id ].Reinitialize();
}

//==============================================================================
// Brief  : 登録解除フラグの立っている要素の登録解除
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
void ManagerExector< TypeItem >::UnregisterNeed( void )
{
	// 登録の解除
	int		indexItemCurrent;		// 現在の要素番号
	int		indexItemNext;			// 次の要素番号
	indexItemNext = -1;
	for( indexItemCurrent = indexTop_; indexItemCurrent >= 0; indexItemCurrent = indexItemNext )
	{
		indexItemNext = pBufferItem_[ indexItemCurrent ].indexNext_;
		if( pBufferItem_[ indexItemCurrent ].needsUnregister_ )
		{
			UnregisterItem( indexItemCurrent );
		}
	}
}
