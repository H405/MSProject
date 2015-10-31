//==============================================================================
//
// File   : ManagerMotion.cpp
// Brief  : モーション管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerMotion.h"
#include "Motion.h"
#include "../system/File.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// テンプレート宣言
//******************************************************************************
template class ManagerMotion< class Motion >;

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
template< class TypeItem >
ManagerMotion< TypeItem >::ManagerMotion( void ) : ManagerResource()
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
ManagerMotion< TypeItem >::~ManagerMotion( void )
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
int ManagerMotion< TypeItem >::Initialize( TCHAR* pDirectory, int maximumItem )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = ManagerResource::Initialize( pDirectory, maximumItem );
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
int ManagerMotion< TypeItem >::Finalize( void )
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
//==============================================================================
template< class TypeItem >
int ManagerMotion< TypeItem >::Reinitialize( TCHAR* pDirectory, int maximumItem )
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
// Arg    : ManagerMotion* pOut					: コピー先アドレス
//==============================================================================
template< class TypeItem >
int ManagerMotion< TypeItem >::Copy( ManagerMotion* pOut ) const
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
void ManagerMotion< TypeItem >::InitializeSelf( void )
{
	// メンバ変数の初期化
}

//==============================================================================
// Brief  : リソースの読み込み
// Return : int									: 実行結果
// Arg    : TCHAR* pPath						: ファイルパス
// Arg    : int index							: 格納要素番号
//==============================================================================
template< class TypeItem >
int ManagerMotion< TypeItem >::LoadResource( TCHAR* pPath, int index )
{
	// ファイルの読み込み
	File	file;		// ファイル
	int		result;		// 実行結果
	result = file.Initialize( pPath );
	if( result != 0 )
	{
		return result;
	}

	// ファイルの種類を確認
	if( !file.IsType( _T( "MOT3" ) ) )
	{
		TCHAR	pStringError[ 256 ];		// エラーメッセージ
		sprintf_s( pStringError, 256, _T( "ファイル\"%s\"が見つかりません。" ), pPath );
		MessageBox( nullptr, &pStringError[ 0 ], _T( "エラー" ), MB_OK );
		return 1;
	}

	// モーション情報の読み込み
	unsigned long	countBone;			// ボーン数
	unsigned long	countMotion;		// モーション数
	unsigned long	countKeyFrame;		// キーフレーム数
	file.Read( &countBone );
	file.Read( &countMotion );
	file.Read( &countKeyFrame );

	// モーションの生成
	Motion*	pMotion = nullptr;				// モデル
	pMotion= new Motion();
	if( pMotion == nullptr )
	{
		return 1;
	}
	result = pMotion->Initialize( countKeyFrame, countBone );
	if( result != 0 )
	{
		return result;
	}
	pBufferItem_[ index ].pItem_ = pMotion;

	// キーフレーム情報の読み込み
	D3DXMATRIX	matrixSet;			// 設定する変換行列
	float		matrix[ 12 ];		// 変換行列読み込み用
	float		countFrame;			// フレーム数読み込み用
	for( unsigned long counterKeyFrame = 0; counterKeyFrame < countKeyFrame; ++counterKeyFrame )
	{
		file.Read( &countFrame );
		for( unsigned long counterBone = 0; counterBone < countBone; ++counterBone )
		{
			file.Read( &matrix[ 0 ], 12 );
			matrixSet._11 = matrix[ 0 ];
			matrixSet._12 = matrix[ 1 ];
			matrixSet._13 = matrix[ 2 ];
			matrixSet._14 = 0.0f;
			matrixSet._21 = matrix[ 3 ];
			matrixSet._22 = matrix[ 4 ];
			matrixSet._23 = matrix[ 5 ];
			matrixSet._24 = 0.0f;
			matrixSet._31 = matrix[ 6 ];
			matrixSet._32 = matrix[ 7 ];
			matrixSet._33 = matrix[ 8 ];
			matrixSet._34 = 0.0f;
			matrixSet._41 = matrix[ 9 ];
			matrixSet._42 = matrix[ 10 ];
			matrixSet._43 = matrix[ 11 ];
			matrixSet._44 = 1.0f;
			pMotion->SetMatrixBone( counterKeyFrame, counterBone, matrixSet );
		}
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
void ManagerMotion< TypeItem >::ReleaseResource( int index )
{
	// モーションの開放
	delete pBufferItem_[ index ].pItem_;
	pBufferItem_[ index ].pItem_ = nullptr;
}
