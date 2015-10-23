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
#include "../framework/develop/Debug.h"
#include "../framework/point/Point.h"
#include "../framework/point/PointState.h"
#include "../framework/polygon/PolygonPoint.h"
#include "../framework/resource/ManagerEffect.h"
#include "../framework/resource/ManagerTexture.h"
#include "../framework/vertex/Vertex.h"
#include "../framework/vertex/VertexBuffer.h"

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
	result = pGraphic_->Initialize( INT_MIN, pParameter, pEffectGeneral, pPolygon_, pTexture );
	if( result != 0 )
	{
		return result;
	}

	// 頂点バッファの作成
	pVertexBuffer_ = new VertexBuffer();
	if( pVertexBuffer_ == nullptr )
	{
		return 1;
	}
	result = pVertexBuffer_->Initialize( maximumItem, pPolygon_->GetVertex() );
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

	// 頂点バッファの開放
	delete pVertexBuffer_;
	pVertexBuffer_ = nullptr;

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
	// 頂点バッファの作成
	int		countPoint;		// ポイントの数
	countPoint = 0;
	for( int counterPoint = 0; counterPoint < maximumItem_; ++counterPoint )
	{
		// 使用されていないとき次へ
		if( !pPoint_[ counterPoint ].IsEnable() )
		{
			continue;
		}

		// ポイントの更新
		pPoint_[ counterPoint ].Update();

		// 頂点バッファへ登録
		D3DXVECTOR3	position;		// 座標
		D3DXCOLOR	color;			// 色
		countPoint, pPoint_[ counterPoint ].GetPosition( &position );
		countPoint, pPoint_[ counterPoint ].GetColor( &color );
		pVertexBuffer_->SetPosition( countPoint, position );
		pVertexBuffer_->SetColorDiffuse( countPoint, color );
		pVertexBuffer_->SetPointSize( countPoint, pPoint_[ counterPoint ].GetSize() );

		// ポイントの数を加算
		++countPoint;
	}

	// ポリゴンへ情報を転送
	pPolygon_->SetVertexBuffer( countPoint, pVertexBuffer_->GetBuffer() );
}

//==============================================================================
// Brief  : ポイントの追加
// Return : void								: なし
// Arg    : int indexState						: ステート番号
// Arg    : const D3DXVECTOR3& position			: 座標
// Arg    : const D3DXCOLOR& color				: 色
// Arg    : float size							: 大きさ
//==============================================================================
void ManagerPoint::Add( int indexState, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size )
{
	// 空き番号の取得
	int		index;		// 空き番号
	index = GetIndex();
	if( index < 0 )
	{
		PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
		return;
	}

	// ポイントの設定
	pPoint_[ index ].Set( indexState, position, color, size );
}

//==============================================================================
// Brief  : ポイントの追加
// Return : void								: なし
// Arg    : int timeExist						: 残存時間
// Arg    : const D3DXVECTOR3& position			: 座標
// Arg    : const D3DXCOLOR& color				: 色
// Arg    : float size							: 大きさ
// Arg    : const D3DXVECTOR3& differencePosition	: 座標の変化量
// Arg    : const D3DXCOLOR& differenceColor	: 色の変化量
// Arg    : float differenceSize				: 大きさの変化量
// Arg    : int indexState						: ステート番号
//==============================================================================
void ManagerPoint::Add( int timeExist, const D3DXVECTOR3& position, const D3DXCOLOR& color, float size,
	const D3DXVECTOR3& differencePosition, const D3DXCOLOR& differenceColor, float differenceSize, int indexState )
{
	// 空き番号の取得
	int		index;		// 空き番号
	index = GetIndex();
	if( index < 0 )
	{
		PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
		return;
	}

	// ポイントの設定
	pPoint_[ index ].Set( timeExist, position, color, size, differencePosition, differenceColor, differenceSize, indexState );
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
	pVertexBuffer_ = nullptr;
}

//==============================================================================
// Brief  : 空き番号の取得
// Return : int									: 空き番号
// Arg    : void								: なし
//==============================================================================
int ManagerPoint::GetIndex( void )
{
	// 空き番号を探す
	for( int counterPoint = 0; counterPoint < maximumItem_; ++counterPoint )
	{
		if( !pPoint_[ counterPoint ].IsEnable() )
		{
			return counterPoint;
		}
	}

	// 空いていなかった
	return -1;
}
