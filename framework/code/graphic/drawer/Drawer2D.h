//==============================================================================
//
// File   : Drawer2D.h
// Brief  : 2Dポリゴン描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_2D_H
#define MY_DRAWER_2D_H

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
class Drawer2D : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,			// ワールドマトリクス
		PARAMETER_TEXTURE,					// テクスチャ
		PARAMETER_WIDTH_SCREEN_HALF,		// 画面幅の半分
		PARAMETER_HEIGHT_SCREEN_HALF,		// 画面高さの半分
		PARAMETER_COLOR,					// 色
		PARAMETER_POSITION_TEXTURE,			// テクスチャ座標
		PARAMETER_SCALE_TEXTURE,			// テクスチャ拡縮
		PARAMETER_MAX						// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Drawer2D( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Drawer2D( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
	// Arg    : D3DXCOLOR* pColor					: 色
	// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
	// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture );

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
	// Arg    : D3DXCOLOR* pColor					: 色
	// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
	// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Drawer2D* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( Drawer2D* pOut ) const;

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
	Polygon2D*				pPolygon_;				// ポリゴン
	D3DXCOLOR*				pColor_;				// 色
	D3DXVECTOR2*			pPositionTexture_;		// テクスチャ座標
	D3DXVECTOR2*			pScaleTexture_;			// テクスチャ拡縮

private:
	void InitializeSelf( void );
	Drawer2D( const Drawer2D& );
	Drawer2D operator=( const Drawer2D& );

};

#endif	// MY_DRAWER_2D_H
