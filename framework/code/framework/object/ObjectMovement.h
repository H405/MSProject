//==============================================================================
//
// File   : ObjectMovement.h
// Brief  : 移動オブジェクト
// Author : Taiga Shirakawa
// Date   : 2015/10/20 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_MOVEMENT_H
#define MY_OBJECT_MOVEMENT_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"
#include "Object.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectMovement : public Object
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectMovement( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	virtual ~ObjectMovement( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	//==============================================================================
	virtual int Initialize( int priority );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	virtual int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	//==============================================================================
	virtual int Reinitialize( int priority );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ObjectMovement* pOut				: コピー先アドレス
	//==============================================================================
	virtual int Copy( ObjectMovement* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	virtual void Update( void );

	//==============================================================================
	// Brief  : ステート更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void UpdateState( void );

	//==============================================================================
	// Brief  : ステートの設定
	// Return : void								: なし
	// Arg    : int index							: ステート番号
	//==============================================================================
	virtual void SetState( int index );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetVelocityPosition( const D3DXVECTOR3& value );
	void SetVelocityPosition( float x, float y, float z );
	void SetVelocityPositionX( float x );
	void SetVelocityPositionY( float y );
	void SetVelocityPositionZ( float z );
	void GetVelocityPosition( D3DXVECTOR3* pOut ) const;
	float GetVelocityPositionX( void ) const;
	float GetVelocityPositionY( void ) const;
	float GetVelocityPositionZ( void ) const;
	void SetVelocityRotation( const D3DXVECTOR3& value );
	void SetVelocityRotation( float x, float y, float z );
	void SetVelocityRotationX( float x );
	void SetVelocityRotationY( float y );
	void SetVelocityRotationZ( float z );
	void GetVelocityRotation( D3DXVECTOR3* pOut ) const;
	float GetVelocityRotationX( void ) const;
	float GetVelocityRotationY( void ) const;
	float GetVelocityRotationZ( void ) const;
	void SetVelocityScale( const D3DXVECTOR3& value );
	void SetVelocityScale( float x, float y, float z );
	void SetVelocityScaleX( float x );
	void SetVelocityScaleY( float y );
	void SetVelocityScaleZ( float z );
	void GetVelocityScale( D3DXVECTOR3* pOut ) const;
	float GetVelocityScaleX( void ) const;
	float GetVelocityScaleY( void ) const;
	float GetVelocityScaleZ( void ) const;
	void SetAccelPosition( const D3DXVECTOR3& value );
	void SetAccelPosition( float x, float y, float z );
	void SetAccelPositionX( float x );
	void SetAccelPositionY( float y );
	void SetAccelPositionZ( float z );
	void GetAccelPosition( D3DXVECTOR3* pOut ) const;
	float GetAccelPositionX( void ) const;
	float GetAccelPositionY( void ) const;
	float GetAccelPositionZ( void ) const;
	void SetFriction( float value );
	float GetFriction( void ) const;
	void SetTimeState( int value );
	int GetTimeState( void ) const;
	int GetIndexStateCurrent( void ) const;
	void SetIndexStateNext( int value );
	int GetIndexStateNext( void ) const;

protected:

private:
	virtual void InitializeSelf( void );
	ObjectMovement( const ObjectMovement& );
	ObjectMovement operator=( const ObjectMovement& );

	D3DXVECTOR3	velocityPosition_;		// 座標速度
	D3DXVECTOR3	velocityRotation_;		// 回転速度
	D3DXVECTOR3	velocityScale_;			// 拡縮速度
	D3DXVECTOR3	accelPosition_;			// 座標加速度
	float		friction_;				// 摩擦
	int			timeState_;				// ステート経過時間
	int			indexStateCurrent_;		// 現在のステート番号
	int			indexStateNext_;		// 次のステート番号
};

#endif	// MY_OBJECT_MOVEMENT_H
