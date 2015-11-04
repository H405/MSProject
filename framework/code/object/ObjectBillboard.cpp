//==============================================================================
//
// File   : ObjectBillboard.cpp
// Brief  : ビルボードポリゴンオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/23 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectBillboard.h"
#include "../framework/resource/Effect.h"
#include "../framework/resource/Texture.h"
#include "../graphic/graphic/GraphicBillboard.h"
#include "../system/EffectParameter.h"

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
ObjectBillboard::ObjectBillboard( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectBillboard::~ObjectBillboard( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectBillboard::Initialize( int priority )
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
int ObjectBillboard::Finalize( void )
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
int ObjectBillboard::Reinitialize( int priority )
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
// Arg    : ObjectBillboard* pOut				: コピー先アドレス
//==============================================================================
int ObjectBillboard::Copy( ObjectBillboard* pOut ) const
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
void ObjectBillboard::Update( void )
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
int ObjectBillboard::CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, Texture* pTexture )
{
	// グラフィックの生成
	int					result;				// 実行結果
	IDirect3DTexture9*	pTextureSet;		// 設定するテクスチャ
	pTextureSet = nullptr;
	if( pTexture != nullptr )
	{
		pTextureSet = pTexture->pTexture_;
	}
	pGraphic_ = new GraphicBillboard();
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

	// 拡縮の設定
	if( pTexture != nullptr )
	{
		scale_.x = static_cast< float >( pTexture->width_ );
		scale_.y = static_cast< float >( pTexture->height_ );
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画クラスの設定
// Return : void								: なし
// Arg    : GraphicBillboard* pValue						: 設定する値
//==============================================================================
void ObjectBillboard::SetGraphic( GraphicBillboard* pValue )
{
	// 値の設定
	pGraphic_ = pValue;
	Object::pGraphic_ = pValue;
}

//==============================================================================
// Brief  : 描画クラスの取得
// Return : GraphicBillboard*							: 返却する値
// Arg    : void								: なし
//==============================================================================
GraphicBillboard* ObjectBillboard::GetGraphic( void ) const
{
	// 値の返却
	return pGraphic_;
}

//==============================================================================
// Brief  : 色の設定
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void ObjectBillboard::SetColor( const D3DXCOLOR& value )
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
void ObjectBillboard::SetColor( float r, float g, float b, float a )
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
void ObjectBillboard::SetColor( float r, float g, float b )
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
void ObjectBillboard::SetColorR( float r )
{
	// 値の設定
	color_.r = r;
}

//==============================================================================
// Brief  : 色のG値の設定
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void ObjectBillboard::SetColorG( float g )
{
	// 値の設定
	color_.g = g;
}

//==============================================================================
// Brief  : 色のB値の設定
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void ObjectBillboard::SetColorB( float b )
{
	// 値の設定
	color_.b = b;
}

//==============================================================================
// Brief  : 色のA値の設定
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void ObjectBillboard::SetColorA( float a )
{
	// 値の設定
	color_.a = a;
}

//==============================================================================
// Brief  : 色のアルファ値の設定
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void ObjectBillboard::SetColorAlpha( float alpha )
{
	// 値の設定
	color_.a = alpha;
}

//==============================================================================
// Brief  : 色の取得
// Return : void								: なし
// Arg    : D3DXCOLOR* pOut						: 値の格納アドレス
//==============================================================================
void ObjectBillboard::GetColor( D3DXCOLOR* pOut ) const
{
	// 値の返却
	*pOut = color_;
}

//==============================================================================
// Brief  : 色のR値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectBillboard::GetColorR( void ) const
{
	// 値の返却
	return color_.r;
}

//==============================================================================
// Brief  : 色のG値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectBillboard::GetColorG( void ) const
{
	// 値の返却
	return color_.g;
}

//==============================================================================
// Brief  : 色のB値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectBillboard::GetColorB( void ) const
{
	// 値の返却
	return color_.b;
}

//==============================================================================
// Brief  : 色のA値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectBillboard::GetColorA( void ) const
{
	// 値の返却
	return color_.a;
}

//==============================================================================
// Brief  : 色の加算
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 加算する値
//==============================================================================
void ObjectBillboard::AddColor( const D3DXCOLOR& value )
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
void ObjectBillboard::AddColor( float r, float g, float b, float a )
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
void ObjectBillboard::AddColor( float r, float g, float b )
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
void ObjectBillboard::AddColorR( float r )
{
	// 値の加算
	color_.r += r;
}

//==============================================================================
// Brief  : 色のG値の加算
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void ObjectBillboard::AddColorG( float g )
{
	// 値の加算
	color_.g += g;
}

//==============================================================================
// Brief  : 色のB値の加算
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void ObjectBillboard::AddColorB( float b )
{
	// 値の加算
	color_.b += b;
}

//==============================================================================
// Brief  : 色のA値の加算
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void ObjectBillboard::AddColorA( float a )
{
	// 値の加算
	color_.a += a;
}

//==============================================================================
// Brief  : 色のアルファ値の加算
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void ObjectBillboard::AddColorAlpha( float alpha )
{
	// 値の加算
	color_.a += alpha;
}

//==============================================================================
// Brief  : テクスチャ座標の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR2& value			: 設定する値
//==============================================================================
void ObjectBillboard::SetPositionTexture( const D3DXVECTOR2& value )
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
void ObjectBillboard::SetPositionTexture( float x, float y )
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
void ObjectBillboard::SetPositionTextureX( float x )
{
	// 値の設定
	positionTexture_.x = x;
}

//==============================================================================
// Brief  : テクスチャ座標のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectBillboard::SetPositionTextureY( float y )
{
	// 値の設定
	positionTexture_.y = y;
}

//==============================================================================
// Brief  : テクスチャ座標の取得
// Return : void								: なし
// Arg    : D3DXVECTOR2* pOut					: 値の格納アドレス
//==============================================================================
void ObjectBillboard::GetPositionTexture( D3DXVECTOR2* pOut ) const
{
	// 値の返却
	*pOut = positionTexture_;
}

//==============================================================================
// Brief  : テクスチャ座標のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectBillboard::GetPositionTextureX( void ) const
{
	// 値の返却
	return positionTexture_.x;
}

//==============================================================================
// Brief  : テクスチャ座標のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectBillboard::GetPositionTextureY( void ) const
{
	// 値の返却
	return positionTexture_.y;
}

//==============================================================================
// Brief  : テクスチャ座標の加算
// Return : void								: なし
// Arg    : const D3DXVECTOR2& value			: 加算する値
//==============================================================================
void ObjectBillboard::AddPositionTexture( const D3DXVECTOR2& value )
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
void ObjectBillboard::AddPositionTexture( float x, float y )
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
void ObjectBillboard::AddPositionTextureX( float x )
{
	// 値の加算
	positionTexture_.x += x;
}

//==============================================================================
// Brief  : テクスチャ座標のY値の加算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectBillboard::AddPositionTextureY( float y )
{
	// 値の加算
	positionTexture_.y += y;
}

//==============================================================================
// Brief  : テクスチャ拡縮の設定
// Return : void								: なし
// Arg    : const D3DXVECTOR2& value			: 設定する値
//==============================================================================
void ObjectBillboard::SetScaleTexture( const D3DXVECTOR2& value )
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
void ObjectBillboard::SetScaleTexture( float x, float y )
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
void ObjectBillboard::SetScaleTextureX( float x )
{
	// 値の設定
	scaleTexture_.x = x;
}

//==============================================================================
// Brief  : テクスチャ拡縮のY値の設定
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectBillboard::SetScaleTextureY( float y )
{
	// 値の設定
	scaleTexture_.y = y;
}

//==============================================================================
// Brief  : テクスチャ拡縮の取得
// Return : void								: なし
// Arg    : D3DXVECTOR2* pOut					: 値の格納アドレス
//==============================================================================
void ObjectBillboard::GetScaleTexture( D3DXVECTOR2* pOut ) const
{
	// 値の返却
	*pOut = scaleTexture_;
}

//==============================================================================
// Brief  : テクスチャ拡縮のX値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectBillboard::GetScaleTextureX( void ) const
{
	// 値の返却
	return scaleTexture_.x;
}

//==============================================================================
// Brief  : テクスチャ拡縮のY値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float ObjectBillboard::GetScaleTextureY( void ) const
{
	// 値の返却
	return scaleTexture_.y;
}

//==============================================================================
// Brief  : テクスチャ拡縮の加算
// Return : void								: なし
// Arg    : const D3DXVECTOR2& value			: 加算する値
//==============================================================================
void ObjectBillboard::AddScaleTexture( const D3DXVECTOR2& value )
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
void ObjectBillboard::AddScaleTexture( float x, float y )
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
void ObjectBillboard::AddScaleTextureX( float x )
{
	// 値の加算
	scaleTexture_.x += x;
}

//==============================================================================
// Brief  : テクスチャ拡縮のY値の加算
// Return : void								: なし
// Arg    : float y								: Y値
//==============================================================================
void ObjectBillboard::AddScaleTextureY( float y )
{
	// 値の加算
	scaleTexture_.y += y;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectBillboard::InitializeSelf( void )
{
	// メンバ変数の初期化
	pGraphic_ = nullptr;
	color_ = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );
	positionTexture_ = D3DXVECTOR2( 0.0f, 0.0f );
	scaleTexture_ = D3DXVECTOR2( 1.0f, 1.0f );
}
