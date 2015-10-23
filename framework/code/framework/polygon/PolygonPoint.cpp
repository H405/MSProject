//==============================================================================
//
// File   : PolygonPoint.cpp
// Brief  : ポイントスプライトポリゴン
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "PolygonPoint.h"
#include "../develop/Debug.h"
#include "../vertex/Vertex.h"
#include "../vertex/VertexBuffer.h"

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
PolygonPoint::PolygonPoint( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
PolygonPoint::~PolygonPoint( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : int maximumItem						: 最大要素数
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
//==============================================================================
int PolygonPoint::Initialize( int maximumItem, IDirect3DDevice9* pDevice )
{
	// メンバ変数の設定
	maximumItem_ = maximumItem;
	pDevice_ = pDevice;

	// 頂点情報の生成
	int		result;		// 実行結果
	pVertex_ = new Vertex();
	if( pVertex_ == nullptr )
	{
		return 1;
	}
	result = pVertex_->Initialize( pDevice, Vertex::ELEMENT_SET_POINT );
	if( result != 0 )
	{
		return result;
	}

	// 頂点バッファ情報を作成
	VertexBuffer	buffer;		// 頂点バッファ情報
	buffer.Initialize( maximumItem, pVertex_ );
	for( int counterVertex = 0; counterVertex < maximumItem; ++counterVertex )
	{
		buffer.SetPosition( counterVertex, 0.0f, 0.0f, 0.0f );
		buffer.SetPointSize( counterVertex, 100.0f );
		buffer.SetColorDiffuse( counterVertex, 1.0f, 1.0f, 1.0f, 1.0f );
	}

	// 頂点バッファの生成
	int		sizeVertex;		// 頂点のサイズ
	sizeVertex = pVertex_->GetSize();
	result = pDevice->CreateVertexBuffer( sizeVertex * maximumItem, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &pVertexBuffer_, nullptr );
	if( result != 0 )
	{
		return result;
	}

	// 頂点バッファに値を設定
	void*	pBufferAddress = nullptr;		// バッファのアドレス
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * maximumItem, buffer.GetBuffer(), sizeVertex * maximumItem );
	pVertexBuffer_->Unlock();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int PolygonPoint::Finalize( void )
{
	// 頂点バッファの開放
	if( pVertexBuffer_ != nullptr )
	{
		pVertexBuffer_->Release();
		pVertexBuffer_ = nullptr;
	}

	// 頂点情報の開放
	delete pVertex_;
	pVertex_ = nullptr;

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
//==============================================================================
int PolygonPoint::Reinitialize( int maximumItem, IDirect3DDevice9* pDevice )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( maximumItem, pDevice );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : PolygonPoint* pOut					: コピー先アドレス
//==============================================================================
int PolygonPoint::Copy( PolygonPoint* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PolygonPoint::Draw( void )
{
	// 描画数の確認
	if( countItem_ <= 0 )
	{
		return;
	}

	// 描画
	pDevice_->SetStreamSource( 0, pVertexBuffer_, 0, pVertex_->GetSize() );
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->DrawPrimitive( D3DPT_POINTLIST, 0, countItem_);
}

//==============================================================================
// Brief  : 頂点バッファの設定
// Return : void								: なし
// Arg    : int count							: 頂点の数
// Arg    : void* pBuffer						: 頂点バッファ
//==============================================================================
void PolygonPoint::SetVertexBuffer( int count, void* pBuffer )
{
	// エラーチェック
	Assert( pBuffer != nullptr, _T( "引数のアドレスが不正です。" ) );

	// 個数の決定
	countItem_ = count;

	// 頂点バッファに値を設定
	void*	pBufferAddress = nullptr;		// バッファのアドレス
	int		sizeVertex;		// 頂点のサイズ
	sizeVertex = pVertex_->GetSize();
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * count, pBuffer, sizeVertex * count );
	pVertexBuffer_->Unlock();
}

//==============================================================================
// Brief  : 頂点情報の取得
// Return : Vertex*								: 返却する値
// Arg    : void								: なし
//==============================================================================
Vertex* PolygonPoint::GetVertex( void ) const
{
	// 値の返却
	return pVertex_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PolygonPoint::InitializeSelf( void )
{
	// メンバ変数の初期化
	maximumItem_ = 0;
	countItem_ = 0;
	pDevice_ = nullptr;
	pVertexBuffer_ = nullptr;
	pVertex_ = nullptr;
}
