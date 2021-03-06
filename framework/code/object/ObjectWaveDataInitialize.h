//==============================================================================
//
// File   : ObjectWaveDataInitialize.h
// Brief  : 波情報描画オブジェクトクラス
// Author : Taiga Shirakawa
// Date   : 2015/11/17 tue : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_OBJECT_WAVE_DATA_INITIALIZE_H
#define MY_OBJECT_WAVE_DATA_INITIALIZE_H

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
class GraphicWaveDataInitialize;
class Texture;

//******************************************************************************
// クラス定義
//******************************************************************************
class ObjectWaveDataInitialize : public Object
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	ObjectWaveDataInitialize( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~ObjectWaveDataInitialize( void );

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
	// Arg    : ObjectWaveDataInitialize* pOut		: コピー先アドレス
	//==============================================================================
	int Copy( ObjectWaveDataInitialize* pOut ) const;

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
	// Arg    : Effect* pEffect						: エフェクト
	// Arg    : Texture* pTexture					: テクスチャ
	//==============================================================================
	int CreateGraphic( int priority, const EffectParameter* pParameter, Effect* pEffect, Texture* pTexture );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void SetGraphic( GraphicWaveDataInitialize* pValue );
	GraphicWaveDataInitialize* GetGraphic( void ) const;

protected:
	GraphicWaveDataInitialize*	pGraphic_;		// 描画クラス

private:
	void InitializeSelf( void );
	ObjectWaveDataInitialize( const ObjectWaveDataInitialize& );
	ObjectWaveDataInitialize operator=( const ObjectWaveDataInitialize& );

	int		timerGraphic_;		// グラフィックをオフにするタイマー
};

#endif	// MY_OBJECT_BLUR_BASE_H
