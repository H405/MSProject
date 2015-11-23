//==============================================================================
//
// File   : DrawerLightEffect.h
// Brief  : ライト描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_LIGHT_EFFECT_H
#define MY_DRAWER_LIGHT_EFFECT_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../../framework/graphic/drawer.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Effect;
class EffectParameter;
class Polygon2D;

//******************************************************************************
// クラス定義
//******************************************************************************
class DrawerLightEffect : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_OFFET_TEXEL = 0,					// テクセルオフセット

		PARAMETER_TEXTURE_DIFFUSE,					// ディフューズテクスチャ
		PARAMETER_TEXTURE_SPECULAR,					// スペキュラテクスチャ
		PARAMETER_TEXTURE_NORMAL,					// 法線テクスチャ
		PARAMETER_TEXTURE_DEPTH,					// 深度テクスチャ
		PARAMETER_TEXTURE_DIFFUSE_RIVER,			// 川のディフューズテクスチャ
		PARAMETER_TEXTURE_SPECULAR_RIVER,			// 川のスペキュラテクスチャ
		PARAMETER_TEXTURE_NORMAL_RIVER,				// 川の法線テクスチャ
		PARAMETER_TEXTURE_DEPTH_RIVER,				// 川の深度テクスチャ

		PARAMETER_MATRIX_PROJECTION_INVERSE,		// プロジェクション変換逆行列
		PARAMETER_MATRIX_VIEW_INVERSE,				// ビュー変換逆行列
		PARAMETER_POSITION_EYE,						// 視点座標
		PARAMETER_CLIP_CAMERA,						// カメラのクリップ値
		PARAMETER_COLOR_AMBIENT,					// 環境光色
		PARAMETER_VECTOR_LIGHT_DIRECTION,			// ディレクショナルライトのベクトル
		PARAMETER_COLOR_LIGHT_DIRECTION,			// ディレクショナルライトの色
		PARAMETER_POSITION_LIGHT_POINT,				// ポイントライトの座標
		PARAMETER_COLOR_LIGHT_POINT,				// ポイントライトの色
		PARAMETER_ATTENUATION_LIGHT_POINT,			// ポイントライトの減衰率

		PARAMETER_MAX								// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerLightEffect( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerLightEffect( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDiffuseRiver		: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecularRiver	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormalRiver		: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepthRiver		: 深度情報テクスチャ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth,
		IDirect3DTexture9* pTextureDiffuseRiver, IDirect3DTexture9* pTextureSpecularRiver, IDirect3DTexture9* pTextureNormalRiver, IDirect3DTexture9* pTextureDepthRiver );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDiffuseRiver		: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecularRiver	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormalRiver		: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepthRiver		: 深度情報テクスチャ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth,
		IDirect3DTexture9* pTextureDiffuseRiver, IDirect3DTexture9* pTextureSpecularRiver, IDirect3DTexture9* pTextureNormalRiver, IDirect3DTexture9* pTextureDepthRiver );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerLightEffect* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( DrawerLightEffect* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : const D3DXMATRIX& matrixWorld		: ワールドマトリクス
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetTextureDiffuse( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureDiffuse( void ) const;
	void SetTextureSpecular( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureSpecular( void ) const;
	void SetTextureNormal( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureNormal( void ) const;
	void SetTextureDepth( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureDepth( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;			// エフェクトパラメータ
	Effect*					pEffect_;					// エフェクト
	IDirect3DTexture9*		pTextureDiffuse_;			// ディフューズ情報テクスチャ
	IDirect3DTexture9*		pTextureSpecular_;			// スペキュラ情報テクスチャ
	IDirect3DTexture9*		pTextureNormal_;			// 法線情報テクスチャ
	IDirect3DTexture9*		pTextureDepth_;				// 深度情報テクスチャ
	IDirect3DTexture9*		pTextureDiffuseRiver_;		// ディフューズ情報テクスチャ
	IDirect3DTexture9*		pTextureSpecularRiver_;		// スペキュラ情報テクスチャ
	IDirect3DTexture9*		pTextureNormalRiver_;		// 法線情報テクスチャ
	IDirect3DTexture9*		pTextureDepthRiver_;		// 深度情報テクスチャ
	Polygon2D*				pPolygon_;					// ポリゴン

private:
	void InitializeSelf( void );
	DrawerLightEffect( const DrawerLightEffect& );
	DrawerLightEffect operator=( const DrawerLightEffect& );

};

#endif	// MY_DRAWER_LIGHT_EFFECT_H
