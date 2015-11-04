//==============================================================================
//
// File   : Target.cpp
// Brief  : ターゲットオブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Target.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerTexture.h"
#include "../../object/ObjectBillboard.h"
#include "../../system/ManagerTarget.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define DELETECOUNT_MAX (1000)
#define RANDAM(value) ((rand() % value) - (rand() % value))

#define APPEAR_COUNT_CROSS (50)
#define APPEAR_COUNT_ARROW (25)
#define APPEAR_COUNT_CIRCLE (50)
#define DISAPPEAR_COUNT_MAX (200)

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
static const float targetSize = 32.0f;
static const float targetCrossDifferentPosition = -50.0f;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Target::Target( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Target::InitializeSelf( void )
{
	// メンバ変数の初期化
	targetCross = nullptr;
	targetArrow = nullptr;
	targetCircle = nullptr;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enable = false;
	counter = 0;
	fpUpdate = nullptr;
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Target::~Target( void )
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
int Target::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pTextureCross,
	Texture* pTextureArrow,
	Texture* pTextureCircle)
{
	//	オブジェクトの生成開始
	targetCircle = new ObjectBillboard;
	targetCircle->Initialize(0);
	targetCircle->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pTextureCircle
		);
	targetCircle->SetEnableGraphic(false);


	targetCross = new ObjectBillboard;
	targetCross->Initialize(0);
	targetCross->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pTextureCross
		);
	targetCross->SetEnableGraphic(false);


	targetArrow = new ObjectBillboard;
	targetArrow->Initialize(0);
	targetArrow->CreateGraphic(
		0,
		pParameter,
		pEffectGeneral,
		pTextureArrow
		);
	targetArrow->SetEnableGraphic(false);


	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int Target::Set(D3DXVECTOR3 _pos)
{
	//	位置セット
	pos = _pos;

	switch(0)
	{
	case 0:
		targetCircle->SetPosition(pos.x, pos.y, pos.z);
		targetArrow->SetPosition(pos.x, pos.y, pos.z);
		targetCross->SetPosition(pos.x + targetCrossDifferentPosition, pos.y + targetCrossDifferentPosition, pos.z);
		break;
	}

	//	可視化
	targetCross->SetEnableGraphic(true);

	//	色初期化
	targetCircle->SetColorAlpha(0.0f);
	targetArrow->SetColorAlpha(0.0f);
	targetCross->SetColorAlpha(0.0f);

	//	回転量初期化
	targetCircle->SetRotation(0.0f, 0.0f, 0.0f);
	targetArrow->SetRotation(0.0f, 0.0f, 0.0f);
	targetCross->SetRotation(0.0f, 0.0f, 0.0f);

	//	スケール変更
	targetCross->SetScale(targetSize, targetSize, targetSize);
	targetArrow->SetScale(targetSize, targetSize, targetSize);
	targetCircle->SetScale(0.0f, 0.0f, 0.0f);

	//	各種変数初期化
	enable = true;
	counter = 0;

	//	更新関数セット
	fpUpdate = &Target::updateAppearCross;

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Target::Finalize( void )
{
	delete targetCircle;
	delete targetArrow;
	delete targetCross;

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
void Target::Update( void )
{
	//	設定された更新関数へ
	(this->*fpUpdate)();
}
//==============================================================================
// Brief  : cross出現時の更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Target::updateAppearCross( void )
{
	//	位置変更
	targetCross->AddPosition(
		-targetCrossDifferentPosition / (float)APPEAR_COUNT_CROSS,
		-targetCrossDifferentPosition / (float)APPEAR_COUNT_CROSS,
		0.0f);

	//	だんだんと出現
	if(counter < APPEAR_COUNT_CROSS / 2)
		targetCross->AddColorAlpha(1.0f / (float)(APPEAR_COUNT_CROSS / 2));

	//	カウンタで動き制御
	counter++;
	if(counter >= APPEAR_COUNT_CROSS)
	{
		counter = 0;

		//	可視化
		targetArrow->SetEnableGraphic(true);

		//	更新関数セット
		fpUpdate = &Target::updateAppearArrow;
	}
}
//==============================================================================
// Brief  : Arrow出現時の更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Target::updateAppearArrow( void )
{
	targetArrow->AddRotationZ(D3DX_PI / (float)APPEAR_COUNT_ARROW);

	//	だんだんと出現
	if(counter < APPEAR_COUNT_ARROW / 2)
		targetArrow->AddColorA(1.0f/ (float)(APPEAR_COUNT_ARROW / 2));

	//	カウンタで動き制御
	counter++;
	if(counter >= APPEAR_COUNT_ARROW)
	{
		counter = 0;

		//	可視化
		targetCircle->SetEnableGraphic(true);

		//	更新関数セット
		fpUpdate = &Target::updateAppearCircle;
	}
}
//==============================================================================
// Brief  : Circle出現時の更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Target::updateAppearCircle( void )
{
	//targetCircle->AddRotationZ(D3DX_PI / (float)APPEAR_COUNT_CIRCLE);

	if(counter < APPEAR_COUNT_CIRCLE / 2)
	{
		//	だんだんと出現
		targetCircle->AddColorA(1.0f / (float)(APPEAR_COUNT_CIRCLE / 2));

		//	だんだん大きく
		float addSize = targetSize / (float)(APPEAR_COUNT_CIRCLE / 2);
		targetCircle->AddScale(addSize, addSize, addSize);
	}

	//	カウンタで動き制御
	counter++;
	if(counter >= APPEAR_COUNT_CIRCLE)
	{
		counter = 0;

		//	更新関数セット
		fpUpdate = &Target::updateDisAppear;
	}
}
//==============================================================================
// Brief  : 消滅時の更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Target::updateDisAppear( void )
{
	//targetCross->AddRotationX(-1.0f / (float)DISAPPEAR_COUNT_MAX);
	//targetArrow->AddRotationY(-1.0f / (float)DISAPPEAR_COUNT_MAX);
	//targetCircle->AddRotationZ(-1.0f / (float)DISAPPEAR_COUNT_MAX);

	//	だんだんと消す
	targetCross->AddColorAlpha(-1.0f / (float)DISAPPEAR_COUNT_MAX);
	targetArrow->AddColorAlpha(-1.0f / (float)DISAPPEAR_COUNT_MAX);
	targetCircle->AddColorAlpha(-1.0f / (float)DISAPPEAR_COUNT_MAX);

	//	カウンタで動き制御
	counter++;
	if(counter >= DISAPPEAR_COUNT_MAX)
	{
		counter = 0;
		enable = false;

		//	不可視化
		targetCross->SetEnableGraphic(false);
		targetArrow->SetEnableGraphic(false);
		targetCircle->SetEnableGraphic(false);
	}
}
//==============================================================================
// Brief  : ターゲットの消滅処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Target::Dissappear()
{
	Finalize();
}
