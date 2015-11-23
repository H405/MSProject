//==============================================================================
//
// File   : FireworksState.cpp
// Brief  : 花火のステート
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "FireworksState.h"
#include "Fireworks.h"
#include "../../system/ManagerPoint.h"
#include "../../framework/radianTable/radianTable.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define DELETECOUNT_MAX (200)
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

//	生成する花火エフェクトの大きさ
static const float effectSize = 30.0f;

//	生成する花火エフェクトの消えるまでの時間
static const int effectExistTime = 50;

//	生成する花火エフェクトの大きさの差異
static const float effectDifferenceSize = -0.2f;

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : Fireworks* pFireworks						: 対象
//==============================================================================
void FireworksState::Update( Fireworks* _fireworks )
{
	// 消滅
	//if( pFireworks->GetTime() >= pFireworks->GetTimeExist() )
	//{
	//	pFireworks->SetIsEnable( false );
	//}
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : Fireworks* pFireworks						: 対象
//==============================================================================
void FireworksStateRight::Update( Fireworks* _fireworks )
{
	//	パラメータへアクセス
	FIREWORKS_PARAM* param = _fireworks->getParam();


	//	花火移動用行列初期化
	D3DXMatrixIdentity(&param->matrix);

	//	回転
	D3DXMatrixRotationYawPitchRoll(
		&param->matrix,
		param->matRot.y,
		param->matRot.x,
		param->matRot.z);


	//	正の向きとしたときの移動方向修正処理
	param->rot += param->rotSpeed;

	//	回転量加算
	/*if(param->rot < 0)
		param->rot = 0.0f;
	else if(param->rot > 90)
		param->rot = 90.0f;*/

	param->rotSpeed *= 0.99f;

	//	位置情報加算(90度が真っ直ぐ上がるとする)
	param->pos.x += CRadianTable::myCosf((double)param->rot) * param->speed.x;
	param->pos.y += CRadianTable::mySinf((double)param->rot) * param->speed.y + 1.0f;
	param->pos.z += param->speed.z;


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
	param->managerPoint->Add(
		effectExistTime,
		D3DXVECTOR3(param->setPos.x, param->setPos.y, param->setPos.z),
		D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f ),
		effectSize,
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
// Arg    : Fireworks* pFireworks						: 対象
//==============================================================================
void FireworksStateLeft::Update( Fireworks* _fireworks )
{
	//	パラメータへアクセス
	FIREWORKS_PARAM* param = _fireworks->getParam();

	//	回転量加算
	param->rot += param->rotSpeed;
	if(param->rot > 0)
		param->rot = 0.0f;
	else if(param->rot < -90)
		param->rot = -90.0f;

	//	位置情報加算
	param->pos.x += (CRadianTable::mySinf((double)param->rot) * param->speed.x);
	param->pos.y += (CRadianTable::myCosf((double)param->rot) * param->speed.y) + 1.0f;
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
