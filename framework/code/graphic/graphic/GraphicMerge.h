//==============================================================================
//
// File   : GraphicMerge.h
// Brief  : 総合3D描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_MERGE_H
#define MY_GRAPHIC_MERGE_H

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
class GraphicMerge : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicMerge( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicMerge( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureLight	: ライトありテクスチャ
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ライトなしテクスチャ
	// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
	// Arg    : IDirect3DTexture9* pTextureAdd		: 加算合成テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	// Arg    : IDirect3DTexture9* pTextureRiver	: 川テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepthRiver	: 川の深度テクスチャ
	//==============================================================================
	int Initialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureRiver, IDirect3DTexture9* pTextureDepthRiver );

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
	// Arg    : IDirect3DTexture9* pTextureLight	: ライトありテクスチャ
	// Arg    : IDirect3DTexture9* pTextureNotLight	: ライトなしテクスチャ
	// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
	// Arg    : IDirect3DTexture9* pTextureAdd		: 加算合成テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	// Arg    : IDirect3DTexture9* pTextureRiver	: 川テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepthRiver	: 川の深度テクスチャ
	//==============================================================================
	int Reinitialize( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureLight, IDirect3DTexture9* pTextureNotLight, IDirect3DTexture9* pTextureMask, IDirect3DTexture9* pTextureAdd,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureRiver, IDirect3DTexture9* pTextureDepthRiver );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicMerge* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( GraphicMerge* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicMerge( const GraphicMerge& );
	GraphicMerge operator=( const GraphicMerge& );

};

#endif	// MY_GRAPHIC_MERGE_H
