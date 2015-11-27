//==============================================================================
//
// File   : DrawerDrawTexture.h
// Brief  : デバッグテクスチャ描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_DRAW_TEXTURE_H
#define MY_DRAWER_DRAW_TEXTURE_H

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
class DrawerDrawTexture : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_OFFSET_TEXEL = 0,		// テクセルオフセット
		PARAMETER_TEXTURE,				// テクスチャ
		PARAMETER_MULTIPLY,				// 色の倍率
		PARAMETER_MAX					// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerDrawTexture( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerDrawTexture( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
	// Arg    : IDirect3DTexture9** pTexture		: テクスチャ
	// Arg    : float* pMultiply					: 色の倍率
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9** ppTexture, float* pMultiply );

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
	// Arg    : IDirect3DTexture9** pTexture		: テクスチャ
	// Arg    : float* pMultiply					: 色の倍率
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9** ppTexture, float* pMultiply );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerDrawTexture* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( DrawerDrawTexture* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : const D3DXMATRIX& matrixWorld		: ワールドマトリクス
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

protected:
	const EffectParameter*	pEffectParameter_;		// エフェクトパラメータ
	Effect*					pEffect_;				// エフェクト
	IDirect3DTexture9**		ppTexture_;				// テクスチャ
	float*					pMultiply_;				// 色の倍率
	Polygon2D*				pPolygon_;				// ポリゴン

private:
	void InitializeSelf( void );
	DrawerDrawTexture( const DrawerDrawTexture& );
	DrawerDrawTexture operator=( const DrawerDrawTexture& );
};

#endif	// MY_DRAWER_DRAW_TEXTURE_H
