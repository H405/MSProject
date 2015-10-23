//==============================================================================
//
// File   : GraphicBillboard.h
// Brief  : ビルボードポリゴン描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/23 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_BILLBOARD_H
#define MY_GRAPHIC_BILLBOARD_H

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
class EffectParameter;
class Effect;

//******************************************************************************
// クラス定義
//******************************************************************************
class GraphicBillboard : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicBillboard( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicBillboard( void );

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
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : D3DXCOLOR* pColor					: 色
	// Arg    : D3DXVECTOR2* pPositionTexture		: テクスチャ座標
	// Arg    : D3DXVECTOR2* pScaleTexture			: テクスチャ拡縮
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		D3DXCOLOR* pColor, D3DXVECTOR2* pPositionTexture, D3DXVECTOR2* pScaleTexture, IDirect3DTexture9* pTexture );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicBillboard* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( GraphicBillboard* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicBillboard( const GraphicBillboard& );
	GraphicBillboard operator=( const GraphicBillboard& );

};

#endif	// MY_GRAPHIC_BILLBOARD_H
