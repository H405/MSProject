//==============================================================================
//
// File   : DrawerShadow.h
// Brief  : ライト描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_SHADOW_H
#define MY_DRAWER_SHADOW_H

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
class DrawerShadow : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_OFFET_TEXEL = 0,					// テクセルオフセット

		PARAMETER_MATRIX_PROJECTION_INVERSE,		// プロジェクション変換逆行列
		PARAMETER_MATRIX_VIEW_INVERSE,				// ビュー変換逆行列
		PARAMETER_TEXTURE_DEPTH,					// 深度テクスチャ

		PARAMETER_POSITION_LOOK_AT_LIGHT,			// 平行光源の注視点

		PARAMETER_MATRIX_TRANSFORM_LIGHT_NEAR,		// 平行光源(近)の変換行列
		PARAMETER_MATRIX_VIEW_LIGHT_NEAR,			// 平行光源(近)のビュー変換行列
		PARAMETER_TEXTURE_DEPTH_LIGHT_NEAR,			// 平行光源(近)の深度テクスチャ
		PARAMETER_CLIP_FAR_LIGHT_NEAR,				// 平行光源(近)のファークリップ面

		PARAMETER_MATRIX_TRANSFORM_LIGHT_FAR,		// 平行光源(遠)の変換行列
		PARAMETER_MATRIX_VIEW_LIGHT_FAR,			// 平行光源(遠)のビュー変換行列
		PARAMETER_TEXTURE_DEPTH_LIGHT_FAR,			// 平行光源(遠)の深度テクスチャ
		PARAMETER_CLIP_FAR_LIGHT_FAR,				// 平行光源(遠)のファークリップ面

		PARAMETER_MATRIX_VIEW_LIGHT_POINT,			// 点光源のビュー変換行列
		PARAMETER_TEXTURE_DEPTH_LIGHT_POINT,		// 点光源の深度テクスチャ
		PARAMETER_CLIP_FAR_LIGHT_POINT,				// 点光源のファークリップ面
		PARAMETER_ATTENUATION_LIGHT_POINT,			// 点光源の減衰率

		PARAMETER_MAX								// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerShadow( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerShadow( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightNear	: 平行光源(近)の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightFar		: 平行光源(遠)の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightPoint	: 点光源の深度情報テクスチャ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint );

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
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightNear	: 平行光源(近)の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightFar		: 平行光源(遠)の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightPoint	: 点光源の深度情報テクスチャ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar, IDirect3DTexture9* pTextureLightPoint );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerShadow* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( DrawerShadow* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : const D3DXMATRIX& matrixWorld		: ワールドマトリクス
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

protected:
	const EffectParameter*	pEffectParameter_;			// エフェクトパラメータ
	Effect*					pEffect_;					// エフェクト
	IDirect3DTexture9*		pTextureDepth_;				// 深度情報テクスチャ
	IDirect3DTexture9*		pTextureLightNear_;			// 平行光源(近)の深度情報テクスチャ
	IDirect3DTexture9*		pTextureLightFar_;			// 平行光源(遠)の深度情報テクスチャ
	IDirect3DTexture9*		pTextureLightPoint_;		// 点光源の深度情報テクスチャ
	Polygon2D*				pPolygon_;					// ポリゴン

private:
	void InitializeSelf( void );
	DrawerShadow( const DrawerShadow& );
	DrawerShadow operator=( const DrawerShadow& );

};

#endif	// MY_DRAWER_SHADOW_H
