//==============================================================================
//
// File   : Object.h
// Brief  : オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_H
#define MY_OBJECT_H

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
class Graphic;
template < class Object > class ManagerUpdate;

//******************************************************************************
// クラス定義
//******************************************************************************
class Object
{
public:
	// 回転の種類
	enum
	{
		ROTATION_VECTOR = 0,		// D3DXVECTOR3型
		ROTATION_QUATERNION,		// D3DXQUATERNION型
		ROTATION_MATRIX,			// D3DXMATRIX型
		ROTATION_MAX				// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Object( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	virtual ~Object( void );

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
	// Arg    : Object* pOut						: コピー先アドレス
	//==============================================================================
	virtual int Copy( Object* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	virtual void Update( void );

	//==============================================================================
	// Brief  : 描画クラスの生成
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	//==============================================================================
	int CreateGraphic( int priority );

	//==============================================================================
	// Brief  : 更新管理クラスの設定
	// Return : void								: なし
	// Arg    : ManagerUpdate* pValue				: 設定する値
	//==============================================================================
	static void SetManagerUpdate( ManagerUpdate< Object >* pValue );

	//==============================================================================
	// Brief  : 描画クラスの有効設定
	// Return : void								: なし
	// Arg    : bool value							: 設定する値
	//==============================================================================
	void SetEnableGraphic( bool value );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetParent( Object* pValue );
	Object* GetParent( void ) const;
	void SetGraphic( Graphic* pValue );
	Graphic* GetGraphic( void ) const;
	void SetPosition( const D3DXVECTOR3& value );
	void SetPosition( float x, float y, float z );
	void SetPositionX( float x );
	void SetPositionY( float y );
	void SetPositionZ( float z );
	void GetPosition( D3DXVECTOR3* pOut ) const;
	float GetPositionX( void ) const;
	float GetPositionY( void ) const;
	float GetPositionZ( void ) const;
	void AddPosition( const D3DXVECTOR3& value );
	void AddPosition( float x, float y, float z );
	void AddPositionX( float x );
	void AddPositionY( float y );
	void AddPositionZ( float z );
	void SetTypeRotation( int value );
	int GetTypeRotation( void ) const;
	void SetRotation( const D3DXVECTOR3& value );
	void SetRotation( float x, float y, float z );
	void SetRotationX( float x );
	void SetRotationY( float y );
	void SetRotationZ( float z );
	void GetRotation( D3DXVECTOR3* pOut ) const;
	float GetRotationX( void ) const;
	float GetRotationY( void ) const;
	float GetRotationZ( void ) const;
	void AddRotation( const D3DXVECTOR3& value );
	void AddRotation( float x, float y, float z );
	void AddRotationX( float x );
	void AddRotationY( float y );
	void AddRotationZ( float z );
	void SetQuaternionRotation( const D3DXQUATERNION& value );
	void GetQuaternionRotation( D3DXQUATERNION* pOut ) const;
	void SetMatrixRotation( const D3DXMATRIX& value );
	void GetMatrixRotation( D3DXMATRIX* pOut ) const;
	void SetScale( const D3DXVECTOR3& value );
	void SetScale( float x, float y, float z );
	void SetScaleX( float x );
	void SetScaleY( float y );
	void SetScaleZ( float z );
	void GetScale( D3DXVECTOR3* pOut ) const;
	float GetScaleX( void ) const;
	float GetScaleY( void ) const;
	float GetScaleZ( void ) const;
	void AddScale( const D3DXVECTOR3& value );
	void AddScale( float x, float y, float z );
	void AddScaleX( float x );
	void AddScaleY( float y );
	void AddScaleZ( float z );
	void SetMatrixWorld( const D3DXMATRIX& value );
	void GetMatrixWorld( D3DXMATRIX* pOut ) const;
	void SetIsEnable( bool value );
	bool GetIsEnable( void ) const;
	bool IsEnable( void ) const;

protected:
	int				idUpdate_;					// 更新登録番号
	Object*			pParent_;					// 親オブジェクト
	Graphic*		pGraphic_;					// 描画クラス
	D3DXVECTOR3		position_;					// 座標
	int				typeRotation_;				// 回転の種類
	D3DXVECTOR3		rotation_;					// 回転
	D3DXQUATERNION	quaternionRotation_;		// 回転クォータニオン
	D3DXMATRIX		matrixRotation_;			// 回転行列
	D3DXVECTOR3		scale_;						// 拡縮
	D3DXMATRIX		matrixWorld_;				// ワールドマトリクス
	bool			needsUpdate_;				// 更新フラグ
	bool			isEnable_;					// 有効フラグ

private:
	virtual void InitializeSelf( void );
	Object( const Object& );
	Object operator=( const Object& );

	static ManagerUpdate< Object >*	pManagerUpdate_;			// 更新管理クラス
};

#endif	// MY_OBJECT_H
