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

		PARAMETER_MATRIX_WORLD_INVERSE_TRANSPOSE,		// ワールド逆転置行列
		PARAMETER_TEXTURE_NORMAL,						// 法線テクスチャ
		PARAMETER_COLOR_DIFFUSE,						// ディフューズ色
		PARAMETER_COLOR_SPECULAR,						// スペキュラ色
		PARAMETER_REFLECTION,							// 反射率
		PARAMETER_POWER,								// 反射の強さ
		PARAMETER_REFLACTIVE,							// 屈折率

		PARAMETER_TEXTURE_ENVIRONMENT_FRONT,			// 正面環境テクスチャ
		PARAMETER_TEXTURE_ENVIRONMENT_BACK,				// 背面環境テクスチャ
		PARAMETER_TEXTURE_ENVIRONMENT_ADD_FRONT,		// 正面加算環境テクスチャ
		PARAMETER_TEXTURE_ENVIRONMENT_ADD_BACK,			// 背面加算環境テクスチャ

		PARAMETER_POSITION_EYE,							// 視点座標
		PARAMETER_CLIP_CAMERA,							// カメラのクリップ値
		PARAMETER_COLOR_AMBIENT,						// 環境光色
		PARAMETER_VECTOR_LIGHT_DIRECTION,				// ディレクショナルライトのベクトル
		PARAMETER_COLOR_LIGHT_DIRECTION,				// ディレクショナルライトの色
		PARAMETER_POSITION_LIGHT_POINT,					// ポイントライトの座標
		PARAMETER_COLOR_LIGHT_POINT,					// ポイントライトの色
		PARAMETER_ATTENUATION_LIGHT_POINT,				// ポイントライトの減衰率

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
	// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: 正面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: 背面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: 正面加算環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: 背面加算環境マップテクスチャ
	//==============================================================================
	int Initialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect,
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
	// Arg    : Model* pModel						: モデル
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffect						: 描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: 正面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: 背面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: 正面加算環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: 背面加算環境マップテクスチャ
	//==============================================================================
	int Reinitialize( Model* pModel, const EffectParameter* pParameter, Effect* pEffect,
		IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
		IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack );

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
	const EffectParameter*	pEffectParameter_;					// エフェクトパラメータ
	Effect*					pEffect_;							// エフェクト
	Model*					pModel_;							// モデル
	IDirect3DTexture9*		pTextureNormal_;					// 法線テクスチャ
	IDirect3DTexture9*		pTextureEnvironmentFront_;			// 正面方向環境マップ
	IDirect3DTexture9*		pTextureEnvironmentBack_;			// 背面方向環境マップ
	IDirect3DTexture9*		pTextureEnvironmentAddFront_;		// 正面加算方向環境マップ
	IDirect3DTexture9*		pTextureEnvironmentAddBack_;		// 背面加算方向環境マップ

private:
	void InitializeSelf( void );
	DrawerRiver( const DrawerRiver& );
	DrawerRiver operator=( const DrawerRiver& );
};

#endif	// MY_DRAWER_RIVER_H
