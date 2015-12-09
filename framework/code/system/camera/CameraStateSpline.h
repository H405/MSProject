//==============================================================================
//
// File   : CameraStateSpline.h
// Brief  : スプライン移動ステート
// Author : Taiga Shirakawa
// Date   : 2015/11/07 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_CAMERA_STATE_SPLINE_H
#define MY_CAMERA_STATE_SPLINE_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../../framework/camera/CameraState.h"
#include "../../framework/system/Utility.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class InputMouse;

//******************************************************************************
// クラス定義
//******************************************************************************
class CameraStateSpline : public CameraState
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	CameraStateSpline( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~CameraStateSpline( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int countSection					: セクション数
	// Arg    : int countControlPointCamera			: 視点コントロールポイント数
	// Arg    : int countControlPointLookAt			: 視点コントロールポイント数
	//==============================================================================
	int Initialize( int countSection, int countControlPointCamera, int countControlPointLookAt );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const TCHAR* pNameFile				: ファイル名
	//==============================================================================
	int Initialize( const TCHAR* pNameFile );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int countSection					: セクション数
	// Arg    : int countControlPointCamera			: 視点コントロールポイント数
	// Arg    : int countControlPointLookAt			: 視点コントロールポイント数
	//==============================================================================
	int Reinitialize( int countSection, int countControlPointCamera, int countControlPointLookAt );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : CameraStateSpline* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( CameraStateSpline* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : CameraObject* pCamera				: カメラクラス
	//==============================================================================
	void Update( CameraObject* pCamera );

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
	void SetSection( int index, int frame, int indexCameraBegin, int indexCameraEnd, int indexLookAtBegin, int indexLookAtEnd );

	//==============================================================================
	// Brief  : 視点コントロールポイントの設定
	// Return : void								: なし
	// Arg    : int index							: 設定する番号
	// Arg    : const D3DXVECTOR3& position			: 座標
	// Arg    : const D3DXVECTOR3& vector			: ベクトル
	//==============================================================================
	void SetControlPointCamera( int index, const D3DXVECTOR3& position, const D3DXVECTOR3& vector );

	//==============================================================================
	// Brief  : 視点コントロールポイントの取得
	// Return : void								: なし
	// Arg    : int index							: 取得する番号
	// Arg    : D3DXVECTOR3* pOutPosition			: 座標
	// Arg    : D3DXVECTOR3* pOutVector				: ベクトル
	//==============================================================================
	void GetControlPointCamera( int index, D3DXVECTOR3* pOutPosition, D3DXVECTOR3* pOutVector ) const;

	//==============================================================================
	// Brief  : 注視点コントロールポイントの設定
	// Return : void								: なし
	// Arg    : int index							: 設定する番号
	// Arg    : const D3DXVECTOR3& position			: 座標
	// Arg    : const D3DXVECTOR3& vector			: ベクトル
	//==============================================================================
	void SetControlPointLookAt( int index, const D3DXVECTOR3& position, const D3DXVECTOR3& vector );

	//==============================================================================
	// Brief  : 注視点コントロールポイントの取得
	// Return : void								: なし
	// Arg    : int index							: 取得する番号
	// Arg    : D3DXVECTOR3* pOutPosition			: 座標
	// Arg    : D3DXVECTOR3* pOutVector				: ベクトル
	//==============================================================================
	void GetControlPointLookAt( int index, D3DXVECTOR3* pOutPosition, D3DXVECTOR3* pOutVector ) const;

	//==============================================================================
	// Brief  : フレーム数の設定
	// Return : void								: なし
	// Arg    : int indexSection					: セクション番号
	// Arg    : int countFrame						: フレーム数
	//==============================================================================
	void SetCountFrame( int indexSection, int countFrame );

	//==============================================================================
	// Brief  : 総フレーム数の取得
	// Return : int									: 総フレーム数
	// Arg    : void								: カメラクラス
	//==============================================================================
	int GetCountFrame( void );

	//==============================================================================
	// Brief  : フレーム数の取得
	// Return : int									: 総フレーム数
	// Arg    : int indexSection					: セクション番号
	//==============================================================================
	int GetCountFrame( int indexSection );

	//==============================================================================
	// Brief  : 開始視点番号の取得
	// Return : int									: 開始視点番号
	// Arg    : int indexSection					: セクション番号
	//==============================================================================
	int GetIndexCameraBegin( int indexSection );

	//==============================================================================
	// Brief  : 終了視点番号の取得
	// Return : int									: 終了視点番号
	// Arg    : int indexSection					: セクション番号
	//==============================================================================
	int GetIndexCameraEnd( int indexSection );

	//==============================================================================
	// Brief  : 開始注視点番号の取得
	// Return : int									: 開始注視点番号
	// Arg    : int indexSection					: セクション番号
	//==============================================================================
	int GetIndexLookAtBegin( int indexSection );

	//==============================================================================
	// Brief  : 終了注視点番号の取得
	// Return : int									: 終了注視点番号
	// Arg    : int indexSection					: セクション番号
	//==============================================================================
	int GetIndexLookAtEnd( int indexSection );

	//==============================================================================
	// Brief  : 視点座標の取得
	// Return : void								: なし
	// Arg    : int indexSection					: セクション番号
	// Arg    : int indexFrame						: フレーム番号
	// Arg    : D3DXVECTOR3* pOut					: 出力先
	//==============================================================================
	void GetPositionCamera( int indexSection, int indexFrame, D3DXVECTOR3* pOut );

	//==============================================================================
	// Brief  : 注視点座標の取得
	// Return : void								: なし
	// Arg    : int indexSection					: セクション番号
	// Arg    : int indexFrame						: フレーム番号
	// Arg    : D3DXVECTOR3* pOut					: 出力先
	//==============================================================================
	void GetPositionLookAt( int indexSection, int indexFrame, D3DXVECTOR3* pOut );

	//==============================================================================
	// アクセサ
	//==============================================================================
	int GetCountSection( void ) const;
	void SetIsEnable( bool value );
	bool GetIsEnable( void ) const;
	bool IsEnable( void ) const;

protected:

private:
	CameraStateSpline( const CameraStateSpline& );
	CameraStateSpline operator=( const CameraStateSpline& );

	void InitializeSelf( void );
	unsigned int GetStringNumber( const TCHAR* pBuffer, unsigned int indexBegin, unsigned int indexEnd, int sizeOut, TCHAR* pOut );
	int GetIndexFromId( const int* pBuffer, int countItem, int id );

	int								countSection_;					// セクション数
	int								countControlPointCamera_;		// 視点コントロールポイント数
	int								countControlPointLookAt_;		// 注視点コントロールポイント数
	int								indexSection_;					// セクション番号
	int								countFrame_;					// 経過フレーム数
	int*							pFrame_;						// 継続時間
	Utility::ControlPointSpline*	pTablePointCamera_;				// 視点コントロールポイントテーブル
	Utility::ControlPointSpline*	pTablePointLookAt_;				// 注視点コントロールポイントテーブル
	int*							pIndexPointCameraBegin_;		// 開始視点コントロールポイント番号
	int*							pIndexPointCameraEnd_;			// 終了視点コントロールポイント番号
	int*							pIndexPointLookAtBegin_;		// 開始注視点コントロールポイント番号
	int*							pIndexPointLookAtEnd_;			// 終了注視点コントロールポイント番号
	bool							isEnable_;						// 有効フラグ
};

#endif	// MY_CAMERA_STATE_SPLINE_H
