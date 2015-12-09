//==============================================================================
//
// File   : EffectParameter.cpp
// Brief  : エフェクトファイル用のパラメータクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/15 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "EffectParameter.h"
#include "../framework/camera/Camera.h"
#include "../framework/light/LightDirection.h"
#include "../framework/light/LightPoint.h"
#include "../graphic/graphic/GraphicMain.h"

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
EffectParameter::EffectParameter( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
EffectParameter::~EffectParameter( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int maximumLightDirection			: ディレクショナルライト最大数
// Arg    : int maximumLightPoint				: ポイントライト最大数
// Arg    : int maximumCamera					: カメラ最大数
//==============================================================================
int EffectParameter::Initialize( int maximumLightDirection, int maximumLightPoint, int maximumCamera )
{
	// メンバ変数の設定
	maximumLightDirection_ = maximumLightDirection;
	maximumLightPoint_ = maximumLightPoint;
	maximumCamera_ = maximumCamera;

	// 格納領域の確保
	if( maximumLightDirection > 0 )
	{
		ppLightDirection_ = new const LightDirection*[ maximumLightDirection ];
		if( ppLightDirection_ == nullptr )
		{
			return 1;
		}
		for( int counterLight = 0; counterLight < maximumLightDirection; ++counterLight )
		{
			ppLightDirection_[ counterLight ] = nullptr;
		}
	}
	if( maximumLightPoint > 0 )
	{
		ppLightPoint_ = new const LightPoint*[ maximumLightPoint ];
		if( ppLightPoint_ == nullptr )
		{
			return 1;
		}
		for( int counterLight = 0; counterLight < maximumLightPoint; ++counterLight )
		{
			ppLightPoint_[ counterLight ] = nullptr;
		}
	}
	if( maximumCamera > 0 )
	{
		ppCamera_ = new const Camera*[ maximumCamera ];
		if( ppCamera_ == nullptr )
		{
			return 1;
		}
		for( int counterLight = 0; counterLight < maximumCamera; ++counterLight )
		{
			ppCamera_[ counterLight ] = nullptr;
		}
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int EffectParameter::Finalize( void )
{
	// 格納領域の開放
	delete[] ppLightDirection_;
	ppLightDirection_ = nullptr;

	delete[] ppLightPoint_;
	ppLightPoint_ = nullptr;

	delete[] ppCamera_;
	ppCamera_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int maximumLightDirection			: ディレクショナルライト最大数
// Arg    : int maximumLightPoint				: ポイントライト最大数
// Arg    : int maximumCamera					: カメラ最大数
//==============================================================================
int EffectParameter::Reinitialize( int maximumLightDirection, int maximumLightPoint, int maximumCamera )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( maximumLightDirection, maximumLightPoint, maximumCamera );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : EffectParameter* pOut				: コピー先アドレス
//==============================================================================
int EffectParameter::Copy( EffectParameter* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 明るい点光源の取得
// Return : const LightPoint*					: 点光源
// Arg    : int index							: 何番目に明るい点光源か
//==============================================================================
const LightPoint* EffectParameter::GetLightPointLightness( int index ) const
{
	// 明るい点光源の検索
	int		countOrder;													// 候補ライト数
	int		pIndexLight[ GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW ];		// ライト番号
	float	pLightness[ GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW ];		// 明るさ
	countOrder = 0;
	for( int counterOrder = 0; counterOrder < GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW; ++counterOrder )
	{
		pIndexLight[ counterOrder ] = -1;
		pLightness[ counterOrder ] = 0.0f;
	}
	for( int counterLight = 0; counterLight < countLightPoint_; ++counterLight )
	{
		// 影を落とさない場合は次へ
		if( !ppLightPoint_[ counterLight ]->IsEnable() || !ppLightPoint_[ counterLight ]->CastsShadow() )
		{
			continue;
		}

		// 明るさを計算
		float		lightness;					// 明るさ
		float		distanceBaseToLight;		// 基準からライトへの距離
		D3DXCOLOR	color;						// 色
		D3DXVECTOR3	attenuation;				// 減衰率
		D3DXVECTOR3	positionLight;				// ライトの座標
		D3DXVECTOR3	vectorBaseToLight;			// 基準からライトへのベクトル
		ppLightPoint_[ counterLight ]->GetPosition( &positionLight );
		ppLightPoint_[ counterLight ]->GetDiffuse( &color );
		ppLightPoint_[ counterLight ]->GetAttenuation( &attenuation );
		vectorBaseToLight = positionBaseLight_ - positionLight;
		distanceBaseToLight = D3DXVec3Length( &vectorBaseToLight );
		lightness = color.r + color.g + color.b;
		lightness /= attenuation.x + distanceBaseToLight * attenuation.y + distanceBaseToLight * distanceBaseToLight * attenuation.z;

		// 順番の入れ替え
		int		indexOrder;		// 候補番号
		indexOrder = 0;
		for( int counterOrder = 0; counterOrder < countOrder; ++counterOrder )
		{
			if( lightness >= pLightness[ counterOrder ] )
			{
				indexOrder = counterOrder;
				break;
			}
		}
		for( int counterOrder = GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW - 1; counterOrder > 0; --counterOrder )
		{
			pIndexLight[ counterOrder ] = pIndexLight[ counterOrder - 1 ];
			pLightness[ counterOrder ] = pLightness[ counterOrder - 1 ];
		}
		pIndexLight[ indexOrder ] = counterLight;
		pLightness[ indexOrder ] = lightness;
		++countOrder;
		if( countOrder > GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW )
		{
			countOrder = GraphicMain::MAXIMUM_LIGHT_POINT_SHADOW;
		}
	}

	// ライトを返す
	if( pIndexLight[ index ] >= 0 )
	{
		return ppLightPoint_[ pIndexLight[ index ] ];
	}
	return nullptr;
}

//==============================================================================
// Brief  : ディレクショナルライト数の設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void EffectParameter::SetCountLightDirection( int value )
{
	// 値の設定
	countLightDirection_ = value;
}

//==============================================================================
// Brief  : ディレクショナルライト数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int EffectParameter::GetCountLightDirection( void ) const
{
	// 値の返却
	return countLightDirection_;
}

//==============================================================================
// Brief  : ディレクショナルライトの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const LightDirection* pValue		: 設定する値
//==============================================================================
void EffectParameter::SetLightDirection( int index, const LightDirection* pValue )
{
	// 値の設定
	ppLightDirection_[ index ] = pValue;
}

//==============================================================================
// Brief  : ディレクショナルライトの取得
// Return : const LightDirection*				: 取得する値
// Arg    : int index							: 設定する番号
//==============================================================================
const LightDirection* EffectParameter::GetLightDirection( int index ) const
{
	// 値の返却
	return ppLightDirection_[ index ];
}

//==============================================================================
// Brief  : ポイントライト数の設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void EffectParameter::SetCountLightPoint( int value )
{
	// 値の設定
	countLightPoint_ = value;
}

//==============================================================================
// Brief  : ポイントライト数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int EffectParameter::GetCountLightPoint( void ) const
{
	// 値の返却
	return countLightPoint_;
}

//==============================================================================
// Brief  : ポイントライトの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const LightPoint& value				: 設定する値
//==============================================================================
void EffectParameter::SetLightPoint( int index, const LightPoint* pValue )
{
	// 値の設定
	ppLightPoint_[ index ] = pValue;
}

//==============================================================================
// Brief  : ポイントライトの取得
// Return : const LightPoint*					: 取得する値
// Arg    : int index							: 設定する番号
//==============================================================================
const LightPoint* EffectParameter::GetLightPoint( int index ) const
{
	// 値の返却
	return ppLightPoint_[ index ];
}

//==============================================================================
// Brief  : カメラ数の設定
// Return : void								: なし
// Arg    : int value							: 設定する値
//==============================================================================
void EffectParameter::SetCountCamera( int value )
{
	// 値の設定
	countCamera_ = value;
}

//==============================================================================
// Brief  : カメラ数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int EffectParameter::GetCountCamera( void ) const
{
	// 値の返却
	return countCamera_;
}

//==============================================================================
// Brief  : カメラの設定
// Return : void								: なし
// Arg    : int index							: 設定する番号
// Arg    : const Camera& value					: 設定する値
//==============================================================================
void EffectParameter::SetCamera( int index, const Camera* pValue )
{
	// 値の設定
	ppCamera_[ index ] = pValue;
}

//==============================================================================
// Brief  : カメラの取得
// Return : const Camera*						: 取得する値
// Arg    : int index							: 設定する番号
// Arg    : Camera* pOut						: 値の格納アドレス
//==============================================================================
const Camera* EffectParameter::GetCamera( int index ) const
{
	// 値の返却
	return ppCamera_[ index ];
}

//==============================================================================
// Brief  : 環境光の設定
// Return : void								: なし
// Arg    : const D3DXCOLOR& value				: 設定する値
//==============================================================================
void EffectParameter::SetColorAmbient( const D3DXCOLOR& value )
{
	// 値の設定
	colorAmbient_ = value;
}

//==============================================================================
// Brief  : 環境光のRGBA値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
// Arg    : float a								: A値
//==============================================================================
void EffectParameter::SetColorAmbient( float r, float g, float b, float a )
{
	// 値の設定
	colorAmbient_.r = r;
	colorAmbient_.g = g;
	colorAmbient_.b = b;
	colorAmbient_.a = a;
}

//==============================================================================
// Brief  : 環境光のRGB値の設定
// Return : void								: なし
// Arg    : float r								: R値
// Arg    : float g								: G値
// Arg    : float b								: B値
//==============================================================================
void EffectParameter::SetColorAmbient( float r, float g, float b )
{
	// 値の設定
	colorAmbient_.r = r;
	colorAmbient_.g = g;
	colorAmbient_.b = b;
}

//==============================================================================
// Brief  : 環境光のR値の設定
// Return : void								: なし
// Arg    : float r								: R値
//==============================================================================
void EffectParameter::SetColorAmbientR( float r )
{
	// 値の設定
	colorAmbient_.r = r;
}

//==============================================================================
// Brief  : 環境光のG値の設定
// Return : void								: なし
// Arg    : float g								: G値
//==============================================================================
void EffectParameter::SetColorAmbientG( float g )
{
	// 値の設定
	colorAmbient_.g = g;
}

//==============================================================================
// Brief  : 環境光のB値の設定
// Return : void								: なし
// Arg    : float b								: B値
//==============================================================================
void EffectParameter::SetColorAmbientB( float b )
{
	// 値の設定
	colorAmbient_.b = b;
}

//==============================================================================
// Brief  : 環境光のA値の設定
// Return : void								: なし
// Arg    : float a								: A値
//==============================================================================
void EffectParameter::SetColorAmbientA( float a )
{
	// 値の設定
	colorAmbient_.a = a;
}

//==============================================================================
// Brief  : 環境光のアルファ値の設定
// Return : void								: なし
// Arg    : float alpha							: アルファ値
//==============================================================================
void EffectParameter::SetColorAmbientAlpha( float alpha )
{
	// 値の設定
	colorAmbient_.a = alpha;
}

//==============================================================================
// Brief  : 環境光の取得
// Return : void								: なし
// Arg    : D3DXCOLOR* pOut						: 値の格納アドレス
//==============================================================================
void EffectParameter::GetColorAmbient( D3DXCOLOR* pOut ) const
{
	// 値の返却
	*pOut = colorAmbient_;
}

//==============================================================================
// Brief  : 環境光のR値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float EffectParameter::GetColorAmbientR( void ) const
{
	// 値の返却
	return colorAmbient_.r;
}

//==============================================================================
// Brief  : 環境光のG値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float EffectParameter::GetColorAmbientG( void ) const
{
	// 値の返却
	return colorAmbient_.g;
}

//==============================================================================
// Brief  : 環境光のB値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float EffectParameter::GetColorAmbientB( void ) const
{
	// 値の返却
	return colorAmbient_.b;
}

//==============================================================================
// Brief  : 環境光のA値の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float EffectParameter::GetColorAmbientA( void ) const
{
	// 値の返却
	return colorAmbient_.a;
}

//==============================================================================
// Brief  : スクリーン幅の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void EffectParameter::SetWidthScreen( float value )
{
	// 値の設定
	widthScreen_ = value;
}

//==============================================================================
// Brief  : スクリーン幅の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float EffectParameter::GetWidthScreen( void ) const
{
	// 値の返却
	return widthScreen_;
}

//==============================================================================
// Brief  : スクリーン高さの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void EffectParameter::SetHeightScreen( float value )
{
	// 値の設定
	heightScreen_ = value;
}

//==============================================================================
// Brief  : スクリーン高さの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float EffectParameter::GetHeightScreen( void ) const
{
	// 値の返却
	return heightScreen_;
}

//==============================================================================
// Brief  : 焦点距離の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void EffectParameter::SetForcus( float value )
{
	// 値の設定
	forcus_ = value;
}

//==============================================================================
// Brief  : 焦点距離の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float EffectParameter::GetForcus( void ) const
{
	// 値の返却
	return forcus_;
}

//==============================================================================
// Brief  : 反射面の高さの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void EffectParameter::SetHeightReflect( float value )
{
	// 値の設定
	heightReflect_ = value;
}

//==============================================================================
// Brief  : 反射面の高さの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float EffectParameter::GetHeightReflect( void ) const
{
	// 値の返却
	return heightReflect_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void EffectParameter::InitializeSelf( void )
{
	// メンバ変数の初期化
	maximumLightDirection_ = 0;
	countLightDirection_ = 0;
	ppLightDirection_ = nullptr;
	maximumLightPoint_ = 0;
	countLightPoint_ = 0;
	ppLightPoint_ = nullptr;
	maximumCamera_ = 0;
	countCamera_ = 0;
	ppCamera_ = nullptr;
	colorAmbient_ = D3DXCOLOR( 0.0f, 0.0f, 0.0f, 1.0f );
	widthScreen_ = 0.0f;
	heightScreen_ = 0.0f;
	forcus_ = 0.0f;
	heightReflect_ = 0.0f;
	positionBaseLight_ = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
}
