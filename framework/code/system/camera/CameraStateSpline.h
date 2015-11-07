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
	// Brief  : 注視点コントロールポイントの設定
	// Return : void								: なし
	// Arg    : int index							: 設定する番号
	// Arg    : const D3DXVECTOR3& position			: 座標
	// Arg    : const D3DXVECTOR3& vector			: ベクトル
	//==============================================================================
	void SetControlPointLookAt( int index, const D3DXVECTOR3& position, const D3DXVECTOR3& vector );

protected:

private:
	void InitializeSelf( void );
	CameraStateSpline( const CameraStateSpline& );
	CameraStateSpline operator=( const CameraStateSpline& );

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
};

#endif	// MY_CAMERA_STATE_SPLINE_H
