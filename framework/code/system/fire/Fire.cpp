//==============================================================================
//
// File   : Fire.cpp
// Brief  : 火花オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Fire.h"
#include "FireState.h"
#include "../../system/ManagerPoint.h"
#include "../../framework/radianTable/radianTable.h"

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
FireState* Fire::ppState_[STATE_MAX];

//==============================================================================
// Brief  : コンストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Fire::Fire( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fire::InitializeSelf( void )
{
	// メンバ変数の初期化
	param.managerPoint = nullptr;
	param.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.rot = 0.0f;
	param.rotSpeed = 0.0f;
	param.speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	param.enable = false;
	param.deleteCount = 0;
	indexState = 0;
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Fire::~Fire( void )
{
	// 終了処理
	Finalize();
}
//==============================================================================
// Brief  : ステートの設定
// Return : void								: なし
//==============================================================================
void Fire::InitializeState()
{
	// ステートテーブルの作成
	//	FireStateArrangeにクラス追加したら、これのヘッダーにステート（enum）増やして
	//	ここにテーブルを追加すること！
	ppState_[ STATE_RIGHT ] = new FireStateRight();
	ppState_[ STATE_LEFT ] = new FireStateLeft();
	ppState_[ STATE_UP ] = new FireStateUp();
	ppState_[ STATE_DOWN ] = new FireStateDown();
}
//==============================================================================
// Brief  : ステートの設定
// Return : void								: なし
//==============================================================================
void Fire::FinalizeState()
{
	for(int count = 0;count < STATE_MAX;count++)
		delete ppState_[count];
}
//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
//==============================================================================
int Fire::Set(
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
	param.speed = _speed;
	param.rot = _rot;
	param.rotSpeed = _rotSpeed;

	param.enable = true;
	param.deleteCount = 0;

	indexState = _indexState;

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Fire::Finalize( void )
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
void Fire::Update( void )
{
	//	ステート毎の更新処理へ
	ppState_[indexState]->Update(this);
}
//==============================================================================
// Brief  : 火花の爆発処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Fire::burn()
{
	Finalize();
}
