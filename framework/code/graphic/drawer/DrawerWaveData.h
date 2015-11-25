//==============================================================================
//
// File   : DrawerWaveData.h
// Brief  : 波情報描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_WAVE_DATA_H
#define MY_DRAWER_WAVE_DATA_H

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
class DrawerWaveData : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,		// ワールド変換行列
		PARAMETER_TEXTURE_HEIGHT,		// 高さテクスチャ
		PARAMETER_WAVE_ADD,				// 波追加情報
		PARAMETER_MAX					// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerWaveData( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerWaveData( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
	// Arg    : IDirect3DTexture9* pTextureHeight0	: 高さテクスチャ0
	// Arg    : IDirect3DTexture9* pTextureHeight1	: 高さテクスチャ1
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 );

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
	// Arg    : IDirect3DTexture9* pTextureHeight0	: 高さテクスチャ0
	// Arg    : IDirect3DTexture9* pTextureHeight1	: 高さテクスチャ1
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTextureHeight0, IDirect3DTexture9* pTextureHeight1 );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerWaveData* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( DrawerWaveData* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : const D3DXMATRIX& matrixWorld		: ワールドマトリクス
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

protected:
	const EffectParameter*	pEffectParameter_;		// エフェクトパラメータ
	Effect*					pEffect_;				// エフェクト
	IDirect3DTexture9*		pTextureHeight0_;		// 高さテクスチャ0
	IDirect3DTexture9*		pTextureHeight1_;		// 高さテクスチャ1
	Polygon2D*				pPolygon_;				// ポリゴン
	bool					isTexture0_;			// テクスチャ0フラグ

private:
	void InitializeSelf( void );
	DrawerWaveData( const DrawerWaveData& );
	DrawerWaveData operator=( const DrawerWaveData& );

};

#endif	// MY_DRAWER_WAVE_DATA_H
