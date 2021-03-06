//==============================================================================
//
// File   : Point.cpp
// Brief  : ポイントスプライトの一点
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Point.h"
#include "PointState.h"
#include "../develop/Debug.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
PointState**	Point::ppState_ = nullptr;		// ステートテーブル

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Point::Point( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Point::~Point( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Point::Initialize( void )
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Point::Finalize( void )
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
int Point::Reinitialize( void )
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
// Arg    : Point* pOut							: コピー先アドレス
//==============================================================================
int Point::Copy( Point* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : ステートの設定
// Return : void								: なし
// Arg    : PointState** ppState				: ステートテーブル
//==============================================================================
void Point::SetState( PointState** ppState )
{
	// ステートテーブルの設定
	ppState_ = ppState;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Point::Update( void )
{
	// ステートの切り替え
	if( indexStateNext_ >= 0 )
	{
		indexStateCurrent_ = indexStateNext_;
		indexStateNext_ = -1;
		time_ = 0;
	}

	// ステートの更新
	Assert( ppState_ != nullptr, _T( "ポイントステートが設定されていません。" ) );
	if( ppState_[ indexStateCurrent_ ] != nullptr )
	{
		ppState_[ indexStateCurrent_ ]->Update( this );
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
void Point::Set( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size )
{
	// メンバ変数の設定
	position_ = position;
	size_ = size;
	color_ = color;

	// ステートの設定
	indexStateCurrent_ = indexState;
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
void Point::Set( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size,
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
	indexStateCurrent_ = indexState;
	time_ = 0;

	// 使用フラグON
	isEnable_ = true;
}

//==============================================================================
// Brief  : ステートの切り替え
// Return : void								: なし
// Arg    : int indexState						: ステート番号
//==============================================================================
void Point::ShiftState( int indexState )
{
	// 次のステート番号を設定
	indexStateNext_ = indexState;
}

//==============================================================================
// Brief  : 現在のステート番号の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int Point::GetIndexStateCurrent( void ) const
{
	// 値の返却
	return indexStateCurrent_;
}

//==============================================================================
// Brief  : 経過時間の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int Point::GetTime( void ) const
{
	// 値の返却
	return time_;
}

//==============================================================================
// Brief  : 残存時間の設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void Point::SetTimeExist( int value )
{
	// 値の設定
	timeExist_ = value;
}

//==============================================================================
// Brief  : 残存時間の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int Point::GetTimeExist( void ) const
{
	// 値の返却
	return timeExist_;
}

//==============================================================================
// Brief  : 座標の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void Point::SetPosition( const D3DXVECTOR3& value )
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
void Point::SetPosition( float x, float y, float z )
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
void Point::SetPositionX( float x )
{
	// 値の設定
	position_.x = x;
}

//==============================================================================
// Brief  : 座標のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Point::SetPositionY( float y )
{
	// 値の設定
	position_.y = y;
}

//==============================================================================
// Brief  : 座標のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void Point::SetPositionZ( float z )
{
	// 値の設定
	position_.z = z;
}

//==============================================================================
// Brief  : 座標の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void Point::GetPosition( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = position_;
}

//==============================================================================
// Brief  : 座標のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetPositionX( void ) const
{
	// 値の返却
	return position_.x;
}

//==============================================================================
// Brief  : 座標のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetPositionY( void ) const
{
	// 値の返却
	return position_.y;
}

//==============================================================================
// Brief  : 座標のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetPositionZ( void ) const
{
	// 値の返却
	return position_.z;
}

//==============================================================================
// Brief  : 座標の加算
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 加算する値
//==============================================================================
void Point::AddPosition( const D3DXVECTOR3& value )
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
void Point::AddPosition( float x, float y, float z )
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
void Point::AddPositionX( float x )
{
	// 値の加算
	position_.x += x;
}

//==============================================================================
// Brief  : 座標のY値の加算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Point::AddPositionY( float y )
{
	// 値の加算
	position_.y += y;
}

//==============================================================================
// Brief  : 座標のZ値の加算
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void Point::AddPositionZ( float z )
{
	// 値の加算
	position_.z += z;
}

//==============================================================================
// Brief  : 座標の乗算
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 乗算する値
//==============================================================================
void Point::MultiplyPosition( const D3DXVECTOR3& value )
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
void Point::MultiplyPosition( float x, float y, float z )
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
void Point::MultiplyPositionX( float x )
{
	// 値の乗算
	position_.x *= x;
}

//==============================================================================
// Brief  : 座標のY値の乗算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Point::MultiplyPositionY( float y )
{
	// 値の乗算
	position_.y *= y;
}

//==============================================================================
// Brief  : 座標のZ値の乗算
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void Point::MultiplyPositionZ( float z )
{
	// 値の乗算
	position_.z *= z;
}

//==============================================================================
// Brief  : サイズの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Point::SetSize( float value )
{
	// 値の設定
	size_ = value;
}

//==============================================================================
// Brief  : サイズの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetSize( void ) const
{
	// 値の設定
	return size_;
}

//==============================================================================
// Brief  : サイズの加算
// Return : void								: なし
// Arg    : float value							: 加算する値
//==============================================================================
void Point::AddSize( float value )
{
	// 値の加算
	size_ += value;
}

//==============================================================================
// Brief  : サイズの乗算
// Return : void								: なし
// Arg    : float value							: 乗算する値
//==============================================================================
void Point::MultiplySize( float value )
{
	// 値の乗算
	size_ *= value;
}

//==============================================================================
// Brief  : 色の設定
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void Point::SetColor( const D3DXCOLOR& value )
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
void Point::SetColor( float r, float g, float b, float a )
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
void Point::SetColor( float r, float g, float b )
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
void Point::SetColorR( float r )
{
	// 値の設定
	color_.r = r;
}

//==============================================================================
// Brief  : 色のG値の設定
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void Point::SetColorG( float g )
{
	// 値の設定
	color_.g = g;
}

//==============================================================================
// Brief  : 色のB値の設定
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void Point::SetColorB( float b )
{
	// 値の設定
	color_.b = b;
}

//==============================================================================
// Brief  : 色のA値の設定
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void Point::SetColorA( float a )
{
	// 値の設定
	color_.a = a;
}

//==============================================================================
// Brief  : 色のアルファ値の設定
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void Point::SetColorAlpha( float alpha )
{
	// 値の設定
	color_.a = alpha;
}

//==============================================================================
// Brief  : 色の取得
// Return : void								: なし
// Arg    : D3DXCOLOR* pOut						: 値の格納アドレス
//==============================================================================
void Point::GetColor( D3DXCOLOR* pOut ) const
{
	// 値の返却
	*pOut = color_;
}

//==============================================================================
// Brief  : 色のR値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetColorR( void ) const
{
	// 値の返却
	return color_.r;
}

//==============================================================================
// Brief  : 色のG値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetColorG( void ) const
{
	// 値の返却
	return color_.g;
}

//==============================================================================
// Brief  : 色のB値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetColorB( void ) const
{
	// 値の返却
	return color_.b;
}

//==============================================================================
// Brief  : 色のA値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetColorA( void ) const
{
	// 値の返却
	return color_.a;
}

//==============================================================================
// Brief  : 色の加算
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 加算する値
//==============================================================================
void Point::AddColor( const D3DXCOLOR& value )
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
void Point::AddColor( float r, float g, float b, float a )
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
void Point::AddColor( float r, float g, float b )
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
void Point::AddColorR( float r )
{
	// 値の加算
	color_.r += r;
}

//==============================================================================
// Brief  : 色のG値の加算
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void Point::AddColorG( float g )
{
	// 値の加算
	color_.g += g;
}

//==============================================================================
// Brief  : 色のB値の加算
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void Point::AddColorB( float b )
{
	// 値の加算
	color_.b += b;
}

//==============================================================================
// Brief  : 色のA値の加算
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void Point::AddColorA( float a )
{
	// 値の加算
	color_.a += a;
}

//==============================================================================
// Brief  : 色のアルファ値の加算
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void Point::AddColorAlpha( float alpha )
{
	// 値の加算
	color_.a += alpha;
}

//==============================================================================
// Brief  : 色の乗算
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 乗算する値
//==============================================================================
void Point::MultiplyColor( const D3DXCOLOR& value )
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
void Point::MultiplyColor( float r, float g, float b, float a )
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
void Point::MultiplyColor( float r, float g, float b )
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
void Point::MultiplyColorR( float r )
{
	// 値の乗算
	color_.r *= r;
}

//==============================================================================
// Brief  : 色のG値の乗算
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void Point::MultiplyColorG( float g )
{
	// 値の乗算
	color_.g *= g;
}

//==============================================================================
// Brief  : 色のB値の乗算
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void Point::MultiplyColorB( float b )
{
	// 値の乗算
	color_.b *= b;
}

//==============================================================================
// Brief  : 色のA値の乗算
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void Point::MultiplyColorA( float a )
{
	// 値の乗算
	color_.a *= a;
}

//==============================================================================
// Brief  : 色のアルファ値の乗算
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void Point::MultiplyColorAlpha( float alpha )
{
	// 値の乗算
	color_.a *= alpha;
}

//==============================================================================
// Brief  : 座標の変化量の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR3& value			: 設定する値
//==============================================================================
void Point::SetDifferencePosition( const D3DXVECTOR3& value )
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
void Point::SetDifferencePosition( float x, float y, float z )
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
void Point::SetDifferencePositionX( float x )
{
	// 値の設定
	differencePosition_.x = x;
}

//==============================================================================
// Brief  : 座標の変化量のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Point::SetDifferencePositionY( float y )
{
	// 値の設定
	differencePosition_.y = y;
}

//==============================================================================
// Brief  : 座標の変化量のZ値の設定
// Return : void								: なし
// Arg    : float z								: Z値
//==============================================================================
void Point::SetDifferencePositionZ( float z )
{
	// 値の設定
	differencePosition_.z = z;
}

//==============================================================================
// Brief  : 座標の変化量の取得
// Return : void								: なし
// Arg    : D3DXVECTOR3* pOut					: 値の格納アドレス
//==============================================================================
void Point::GetDifferencePosition( D3DXVECTOR3* pOut ) const
{
	// 値の返却
	*pOut = differencePosition_;
}

//==============================================================================
// Brief  : 座標の変化量のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetDifferencePositionX( void ) const
{
	// 値の返却
	return differencePosition_.x;
}

//==============================================================================
// Brief  : 座標の変化量のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetDifferencePositionY( void ) const
{
	// 値の返却
	return differencePosition_.y;
}

//==============================================================================
// Brief  : 座標の変化量のZ値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetDifferencePositionZ( void ) const
{
	// 値の返却
	return differencePosition_.z;
}

//==============================================================================
// Brief  : サイズの変化量の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Point::SetDifferenceSize( float value )
{
	// 値の設定
	differenceSize_ = value;
}

//==============================================================================
// Brief  : サイズの変化量の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetDifferenceSize( void ) const
{
	// 値の設定
	return differenceSize_;
}

//==============================================================================
// Brief  : 色の変化量の設定
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void Point::SetDifferenceColor( const D3DXCOLOR& value )
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
void Point::SetDifferenceColor( float r, float g, float b, float a )
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
void Point::SetDifferenceColor( float r, float g, float b )
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
void Point::SetDifferenceColorR( float r )
{
	// 値の設定
	differenceColor_.r = r;
}

//==============================================================================
// Brief  : 色の変化量のG値の設定
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void Point::SetDifferenceColorG( float g )
{
	// 値の設定
	differenceColor_.g = g;
}

//==============================================================================
// Brief  : 色の変化量のB値の設定
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void Point::SetDifferenceColorB( float b )
{
	// 値の設定
	differenceColor_.b = b;
}

//==============================================================================
// Brief  : 色の変化量のA値の設定
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void Point::SetDifferenceColorA( float a )
{
	// 値の設定
	differenceColor_.a = a;
}

//==============================================================================
// Brief  : 色の変化量のアルファ値の設定
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void Point::SetDifferenceColorAlpha( float alpha )
{
	// 値の設定
	differenceColor_.a = alpha;
}

//==============================================================================
// Brief  : 色の変化量の取得
// Return : void								: なし
// Arg    : D3DXCOLOR* pOut						: 値の格納アドレス
//==============================================================================
void Point::GetDifferenceColor( D3DXCOLOR* pOut ) const
{
	// 値の返却
	*pOut = differenceColor_;
}

//==============================================================================
// Brief  : 色の変化量のR値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetDifferenceColorR( void ) const
{
	// 値の返却
	return differenceColor_.r;
}

//==============================================================================
// Brief  : 色の変化量のG値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetDifferenceColorG( void ) const
{
	// 値の返却
	return differenceColor_.g;
}

//==============================================================================
// Brief  : 色の変化量のB値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetDifferenceColorB( void ) const
{
	// 値の返却
	return differenceColor_.b;
}

//==============================================================================
// Brief  : 色の変化量のA値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Point::GetDifferenceColorA( void ) const
{
	// 値の返却
	return differenceColor_.a;
}

//==============================================================================
// Brief  : 有効フラグの設定
// Return : void								: なし
// Arg    : bool value							: 設定する値
//==============================================================================
void Point::SetIsEnable( bool value )
{
	// 値の設定
	isEnable_ = value;
}

//==============================================================================
// Brief  : 有効フラグの取得
// Return : bool								: 返却する値
// Arg    : void								: なし
//==============================================================================
bool Point::GetIsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : 有効フラグの判定
// Return : bool								: 判定結果
// Arg    : void								: なし
//==============================================================================
bool Point::IsEnable( void ) const
{
	// 値の返却
	return isEnable_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Point::InitializeSelf( void )
{
	// メンバ変数の初期化
	indexStateCurrent_ = 0;
	indexStateNext_ = -1;
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
