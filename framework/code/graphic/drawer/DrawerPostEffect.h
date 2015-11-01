//==============================================================================
//
// File   : DrawerPostEffect.h
// Brief  : 画面ポリゴン描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_POST_EFFECT_H
#define MY_DRAWER_POST_EFFECT_H

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
class DrawerPostEffect : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,			// ワールドマトリクス
		PARAMETER_TEXTURE,					// テクスチャ
		PARAMETER_TEXTURE_3D,				// 3D描画テクスチャ
		PARAMETER_TEXTURE_2D,				// 2D描画テクスチャ
		PARAMETER_TEXTURE_MASK,				// マスクテクスチャ
		PARAMETER_COLOR_FADE,				// フェードの色
		PARAMETER_WIDTH_SCREEN_HALF,		// 画面幅の半分
		PARAMETER_HEIGHT_SCREEN_HALF,		// 画面高さの半分
		PARAMETER_PROPORTION_FADE,			// フェードの割合
		PARAMETER_MAX						// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerPostEffect( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerPostEffect( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 画面ポリゴン
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTexture2D		: 2D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	// Arg    : const D3DXCOLOR* pColorFade			: フェードの色
	// Arg    : const float* pProportionFade		: フェードの割合
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture,
		const D3DXCOLOR* pColorFade, const float* pProportionFade );

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
	// Arg    : Polygon2D* pPolygon					: 画面ポリゴン
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTexture2D		: 2D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	// Arg    : const D3DXCOLOR* pColorFade			: フェードの色
	// Arg    : const float* pProportionFade		: フェードの割合
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTexture,
		const D3DXCOLOR* pColorFade, const float* pProportionFade );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerPostEffect* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( DrawerPostEffect* pOut ) const;

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
	void SetPolygon( Polygon2D* pValue );
	Polygon2D* GetPolygon( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;		// エフェクトパラメータ
	Effect*					pEffect_;				// エフェクト
	IDirect3DTexture9*		pTexture_;				// テクスチャ
	IDirect3DTexture9*		pTexture3D_;			// 3D描画テクスチャ
	IDirect3DTexture9*		pTexture2D_;			// 2D描画テクスチャ
	IDirect3DTexture9*		pTextureMask_;			// マスクテクスチャ
	Polygon2D*				pPolygon_;				// ポリゴン
	const D3DXCOLOR*		pColorFade_;			// フェード色
	const float*			pProportionFade_;		// フェード割合

private:
	void InitializeSelf( void );
	DrawerPostEffect( const DrawerPostEffect& );
	DrawerPostEffect operator=( const DrawerPostEffect& );

};

#endif	// MY_DRAWER_POST_EFFECT_H
