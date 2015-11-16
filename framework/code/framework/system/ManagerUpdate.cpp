//==============================================================================
//
// File   : ManagerUpdate.cpp
// Brief  : 更新実行クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerUpdate.h"
#include "../develop/DebugProc.h"
#include "../object/Object.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// テンプレート宣言
//******************************************************************************
template class ManagerUpdate< class Object >;

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerUpdate< TypeItem >::ManagerUpdate( void ) : ManagerExector()
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
ManagerUpdate< TypeItem >::~ManagerUpdate( void )
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
int ManagerUpdate< TypeItem >::Initialize( int maximumItem )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerExector::Initialize( maximumItem );
	if( result != 0 )
	{
		return result;
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
int ManagerUpdate< TypeItem >::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerExector::Finalize();
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
// Arg    : int maximumItem						: 最大要素数
//==============================================================================
template< class TypeItem >
int ManagerUpdate< TypeItem >::Reinitialize( int maximumItem )
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
// Arg    : ManagerUpdate* pOut					: コピー先アドレス
//==============================================================================
template< class TypeItem >
int ManagerUpdate< TypeItem >::Copy( ManagerUpdate* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerExector::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 実行
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
int ManagerUpdate< TypeItem >::Execute( void )
{
	// オブジェクトの更新
	int		indexItemCurrent;		// 現在の要素番号
	int	a = 0;
	for( indexItemCurrent = indexTop_; indexItemCurrent >= 0; indexItemCurrent = pBufferItem_[ indexItemCurrent ].indexNext_ )
	{
		if( pBufferItem_[ indexItemCurrent ].needsUnregister_ || !pBufferItem_[ indexItemCurrent ].isEnable_ || !pBufferItem_[ indexItemCurrent ].pItem_->IsEnable() )
		{
			continue;
		}
		pBufferItem_[ indexItemCurrent ].pItem_->Update();
		++a;
	}
	PrintDebug( "Update : %d", a );

	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerExector::Execute();
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
void ManagerUpdate< TypeItem >::InitializeSelf( void )
{
	// メンバ変数の初期化
}
