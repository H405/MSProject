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
#include <stdio.h>
#include "CameraStateSpline.h"
#include "../../framework/camera/CameraObject.h"
#include "../../framework/develop/Debug.h"
#include "../../framework/develop/DebugProc.h"

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
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : const TCHAR* pNameFile				: ファイル名
//==============================================================================
int CameraStateSpline::Initialize( const TCHAR* pNameFile )
{
	// ファイルを開く
	FILE*	pFile = nullptr;		// ファイル
	_tfopen_s( &pFile, pNameFile, _T( "rt" ) );
	if( pFile == nullptr )
	{
		TCHAR	pStringError[ 256 ];		// エラー文字列
		_stprintf_s( pStringError, 256, _T( "ファイル\"%s\"が見つかりません。" ), pNameFile );
		PrintMsgBox( pStringError );
		return 1;
	}

	// サイズを求める
	unsigned int	sizeFile;		// ファイルのサイズ
	fseek( pFile, 0, SEEK_END );
	sizeFile = ftell( pFile );
	fseek( pFile, 0, SEEK_SET );

	// バッファの確保
	char*	pBufferFile = nullptr;		// 格納用
	pBufferFile = new char[ sizeFile ];
	if( pBufferFile == nullptr )
	{
		return -1;
	}
	memset( pBufferFile, 0x00, sizeof( char ) * sizeFile );

	// ファイルの内容をコピー
	fread( pBufferFile, sizeof( char ), sizeFile, pFile );

	// ファイルを閉じる
	fclose( pFile );
	pFile = nullptr;

	// 改行の補正
	int		countBreak;		// 改行数
	countBreak = 0;
	for( unsigned int counterCharacter = 0; counterCharacter < sizeFile; ++counterCharacter )
	{
		if( pBufferFile[ counterCharacter ] == '\n' )
		{
			++countBreak;
		}
	}
	sizeFile -= countBreak;

	// データの開始位置を記録
	unsigned int	indexBeginLookAt;			// 注視点情報開始位置
	unsigned int	indexBeginSection;			// セクション情報開始位置
	int				lengthCompareLookAt;		// 比較文字数
	int				lengthCompareSection;		// 比較文字数
	lengthCompareLookAt = _tcslen( _T( "[注視点]" ) );
	lengthCompareSection = _tcslen( _T( "[セクション]" ) );
	for( unsigned int counterCharacter = 0; counterCharacter < sizeFile - lengthCompareSection; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "[注視点]" ), lengthCompareLookAt ) )
		{
			indexBeginLookAt = counterCharacter;
		}
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "[セクション]" ), lengthCompareSection ) )
		{
			indexBeginSection = counterCharacter;
		}
	}

	// 各要素の個数を求める
	int		countPointCamera;		// 視点のコントロールポイント数
	int		countPointLookAt;		// 注視点のコントロールポイント数
	int		countSection;			// セクション数
	int		lengthCompare;			// 比較文字数
	countPointCamera = 0;
	lengthCompare = _tcslen( _T( "CP" ) );
	for( unsigned int counterCharacter = 0; counterCharacter < indexBeginLookAt - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "CP" ), lengthCompare ) )
		{
			++countPointCamera;
		}
	}
	countPointLookAt = 0;
	for( unsigned int counterCharacter = indexBeginLookAt; counterCharacter < indexBeginSection - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "CP" ), lengthCompare ) )
		{
			++countPointLookAt;
		}
	}
	countSection = 0;
	for( unsigned int counterCharacter = indexBeginSection; counterCharacter < sizeFile - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "SE" ), lengthCompare ) )
		{
			++countSection;
		}
	}

	// 初期化処理
	int		result;		// 実行結果
	result = Initialize( countSection, countPointCamera, countPointLookAt );
	if( result != 0 )
	{
		return result;
	}

	// コントロールポイントのID格納領域を確保
	int*	pIdPointCamera = nullptr;		// 視点コントロールポイントID
	int*	pIdPointLookAt = nullptr;		// 注視点コントロールポイントID
	pIdPointCamera = new int[ countPointCamera ];
	if( pIdPointCamera == nullptr )
	{
		return 1;
	}
	pIdPointLookAt = new int[ countPointLookAt ];
	if( pIdPointLookAt == nullptr )
	{
		return 1;
	}

	// 視点情報の設定
	int			indexIdPointCamera;			// 視点コントロールポイントID番号
	TCHAR		pStringNumber[ 64 ];		// 数字文字列
	D3DXVECTOR3	positionPoint;				// コントロールポイントの座標
	D3DXVECTOR3	vectorPoint;				// コントロールポイントのベクトル
	indexIdPointCamera = 0;
	for( unsigned int counterCharacter = 0; counterCharacter < indexBeginLookAt - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "CP" ), lengthCompare ) )
		{
			// IDの取得
			counterCharacter += 2;
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			pIdPointCamera[ indexIdPointCamera ] = _tstoi( pStringNumber );

			// コントロールポイント情報の取得
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			positionPoint.x = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			positionPoint.y = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			positionPoint.z = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			vectorPoint.x = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			vectorPoint.y = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginLookAt - lengthCompare, 64, pStringNumber );
			vectorPoint.z = static_cast< float >( _tstof( pStringNumber ) );

			// コントロールポイントの設定
			SetControlPointCamera( indexIdPointCamera, positionPoint, vectorPoint );

			// ID番号を進める
			++indexIdPointCamera;
		}
	}

	// 注視点情報の設定
	int		indexIdPointLookAt;		// 視点コントロールポイントID番号
	indexIdPointLookAt = 0;
	for( unsigned int counterCharacter = indexBeginLookAt; counterCharacter < indexBeginSection - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "CP" ), lengthCompare ) )
		{
			// IDの取得
			counterCharacter += 2;
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			pIdPointLookAt[ indexIdPointLookAt ] = _tstoi( pStringNumber );

			// コントロールポイント情報の取得
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			positionPoint.x = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			positionPoint.y = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			positionPoint.z = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			vectorPoint.x = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			vectorPoint.y = static_cast< float >( _tstof( pStringNumber ) );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, indexBeginSection - lengthCompare, 64, pStringNumber );
			vectorPoint.z = static_cast< float >( _tstof( pStringNumber ) );

			// コントロールポイントの設定
			SetControlPointLookAt( indexIdPointLookAt, positionPoint, vectorPoint );

			// ID番号を進める
			++indexIdPointLookAt;
		}
	}

	// セクション情報の設定
	int		indexSection;			// セクション番号
	int		countFrame;				// フレーム数
	int		idCameraBegin;			// 視点開始コントロールポイントID
	int		idCameraEnd;			// 視点終了コントロールポイントID
	int		idLookAtBegin;			// 注視点開始コントロールポイントID
	int		idLookAtEnd;			// 注視点終了コントロールポイントID
	int		indexCameraBegin;		// 視点開始コントロールポイント番号
	int		indexCameraEnd;			// 視点終了コントロールポイント番号
	int		indexLookAtBegin;		// 注視点開始コントロールポイント番号
	int		indexLookAtEnd;			// 注視点終了コントロールポイント番号
	indexSection = 0;
	for( unsigned int counterCharacter = indexBeginSection; counterCharacter < sizeFile - lengthCompare; ++counterCharacter )
	{
		if( !_tcsncmp( &pBufferFile[ counterCharacter ], _T( "SE" ), lengthCompare ) )
		{
			// フレーム数の取得
			counterCharacter += 2;
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			countFrame = _tstoi( pStringNumber );

			// コントロールポイントIDの取得
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			idCameraBegin = _tstoi( pStringNumber );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			idCameraEnd = _tstoi( pStringNumber );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			idLookAtBegin = _tstoi( pStringNumber );
			counterCharacter = GetStringNumber( pBufferFile, counterCharacter, sizeFile - lengthCompare, 64, pStringNumber );
			idLookAtEnd = _tstoi( pStringNumber );

			// IDを番号に変換
			indexCameraBegin = GetIndexFromId( pIdPointCamera, countPointCamera, idCameraBegin );
			indexCameraEnd = GetIndexFromId( pIdPointCamera, countPointCamera, idCameraEnd );
			indexLookAtBegin = GetIndexFromId( pIdPointLookAt, countPointLookAt, idLookAtBegin );
			indexLookAtEnd = GetIndexFromId( pIdPointLookAt, countPointLookAt, idLookAtEnd );

			// セクションの設定
			SetSection( indexSection, countFrame, indexCameraBegin, indexCameraEnd, indexLookAtBegin, indexLookAtEnd );

			// セクション番号を進める
			++indexSection;
		}
	}

	// コントロールポイントのID格納領域を開放
	delete[] pIdPointCamera;
	pIdPointCamera = nullptr;
	delete[] pIdPointLookAt;
	pIdPointLookAt = nullptr;

	// バッファの開放
	delete[] pBufferFile;
	pBufferFile = nullptr;

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
// Brief  : 視点コントロールポイントの取得
// Return : void								: なし
// Arg    : int index							: 取得する番号
// Arg    : D3DXVECTOR3* pOutPosition			: 座標
// Arg    : D3DXVECTOR3* pOutVector				: ベクトル
//==============================================================================
void CameraStateSpline::GetControlPointCamera( int index, D3DXVECTOR3* pOutPosition, D3DXVECTOR3* pOutVector ) const
{
	// 値を返す
	*pOutPosition = pTablePointCamera_[ index ].position_;
	*pOutVector = pTablePointCamera_[ index ].vector_;
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
// Brief  : 注視点コントロールポイントの取得
// Return : void								: なし
// Arg    : int index							: 取得する番号
// Arg    : D3DXVECTOR3* pOutPosition			: 座標
// Arg    : D3DXVECTOR3* pOutVector				: ベクトル
//==============================================================================
void CameraStateSpline::GetControlPointLookAt( int index, D3DXVECTOR3* pOutPosition, D3DXVECTOR3* pOutVector ) const
{
	// 値を返す
	*pOutPosition = pTablePointLookAt_[ index ].position_;
	*pOutVector = pTablePointLookAt_[ index ].vector_;
}

//==============================================================================
// Brief  : フレーム数の設定
// Return : void								: なし
// Arg    : int indexSection					: セクション番号
// Arg    : int countFrame						: フレーム数
//==============================================================================
void CameraStateSpline::SetCountFrame( int indexSection, int countFrame )
{
	// フレーム数を設定する
	pFrame_[ indexSection ] = countFrame;
}

//==============================================================================
// Brief  : 総フレーム数の取得
// Return : int									: 総フレーム数
// Arg    : void								: カメラクラス
//==============================================================================
int CameraStateSpline::GetCountFrame( void )
{
	// 総フレーム数を求める
	int		countFrame;		// 総フレーム数
	countFrame = 0;
	for( int counterSection = 0; counterSection < countSection_; ++counterSection )
	{
		countFrame += pFrame_[ counterSection ];
	}

	// 総フレーム数を返す
	return countFrame;
}

//==============================================================================
// Brief  : 総フレーム数の取得
// Return : int									: 総フレーム数
// Arg    : int indexSection					: セクション番号
//==============================================================================
int CameraStateSpline::GetCountFrame( int indexSection )
{
	// フレーム数を返す
	return pFrame_[ indexSection ];
}

//==============================================================================
// Brief  : 開始視点番号の取得
// Return : int									: 開始視点番号
// Arg    : int indexSection					: セクション番号
//==============================================================================
int CameraStateSpline::GetIndexCameraBegin( int indexSection )
{
	// 開始視点番号を返す
	return pIndexPointCameraBegin_[ indexSection ];
}

//==============================================================================
// Brief  : 終了視点番号の取得
// Return : int									: 終了視点番号
// Arg    : int indexSection					: セクション番号
//==============================================================================
int CameraStateSpline::GetIndexCameraEnd( int indexSection )
{
	// 終了視点番号を返す
	return pIndexPointCameraEnd_[ indexSection ];
}

//==============================================================================
// Brief  : 開始注視点番号の取得
// Return : int									: 開始注視点番号
// Arg    : int indexSection					: セクション番号
//==============================================================================
int CameraStateSpline::GetIndexLookAtBegin( int indexSection )
{
	// 開始注視点番号を返す
	return pIndexPointLookAtBegin_[ indexSection ];
}

//==============================================================================
// Brief  : 終了注視点番号の取得
// Return : int									: 終了注視点番号
// Arg    : int indexSection					: セクション番号
//==============================================================================
int CameraStateSpline::GetIndexLookAtEnd( int indexSection )
{
	// 終了注視点番号を返す
	return pIndexPointLookAtEnd_[ indexSection ];
}

//==============================================================================
// Brief  : 視点座標の取得
// Return : void								: なし
// Arg    : int indexSection					: セクション番号
// Arg    : int indexFrame						: フレーム番号
// Arg    : D3DXVECTOR3* pOut					: 出力先
//==============================================================================
void CameraStateSpline::GetPositionCamera( int indexSection, int indexFrame, D3DXVECTOR3* pOut )
{
	// 視点座標を設定
	int		indexPointCameraBegin;		// 開始視点番号
	int		indexPointCameraEnd;		// 終了視点番号
	indexPointCameraBegin = pIndexPointCameraBegin_[ indexSection ];
	indexPointCameraEnd = pIndexPointCameraEnd_[ indexSection ];
	if( indexPointCameraBegin == -1 )
	{
		Assert( indexSection != 0, _T( "スプラインカメラステートの設定が不正です。" ) );
		indexPointCameraBegin = pIndexPointCameraEnd_[ indexSection - 1 ];
	}
	Utility::Spline( pTablePointCamera_[ indexPointCameraBegin ], pTablePointCamera_[ indexPointCameraEnd ],
		static_cast< float >( indexFrame ) / pFrame_[ indexSection ], pOut );
}

//==============================================================================
// Brief  : 注視点座標の取得
// Return : void								: なし
// Arg    : int indexSection					: セクション番号
// Arg    : int indexFrame						: フレーム番号
// Arg    : D3DXVECTOR3* pOut					: 出力先
//==============================================================================
void CameraStateSpline::GetPositionLookAt( int indexSection, int indexFrame, D3DXVECTOR3* pOut )
{
	// 視点座標を設定
	int		indexPointLookAtBegin;		// 開始視点番号
	int		indexPointLookAtEnd;		// 終了視点番号
	indexPointLookAtBegin = pIndexPointLookAtBegin_[ indexSection ];
	indexPointLookAtEnd = pIndexPointLookAtEnd_[ indexSection ];
	if( indexPointLookAtBegin == -1 )
	{
		Assert( indexSection != 0, _T( "スプラインカメラステートの設定が不正です。" ) );
		indexPointLookAtBegin = pIndexPointLookAtEnd_[ indexSection - 1 ];
	}
	Utility::Spline( pTablePointLookAt_[ indexPointLookAtBegin ], pTablePointLookAt_[ indexPointLookAtEnd ],
		static_cast< float >( indexFrame ) / pFrame_[ indexSection ], pOut );
}

//==============================================================================
// Brief  : セクション数の取得
// Return : int									: セクション数
// Arg    : void								: なし
//==============================================================================
int CameraStateSpline::GetCountSection( void ) const
{
	// 値の返却
	return countSection_;
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

//==============================================================================
// Brief  : 数字文字列の取得
// Return : unsigned int						: 取得後の番号
// Arg    : const TCHAR* pBuffer				: バッファ
// Arg    : unsigned int indexBegin				: 開始番号
// Arg    : unsigned int indexEnd				: 終了番号
// Arg    : int sizeOut							: 出力先サイズ
// Arg    : TCHAR* pOut							: 出力先
//==============================================================================
unsigned int CameraStateSpline::GetStringNumber( const TCHAR* pBuffer, unsigned int indexBegin, unsigned int indexEnd, int sizeOut, TCHAR* pOut )
{
	// 開始番号の決定
	unsigned int	indexCurrent;			// 現在の番号
	unsigned int	indexBeginNumber;		// 文字列開始番号
	for( indexCurrent = indexBegin; indexCurrent < indexEnd; ++indexCurrent )
	{
		if( pBuffer[ indexCurrent ] != _T( ' ' ) && pBuffer[ indexCurrent ] != _T( '\t' ) && pBuffer[ indexCurrent ] != _T( ':' )
			&& pBuffer[ indexCurrent ] != _T( '(' ) && pBuffer[ indexCurrent ] != _T( ')' ) && pBuffer[ indexCurrent ] != _T( ',' ) )
		{
			indexBeginNumber = indexCurrent;
			break;
		}
	}

	// 終了番号の決定
	unsigned int	indexEndNumber;		// 文字列終了番号
	for( ; indexCurrent < indexEnd; ++indexCurrent )
	{
		if( pBuffer[ indexCurrent ] == _T( ' ' ) || pBuffer[ indexCurrent ] == _T( '\t' ) || pBuffer[ indexCurrent ] == _T( ')' ) || pBuffer[ indexCurrent ] == _T( '\n' ) )
		{
			indexEndNumber = indexCurrent;
			break;
		}
	}

	// 文字列の取り出し
	_tcsncpy_s( pOut, sizeOut, &pBuffer[ indexBeginNumber ], indexEndNumber - indexBeginNumber );
	pOut[ indexEndNumber - indexBeginNumber ] = _T( '\0' );

	// 現在の番号を返す
	return indexCurrent;
}

//==============================================================================
// Brief  : IDからコントロール番号を取得
// Return : int									: 格納場所
// Arg    : const int* pBuffer					: ID格納領域
// Arg    : int countItem						: 格納領域要素数
// Arg    : int id								: 対象ID
//==============================================================================
int CameraStateSpline::GetIndexFromId( const int* pBuffer, int countItem, int id )
{
	// 一致するIDを検索
	for( int counterItem = 0; counterItem < countItem; ++counterItem )
	{
		if( pBuffer[ counterItem ] == id )
		{
			return counterItem;
		}
	}

	// 見つからなかった
	return -1;
}
