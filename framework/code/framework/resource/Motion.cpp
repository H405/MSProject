//==============================================================================
//
// File   : Motion.cpp
// Brief  : モーションクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Motion.h"

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
Motion::Motion( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Motion::~Motion( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : unsigned int countFrame				: フレーム数
// Arg    : unsigned int countBone				: ボーン数
//==============================================================================
int Motion::Initialize( unsigned int countFrame, unsigned int countBone )
{
	// メンバ変数の設定
	countFrame_ = countFrame;
	countBone_ = countBone;
	pMatrixBone_ = new D3DXMATRIX[ countFrame * countBone ];
	for( unsigned int counterItem = 0; counterItem < countFrame * countBone; ++counterItem )
	{
		D3DXMatrixIdentity( &pMatrixBone_[ counterItem ] );
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Motion::Finalize( void )
{
	// 格納領域の開放
	delete[] pMatrixBone_;
	pMatrixBone_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : unsigned int countFrame				: フレーム数
// Arg    : unsigned int countBone				: ボーン数
//==============================================================================
int Motion::Reinitialize( unsigned int countFrame, unsigned int countBone )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( countFrame, countBone );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Motion* pOut						: コピー先アドレス
//==============================================================================
int Motion::Copy( Motion* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : フレーム数の取得
// Return : unsigned int						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned int Motion::GetCountFrame( void ) const
{
	// 値の返却
	return countFrame_;
}

//==============================================================================
// Brief  : ボーン数の取得
// Return : unsigned int						: 返却する値
// Arg    : void								: なし
//==============================================================================
unsigned int Motion::GetCountBone( void ) const
{
	// 値の返却
	return countBone_;
}

//==============================================================================
// Brief  : ボーン変換行列の設定
// Return : void								: なし
// Arg    : int indexFrame						: 設定するフレーム番号
// Arg    : int indexBone						: 設定するボーン番号
// Arg    : const D3DXMATRIX& value				: 設定する値
//==============================================================================
void Motion::SetMatrixBone( int indexFrame, int indexBone, const D3DXMATRIX& value )
{
	// 値の設定
	pMatrixBone_[ countBone_ * indexFrame + indexBone ] = value;
}

//==============================================================================
// Brief  : ボーン変換行列の取得
// Return : void								: なし
// Arg    : int indexFrame						: 設定するフレーム番号
// Arg    : int indexBone						: 設定するボーン番号
// Arg    : D3DXMATRIX* pOut					: 値の格納アドレス
//==============================================================================
void Motion::GetMatrixBone( int indexFrame, int indexBone, D3DXMATRIX* pOut ) const
{
	// 値の返却
	*pOut = pMatrixBone_[ countBone_ * indexFrame + indexBone ];
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Motion::InitializeSelf( void )
{
	// メンバ変数の初期化
	countFrame_ = 0;
	countBone_ = 0;
	pMatrixBone_ = nullptr;
}
