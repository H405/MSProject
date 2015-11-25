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
		
		PARAMETER_MATRIX_TRANSFORM_LIGHT,			// ライトの変換行列
		PARAMETER_MATRIX_VIEW_LIGHT,				// ライトのビュー変換行列
		PARAMETER_TEXTURE_DEPTH_LIGHT,				// ライトの深度テクスチャ

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
	// Arg    : IDirect3DTexture9* pTextureLight	: ライトの深度情報テクスチャ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLight );

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
	// Arg    : IDirect3DTexture9* pTextureLight	: ライトの深度情報テクスチャ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLight );

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
	const EffectParameter*	pEffectParameter_;		// エフェクトパラメータ
	Effect*					pEffect_;				// エフェクト
	IDirect3DTexture9*		pTextureDepth_;			// 深度情報テクスチャ
	IDirect3DTexture9*		pTextureLight_;			// ライトの深度情報テクスチャ
	Polygon2D*				pPolygon_;				// ポリゴン

private:
	void InitializeSelf( void );
	DrawerShadow( const DrawerShadow& );
	DrawerShadow operator=( const DrawerShadow& );

};

#endif	// MY_DRAWER_SHADOW_H
