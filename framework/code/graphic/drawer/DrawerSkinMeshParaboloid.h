//==============================================================================
//
// File   : DrawerSkinMeshParaboloid.h
// Brief  : モデル影描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/24 sun : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_SKIN_MESH_PARABOLOID_H
#define MY_DRAWER_SKIN_MESH_PARABOLOID_H

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
class DrawerSkinMeshParaboloid : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_WORLD_VIEW = 0,		// ワールドビュー変換行列
		PARAMETER_MATRIX_BONE,					// ボーン変換行列
		PARAMETER_CLIP_CAMERA,					// カメラのクリップ面
		PARAMETER_MAX							// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerSkinMeshParaboloid( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerSkinMeshParaboloid( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : int indexCamera						: カメラ番号
	// Arg    : int countBone						: ボーン数
	// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
	//==============================================================================
	int Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, int indexCamera,
		int countBone, D3DXMATRIX* pMatrixBone );

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
	// Arg    : int indexCamera						: カメラ番号
	// Arg    : int countBone						: ボーン数
	// Arg    : D3DXMATRIX* pMatrixBone				: ボーン変換行列参照アドレス
	//==============================================================================
	int Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, int indexCamera,
		int countBone, D3DXMATRIX* pMatrixBone );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerSkinMeshParaboloid* pOut		: コピー先アドレス
	//==============================================================================
	int Copy( DrawerSkinMeshParaboloid* pOut ) const;

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
	int						indexCamera_;			// カメラ番号
	int						countBone_;				// ボーン数
	D3DXMATRIX*				pMatrixBone_;			// ボーン変換行列参照アドレス

private:
	void InitializeSelf( void );
	DrawerSkinMeshParaboloid( const DrawerSkinMeshParaboloid& );
	DrawerSkinMeshParaboloid operator=( const DrawerSkinMeshParaboloid& );
};

#endif	// MY_DRAWER_SKIN_MESH_PARABOLOID_H
