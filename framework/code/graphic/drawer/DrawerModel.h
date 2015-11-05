//==============================================================================
//
// File   : DrawerModel.h
// Brief  : モデル描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/18 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_MODEL_H
#define MY_DRAWER_MODEL_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../../framework/graphic/drawer.h"

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
class Model;

//******************************************************************************
// クラス定義
//******************************************************************************
class DrawerModel : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// 変換行列
		PARAMETER_MATRIX_WORLD,				// ワールド変換行列
		PARAMETER_MATRIX_WORLD_VIEW,		// ワールドビュー変換行列
		PARAMETER_TEXTURE,					// テクスチャ
		PARAMETER_COLOR_SPECULAR,			// スペキュラ色
		PARAMETER_REFLECTION,				// 反射率
		PARAMETER_POWER,					// 反射の強さ
		PARAMETER_REFLACTIVE,				// 屈折率
		PARAMETER_MAX						// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerModel( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerModel( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	//==============================================================================
	int Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	//==============================================================================
	int Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerModel* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( DrawerModel* pOut ) const;

	//==============================================================================
	// Brief  : 描画処理
	// Return : void								: なし
	// Arg    : const D3DXMATRIX& matrixWorld		: ワールドマトリクス
	//==============================================================================
	void Draw( const D3DXMATRIX& matrixWorld );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetModel( Model* pValue );
	Model* GetModel( void ) const;

protected:
	const EffectParameter*	pEffectParameter_;		// エフェクトパラメータ
	Effect*					pEffect_;				// エフェクト
	Model*					pModel_;				// モデル

private:
	void InitializeSelf( void );
	DrawerModel( const DrawerModel& );
	DrawerModel operator=( const DrawerModel& );
};

#endif	// MY_DRAWER_MODEL_H
