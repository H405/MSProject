//==============================================================================
//
// File   : DrawerSkinMeshReflect.h
// Brief  : スキンメッシュ描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/03 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_SKIN_MESH_REFLECT_H
#define MY_DRAWER_SKIN_MESH_REFLECT_H

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
class Motion;

//******************************************************************************
// クラス定義
//******************************************************************************
class DrawerSkinMeshReflect : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,		// 変換行列
		PARAMETER_MATRIX_WORLD,				// ワールド変換行列
		PARAMETER_MATRIX_WORLD_VIEW,		// ワールドビュー変換行列
		PARAMETER_MATRIX_BONE,				// ボーン変換行列
		PARAMETER_HEIGHT,					// 反射面の高さ
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
	DrawerSkinMeshReflect( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerSkinMeshReflect( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Model* pModel						: モデル
	// Arg    : int countBone						: ボーン数
	// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
	//==============================================================================
	int Initialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone );

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 再初期化処理
	// Return : int									: 実行結果
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : Model* pModel						: モデル
	// Arg    : int countBone						: ボーン数
	// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
	//==============================================================================
	int Reinitialize( const EffectParameter* pParameter, Effect* pEffect, Model* pModel, int countBone, D3DXMATRIX* pMatrixBone );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerSkinMeshReflect* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( DrawerSkinMeshReflect* pOut ) const;

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
	int						countBone_;				// ボーン数
	D3DXMATRIX*				pMatrixBone_;			// ボーン変換行列参照アドレス

private:
	void InitializeSelf( void );
	DrawerSkinMeshReflect( const DrawerSkinMeshReflect& );
	DrawerSkinMeshReflect operator=( const DrawerSkinMeshReflect& );

};

#endif	// MY_DRAWER_SKIN_MESH_REFLECT_H
