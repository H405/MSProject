//==============================================================================
//
// File   : Object2D.cpp
// Brief  : 2Dポリゴンオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Object2D.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/Graphic2D.h"

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
Object2D::Object2D( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Object2D::~Object2D( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int Object2D::Initialize( int priority )
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
int Object2D::Finalize( void )
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
int Object2D::Reinitialize( int priority )
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
// Arg    : Object2D* pOut						: コピー先アドレス
//==============================================================================
int Object2D::Copy( Object2D* pOut ) const
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
void Object2D::Update( void )
{
	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 描画クラスの生成
// Return : int									: 実行結果
// Arg    : int priority						: 描画優先度
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Texture* pTexture					: テクスチャ
//==============================================================================
int Object2D::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// グラフィックの生成
	int					result;				// 実行結果
	IDirect3DTexture9*	pTextureSet;		// 設定するテクスチャ
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new Graphic2D();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( priority, pParameter, pEffectGeneral, &color_, &positionTexture_, &scaleTexture_, pTextureSet );
	if( result != 0 )
	{
		return result;
	}
	Object::pGraphic_ = pGraphic_;

	// サイズの設定
	if( pTexture != nullptr )
	{
		width_ = static_cast< float >( pTexture->width_ );
		height_ = static_cast< float >( pTexture->height_ );
		scale_.x = width_;
		scale_.y = height_;
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : Graphic2D* pValue						: 設定する値
//==============================================================================
void Object2D::SetGraphic( Graphic2D* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : Graphic2D*							: 返却する値
// Arg    : void								: なし
//==============================================================================
Graphic2D* Object2D::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : 幅の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Object2D::SetWidth( float value )
{
	// 値の設定
	width_ = value;
}

//==============================================================================
// Brief  : 幅の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetWidth( void ) const
{
	// 値の返却
	return width_;
}

//==============================================================================
// Brief  : 高さの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void Object2D::SetHeight( float value )
{
	// 値の設定
	height_ = value;
}

//==============================================================================
// Brief  : 高さの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetHeight( void ) const
{
	// 値の返却
	return height_;
}

//==============================================================================
// Brief  : 色の設定
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void Object2D::SetColor( const D3DXCOLOR& value )
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
void Object2D::SetColor( float r, float g, float b, float a )
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
void Object2D::SetColor( float r, float g, float b )
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
void Object2D::SetColorR( float r )
{
	// 値の設定
	color_.r = r;
}

//==============================================================================
// Brief  : 色のG値の設定
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void Object2D::SetColorG( float g )
{
	// 値の設定
	color_.g = g;
}

//==============================================================================
// Brief  : 色のB値の設定
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void Object2D::SetColorB( float b )
{
	// 値の設定
	color_.b = b;
}

//==============================================================================
// Brief  : 色のA値の設定
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void Object2D::SetColorA( float a )
{
	// 値の設定
	color_.a = a;
}

//==============================================================================
// Brief  : 色のアルファ値の設定
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void Object2D::SetColorAlpha( float alpha )
{
	// 値の設定
	color_.a = alpha;
}

//==============================================================================
// Brief  : 色の取得
// Return : void								: なし
// Arg    : D3DXCOLOR* pOut						: 値の格納アドレス
//==============================================================================
void Object2D::GetColor( D3DXCOLOR* pOut ) const
{
	// 値の返却
	*pOut = color_;
}

//==============================================================================
// Brief  : 色のR値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetColorR( void ) const
{
	// 値の返却
	return color_.r;
}

//==============================================================================
// Brief  : 色のG値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetColorG( void ) const
{
	// 値の返却
	return color_.g;
}

//==============================================================================
// Brief  : 色のB値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetColorB( void ) const
{
	// 値の返却
	return color_.b;
}

//==============================================================================
// Brief  : 色のA値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetColorA( void ) const
{
	// 値の返却
	return color_.a;
}

//==============================================================================
// Brief  : 色の加算
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 加算する値
//==============================================================================
void Object2D::AddColor( const D3DXCOLOR& value )
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
void Object2D::AddColor( float r, float g, float b, float a )
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
void Object2D::AddColor( float r, float g, float b )
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
void Object2D::AddColorR( float r )
{
	// 値の加算
	color_.r += r;
}

//==============================================================================
// Brief  : 色のG値の加算
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void Object2D::AddColorG( float g )
{
	// 値の加算
	color_.g += g;
}

//==============================================================================
// Brief  : 色のB値の加算
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void Object2D::AddColorB( float b )
{
	// 値の加算
	color_.b += b;
}

//==============================================================================
// Brief  : 色のA値の加算
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void Object2D::AddColorA( float a )
{
	// 値の加算
	color_.a += a;
}

//==============================================================================
// Brief  : 色のアルファ値の加算
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void Object2D::AddColorAlpha( float alpha )
{
	// 値の加算
	color_.a += alpha;
}

//==============================================================================
// Brief  : テクスチャ座標の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR2& value			: 設定する値
//==============================================================================
void Object2D::SetPositionTexture( const D3DXVECTOR2& value )
{
	// 値の設定
	positionTexture_ = value;
}

//==============================================================================
// Brief  : テクスチャ座標の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
//==============================================================================
void Object2D::SetPositionTexture( float x, float y )
{
	// 値の設定
	positionTexture_.x = x;
	positionTexture_.y = y;
}

//==============================================================================
// Brief  : テクスチャ座標のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void Object2D::SetPositionTextureX( float x )
{
	// 値の設定
	positionTexture_.x = x;
}

//==============================================================================
// Brief  : テクスチャ座標のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Object2D::SetPositionTextureY( float y )
{
	// 値の設定
	positionTexture_.y = y;
}

//==============================================================================
// Brief  : テクスチャ座標の取得
// Return : void								: なし
// Arg    : D3DXVECTOR2* pOut					: 値の格納アドレス
//==============================================================================
void Object2D::GetPositionTexture( D3DXVECTOR2* pOut ) const
{
	// 値の返却
	*pOut = positionTexture_;
}

//==============================================================================
// Brief  : テクスチャ座標のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetPositionTextureX( void ) const
{
	// 値の返却
	return positionTexture_.x;
}

//==============================================================================
// Brief  : テクスチャ座標のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetPositionTextureY( void ) const
{
	// 値の返却
	return positionTexture_.y;
}

//==============================================================================
// Brief  : テクスチャ座標の加算
// Return : void								: なし
// Arg    : const D3DXVECTOR2& value			: 加算する値
//==============================================================================
void Object2D::AddPositionTexture( const D3DXVECTOR2& value )
{
	// 値の加算
	positionTexture_ += value;
}

//==============================================================================
// Brief  : テクスチャ座標の加算
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
//==============================================================================
void Object2D::AddPositionTexture( float x, float y )
{
	// 値の加算
	positionTexture_.x += x;
	positionTexture_.y += y;
}

//==============================================================================
// Brief  : テクスチャ座標のX値の加算
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void Object2D::AddPositionTextureX( float x )
{
	// 値の加算
	positionTexture_.x += x;
}

//==============================================================================
// Brief  : テクスチャ座標のY値の加算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Object2D::AddPositionTextureY( float y )
{
	// 値の加算
	positionTexture_.y += y;
}

//==============================================================================
// Brief  : テクスチャ拡縮の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR2& value			: 設定する値
//==============================================================================
void Object2D::SetScaleTexture( const D3DXVECTOR2& value )
{
	// 値の設定
	scaleTexture_ = value;
}

//==============================================================================
// Brief  : テクスチャ拡縮の設定
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
//==============================================================================
void Object2D::SetScaleTexture( float x, float y )
{
	// 値の設定
	scaleTexture_.x = x;
	scaleTexture_.y = y;
}

//==============================================================================
// Brief  : テクスチャ拡縮のX値の設定
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void Object2D::SetScaleTextureX( float x )
{
	// 値の設定
	scaleTexture_.x = x;
}

//==============================================================================
// Brief  : テクスチャ拡縮のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Object2D::SetScaleTextureY( float y )
{
	// 値の設定
	scaleTexture_.y = y;
}

//==============================================================================
// Brief  : テクスチャ拡縮の取得
// Return : void								: なし
// Arg    : D3DXVECTOR2* pOut					: 値の格納アドレス
//==============================================================================
void Object2D::GetScaleTexture( D3DXVECTOR2* pOut ) const
{
	// 値の返却
	*pOut = scaleTexture_;
}

//==============================================================================
// Brief  : テクスチャ拡縮のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetScaleTextureX( void ) const
{
	// 値の返却
	return scaleTexture_.x;
}

//==============================================================================
// Brief  : テクスチャ拡縮のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float Object2D::GetScaleTextureY( void ) const
{
	// 値の返却
	return scaleTexture_.y;
}

//==============================================================================
// Brief  : テクスチャ拡縮の加算
// Return : void								: なし
// Arg    : const D3DXVECTOR2& value			: 加算する値
//==============================================================================
void Object2D::AddScaleTexture( const D3DXVECTOR2& value )
{
	// 値の加算
	scaleTexture_ += value;
}

//==============================================================================
// Brief  : テクスチャ拡縮の加算
// Return : void								: なし
// Arg    : float x								: X値
// Arg    : float y								: Y値
//==============================================================================
void Object2D::AddScaleTexture( float x, float y )
{
	// 値の加算
	scaleTexture_.x += x;
	scaleTexture_.y += y;
}

//==============================================================================
// Brief  : テクスチャ拡縮のX値の加算
// Return : void								: なし
// Arg    : float x								: X値
//==============================================================================
void Object2D::AddScaleTextureX( float x )
{
	// 値の加算
	scaleTexture_.x += x;
}

//==============================================================================
// Brief  : テクスチャ拡縮のY値の加算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void Object2D::AddScaleTextureY( float y )
{
	// 値の加算
	scaleTexture_.y += y;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Object2D::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
	width_ = 0.0f;
	height_ = 0.0f;
	color_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	positionTexture_ = D3DXVECTOR2( 0.0f, 0.0f );
	scaleTexture_ = D3DXVECTOR2( 1.0f, 1.0f );
}
