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
#define MOVE_COUNT_MAX (5)

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
static const float posRate = 160.0f;
static const float rotRate = D3DX_PI / 6.0f;
static const float rotOffset = 0.78399348f;
static const float defaultScale = 64.0f;
static const float addScale = 12.0f;

static const COLOR_STATE stateTable[FIREWORKS_UI_MAX] =
{
	COLOR_STATE_R,
	COLOR_STATE_G,
	COLOR_STATE_B,

	COLOR_STATE_R,
	COLOR_STATE_G,
	COLOR_STATE_B,

	COLOR_STATE_R,
	COLOR_STATE_G,
	COLOR_STATE_B,

	COLOR_STATE_R,
	COLOR_STATE_G,
	COLOR_STATE_B,
};

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
	fireworksUI = nullptr;

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = 0.0f;
	addRot = 0.0f;

	stateNum = 0;
	colorState = stateTable[stateNum];
	stateNumOld = stateNum;
	moveFlag = false;
	moveCount = 0;
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

	fireworksUI = new Object2D[FIREWORKS_UI_MAX];
	for(int count = 0;count < FIREWORKS_UI_MAX;count++)
	{
		fireworksUI[count].Initialize(0);
		fireworksUI[count].CreateGraphic(
			0,
			pParameter,
			pEffectGeneral,
			pFireworksUITex
		);
		fireworksUI[count].SetScale(defaultScale, defaultScale, 0.0f);

		//	setScaleTextureで、分割数を設定
		fireworksUI[count].SetScaleTexture(3.0f, 1.0f);
	}

	//	setPositionTextureで、0～1（丸め込む必要無し！）値を設定して、UVスクロールする
	fireworksUI[0].SetPositionTexture(0.0f, 0.0f);
	fireworksUI[1].SetPositionTexture(1.0f / 3.0f, 0.0f);
	fireworksUI[2].SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);
	fireworksUI[3].SetPositionTexture(0.0f, 0.0f);
	fireworksUI[4].SetPositionTexture(1.0f / 3.0f, 0.0f);
	fireworksUI[5].SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);
	fireworksUI[6].SetPositionTexture(0.0f, 0.0f);
	fireworksUI[7].SetPositionTexture(1.0f / 3.0f, 0.0f);
	fireworksUI[8].SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);
	fireworksUI[9].SetPositionTexture(0.0f, 0.0f);
	fireworksUI[10].SetPositionTexture(1.0f / 3.0f, 0.0f);
	fireworksUI[11].SetPositionTexture(1.0f / 3.0f * 2.0f, 0.0f);

	fireworksUI[0].AddScale(addScale * MOVE_COUNT_MAX, addScale * MOVE_COUNT_MAX, 0.0f);

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
	delete[] fireworksUI;

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
	if(moveFlag == true)
	{
		moveCount++;
		if(moveCount > MOVE_COUNT_MAX)
		{
			moveCount = 0;
			moveFlag = false;
		}
		else
		{
			rot += addRot;
			fireworksUI[stateNum].AddScale(addScale, addScale, 0.0f);
			fireworksUI[stateNumOld].AddScale(-addScale, -addScale, 0.0f);
		}
	}


	D3DXMATRIX transMatrix, transOffsetMatrix, rotMatrix;
	D3DXMATRIX outMatrix;

	for(int count = 0;count < FIREWORKS_UI_MAX;count++)
	{
		D3DXMatrixIdentity(&outMatrix);
		D3DXMatrixIdentity(&transMatrix);
		D3DXMatrixIdentity(&transOffsetMatrix);
		D3DXMatrixIdentity(&rotMatrix);

		//	オフセット値として、少しずらす
		D3DXMatrixTranslation(
			&transOffsetMatrix,
			0.0f,
			posRate,
			0.0f);

		D3DXMatrixMultiply(
			&outMatrix,
			&outMatrix,
			&transOffsetMatrix
			);


		//	移動した後に回転
		D3DXMatrixRotationYawPitchRoll(
			&rotMatrix,
			0.0f,
			0.0f,
			rot + (rotRate * count) + rotOffset);

		D3DXMatrixMultiply(
			&outMatrix,
			&outMatrix,
			&rotMatrix
			);


		//	共通の位置移動
		D3DXMatrixTranslation(
			&transMatrix,
			pos.x,
			pos.y,
			pos.z);

		D3DXMatrixMultiply(
			&outMatrix,
			&outMatrix,
			&transMatrix
			);

		fireworksUI[count].SetPosition(outMatrix._41, outMatrix._42, outMatrix._43);
	}

	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 位置セット処理
//==============================================================================
void FireworksUI::setPosition(float _x, float _y, float _z)
{
	pos.x = _x;
	pos.y = _y;
	pos.z = _z;

	// 基本クラスの処理
	ObjectMovement::Update();
}

//==============================================================================
// Brief  : 花火色情報セット処理
//==============================================================================
void FireworksUI::addRotColor()
{
	if(moveFlag == false)
	{
		stateNumOld = stateNum;

		stateNum--;
		if(stateNum <= -1)
			stateNum = FIREWORKS_UI_MAX - 1;

		colorState = stateTable[stateNum];

		moveFlag = true;

		addRot = (rotRate / (float)MOVE_COUNT_MAX);

	}
}
void FireworksUI::subRotColor()
{
	if(moveFlag == false)
	{
		stateNumOld = stateNum;

		stateNum++;
		if(stateNum >= FIREWORKS_UI_MAX)
			stateNum = 0;

		colorState = stateTable[stateNum];

		moveFlag = true;

		addRot = (-rotRate / (float)MOVE_COUNT_MAX);
	}
}



void FireworksUI::SetEnableGraphic(bool _flag)
{
	fireworksUI[0].SetEnableGraphic(_flag);
	fireworksUI[1].SetEnableGraphic(_flag);
	fireworksUI[2].SetEnableGraphic(_flag);
	fireworksUI[3].SetEnableGraphic(_flag);
	fireworksUI[4].SetEnableGraphic(_flag);
	fireworksUI[5].SetEnableGraphic(_flag);
	fireworksUI[6].SetEnableGraphic(_flag);
	fireworksUI[7].SetEnableGraphic(_flag);
	fireworksUI[8].SetEnableGraphic(_flag);
	fireworksUI[9].SetEnableGraphic(_flag);
	fireworksUI[10].SetEnableGraphic(_flag);
	fireworksUI[11].SetEnableGraphic(_flag);
}