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
#define APPEAR_COUNT_ARROW2 (80)
#define APPEAR_COUNT_CIRCLE (50)
#define DISAPPEAR_COUNT_MAX (200)

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
static const float targetSize = 50.0f;
static const float targetSizeBig = targetSize * 1.5f;
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
	targetCrossLocalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	targetArrowLocalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	targetCircleLocalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enable = false;
	counter = 0;
	fpUpdate = nullptr;
	D3DXMatrixIdentity(&invViewMatrix);
	colorState = COLOR_STATE_W;
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
int Target::Set(D3DXVECTOR3 _pos, COLOR_STATE _colorState)
{
	//	位置セット
	pos = _pos;
	targetCrossLocalPos = pos;
	targetArrowLocalPos = pos;
	targetCircleLocalPos = D3DXVECTOR3(pos.x + targetCrossDifferentPosition, pos.y + targetCrossDifferentPosition, pos.z);

	switch(0)
	{
	case 0:
		targetCircle->SetPosition(0.0f, 0.0f, 0.0f);
		targetArrow->SetPosition(0.0f, 0.0f, 0.0f);
		targetCross->SetPosition(0.0f, 0.0f, 0.0f);
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

	//	色変更
	colorState = _colorState;
	if(colorState == COLOR_STATE_R)
		targetCircle->SetColor(1.0f, 0.0f, 0.0f, 0.0f);
	else if(colorState == COLOR_STATE_G)
		targetCircle->SetColor(0.0f, 1.0f, 0.0f, 0.0f);
	else if(colorState == COLOR_STATE_B)
		targetCircle->SetColor(0.0f, 0.0f, 1.0f, 0.0f);
	else if(colorState == COLOR_STATE_W)
		targetCircle->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
	else if(colorState == COLOR_STATE_S)
	{
		targetCircle->SetColor(1.0f, 0.5f, 0.0f, 0.0f);

		//	スケール変更
		targetCross->SetScale(targetSizeBig, targetSizeBig, targetSizeBig);
		targetArrow->SetScale(targetSizeBig, targetSizeBig, targetSizeBig);
		targetCircle->SetScale(0.0f, 0.0f, 0.0f);
	}

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

	//	カメラの逆行列をかけて、常に一定の場所に出るようにする処理
	D3DXVECTOR4 setPos;

	D3DXVec3Transform(&setPos, &targetCrossLocalPos, &invViewMatrix);
	targetCross->SetPosition(setPos.x, setPos.y, setPos.z);

	D3DXVec3Transform(&setPos, &targetArrowLocalPos, &invViewMatrix);
	targetArrow->SetPosition(setPos.x, setPos.y, setPos.z);

	D3DXVec3Transform(&setPos, &targetCircleLocalPos, &invViewMatrix);
	targetCircle->SetPosition(setPos.x, setPos.y, setPos.z);
}
//==============================================================================
// Brief  : cross出現時の更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Target::updateAppearCross( void )
{
	//	位置変更
	targetCircleLocalPos +=
		D3DXVECTOR3(-targetCrossDifferentPosition / (float)APPEAR_COUNT_CROSS,
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
		if(colorState == COLOR_STATE_S)
			fpUpdate = &Target::updateAppearArrowBig;
		else
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
	if(counter < APPEAR_COUNT_ARROW2 / 2)
	{
		targetArrow->AddColorA(1.0f/ (float)(APPEAR_COUNT_ARROW2 / 2));
		targetArrow->AddRotationZ(D3DX_PI / (float)(APPEAR_COUNT_ARROW2 / 2));
	}
	if(counter > 20)
	{
		//	だんだんと出現
		targetCircle->AddColorA(1.0f / (float)(60));

		//	だんだん大きく
		float addSize = targetSize / (float)(60);
		targetCircle->AddScale(addSize, addSize, addSize);
	}

	counter++;
	if(counter == APPEAR_COUNT_ARROW2 / 2)
	{
		//	可視化
		targetCircle->SetEnableGraphic(true);
	}

	if(counter >= APPEAR_COUNT_ARROW2)
	{
		counter = 0;

		//	更新関数セット
		fpUpdate = &Target::updateDisAppear;
	}
}
void Target::updateAppearArrowBig( void )
{
	if(counter < APPEAR_COUNT_ARROW2 / 2)
	{
		targetArrow->AddColorA(1.0f/ (float)(APPEAR_COUNT_ARROW2 / 2));
		targetArrow->AddRotationZ(D3DX_PI / (float)(APPEAR_COUNT_ARROW2 / 2));
	}
	if(counter > 20)
	{
		//	だんだんと出現
		targetCircle->AddColorA(1.0f / (float)(60));

		//	だんだん大きく
		float addSize = targetSizeBig / (float)(60);
		targetCircle->AddScale(addSize, addSize, addSize);
	}

	counter++;
	if(counter == APPEAR_COUNT_ARROW2 / 2)
	{
		//	可視化
		targetCircle->SetEnableGraphic(true);
	}

	if(counter >= APPEAR_COUNT_ARROW2)
	{
		counter = 0;

		//	更新関数セット
		fpUpdate = &Target::updateDisAppear;
	}
}
//==============================================================================
// Brief  : Circle出現時の更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Target::updateAppearCircle( void )
{
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
void Target::updateAppearCircleBig( void )
{
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
	counter = 0;
	enable = false;

	//	不可視化
	targetCross->SetEnableGraphic(false);
	targetArrow->SetEnableGraphic(false);
	targetCircle->SetEnableGraphic(false);
}
//==============================================================================
// アクセサ
//==============================================================================
float Target::getScale()
{
	return targetSize;
}
