//==============================================================================
//
// File   : DrawerMerge.h
// Brief  : 総合3D描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_MERGE_H
#define MY_DRAWER_MERGE_H

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
class DrawerMerge : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,			// ワールド変換行列
		PARAMETER_SIZE_SCREEN_HALF,			// 画面サイズの半分

		PARAMETER_FORCUS,					// 焦点距離

		PARAMETER_TEXTURE_LIGHT,			// ライトありテクスチャ
		PARAMETER_TEXTURE_NOT_LIGHT,		// ライトなしテクスチャ
		PARAMETER_TEXTURE_MASK,				// マスクテクスチャ
		PARAMETER_TEXTURE_ADD,				// 加算合成テクスチャ
		PARAMETER_TEXTURE_DEPTH,			// 深度テクスチャ

		PARAMETER_MAX						// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerMerge( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerMerge( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
	// Arg    : IDirect3DTexture9* pTextureLight	: ライトありテクスチャ
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ライトなしテクスチャ
	// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
	// Arg    : IDirect3DTexture9* pTextureAdd		: 加算合成テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask,
		IDirect3DTexture9* pTextureAdd, IDirect3DTexture9* pTextureDepth );

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
	// Arg    : IDirect3DTexture9* pTextureLight	: ライトありテクスチャ
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ライトなしテクスチャ
	// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
	// Arg    : IDirect3DTexture9* pTextureAdd		: 加算合成テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask,
		IDirect3DTexture9* pTextureAdd, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerMerge* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( DrawerMerge* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : const D3DXMATRIX& matrixWorld		: ワールドマトリクス
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetTextureLight( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureLight( void ) const;
	void SetTextureNotLight( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureNotLight( void ) const;
	void SetTextureMask( IDirect3DTexture9* pValue );
	IDirect3DTexture9* GetTextureMask( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;			// エフェクトパラメータ
	Effect*					pEffect_;					// エフェクト
	IDirect3DTexture9*		pTextureLight_;				// ライトありテクスチャ
	IDirect3DTexture9*		pTextureNotLight_;			// ライトなしテクスチャ
	IDirect3DTexture9*		pTextureMask_;				// マスクテクスチャ
	IDirect3DTexture9*		pTextureAdd_;				// 加算合成テクスチャ
	IDirect3DTexture9*		pTextureDepth_;				// 深度テクスチャ
	Polygon2D*				pPolygon_;					// ポリゴン

private:
	void InitializeSelf( void );
	DrawerMerge( const DrawerMerge& );
	DrawerMerge operator=( const DrawerMerge& );
};

#endif	// MY_DRAWER_MERGE_H
