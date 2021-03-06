//==============================================================================
//
// File   : ObjectPostEffect.h
// Brief  : 画面ポリゴンオブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/10/17 sat : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_POST_EFFECT_H
#define MY_OBJECT_POST_EFFECT_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "../framework/object/Object.h"

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
class Fade;
class GraphicPostEffect;
class Texture;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectPostEffect : public Object
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectPostEffect( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectPostEffect( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	// Arg    : Fade* pFade							: フェード
	//==============================================================================
	int Initialize( int priority, Fade* pFade );

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
	// Arg    : Fade* pFade							: フェード
	//==============================================================================
	int Reinitialize( int priority, Fade* pFade );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ObjectPostEffect* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( ObjectPostEffect* pOut ) const;

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
	// Arg    : IDirect3DTexture9* pTexture3D		: 3D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTextureLuminance	: 輝度テクスチャ
	// Arg    : IDirect3DTexture9* pTextureBlur		: ブラーテクスチャ
	// Arg    : IDirect3DTexture9* pTextureDepth	: 深度テクスチャ
	// Arg    : IDirect3DTexture9* pTexture2D		: 2D描画テクスチャ
	// Arg    : IDirect3DTexture9* pTextureMask		: マスクテクスチャ
	// Arg    : Texture* pTexture					: テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral,
		IDirect3DTexture9* pTexture3D, IDirect3DTexture9* pTextureLuminance, IDirect3DTexture9* pTextureBlur, IDirect3DTexture9* pTextureDepth,
		IDirect3DTexture9* pTexture2D, IDirect3DTexture9* pTextureMask, Texture* pTexture = nullptr );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicPostEffect* pValue );
	GraphicPostEffect* GetGraphic( void ) const;

protected:
	GraphicPostEffect*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	ObjectPostEffect( const ObjectPostEffect& );
	ObjectPostEffect operator=( const ObjectPostEffect& );

	Fade*	pFade_;					// フェード
	float	proportionFade_;		// フェード割合
};

#endif	// MY_OBJECT_POST_EFFECT_H
