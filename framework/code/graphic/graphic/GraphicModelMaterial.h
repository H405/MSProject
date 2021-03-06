//==============================================================================
//
// File   : GraphicModelMaterial.h
// Brief  : モデル描画処理の管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GRAPHIC_MODEL_H
#define MY_GRAPHIC_MODEL_H

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
class Model;
class EffectParameter;
class Effect;

//******************************************************************************
// クラス定義
//******************************************************************************
class GraphicModelMaterial : public GraphicMain
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	GraphicModelMaterial( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~GraphicModelMaterial( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
	// Arg    : Effect* pEffectShadow				: 影描画エフェクト
	// Arg    : Effect* pEffectParaboloid			: 放物変換描画エフェクト
	//==============================================================================
	int Initialize( int priority, Model* pModel, const EffectParameter* pParameter,
		Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid );

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
	// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
	// Arg    : Effect* pEffectShadow				: 影描画エフェクト
	// Arg    : Effect* pEffectParaboloid			: 放物変換描画エフェクト
	//==============================================================================
	int Reinitialize( int priority, Model* pModel, const EffectParameter* pParameter,
		Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : GraphicModelMaterial* pOut			: コピー先アドレス
	//==============================================================================
	int Copy( GraphicModelMaterial* pOut ) const;

protected:

private:
	void InitializeSelf( void );
	GraphicModelMaterial( const GraphicModelMaterial& );
	GraphicModelMaterial operator=( const GraphicModelMaterial& );
};

#endif	// MY_GRAPHIC_MODEL_H
