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
#include "../../scene/SceneGame.h"
#include "../../framework/system/Utility.h"
#include "../target/Target.h"

#include "../SceneArgumentMain.h"
#include "../../framework/resource/ManagerSound.h"
#include "../../framework/resource/Sound.h"

#include <stdio.h>

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define RANDAM(value) (float)((rand() % value) - (rand() % value))

//******************************************************************************
// 静的メンバ変数
//******************************************************************************
//	ステートテーブル
FireworksState** Fireworks::ppState_ = nullptr;

static const int bigFireFirstSpeed = 10;
static const int fireBGExistTime = 50;

static const float fireBGAddSize = 5.0f;

static int createFireNum = 0;

static const D3DXVECTOR3 attenuationValue = D3DXVECTOR3(0.0f, 0.00028f, 0.00000005f);

static const TIME compAppear = (int)(DELETECOUNT_MAX * 0.9f);
static const TIME compDisppear = (int)(DELETECOUNT_MAX);


static const TIME compLaunchAppear = (int)(DELETECOUNT_MAX * 0.5f);
static const TIME compLaunchDisppear = (int)(DELETECOUNT_MAX);

static const float diffRotMul = 16.0f;

static const float fireSpeed = 3.0f;

static const float mainColor = 1.0f;
static const float subColor = 0.15f;

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
	param.fire = new Fire[FIRE_XZ_MAX * FIRE_Y_MAX * SMALL_FIREWORKS_MAX];
	//param.smallFire = new Fire[FIRE_XZ_MAX * FIRE_Y_MAX * SMALL_FIREWORKS_MAX];

	burnSoundIndex = -1;
	launchSoundIndex = -1;
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
	param.burnSPFlag = false;

	param.lightPoint = nullptr;

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

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(1.0f, 1.0f, 0.5f);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetAttenuation(0.0f, 0.0028f, 0.00005f);
	//param.lightPoint->SetIsEnable(true);


	//	音再生
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();


	//	更新関数設定
	fpUpdate = &Fireworks::NormalUpdate;

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 花火あげる処理(wiiリモコンの情報に応じて)
// Return : int									: 実行結果
//==============================================================================
int Fireworks::Set(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _diffRot,
	COLOR_STATE _colorState)
{
	//	変数の保存と初期化
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	//	色情報
	param.colorState = _colorState;
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(mainColor, subColor, subColor, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(subColor, mainColor, subColor, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(subColor, subColor, mainColor, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	indexState = _indexState;

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(param.color);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetDiffuse(param.color);
	param.lightPoint->SetAttenuation(0.0f, 0.00028f, 0.0000005f);
	param.lightPoint->SetIsEnable(true);

	//	音再生
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();

	//	更新関数設定
	fpUpdate = &Fireworks::NormalUpdate;



	//	endの上限値は、yが200くらい、xが-200～200くらい？
	param.startPos = _pos;
	//param.buffPos1 = D3DXVECTOR3(_pos.x - (_diffRot.z * (diffRotMul * 0.25f)), 450.0f, _pos.z + 2000.0f);
	//param.endPos = D3DXVECTOR3(_pos.x - (_diffRot.z * diffRotMul), 650.0f, _pos.z + 4500.0f);
	param.buffPos1 = D3DXVECTOR3(_pos.x - (_diffRot.z * (diffRotMul * 0.3f)), 140.0f, _pos.z);
	param.endPos = D3DXVECTOR3(_pos.x - (_diffRot.z * diffRotMul), 200.0f, _pos.z);

	param.count = 0;
	param.burnSPFlag = false;
	param.deleteCountMax = DELETECOUNT_MAX;

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 花火あげる処理(コンボ数に応じて)
// Return : int									: 実行結果
//==============================================================================
int Fireworks::SetSP(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _diffRot,
	COLOR_STATE _colorState)
{
	//	変数の保存と初期化
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	//	色情報
	param.colorState = _colorState;
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	indexState = _indexState;

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(param.color);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetDiffuse(param.color);
	param.lightPoint->SetAttenuation(0.0f, 0.0028f, 0.0000005f);
	param.lightPoint->SetIsEnable(true);

	//	音再生
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();

	//	更新関数設定
	fpUpdate = &Fireworks::NormalUpdate;



	//	endの上限値は、yが200くらい、xが-200～200くらい？
	param.startPos = _pos;
	param.buffPos1 = D3DXVECTOR3(_pos.x - (_diffRot.z * (diffRotMul * 0.25f)), 100.0f, _pos.z);
	param.endPos = D3DXVECTOR3(_pos.x - (_diffRot.z * diffRotMul), 130.0f, _pos.z);

	param.count = 0;
	param.burnSPFlag = true;
	param.deleteCountMax = DELETECOUNT_MAX;

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 花火あげる処理(ターゲットへ向かって)
// Return : int									: 実行結果
//==============================================================================
int Fireworks::Set(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _diffRot,
	Target* _target)
{
	//	変数の保存と初期化
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	//	色情報
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↓
///////////////////////////////////////////////////////////////////////////////
#if 1
	param.colorState = _target->getColorState();
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(mainColor, subColor, subColor, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(subColor, mainColor, subColor, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(subColor, subColor, mainColor, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
#else
	param.colorState = _target->getColorState();
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(1.0f, 0.4f, 0.3f, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(0.3f, 1.0f, 0.4f, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(0.4f, 0.3f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
#endif
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↑
///////////////////////////////////////////////////////////////////////////////

	indexState = _indexState;

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(param.color);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetDiffuse(param.color);
	param.lightPoint->SetAttenuation(7.0f * attenuationValue);
	param.lightPoint->SetIsEnable(true);

	//	音再生
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();

	//	更新関数設定
	fpUpdate = &Fireworks::NormalUpdate;



	//	endの上限値は、yが200くらい、xが-200～200くらい？
	param.startPos = _pos;
	param.buffPos1 = D3DXVECTOR3(_pos.x + (_target->getPosition().x - _pos.x) * 0.3f, _pos.y + (_target->getPosition().y - _pos.y) * 0.7f, _pos.z);
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↓
///////////////////////////////////////////////////////////////////////////////
#if 1
	param.endPos = D3DXVECTOR3(_target->getPosition().x, _target->getPosition().y, _pos.z);
#else
	param.endPos = D3DXVECTOR3(_target->getPosition().x, _target->getPosition().y + 550.0f, _pos.z + 3000.0f);
#endif
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↑
///////////////////////////////////////////////////////////////////////////////

	param.count = 0;
	param.burnSPFlag = false;
	param.deleteCountMax = DELETECOUNT_MAX / 2;

///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川追加 ↓
///////////////////////////////////////////////////////////////////////////////
	timerForLight = 0;
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川追加 ↑
///////////////////////////////////////////////////////////////////////////////

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 花火あげる処理
// Return : int									: 実行結果
//==============================================================================
int Fireworks::SetW(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _diffRot,
	Target* _target)
{
	//	変数の保存と初期化
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	//	色情報
	param.colorState = (COLOR_STATE)(rand() % COLOR_STATE_W);
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(mainColor, subColor, subColor, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(subColor, mainColor, subColor, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(subColor, subColor, mainColor, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	indexState = _indexState;

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(param.color);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetDiffuse(param.color);
	param.lightPoint->SetAttenuation(0.0f, 0.0028f, 0.0000005f);
	param.lightPoint->SetIsEnable(true);

	//	音再生
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();

	//	更新関数設定
	fpUpdate = &Fireworks::NormalUpdate;



	//	endの上限値は、yが200くらい、xが-200～200くらい？
	param.startPos = _pos;
	param.buffPos1 = D3DXVECTOR3(_pos.x + (_target->getPosition().x - _pos.x) * 0.3f, _pos.y + (_target->getPosition().y - _pos.y) * 0.7f, _pos.z);
	param.endPos = D3DXVECTOR3(_target->getPosition().x, _target->getPosition().y, _pos.z);

	param.count = 0;
	param.deleteCountMax = DELETECOUNT_MAX / 2;

	// 正常終了
	return 0;
}
//==============================================================================
// Brief  : 花火あげる処理
// Return : int									: 実行結果
//==============================================================================
int Fireworks::SetW(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _diffRot,
	Target* _target,
	int _near)
{
	//	変数の保存と初期化
	param.managerPoint = _managerPoint;
	param.pos = _pos;
	param.matRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = true;
	param.burnFlag = false;
	param.disappear = 0;
	param.fireMax = 0;
	param.smallFireMax = 0;
	param.setSmallFireIndex = 0;
	param.setPosOld = 0;

	//	色情報
	param.colorState = (COLOR_STATE)(rand() % COLOR_STATE_W);
	if(param.colorState == COLOR_STATE_R)
		param.color = D3DXCOLOR(mainColor, subColor, subColor, 1.0f);
	else if(param.colorState == COLOR_STATE_G)
		param.color = D3DXCOLOR(subColor, mainColor, subColor, 1.0f);
	else if(param.colorState == COLOR_STATE_B)
		param.color = D3DXCOLOR(subColor, subColor, mainColor, 1.0f);
	else if(param.colorState == COLOR_STATE_W)
		param.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	else if(param.colorState == COLOR_STATE_S)
		param.color = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);

	indexState = _indexState;

	if(param.lightPoint == nullptr)
	{
		param.lightPoint = managerLight->GetLightPoint();
		param.lightPoint->SetDiffuse(param.color);
		param.lightPoint->SetSpecular(1.0f, 1.0f, 1.0f);
	}
	param.lightPoint->SetDiffuse(param.color);
	param.lightPoint->SetAttenuation(0.0f, 0.0028f, 0.0000005f);
	param.lightPoint->SetIsEnable(true);

	//	音再生
	burnSoundIndex = -1;
	launchSoundIndex = -1;
	launchSoundIndex = param.launchSound->Play();

	//	更新関数設定
	fpUpdate = &Fireworks::NormalUpdate;



	//	endの上限値は、yが200くらい、xが-200～200くらい？
	if(_near == 0)
	{
		param.startPos = _pos;
		param.buffPos1 = D3DXVECTOR3(_pos.x + (_target->getPosition().x - _pos.x) * 0.3f, _pos.y + (_target->getPosition().y - _pos.y) * 0.7f, _pos.z);
		param.endPos = D3DXVECTOR3(_target->getPosition().x, _target->getPosition().y, _pos.z);
	}
	else if(_near == 1)
	{
		param.startPos = _pos;
		param.buffPos1 = D3DXVECTOR3(_pos.x + (_target->getPosition().x - _pos.x) * 0.3f, _pos.y + (_target->getPosition().y - _pos.y) * 0.7f, _pos.z);
		param.endPos = D3DXVECTOR3(_target->getPosition().x, _target->getPosition().y * 0.9f, _pos.z);
	}
	else if(_near == 2)
	{
		param.startPos = _pos;
		param.buffPos1 = D3DXVECTOR3(_pos.x + (_target->getPosition().x - _pos.x) * 0.3f, _pos.y + (_target->getPosition().y - _pos.y) * 0.7f, _pos.z);
		param.endPos = D3DXVECTOR3(_target->getPosition().x, _target->getPosition().y * 0.8f, _pos.z);
	}

	param.count = 0;
	param.deleteCountMax = DELETECOUNT_MAX/ 2;

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
	//	音
	param.launchSound->Stop(launchSoundIndex);
	param.burnSound->Stop(burnSoundIndex);

	if(param.lightPoint != nullptr)
		param.lightPoint->Release();

	param.lightPoint = nullptr;

	//delete[] param.smallFire;
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
#if 0
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川追加 ↓
///////////////////////////////////////////////////////////////////////////////
	if( param.pos.y >= 500.0f && !param.burnFlag )
	{
		burn( 0.0f, 0.0f );
	}
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川追加 ↑
///////////////////////////////////////////////////////////////////////////////
#endif
	//	設定された更新関数へ
	(this->*fpUpdate)();

	param.lightPoint->SetPosition(param.setPos.x, param.setPos.y, param.setPos.z);
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
		//param.smallFire[count].setInvViewMatrix(param.invViewMatrix);
		param.fire[count].Update();
		//param.smallFire[count].Update();
	}

	//PrintDebug( _T( "\ncountFire:Burn1 = %d\n"), param.fireMax - buffCount );

///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↓
///////////////////////////////////////////////////////////////////////////////
#if 1
	if(buffCount == param.fireMax)
	{
		param.enable = false;
		param.lightPoint->SetIsEnable(false);
	}
#endif
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↑
///////////////////////////////////////////////////////////////////////////////


	// 割合の決定
	float	proportion;		// 割合
	int counter = param.fire[0].getDeleteCount();
	
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↓
///////////////////////////////////////////////////////////////////////////////
#if 1
	if( counter < compAppear )
	{
		proportion = Utility::Easing( 0.0f, 1.0f, (float)counter / (float)compAppear);
	}
	else
	{
		proportion = Utility::Easing( 1.0f, 0.0f, (float)(counter - compAppear) / (float)compDisppear);
	}
#else
	if( timerForLight < 60 )
	{
		proportion = Utility::Easing( 1.0f, 0.0f, (float)timerForLight / 60.0f);
	}
	else
	{
		proportion = Utility::Easing( 0.0f, 1.0f, (float)(timerForLight - 60) / 100);
	}
#endif
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↑
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↓
///////////////////////////////////////////////////////////////////////////////
#if 1
	// 減衰率の設定
	D3DXVECTOR3	attenuation;		// 減衰率0.00028f, 0.00000005f     0.0005f, 0.00005f
	attenuation = attenuationValue + D3DXVECTOR3( 0.0f, 0.0028f * proportion, 0.000005f * proportion );
	//param.lightPoint->SetAttenuation(0.0f, 0.00028f, 0.0000005f);
	param.lightPoint->SetAttenuation( attenuation );
#else
	D3DXVECTOR3	attenuation;
	if( timerForLight < 60 )
	{
		attenuation = (1.0f - proportion) * attenuationValue;
		attenuation += proportion * 7.0f * attenuationValue;
	}
	else
	{
		attenuation = attenuationValue + D3DXVECTOR3( 0.0f, 0.01f * proportion, 0.0001f * proportion );
	}
	param.lightPoint->SetAttenuation( attenuation );
#endif
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川変更 ↑
///////////////////////////////////////////////////////////////////////////////
#if 0
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川追加 ↓
///////////////////////////////////////////////////////////////////////////////
	if(timerForLight >= 100)
	{
		param.enable = false;
		param.lightPoint->SetIsEnable(false);
	}
	++timerForLight;
///////////////////////////////////////////////////////////////////////////////
// 2015_12_20 白川追加 ↑
///////////////////////////////////////////////////////////////////////////////
#endif
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
		//param.smallFire[count].setInvViewMatrix(param.invViewMatrix);
		param.fire[count].Update();
		//param.smallFire[count].Update();
	}

	//PrintDebug( _T( "\ncountFire:Burn2 = %d\n"), param.fireMax * SMALL_FIREWORKS_MAX - buffCount );

	if(buffCount == param.fireMax * param.setSmallFireIndex)
	{
		param.enable = false;
		param.lightPoint->SetIsEnable(false);
	}


	// 割合の決定
	float	proportion;		// 割合
	int counter = param.fire[0].getDeleteCount();

	if( counter < compAppear )
	{
		proportion = Utility::Easing( 0.0f, 1.0f, (float)counter / (float)compAppear);
	}
	else
	{
		proportion = Utility::Easing( 1.0f, 0.0f, (float)(counter - compAppear) / (float)compDisppear);
	}

	// 減衰率の設定
	D3DXVECTOR3	attenuation;		// 減衰率0.00028f, 0.00000005f     0.0005f, 0.00005f
	attenuation = attenuationValue + D3DXVECTOR3( 0.0f, 0.0028f * proportion, 0.0000005f * proportion );
	param.lightPoint->SetAttenuation( attenuation );
}

//==============================================================================
// Brief  : 花火の爆発処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
int Fireworks::burn(
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

	//	返り値
	int returnValue;

	//	優
	if(_hitPosLength <= (_hitCheckOffset * 0.1f))
	{
		param.fireMax = FIRE_MAX;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 45.0f;

		returnValue = ADD_10;
	}
	//	良
	else if(_hitPosLength <= (_hitCheckOffset * 0.3f))
	{
		param.fireMax = FIRE_MAX / 3;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 15.0f;

		returnValue = ADD_5;
	}
	//	可
	else
	{
		param.fireMax = FIRE_MAX / 6;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 5.0f;

		returnValue = ADD_1;
	}

	param.fireMax = FIRE_MAX;
	buffValue = 360.0f / (float)(param.fireMax);
	fireSize = 45.0f;

	returnValue = ADD_10;

	//	花火の背景用生成
	param.managerPoint->Add(
		fireBGExistTime,
		param.setPos,
		param.color,
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
		float speedX = CRadianTable::mySinf((buffValue * count) + ((rand() % 10) + (rand() % 10)));
		float speedY = CRadianTable::myCosf((buffValue * count) + ((rand() % 10) + (rand() % 10)));

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
			param.color);


		//	小さい火花生成
		//param.smallFire[count].Set(
		//	Fire::STATE_SMALL,
		//	param.managerPoint,
		//	buffSetPos,
		//	D3DXVECTOR3((speedX * (float)(rand() % bigFireFirstSpeed) * 0.1f),
		//				(speedY * (float)(rand() % bigFireFirstSpeed) * 0.1f),
		//				0.0f),
		//	param.color);
	}



	//	更新関数設定
	fpUpdate = &Fireworks::BurnUpdate;

	//	破裂フラグON
	param.burnFlag = true;

	//	音再生
	param.launchSound->Stop(launchSoundIndex);
	burnSoundIndex = param.burnSound->Play();

	return returnValue;
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
			param.color,
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
				param.color);
		}
	}


	//	更新関数設定
	fpUpdate = &Fireworks::Burn2Update;

	//	破裂フラグON
	param.burnFlag = true;

	//	音再生
	param.launchSound->Stop(launchSoundIndex);
	burnSoundIndex = param.burnSound->Play();
}

//==============================================================================
// Brief  : 花火の爆発処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
int Fireworks::burnNew151220(
	float _hitCheckOffset,
	float _hitPosLength)
{
	//	カメラの逆行列をかけて、常に一定の場所に出るようにする処理
	D3DXVECTOR4 setPos;
	D3DXVec3Transform(&setPos, &param.pos, &param.invViewMatrix);
	param.setPos.x = setPos.x;
	param.setPos.y = setPos.y;
	param.setPos.z = setPos.z;

	//	火花のスピード
	float buffFireSpeed;

	//	火花の最大数
	float fireSize;

	//	返り値
	int returnValue;

	//	優
	if(_hitPosLength <= (_hitCheckOffset * 0.1f))
	{
		param.fireXZMax = FIRE_XZ_MAX;
		param.fireYMax = FIRE_Y_MAX;
		param.fireMax = param.fireXZMax * param.fireYMax;
		fireSize = 45.0f;
		buffFireSpeed = fireSpeed;
		returnValue = ADD_10;
	}
	//	良
	else if(_hitPosLength <= (_hitCheckOffset * 0.3f))
	{
		param.fireXZMax = FIRE_XZ_MAX * 2 / 3;
		param.fireYMax = FIRE_Y_MAX * 2 / 3;
		param.fireMax = param.fireXZMax * param.fireYMax;
		buffFireSpeed = fireSpeed / 3.0f * 2.0f;
		fireSize = 25.0f;

		returnValue = ADD_5;
	}
	//	可
	else
	{
		param.fireXZMax = FIRE_XZ_MAX / 3;
		param.fireYMax = FIRE_Y_MAX / 3;
		param.fireMax = param.fireXZMax * param.fireYMax;
		buffFireSpeed = fireSpeed / 3.0f;
		fireSize = 5.0f;

		returnValue = ADD_1;
	}

	//	花火の背景用生成
	param.managerPoint->Add(
		fireBGExistTime,
		param.setPos,
		param.color,
		fireSize,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.02f ),
		fireBGAddSize,
		PointMain::STATE_ADD
		);

	//	火花の数だけループ
	for(int countY = 0;countY < param.fireYMax;countY++)
	{
		for(int count = 0;count < param.fireXZMax;count++)
		{
			D3DXVECTOR3 fireVec = D3DXVECTOR3(RANDAM((int)(buffFireSpeed * 100.0f)) * 0.001f, buffFireSpeed + RANDAM((int)(buffFireSpeed * 100.0f)) * 0.001f, RANDAM((int)(buffFireSpeed * 100.0f)) * 0.001f);
			D3DXVECTOR4 fireSetVec = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
			D3DXMATRIX rotMatrix;
			D3DXMatrixIdentity(&rotMatrix);
			float fBuff = (D3DX_PI  / (float)FIRE_Y_MAX) * 1000.0f;
			D3DXMatrixRotationYawPitchRoll(
				&rotMatrix,
				(D3DX_PI  / (float)param.fireYMax) * countY + (RANDAM((int)fBuff) * 0.01f),
				(RANDAM((int)fBuff) * 0.01f),
				(D3DX_PI / (float)param.fireXZMax) * count);
			D3DXVec3Transform(
				&fireSetVec,
				&fireVec,
				&rotMatrix
				);


			//	ローカル頂点座標を計算
			D3DXVECTOR3 buffSetPos = D3DXVECTOR3(param.pos.x, param.pos.y, param.pos.z);

			//	火花生成
			param.fire[count + (param.fireXZMax * countY)].Set(
				Fire::STATE_BIG,
				param.managerPoint,
				buffSetPos,
				D3DXVECTOR3(
							fireSetVec.x,
							fireSetVec.y,
							-fireSetVec.z),
				param.color);
		}
	}



	//	更新関数設定
	fpUpdate = &Fireworks::BurnUpdate;

	//	破裂フラグON
	param.burnFlag = true;

	//	音再生
	param.launchSound->Stop(launchSoundIndex);
	burnSoundIndex = param.burnSound->Play();

	return returnValue;
}

//==============================================================================
// Brief  : 花火の爆発処理(予備・前Ver)
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::burn2New151220()
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

		//	火花のスピード
		float buffFireSpeed;

		//	花火の数に応じた、１つの火花の角度間隔
		float buffValue = 0.0f;

		//	火花の最大数
		float fireSize;


		//	強制的に優に設定
		param.fireXZMax = FIRE_XZ_MAX * 2 / 3;
		param.fireYMax = FIRE_Y_MAX * 2 / 3;
		param.fireMax = param.fireXZMax * param.fireYMax;
		buffFireSpeed = fireSpeed / 3.0f * 2.0f;
		fireSize = 25.0f;


		//	花火の背景用生成
		param.managerPoint->Add(
			fireBGExistTime,
			param.setPos,
			param.color,
			fireSize,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.02f ),
			fireBGAddSize,
			PointMain::STATE_ADD
			);

		//	火花の数だけループ
		for(int countY = 0;countY < param.fireYMax;countY++)
		{
			for(int count = 0;count < param.fireXZMax;count++)
			{
				D3DXVECTOR3 fireVec = D3DXVECTOR3(RANDAM((int)(buffFireSpeed * 100.0f)) * 0.001f, buffFireSpeed + RANDAM((int)(buffFireSpeed * 100.0f)) * 0.001f, RANDAM((int)(buffFireSpeed * 100.0f)) * 0.001f);
				D3DXVECTOR4 fireSetVec = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
				D3DXMATRIX rotMatrix;
				D3DXMatrixIdentity(&rotMatrix);
				float fBuff = (D3DX_PI  / (float)FIRE_Y_MAX) * 1000.0f;
				D3DXMatrixRotationYawPitchRoll(
					&rotMatrix,
					(D3DX_PI  / (float)param.fireYMax) * countY + (RANDAM((int)fBuff) * 0.01f),
					(RANDAM((int)fBuff) * 0.01f),
					(D3DX_PI / (float)param.fireXZMax) * count);
				D3DXVec3Transform(
					&fireSetVec,
					&fireVec,
					&rotMatrix
					);


				//	ローカル頂点座標を計算
				D3DXVECTOR3 buffSetPos = D3DXVECTOR3(buffPos.x, buffPos.y, buffPos.z);

				//	火花生成
				param.fire[count + (param.fireXZMax * countY) + (smallFireCount * param.fireMax)].Set(
					Fire::STATE_BIG,
					param.managerPoint,
					buffSetPos,
					D3DXVECTOR3(
								fireSetVec.x,
								fireSetVec.y,
								-fireSetVec.z),
					param.color);
			}
		}
	}


	//	更新関数設定
	fpUpdate = &Fireworks::Burn2Update;

	//	破裂フラグON
	param.burnFlag = true;

	//	音再生
	param.launchSound->Stop(launchSoundIndex);
	burnSoundIndex = param.burnSound->Play();
}


//==============================================================================
// Brief  : 花火の音生成処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::setSound(Sound* _burnSound, Sound* _launchSound)
{
	param.burnSound = _burnSound;
	param.launchSound = _launchSound;
}

void Fireworks::setManagerLight(ManagerLight* _managerLight)
{
	managerLight = _managerLight;
}
