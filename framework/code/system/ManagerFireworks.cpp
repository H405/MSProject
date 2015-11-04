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
#include "../framework/develop/Debug.h"
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
	burnIndex = 0;

	//list.top = nullptr;
	//list.cur = nullptr;
	//list.prev = nullptr;
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
	ppState_[ STATE_NORMAL ] = new FireworksStateNormal();
	ppState_[ STATE_SLOW ] = new FireworksStateSlow();
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
void ManagerFireworks::Update( void )
{
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		// 使用されていないとき次へ
		if( !fireworks[ count ].IsEnable() )
		{
			continue;
		}

		fireworks[count].Update();
	}

	//	リスト作成
	sort();
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
void ManagerFireworks::Add(
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
		return;
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
}
//==============================================================================
// Brief  : インデックス取得処理
// Return : int									: 使用可能なオブジェクトの番号（全部使用中の場合は負の値が返る）
// Arg    : void								: なし
//==============================================================================
int ManagerFireworks::GetIndex()
{
	// 空き番号を探す
	for( int count = burnIndex; count < FIREWORKS_MAX; ++count )
	{
		if( !fireworks[ count ].IsEnable() )
		{
			return count;
		}
	}
	for( int count = 0; count < burnIndex; ++count )
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
	//	指定の花火の爆発
	fireworks[burnIndex].burn();

	//	インデックスの更新
	burnIndex++;
	if(burnIndex >= FIREWORKS_MAX)
		burnIndex = 0;
}
//==============================================================================
// Brief  : 花火を打ち上げた順番通りに格納する
//			※多分もっとうまい方法あるけど、どりあえずカウンタの値を見てバブルソートする
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerFireworks::sort()
{
	int sortList[FIREWORKS_MAX];

	//	リストを全部初期化
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		fireworksList[count] = nullptr;
	}

	//	花火ごとのカウンタ格納用
	int counterList[FIREWORKS_MAX];

	//	有効化されている花火のカウンタを取得
	for( int count = 0; count < FIREWORKS_MAX; ++count )
	{
		if(fireworks[count].IsEnable() == true)
			counterList[count] = fireworks[count].getDeleteCount();
		else
			counterList[count] = -1;
	}

	//	ソート結果（インデックス番号）格納用
	int counter1 = 0;
	int counter2 = 0;
	int temp = 0;

	//	バブルソート
	for(counter1 = 0;counter1 < FIREWORKS_MAX - 1;counter1++)
	{
		for(counter2 = FIREWORKS_MAX - 1;counter2 > counter1;counter2--)
		{
			//	前の要素の方が大きければ交換
			if(counterList[counter2 - 1] > counterList[counter2])
			{
				temp = counterList[counter2];
				counterList[counter2] = counterList[counter2 - 1];
				counterList[counter2 - 1] = temp;


			}
		}
	}
}
