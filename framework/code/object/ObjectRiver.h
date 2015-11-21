//==============================================================================
//
// File   : ObjectRiver.h
// Brief  : 川オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/19 thr : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_RIVER_H
#define MY_OBJECT_RIVER_H

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
class GraphicRiver;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectRiver : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectRiver( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectRiver( void );

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
	// Arg    : ObjectRiver* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( ObjectRiver* pOut ) const;

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
	// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線テクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentFront	: 正面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentBack	: 背面環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddFront	: 正面加算環境マップテクスチャ
	// Arg    : IDirect3DTexture9* pTextureEnvironmentAddBack	: 背面加算環境マップテクスチャ
	//==============================================================================
	int CreateGraphic( int priority, Model* pModel, const EffectParameter* pParameter, Effect** ppEffectGeneral,
		IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureEnvironmentFront, IDirect3DTexture9* pTextureEnvironmentBack,
		IDirect3DTexture9* pTextureEnvironmentAddFront, IDirect3DTexture9* pTextureEnvironmentAddBack );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicRiver* pValue );
	GraphicRiver* GetGraphic( void ) const;

protected:
	GraphicRiver*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	ObjectRiver( const ObjectRiver& );
	ObjectRiver operator=( const ObjectRiver& );
};

#endif	// MY_OBJECT_RIVER_H
