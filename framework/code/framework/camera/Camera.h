//==============================================================================
//
// File   : Camera.h
// Brief  : カメラクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_CAMERA_H
#define MY_CAMERA_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class RenderMatrix;

//******************************************************************************
// クラス定義
//******************************************************************************
class Camera
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Camera( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	virtual ~Camera( void );

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
	virtual int Initialize( float viewField, int widthScreen, int heightScreen,
		float clipNear, float clipFar, const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	virtual int Finalize( void );

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
	virtual int Reinitialize( float viewField, int widthScreen, int heightScreen,
		float clipNear, float clipFar, const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Camera* pOut						: コピー先アドレス
	//==============================================================================
	virtual int Copy( Camera* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetViewField( float value );
	float GetViewField( void ) const;
	void SetWidthScreen( float value );
	float GetWidthScreen( void ) const;
	void SetHeightScreen( float value );
	float GetHeightScreen( void ) const;
	void SetClipNear( float value );
	float GetClipNear( void ) const;
	void SetClipFar( float value );
	float GetClipFar( void ) const;
	void SetPositionCamera( const D3DXVECTOR3& value );
	void SetPositionCamera( float x, float y, float z );
	void SetPositionCameraX( float x );
	void SetPositionCameraY( float y );
	void SetPositionCameraZ( float z );
	void GetPositionCamera( D3DXVECTOR3* pOut ) const;
	float GetPositionCameraX( void ) const;
	float GetPositionCameraY( void ) const;
	float GetPositionCameraZ( void ) const;
	void AddPositionCamera( const D3DXVECTOR3& value );
	void AddPositionCamera( float x, float y, float z );
	void AddPositionCameraX( float x );
	void AddPositionCameraY( float y );
	void AddPositionCameraZ( float z );
	void SetPositionLookAt( const D3DXVECTOR3& value );
	void SetPositionLookAt( float x, float y, float z );
	void SetPositionLookAtX( float x );
	void SetPositionLookAtY( float y );
	void SetPositionLookAtZ( float z );
	void GetPositionLookAt( D3DXVECTOR3* pOut ) const;
	float GetPositionLookAtX( void ) const;
	float GetPositionLookAtY( void ) const;
	float GetPositionLookAtZ( void ) const;
	void AddPositionLookAt( const D3DXVECTOR3& value );
	void AddPositionLookAt( float x, float y, float z );
	void AddPositionLookAtX( float x );
	void AddPositionLookAtY( float y );
	void AddPositionLookAtZ( float z );
	void SetVectorUp( const D3DXVECTOR3& value );
	void SetVectorUp( float x, float y, float z );
	void SetVectorUpX( float x );
	void SetVectorUpY( float y );
	void SetVectorUpZ( float z );
	void GetVectorUp( D3DXVECTOR3* pOut ) const;
	float GetVectorUpX( void ) const;
	float GetVectorUpY( void ) const;
	float GetVectorUpZ( void ) const;
	void SetRenderMatrix( RenderMatrix* pValue );
	RenderMatrix* GetRenderMatrix( void ) const;

protected:
	float			viewField_;				// 視野角
	float			widthScreen_;			// スクリーン幅
	float			heightScreen_;			// スクリーン幅
	float			clipNear_;				// 近くのクリップ面
	float			clipFar_;				// 遠くのクリップ面
	D3DXVECTOR3		positionCamera_;		// 視点座標
	D3DXVECTOR3		positionLookAt_;		// 注視点座標
	D3DXVECTOR3		vectorUp_;				// 上方向ベクトル
	RenderMatrix*	pRenderMatrix_;			// 描画用変換行列

private:
	virtual void InitializeSelf( void );
	Camera( const Camera& );
	Camera operator=( const Camera& );

};

#endif	// MY_CAMERA_H
