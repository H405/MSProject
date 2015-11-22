//==============================================================================
//
// File   : GraphicLightReflect.h
// Brief  : 反射ライト描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/22 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_LIGHT_REFLECT_H
#define MY_GRAPHIC_LIGHT_REFLECT_H

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
class DrawerLightReflect;
class Effect;
class EffectParameter;

//******************************************************************************
// クラス定義
//******************************************************************************
class GraphicLightReflect : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicLightReflect( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicLightReflect( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
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
	// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicLightReflect* pOut			: コピー先アドレス
	//==============================================================================
	int Copy( GraphicLightReflect* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : int index							: 描画番号
	//==============================================================================
	void Draw( int index );

protected:

private:
	void InitializeSelf( void );
	GraphicLightReflect( const GraphicLightReflect& );
	GraphicLightReflect operator=( const GraphicLightReflect& );

	const EffectParameter*	pParameter_;		// エフェクトパラメータ
	DrawerLightReflect*		pDrawerLight_;		// ライト描画クラス
};

#endif	// MY_GRAPHIC_LIGHT_REFLECT_H
