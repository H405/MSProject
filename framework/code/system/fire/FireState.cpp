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
#define DELETECOUNT_MAX (80)
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
static const float effectSizeSmall = 5.0f;

//	生成する火花エフェクトの消えるまでの時間
static const int effectExistTime = 5;
static const int effectExistTimeRandom = (int)(effectExistTime * 0.9f);

static const int effectExistTimeSmall = 30;
static const int effectExistTimeRandomSmall = (int)(effectExistTime * 0.9f);

//	生成する火花エフェクトの大きさの差異
static const float effectDifferenceSize = -0.5f;
static const float effectDifferenceSizeSmall = -0.01f;

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
void FireStateBig::Update( Fire* _fireworks )
{
	FIRE_PARAM* param = _fireworks->getParam();


	param->pos += param->speed;
	param->speed *= 0.99f;


	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &param->pos, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;


	//	エフェクト生成
	_fireworks->getManagerPoint()->Add(
		effectExistTime + (int)RANDAM(effectExistTimeRandom),
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
		param->color,
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
void FireStateSmall::Update( Fire* _fireworks )
{
	//	パラメータへアクセス
	FIRE_PARAM* param = _fireworks->getParam();


	param->pos += param->speed;
	param->speed *= 0.99f;


	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &param->pos, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;


	//	エフェクト生成
	_fireworks->getManagerPoint()->Add(
		effectExistTimeSmall + (int)RANDAM(effectExistTimeRandomSmall),
		param->setPos,
		param->color,
		effectSizeSmall - ((effectSizeSmall / DELETECOUNT_MAX) * param->deleteCount),
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ),
		0.0f,
		ManagerPoint::STATE_ADD
		);


	//	カウンタ更新
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}
}
//	EOF