//==============================================================================
//
// File   : DrawerRiver.h
// Brief  : 川描画クラス
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_DRAWER_RIVER_H
#define MY_DRAWER_RIVER_H

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
class DrawerRiver : public Drawer
{
public:
	// パラメータ
	enum
	{
		PARAMETER_MATRIX_TRANSFORM = 0,					// 変換行列
		PARAMETER_MATRIX_WORLD,							// ワールド変換行列
		PARAMETER_MATRIX_WORLD_VIEW,					// ワールドビュー変換行列
		PARAMETER_MATRIX_TRANSFORM_TEXTURE,				// テクスチャ座標変換行列

		PARAMETER_MATRIX_WORLD_INVERSE_TRANSPOSE,		// ワールド逆転置行列
		PARAMETER_TEXTURE_NORMAL,						// 法線テクスチャ
		PARAMETER_COLOR_DIFFUSE,						// ディフューズ色
		PARAMETER_COLOR_SPECULAR,						// スペキュラ色
		PARAMETER_REFLECTION,							// 反射率
		PARAMETER_POWER,								// 反射の強さ
		PARAMETER_REFLACTIVE,							// 屈折率

		PARAMETER_TEXTURE_REFLECT,						// 反射テクスチャ
		PARAMETER_TEXTURE_REFLECT_NOT_LIGHT,			// 反射ライティングなしテクスチャ
		PARAMETER_TEXTURE_REFLECT_ADD,					// 反射加算合成テクスチャ
		PARAMETER_TEXTURE_3D,							// 3D描画テクスチャ
		PARAMETER_TEXTURE_DEPTH,						// 深度テクスチャ

		PARAMETER_POSITION_EYE,							// 視点座標
		PARAMETER_CLIP_CAMERA,							// カメラのクリップ値

		PARAMETER_MAX									// 最大値
	};

	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	DrawerRiver( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~DrawerRiver( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflect	: 反射テクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: 反射ライティングなしテクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflectAdd		: 反射加算合成テクスチャ
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	//==============================================================================
	int Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTextureNormal,
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
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflect	: 反射テクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflectNotLight	: 反射ライティングなしテクスチャ
	// Arg    : IDirect3DTexture9* pTextureReflectAdd		: 反射加算合成テクスチャ
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	//==============================================================================
	int Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect, IDirect3DTexture9* pTextureNormal,
		IDirect3DTexture9* pTextureReflect, IDirect3DTexture9* pTextureReflectNotLight, IDirect3DTexture9* pTextureReflectAdd,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureDepth );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : DrawerRiver* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( DrawerRiver* pOut ) const;

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
	const EffectParameter*	pEffectParameter_;				// エフェクトパラメータ
	Effect*					pEffect_;						// エフェクト
	Model*					pModel_;						// モデル
	IDirect3DTexture9*		pTextureNormal_;				// 法線テクスチャ
	IDirect3DTexture9*		pTextureReflect_;				// 反射テクスチャ
	IDirect3DTexture9*		pTextureReflectNotLight_;		// 反射ライティングなしテクスチャ
	IDirect3DTexture9*		pTextureReflectAdd_;			// 反射加算合成テクスチャ
	IDirect3DTexture9*		pTexture3D_;					// 3D描画テクスチャ
	IDirect3DTexture9*		pTextureDepth_;					// 深度テクスチャ

private:
	void InitializeSelf( void );
	DrawerRiver( const DrawerRiver& );
	DrawerRiver operator=( const DrawerRiver& );
};

#endif	// MY_DRAWER_RIVER_H
