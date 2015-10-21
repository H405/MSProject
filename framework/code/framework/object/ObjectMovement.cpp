//==============================================================================
//
// File   : ObjectMovement.cpp
// Brief  : 移動オブジェクト
// Author : Taiga Shirakawa
// Date   : 2015/10/20 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectMovement.h"

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
ObjectMovement::ObjectMovement( void ) : Object()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectMovement::~ObjectMovement( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectMovement::Initialize( int priority )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( priority );
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
int ObjectMovement::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Finalize();
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
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectMovement::Reinitialize( int priority )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( priority );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ObjectMovement* pOut				: コピー先アドレス
//==============================================================================
int ObjectMovement::Copy( ObjectMovement* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Copy( pOut );
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
// Arg    : void								: なし
//==============================================================================
void ObjectMovement::Update( void )
{
	// 速度の加算
	position_ += velocityPosition_;
	rotation_ += velocityRotation_;
	scale_ += velocityScale_;
	velocityPosition_ += accelPosition_;
	velocityPosition_.x *= friction_;
	velocityPosition_.z *= friction_;

	// 処理時間経過
	++indexStateCurrent_;

	// 基本クラスの処理
	Object::Update();
}

//==============================================================================
// Brief  : ステート更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectMovement::UpdateState( void )
{
	// ステート番号の更新
	if( indexStateNext_ != -1 )
	{
		indexStateCurrent_ = indexStateNext_;
		indexStateNext_ = -1;
		timeState_ = 0;
	}
}

//==============================================================================
// Brief  : ステートの設定
// Return : void								: なし
// Arg    : int index							: ステート番号
//==============================================================================
void ObjectMovement::SetState( int index )
{
	// 次のステートを設定
	indexStateNext_ = index;
}

//==============================================================================
// Brief  : 座標速度の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void ObjectMovement::SetVelocityPosition( const D3DXVECTOR3& value )
{
	// 値の設定
	velocityPosition_ = value;
}

//==============================================================================
// Brief  : 座標速度の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void ObjectMovement::SetVelocityPosition( float x, float y, float z )
{
	// 値の設定
	velocityPosition_.x = x;
	velocityPosition_.y = y;
	velocityPosition_.z = z;
}

//==============================================================================
// Brief  : 座標速度のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void ObjectMovement::SetVelocityPositionX( float x )
{
	// 値の設定
	velocityPosition_.x = x;
}

//==============================================================================
// Brief  : 座標速度のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectMovement::SetVelocityPositionY( float y )
{
	// 値の設定
	velocityPosition_.y = y;
}

//==============================================================================
// Brief  : 座標速度のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void ObjectMovement::SetVelocityPositionZ( float z )
{
	// 値の設定
	velocityPosition_.z = z;
}

//==============================================================================
// Brief  : 座標速度の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void ObjectMovement::GetVelocityPosition( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = velocityPosition_;
}

//==============================================================================
// Brief  : 座標速度のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetVelocityPositionX( void ) const
{
	// 値の返却
	return velocityPosition_.x;
}

//==============================================================================
// Brief  : 座標速度のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetVelocityPositionY( void ) const
{
	// 値の返却
	return velocityPosition_.y;
}

//==============================================================================
// Brief  : 座標速度のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetVelocityPositionZ( void ) const
{
	// 値の返却
	return velocityPosition_.z;
}

//==============================================================================
// Brief  : 回転速度の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void ObjectMovement::SetVelocityRotation( const D3DXVECTOR3& value )
{
	// 値の設定
	velocityRotation_ = value;
}

//==============================================================================
// Brief  : 回転速度の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void ObjectMovement::SetVelocityRotation( float x, float y, float z )
{
	// 値の設定
	velocityRotation_.x = x;
	velocityRotation_.y = y;
	velocityRotation_.z = z;
}

//==============================================================================
// Brief  : 回転速度のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void ObjectMovement::SetVelocityRotationX( float x )
{
	// 値の設定
	velocityRotation_.x = x;
}

//==============================================================================
// Brief  : 回転速度のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectMovement::SetVelocityRotationY( float y )
{
	// 値の設定
	velocityRotation_.y = y;
}

//==============================================================================
// Brief  : 回転速度のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void ObjectMovement::SetVelocityRotationZ( float z )
{
	// 値の設定
	velocityRotation_.z = z;
}

//==============================================================================
// Brief  : 回転速度の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void ObjectMovement::GetVelocityRotation( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = velocityRotation_;
}

//==============================================================================
// Brief  : 回転速度のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetVelocityRotationX( void ) const
{
	// 値の返却
	return velocityRotation_.x;
}

//==============================================================================
// Brief  : 回転速度のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetVelocityRotationY( void ) const
{
	// 値の返却
	return velocityRotation_.y;
}

//==============================================================================
// Brief  : 回転速度のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetVelocityRotationZ( void ) const
{
	// 値の返却
	return velocityRotation_.z;
}

//==============================================================================
// Brief  : 拡縮速度の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void ObjectMovement::SetVelocityScale( const D3DXVECTOR3& value )
{
	// 値の設定
	velocityScale_ = value;
}

//==============================================================================
// Brief  : 拡縮速度の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void ObjectMovement::SetVelocityScale( float x, float y, float z )
{
	// 値の設定
	velocityScale_.x = x;
	velocityScale_.y = y;
	velocityScale_.z = z;
}

//==============================================================================
// Brief  : 拡縮速度のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void ObjectMovement::SetVelocityScaleX( float x )
{
	// 値の設定
	velocityScale_.x = x;
}

//==============================================================================
// Brief  : 拡縮速度のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectMovement::SetVelocityScaleY( float y )
{
	// 値の設定
	velocityScale_.y = y;
}

//==============================================================================
// Brief  : 拡縮速度のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void ObjectMovement::SetVelocityScaleZ( float z )
{
	// 値の設定
	velocityScale_.z = z;
}

//==============================================================================
// Brief  : 拡縮速度の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void ObjectMovement::GetVelocityScale( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = velocityScale_;
}

//==============================================================================
// Brief  : 拡縮速度のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetVelocityScaleX( void ) const
{
	// 値の返却
	return velocityScale_.x;
}

//==============================================================================
// Brief  : 拡縮速度のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetVelocityScaleY( void ) const
{
	// 値の返却
	return velocityScale_.y;
}

//==============================================================================
// Brief  : 拡縮速度のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetVelocityScaleZ( void ) const
{
	// 値の返却
	return velocityScale_.z;
}

//==============================================================================
// Brief  : 座標加速度の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void ObjectMovement::SetAccelPosition( const D3DXVECTOR3& value )
{
	// 値の設定
	accelPosition_ = value;
}

//==============================================================================
// Brief  : 座標加速度の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void ObjectMovement::SetAccelPosition( float x, float y, float z )
{
	// 値の設定
	accelPosition_.x = x;
	accelPosition_.y = y;
	accelPosition_.z = z;
}

//==============================================================================
// Brief  : 座標加速度のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void ObjectMovement::SetAccelPositionX( float x )
{
	// 値の設定
	accelPosition_.x = x;
}

//==============================================================================
// Brief  : 座標加速度のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectMovement::SetAccelPositionY( float y )
{
	// 値の設定
	accelPosition_.y = y;
}

//==============================================================================
// Brief  : 座標加速度のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void ObjectMovement::SetAccelPositionZ( float z )
{
	// 値の設定
	accelPosition_.z = z;
}

//==============================================================================
// Brief  : 座標加速度の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void ObjectMovement::GetAccelPosition( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = accelPosition_;
}

//==============================================================================
// Brief  : 座標加速度のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetAccelPositionX( void ) const
{
	// 値の返却
	return accelPosition_.x;
}

//==============================================================================
// Brief  : 座標加速度のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetAccelPositionY( void ) const
{
	// 値の返却
	return accelPosition_.y;
}

//==============================================================================
// Brief  : 座標加速度のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetAccelPositionZ( void ) const
{
	// 値の返却
	return accelPosition_.z;
}

//==============================================================================
// Brief  : 摩擦の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void ObjectMovement::SetFriction( float value )
{
	// 値の設定
	friction_ = value;
}

//==============================================================================
// Brief  : 摩擦の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectMovement::GetFriction( void ) const
{
	// 値の返却
	return friction_;
}

//==============================================================================
// Brief  : ステート経過時間の設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void ObjectMovement::SetTimeState( int value )
{
	// 値の設定
	timeState_ = value;
}

//==============================================================================
// Brief  : ステート経過時間の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int ObjectMovement::GetTimeState( void ) const
{
	// 値の返却
	return timeState_;
}

//==============================================================================
// Brief  : 現在のステート番号の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int ObjectMovement::GetIndexStateCurrent( void ) const
{
	// 値の返却
	return indexStateCurrent_;
}

//==============================================================================
// Brief  : 次のステート番号の設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void ObjectMovement::SetIndexStateNext( int value )
{
	// 値の設定
	indexStateNext_ = value;
}

//==============================================================================
// Brief  : 次のステート番号の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int ObjectMovement::GetIndexStateNext( void ) const
{
	// 値の返却
	return indexStateNext_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectMovement::InitializeSelf( void )
{
	// メンバ変数の初期化
	velocityPosition_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );;
	velocityRotation_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );;
	velocityScale_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );;
	accelPosition_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );;
	friction_ = 1.0f;
	timeState_ = 0;
	indexStateCurrent_ = 0;
	indexStateNext_ = -1;
}
