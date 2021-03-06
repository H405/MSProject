//==============================================================================
//
// File   : FireworksUI.h
// Brief  : 花火UIオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef MY_FIREWORKSUI_H
#define MY_FIREWORKSUI_H

//******************************************************************************
// インクルード
//******************************************************************************
#include "d3dx9.h"
#include "../target/Target.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ
//******************************************************************************
#define FIREWORKS_UI_MAX (12)

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
class FireworksUI : public ObjectMovement
{
public:
	//==============================================================================
	// Brief  : コンストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	FireworksUI( void );

	//==============================================================================
	// Brief  : デストラクタ
	// Return : 									: 
	// Arg    : void								: なし
	//==============================================================================
	~FireworksUI( void );

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
	Texture* pFireworksUITex);

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
	void addPositionX(float _value){pos.x += _value;}
	void addPositionY(float _value){pos.y += _value;}
	COLOR_STATE getColorState(){return colorState;}
	void addRotColor();
	void subRotColor();

	void SetEnableGraphic(bool _flag);

protected:

	Object2D* fireworksUI;

	D3DXVECTOR3 pos;
	float rot;
	float addRot;

	COLOR_STATE colorState;
	int stateNum;
	int stateNumOld;
	bool moveFlag;
	int moveCount;

private:
	void InitializeSelf( void );
	FireworksUI( const FireworksUI& );
	FireworksUI operator=( const FireworksUI& );
};

#endif	// MY_FIREWORKSUI_H
