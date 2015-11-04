//==============================================================================
//
// File   : ManagerTarget.cpp
// Brief  : ターゲット管理オブジェクトクラス
// Author : Kotaro Nagasaki
// Date   : 2015/10/29 Tur : Kotaro Nagasaki : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerTarget.h"
#include "../framework/develop/Debug.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerTexture.h"

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
ManagerTarget::ManagerTarget( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}
//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerTarget::InitializeSelf( void )
{
	// メンバ変数の初期化
	target = nullptr;
}
//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerTarget::~ManagerTarget( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int ManagerTarget::Initialize(
	IDirect3DDevice9* pDevice,
	const EffectParameter* pParameter,
	Effect* pEffectGeneral,
	Texture* pTextureCross,
	Texture* pTextureArrow,
	Texture* pTextureCircle
	)
{
	//	ターゲットを指定個数分用意
	target = new Target[TARGET_MAX];
	for(int count = 0;count < TARGET_MAX;count++)
	{
		target[count].Initialize(
			pDevice,
			pParameter,
			pEffectGeneral,
			pTextureCross,
			pTextureArrow,
			pTextureCircle);
	}

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerTarget::Finalize( void )
{
	delete[] target;

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
void ManagerTarget::Update( void )
{
	for( int counterPoint = 0; counterPoint < TARGET_MAX; ++counterPoint )
	{
		// 使用されていないとき次へ
		if( !target[ counterPoint ].IsEnable() )
		{
			continue;
		}

		target[counterPoint].Update();
	}
}
//==============================================================================
// Brief  : ターゲット発射処理
// Return : void								: なし
// Arg2   : D3DXVECTOR3							: 発生位置
//==============================================================================
void ManagerTarget::Add(D3DXVECTOR3 _pos)
{
	int index = GetIndex();
	if(index < 0)
	{
		//PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
		return;
	}

	//	ターゲットのセット
	target[index].Set(_pos);
}
//==============================================================================
// Brief  : インデックス取得処理
// Return : int									: 使用可能なオブジェクトの番号（全部使用中の場合は負の値が返る）
// Arg    : void								: なし
//==============================================================================
int ManagerTarget::GetIndex()
{
	// 空き番号を探す
	for( int counterPoint = 0; counterPoint < TARGET_MAX; ++counterPoint )
	{
		if( !target[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}

	// 空いていなかった
	return -1;
}
