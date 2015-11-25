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
#include "../framework/develop/DebugProc.h"
#include "../framework/develop/DebugMeasure.h"
#include "fireworks/FireworksState.h"

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

	for(int count = 0;count < FIREWORKS_MAX;count++)
		enableOld[count] = false;
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
	fireworksList = new Fireworks*[FIREWORKS_MAX];

	// ステートテーブルの作成
	//	FireworksStateArrangeにクラス追加したら、これのヘッダーにステート（enum）増やして
	//	ここにテーブルを追加すること！
	ppState_[ STATE_RIGHT ] = new FireworksStateRight();
	ppState_[ STATE_LEFT ] = new FireworksStateLeft();
	Fireworks::SetState( ppState_ );

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
	// ステートテーブルの開放
	for( int count = 0; count < STATE_MAX; ++count )
	{
		delete ppState_[ count ];
		ppState_[ count ] = nullptr;
	}

	delete[] fireworksList;
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
void ManagerFireworks::Update(int* _table , int* _fireworksTableIndex)
{
	int countFireworks = 0;

	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		//	消えた瞬間を判定して、テーブルを再構築
		if(enableOld[count] == true &&
			fireworks[count].IsEnable() == false)
		{
			Sort(_table, count);
			*_fireworksTableIndex -= 1;
		}

		//	使用状態の前情報を保存
		enableOld[ count ] = fireworks[ count ].IsEnable();

		// 使用されていないとき次へ
		if( !fireworks[ count ].IsEnable() )
		{
			continue;
		}

		fireworks[count].setInvViewMatrix(invViewMatrix);
		fireworks[count].Update();

		countFireworks++;
	}

	PrintDebug( _T( "\ncountFireworks = %d\n"), countFireworks );
}
//==============================================================================
// Brief  : テーブルのソート処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerFireworks::Sort(int* _table, int _deleteIndex)
{
	//	消去するテーブル番号の一時保存
	int tempIndex;

	//	テーブルを全て一時保存
	int tempTable[FIREWORKS_MAX];

	for(int count = 0;count < FIREWORKS_MAX;count++)
	{
		//	テーブルを全て一時保存
		tempTable[count] = _table[count];

		//	消去するテーブル番号の一時保存
		if(_table[count] == _deleteIndex)
			tempIndex = count;
	}

	//	配列保存用の一時カウンタ
	int tempCount = 0;

	for(int count = 0;count < FIREWORKS_MAX;count++)
	{
		//	削除する番号以外
		if(count != tempIndex)
		{
			_table[tempCount] = tempTable[count];
			tempCount++;
		}
	}

	//	最後に-1追加
	_table[FIREWORKS_MAX - 1] = -1;
}
//==============================================================================
// Brief  : 花火発射処理
// Return : void								: なし
// Arg    : int indexState						: ステート番号
// Arg   : ManagerPoint*						: ポイントスプライト生成用マネージャ
// Arg   : D3DXVECTOR3							: 発生位置
// Arg   : D3DXVECTOR3							: 速度
// Arg   : float								: 更新ごとの回転量
// Arg   : float								: ↑に加算する回転量（大きすぎると変になるから注意）
//==============================================================================
int ManagerFireworks::Add(
	int _indexState,
	ManagerPoint* _managerPoint,
	D3DXVECTOR3 _pos,
	D3DXVECTOR3 _speed,
	float _rot,
	float _rotSpeed)
{
	int index = GetIndex();
	if(index < 0)
	{
		//PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
		return -1;
	}

	//	花火のセット
	fireworks[index].Set(
		_indexState,
		_managerPoint,
		_pos,
		_speed,
		_rot,
		_rotSpeed
		);

	return index;
}
//==============================================================================
// Brief  : インデックス取得処理
// Return : int									: 使用可能なオブジェクトの番号（全部使用中の場合は負の値が返る）
// Arg    : void								: なし
//==============================================================================
int ManagerFireworks::GetIndex()
{
	// 空き番号を探す
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		if( !fireworks[ count ].IsEnable() )
		{
			return count;
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
}

void ManagerFireworks::setManagerLight(ManagerLight* _managerLight)
{
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		fireworks[count].setManagerLight(_managerLight);
	}
}
