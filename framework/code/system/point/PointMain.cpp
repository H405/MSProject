//==============================================================================
//
// File   : PointMain.cpp
// Brief  : ポイントスプライトの一点
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "PointMain.h"
#include "../../framework/develop/Debug.h"

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
PointMain::PointMain( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
PointMain::~PointMain( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int PointMain::Initialize( void )
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int PointMain::Finalize( void )
{
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
int PointMain::Reinitialize( void )
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
// Arg    : PointMain* pOut							: コピー先アドレス
//==============================================================================
int PointMain::Copy( PointMain* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PointMain::Update( void )
{
	// ステートの更新
	Assert( pFunctionState != nullptr, _T( "ポイントステートが設定されていません。" ) );
	if( pFunctionState != nullptr )
	{
		(this->*pFunctionState)();
	}

	// 時間の経過
	++time_;
}

//==============================================================================
// Brief  : 設定
// Return : void								: なし
// Arg    : int indexState						: ステート番号
// Arg    : const D3DXVECTOR3& position			: 座標
// Arg    : const D3DXCOLOR& color				: 色
// Arg    : float size							: 大きさ
//==============================================================================
void PointMain::Set( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size )
{
	// メンバ変数の設定
	position_ = position;
	size_ = size;
	color_ = color;

	// ステートの設定
	SetState( indexState );
	time_ = 0;

	// 使用フラグON
	isEnable_ = true;
}

//==============================================================================
// Brief  : 設定
// Return : void								: なし
// Arg    : int timeExist						: 残存時間
// Arg    : const D3DXVECTOR3& position			: 座標
// Arg    : const D3DXCOLOR& color				: 色
// Arg    : float size							: 大きさ
// Arg    : const D3DXVECTOR3& differencePosition	: 座標の変化量
// Arg    : const D3DXCOLOR& differenceColor	: 色の変化量
// Arg    : float differenceSize				: 大きさの変化量
// Arg    : int indexState						: ステート番号
//==============================================================================
void PointMain::Set( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size,
	const D3DXVECTOR3& differencePosition, const D3DXCOLOR& differenceColor, float differenceSize, int indexState )
{
	// メンバ変数の設定
	timeExist_ = timeExist;
	position_ = position;
	size_ = size;
	color_ = color;
	differencePosition_ = differencePosition;
	differenceColor_ = differenceColor;
	differenceSize_ = differenceSize;

	// ステートの設定
	SetState( indexState );
	time_ = 0;

	// 使用フラグON
	isEnable_ = true;
}

//==============================================================================
// Brief  : 経過時間の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PointMain::GetTime( void ) const
{
	// 値の返却
	return time_;
}

//==============================================================================
// Brief  : 残存時間の設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void PointMain::SetTimeExist( int value )
{
	// 値の設定
	timeExist_ = value;
}

//==============================================================================
// Brief  : 残存時間の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PointMain::GetTimeExist( void ) const
{
	// 値の返却
	return timeExist_;
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void PointMain::SetPosition( const D3DXVECTOR3& value )
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
void PointMain::SetPosition( float x, float y, float z )
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
void PointMain::SetPositionX( float x )
{
	// 値の設定
	position_.x = x;
}

//==============================================================================
// Brief  : 座標のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void PointMain::SetPositionY( float y )
{
	// 値の設定
	position_.y = y;
}

//==============================================================================
// Brief  : 座標のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void PointMain::SetPositionZ( float z )
{
	// 値の設定
	position_.z = z;
}

//==============================================================================
// Brief  : 座標の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void PointMain::GetPosition( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = position_;
}

//==============================================================================
// Brief  : 座標のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetPositionX( void ) const
{
	// 値の返却
	return position_.x;
}

//==============================================================================
// Brief  : 座標のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetPositionY( void ) const
{
	// 値の返却
	return position_.y;
}

//==============================================================================
// Brief  : 座標のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetPositionZ( void ) const
{
	// 値の返却
	return position_.z;
}

//==============================================================================
// Brief  : 座標の加算
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 加算する値
//==============================================================================
void PointMain::AddPosition( const D3DXVECTOR3& value )
{
	// 値の加算
	position_ += value;
}

//==============================================================================
// Brief  : 座標の加算
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void PointMain::AddPosition( float x, float y, float z )
{
	// 値の加算
	position_.x += x;
	position_.y += y;
	position_.z += z;
}

//==============================================================================
// Brief  : 座標のX値の加算
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void PointMain::AddPositionX( float x )
{
	// 値の加算
	position_.x += x;
}

//==============================================================================
// Brief  : 座標のY値の加算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void PointMain::AddPositionY( float y )
{
	// 値の加算
	position_.y += y;
}

//==============================================================================
// Brief  : 座標のZ値の加算
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void PointMain::AddPositionZ( float z )
{
	// 値の加算
	position_.z += z;
}

//==============================================================================
// Brief  : 座標の乗算
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 乗算する値
//==============================================================================
void PointMain::MultiplyPosition( const D3DXVECTOR3& value )
{
	// 値の乗算
	position_.x *= value.x;
	position_.y *= value.y;
	position_.z *= value.z;
}

//==============================================================================
// Brief  : 座標の乗算
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void PointMain::MultiplyPosition( float x, float y, float z )
{
	// 値の乗算
	position_.x *= x;
	position_.y *= y;
	position_.z *= z;
}

//==============================================================================
// Brief  : 座標のX値の乗算
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void PointMain::MultiplyPositionX( float x )
{
	// 値の乗算
	position_.x *= x;
}

//==============================================================================
// Brief  : 座標のY値の乗算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void PointMain::MultiplyPositionY( float y )
{
	// 値の乗算
	position_.y *= y;
}

//==============================================================================
// Brief  : 座標のZ値の乗算
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void PointMain::MultiplyPositionZ( float z )
{
	// 値の乗算
	position_.z *= z;
}

//==============================================================================
// Brief  : サイズの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void PointMain::SetSize( float value )
{
	// 値の設定
	size_ = value;
}

//==============================================================================
// Brief  : サイズの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetSize( void ) const
{
	// 値の設定
	return size_;
}

//==============================================================================
// Brief  : サイズの加算
// Return : void								: なし
// Arg    : float value							: 加算する値
//==============================================================================
void PointMain::AddSize( float value )
{
	// 値の加算
	size_ += value;
}

//==============================================================================
// Brief  : サイズの乗算
// Return : void								: なし
// Arg    : float value							: 乗算する値
//==============================================================================
void PointMain::MultiplySize( float value )
{
	// 値の乗算
	size_ *= value;
}

//==============================================================================
// Brief  : 色の設定
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void PointMain::SetColor( const D3DXCOLOR& value )
{
	// 値の設定
	color_ = value;
}

//==============================================================================
// Brief  : 色のRGBA値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void PointMain::SetColor( float r, float g, float b, float a )
{
	// 値の設定
	color_.r = r;
	color_.g = g;
	color_.b = b;
	color_.a = a;
}

//==============================================================================
// Brief  : 色のRGB値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
//==============================================================================
void PointMain::SetColor( float r, float g, float b )
{
	// 値の設定
	color_.r = r;
	color_.g = g;
	color_.b = b;
}

//==============================================================================
// Brief  : 色のR値の設定
// Return : void								: なし
// Arg    : float r								: R値
//==============================================================================
void PointMain::SetColorR( float r )
{
	// 値の設定
	color_.r = r;
}

//==============================================================================
// Brief  : 色のG値の設定
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void PointMain::SetColorG( float g )
{
	// 値の設定
	color_.g = g;
}

//==============================================================================
// Brief  : 色のB値の設定
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void PointMain::SetColorB( float b )
{
	// 値の設定
	color_.b = b;
}

//==============================================================================
// Brief  : 色のA値の設定
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void PointMain::SetColorA( float a )
{
	// 値の設定
	color_.a = a;
}

//==============================================================================
// Brief  : 色のアルファ値の設定
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void PointMain::SetColorAlpha( float alpha )
{
	// 値の設定
	color_.a = alpha;
}

//==============================================================================
// Brief  : 色の取得
// Return : void								: なし
// Arg    : D3DXCOLOR* pOut						: 値の格納アドレス
//==============================================================================
void PointMain::GetColor( D3DXCOLOR* pOut ) const
{
	// 値の返却
	*pOut = color_;
}

//==============================================================================
// Brief  : 色のR値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetColorR( void ) const
{
	// 値の返却
	return color_.r;
}

//==============================================================================
// Brief  : 色のG値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetColorG( void ) const
{
	// 値の返却
	return color_.g;
}

//==============================================================================
// Brief  : 色のB値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetColorB( void ) const
{
	// 値の返却
	return color_.b;
}

//==============================================================================
// Brief  : 色のA値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetColorA( void ) const
{
	// 値の返却
	return color_.a;
}

//==============================================================================
// Brief  : 色の加算
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 加算する値
//==============================================================================
void PointMain::AddColor( const D3DXCOLOR& value )
{
	// 値の加算
	color_ += value;
}

//==============================================================================
// Brief  : 色のRGBA値の加算
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void PointMain::AddColor( float r, float g, float b, float a )
{
	// 値の加算
	color_.r += r;
	color_.g += g;
	color_.b += b;
	color_.a += a;
}

//==============================================================================
// Brief  : 色のRGB値の加算
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
//==============================================================================
void PointMain::AddColor( float r, float g, float b )
{
	// 値の加算
	color_.r += r;
	color_.g += g;
	color_.b += b;
}

//==============================================================================
// Brief  : 色のR値の加算
// Return : void								: なし
// Arg    : float r								: R値
//==============================================================================
void PointMain::AddColorR( float r )
{
	// 値の加算
	color_.r += r;
}

//==============================================================================
// Brief  : 色のG値の加算
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void PointMain::AddColorG( float g )
{
	// 値の加算
	color_.g += g;
}

//==============================================================================
// Brief  : 色のB値の加算
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void PointMain::AddColorB( float b )
{
	// 値の加算
	color_.b += b;
}

//==============================================================================
// Brief  : 色のA値の加算
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void PointMain::AddColorA( float a )
{
	// 値の加算
	color_.a += a;
}

//==============================================================================
// Brief  : 色のアルファ値の加算
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void PointMain::AddColorAlpha( float alpha )
{
	// 値の加算
	color_.a += alpha;
}

//==============================================================================
// Brief  : 色の乗算
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 乗算する値
//==============================================================================
void PointMain::MultiplyColor( const D3DXCOLOR& value )
{
	// 値の乗算
	color_.r *= value.r;
	color_.g *= value.g;
	color_.b *= value.b;
	color_.a *= value.a;
}

//==============================================================================
// Brief  : 色のRGBA値の乗算
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void PointMain::MultiplyColor( float r, float g, float b, float a )
{
	// 値の乗算
	color_.r *= r;
	color_.g *= g;
	color_.b *= b;
	color_.a *= a;
}

//==============================================================================
// Brief  : 色のRGB値の乗算
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
//==============================================================================
void PointMain::MultiplyColor( float r, float g, float b )
{
	// 値の乗算
	color_.r *= r;
	color_.g *= g;
	color_.b *= b;
}

//==============================================================================
// Brief  : 色のR値の乗算
// Return : void								: なし
// Arg    : float r								: R値
//==============================================================================
void PointMain::MultiplyColorR( float r )
{
	// 値の乗算
	color_.r *= r;
}

//==============================================================================
// Brief  : 色のG値の乗算
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void PointMain::MultiplyColorG( float g )
{
	// 値の乗算
	color_.g *= g;
}

//==============================================================================
// Brief  : 色のB値の乗算
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void PointMain::MultiplyColorB( float b )
{
	// 値の乗算
	color_.b *= b;
}

//==============================================================================
// Brief  : 色のA値の乗算
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void PointMain::MultiplyColorA( float a )
{
	// 値の乗算
	color_.a *= a;
}

//==============================================================================
// Brief  : 色のアルファ値の乗算
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void PointMain::MultiplyColorAlpha( float alpha )
{
	// 値の乗算
	color_.a *= alpha;
}

//==============================================================================
// Brief  : 座標の変化量の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void PointMain::SetDifferencePosition( const D3DXVECTOR3& value )
{
	// 値の設定
	differencePosition_ = value;
}

//==============================================================================
// Brief  : 座標の変化量の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
// Arg    : float z								: Z値
//==============================================================================
void PointMain::SetDifferencePosition( float x, float y, float z )
{
	// 値の設定
	differencePosition_.x = x;
	differencePosition_.y = y;
	differencePosition_.z = z;
}

//==============================================================================
// Brief  : 座標の変化量のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void PointMain::SetDifferencePositionX( float x )
{
	// 値の設定
	differencePosition_.x = x;
}

//==============================================================================
// Brief  : 座標の変化量のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void PointMain::SetDifferencePositionY( float y )
{
	// 値の設定
	differencePosition_.y = y;
}

//==============================================================================
// Brief  : 座標の変化量のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void PointMain::SetDifferencePositionZ( float z )
{
	// 値の設定
	differencePosition_.z = z;
}

//==============================================================================
// Brief  : 座標の変化量の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void PointMain::GetDifferencePosition( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = differencePosition_;
}

//==============================================================================
// Brief  : 座標の変化量のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetDifferencePositionX( void ) const
{
	// 値の返却
	return differencePosition_.x;
}

//==============================================================================
// Brief  : 座標の変化量のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetDifferencePositionY( void ) const
{
	// 値の返却
	return differencePosition_.y;
}

//==============================================================================
// Brief  : 座標の変化量のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetDifferencePositionZ( void ) const
{
	// 値の返却
	return differencePosition_.z;
}

//==============================================================================
// Brief  : サイズの変化量の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void PointMain::SetDifferenceSize( float value )
{
	// 値の設定
	differenceSize_ = value;
}

//==============================================================================
// Brief  : サイズの変化量の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetDifferenceSize( void ) const
{
	// 値の設定
	return differenceSize_;
}

//==============================================================================
// Brief  : 色の変化量の設定
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void PointMain::SetDifferenceColor( const D3DXCOLOR& value )
{
	// 値の設定
	differenceColor_ = value;
}

//==============================================================================
// Brief  : 色の変化量のRGBA値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void PointMain::SetDifferenceColor( float r, float g, float b, float a )
{
	// 値の設定
	differenceColor_.r = r;
	differenceColor_.g = g;
	differenceColor_.b = b;
	differenceColor_.a = a;
}

//==============================================================================
// Brief  : 色の変化量のRGB値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
//==============================================================================
void PointMain::SetDifferenceColor( float r, float g, float b )
{
	// 値の設定
	differenceColor_.r = r;
	differenceColor_.g = g;
	differenceColor_.b = b;
}

//==============================================================================
// Brief  : 色の変化量のR値の設定
// Return : void								: なし
// Arg    : float r								: R値
//==============================================================================
void PointMain::SetDifferenceColorR( float r )
{
	// 値の設定
	differenceColor_.r = r;
}

//==============================================================================
// Brief  : 色の変化量のG値の設定
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void PointMain::SetDifferenceColorG( float g )
{
	// 値の設定
	differenceColor_.g = g;
}

//==============================================================================
// Brief  : 色の変化量のB値の設定
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void PointMain::SetDifferenceColorB( float b )
{
	// 値の設定
	differenceColor_.b = b;
}

//==============================================================================
// Brief  : 色の変化量のA値の設定
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void PointMain::SetDifferenceColorA( float a )
{
	// 値の設定
	differenceColor_.a = a;
}

//==============================================================================
// Brief  : 色の変化量のアルファ値の設定
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void PointMain::SetDifferenceColorAlpha( float alpha )
{
	// 値の設定
	differenceColor_.a = alpha;
}

//==============================================================================
// Brief  : 色の変化量の取得
// Return : void								: なし
// Arg    : D3DXCOLOR* pOut						: 値の格納アドレス
//==============================================================================
void PointMain::GetDifferenceColor( D3DXCOLOR* pOut ) const
{
	// 値の返却
	*pOut = differenceColor_;
}

//==============================================================================
// Brief  : 色の変化量のR値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetDifferenceColorR( void ) const
{
	// 値の返却
	return differenceColor_.r;
}

//==============================================================================
// Brief  : 色の変化量のG値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetDifferenceColorG( void ) const
{
	// 値の返却
	return differenceColor_.g;
}

//==============================================================================
// Brief  : 色の変化量のB値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetDifferenceColorB( void ) const
{
	// 値の返却
	return differenceColor_.b;
}

//==============================================================================
// Brief  : 色の変化量のA値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PointMain::GetDifferenceColorA( void ) const
{
	// 値の返却
	return differenceColor_.a;
}

//==============================================================================
// Brief  : 有効フラグの設定
// Return : void								: なし
// Arg    : bool value							: 設定する値
//==============================================================================
void PointMain::SetIsEnable( bool value )
{
	// 値の設定
	isEnable_ = value;
}

//==============================================================================
// Brief  : 有効フラグの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
bool PointMain::GetIsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : 有効フラグの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
bool PointMain::IsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PointMain::InitializeSelf( void )
{
	// メンバ変数の初期化
	pFunctionState = &PointMain::UpdateNone;
	time_ = 0;
	timeExist_ = 0;
	position_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	size_ = 0.0f;
	color_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	differencePosition_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	differenceSize_ = 0.0f;
	differenceColor_ = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 0.0f );
	isEnable_ = false;
}

//==============================================================================
// Brief  : ステートの設定
// Return : void								: なし
// Arg    : int index							: ステート番号
//==============================================================================
void PointMain::SetState( int index )
{
	// ステートの設定
	switch( index )
	{
		case STATE_NONE:		pFunctionState = &PointMain::UpdateNone;		break;
		case STATE_ADD:			pFunctionState = &PointMain::UpdateAdd;			break;
		case STATE_MULTIPLY:	pFunctionState = &PointMain::UpdateMultiply;	break;
		default:				break;
	}
}

//==============================================================================
// Brief  : 処理なし
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PointMain::UpdateNone( void )
{
	// 消滅
	if( time_ >= timeExist_ )
	{
		isEnable_ = false;
	}
}

//==============================================================================
// Brief  : 加算
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PointMain::UpdateAdd( void )
{
	// 変化量を加算
	position_ += differencePosition_;
	color_ += differenceColor_;
	size_ += differenceSize_;

	// 消滅
	if( time_ >= timeExist_ )
	{
		isEnable_ = false;
	}
}

//==============================================================================
// Brief  : 乗算
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PointMain::UpdateMultiply( void )
{
	// 変化量を加算
	position_.x *= differencePosition_.x;
	position_.y *= differencePosition_.y;
	position_.z *= differencePosition_.z;
	color_.r *= differenceColor_.r;
	color_.g *= differenceColor_.g;
	color_.b *= differenceColor_.b;
	color_.a *= differenceColor_.a;
	size_ *= differenceSize_;

	// 消滅
	if( time_ >= timeExist_ )
	{
		isEnable_ = false;
	}
}
