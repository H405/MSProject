//==============================================================================
//
// File   : CameraObject.h
// Brief  : カメラオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_CAMERA_OBJECT_H
#define MY_CAMERA_OBJECT_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "Camera.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class CameraStateDebug;
class CameraState;

//******************************************************************************
// クラス定義
//******************************************************************************
class CameraObject : public Camera
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	CameraObject( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~CameraObject( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : float viewField						: 視野角
	// Arg    : int widthScreen						: スクリーン幅
	// Arg    : int heightScreen					: スクリーン高さ
	// Arg    : float clipNear						: 近くのクリップ面
	// Arg    : float clipFar						: 遠くのクリップ面
	// Arg    : const D3DXVECTOR3& positionCamera	: 視点
	// Arg    : const D3DXVECTOR3& positionLookAt	: 注視点
	// Arg    : const D3DXVECTOR3& vectorUp			: 上方向ベクトル
	//==============================================================================
	int Initialize( float viewField, int widthScreen, int heightScreen, float clipNear, float clipFar, const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : float viewField						: 視野角
	// Arg    : int widthScreen						: スクリーン幅
	// Arg    : int heightScreen					: スクリーン高さ
	// Arg    : float clipNear						: 近くのクリップ面
	// Arg    : float clipFar						: 遠くのクリップ面
	// Arg    : const D3DXVECTOR3& positionCamera	: 視点
	// Arg    : const D3DXVECTOR3& positionLookAt	: 注視点
	// Arg    : const D3DXVECTOR3& vectorUp			: 上方向ベクトル
	//==============================================================================
	int Reinitialize( float viewField, int widthScreen, int heightScreen, float clipNear, float clipFar, const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : CameraObject* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( CameraObject* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : デバッグ設定
	// Return : void								: なし
	// Arg    : bool value							: 設定する値
	//==============================================================================
	void SetDebug( bool value );

	//==============================================================================
	// Brief  : カメラベクトルの取得
	// Return : void								: なし
	// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
	//==============================================================================
	void GetVector( D3DXVECTOR3* pOut );

	//==============================================================================
	// Brief  : 移動
	// Return : void								: なし
	// Arg    : const D3DXVECTOR3& vectorMove		: 移動ベクトル
	//==============================================================================
	void Move( const D3DXVECTOR3& vectorMove );

	//==============================================================================
	// Brief  : ビュー空間のZ値を取得
	// Return : float								: Z値
	// Arg    : const D3DXVECTOR3& position			: 座標
	//==============================================================================
	float GetViewZ( const D3DXVECTOR3& position );

	//==============================================================================
	// Brief  : プロジェクション空間のZ値を取得
	// Return : float								: Z値
	// Arg    : const D3DXVECTOR3& position			: 座標
	//==============================================================================
	float GetProjectionZ( const D3DXVECTOR3& position );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetPosition( const D3DXVECTOR3& value );
	void SetPosition( float x, float y, float z );
	void SetPositionX( float x );
	void SetPositionY( float y );
	void SetPositionZ( float z );
	void AddPosition( const D3DXVECTOR3& value );
	void AddPosition( float x, float y, float z );
	void AddPositionX( float x );
	void AddPositionY( float y );
	void AddPositionZ( float z );
	void SetRotationCameraX( float x );
	void SetRotationCameraY( float y );
	void AddRotationCameraX( float x );
	void AddRotationCameraY( float y );
	void SetRotationLookAtX( float x );
	void SetRotationLookAtY( float y );
	void AddRotationLookAtX( float x );
	void AddRotationLookAtY( float y );
	float GetRotationX( void );
	float GetRotationY( void );
	void SetState( CameraState* pValue );
	CameraState* GetState( void ) const;

protected:
	CameraState*		pState_;				// ステート

#ifdef _DEVELOP
	CameraState*		pStateOriginal_;		// 元のステート
	CameraStateDebug*	pStateDebug_;			// デバッグステート
	bool				isDebugMode_;			// デバッグモードフラグ
#endif

private:
	void InitializeSelf( void );
	CameraObject( const CameraObject& );
	CameraObject operator=( const CameraObject& );

};

#endif	// MY_CAMERA_OBJECT_H
