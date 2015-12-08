//==============================================================================
//
// File   : ObjectShadow.h
// Brief  : ライト描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/31 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_SHADOW_H
#define MY_OBJECT_SHADOW_H

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
class GraphicShadow;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectShadow : public Object
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectShadow( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectShadow( void );

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
	// Arg    : ObjectShadow* pOut					: コピー先アドレス
	//==============================================================================
	int Copy( ObjectShadow* pOut ) const;

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
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightNear	: 平行光源(近)の深度情報テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLightFar		: 平行光源(遠)の深度情報テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTextureDepth, IDirect3DTexture9* pTextureLightNear, IDirect3DTexture9* pTextureLightFar );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicShadow* pValue );
	GraphicShadow* GetGraphic( void ) const;

protected:
	GraphicShadow*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	ObjectShadow( const ObjectShadow& );
	ObjectShadow operator=( const ObjectShadow& );

};

#endif	// MY_OBJECT_SHADOW_H
