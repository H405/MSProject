//==============================================================================
//
// File   : DrawerGrass.h
// Brief  : 草描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/12/11 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_GRASS_H
#define MY_DRAWER_GRASS_H

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
class PolygonSignboard;

//******************************************************************************
// クラス定義
//******************************************************************************
class DrawerGrass : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// 変換行列
		PARAMETER_TEXTURE,					// テクスチャ
		PARAMETER_VECTOR_WIND,				// 風向き
		PARAMETER_MAX						// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerGrass( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerGrass( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : PolygonSignboard* pPolygon			: ビルボードポリゴン
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	// Arg    : float hardness						: 硬さ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, PolygonSignboard* pPolygon,
		IDirect3DTexture9* pTexture, float hardness );

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
	// Arg    : PolygonSignboard* pPolygon			: ビルボードポリゴン
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	// Arg    : float hardness						: 硬さ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, PolygonSignboard* pPolygon,
		IDirect3DTexture9* pTexture, float hardness );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerGrass* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( DrawerGrass* pOut ) const;

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
	const EffectParameter*	pEffectParameter_;			// エフェクトパラメータ
	Effect*					pEffect_;					// エフェクト
	IDirect3DTexture9*		pTexture_;					// テクスチャ
	PolygonSignboard*		pPolygon_;					// ポリゴン
	float					hardness_;					// 硬さ
	D3DXVECTOR3				vectorTransform_;			// 変形のベクトル
	D3DXVECTOR3				velocityTransform_;			// 変形の速度

private:
	void InitializeSelf( void );
	DrawerGrass( const DrawerGrass& );
	DrawerGrass operator=( const DrawerGrass& );

};

#endif	// MY_DRAWER_GRASS_H
