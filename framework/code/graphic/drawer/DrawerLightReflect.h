//==============================================================================
//
// File   : DrawerLightReflect.h
// Brief  : 反射ライト描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/22 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_LIGHT_REFLECT_H
#define MY_DRAWER_LIGHT_REFLECT_H

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
class DrawerLightReflect : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_OFFSET_TEXEL = 0,					// テクセルオフセット

		PARAMETER_TEXTURE_DIFFUSE,					// ディフューズテクスチャ
		PARAMETER_TEXTURE_SPECULAR,					// スペキュラテクスチャ
		PARAMETER_TEXTURE_NORMAL,					// 法線テクスチャ
		PARAMETER_TEXTURE_DEPTH,					// 深度テクスチャ

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
	DrawerLightReflect( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerLightReflect( void );

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
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth );

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
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerLightReflect* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( DrawerLightReflect* pOut ) const;

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
	const EffectParameter*	pEffectParameter_;		// エフェクトパラメータ
	Effect*					pEffect_;				// エフェクト
	IDirect3DTexture9*		pTextureDiffuse_;		// ディフューズ情報テクスチャ
	IDirect3DTexture9*		pTextureSpecular_;		// スペキュラ情報テクスチャ
	IDirect3DTexture9*		pTextureNormal_;		// 法線情報テクスチャ
	IDirect3DTexture9*		pTextureDepth_;			// 深度情報テクスチャ
	Polygon2D*				pPolygon_;				// ポリゴン

private:
	void InitializeSelf( void );
	DrawerLightReflect( const DrawerLightReflect& );
	DrawerLightReflect operator=( const DrawerLightReflect& );

};

#endif	// MY_DRAWER_LIGHT_REFLECT_H
