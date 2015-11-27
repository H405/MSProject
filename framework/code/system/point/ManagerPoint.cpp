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
#include <process.h>
#include "ManagerPoint.h"
#include "PointMain.h"
#include "../../graphic/graphic/GraphicPoint.h"
#include "../../framework/develop/Debug.h"
#include "../../framework/develop/DebugProc.h"
#include "../../framework/develop/DebugMeasure.h"
#include "../../framework/polygon/PolygonPoint.h"
#include "../../framework/resource/ManagerEffect.h"
#include "../../framework/resource/ManagerTexture.h"
#include "../../framework/vertex/Vertex.h"
#include "../../framework/vertex/VertexBuffer.h"

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
// Arg    : int countThread						: スレッド数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int ManagerPoint::Initialize( int maximumItem, int countThread, IDirect3DDevice9* pDevice, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, IDirect3DTexture9* pTexture )
{
	// メンバ変数の設定
	countThread_ = countThread;
	countItemBuffer_ = (maximumItem + countThread - 1) / countThread;
	maximumItem_ = countThread_ * countItemBuffer_;

	// ポイント情報格納バッファの確保
	ppPoint_ = new PointMain*[ countThread ];
	if( ppPoint_ == nullptr )
	{
		return 1;
	}
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		ppPoint_[ counterThread ] = new PointMain[ maximumItem ];
		if( ppPoint_[ counterThread ] == nullptr )
		{
			return 1;
		}
		for( int counterItem = 0; counterItem < maximumItem; ++counterItem )
		{
			ppPoint_[ counterThread ][ counterItem ].Initialize();
		}
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
	result = pGraphic_->Initialize( INT_MIN, pParameter, pEffectGeneral, pEffectReflect, pPolygon_, pTexture );
	if( result != 0 )
	{
		return result;
	}

	// 頂点バッファの作成
	pVertexBuffer_ = new VertexBuffer[ countThread ];
	if( pVertexBuffer_ == nullptr )
	{
		return 1;
	}
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		result = pVertexBuffer_[ counterThread ].Initialize( countItemBuffer_, pPolygon_->GetVertex() );
		if( result != 0 )
		{
			return result;
		}
	}

	// 総合頂点バッファの作成
	pVertexBufferMerge_ = new VertexBuffer();
	if( pVertexBufferMerge_ == nullptr )
	{
		return 1;
	}
	result = pVertexBufferMerge_->Initialize( maximumItem_, pPolygon_->GetVertex() );
	if( result != 0 )
	{
		return result;
	}

	// 設定ポイント数格納領域の確保
	pCountPoint_ = new int[ countThread ];
	if( pCountPoint_ == nullptr )
	{
		return 1;
	}
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		pCountPoint_[ counterThread ] = 0;
	}

	// クリティカルセクションの初期化
	InitializeCriticalSectionEx( &criticalSectionFinish_, 0, 0 );

	// 読み込みスレッドの生成
	pHandleThread_ = new HANDLE[ countThread ];
	if( pHandleThread_ == nullptr )
	{
		return 1;
	}
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		// スレッド番号の設定
		EnterCriticalSection( &criticalSectionFinish_ );
		countThreadFinish_ = counterThread;
		LeaveCriticalSection( &criticalSectionFinish_ );

		// スレッドの作成
		pHandleThread_[ counterThread ] = reinterpret_cast< HANDLE >( _beginthreadex( nullptr, 0, UpdateBuffer, this, 0, nullptr ) );

		// スレッド作成待機
		for( ; ; )
		{
			// 待機
			Sleep( 1 );

			// 作成されたか確認
			int		indexCurrent;		// 現在のスレッド番号
			EnterCriticalSection( &criticalSectionFinish_ );
			indexCurrent = countThreadFinish_;
			LeaveCriticalSection( &criticalSectionFinish_ );
			if( indexCurrent == -1 )
			{
				break;
			}
		}

		int		indexDebug;		// 現在のスレッド番号
		EnterCriticalSection( &criticalSectionFinish_ );
		indexDebug = countThreadFinish_;
		LeaveCriticalSection( &criticalSectionFinish_ );
		PrintDebugWnd( _T( "Create %2d\n" ), indexDebug );
	}

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
	// スレッドの開放
	needsDelete_ = true;
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		ResumeThread( pHandleThread_[ counterThread ] );
		WaitForSingleObject( pHandleThread_[ counterThread ], INFINITE );
		CloseHandle( pHandleThread_[ counterThread ] );
		pHandleThread_[ counterThread ] = NULL;
	}
	delete[] pHandleThread_;
	pHandleThread_ = nullptr;

	// クリティカルセクションの開放
	DeleteCriticalSection( &criticalSectionFinish_ );

	// 設定ポイント数格納領域の開放
	delete[] pCountPoint_;
	pCountPoint_ = nullptr;

	// 総合頂点バッファの開放
	delete pVertexBufferMerge_;
	pVertexBufferMerge_ = nullptr;

	// 頂点バッファの開放
	delete[] pVertexBuffer_;
	pVertexBuffer_ = nullptr;

	// 描画クラスの開放
	delete pGraphic_;
	pGraphic_ = nullptr;

	// ポリゴンの開放
	delete pPolygon_;
	pPolygon_ = nullptr;

	// 格納領域の開放
	if( ppPoint_ != nullptr )
	{
		for( int counterThread = 0; counterThread < countThread_; ++counterThread )
		{
			delete[] ppPoint_[ counterThread ];
			ppPoint_[ counterThread ] = nullptr;
		}
	}
	delete[] ppPoint_;
	ppPoint_ = nullptr;

	// クラス内の初期化処理
	InitializeSelf();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 再初期化処理
// Return : int									: 実行結果
// Arg    : int maximumItem						: 最大要素数
// Arg    : int countThread						: スレッド数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : const EffectParameter* pParameter	: エフェクトパラメータ
// Arg    : Effect* pEffectGeneral				: 通常描画エフェクト
// Arg    : Effect* pEffectReflect				: 反射描画エフェクト
// Arg    : IDirect3DTexture9* pTexture			: テクスチャ
//==============================================================================
int ManagerPoint::Reinitialize( int maximumItem, int countThread, IDirect3DDevice9* pDevice, const EffectParameter* pParameter,
	Effect* pEffectGeneral, Effect* pEffectReflect, IDirect3DTexture9* pTexture )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( maximumItem, countThread, pDevice, pParameter, pEffectGeneral, pEffectReflect, pTexture );
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
	// 終了スレッド数のクリア
	EnterCriticalSection( &criticalSectionFinish_ );
	countThreadFinish_ = 0;
	LeaveCriticalSection( &criticalSectionFinish_ );

	// 設定ポイント数のクリア
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		pCountPoint_[ counterThread ] = 0;
	}

	// バッファの更新
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		ResumeThread( pHandleThread_[ counterThread ] );
	}

	// 更新待機
	for( ; ; )
	{
		// 待機
		Sleep( 1 );

		// 更新されたか確認
		int		countThreadUpdated;		// 更新されたスレッド数
		EnterCriticalSection( &criticalSectionFinish_ );
		countThreadUpdated = countThreadFinish_;
		LeaveCriticalSection( &criticalSectionFinish_ );
		if( countThreadUpdated >= countThread_ )
		{
			break;
		}
	}

	// バッファの統合
	int		countPoint;		// 設定ポイント数
	countPoint = 0;
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
		pVertexBufferMerge_->Merge( countPoint, pVertexBuffer_[ counterThread ], pCountPoint_[ counterThread ] );
		countPoint += pCountPoint_[ counterThread ];
//		PrintDebug( _T( "Thread Point %2d\n" ), pCountPoint_[ counterThread ] );
	}

	// ポリゴンへ情報を転送
	for( int counterThread = 0; counterThread < countThread_; ++counterThread )
	{
	}
	pPolygon_->SetVertexBuffer( countPoint, pVertexBufferMerge_->GetBuffer() );
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
	int		indexBuffer;		// 空きバッファ番号
	int		indexItem;			// 空き要素番号
	GetVacantIndex( &indexBuffer, &indexItem );
	if( indexBuffer < 0 || indexItem < 0 )
	{
		PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
		return;
	}

	// ポイントの設定
	ppPoint_[ indexBuffer ][ indexItem ].Set( indexState, position, color, size );
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
	int		indexBuffer;		// 空きバッファ番号
	int		indexItem;			// 空き要素番号
	GetVacantIndex( &indexBuffer, &indexItem );
	if( indexBuffer < 0 || indexItem < 0 )
	{
		PrintDebugWnd( _T( "ポイントに空きがありません。\n" ) );
		return;
	}

	// ポイントの設定
	ppPoint_[ indexBuffer ][ indexItem ].Set( timeExist, position, color, size, differencePosition, differenceColor, differenceSize, indexState );
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
	countThread_ = 0;
	countItemBuffer_ = 0;
	indexBuffer_ = 0;
	indexItem_ = 0;
	ppPoint_ = nullptr;
	pPolygon_ = nullptr;
	pGraphic_ = nullptr;
	pVertexBuffer_ = nullptr;
	pVertexBufferMerge_ = nullptr;
	pHandleThread_ = nullptr;
	ZeroMemory( &criticalSectionFinish_, sizeof( CRITICAL_SECTION ) );
	countThreadFinish_ = 0;
	pCountPoint_ = nullptr;
	needsDelete_ = false;
}

//==============================================================================
// Brief  : 空き番号の取得
// Return : void								: なし
// Arg    : int* pOutIndexThread				: スレッド番号格納先
// Arg    : int* pOutIndexItem					: 要素番号格納先
//==============================================================================
void ManagerPoint::GetVacantIndex( int* pOutIndexThread, int* pOutIndexItem )
{
	// 空き番号を探す
	for( int counterItem = 0; counterItem < maximumItem_; ++counterItem )
	{
		++indexBuffer_;
		if( indexBuffer_ >= countThread_ )
		{
			indexBuffer_ = 0;
			++indexItem_;
			if( indexItem_ >= countItemBuffer_ )
			{
				indexItem_ = 0;
			}
		}
		if( !ppPoint_[ indexBuffer_ ][ indexItem_ ].IsEnable() )
		{
			*pOutIndexThread = indexBuffer_;
			*pOutIndexItem = indexItem_;
			return;
		}
	}

	// 空いていなかった
	*pOutIndexThread = -1;
	*pOutIndexItem = -1;
}

//==============================================================================
// Brief  : バッファの更新
// Return : unsigned int						: 実行結果
// Arg    : LPVOID pParameter					: パラメータ
//==============================================================================
unsigned int _stdcall ManagerPoint::UpdateBuffer( LPVOID pParameter )
{
	// クラスのアドレスを取得
	ManagerPoint*	pManagerPoint = reinterpret_cast< ManagerPoint* >( pParameter );

	// 自身の番号を記録
	int		index;		// 自身の番号
	EnterCriticalSection( &pManagerPoint->criticalSectionFinish_ );
	index = pManagerPoint->countThreadFinish_;
	pManagerPoint->countThreadFinish_ = -1;
	LeaveCriticalSection( &pManagerPoint->criticalSectionFinish_ );
	SuspendThread( pManagerPoint->pHandleThread_[ index ] );
	PrintDebugWnd( _T( "Save Index %2d\n" ), index );

	// 更新ループ
	bool	needsUpdate;		// 更新フラグ
	needsUpdate = !pManagerPoint->needsDelete_;
	while( needsUpdate )
	{
		// 頂点バッファの作成
		int		countPoint;		// ポイントの数
		countPoint = 0;
		for( int counterPoint = 0; counterPoint < pManagerPoint->countItemBuffer_; ++counterPoint )
		{
			// 使用されていないとき次へ
			if( !pManagerPoint->ppPoint_[ index ][ counterPoint ].IsEnable() )
			{
				continue;
			}

			// ポイントの更新
			pManagerPoint->ppPoint_[ index ][ counterPoint ].Update();

			// 頂点バッファへ登録
			D3DXVECTOR3	position;		// 座標
			D3DXCOLOR	color;			// 色
			pManagerPoint->ppPoint_[ index ][ counterPoint ].GetPosition( &position );
			pManagerPoint->ppPoint_[ index ][ counterPoint ].GetColor( &color );
			pManagerPoint->pVertexBuffer_[ index ].SetValueForPoint( countPoint, position, color, pManagerPoint->ppPoint_[ index ][ counterPoint ].GetSize() );

			// ポイントの数を加算
			++countPoint;
		}

		// 設定ポイント数を格納
		pManagerPoint->pCountPoint_[ index ] = countPoint;

		// 終了カウントの加算
		EnterCriticalSection( &pManagerPoint->criticalSectionFinish_ );
		++pManagerPoint->countThreadFinish_;
		LeaveCriticalSection( &pManagerPoint->criticalSectionFinish_ );

		// 一時停止
		SuspendThread( pManagerPoint->pHandleThread_[ index ] );

		// 終了判定
		if( pManagerPoint->needsDelete_ )
		{
			needsUpdate = false;
		}
	}

	// スレッドの終了
	_endthreadex( 0 );
	return 0;
}
