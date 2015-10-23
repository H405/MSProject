//==============================================================================
//
// File   : DrawerBillboard.h
// Brief  : ビルボードポリゴン描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/23 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_BILLBOARD_H
#define MY_DRAWER_BILLBOARD_H

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
class Polygon3D;

//******************************************************************************
// クラス定義
//******************************************************************************
class DrawerBillboard : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// 変換行列
		PARAMETER_TEXTURE,					// テクスチャ
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
	DrawerBillboard( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerBillboard( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Polygon3D* pPolygon					: ビルボードポリゴン
	// Arg    : D3DXCOLOR* pColor					: 色
	// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
	// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Polygon3D* pPolygon,
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
	// Arg    : Polygon3D* pPolygon					: ビルボードポリゴン
	// Arg    : D3DXCOLOR* pColor					: 色
	// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
	// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Polygon3D* pPolygon,
		D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerBillboard* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( DrawerBillboard* pOut ) const;

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
	D3DXCOLOR*				pColor_;				// 色
	D3DXVECTOR2*			pPositionTexture_;		// テクスチャ座標
	D3DXVECTOR2*			pScaleTexture_;			// テクスチャ拡縮

private:
	void InitializeSelf( void );
	DrawerBillboard( const DrawerBillboard& );
	DrawerBillboard operator=( const DrawerBillboard& );

};

#endif	// MY_DRAWER_BILLBOARD_H
