//==============================================================================
//
// File   : GraphicLightEffect.h
// Brief  : ライト描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_LIGHT_EFFECT_H
#define MY_GRAPHIC_LIGHT_EFFECT_H

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
class GraphicLightEffect : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicLightEffect( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicLightEffect( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth );

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
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicLightEffect* pOut			: コピー先アドレス
	//==============================================================================
	int Copy( GraphicLightEffect* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicLightEffect( const GraphicLightEffect& );
	GraphicLightEffect operator=( const GraphicLightEffect& );

};

#endif	// MY_GRAPHIC_LIGHT_EFFECT_H
