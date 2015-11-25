//==============================================================================
//
// File   : DrawerWaveDataInitialize.h
// Brief  : 波情報描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_WAVE_DATA_INITIALIZE_H
#define MY_DRAWER_WAVE_DATA_INITIALIZE_H

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
class DrawerWaveDataInitialize : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,		// ワールド変換行列
		PARAMETER_TEXTURE_HEIGHT,		// 高さテクスチャ
		PARAMETER_MAX					// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerWaveDataInitialize( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerWaveDataInitialize( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTexture );

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
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerWaveDataInitialize* pOut		: コピー先アドレス
	//==============================================================================
	int Copy( DrawerWaveDataInitialize* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : const D3DXMATRIX& matrixWorld		: ワールドマトリクス
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

protected:
	const EffectParameter*	pEffectParameter_;		// エフェクトパラメータ
	Effect*					pEffect_;				// エフェクト
	IDirect3DTexture9*		pTexture_;				// テクスチャ
	Polygon2D*				pPolygon_;				// ポリゴン

private:
	void InitializeSelf( void );
	DrawerWaveDataInitialize( const DrawerWaveDataInitialize& );
	DrawerWaveDataInitialize operator=( const DrawerWaveDataInitialize& );

};

#endif	// MY_DRAWER_WAVE_DATA_INITIALIZE_H
