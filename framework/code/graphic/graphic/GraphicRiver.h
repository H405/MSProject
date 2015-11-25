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
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflect	: 反射テクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: 反射ライティングなしテクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflectAdd		: 反射加算合成テクスチャ
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	//==============================================================================
	int Initialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureNormal,
		IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth );

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
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflect	: 反射テクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: 反射ライティングなしテクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflectAdd		: 反射加算合成テクスチャ
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	//==============================================================================
	int Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTextureNormal,
		IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicRiver* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( GraphicRiver* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicRiver( const GraphicRiver& );
	GraphicRiver operator=( const GraphicRiver& );

	const EffectParameter*	pParameter_;		// エフェクトパラメータ
	DrawerRiver*			pDrawerRiver_;		// 川描画クラス
};

#endif	// MY_GRAPHIC_RIVER_H
