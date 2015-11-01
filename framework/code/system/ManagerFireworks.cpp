//==============================================================================
//
// File   : ManagerFireworks.cpp
// Brief  : 花火管理オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerFireworks.h"
#include "../framework/fireworks/Fireworks.h"
#include "../framework/develop/Debug.h"

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
ManagerFireworks::ManagerFireworks( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerFireworks::InitializeSelf( void )
{
	// メンバ変数の初期化
	fireworks = nullptr;
	managerPoint = nullptr;
	burnIndex = 0;
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerFireworks::~ManagerFireworks( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
//==============================================================================
int ManagerFireworks::Initialize(ManagerPoint* _managerPoint)
{
	managerPoint = _managerPoint;

	//	花火を指定個数分用意
	fireworks = new Fireworks[FIREWORKS_MAX];

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerFireworks::Finalize( void )
{
	delete[] fireworks;

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
void ManagerFireworks::Update( void )
{
	for( int counterPoint = 0; counterPoint < FIREWORKS_MAX; ++counterPoint )
	{
		// 使用されていないとき次へ
		if( !fireworks[ counterPoint ].IsEnable() )
		{
			continue;
		}

		fireworks[counterPoint].Update();
	}
}
//==============================================================================
// Brief  : 花火発射処理
// Return : void								: なし
// Arg1   : ManagerPoint*						: ポイントスプライト生成用マネージャ
// Arg2   : D3DXVECTOR3							: 発生位置
// Arg3   : D3DXVECTOR3							: 速度
// Arg4   : float								: 更新ごとの回転量
// Arg5   : float								: ↑に加算する回転量（大きすぎると変になるから注意）
//==============================================================================
void ManagerFireworks::Add(
		ManagerPoint* _managerPoint,
		D3DXVECTOR3 _pos,
		D3DXVECTOR3 _speed,
		float _rot,
		float _rotSpeed)
{
	int index = GetIndex();
	if(index < 0)
	{
		PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
		return;
	}

	//	花火のセット
	fireworks[index].Set(
		_managerPoint,
		_pos,
		_speed,
		_rot,
		_rotSpeed
		);
}
//==============================================================================
// Brief  : インデックス取得処理
// Return : int									: 使用可能なオブジェクトの番号（全部使用中の場合は負の値が返る）
// Arg    : void								: なし
//==============================================================================
int ManagerFireworks::GetIndex()
{
	// 空き番号を探す
	for( int counterPoint = burnIndex; counterPoint < FIREWORKS_MAX; ++counterPoint )
	{
		if( !fireworks[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}
	for( int counterPoint = 0; counterPoint < burnIndex; ++counterPoint )
	{
		if( !fireworks[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}

	// 空いていなかった
	return -1;
}
//==============================================================================
// Brief  : 花火の爆発処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerFireworks::Burn()
{
	//	指定の花火の爆発
	fireworks[burnIndex].burn();

	//	インデックスの更新
	burnIndex++;
	if(burnIndex >= FIREWORKS_MAX)
		burnIndex = 0;
}
