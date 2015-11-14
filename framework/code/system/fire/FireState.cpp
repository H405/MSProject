//==============================================================================
//
// File   : FireState.cpp
// Brief  : 火花のステート
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "FireState.h"
#include "Fire.h"
#include "../../system/ManagerPoint.h"
#include "../../framework/radianTable/radianTable.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define FIRE_MAX (36)
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define DELETECOUNT_MAX (100)
#define RANDAM(value) (float)((rand() % value) - (rand() % value))
#define FIRE_APPEAR_RANDAM (RANDAM(100) * 0.01f)

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//	生成する火花の数
static const int fireNum[] =
{
	FIRE_MAX,	//	優
	FIRE_MAX / 2,	//	良
	FIRE_MAX / 4	//	可
};

//	生成する火花エフェクトの大きさ
static const float effectSize = 15.0f;

//	生成する火花エフェクトの消えるまでの時間
static const int effectExistTime = 50;

//	生成する火花エフェクトの大きさの差異
static const float effectDifferenceSize = -0.2f;

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : Fire* pFire						: 対象
//==============================================================================
void FireState::Update( Fire* _fireworks )
{
	// 消滅
	//if( pFire->GetTime() >= pFire->GetTimeExist() )
	//{
	//	pFire->SetIsEnable( false );
	//}
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : Fire* pFire						: 対象
//==============================================================================
void FireStateNormal::Update( Fire* _fireworks )
{
	//	パラメータへアクセス
	FIRE_PARAM* param = _fireworks->getParam();

	//	回転量加算.
	param->rot += param->rotSpeed;

	//	位置情報加算.
	float f1 = sinf(param->rot);
	float f2 = cosf(param->rot);
	param->pos.x += (CRadianTable::mySinf(param->rot) * param->speed.x);
	param->pos.y += (CRadianTable::myCosf(param->rot) * param->speed.y);
	param->pos.z += param->speed.z;

	//	エフェクト生成
	_fireworks->getManagerPoint()->Add(
		effectExistTime,
		D3DXVECTOR3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM),
		D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		effectSize - ((effectSize / DELETECOUNT_MAX) * param->deleteCount),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ),
		effectDifferenceSize,
		ManagerPoint::STATE_ADD
		);

	//	カウンタ更新
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}
}
//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : Fire* pFire						: 対象
//==============================================================================
void FireStateSlow::Update( Fire* _fireworks )
{
	//	パラメータへアクセス
	FIRE_PARAM* param = _fireworks->getParam();

	//	回転量加算
	param->rot -= param->rotSpeed;

	//	位置情報加算
	param->pos.x += (CRadianTable::mySinf(param->rot) * param->speed.x);
	param->pos.y += (CRadianTable::myCosf(param->rot) * param->speed.y) + 0.5f;
	param->pos.z += param->speed.z;

	//	エフェクト生成
	_fireworks->getManagerPoint()->Add(
		effectExistTime,
		D3DXVECTOR3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM),
		D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ),
		effectSize - ((effectSize / DELETECOUNT_MAX) * param->deleteCount),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ),
		effectDifferenceSize,
		ManagerPoint::STATE_ADD
		);

	//	カウンタ更新
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}
}
