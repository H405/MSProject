//==============================================================================
//
// File   : Graphic2D.h
// Brief  : 2Dポリゴン描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_2D_H
#define MY_GRAPHIC_2D_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "GraphicMain.h"

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

//******************************************************************************
// クラス定義
//******************************************************************************
class Graphic2D : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Graphic2D( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Graphic2D( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : D3DXCOLOR* pColor					: 色
	// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
	// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture = nullptr );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : D3DXCOLOR* pColor					: 色
	// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
	// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture = nullptr );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : Graphic2D* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( Graphic2D* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	Graphic2D( const Graphic2D& );
	Graphic2D operator=( const Graphic2D& );
};

#endif	// MY_GRAPHIC_2D_H
