//==============================================================================
//
// File   : CameraStateSpline.cpp
// Brief  : デバッグステート
// Author : Taiga Shirakawa
// Date   : 2015/11/07 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "CameraStateSpline.h"
#include "../../framework/camera/CameraObject.h"
#include "../../framework/develop/Debug.h"

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
CameraStateSpline::CameraStateSpline( void ) : CameraState()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
CameraStateSpline::~CameraStateSpline( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int countSection					: セクション数
// Arg    : int countControlPointCamera			: 視点コントロールポイント数
// Arg    : int countControlPointLookAt			: 視点コントロールポイント数
//==============================================================================
int CameraStateSpline::Initialize( int countSection, int countControlPointCamera, int countControlPointLookAt )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = CameraState::Initialize();
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	countSection_ = countSection;
	countControlPointCamera_ = countControlPointCamera;
	countControlPointLookAt_ = countControlPointLookAt;

	// 格納領域の確保
	pFrame_ = new int[ countSection ];
	if( pFrame_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pFrame_[ counterItem ] = 0;
	}

	pTablePointCamera_ = new Utility::ControlPointSpline[ countControlPointCamera ];
	if( pTablePointCamera_ == nullptr )
	{
		return 1;
	}

	pTablePointLookAt_ = new Utility::ControlPointSpline[ countControlPointLookAt ];
	if( pTablePointLookAt_ == nullptr )
	{
		return 1;
	}

	pIndexPointCameraBegin_ = new int[ countSection ];
	if( pIndexPointCameraBegin_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pIndexPointCameraBegin_[ counterItem ] = 0;
	}

	pIndexPointCameraEnd_ = new int[ countSection ];
	if( pIndexPointCameraEnd_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pIndexPointCameraEnd_[ counterItem ] = 0;
	}

	pIndexPointLookAtBegin_ = new int[ countSection ];
	if( pIndexPointLookAtBegin_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pIndexPointLookAtBegin_[ counterItem ] = 0;
	}

	pIndexPointLookAtEnd_ = new int[ countSection ];
	if( pIndexPointLookAtEnd_ == nullptr )
	{
		return 1;
	}
	for( int counterItem = 0; counterItem < countSection; ++counterItem )
	{
		pIndexPointLookAtEnd_[ counterItem ] = 0;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int CameraStateSpline::Finalize( void )
{
	// 確保した領域の開放
	delete[] pFrame_;
	pFrame_ = nullptr;
	delete[] pTablePointCamera_;
	pTablePointCamera_ = nullptr;
	delete[] pTablePointLookAt_;
	pTablePointLookAt_ = nullptr;
	delete[] pIndexPointCameraBegin_;
	pIndexPointCameraBegin_ = nullptr;
	delete[] pIndexPointCameraEnd_;
	pIndexPointCameraEnd_ = nullptr;
	delete[] pIndexPointLookAtBegin_;
	pIndexPointLookAtBegin_ = nullptr;
	delete[] pIndexPointLookAtEnd_;
	pIndexPointLookAtEnd_ = nullptr;

	// 基本クラスの処理
	int		result;		// 実行結果
	result = CameraState::Finalize();
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
// Arg    : int countSection					: セクション数
// Arg    : int countControlPointCamera			: 視点コントロールポイント数
// Arg    : int countControlPointLookAt			: 視点コントロールポイント数
//==============================================================================
int CameraStateSpline::Reinitialize( int countSection, int countControlPointCamera, int countControlPointLookAt )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( countSection, countControlPointCamera, countControlPointLookAt );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : CameraStateSpline* pOut				: コピー先アドレス
//==============================================================================
int CameraStateSpline::Copy( CameraStateSpline* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = CameraState::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : CameraObject* pCamera				: カメラクラス
//==============================================================================
void CameraStateSpline::Update( CameraObject* pCamera )
{
	// 有効なときのみ処理する
	if( !isEnable_ )
	{
		return;
	}

	// 視点座標を設定
	int			indexPointCameraBegin;		// 開始視点番号
	int			indexPointCameraEnd;		// 終了視点番号
	D3DXVECTOR3	positionCamera;				// 視点の座標
	indexPointCameraBegin = pIndexPointCameraBegin_[ indexSection_ ];
	indexPointCameraEnd = pIndexPointCameraEnd_[ indexSection_ ];
	if( indexPointCameraBegin == -1 )
	{
		Assert( indexSection_ != 0, _T( "スプラインカメラステートの設定が不正です。" ) );
		indexPointCameraBegin = pIndexPointCameraEnd_[ indexSection_ - 1 ];
	}
	Utility::Spline( pTablePointCamera_[ indexPointCameraBegin ], pTablePointCamera_[ indexPointCameraEnd ],
		static_cast< float >( countFrame_ ) / pFrame_[ indexSection_ ], &positionCamera );
	pCamera->SetPositionCamera( positionCamera );

	// 注視点座標を設定
	int			indexPointLookAtBegin;		// 開始視点番号
	int			indexPointLookAtEnd;		// 終了視点番号
	D3DXVECTOR3	positionLookAt;				// 注視点の座標
	indexPointLookAtBegin = pIndexPointLookAtBegin_[ indexSection_ ];
	indexPointLookAtEnd = pIndexPointLookAtEnd_[ indexSection_ ];
	if( indexPointLookAtBegin == -1 )
	{
		Assert( indexSection_ != 0, _T( "スプラインカメラステートの設定が不正です。" ) );
		indexPointLookAtBegin = pIndexPointLookAtEnd_[ indexSection_ - 1 ];
	}
	Utility::Spline( pTablePointLookAt_[ indexPointLookAtBegin ], pTablePointLookAt_[ indexPointLookAtEnd ],
		static_cast< float >( countFrame_ ) / pFrame_[ indexSection_ ], &positionLookAt );
	pCamera->SetPositionLookAt( positionLookAt );

	// 経過フレーム数の加算
	++countFrame_;

	// フレーム番号を進める
	if( countFrame_ >= pFrame_[ indexSection_ ] )
	{
		countFrame_ = 0;
		++indexSection_;
		if( indexSection_ >= countSection_ )
		{
			indexSection_ = 0;
		}
	}
}

//==============================================================================
// Brief  : セクションの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : int frame							: 持続時間
// Arg    : int indexCameraBegin				: 開始視点コントロールポイント番号
// Arg    : int indexCameraEnd					: 終了視点コントロールポイント番号
// Arg    : int indexLookAtBegin				: 開始注視点コントロールポイント番号
// Arg    : int indexLookAtEnd					: 終了注視点コントロールポイント番号
//==============================================================================
void CameraStateSpline::SetSection( int index, int frame, int indexCameraBegin, int indexCameraEnd, int indexLookAtBegin, int indexLookAtEnd )
{
	// エラーチェック
	Assert( index < countSection_, _T( "引数の値が不正です。" ) );

	// メンバ変数の設定
	pFrame_[ index ] = frame;
	pIndexPointCameraBegin_[ index ] = indexCameraBegin;
	pIndexPointCameraEnd_[ index ] = indexCameraEnd;
	pIndexPointLookAtBegin_[ index ] = indexLookAtBegin;
	pIndexPointLookAtEnd_[ index ] = indexLookAtEnd;
}

//==============================================================================
// Brief  : 視点コントロールポイントの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& position			: 座標
// Arg    : const D3DXVECTOR3& vector			: ベクトル
//==============================================================================
void CameraStateSpline::SetControlPointCamera( int index, const D3DXVECTOR3& position, const D3DXVECTOR3& vector )
{
	// エラーチェック
	Assert( index < countControlPointCamera_, _T( "引数の値が不正です。" ) );

	// メンバ変数の設定
	pTablePointCamera_[ index ].position_ = position;
	pTablePointCamera_[ index ].vector_ = vector;
}

//==============================================================================
// Brief  : 注視点コントロールポイントの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const D3DXVECTOR3& position			: 座標
// Arg    : const D3DXVECTOR3& vector			: ベクトル
//==============================================================================
void CameraStateSpline::SetControlPointLookAt( int index, const D3DXVECTOR3& position, const D3DXVECTOR3& vector )
{
	// エラーチェック
	Assert( index < countControlPointLookAt_, _T( "引数の値が不正です。" ) );

	// メンバ変数の設定
	pTablePointLookAt_[ index ].position_ = position;
	pTablePointLookAt_[ index ].vector_ = vector;
}

//==============================================================================
// Brief  : 有効フラグの設定
// Return : void								: なし
// Arg    : bool value							: 設定する値
//==============================================================================
void CameraStateSpline::SetIsEnable( bool value )
{
	// 値の設定
	isEnable_ = value;
}

//==============================================================================
// Brief  : 有効フラグの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
bool CameraStateSpline::GetIsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : 有効フラグの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
bool CameraStateSpline::IsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void CameraStateSpline::InitializeSelf( void )
{
	// メンバ変数の初期化
	countSection_ = 0;
	countControlPointCamera_ = 0;
	countControlPointLookAt_ = 0;
	indexSection_ = 0;
	countFrame_ = 0;
	pFrame_ = nullptr;
	pTablePointCamera_ = nullptr;
	pTablePointLookAt_ = nullptr;
	pIndexPointCameraBegin_ = nullptr;
	pIndexPointCameraEnd_ = nullptr;
	pIndexPointLookAtBegin_ = nullptr;
	pIndexPointLookAtEnd_ = nullptr;
	isEnable_ = true;
}
