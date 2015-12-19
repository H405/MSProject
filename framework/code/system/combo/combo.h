//==============================================================================
//
// File   : Combo.h
// Brief  : コンボオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_COMBO_H
#define MY_COMBO_H

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
class Combo : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	Combo( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~Combo( void );

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
	Texture* pComboString,
	Texture* pComboScore);

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
	void addScore();
	void setScore(int _value){score = _value;}
	int getScore(){return score;}
	int getScorePrev(){return scorePrev;}
	int getScoreMax(){return scoreMax;}

protected:

	Object2D* comboString;
	ObjectScore* comboScore;

	int score;
	int scorePrev;
	int scoreMax;
	int flashingCount;
	float alpha;

private:
	void InitializeSelf( void );
	Combo( const Combo& );
	Combo operator=( const Combo& );

	//	更新関数格納用ポインタ
	void (Combo::*fpUpdate)(void);
};

#endif	// MY_COMBO_H
