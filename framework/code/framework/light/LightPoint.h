//==============================================================================
//
// File   : LightPoint.h
// Brief  : ポイントライトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_LIGHT_POINT_H
#define MY_LIGHT_POINT_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "Light.h"

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
class LightPoint : public Light
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	LightPoint( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~LightPoint( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Initialize( void );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Reinitialize( void );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : LightPoint* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( LightPoint* pOut ) const;

	//==============================================================================
	// アクセサ
	//==============================================================================
	void Set( const D3DXCOLOR& diffuse, const D3DXCOLOR& specular, const D3DXVECTOR3& position, const D3DXVECTOR3& attemuation );
	void SetPosition( const D3DXVECTOR3& value );
	void SetPosition( float x, float y, float z );
	void SetPositionX( float x );
	void SetPositionY( float y );
	void SetPositionZ( float z );
	void GetPosition( D3DXVECTOR3* pOut ) const;
	float GetPositionX( void ) const;
	float GetPositionY( void ) const;
	float GetPositionZ( void ) const;
	void SetAttemuation( const D3DXVECTOR3& value );
	void SetAttemuation( float x, float y, float z );
	void SetAttemuationX( float x );
	void SetAttemuationY( float y );
	void SetAttemuationZ( float z );
	void GetAttemuation( D3DXVECTOR3* pOut ) const;
	float GetAttemuationX( void ) const;
	float GetAttemuationY( void ) const;
	float GetAttemuationZ( void ) const;

protected:
	D3DXVECTOR3	position_;			// 座標
	D3DXVECTOR3	attemuation_;		// 減衰率

private:
	void InitializeSelf( void );
	LightPoint( const LightPoint& );
	LightPoint operator=( const LightPoint& );

};

#endif	// MY_LIGHT_POINT_H
