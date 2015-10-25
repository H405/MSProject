//==============================================================================
//
// File   : Drawer3D.h
// Brief  : 3Dポリゴン描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_3D_H
#define MY_DRAWER_3D_H

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
class Material;
class Polygon3D;

//******************************************************************************
// クラス定義
//******************************************************************************
class Drawer3D : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,			// 変換行列
		PARAMETER_MATRIX_WORLD,					// ワールドマトリクス
		PARAMETER_POSITION_EYE,					// 視点座標
		PARAMETER_COLOR_AMBIENT,				// 環境光色
		PARAMETER_VECTOR_LIGHT_DIRECTION,		// ディレクショナルライトのベクトル
		PARAMETER_COLOR_LIGHT_DIRECTION,		// ディレクショナルライトの色
		PARAMETER_POSITION_LIGHT_POINT,			// ポイントライトの座標
		PARAMETER_COLOR_LIGHT_POINT,			// ポイントライトの色
		PARAMETER_ATTENUATION_LIGHT_POINT,		// ポイントライトの減衰率
		PARAMETER_COUNT_LIGHT_POINT,			// ポイントライトの数
		PARAMETER_TEXTURE,						// テクスチャ
		PARAMETER_COLOR_SPECULAR,				// スペキュラ色
		PARAMETER_REFLECTION,					// 反射率
		PARAMETER_POWER,						// 反射の強さ
		PARAMETER_REFLACTIVE,					// 屈折率
		PARAMETER_MAX							// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Drawer3D( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Drawer3D( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon3D* pPolygon					: 3Dポリゴン
	// Arg    : Material* pMaterial					: マテリアル
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect,
		Polygon3D* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

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
	// Arg    : Polygon3D* pPolygon					: 3Dポリゴン
	// Arg    : Material* pMaterial					: マテリアル
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect,
		Polygon3D* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Drawer3D* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( Drawer3D* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : const D3DXMATRIX& matrixWorld		: ワールドマトリクス
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetTexture( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTexture( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;		// エフェクトパラメータ
	Effect*					pEffect_;				// エフェクト
	IDirect3DTexture9*		pTexture_;				// テクスチャ
	Polygon3D*				pPolygon_;				// ポリゴン
	Material*				pMaterial_;				// マテリアル

private:
	void InitializeSelf( void );
	Drawer3D( const Drawer3D& );
	Drawer3D operator=( const Drawer3D& );

};

#endif	// MY_DRAWER_3D_H
