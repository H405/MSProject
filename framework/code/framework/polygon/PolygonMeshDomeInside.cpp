//==============================================================================
//
// File   : PolygonMeshDomeInside.cpp
// Brief  : 内側メッシュドームポリゴン
// Author : Taiga Shirakawa
// Date   : 2015/10/21 wed : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "PolygonMeshDomeInside.h"
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
PolygonMeshDomeInside::PolygonMeshDomeInside( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
PolygonMeshDomeInside::~PolygonMeshDomeInside( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int countCellX						: X方向セル数
// Arg    : int countCellY						: Y方向セル数
// Arg    : float radius						: 半径
// Arg    : float lengthTextureX				: X方向テクスチャ長さ
// Arg    : float lengthTextureY				: Y方向テクスチャ長さ
//==============================================================================
int PolygonMeshDomeInside::Initialize( IDirect3DDevice9* pDevice, int countCellX, int countCellY,
	float radius, float lengthTextureX, float lengthTextureY )
{
	// メンバ変数の設定
	pDevice_ = pDevice;
	countCellX_ = countCellX;
	countCellY_ = countCellY;
	radius_ = radius;
	lengthTextureX_ = lengthTextureX;
	lengthTextureY_ = lengthTextureY;

	// 頂点とインデックスの数を計算
	int		countVertexX;		// X方向頂点数
	int		countVertexY;		// Y方向頂点数
	countVertexX = countCellX + 1;
	countVertexY = countCellY + 1;
	countVertex_ = countVertexX * countVertexY;
	countIndex_ = 2 * countVertexX * (countVertexY - 1) + 2 * (countVertexY - 2);

	// インデックスのサイズを決定
	sizeIndex_ = (countVertexX > USHRT_MAX ? sizeof( DWORD ) : sizeof( WORD ));

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
	buffer.Initialize( countVertex_, pVertex_ );
	for( int counterVertexY = 0; counterVertexY < countVertexY; ++counterVertexY )
	{
		for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
		{
			int		indexVertex;		// 頂点の番号
			indexVertex = countVertexX * counterVertexY + counterVertexX;
			buffer.SetPositionX( indexVertex, radius * cosf( 0.5f * D3DX_PI * (countVertexY - 1 - counterVertexY) / countCellY ) * cosf( 2.0f * D3DX_PI * counterVertexX / countCellX ) );
			buffer.SetPositionY( indexVertex, radius * cosf( radius * sinf( 0.5f * D3DX_PI * (countVertexY - 1 - counterVertexY) / countCellY ) ) );
			buffer.SetPositionZ( indexVertex, radius * cosf( radius * cosf( 0.5f * D3DX_PI * (countVertexY - 1 - counterVertexY) / countCellY ) * sinf( 2.0f * D3DX_PI * counterVertexX / countCellX ) ) );
			buffer.SetNormal( indexVertex, cosf( 2.0f * D3DX_PI * counterVertexX / countCellX ), 0.0f, -sinf( 2.0f * D3DX_PI * counterVertexX / countCellX ) );
			buffer.SetTextureCoord0( indexVertex, lengthTextureX * counterVertexX, lengthTextureY * counterVertexY );
			buffer.SetColorDiffuse( indexVertex, 1.0f, 1.0f, 1.0f, 1.0f );
		}
	}

	// 頂点バッファの生成
	int		sizeVertex;		// 頂点のサイズ
	sizeVertex = pVertex_->GetSize();
	result = pDevice->CreateVertexBuffer( sizeVertex * countVertex_, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &pVertexBuffer_, nullptr );
	if( result != 0 )
	{
		return result;
	}

	// 頂点バッファに値を設定
	void*	pBufferAddress = nullptr;		// バッファのアドレス
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * countVertex_, buffer.GetBuffer(), sizeVertex * countVertex_ );
	pVertexBuffer_->Unlock();

	// インデックスバッファの作成
	result = pDevice->CreateIndexBuffer( sizeIndex_ * countIndex_, D3DUSAGE_WRITEONLY,
		(sizeIndex_ == sizeof( DWORD ) ? D3DFMT_INDEX32 : D3DFMT_INDEX16), D3DPOOL_MANAGED, &pIndexBuffer_, NULL );
	if( result != S_OK )
	{
		return result;
	}

	// インデックスバッファの設定
	if( sizeIndex_ == sizeof( DWORD ) )
	{
		// インデックスバッファ更新開始
		DWORD	*pIndex = nullptr;	// 書き換え用インデックスバッファアドレス
		pIndexBuffer_->Lock( 0, 0, (void**)&pIndex, 0 );

		// インデックス情報設定
		for( int counterVertexY = 0; counterVertexY < countVertexY - 1; ++counterVertexY )
		{
			for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
			{
				pIndex[ (2 * countVertexX + 2) * counterVertexY + 2 * counterVertexX + 0 ] = static_cast< DWORD >( countVertexX * (counterVertexY + 0) + counterVertexX );
				pIndex[ (2 * countVertexX + 2) * counterVertexY + 2 * counterVertexX + 1 ] = static_cast< DWORD >( countVertexX * (counterVertexY + 1) + counterVertexX );
			}
		}
		for( int counterVertexY = 0; counterVertexY < countVertexY - 2; ++counterVertexY )
		{
			pIndex[ (2 * countVertexX + 2) * (counterVertexY + 1) - 2 ] = static_cast< DWORD >( countVertexX * (counterVertexY + 1) + countVertexX - 1 );
			pIndex[ (2 * countVertexX + 2) * (counterVertexY + 1) - 1 ] = static_cast< DWORD >( countVertexX * (counterVertexY + 1) );
		}
	}
	else
	{
		// インデックスバッファ更新開始
		WORD	*pIndex = nullptr;		// 書き換え用インデックスバッファアドレス
		pIndexBuffer_->Lock( 0, 0, (void**)&pIndex, 0 );

		// インデックス情報設定
		for( int counterVertexY = 0; counterVertexY < countVertexY - 1; ++counterVertexY )
		{
			for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
			{
				pIndex[ (2 * countVertexX + 2) * counterVertexY + 2 * counterVertexX + 0 ] = static_cast< WORD >( countVertexX * (counterVertexY + 0) + counterVertexX );
				pIndex[ (2 * countVertexX + 2) * counterVertexY + 2 * counterVertexX + 1 ] = static_cast< WORD >( countVertexX * (counterVertexY + 1) + counterVertexX );
			}
		}
		for( int counterVertexY = 0; counterVertexY < countVertexY - 2; ++counterVertexY )
		{
			pIndex[ (2 * countVertexX + 2) * (counterVertexY + 1) - 2 ] = static_cast< WORD >( countVertexX * (counterVertexY + 1) + countVertexX - 1 );
			pIndex[ (2 * countVertexX + 2) * (counterVertexY + 1) - 1 ] = static_cast< WORD >( countVertexX * (counterVertexY + 1) );
		}
	}

	// インデックスバッファ更新終了
	pIndexBuffer_->Unlock();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 終了処理
// Return : int									: 実行結果
// Arg    : void								: なし
//==============================================================================
int PolygonMeshDomeInside::Finalize( void )
{
	// 頂点バッファの開放
	if( pVertexBuffer_ != nullptr )
	{
		pVertexBuffer_->Release();
		pVertexBuffer_ = nullptr;
	}

	// インデックスバッファの開放
	if( pIndexBuffer_ != nullptr )
	{
		pIndexBuffer_->Release();
		pIndexBuffer_ = nullptr;
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
// Arg    : int countCellX						: X方向セル数
// Arg    : int countCellY						: Y方向セル数
// Arg    : float radius						: 半径
// Arg    : float lengthTextureX				: X方向テクスチャ長さ
// Arg    : float lengthTextureY				: Y方向テクスチャ長さ
//==============================================================================
int PolygonMeshDomeInside::Reinitialize( IDirect3DDevice9* pDevice, int countCellX, int countCellY,
	float radius, float lengthTextureX, float lengthTextureY )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, countCellX, countCellY, radius, lengthTextureX, lengthTextureY );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : PolygonMeshDomeInside* pOut					: コピー先アドレス
//==============================================================================
int PolygonMeshDomeInside::Copy( PolygonMeshDomeInside* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PolygonMeshDomeInside::Draw( void )
{
	// 描画
	pDevice_->SetStreamSource( 0, pVertexBuffer_, 0, pVertex_->GetSize() );
	pDevice_->SetIndices( pIndexBuffer_ );
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, countVertex_, 0, countIndex_ - 2 );
}

//==============================================================================
// Brief  : 頂点数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PolygonMeshDomeInside::GetCountVertex( void ) const
{
	// 値の返却
	return countVertex_;
}

//==============================================================================
// Brief  : インデックス数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PolygonMeshDomeInside::GetCountIndex( void ) const
{
	// 値の返却
	return countIndex_;
}

//==============================================================================
// Brief  : インデックスのサイズの取得
// Return : void								: なし
// Arg    : size_t* pOut						: 値の格納アドレス
//==============================================================================
void PolygonMeshDomeInside::GetSizeIndex( size_t* pOut ) const
{
	// 値の返却
	*pOut = sizeIndex_;
}

//==============================================================================
// Brief  : X方向セル数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PolygonMeshDomeInside::GetCountCellX( void ) const
{
	// 値の返却
	return countCellX_;
}

//==============================================================================
// Brief  : Y方向セル数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PolygonMeshDomeInside::GetCountCellY( void ) const
{
	// 値の返却
	return countCellY_;
}

//==============================================================================
// Brief  :半径の設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void PolygonMeshDomeInside::SetRadius( float value )
{
	// 値の設定
	radius_ = value;
}

//==============================================================================
// Brief  : 半径の取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PolygonMeshDomeInside::GetRadius( void ) const
{
	// 値の返却
	return radius_;
}

//==============================================================================
// Brief  : X方向テクスチャ長さの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void PolygonMeshDomeInside::SetLengthTextureX( float value )
{
	// 値の設定
	lengthTextureX_ = value;
}

//==============================================================================
// Brief  : X方向テクスチャ長さの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PolygonMeshDomeInside::GetLengthTextureX( void ) const
{
	// 値の返却
	return lengthTextureX_;
}

//==============================================================================
// Brief  : Y方向テクスチャ長さの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void PolygonMeshDomeInside::SetLengthTextureY( float value )
{
	// 値の設定
	lengthTextureY_ = value;
}

//==============================================================================
// Brief  : Y方向テクスチャ長さの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PolygonMeshDomeInside::GetLengthTextureY( void ) const
{
	// 値の返却
	return lengthTextureY_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PolygonMeshDomeInside::InitializeSelf( void )
{
	// メンバ変数の初期化
	pDevice_ = nullptr;
	pVertexBuffer_ = nullptr;
	pIndexBuffer_ = nullptr;
	pVertex_ = nullptr;
	countVertex_ = 0;
	countIndex_ = 0;
	sizeIndex_ = 0;
	countCellX_ = 0;
	countCellY_ = 0;
	radius_ = 0.0f;
	lengthTextureX_ = 1.0f;
	lengthTextureY_ = 1.0f;
}
