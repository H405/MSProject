//==============================================================================
//
// File   : ObjectModelMaterial.h
// Brief  : モデルオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_MODEL_MATERIAL_H
#define MY_OBJECT_MODEL_MATERIAL_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/object/ObjectMovement.h"

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
class GraphicModelMaterial;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectModelMaterial : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectModelMaterial( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectModelMaterial( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	//==============================================================================
	int Initialize( int priority );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	//==============================================================================
	int Reinitialize( int priority );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ObjectModelMaterial* pOut			: コピー先アドレス
	//==============================================================================
	int Copy( ObjectModelMaterial* pOut ) const;

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// Brief  : 描画クラスの生成
	// Return : int									: 実行結果
	// Arg    : int priority						: 描画優先度
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
	// Arg    : Effect* pEffectShadow				: 影描画エフェクト
	// Arg    : Effect* pEffectParaboloid			: 放物変換描画エフェクト
	//==============================================================================
	int CreateGraphic( int priority, Model* pModel, const EffectParameter* pParameter,
		Effect* pEffectGeneral, Effect* pEffectReflect, Effect* pEffectShadow, Effect* pEffectParaboloid );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicModelMaterial* pValue );
	GraphicModelMaterial* GetGraphic( void ) const;

protected:
	GraphicModelMaterial*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	ObjectModelMaterial( const ObjectModelMaterial& );
	ObjectModelMaterial operator=( const ObjectModelMaterial& );
};

#endif	// MY_OBJECT_MODEL_MATERIAL_H
