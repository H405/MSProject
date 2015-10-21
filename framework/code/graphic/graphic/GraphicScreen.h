//==============================================================================
//
// File   : GraphicScreen.h
// Brief  : 画面ポリゴン描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_SCREEN_H
#define MY_GRAPHIC_SCREEN_H

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
class GraphicScreen : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicScreen( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicScreen( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : const float* pProportionFade		: フェード割合
	// Arg    : IDirect3DTexture9* pTextureGeneral	: 通常描画テクスチャ
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
		IDirect3DTexture9* pTextureGeneral, IDirect3DTexture9* pTexture = nullptr );

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
	// Arg    : const float* pProportionFade		: フェード割合
	// Arg    : IDirect3DTexture9* pTextureGeneral	: 通常描画テクスチャ
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, const float* pProportionFade,
		IDirect3DTexture9* pTextureGeneral, IDirect3DTexture9* pTexture = nullptr );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicScreen* pOut						: コピー先アドレス
	//==============================================================================
	int Copy( GraphicScreen* pOut ) const;

protected:
	IDirect3DTexture9*	pTexture_;			// テクスチャ
	D3DXCOLOR			colorFade_;			// フェード色

private:
	void InitializeSelf( void );
	GraphicScreen( const GraphicScreen& );
	GraphicScreen operator=( const GraphicScreen& );
};

#endif	// MY_GRAPHIC_SCREEN_H
