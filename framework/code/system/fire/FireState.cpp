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
static const float effectSize = 30.0f;
static const float effectSizeSmall = 5.0f;

//	生成する火花エフェクトの消えるまでの時間
static const int effectExistTime = 5;
static const int effectExistTimeRandom = (int)(effectExistTime * 0.9f);

static const int effectExistTimeSmall = 5;
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










	/*避難　　行列も減ったくれもなしVer
	//------------------------------------------------------------
	//	回転量加算
	param->rot += param->rotSpeed;

	if(param->rot < 0.0f)
		param->rot = 0.0f;
	else if(param->rot > 180.0f)
	{
		param->rot = 180.0f;
	}

	//	速度計算
	param->speed *= 0.999f;

	//	位置情報加算
	param->offsetPos.x += (CRadianTable::mySinf((double)param->rot) * param->speed.x);
	param->offsetPos.y += (CRadianTable::myCosf((double)param->rot) * param->speed.y);



	for(int count = 0;count < 2;count++)
	{
		//	花火移動用行列初期化
		D3DXMatrixIdentity(&param->matrix);

		//	行列で位置を３次元的に回転
		D3DXVECTOR4 buffPos;
		D3DXVECTOR3 buffPos3(param->offsetPos.x + FIRE_APPEAR_RANDAM, param->offsetPos.y + FIRE_APPEAR_RANDAM, param->offsetPos.z + FIRE_APPEAR_RANDAM);

		//	平行移動
		D3DXMatrixTranslation(
			&param->matrix,
			param->pos.x,
			param->pos.y,
			param->pos.z);

		D3DXVec3Transform(&buffPos, &buffPos3, &param->matrix);
		buffPos3.x = buffPos.x;
		buffPos3.y = buffPos.y;
		buffPos3.z = buffPos.z;


		//	カメラの逆行列をかけて、常に一定の場所に出るようにする処理
		D3DXVECTOR4 setPos;
		D3DXVec3Transform(&setPos, &buffPos3, &param->invViewMatrix);
		param->setPos.x = setPos.x;
		param->setPos.y = setPos.y;
		param->setPos.z = setPos.z;



		//	エフェクト生成
		_fireworks->getManagerPoint()->Add(
			effectExistTime + (int)RANDAM(effectExistTimeRandom),
			D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
			D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
			effectSize - ((effectSize / DELETECOUNT_MAX) * param->deleteCount),
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ),
			effectDifferenceSize,
			ManagerPoint::STATE_ADD
			);
	}

	//	カウンタ更新
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}
	//------------------------------------------------------------



	/*避難　　行列での位置操作前
	//------------------------------------------------------------
	//	パラメータへアクセス
	FIRE_PARAM* param = _fireworks->getParam();


	//	花火移動用行列初期化
	D3DXMatrixIdentity(&param->matrix);

	//	回転
	D3DXMatrixRotationYawPitchRoll(
		&param->matrix,
		param->matRot.y,
		param->matRot.x,
		param->matRot.z);



	//	回転量加算.
	param->rot += param->rotSpeed;

	if(param->rot < 0.0f)
		param->rot = 0.0f;
	else if(param->rot > 180.0f)
	{
		param->rot = 180.0f;
		//param->speed.y -= 0.1f;
	}

	//	速度計算
	param->speed *= 0.999f;

	//	位置情報加算
	param->pos.x += (CRadianTable::mySinf((double)param->rot) * param->speed.x);
	param->pos.y += (CRadianTable::myCosf((double)param->rot) * param->speed.y);
	//param->pos.z += param->speed.z;



	//	行列で位置を３次元的に回転
	D3DXVECTOR4 buffPos;
	D3DXVECTOR3 buffPos3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM);
	D3DXVec3Transform(&buffPos, &buffPos3, &param->matrix);
	buffPos3.x = buffPos.x;
	buffPos3.y = buffPos.y;
	buffPos3.z = buffPos.z;


	//	カメラの逆行列をかけて、常に一定の場所に出るようにする処理
	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &buffPos3, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;



	//	エフェクト生成
	_fireworks->getManagerPoint()->Add(
		effectExistTime + (int)RANDAM(effectExistTimeRandom),
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
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
	*/
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
		effectDifferenceSizeSmall,
		ManagerPoint::STATE_ADD
		);


	//	カウンタ更新
	param->deleteCount++;
	if(param->deleteCount >= DELETECOUNT_MAX)
	{
		param->enable = false;
	}


	/*避難　　行列も減ったくれもなしVer
	//------------------------------------------------------------
	//	花火移動用行列初期化
	D3DXMatrixIdentity(&param->matrix);

	//	回転
	D3DXMatrixRotationYawPitchRoll(
		&param->matrix,
		param->matRot.y,
		param->matRot.x,
		param->matRot.z);


	//	回転量加算
	param->rot -= param->rotSpeed;

	if(param->rot < 180.0f)
		param->rot = 180.0f;
	else if(param->rot > 360.0f)
	{
		param->rot = 360.0f;
		//param->speed.y -= 0.1f;
	}

	//	速度計算
	param->speed *= 0.999f;

	//	位置情報加算
	param->pos.x += (CRadianTable::mySinf((double)param->rot) * param->speed.x);
	param->pos.y += (CRadianTable::myCosf((double)param->rot) * param->speed.y);
	//param->pos.z += param->speed.z;



	//	行列で位置を３次元的に回転
	D3DXVECTOR4 buffPos;
	D3DXVECTOR3 buffPos3(param->pos.x + FIRE_APPEAR_RANDAM, param->pos.y + FIRE_APPEAR_RANDAM, param->pos.z + FIRE_APPEAR_RANDAM);
	D3DXVec3Transform(&buffPos, &buffPos3, &param->matrix);
	buffPos3.x = buffPos.x;
	buffPos3.y = buffPos.y;
	buffPos3.z = buffPos.z;


	//	カメラの逆行列をかけて、常に一定の場所に出るようにする処理
	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &buffPos3, &param->invViewMatrix);
	param->setPos.x = setPos.x;
	param->setPos.y = setPos.y;
	param->setPos.z = setPos.z;



	//	エフェクト生成
	_fireworks->getManagerPoint()->Add(
		effectExistTime + (int)RANDAM(effectExistTimeRandom),
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
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
	}*/
	//------------------------------------------------------------
}
//	EOF