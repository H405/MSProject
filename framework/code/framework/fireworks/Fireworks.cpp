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
#include "../../system/ManagerPoint.h"
#include "../../system/ManagerFireworks.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************
#define FIRE_MAX (36)
#define DEG_TO_RAD(_deg)	((D3DX_PI / 180.0f) * _deg)
#define DELETECOUNT_MAX (1000)
#define RANDAM(value) ((rand() % value) - (rand() % value))

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
static const float effectSize = 15.0f;

//	生成する花火エフェクトの消えるまでの時間
static const int effectExistTime = 200;

//	生成する花火エフェクトの大きさの差異
static const float effectDifferenceSize = -0.2f;

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Fireworks::Fireworks( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::InitializeSelf( void )
{
	// メンバ変数の初期化
	managerPoint = nullptr;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = 0.0f;
	rotSpeed = 0.0f;
	speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enable = false;
	deleteCount = 0;
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
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int Fireworks::Set(
					ManagerPoint* _managerPoint,
					D3DXVECTOR3 _pos,
					D3DXVECTOR3 _speed,
					float _rot,
					float _rotSpeed )
{
	managerPoint = _managerPoint;
	pos = _pos;
	speed = _speed;
	rot = _rot;
	rotSpeed = _rotSpeed;

	enable = true;
	deleteCount = 0;

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
	//	回転量加算
	rot += rotSpeed;

	pos.y++;

	//	位置情報加算
	pos.x += sinf(rot) * speed.x;
	pos.y += cosf(rot) * speed.y;
	pos.z += speed.z;

	managerPoint->Add(
			effectExistTime,
			D3DXVECTOR3(pos.x + (RANDAM(100) * 0.01f), pos.y + (RANDAM(100) * 0.01f), pos.z + (RANDAM(100) * 0.01f)),
			D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ),
			effectSize - ((effectSize / DELETECOUNT_MAX) * deleteCount),
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.01f ),
			effectDifferenceSize,
			ManagerPoint::STATE_ADD
			);

	deleteCount++;
	if(deleteCount >= DELETECOUNT_MAX)
	{
		enable = false;
	}
}
//==============================================================================
// Brief  : 花火の爆発処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fireworks::burn()
{
	Finalize();
}
