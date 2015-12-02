//==============================================================================
//
// File   : ObjectDrawTexture.h
// Brief  : デバッグテクスチャ描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/27 fri : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_DRAW_TEXTURE_H
#define MY_OBJECT_DRAW_TEXTURE_H

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
class GraphicDrawTexture;
class InputKeyboard;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectDrawTexture : public Object
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectDrawTexture( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectDrawTexture( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : int priority						: 更新優先度
	// Arg    : InputKeyboard* pKeyboard			: キーボード入力
	//==============================================================================
	int Initialize( int priority, InputKeyboard* pKeyboard );

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
	// Arg    : InputKeyboard* pKeyboard			: キーボード入力
	//==============================================================================
	int Reinitialize( int priority, InputKeyboard* pKeyboard );

	//==============================================================================
	// Brief  : クラスのコピー
	// Return : int									: 実行結果
	// Arg    : ObjectDrawTexture* pOut				: コピー先アドレス
	//==============================================================================
	int Copy( ObjectDrawTexture* pOut ) const;

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
	// Arg    : int countTexture					: テクスチャ数
	// Arg    : IDirect3DTexture9** ppTexture		: テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffectGeneral, int countTexture, IDirect3DTexture9** ppTexture );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicDrawTexture* pValue );
	GraphicDrawTexture* GetGraphic( void ) const;

protected:
	GraphicDrawTexture*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	ObjectDrawTexture( const ObjectDrawTexture& );
	ObjectDrawTexture operator=( const ObjectDrawTexture& );

	const EffectParameter*	pParameter_;			// エフェクトのパラメータ
	int						countTexture_;			// テクスチャ数
	int						indexTexture_;			// テクスチャ番号
	IDirect3DTexture9**		ppTableTexture_;		// テクスチャテーブル
	IDirect3DTexture9*		pTextureCurrent_;		// 現在のテクスチャ
	float					pMultiply_[ 3 ];		// 色の倍率
	InputKeyboard*			pKeyboard_;				// キーボード入力
	bool					isEnableDraw_;			// 表示フラグ
};

#endif	// MY_OBJECT_DRAW_TEXTURE_H
