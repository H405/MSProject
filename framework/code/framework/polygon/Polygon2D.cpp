//==============================================================================
//
// File   : Polygon2D.cpp
// Brief  : 2Dポリゴン
// Author : Taiga Shirakawa
// Date   : 2015/10/14 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "Polygon2D.h"
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
Polygon2D::Polygon2D( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
Polygon2D::~Polygon2D( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
//==============================================================================
int Polygon2D::Initialize( IDirect3DDevice9* pDevice )
{
	// メンバ変数の設定
	pDevice_ = pDevice;

	// 頂点情報の生成
	int		result;		// 実行結果
	pVertex_ = new Vertex();
	if( pVertex_ == nullptr )
	{
		return 1;
	}
	result = pVertex_->Initialize( pDevice, Vertex::ELEMENT_SET_SIMPLE );
	if( result != 0 )
	{
		return result;
	}

	// 頂点バッファ情報を作成
	VertexBuffer	buffer;		// 頂点バッファ情報
	buffer.Initialize( COUNT_VERTEX, pVertex_ );
	for( int counterVertex = 0; counterVertex < COUNT_VERTEX; ++counterVertex )
	{
		buffer.SetPosition( counterVertex, 2.0f * (counterVertex % COUNT_VERTEX_LINE) - 1.0f, -2.0f * (counterVertex / COUNT_VERTEX_LINE) + 1.0f, 0.0f );
		buffer.SetNormal( counterVertex, 0.0f, 0.0f, -1.0f );
		buffer.SetTextureCoord0( counterVertex, 1.0f * (counterVertex % COUNT_VERTEX_LINE), 1.0f * (counterVertex / COUNT_VERTEX_LINE) );
		buffer.SetColorDiffuse( counterVertex, 1.0f, 1.0f, 1.0f, 1.0f );
	}

	// 頂点バッファの生成
	int		sizeVertex;		// 頂点のサイズ
	sizeVertex = pVertex_->GetSize();
	result = pDevice->CreateVertexBuffer( sizeVertex * COUNT_VERTEX, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &pVertexBuffer_, nullptr );
	if( result != 0 )
	{
		return result;
	}

	// 頂点バッファに値を設定
	void*	pBufferAddress = nullptr;		// バッファのアドレス
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * COUNT_VERTEX, buffer.GetBuffer(), sizeVertex * COUNT_VERTEX );
	pVertexBuffer_->Unlock();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int Polygon2D::Finalize( void )
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
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
//==============================================================================
int Polygon2D::Reinitialize( IDirect3DDevice9* pDevice )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : Polygon2D* pOut						: コピー先アドレス
//==============================================================================
int Polygon2D::Copy( Polygon2D* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Polygon2D::Draw( void )
{
	// 描画
	pDevice_->SetStreamSource( 0, pVertexBuffer_, 0, pVertex_->GetSize() );
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, COUNT_VERTEX - 2 );
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void Polygon2D::InitializeSelf( void )
{
	// メンバ変数の初期化
	pDevice_ = nullptr;
	pVertexBuffer_ = nullptr;
	pVertex_ = nullptr;
}
