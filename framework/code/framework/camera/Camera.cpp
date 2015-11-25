//==============================================================================
//
// File   : Camera.cpp
// Brief  : カメラクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Camera.h"
#include "../render/RenderMatrix.h"

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
Camera::Camera( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Camera::~Camera( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Camera::Initialize( void )
{
	// 描画用変換行列の生成
	int		result;		// 実行結果
	pRenderMatrix_ = new RenderMatrix();
	if( pRenderMatrix_ == nullptr )
	{
		return 1;
	}
	result = pRenderMatrix_->Initialize();
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
int Camera::Finalize( void )
{
	// 描画用変換行列の破棄
	delete pRenderMatrix_;
	pRenderMatrix_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Camera::Reinitialize( void )
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
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Camera* pOut						: コピー先アドレス
//==============================================================================
int Camera::Copy( Camera* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Camera::Update( void )
{
	// ビューマトリクスの更新
	if( pRenderMatrix_ != nullptr )
	{
		D3DXMATRIX	matrixView;		// ビューマトリクス
		D3DXMatrixLookAtLH( &matrixView, &positionCamera_, &positionLookAt_, &vectorUp_ );
		pRenderMatrix_->SetMatrixView( matrixView );
	}
}

//==============================================================================
// Brief  : 値の設定
// Return : void								: なし
// Arg    : float viewField						: 視野角
// Arg    : int widthScreen						: スクリーン幅
// Arg    : int heightScreen					: スクリーン高さ
// Arg    : float clipNear						: 近くのクリップ面
// Arg    : float clipFar						: 遠くのクリップ面
// Arg    : const D3DXVECTOR3& positionCamera	: 視点
// Arg    : const D3DXVECTOR3& positionLookAt	: 注視点
// Arg    : const D3DXVECTOR3& vectorUp			: 上方向ベクトル
//==============================================================================
void Camera::Set( float viewField, int widthScreen, int heightScreen, float clipNear, float clipFar,
	const D3DXVECTOR3& positionCamera, const D3DXVECTOR3& positionLookAt, const D3DXVECTOR3& vectorUp, bool isPerspective )
{
	// メンバ変数の設定
	viewField_ = viewField;
	widthScreen_ = static_cast< float >( widthScreen );
	heightScreen_ = static_cast< float >( heightScreen );
	clipNear_ = clipNear;
	clipFar_ = clipFar;
	positionCamera_ = positionCamera;
	positionLookAt_ = positionLookAt;
	vectorUp_ = vectorUp;

	// プロジェクションマトリクスの生成
	D3DXMATRIX	matrixProjection;		// プロジェクションマトリクス
	if( isPerspective )
	{
		D3DXMatrixPerspectiveFovLH( &matrixProjection, viewField, widthScreen_ / heightScreen_, clipNear_, clipFar_ );
	}
	else
	{
		D3DXMatrixOrthoLH( &matrixProjection, widthScreen_, heightScreen_, clipNear_, clipFar_ );
	}
	pRenderMatrix_->SetMatrixProjection( matrixProjection );
}

//==============================================================================
// Brief  : 視野角の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Camera::SetViewField( float value )
{
	// 値の設定
	viewField_ = value;
}

//==============================================================================
// Brief  : 視野角の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetViewField( void ) const
{
	// 値の返却
	return viewField_;
}

//==============================================================================
// Brief  : スクリーン幅の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Camera::SetWidthScreen( float value )
{
	// 値の設定
	widthScreen_ = value;
}

//==============================================================================
// Brief  : スクリーン幅の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetWidthScreen( void ) const
{
	// 値の返却
	return widthScreen_;
}

//==============================================================================
// Brief  : スクリーン幅の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Camera::SetHeightScreen( float value )
{
	// 値の設定
	heightScreen_ = value;
}

//==============================================================================
// Brief  : スクリーン幅の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetHeightScreen( void ) const
{
	// 値の返却
	return heightScreen_;
}

//==============================================================================
// Brief  : 近くのクリップ面の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Camera::SetClipNear( float value )
{
	// 値の設定
	clipNear_ = value;
}

//==============================================================================
// Brief  : 近くのクリップ面の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetClipNear( void ) const
{
	// 値の返却
	return clipNear_;
}

//==============================================================================
// Brief  : 遠くのクリップ面の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Camera::SetClipFar( float value )
{
	// 値の設定
	clipFar_ = value;
}

//==============================================================================
// Brief  : 遠くのクリップ面の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetClipFar( void ) const
{
	// 値の返却
	return clipFar_;
}

//==============================================================================
// Brief  : 視点座標の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void Camera::SetPositionCamera( const D3DXVECTOR3& value )
{
	// 値の設定
	positionCamera_ = value;
}

//==============================================================================
// Brief  : 視点座標の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void Camera::SetPositionCamera( float x, float y, float z )
{
	// 値の設定
	positionCamera_.x = x;
	positionCamera_.y = y;
	positionCamera_.z = z;
}

//==============================================================================
// Brief  : 視点座標のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void Camera::SetPositionCameraX( float x )
{
	// 値の設定
	positionCamera_.x = x;
}

//==============================================================================
// Brief  : 視点座標のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Camera::SetPositionCameraY( float y )
{
	// 値の設定
	positionCamera_.y = y;
}

//==============================================================================
// Brief  : 視点座標のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void Camera::SetPositionCameraZ( float z )
{
	// 値の設定
	positionCamera_.z = z;
}

//==============================================================================
// Brief  : 視点座標の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void Camera::GetPositionCamera( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = positionCamera_;
}

//==============================================================================
// Brief  : 視点座標のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetPositionCameraX( void ) const
{
	// 値の返却
	return positionCamera_.x;
}

//==============================================================================
// Brief  : 視点座標のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetPositionCameraY( void ) const
{
	// 値の返却
	return positionCamera_.y;
}

//==============================================================================
// Brief  : 視点座標のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetPositionCameraZ( void ) const
{
	// 値の返却
	return positionCamera_.z;
}
//==============================================================================
// Brief  : 視点座標の加算
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 加算する値
//==============================================================================
void Camera::AddPositionCamera( const D3DXVECTOR3& value )
{
	// 値の加算
	positionCamera_ += value;
}

//==============================================================================
// Brief  : 視点座標の加算
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void Camera::AddPositionCamera( float x, float y, float z )
{
	// 値の加算
	positionCamera_.x += x;
	positionCamera_.y += y;
	positionCamera_.z += z;
}

//==============================================================================
// Brief  : 視点座標のX値の加算
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void Camera::AddPositionCameraX( float x )
{
	// 値の加算
	positionCamera_.x += x;
}

//==============================================================================
// Brief  : 視点座標のY値の加算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Camera::AddPositionCameraY( float y )
{
	// 値の加算
	positionCamera_.y += y;
}

//==============================================================================
// Brief  : 視点座標のZ値の加算
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void Camera::AddPositionCameraZ( float z )
{
	// 値の加算
	positionCamera_.z += z;
}

//==============================================================================
// Brief  : 注視点座標の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void Camera::SetPositionLookAt( const D3DXVECTOR3& value )
{
	// 値の設定
	positionLookAt_ = value;
}

//==============================================================================
// Brief  : 注視点座標の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void Camera::SetPositionLookAt( float x, float y, float z )
{
	// 値の設定
	positionLookAt_.x = x;
	positionLookAt_.y = y;
	positionLookAt_.z = z;
}

//==============================================================================
// Brief  : 注視点座標のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void Camera::SetPositionLookAtX( float x )
{
	// 値の設定
	positionLookAt_.x = x;
}

//==============================================================================
// Brief  : 注視点座標のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Camera::SetPositionLookAtY( float y )
{
	// 値の設定
	positionLookAt_.y = y;
}

//==============================================================================
// Brief  : 注視点座標のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void Camera::SetPositionLookAtZ( float z )
{
	// 値の設定
	positionLookAt_.z = z;
}

//==============================================================================
// Brief  : 注視点座標の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void Camera::GetPositionLookAt( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = positionLookAt_;
}

//==============================================================================
// Brief  : 注視点座標のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetPositionLookAtX( void ) const
{
	// 値の返却
	return positionLookAt_.x;
}

//==============================================================================
// Brief  : 注視点座標のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetPositionLookAtY( void ) const
{
	// 値の返却
	return positionLookAt_.y;
}

//==============================================================================
// Brief  : 注視点座標のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetPositionLookAtZ( void ) const
{
	// 値の返却
	return positionLookAt_.z;
}

//==============================================================================
// Brief  : 注視点座標の加算
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 加算する値
//==============================================================================
void Camera::AddPositionLookAt( const D3DXVECTOR3& value )
{
	// 値の加算
	positionLookAt_ += value;
}

//==============================================================================
// Brief  : 注視点座標の加算
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void Camera::AddPositionLookAt( float x, float y, float z )
{
	// 値の加算
	positionLookAt_.x += x;
	positionLookAt_.y += y;
	positionLookAt_.z += z;
}

//==============================================================================
// Brief  : 注視点座標のX値の加算
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void Camera::AddPositionLookAtX( float x )
{
	// 値の加算
	positionLookAt_.x += x;
}

//==============================================================================
// Brief  : 注視点座標のY値の加算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Camera::AddPositionLookAtY( float y )
{
	// 値の加算
	positionLookAt_.y += y;
}

//==============================================================================
// Brief  : 注視点座標のZ値の加算
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void Camera::AddPositionLookAtZ( float z )
{
	// 値の加算
	positionLookAt_.z += z;
}

//==============================================================================
// Brief  : 上方向ベクトルの設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void Camera::SetVectorUp( const D3DXVECTOR3& value )
{
	// 値の設定
	vectorUp_ = value;
}

//==============================================================================
// Brief  : 上方向ベクトルの設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void Camera::SetVectorUp( float x, float y, float z )
{
	// 値の設定
	vectorUp_.x = x;
	vectorUp_.y = y;
	vectorUp_.z = z;
}

//==============================================================================
// Brief  : 上方向ベクトルのX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void Camera::SetVectorUpX( float x )
{
	// 値の設定
	vectorUp_.x = x;
}

//==============================================================================
// Brief  : 上方向ベクトルのY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Camera::SetVectorUpY( float y )
{
	// 値の設定
	vectorUp_.y = y;
}

//==============================================================================
// Brief  : 上方向ベクトルのZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void Camera::SetVectorUpZ( float z )
{
	// 値の設定
	vectorUp_.z = z;
}

//==============================================================================
// Brief  : 上方向ベクトルの取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void Camera::GetVectorUp( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = vectorUp_;
}

//==============================================================================
// Brief  : 上方向ベクトルのX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetVectorUpX( void ) const
{
	// 値の返却
	return vectorUp_.x;
}

//==============================================================================
// Brief  : 上方向ベクトルのY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetVectorUpY( void ) const
{
	// 値の返却
	return vectorUp_.y;
}

//==============================================================================
// Brief  : 上方向ベクトルのZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Camera::GetVectorUpZ( void ) const
{
	// 値の返却
	return vectorUp_.z;
}

//==============================================================================
// Brief  : 描画用変換行列の設定
// Return : void								: なし
// Arg    : RenderMatrix* pValue				: 設定する値
//==============================================================================
void Camera::SetRenderMatrix( RenderMatrix* pValue )
{
	// 値の設定
	pRenderMatrix_ = pValue;
}

//==============================================================================
// Brief  : 描画用変換行列の取得
// Return : RenderMatrix*						: 返却する値
// Arg    : void								: なし
//==============================================================================
RenderMatrix* Camera::GetRenderMatrix( void ) const
{
	// 値の返却
	return pRenderMatrix_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Camera::InitializeSelf( void )
{
	// メンバ変数の初期化
	viewField_ = 0.0f;
	widthScreen_ = 0.0f;
	heightScreen_ = 0.0f;
	clipNear_ = 0.0f;
	clipFar_ = 0.0f;
	positionCamera_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	positionLookAt_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vectorUp_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	pRenderMatrix_ = nullptr;
}
