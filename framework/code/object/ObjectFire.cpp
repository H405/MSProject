//==============================================================================
//
// File   : ObjectFire.cpp
// Brief  : 火花オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ObjectFire.h"
#include "../system/ManagerPoint.h"

//******************************************************************************
// ライブラリ
//******************************************************************************

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 静的メンバ変数
//******************************************************************************

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectFire::ObjectFire( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ObjectFire::~ObjectFire( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int priority						: 更新優先度
//==============================================================================
int ObjectFire::Initialize(
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

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ObjectFire::Finalize( void )
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
void ObjectFire::Update( void )
{
	//	回転量加算
	rot += rotSpeed;

	pos.y++;

	//	位置情報加算
	pos.x += sinf(rot) * speed.x;
	pos.y += cosf(rot) * speed.y;
	pos.z += speed.z;


	managerPoint->Add(
			200,
			pos,
			D3DXCOLOR( 1.0f, 0.25f, 0.25f, 1.0f ),
			50.0f,
			D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
			D3DXCOLOR( 0.0f, 0.0f, 0.0f, -0.05f ),
			-2.0f,
			ManagerPoint::STATE_ADD
			);
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ObjectFire::InitializeSelf( void )
{
	// メンバ変数の初期化
	managerPoint = nullptr;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rot = 0.0f;
	rotSpeed = 0.0f;
	speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
