//==============================================================================
//
// File   : Fireworks.cpp
// Brief  : 花火オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Fireworks.h"
#include "FireworksState.h"
#include "../../system/point/ManagerPoint.h"
#include "../../system/point/PointMain.h"
#include "../../system/ManagerFireworks.h"
#include "../fire/Fire.h"
#include "../../framework/radianTable/radianTable.h"
#include "../../framework/light/ManagerLight.h"
#include "../../framework/light/LightPoint.h"
#include "../../framework/develop/DebugProc.h"
#include "../../framework/develop/DebugMeasure.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
//	ステートテーブル
FireworksState** Fireworks::ppState_ = nullptr;

static const int bigFireFirstSpeed = 10;
static const int fireBGExistTime = 50;
static const float fireBGAddSize = 5.0f;

static int createFireNum = 0;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Fireworks::Fireworks( void )
{
	// クラス内の初期化処理
	InitializeSelf();

	//	火花生成
	param.fire = new Fire[FIRE_MAX * SMALL_FIREWORKS_MAX];
	param.smallFire = new Fire[FIRE_MAX * SMALL_FIREWORKS_MAX];
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::InitializeSelf( void )
{
	// メンバ変数の初期化
	param.managerPoint = nullptr;
	param.pos = D3DXVECTOR3(createFireNum * 10.0f, 0.0f, 0.0f);
	param.setPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for(int count = 0;count < SMALL_FIREWORKS_MAX;count++)
		param.posOld[count] = D3DXVECTOR3(0.0f, -100.0f, 0.0f);

	param.rot = 0.0f;
	param.rotSpeed = 0.0f;
	param.speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = false;
	param.disappear = 0;
	param.appear = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	lightPoint = nullptr;

	indexState = 0;
	D3DXMatrixIdentity(&param.matrix);
	D3DXMatrixIdentity(&param.invViewMatrix);
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Fireworks::~Fireworks( void )
{
	// 終了処理
	Finalize();
}
//==============================================================================
// Brief  : ステートの設定
// Return : void								: なし
// Arg    : FireworksState** ppState				: ステートテーブル
//==============================================================================
void Fireworks::SetState( FireworksState** ppState )
{
	// ステートテーブルの設定
	ppState_ = ppState;
}
//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
//==============================================================================
int Fireworks::Set(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _speed,
	float _rot,
	float _rotSpeed )
{
	//	変数の保存と初期化
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.speed = _speed;
	param.rot = _rot;
	param.rotSpeed = _rotSpeed;

	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	indexState = _indexState;

	if(lightPoint == nullptr)
	{
		lightPoint = managerLight->GetLightPoint();
		lightPoint->SetDiffuse(1.0f, 0.0f, 1.0f);
		lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
		lightPoint->SetAttemuation(0.00f, 0.0006f, 0.00006f);
	}
	lightPoint->SetIsEnable(true);

	//	更新関数設定
	fpUpdate = &Fireworks::NormalUpdate;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Fireworks::Finalize( void )
{
	if(lightPoint != nullptr)
		lightPoint->Release();

	lightPoint = nullptr;

	delete[] param.smallFire;
	delete[] param.fire;

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
void Fireworks::Update( void )
{
	MeasureTime("fireworksUpdate");

	//	設定された更新関数へ
	(this->*fpUpdate)();

	lightPoint->SetPosition(param.setPos.x, param.setPos.y, param.setPos.z);
}
//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::NormalUpdate( void )
{
	//	ステート毎の更新処理へ
	ppState_[indexState]->Update(this);
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::BurnUpdate( void )
{
	int buffCount = 0;

	for(int count = 0;count < param.fireMax;count++)
	{
		if(!param.fire[count].IsEnable())
		{
			buffCount++;
			continue;
		}

		param.fire[count].setInvViewMatrix(param.invViewMatrix);
		param.smallFire[count].setInvViewMatrix(param.invViewMatrix);
		param.fire[count].Update();
		param.smallFire[count].Update();
	}

	PrintDebug( _T( "\ncountFire:Burn1 = %d\n"), param.fireMax - buffCount );

	if(buffCount == param.fireMax)
	{
		param.enable = false;
		lightPoint->SetIsEnable(false);
	}
}
//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::Burn2Update( void )
{
	int buffCount = 0;

	for(int count = 0;count < param.fireMax * param.setSmallFireIndex;count++)
	{
		if(!param.fire[count].IsEnable())
		{
			buffCount++;
			continue;
		}

		param.fire[count].setInvViewMatrix(param.invViewMatrix);
		param.smallFire[count].setInvViewMatrix(param.invViewMatrix);
		param.fire[count].Update();
		param.smallFire[count].Update();
	}

	PrintDebug( _T( "\ncountFire:Burn2 = %d\n"), param.fireMax * SMALL_FIREWORKS_MAX - buffCount );

	if(buffCount == param.fireMax * SMALL_FIREWORKS_MAX)
	{
		param.enable = false;
		lightPoint->SetIsEnable(false);
	}
}

//==============================================================================
// Brief  : 花火の爆発処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::burn(
	float _hitCheckOffset,
	float _hitPosLength)
{
	//	カメラの逆行列をかけて、常に一定の場所に出るようにする処理
	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &param.pos, &param.invViewMatrix);
	param.setPos.x = setPos.x;
	param.setPos.y = setPos.y;
	param.setPos.z = setPos.z;

	//	花火の数に応じた、１つの火花の角度間隔
	float buffValue = 0.0f;

	//	火花の最大数
	float fireSize;

	//	可
	if(_hitPosLength <= (_hitCheckOffset * 0.1f))
	{
		param.fireMax = FIRE_MAX;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 15.0f;
	}
	//	良
	else if(_hitPosLength <= (_hitCheckOffset * 0.3f))
	{
		param.fireMax = FIRE_MAX / 2;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 30.0f;
	}
	//	優
	else
	{
		param.fireMax = FIRE_MAX / 3;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 45.0f;
	}



	//	花火の背景用生成
	param.managerPoint->Add(
		fireBGExistTime,
		param.setPos,
		D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f),
		fireSize,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.02f ),
		fireBGAddSize,
		PointMain::STATE_ADD
		);

	//	火花の数だけループ
	for(int count = 0;count < param.fireMax;count++)
	{
		//	スピードをsin cosで計算
		float speedX = CRadianTable::mySinf((buffValue * count) + ((rand() % (int)buffValue) + (rand() % (int)buffValue)) * 0.5f);
		float speedY = CRadianTable::myCosf((buffValue * count) + ((rand() % (int)buffValue) + (rand() % (int)buffValue)) * 0.5f);

		//	ローカル頂点座標を計算
		D3DXVECTOR3 buffSetPos = D3DXVECTOR3(param.pos.x + speedX, param.pos.y + speedY, param.pos.z);

		//	大きい火花生成
		param.fire[count].Set(
			Fire::STATE_BIG,
			param.managerPoint,
			buffSetPos,
			D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.1f),
						(speedY * (float)(rand() % bigFireFirstSpeed) * 0.1f),
						0.0f),
			D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));


		//	小さい火花生成
		param.smallFire[count].Set(
			Fire::STATE_SMALL,
			param.managerPoint,
			buffSetPos,
			D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.13f),
						(speedY * (float)(rand() % bigFireFirstSpeed) * 0.13f),
						0.0f),
			D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));
	}



	//	更新関数設定
	fpUpdate = &Fireworks::BurnUpdate;

	//	破裂フラグON
	param.burnFlag = true;
}

//==============================================================================
// Brief  : 花火の爆発処理(予備・前Ver)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::burn2()
{
	for(int smallFireCount = 0;smallFireCount < param.setSmallFireIndex;smallFireCount++)
	{
		//	カメラの逆行列をかけて、常に一定の場所に出るようにする処理
		D3DXVECTOR4 setPos;
		D3DXVECTOR3 buffPos = param.posOld[smallFireCount];
		D3DXVec3Transform(&setPos, &buffPos, &param.invViewMatrix);
		param.setPos.x = setPos.x;
		param.setPos.y = setPos.y;
		param.setPos.z = setPos.z;

		//	花火の数に応じた、１つの火花の角度間隔
		float buffValue = 0.0f;

		//	火花の最大数
		float fireSize;


		//	強制的に優に設定
		param.fireMax = FIRE_MAX;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 15.0f;


		//	花火の背景用生成
		param.managerPoint->Add(
			fireBGExistTime,
			param.setPos,
			D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f),
			fireSize,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.02f ),
			fireBGAddSize,
			PointMain::STATE_ADD
			);


		//	火花の数だけループ
		for(int count = 0;count < param.fireMax;count++)
		{
			//	スピードをsin cosで計算
			float speedX = CRadianTable::mySinf((buffValue * count) + ((rand() % (int)buffValue) + (rand() % (int)buffValue)) * 0.5f);
			float speedY = CRadianTable::myCosf((buffValue * count) + ((rand() % (int)buffValue) + (rand() % (int)buffValue)) * 0.5f);

			//	ローカル頂点座標を計算
			D3DXVECTOR3 buffSetPos = D3DXVECTOR3(buffPos.x + speedX, buffPos.y + speedY, buffPos.z);

			//	大きい火花生成
			param.fire[count + (FIRE_MAX * smallFireCount)].Set(
				Fire::STATE_BIG,
				param.managerPoint,
				buffSetPos,
				D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.1f),
							(speedY * (float)(rand() % bigFireFirstSpeed) * 0.1f),
							0.0f),
				D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));


			//	小さい火花生成
			param.smallFire[count + (FIRE_MAX * smallFireCount)].Set(
				Fire::STATE_SMALL,
				param.managerPoint,
				buffSetPos,
				D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.13f),
							(speedY * (float)(rand() % bigFireFirstSpeed) * 0.13f),
							0.0f),
				D3DXCOLOR(1.0f, 0.25f, 0.0f, 1.0f));
		}
	}


	//	更新関数設定
	fpUpdate = &Fireworks::Burn2Update;

	//	破裂フラグON
	param.burnFlag = true;
}

void Fireworks::setManagerLight(ManagerLight* _managerLight)
{
	managerLight = _managerLight;
}
