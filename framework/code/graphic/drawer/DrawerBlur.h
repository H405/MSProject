//==============================================================================
//
// File   : DrawerBlur.h
// Brief  : ブラー描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/10 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_BLUR_H
#define MY_DRAWER_BLUR_H

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
class DrawerBlur : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_WORLD = 0,		// ワールド変換行列
		PARAMETER_SIZE_SCREEN_HALF,		// 画面サイズの半分
		PARAMETER_TEXTURE,				// ブラーを掛けるテクスチャ
		PARAMETER_OFFSET,				// オフセット
		PARAMETER_MAX					// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerBlur( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerBlur( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon2D* pPolygon					: 2Dポリゴン
	// Arg    : IDirect3DTexture9* pTexture			: ブラーを掛けるテクスチャ
	// Arg    : const D3DXVECTOR2& offset			: オフセット
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTexture, const D3DXVECTOR2& offset );

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
	// Arg    : IDirect3DTexture9* pTexture			: ブラーを掛けるテクスチャ
	// Arg    : const D3DXVECTOR2& offset			: オフセット
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon2D* pPolygon, IDirect3DTexture9* pTexture, const D3DXVECTOR2& offset );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerBlur* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( DrawerBlur* pOut ) const;

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
	IDirect3DTexture9*		pTexture_;				// ブラーを掛けるテクスチャ
	Polygon2D*				pPolygon_;				// ポリゴン

private:
	void InitializeSelf( void );
	DrawerBlur( const DrawerBlur& );
	DrawerBlur operator=( const DrawerBlur& );

};

#endif	// MY_DRAWER_BLUR_H
