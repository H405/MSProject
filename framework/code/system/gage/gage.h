//==============================================================================
//
// File   : Gage.h
// Brief  : シンクロゲージオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_GAGE_H
#define MY_GAGE_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************
#define GAGEBAR_MAX (25)

//******************************************************************************
// クラス前方宣言
//******************************************************************************
class Object2D;
class Effect;
class EffectParameter;
class Texture;
class ObjectScore;

//******************************************************************************
// インクルード
//******************************************************************************
#include "../../framework/object/ObjectMovement.h"

//******************************************************************************
// クラス定義
//******************************************************************************
class Gage : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Gage( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Gage( void );

	//==============================================================================
	// Brief  : 初期化処理
	// Return : int									: 実行結果
	// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
	// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
	// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
	// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
	//==============================================================================
	int Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Effect* pEffectGeneral2,
	Texture* pGageBar,
	Texture* pGageBase,
	Texture* pGageBack,
	Texture* pGageScore);

	//==============================================================================
	// Brief  : 終了処理
	// Return : int									: 実行結果
	// Arg    : void								: なし
	//==============================================================================
	int Finalize( void );

	//==============================================================================
	// Brief  : 更新処理
	// Return : void								: なし
	// Arg    : void								: なし
	//==============================================================================
	void Update( void );

	//==============================================================================
	// アクセサ
	//==============================================================================
	void setPosition(float _x, float _y, float _z);
	void setPercent(float _value){percent = _value;if(percent < 0.0f)percent = 0.0f;if(percent > 100.0f)percent = 100.0f;}
	void addPercent(float _value){percent += _value;if(percent < 0.0f)percent = 0.0f;if(percent > 100.0f)percent = 100.0f;}

	void setPercentFuture(float _value){percentFuture = _value;if(percentFuture < 0.0f)percentFuture = 0.0f;if(percentFuture > 100.0f)percentFuture = 100.0f;}
	void addPercentFuture(float _value){percentFuture += _value;if(percentFuture < 0.0f)percentFuture = 0.0f;if(percentFuture > 100.0f)percentFuture = 100.0f;}

protected:

	Object2D* gageBar;
	Object2D* gageBase;
	Object2D* gageBack;
	int gageBackCount;
	float gageBackAddSize;

	ObjectScore* gageScore;

	float percent;
	float percentFuture;
	int barNum;
	int barNumOld;

private:
	void InitializeSelf( void );
	Gage( const Gage& );
	Gage operator=( const Gage& );

	//	更新関数格納用ポインタ
	void (Gage::*fpUpdate)(void);
};

#endif	// MY_GAGE_H
