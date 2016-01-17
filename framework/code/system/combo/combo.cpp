//==============================================================================
//
// File   : Combo.cpp
// Brief  : コンボオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "combo.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerTexture.h"
#include "../../object/Object2D.h"
#include "../../object/ObjectScore.h"
#include "../../framework/develop/DebugProc.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define FLASHING_COUNT_MAX (10)
#define RANDAM(value) ((rand() % value) - (rand() % value))

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
static const float addAlpha = -0.005f;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Combo::Combo( void ) : ObjectMovement()
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Combo::InitializeSelf( void )
{
	comboString = nullptr;
	comboScore = nullptr;
	comboSya = nullptr;

	score = 0;
	scorePrev = 0;
	scoreMax = 0;
	flashingCount = 0;
	alpha = 0.0f;
	startFlag = false;

	// メンバ変数の初期化
	fpUpdate = nullptr;
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Combo::~Combo( void )
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
int Combo::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pComboSya,
	Texture* pComboString,
	Texture* pComboScore)
{
	// 基本クラスの処理
	int		result;		// 実行結果
	result = Object::Initialize( 0 );
	if( result != 0 )
	{
		return result;
	}


	//	シャッ　テクスチャ
	comboSya = new Object2D();
	comboSya->Initialize(0);
	comboSya->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pComboSya
		);
	comboSya->SetScale(224.0f, 56.0f, 0.0f);


	//	「連発」文字テクスチャ
	comboString = new Object2D();
	comboString->Initialize(0);
	comboString->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pComboString
		);
	comboString->SetScale(96.0f, 48.0f, 0.0f);
	comboString->SetScaleTexture(8.0f, 16.0f);
	comboString->SetPositionTexture(1.0f / 8.0f * 2.0f, 1.0f / 16.0f * 4.0f);


	//	スコア
	comboScore = new ObjectScore();
	comboScore->Initialize(0, 2);
	comboScore->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pComboScore);
	comboScore->SetSizeX(64.0f);
	comboScore->SetSizeY(64.0f);
	comboScore->setAlphaFlag(true);
	comboScore->setAlphaSPFlag(true);


	comboSya->SetColorA(0.0f);
	comboString->SetColorA(0.0f);
	comboScore->SetColorA(0.0f);


	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Combo::Finalize( void )
{
	delete comboScore;
	delete comboString;
	delete comboSya;

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
void Combo::Update( void )
{
	if(startFlag == true)
	{
		scorePrev = score;

		if(alpha > 0.0f)
		{
			flashingCount++;
			alpha += addAlpha;

			if(flashingCount == (FLASHING_COUNT_MAX / 2))
			{
				comboSya->SetColorA(alpha);
				comboString->SetColorA(alpha);
				comboScore->SetColorA(alpha);
				comboScore->setAlphaSP(alpha);

				comboScore->desideScoreSP(alpha);
			}
			else if(flashingCount == FLASHING_COUNT_MAX)
			{
				flashingCount = 0;

				comboSya->SetColorA(0.0f);
				comboString->SetColorA(0.0f);
				comboScore->SetColorA(0.0f);
			}
		}

		// 基本クラスの処理
		ObjectMovement::Update();
	}
}
void Combo::firstUpdate()
{
	comboScore->desideScoreSP(alpha);
	comboSya->SetColorA(0.0f);
	comboString->SetColorA(0.0f);
	comboScore->SetColorA(0.0f);
}
//==============================================================================
// Brief  : 位置セット処理
//==============================================================================
void Combo::setPosition(float _x, float _y, float _z)
{
	comboString->SetPosition(_x + 134.0f, _y - 8.0f, _z);
	comboSya->SetPosition(_x + 112.0f, _y - 32.0f, _z);

	comboScore->SetPos(_x, _y, _z);

	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : アクセサ
//==============================================================================
void Combo::addScore()
{
	if(alpha <= 0.0f)
	{
		flashingCount = 0;
		score = 0;
	}

	alpha = 1.0f;
	score++;

	if(score > scoreMax)
		scoreMax = score;

	comboScore->SetScore(score);
	comboScore->SetScoreFuture(score);

	// 基本クラスの処理
	ObjectMovement::Update();
}
void Combo::setColor(D3DXCOLOR _color)
{
	comboScore->SetColor(_color.r, _color.g, _color.b, _color.a);
	comboSya->SetColor(_color.r, _color.g, _color.b, _color.a);
	comboString->SetColor(_color.r, _color.g, _color.b, _color.a);
}