//==============================================================================
//
// File   : GraphicRiver.h
// Brief  : 川描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_RIVER_H
#define MY_GRAPHIC_RIVER_H

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
class DrawerRiver;
class Effect;
class EffectParameter;
class Model;

//******************************************************************************
// クラス定義
//******************************************************************************
class GraphicRiver : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicRiver( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicRiver( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: 正面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: 背面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: 正面加算環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: 背面加算環境マップテクスチャ
	//==============================================================================
	int Initialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
		IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
		IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack );

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
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: 正面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: 背面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: 正面加算環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: 背面加算環境マップテクスチャ
	//==============================================================================
	int Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
		IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
		IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicRiver* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( GraphicRiver* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : int index							: 描画番号
	//==============================================================================
	void Draw( int index );

protected:

private:
	void InitializeSelf( void );
	GraphicRiver( const GraphicRiver& );
	GraphicRiver operator=( const GraphicRiver& );

	const EffectParameter*	pParameter_;		// エフェクトパラメータ
	DrawerRiver*			pDrawerRiver_;		// 川描画クラス
};

#endif	// MY_GRAPHIC_RIVER_H
