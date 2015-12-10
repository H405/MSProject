//==============================================================================
//
// File   : GraphicShadow.h
// Brief  : ライト描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_SHADOW_H
#define MY_GRAPHIC_SHADOW_H

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
class DrawerShadow;
class Effect;
class EffectParameter;

//******************************************************************************
// クラス定義
//******************************************************************************
class GraphicShadow : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicShadow( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicShadow( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightNear	: 平行光源(近)の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightFar		: 平行光源(遠)の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightPoint0	: 点光源0の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightPoint1	: 点光源1の深度情報テクスチャ
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar,
		IDirect3DTexture9* pTextureLightPoint0, IDirect3DTexture9* pTextureLightPoint1 );

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
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightNear	: 平行光源(近)の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightFar		: 平行光源(遠)の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightPoint0	: 点光源0の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightPoint1	: 点光源1の深度情報テクスチャ
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar,
		IDirect3DTexture9* pTextureLightPoint0, IDirect3DTexture9* pTextureLightPoint1 );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicShadow* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( GraphicShadow* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicShadow( const GraphicShadow& );
	GraphicShadow operator=( const GraphicShadow& );

	const EffectParameter*	pParameter_;		// エフェクトパラメータ
	DrawerShadow*		pDrawerLight_;		// ライト描画クラス
};

#endif	// MY_GRAPHIC_SHADOW_H
