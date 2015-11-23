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
#include "../../system/ManagerPoint.h"
#include "../../system/ManagerFireworks.h"
#include "../fire/Fire.h"

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

static const float bigFireFirstSpeed = 1.0f;

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
	param.fire = new Fire[FIRE_MAX];
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
	param.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.setPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.rot = 0.0f;
	param.rotSpeed = 0.0f;
	param.speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = false;
	param.deleteCount = 0;
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
	param.deleteCount = 0;
	param.fireMax = 0;

	indexState = _indexState;

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
	//	設定された更新関数へ
	(this->*fpUpdate)();
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
		param.fire[count].Update();
	}

	if(buffCount == param.fireMax)
		param.enable = false;
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

	float buffValue = 0.0f;
	float fireSize;

	//	可
	if(_hitPosLength <= (_hitCheckOffset * 0.1f))
	{
		param.fireMax = FIRE_MAX;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 10.0f;
	}
	//	良
	else if(_hitPosLength <= (_hitCheckOffset * 0.3f))
	{
		param.fireMax = FIRE_MAX / 2;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 20.0f;
	}
	//	優
	else
	{
		param.fireMax = FIRE_MAX / 3;
		buffValue = 360.0f / (float)(param.fireMax);
		fireSize = 30.0f;
	}



	//	花火の背景用生成
	param.managerPoint->Add(
		150,
		D3DXVECTOR3(param.setPos.x, param.setPos.y, param.setPos.z),
		D3DXCOLOR( 0.9f, 0.9f, 0.9f, 0.9f ),
		fireSize,
		D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
		D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.02f ),
		5.0f,
		ManagerPoint::STATE_ADD
		);


	for(int count = 0;count < param.fireMax;count++)
	{
		float value = (float)(count * buffValue) + (buffValue * 0.1f);

		if(value == 0.0f)
		{
			param.fire[count].Set(
				Fire::STATE_UP,
				param.managerPoint,
				param.pos,
				D3DXVECTOR3(bigFireFirstSpeed, bigFireFirstSpeed, param.speed.z),
				value,
				0.1f);
		}
		else if(value == 180.0f)
		{
			param.fire[count].Set(
				Fire::STATE_DOWN,
				param.managerPoint,
				param.pos,
				D3DXVECTOR3(bigFireFirstSpeed, bigFireFirstSpeed, param.speed.z),
				value,
				1.0f);
		}
		else if(value > 180.0f && value < 360.0f)
		{
			param.fire[count].Set(
				Fire::STATE_LEFT,
				param.managerPoint,
				param.pos,
				D3DXVECTOR3(bigFireFirstSpeed, bigFireFirstSpeed, param.speed.z),
				value,
				0.2f);
		}
		else
		{
			param.fire[count].Set(
				Fire::STATE_RIGHT,
				param.managerPoint,
				param.pos,
				D3DXVECTOR3(bigFireFirstSpeed, bigFireFirstSpeed, param.speed.z),
				value,
				0.2f);
		}
	}

	//	更新関数設定
	fpUpdate = &Fireworks::BurnUpdate;

	//	破裂フラグON
	param.burnFlag = true;
}

