//==============================================================================
//
// File   : DrawerMesh.h
// Brief  : メッシュポリゴン描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_MESH_H
#define MY_DRAWER_MESH_H

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
class PolygonMesh;

//******************************************************************************
// クラス定義
//******************************************************************************
class DrawerMesh : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// 変換行列
		PARAMETER_MATRIX_WORLD,				// ワールドマトリクス
		PARAMETER_VECTOR_LIGHT,				// ライトベクトル
		PARAMETER_POSITION_EYE,				// 視点座標
		PARAMETER_TEXTURE,					// テクスチャ
		PARAMETER_COLOR_AMBIENT,			// アンビエント色
		PARAMETER_COLOR_LIGHT,				// ライトの色
		PARAMETER_COLOR_DIFFUSE,			// ディフューズ色
		PARAMETER_COLOR_SPECULAR,			// スペキュラ色
		PARAMETER_REFLECTION,				// 反射率
		PARAMETER_POWER,					// 反射の強さ
		PARAMETER_REFLACTIVE,				// 屈折率
		PARAMETER_MAX						// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerMesh( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerMesh( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : PolygonMesh* pPolygon				: メッシュポリゴン
	// Arg    : Material* pMaterial					: マテリアル
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

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
	// Arg    : PolygonMesh* pPolygon				: メッシュポリゴン
	// Arg    : Material* pMaterial					: マテリアル
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonMesh* pPolygon, Material* pMaterial, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerMesh* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( DrawerMesh* pOut ) const;

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
	PolygonMesh*			pPolygon_;				// ポリゴン
	Material*				pMaterial_;				// マテリアル

private:
	void InitializeSelf( void );
	DrawerMesh( const DrawerMesh& );
	DrawerMesh operator=( const DrawerMesh& );
};

#endif	// MY_DRAWER_MESH_H
