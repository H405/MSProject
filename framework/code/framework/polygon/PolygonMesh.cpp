//==============================================================================
//
// File   : PolygonMesh.cpp
// Brief  : メッシュポリゴン
// Author : Taiga Shirakawa
// Date   : 2015/10/19 mon : Taiga Shirakawa : create
//
//==============================================================================

//******************************************************************************
// インクルード
//******************************************************************************
#include "PolygonMesh.h"
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
PolygonMesh::PolygonMesh( void )
{
	// クラス内の初期化処理
	InitializeSelf();
}

//==============================================================================
// Brief  : デストラクタ
// Return : 									: 
// Arg    : void								: なし
//==============================================================================
PolygonMesh::~PolygonMesh( void )
{
	// 終了処理
	Finalize();
}

//==============================================================================
// Brief  : 初期化処理
// Return : int									: 実行結果
// Arg    : IDirect3DDevice9* pDevice			: Direct3Dデバイス
// Arg    : int countCellX						: X方向セル数
// Arg    : int countCellZ						: Z方向セル数
// Arg    : float lengthCellX					: X方向セル長さ
// Arg    : float lengthCellZ					: Z方向セル長さ
// Arg    : float lengthTextureX				: X方向テクスチャ長さ
// Arg    : float lengthTextureZ				: Z方向テクスチャ長さ
//==============================================================================
int PolygonMesh::Initialize( IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
	float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ )
{
	// メンバ変数の設定
	pDevice_ = pDevice;
	countCellX_ = countCellX;
	countCellZ_ = countCellZ;
	lengthCellX_ = lengthCellX;
	lengthCellZ_ = lengthCellZ;
	lengthTextureX_ = lengthTextureX;
	lengthTextureZ_ = lengthTextureZ;

	// 頂点とインデックスの数を計算
	int		countVertexX;		// X方向頂点数
	int		countVertexZ;		// Z方向頂点数
	countVertexX = countCellX + 1;
	countVertexZ = countCellZ + 1;
	countVertex_ = countVertexX * countVertexZ;
	countIndex_ = 2 * countVertexX * (countVertexZ - 1) + 2 * (countVertexZ - 2);

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
	for( int counterVertexZ = 0; counterVertexZ < countVertexZ; ++counterVertexZ )
	{
		for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
		{
			int		indexVertex;		// 頂点の番号
			indexVertex = countVertexX * counterVertexZ + counterVertexX;
			buffer.SetPosition( indexVertex, lengthCellX * (counterVertexX - countCellX / 2.0f), 0.0f, lengthCellZ * (counterVertexZ - countCellZ / 2.0f) );
			buffer.SetNormal( indexVertex, 0.0f, 1.0f, 0.0f );
			buffer.SetTextureCoord0( indexVertex, lengthTextureX * counterVertexX, lengthTextureZ * counterVertexZ );
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
		for( int counterVertexZ = 0; counterVertexZ < countVertexZ - 1; ++counterVertexZ )
		{
			for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
			{
				pIndex[ (2 * countVertexX + 2) * counterVertexZ + 2 * counterVertexX + 0 ] = static_cast< DWORD >( countVertexX * (counterVertexZ + 0) + counterVertexX );
				pIndex[ (2 * countVertexX + 2) * counterVertexZ + 2 * counterVertexX + 1 ] = static_cast< DWORD >( countVertexX * (counterVertexZ + 1) + counterVertexX );
			}
		}
		for( int counterVertexZ = 0; counterVertexZ < countVertexZ - 2; ++counterVertexZ )
		{
			pIndex[ (2 * countVertexX + 2) * (counterVertexZ + 1) - 2 ] = static_cast< DWORD >( countVertexX * (counterVertexZ + 1) + countVertexX - 1 );
			pIndex[ (2 * countVertexX + 2) * (counterVertexZ + 1) - 1 ] = static_cast< DWORD >( countVertexX * (counterVertexZ + 1) );
		}
	}
	else
	{
		// インデックスバッファ更新開始
		WORD	*pIndex = nullptr;		// 書き換え用インデックスバッファアドレス
		pIndexBuffer_->Lock( 0, 0, (void**)&pIndex, 0 );

		// インデックス情報設定
		for( int counterVertexZ = 0; counterVertexZ < countVertexZ - 1; ++counterVertexZ )
		{
			for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
			{
				pIndex[ (2 * countVertexX + 2) * counterVertexZ + 2 * counterVertexX + 0 ] = static_cast< WORD >( countVertexX * (counterVertexZ + 0) + counterVertexX );
				pIndex[ (2 * countVertexX + 2) * counterVertexZ + 2 * counterVertexX + 1 ] = static_cast< WORD >( countVertexX * (counterVertexZ + 1) + counterVertexX );
			}
		}
		for( int counterVertexZ = 0; counterVertexZ < countVertexZ - 2; ++counterVertexZ )
		{
			pIndex[ (2 * countVertexX + 2) * (counterVertexZ + 1) - 2 ] = static_cast< WORD >( countVertexX * (counterVertexZ + 1) + countVertexX - 1 );
			pIndex[ (2 * countVertexX + 2) * (counterVertexZ + 1) - 1 ] = static_cast< WORD >( countVertexX * (counterVertexZ + 1) );
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
int PolygonMesh::Finalize( void )
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
// Arg    : int countCellZ						: Z方向セル数
// Arg    : float lengthCellX					: X方向セル長さ
// Arg    : float lengthCellZ					: Z方向セル長さ
// Arg    : float lengthTextureX				: X方向テクスチャ長さ
// Arg    : float lengthTextureZ				: Z方向テクスチャ長さ
//==============================================================================
int PolygonMesh::Reinitialize( IDirect3DDevice9* pDevice, int countCellX, int countCellZ,
	float lengthCellX, float lengthCellZ, float lengthTextureX, float lengthTextureZ )
{
	// 終了処理
	int		result;		// 実行結果
	result = Finalize();
	if( result != 0 )
	{
		return result;
	}

	// 初期化処理
	return Initialize( pDevice, countCellX, countCellZ, lengthCellX, lengthCellZ, lengthTextureX, lengthTextureZ );
}

//==============================================================================
// Brief  : クラスのコピー
// Return : int									: 実行結果
// Arg    : PolygonMesh* pOut					: コピー先アドレス
//==============================================================================
int PolygonMesh::Copy( PolygonMesh* pOut ) const
{
	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 描画処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PolygonMesh::Draw( void )
{
	// 描画
	pDevice_->SetStreamSource( 0, pVertexBuffer_, 0, pVertex_->GetSize() );
	pDevice_->SetIndices( pIndexBuffer_ );
	pDevice_->SetVertexDeclaration( pVertex_->GetDeclaration() );
	pDevice_->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, 0, 0, countVertex_, 0, countIndex_ - 2 );
}

//==============================================================================
// Brief  : 高さの設定
// Return : int									: 実行結果
// Arg    : float* pHeight						: 高さ情報
//==============================================================================
int PolygonMesh::SetHeight( float* pHeight )
{
	// 頂点の数を計算
	int		countVertexX;		// X方向頂点数
	int		countVertexZ;		// Z方向頂点数
	countVertexX = countCellX_ + 1;
	countVertexZ = countCellZ_ + 1;

	// 法線バッファ確保
	D3DXVECTOR3*	pVectorNormal = nullptr;
	pVectorNormal = new D3DXVECTOR3[ countVertex_ ];
	if( pVectorNormal == NULL )
	{
		return 1;
	}
	ZeroMemory( pVectorNormal, sizeof( D3DXVECTOR3 ) * countVertex_ );

	// 法線の設定
	D3DXVECTOR3	pVectorNormalPlane[ 2 ];		// 法線ベクトル
	D3DXVECTOR3	pVectorPlaneX[ 2 ];				// X方向ベクトル
	D3DXVECTOR3	pVectorPlaneZ[ 2 ];				// Z方向ベクトル
	for( int counterVertexZ = 1; counterVertexZ < countVertexZ - 1; ++counterVertexZ )
	{
		for( int counterVertexX = 1; counterVertexX < countVertexX - 1; ++counterVertexX )
		{
			pVectorPlaneX[ 0 ].x = -lengthCellX_;
			pVectorPlaneX[ 0 ].z = 0.0f;
			pVectorPlaneX[ 0 ].y = pHeight[ countVertexX * counterVertexZ + (counterVertexX + 1) ];
			pVectorPlaneZ[ 0 ].x = 0.0f;
			pVectorPlaneZ[ 0 ].z = lengthCellZ_;
			pVectorPlaneZ[ 0 ].y = pHeight[ countVertexX * (counterVertexZ + 1) + counterVertexX ];
			pVectorPlaneX[ 1 ].x = lengthCellX_;
			pVectorPlaneX[ 1 ].z = 0.0f;
			pVectorPlaneX[ 1 ].y = pHeight[ countVertexX * counterVertexZ + (counterVertexX - 1) ];
			pVectorPlaneZ[ 1 ].x = 0.0f;
			pVectorPlaneZ[ 1 ].z = -lengthCellZ_;
			pVectorPlaneZ[ 1 ].y = pHeight[ countVertexX * (counterVertexZ - 1) + counterVertexX ];
			pVectorPlaneX[ 0 ].y -= pHeight[ countVertexX * counterVertexZ + counterVertexX ];
			pVectorPlaneX[ 1 ].y -= pHeight[ countVertexX * counterVertexZ + counterVertexX ];
			pVectorPlaneZ[ 0 ].y -= pHeight[ countVertexX * counterVertexZ + counterVertexX ];
			pVectorPlaneZ[ 1 ].y -= pHeight[ countVertexX * counterVertexZ + counterVertexX ];
			D3DXVec3Normalize( &pVectorPlaneX[ 0 ], &pVectorPlaneX[ 0 ] );
			D3DXVec3Normalize( &pVectorPlaneX[ 1 ], &pVectorPlaneX[ 1 ] );
			D3DXVec3Normalize( &pVectorPlaneZ[ 0 ], &pVectorPlaneZ[ 0 ] );
			D3DXVec3Normalize( &pVectorPlaneZ[ 1 ], &pVectorPlaneZ[ 1 ] );
			D3DXVec3Cross( &pVectorNormalPlane[ 0 ], &pVectorPlaneX[ 0 ], &pVectorPlaneZ[ 0 ] );
			D3DXVec3Cross( &pVectorNormalPlane[ 1 ], &pVectorPlaneX[ 1 ], &pVectorPlaneZ[ 1 ] );
			D3DXVec3Normalize( &pVectorNormalPlane[ 0 ], &pVectorNormalPlane[ 0 ] );
			D3DXVec3Normalize( &pVectorNormalPlane[ 1 ], &pVectorNormalPlane[ 1 ] );
			pVectorNormalPlane[ 0 ] += pVectorNormalPlane[ 1 ];
			D3DXVec3Normalize( &pVectorNormalPlane[ 0 ], &pVectorNormalPlane[ 0 ] );
			pVectorNormal[ countVertexX * counterVertexZ + counterVertexX ] = pVectorNormalPlane[ 0 ];
		}
	}

	// 端の法線の設定
	for( int counterVertexZ = 1; counterVertexZ < countVertexZ - 1; ++counterVertexZ )
	{
		pVectorNormal[ countVertexX * counterVertexZ ] = pVectorNormal[ countVertexX * counterVertexZ + 1 ];
		pVectorNormal[ countVertexX * counterVertexZ + countVertexX - 1 ] = pVectorNormal[ countVertexX * counterVertexZ + countVertexX - 2 ];
	}
	for( int counterVertexX = 1; counterVertexX < countVertexX - 1; ++counterVertexX )
	{
		pVectorNormal[ counterVertexX ] = pVectorNormal[ countVertexX + counterVertexX ];
		pVectorNormal[ countVertexX * (countVertexZ - 1) + counterVertexX ] = pVectorNormal[ countVertexX * (countVertexZ - 2) + counterVertexX ];
	}
	pVectorNormalPlane[ 0 ] = pVectorNormal[ 1 ] + pVectorNormal[ countVertexX ];
	D3DXVec3Normalize( &pVectorNormal[ 0 ], &pVectorNormalPlane[ 0 ] );
	pVectorNormalPlane[ 0 ] = pVectorNormal[ countVertexX - 2 ] + pVectorNormal[ countVertexX * 2 - 1 ];
	D3DXVec3Normalize( &pVectorNormal[ countVertexX - 1 ], &pVectorNormalPlane[ 0 ] );
	pVectorNormalPlane[ 0 ] = pVectorNormal[ countVertexX * (countVertexZ - 1) + 1 ] + pVectorNormal[ countVertexX * (countVertexZ - 2) ];
	D3DXVec3Normalize( &pVectorNormal[ countVertexX * (countVertexZ - 1) ], &pVectorNormalPlane[ 0 ] );
	pVectorNormalPlane[ 0 ] = pVectorNormal[ countVertexX * (countVertexZ - 1) + countVertexX - 2 ] + pVectorNormal[ countVertexX * (countVertexZ - 2) + countVertexX - 1 ];
	D3DXVec3Normalize( &pVectorNormal[ countVertexX * (countVertexZ - 1) + countVertexX - 1 ], &pVectorNormalPlane[ 0 ] );

	// 頂点バッファ情報を作成
	VertexBuffer	buffer;		// 頂点バッファ情報
	buffer.Initialize( countVertex_, pVertex_ );
	for( int counterVertexZ = 0; counterVertexZ < countVertexZ; ++counterVertexZ )
	{
		for( int counterVertexX = 0; counterVertexX < countVertexX; ++counterVertexX )
		{
			int		indexVertex;		// 頂点の番号
			indexVertex = countVertexX * counterVertexZ + counterVertexX;
			buffer.SetPosition( indexVertex, lengthCellX_ * (counterVertexX - countCellX_ / 2.0f), pHeight[ indexVertex ], lengthCellZ_ * (counterVertexZ - countCellZ_ / 2.0f) );
			buffer.SetNormal( indexVertex, pVectorNormal[ indexVertex ] );
			buffer.SetTextureCoord0( indexVertex, lengthTextureX_ * counterVertexX, lengthTextureZ_ * counterVertexZ );
			buffer.SetColorDiffuse( indexVertex, 1.0f, 1.0f, 1.0f, 1.0f );
		}
	}

	// 法線バッファの破棄
	delete pVectorNormal;
	pVectorNormal = nullptr;

	// 頂点バッファに値を設定
	int		sizeVertex;						// 頂点のサイズ
	void*	pBufferAddress = nullptr;		// バッファのアドレス
	sizeVertex = pVertex_->GetSize();
	pVertexBuffer_->Lock( 0, 0, &pBufferAddress, 0 );
	memcpy_s( pBufferAddress, sizeVertex * countVertex_, buffer.GetBuffer(), sizeVertex * countVertex_ );
	pVertexBuffer_->Unlock();

	// 正常終了
	return 0;
}

//==============================================================================
// Brief  : 頂点数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PolygonMesh::GetCountVertex( void ) const
{
	// 値の返却
	return countVertex_;
}

//==============================================================================
// Brief  : インデックス数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PolygonMesh::GetCountIndex( void ) const
{
	// 値の返却
	return countIndex_;
}

//==============================================================================
// Brief  : インデックスのサイズの取得
// Return : void								: なし
// Arg    : size_t* pOut						: 値の格納アドレス
//==============================================================================
void PolygonMesh::GetSizeIndex( size_t* pOut ) const
{
	// 値の返却
	*pOut = sizeIndex_;
}

//==============================================================================
// Brief  : X方向セル数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PolygonMesh::GetCountCellX( void ) const
{
	// 値の返却
	return countCellX_;
}

//==============================================================================
// Brief  : Z方向セル数の取得
// Return : int									: 返却する値
// Arg    : void								: なし
//==============================================================================
int PolygonMesh::GetCountCellZ( void ) const
{
	// 値の返却
	return countCellZ_;
}

//==============================================================================
// Brief  : X方向セル長さの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void PolygonMesh::SetLengthCellX( float value )
{
	// 値の設定
	lengthCellX_ = value;
}

//==============================================================================
// Brief  : X方向セル長さの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PolygonMesh::GetLengthCellX( void ) const
{
	// 値の返却
	return lengthCellX_;
}

//==============================================================================
// Brief  : Z方向セル長さの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void PolygonMesh::SetLengthCellZ( float value )
{
	// 値の設定
	lengthCellZ_ = value;
}

//==============================================================================
// Brief  : Z方向セル長さの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PolygonMesh::GetLengthCellZ( void ) const
{
	// 値の返却
	return lengthCellZ_;
}

//==============================================================================
// Brief  : X方向テクスチャ長さの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void PolygonMesh::SetLengthTextureX( float value )
{
	// 値の設定
	lengthTextureX_ = value;
}

//==============================================================================
// Brief  : X方向テクスチャ長さの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PolygonMesh::GetLengthTextureX( void ) const
{
	// 値の返却
	return lengthTextureX_;
}

//==============================================================================
// Brief  : Z方向テクスチャ長さの設定
// Return : void								: なし
// Arg    : float value							: 設定する値
//==============================================================================
void PolygonMesh::SetLengthTextureZ( float value )
{
	// 値の設定
	lengthTextureZ_ = value;
}

//==============================================================================
// Brief  : Z方向テクスチャ長さの取得
// Return : float								: 返却する値
// Arg    : void								: なし
//==============================================================================
float PolygonMesh::GetLengthTextureZ( void ) const
{
	// 値の返却
	return lengthTextureZ_;
}

//==============================================================================
// Brief  : クラス内の初期化処理
// Return : void								: なし
// Arg    : void								: なし
//==============================================================================
void PolygonMesh::InitializeSelf( void )
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
	countCellZ_ = 0;
	lengthCellX_ = 0.0f;
	lengthCellZ_ = 0.0f;
	lengthTextureX_ = 1.0f;
	lengthTextureZ_ = 1.0f;
}
