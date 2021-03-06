//==============================================================================
//
// File   : ObjectLightEffect.h
// Brief  : ライト描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_LIGHT_EFFECT_H
#define MY_OBJECT_LIGHT_EFFECT_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/object/object.h"

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
class GraphicLightEffect;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectLightEffect : public Object
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectLightEffect( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectLightEffect( void );

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
	// Arg    : ObjectLightEffect* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( ObjectLightEffect* pOut ) const;

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
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect** ppEffectGeneral			: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureDiffuse	: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecular	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormal	: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDiffuseRiver		: ディフューズ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureSpecularRiver	: スペキュラ情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureNormalRiver		: 法線情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepthRiver		: 深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureShadow	: 影テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect** ppEffectGeneral,
		IDirect3DTexture9* pTextureDiffuse, IDirect3DTexture9* pTextureSpecular, IDirect3DTexture9* pTextureNormal, IDirect3DTexture9* pTextureDepth,
		IDirect3DTexture9* pTextureDiffuseRiver, IDirect3DTexture9* pTextureSpecularRiver, IDirect3DTexture9* pTextureNormalRiver, IDirect3DTexture9* pTextureDepthRiver,
		IDirect3DTexture9* pTextureShadow );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicLightEffect* pValue );
	GraphicLightEffect* GetGraphic( void ) const;

protected:
	GraphicLightEffect*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	ObjectLightEffect( const ObjectLightEffect& );
	ObjectLightEffect operator=( const ObjectLightEffect& );

};

#endif	// MY_OBJECT_LIGHT_EFFECT_H
