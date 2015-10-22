//==============================================================================
//
// File   : ManagerPoint.cpp
// Brief  : ポイントスプライトの管理クラス
// Author : Taiga Shirakawa
// Date   : 2015/10/22 thu : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "ManagerPoint.h"
#include "../graphic/graphic/GraphicPoint.h"
#include "../framework/point/Point.h"
#include "../framework/point/PointState.h"
#include "../framework/polygon/PolygonPoint.h"
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
ManagerPoint::ManagerPoint( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
ManagerPoint::~ManagerPoint( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int ManagerPoint::Initialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTexture )
{
	// メンバ変数の設定
	maximumItem_ = maximumItem;
	pPoint_ = new Point[ maximumItem ];
	for( int counterItem = 0; counterItem < maximumItem; ++counterItem )
	{
		pPoint_[ counterItem ].Initialize();
	}

	// ポリゴンの生成
	int		result;		// 実行結果
	pPolygon_ = new PolygonPoint();
	if( pPolygon_ == nullptr )
	{
		return 1;
	}
	result = pPolygon_->Initialize( maximumItem, pDevice );
	if( result != 0 )
	{
		return result;
	}

	// 描画クラスの生成
	pGraphic_ = new GraphicPoint();
	if( pGraphic_ == nullptr )
	{
		return 1;
	}
	result = pGraphic_->Initialize( 0, pParameter, pEffectGeneral, pPolygon_, pTexture );
	if( result != 0 )
	{
		return result;
	}

	// ステートテーブルの作成
	ppState_[ STATE_NONE ]		= new PointStateNone();
	ppState_[ STATE_ADD ]		= new PointStateAdd();
	ppState_[ STATE_MULTIPLY ]	= new PointStateMultiply();
	Point::SetState( ppState_ );

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int ManagerPoint::Finalize( void )
{
	// ステートテーブルの開放
	for( int counterState = 0; counterState < STATE_MAX; ++counterState )
	{
		delete ppState_[ counterState ];
		ppState_[ counterState ] = nullptr;
	}

	// 描画クラスの開放
	delete pGraphic_;
	pGraphic_ = nullptr;

	// ポリゴンの開放
	delete pPolygon_;
	pPolygon_ = nullptr;

	// 格納領域の開放
	delete[] pPoint_;
	pPoint_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int ManagerPoint::Reinitialize( int maximumItem, IDirect3DDevice9* pDevice, const EffectParameter* pParameter, Effect* pEffectGeneral, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( maximumItem, pDevice, pParameter, pEffectGeneral, pTexture );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : ManagerPoint* pOut					: コピー先アドレス
//==============================================================================
int ManagerPoint::Copy( ManagerPoint* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 更新処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerPoint::Update( void )
{
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void ManagerPoint::InitializeSelf( void )
{
	// メンバ変数の初期化
	maximumItem_ = 0;
	pPoint_ = nullptr;
	pPolygon_ = nullptr;
	pGraphic_ = nullptr;
}
