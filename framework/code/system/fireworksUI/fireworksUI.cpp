//==============================================================================
//
// File   : FireworksUI.cpp
// Brief  : 花火UIオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "fireworksUI.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerTexture.h"
#include "../../object/Object2D.h"
#include "../../framework/develop/DebugProc.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
FireworksUI::FireworksUI( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void FireworksUI::InitializeSelf( void )
{
	// メンバ変数の初期化
	fpUpdate = nullptr;
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
FireworksUI::~FireworksUI( void )
{
	// 終了処理
	Finalize();
}
//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int FireworksUI::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pFireworksUITex)
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}

	fireworksUI1 = new Object2D();
	fireworksUI1->Initialize(0);
	fireworksUI1->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pFireworksUITex
		);
	fireworksUI1->SetScale(100.0f, 100.0f, 0.0f);

	//	setScaleTextureで、分割数を設定
	fireworksUI1->SetScaleTexture(3.0f, 1.0f);

	//	setPositionTextureで、0～1（丸め込む必要無し！）値を設定して、UVスクロールする
	fireworksUI1->SetPositionTexture(0.0f, 0.0f);


	fireworksUI2 = new Object2D();
	fireworksUI2->Initialize(0);
	fireworksUI2->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pFireworksUITex
		);
	fireworksUI2->SetScale(180.0f, 180.0f, 0.0f);

	fireworksUI2->SetScaleTexture(3.0f, 1.0f);
	fireworksUI2->SetPositionTexture(1.0f / 3.0f, 0.0f);

	fireworksUI3 = new Object2D();
	fireworksUI3->Initialize(0);
	fireworksUI3->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pFireworksUITex
		);
	fireworksUI3->SetScale(100.0f, 100.0f, 0.0f);

	fireworksUI3->SetScaleTexture(3.0f, 1.0f);
	fireworksUI3->SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int FireworksUI::Finalize( void )
{
	delete fireworksUI1;
	delete fireworksUI2;
	delete fireworksUI3;

	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Finalize();
	if( result != 0 )
	{
		return result;
	}

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void FireworksUI::Update( void )
{
	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 位置セット処理
//==============================================================================
void FireworksUI::setPosition(float _x, float _y, float _z)
{
	fireworksUI1->SetPosition(_x + 100.0f, _y, _z);
	fireworksUI2->SetPosition(_x, _y, _z);
	fireworksUI3->SetPosition(_x - 100.0f, _y, _z);

	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 色のセット
//==============================================================================
void FireworksUI::setColorState(COLOR_STATE _colorState)
{
	switch(_colorState)
	{
	case COLOR_STATE_R:

		fireworksUI1->SetPositionTextureX(-1.0f / 3.0f);
		fireworksUI2->SetPositionTextureX(0.0f);
		fireworksUI3->SetPositionTextureX(1.0f / 3.0f);

		break;

	case COLOR_STATE_G:

		fireworksUI1->SetPositionTextureX(0.0f);
		fireworksUI2->SetPositionTextureX(1.0f / 3.0f);
		fireworksUI3->SetPositionTextureX(-1.0f / 3.0f);

		break;

	case COLOR_STATE_B:

		fireworksUI1->SetPositionTextureX(1.0f / 3.0f);
		fireworksUI2->SetPositionTextureX(-1.0f / 3.0f);
		fireworksUI3->SetPositionTextureX(0.0f);

		break;
	}
}