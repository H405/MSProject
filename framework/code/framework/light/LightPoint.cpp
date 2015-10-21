//==============================================================================
//
// File   : LightPoint.cpp
// Brief  : ポイントライトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/13 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "LightPoint.h"

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
LightPoint::LightPoint( void ) : Light()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
LightPoint::~LightPoint( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : const D3DXCOLOR& diffuse			: ディフューズカラー
// Arg    : const D3DXCOLOR& specular			: スペキュラカラー
// Arg    : const D3DXVECTOR3& position			: 座標
// Arg    : const D3DXVECTOR3& attemuation		: 減衰率
//==============================================================================
int LightPoint::Initialize( const D3DXCOLOR& diffuse, const D3DXCOLOR& specular, const D3DXVECTOR3& position, const D3DXVECTOR3& attemuation )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Light::Initialize( diffuse, specular );
	if( result != 0 )
	{
		return result;
	}

	// メンバ変数の設定
	position_ = position;
	attemuation_ = attemuation;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int LightPoint::Finalize( void )
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Light::Finalize();
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
// Arg    : const D3DXCOLOR& diffuse			: ディフューズカラー
// Arg    : const D3DXCOLOR& specular			: スペキュラカラー
// Arg    : const D3DXVECTOR3& position			: 座標
// Arg    : const D3DXVECTOR3& attemuation		: 減衰率
//==============================================================================
int LightPoint::Reinitialize( const D3DXCOLOR& diffuse, const D3DXCOLOR& specular, const D3DXVECTOR3& position, const D3DXVECTOR3& attemuation )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( diffuse, specular, position, attemuation );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : LightPoint* pOut					: コピー先アドレス
//==============================================================================
int LightPoint::Copy( LightPoint* pOut ) const
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Light::Copy( pOut );
	if( result != 0 )
	{
		return result;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void LightPoint::SetPosition( const D3DXVECTOR3& value )
{
	// 値の設定
	position_ = value;
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void LightPoint::SetPosition( float x, float y, float z )
{
	// 値の設定
	position_.x = x;
	position_.y = y;
	position_.z = z;
}

//==============================================================================
// Brief  : 座標のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void LightPoint::SetPositionX( float x )
{
	// 値の設定
	position_.x = x;
}

//==============================================================================
// Brief  : 座標のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void LightPoint::SetPositionY( float y )
{
	// 値の設定
	position_.y = y;
}

//==============================================================================
// Brief  : 座標のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void LightPoint::SetPositionZ( float z )
{
	// 値の設定
	position_.z = z;
}

//==============================================================================
// Brief  : 座標の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void LightPoint::GetPosition( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = position_;
}

//==============================================================================
// Brief  : 座標のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float LightPoint::GetPositionX( void ) const
{
	// 値の返却
	return position_.x;
}

//==============================================================================
// Brief  : 座標のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float LightPoint::GetPositionY( void ) const
{
	// 値の返却
	return position_.y;
}

//==============================================================================
// Brief  : 座標のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float LightPoint::GetPositionZ( void ) const
{
	// 値の返却
	return position_.z;
}

//==============================================================================
// Brief  : 減衰率の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void LightPoint::SetAttemuation( const D3DXVECTOR3& value )
{
	// 値の設定
	attemuation_ = value;
}

//==============================================================================
// Brief  : 減衰率の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void LightPoint::SetAttemuation( float x, float y, float z )
{
	// 値の設定
	attemuation_.x = x;
	attemuation_.y = y;
	attemuation_.z = z;
}

//==============================================================================
// Brief  : 減衰率のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void LightPoint::SetAttemuationX( float x )
{
	// 値の設定
	attemuation_.x = x;
}

//==============================================================================
// Brief  : 減衰率のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void LightPoint::SetAttemuationY( float y )
{
	// 値の設定
	attemuation_.y = y;
}

//==============================================================================
// Brief  : 減衰率のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void LightPoint::SetAttemuationZ( float z )
{
	// 値の設定
	attemuation_.z = z;
}

//==============================================================================
// Brief  : 減衰率の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void LightPoint::GetAttemuation( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = attemuation_;
}

//==============================================================================
// Brief  : 減衰率のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float LightPoint::GetAttemuationX( void ) const
{
	// 値の返却
	return attemuation_.x;
}

//==============================================================================
// Brief  : 減衰率のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float LightPoint::GetAttemuationY( void ) const
{
	// 値の返却
	return attemuation_.y;
}

//==============================================================================
// Brief  : 減衰率のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float LightPoint::GetAttemuationZ( void ) const
{
	// 値の返却
	return attemuation_.z;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void LightPoint::InitializeSelf( void )
{
	// メンバ変数の初期化
	position_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	attemuation_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}
